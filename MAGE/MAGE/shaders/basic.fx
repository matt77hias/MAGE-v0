//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#include "vs_input_structures.fx"

//-----------------------------------------------------------------------------
// Transformations
//-----------------------------------------------------------------------------
cbuffer Transform : register(b0) {
	// The object-to-world transformation matrix.
	float4x4 object_to_world					: packoffset(c0);
	// The world-to-view transformation matrix.
	float4x4 world_to_view						: packoffset(c4);
	// The object-to-view inverse transpose transformation matrix.
	float4x4 object_to_view_inverse_transpose	: packoffset(c8);
	// The view-to-projection transformation matrix.
	float4x4 view_to_projection					: packoffset(c12);
}

//-----------------------------------------------------------------------------
// Materials
//-----------------------------------------------------------------------------
Texture2D diffuse_texture_map : register(t0);
Texture2D normal_texture_map  : register(t4);
sampler texture_sampler       : register(s0);

cbuffer Material : register(b1) {
	// The diffuse reflectivity of the material.
	float3 Kd									: packoffset(c0);
	// The dissolve of the material.
	float dissolve								: packoffset(c0.w);
	// The specular reflectivity of the material.
	float3 Ks									: packoffset(c1);
	// The specular exponent of the material.
	float Ns									: packoffset(c1.w);
};

// Calculates the dot product of two vectors and clamp negative values to 0. 
float max_dot(float3 x, float3 y) {
	return max(0.0f, dot(x, y));
}
// Calculates the reflected direction of the given l about the given n.
float3 ReflectedDirection(float3 n, float3 l) {
	return reflect(-l, n);
}
// Calculates the half direction between the given l and given v.
float3 HalfDirection(float3 l, float3 v) {
	// l+v / ||l+v||
	return normalize(l + v);
}

// Calculates the Lambertian BRDF (independent of kd).
float LambertianBRDF(float3 n, float3 l) {
	return max_dot(n, l);
}
// Calculates the (specular) Phong BRDF (independent of ks).
float PhongBRDF(float3 n, float3 l, float3 v) {
	// dot(r, v)^Ns / dot(n, l)
	const float n_dot_l = dot(n, l);
	if (n_dot_l <= 0.0f) {
		return 0.0f;
	}
	const float3 r = ReflectedDirection(n, l);
	return pow(max_dot(r, v), Ns) / n_dot_l;
}
// Calculates the (specular) Modified Blinn-Phong BRDF (independent of ks).
float ModifiedBlinnPhongBRDF(float3 n, float3 l, float3 v) {
	// dot(n, h)^Ns
	const float3 h = HalfDirection(l, v);
	return pow(max_dot(n, h), Ns);
}
// Calculates the (specular) Modified Phong BRDF (independent of ks).
float ModifiedPhongBRDF(float3 n, float3 l, float3 v) {
	// dot(n, h)^Ns * (Ns+2)/2
	return ModifiedBlinnPhongBRDF(n, l, v) * (Ns + 2.0f) / 2.0f;
}
// Calculates the (specular) Blinn-Phong BRDF (independent of ks).
float BlinnPhongBRDF(float3 n, float3 l, float3 v) {
	// dot(n, h)^Ns / dot(n, l)
	const float n_dot_l = dot(n, l);
	if (n_dot_l <= 0.01f) { // Prevents flickering.
		return 0.0f;
	}
	return ModifiedBlinnPhongBRDF(n, l, v) / n_dot_l;
}

// Perturbs the given normal.
float3 TangentSpaceNormalMapping_PerturbNormal(float3 p, float3 n, float2 tex) {
	// Calculates the edge differences.
	const float3 dp_dj = ddx(p);
	const float3 dp_di = ddy(p);
	const float2 dtex_dj = ddx(tex);
	const float2 dtex_di = ddy(tex);

	// Solve the linear system of equations to obtain
	// the cotangents t and b.
	const float3 dp_di_ortho = cross(dp_di, n);
	const float3 dp_dj_ortho = cross(n, dp_dj);
	// t: gradient of texture coordinate u as a function of p.
	const float3 t = dtex_dj.x * dp_di_ortho + dtex_di.x * dp_dj_ortho;
	// b: gradient of texture coordinate v as a function of p.
	const float3 b = dtex_dj.y * dp_di_ortho + dtex_di.y * dp_dj_ortho;

	// Construct a scale-invariant frame.
	const float inv_det = rsqrt(max(dot(t, t), dot(b, b)));
	const float3x3 TBN = { t * inv_det, b * inv_det, n };
	
	float3 coefficients = normal_texture_map.Sample(texture_sampler, tex).xyz;
	coefficients = 2.0f * coefficients - 1.0f;
	return normalize(mul(coefficients, TBN));
}
float3 ObjectSpaceNormalMapping_PerturbNormal(float2 tex) {
	float3 coefficients = normal_texture_map.Sample(texture_sampler, tex).xyz;
	coefficients = 2.0f * coefficients - 1.0f;
	return normalize(mul(coefficients, (float3x3)object_to_view_inverse_transpose));
}

//-----------------------------------------------------------------------------
// Lights
//-----------------------------------------------------------------------------

cbuffer LightData : register(b2) {
	// The intensity of the ambient light. 
	float3 Ia									: packoffset(c0);
	// The number of omni lights.
	uint nb_omnilights							: packoffset(c0.w);
	// The intensity of the directional light.
	float3 Id									: packoffset(c1);
	// The number of spotlights.
	uint nb_spotlights							: packoffset(c1.w);
	// The direction of the directional light in camera space.
	float3 d									: packoffset(c2);
	uint padding								: packoffset(c2.w);
};

struct OmniLight {
	// The position of the omni light in camera space.
	float4 p;
	// The intensity of the omni light.
	float3 I;
	// The distance at which intensity falloff starts.
	float distance_falloff_start;
	// The distance at which intensity falloff ends.
	float distance_falloff_end;
	uint padding[3];
};

struct SpotLight {
	// The position of the spotlight in camera space.
	float4 p;
	// The intensity of the spotlight.
	float3 I;
	// The exponent property of the spotlight.
	float exponent_property;
	// The direction of the spotlight in camera space.
	float3 d;
	// The distance at which intensity falloff starts.
	float distance_falloff_start;
	// The distance at which intensity falloff ends.
	float distance_falloff_end;
	// The cosine of the penumbra angle at which intensity falloff starts.
	float cos_penumbra;
	// The cosine of the umbra angle at which intensity falloff ends.
	float cos_umbra;
	uint padding;
};

StructuredBuffer< OmniLight > omni_lights : register(t1);
StructuredBuffer< SpotLight > spot_lights : register(t2);

// Calculates the distance fall off at a given distance r.
float DistanceFalloff(float r, float r_start, float r_end) {
	return saturate((r_end - r) / (r_end - r_start));
}
// Calculates the angular fall off at a given angle theta.
float AngularFalloff(float cos_theta, float cos_penumbra, float cos_umbra, float s_exp) {
	return pow(saturate((cos_theta - cos_umbra) / (cos_penumbra - cos_umbra)), s_exp);
}

// Calculates the maximum contribution of the given omni light on the given point.
float3 OmniLightMaxContribution(OmniLight light, float3 p) {
	const float r  = distance(light.p.xyz, p);
	const float df = DistanceFalloff(r, light.distance_falloff_start, light.distance_falloff_end);
	return df * light.I;
}
// Calculates the maximum contribution of the given spotlight on the given point.
float3 SpotLightMaxContribution(SpotLight light, float3 p, float3 l) {
	const float r  = distance(light.p.xyz, p);
	const float cos_theta = dot(light.d, -l);
	const float df = DistanceFalloff(r, light.distance_falloff_start, light.distance_falloff_end);
	const float af = AngularFalloff(cos_theta, light.cos_penumbra, light.cos_umbra, light.exponent_property);
	return df * af * light.I;
}

//-----------------------------------------------------------------------------
// Shading
//-----------------------------------------------------------------------------

// Calculates the Lambertian shading.
float4 LambertianBRDFShading(float3 p, float3 n, float2 tex) {
	float3 I_diffuse = float3(0.0f, 0.0f, 0.0f);

	// Ambient light and directional light contribution
	float3 brdf = LambertianBRDF(n, -d);
	I_diffuse = Ia + brdf * Id;

	// Omni lights contribution
	for (uint i = 0; i < nb_omnilights; ++i) {
		const OmniLight light = omni_lights[i];
		const float3 l = normalize(light.p.xyz - p);
		const float3 I_light = OmniLightMaxContribution(light, p);
		
		brdf = LambertianBRDF(n, l);
		I_diffuse += brdf * I_light;
	}
	
	// Spotlights contribution
	for (uint j = 0; j < nb_spotlights; ++j) {
		const SpotLight light = spot_lights[j];
		const float3 l = normalize(light.p.xyz - p);
		const float3 I_light = SpotLightMaxContribution(light, p, l);
		
		brdf = LambertianBRDF(n, l);
		I_diffuse += brdf * I_light;
	}

	float4 I = float4(Kd * I_diffuse, dissolve);
	I *= diffuse_texture_map.Sample(texture_sampler, tex);
	return I;
}
// Calculates the Phong BRDF shading.
float4 PhongBRDFShading(float3 p, float3 n, float2 tex) {
	const float3 v = normalize(-p);

	float3 I_diffuse  = float3(0.0f, 0.0f, 0.0f);
	float3 I_specular = float3(0.0f, 0.0f, 0.0f);

	// Ambient light and directional light contribution
	float3 brdf = LambertianBRDF(n, -d);
	I_diffuse = Ia + brdf * Id;

	// Omni lights contribution
	for (uint i = 0; i < nb_omnilights; ++i) {
		const OmniLight light = omni_lights[i];
		const float3 l = normalize(light.p.xyz - p);
		const float3 I_light = OmniLightMaxContribution(light, p);

		brdf = LambertianBRDF(n, l);
		I_diffuse += brdf * I_light;

		brdf = PhongBRDF(n, l, v);
		I_specular += brdf * I_light;
	}

	// Spotlights contribution
	for (uint j = 0; j < nb_spotlights; ++j) {
		const SpotLight light = spot_lights[j];
		const float3 l = normalize(light.p.xyz - p);
		const float3 I_light = SpotLightMaxContribution(light, p, l);

		brdf = LambertianBRDF(n, l);
		I_diffuse += brdf * I_light;

		brdf = PhongBRDF(n, l, v);
		I_specular += brdf * I_light;
	}

	float4 I = float4(Kd * I_diffuse, dissolve);
	I *= diffuse_texture_map.Sample(texture_sampler, tex);
	I.xyz += Ks * I_specular;
	return I;
}
// Calculates the Modified Phong BRDF shading.
float4 ModifiedPhongBRDFShading(float3 p, float3 n, float2 tex) {
	const float3 v = normalize(-p);

	float3 I_diffuse  = float3(0.0f, 0.0f, 0.0f);
	float3 I_specular = float3(0.0f, 0.0f, 0.0f);

	// Ambient light and directional light contribution
	float3 brdf = LambertianBRDF(n, -d);
	I_diffuse = Ia + brdf * Id;

	// Omni lights contribution
	for (uint i = 0; i < nb_omnilights; ++i) {
		const OmniLight light = omni_lights[i];
		const float3 l = normalize(light.p.xyz - p);
		const float3 I_light = OmniLightMaxContribution(light, p);

		brdf = LambertianBRDF(n, l);
		I_diffuse += brdf * I_light;

		brdf = ModifiedPhongBRDF(n, l, v);
		I_specular += brdf * I_light;
	}

	// Spotlights contribution
	for (uint j = 0; j < nb_spotlights; ++j) {
		const SpotLight light = spot_lights[j];
		const float3 l = normalize(light.p.xyz - p);
		const float3 I_light = SpotLightMaxContribution(light, p, l);

		brdf = LambertianBRDF(n, l);
		I_diffuse += brdf * I_light;

		brdf = ModifiedPhongBRDF(n, l, v);
		I_specular += brdf * I_light;
	}

	float4 I = float4(Kd * I_diffuse, dissolve);
	I *= diffuse_texture_map.Sample(texture_sampler, tex);
	I.xyz += Ks * I_specular;
	return I;
}
// Calculates the Blinn-Phong BRDF shading.
float4 BlinnPhongBRDFShading(float3 p, float3 n, float2 tex) {
	const float3 v = normalize(-p);

	float3 I_diffuse  = float3(0.0f, 0.0f, 0.0f);
	float3 I_specular = float3(0.0f, 0.0f, 0.0f);

	// Ambient light and directional light contribution
	float3 brdf = LambertianBRDF(n, -d);
	I_diffuse = Ia + brdf * Id;

	// Omni lights contribution
	for (uint i = 0; i < nb_omnilights; ++i) {
		const OmniLight light = omni_lights[i];
		const float3 l = normalize(light.p.xyz - p);
		const float3 I_light = OmniLightMaxContribution(light, p);

		brdf = LambertianBRDF(n, l);
		I_diffuse += brdf * I_light;

		brdf = BlinnPhongBRDF(n, l, v);
		I_specular += brdf * I_light;
	}

	// Spotlights contribution
	for (uint j = 0; j < nb_spotlights; ++j) {
		const SpotLight light = spot_lights[j];
		const float3 l = normalize(light.p.xyz - p);
		const float3 I_light = SpotLightMaxContribution(light, p, l);

		brdf = LambertianBRDF(n, l);
		I_diffuse += brdf * I_light;

		brdf = BlinnPhongBRDF(n, l, v);
		I_specular += brdf * I_light;
	}

	float4 I = float4(Kd * I_diffuse, dissolve);
	I *= diffuse_texture_map.Sample(texture_sampler, tex);
	I.xyz += Ks * I_specular;
	return I;
}
// Calculates the Modified Blinn-Phong BRDF shading.
float4 ModifiedBlinnPhongBRDFShading(float3 p, float3 n, float2 tex) {
	const float3 v = normalize(-p);

	float3 I_diffuse  = float3(0.0f, 0.0f, 0.0f);
	float3 I_specular = float3(0.0f, 0.0f, 0.0f);

	// Ambient light and directional light contribution
	float3 brdf = LambertianBRDF(n, -d);
	I_diffuse = Ia + brdf * Id;

	// Omni lights contribution
	for (uint i = 0; i < nb_omnilights; ++i) {
		const OmniLight light = omni_lights[i];
		const float3 l = normalize(light.p.xyz - p);
		const float3 I_light = OmniLightMaxContribution(light, p);

		brdf = LambertianBRDF(n, l);
		I_diffuse += brdf * I_light;

		brdf = ModifiedBlinnPhongBRDF(n, l, v);
		I_specular += brdf * I_light;
	}

	// Spotlights contribution
	for (uint j = 0; j < nb_spotlights; ++j) {
		const SpotLight light = spot_lights[j];
		const float3 l = normalize(light.p.xyz - p);
		const float3 I_light = SpotLightMaxContribution(light, p, l);

		brdf = LambertianBRDF(n, l);
		I_diffuse += brdf * I_light;

		brdf = ModifiedBlinnPhongBRDF(n, l, v);
		I_specular += brdf * I_light;
	}

	float4 I = float4(Kd * I_diffuse, dissolve);
	I *= diffuse_texture_map.Sample(texture_sampler, tex);
	I.xyz += Ks * I_specular;
	return I;
}

//-----------------------------------------------------------------------------
// Input structures
//-----------------------------------------------------------------------------

struct PS_INPUT {
	float4 p      : SV_POSITION;
	float4 p_view : POSITION0;
	float3 n_view : NORMAL0;
	float2 tex    : TEXCOORD0;
};

//-----------------------------------------------------------------------------
// Vertex Shaders
//-----------------------------------------------------------------------------

PS_INPUT Transform_VS(VertexPositionNormalTexture_VS_INPUT input) {
	PS_INPUT output = (PS_INPUT)0;
	output.p_view   = mul(input.p, object_to_world);
	output.p_view   = mul(output.p_view, world_to_view);
	output.p        = mul(output.p_view, view_to_projection);
	output.tex      = input.tex;
	output.n_view   = normalize(mul(input.n, (float3x3)object_to_view_inverse_transpose));
	return output;
}

PS_INPUT Normal_VS(VertexPositionNormalTexture_VS_INPUT input) {
	PS_INPUT output = (PS_INPUT)0;
	output.n_view   = input.n;
	return output;
}

//-----------------------------------------------------------------------------
// Pixel Shaders
//-----------------------------------------------------------------------------

float4 Diffuse_PS(PS_INPUT input) : SV_Target {
	const float4 I = float4(Kd, dissolve);
	return diffuse_texture_map.Sample(texture_sampler, input.tex) * I;
}

float4 Lambertian_PS(PS_INPUT input) : SV_Target {
	const float3 p = input.p_view.xyz;
	return LambertianBRDFShading(p, input.n_view, input.tex);
}
float4 Phong_PS(PS_INPUT input) : SV_Target {
	const float3 p = input.p_view.xyz;
	return PhongBRDFShading(p, input.n_view, input.tex);
}
float4 ModifiedPhong_PS(PS_INPUT input) : SV_Target{
	const float3 p = input.p_view.xyz;
	return ModifiedPhongBRDFShading(p, input.n_view, input.tex);
}
float4 BlinnPhong_PS(PS_INPUT input) : SV_Target {
	const float3 p = input.p_view.xyz;
	return BlinnPhongBRDFShading(p, input.n_view, input.tex);
}
float4 ModifiedBlinnPhong_PS(PS_INPUT input) : SV_Target {
	const float3 p = input.p_view.xyz;
	return ModifiedBlinnPhongBRDFShading(p, input.n_view, input.tex);
}
float4 Normal_PS(PS_INPUT input) : SV_Target {
	return float4(0.5f + 0.5f * input.n_view, 1.0f);
}

float4 TangentSpaceNormalMapping_Lambertian_PS(PS_INPUT input) : SV_Target {
	const float3 p = input.p_view.xyz;
	const float3 n = TangentSpaceNormalMapping_PerturbNormal(p, input.n_view, input.tex);
	return LambertianBRDFShading(p, n, input.tex);
}
float4 TangentSpaceNormalMapping_Phong_PS(PS_INPUT input) : SV_Target {
	const float3 p = input.p_view.xyz;
	const float3 n = TangentSpaceNormalMapping_PerturbNormal(p, input.n_view, input.tex);
	return PhongBRDFShading(p, n, input.tex);
}
float4 TangentSpaceNormalMapping_ModifiedPhong_PS(PS_INPUT input) : SV_Target{
	const float3 p = input.p_view.xyz;
	const float3 n = TangentSpaceNormalMapping_PerturbNormal(p, input.n_view, input.tex);
	return ModifiedPhongBRDFShading(p, n, input.tex);
}
float4 TangentSpaceNormalMapping_BlinnPhong_PS(PS_INPUT input) : SV_Target {
	const float3 p = input.p_view.xyz;
	const float3 n = TangentSpaceNormalMapping_PerturbNormal(p, input.n_view, input.tex);
	return BlinnPhongBRDFShading(p, n, input.tex);
}
float4 TangentSpaceNormalMapping_ModifiedBlinnPhong_PS(PS_INPUT input) : SV_Target {
	const float3 p = input.p_view.xyz;
	const float3 n = TangentSpaceNormalMapping_PerturbNormal(p, input.n_view, input.tex);
	return ModifiedBlinnPhongBRDFShading(p, n, input.tex);
}
float4 TangentSpaceNormalMapping_Normal_PS(PS_INPUT input) : SV_Target {
	const float3 p = input.p_view.xyz;
	const float3 n = TangentSpaceNormalMapping_PerturbNormal(p, input.n_view, input.tex);
	return float4(0.5f + 0.5f * n, 1.0f);
}

float4 ObjectSpaceNormalMapping_Lambertian_PS(PS_INPUT input) : SV_Target {
	const float3 p = input.p_view.xyz;
	const float3 n = ObjectSpaceNormalMapping_PerturbNormal(input.tex);
	return LambertianBRDFShading(p, n, input.tex);
}
float4 ObjectSpaceNormalMapping_Phong_PS(PS_INPUT input) : SV_Target {
	const float3 p = input.p_view.xyz;
	const float3 n = ObjectSpaceNormalMapping_PerturbNormal(input.tex);
	return PhongBRDFShading(p, n, input.tex);
}
float4 ObjectSpaceNormalMapping_ModifiedPhong_PS(PS_INPUT input) : SV_Target{
	const float3 p = input.p_view.xyz;
	const float3 n = ObjectSpaceNormalMapping_PerturbNormal(input.tex);
	return ModifiedPhongBRDFShading(p, n, input.tex);
}
float4 ObjectSpaceNormalMapping_BlinnPhong_PS(PS_INPUT input) : SV_Target {
	const float3 p = input.p_view.xyz;
	const float3 n = ObjectSpaceNormalMapping_PerturbNormal(input.tex);
	return BlinnPhongBRDFShading(p, n, input.tex);
}
float4 ObjectSpaceNormalMapping_ModifiedBlinnPhong_PS(PS_INPUT input) : SV_Target {
	const float3 p = input.p_view.xyz;
	const float3 n = ObjectSpaceNormalMapping_PerturbNormal(input.tex);
	return ModifiedBlinnPhongBRDFShading(p, n, input.tex);
}
float4 ObjectSpaceNormalMapping_Normal_PS(PS_INPUT input) : SV_Target {
	const float3 p = input.p_view.xyz;
	const float3 n = ObjectSpaceNormalMapping_PerturbNormal(input.tex);
	return float4(0.5f + 0.5f * n, 1.0f);
}

float4 Distance_PS(PS_INPUT input) : SV_Target{
	const float c = 1.0f - saturate(length(input.p_view) / 5.0f);
	return float4(c, c, c, 1.0f);
}