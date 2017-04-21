//-----------------------------------------------------------------------------
// Transformations
//-----------------------------------------------------------------------------
cbuffer Transform : register(b0) {
	matrix model_to_world;
	matrix world_to_view;
	matrix world_to_view_inverse_transpose;
	matrix view_to_projection;
}

//-----------------------------------------------------------------------------
// Materials
//-----------------------------------------------------------------------------
Texture2D diffuse_texture_map : register(t0);
sampler texture_sampler       : register(s0);

cbuffer Material : register(b1) {
	float3 Kd;						// The diffuse reflectivity of the material.
	float  dissolve;				// The dissolve of the material.
	float3 Ks;						// The specular reflectivity of the material.
	float  Ns;						// The specular exponent of the material.
};

// Calculates the reflected direction of the given l about the given n.
float3 ReflectedDirection(float3 n, float3 l) {
	return reflect(-l, n);
}
// Calculates the half direction between the v (0,0,-1) and given l.
float3 HalfDirection(float3 l) {
	l.z -= 1.0f;
	return normalize(l);
}

// Calculates the Lambertian BRDF (independent of kd).
float LambertianBRDF(float3 n, float3 l) {
	return max(0.0f, dot(n, l));
}
// Calculates the Phong BRDF (independent of ks).
float PhongBRDF(float3 n, float3 l) {
	const float3 r = ReflectedDirection(n, l);
	return max(0.0f, pow(-r.z, Ns) / dot(n, l));
}
// Calculates the Blinn-Phong BRDF (independent of ks).
float BlinnPhongBRDF(float3 n, float3 l) {
	const float3 h = HalfDirection(l);
	return max(0.0f, pow(dot(n, h), Ns) / dot(n, l));
}
// Calculates the Modified Blinn-Phong BRDF (independent of ks).
float ModifiedBlinnPhongBRDF(float3 n, float3 l) {
	const float3 h = HalfDirection(l);
	return pow(max(0.0f, dot(n, h)), Ns);
}

//-----------------------------------------------------------------------------
// Lights
//-----------------------------------------------------------------------------

cbuffer LightData : register(b2) {
	float3 Ia;						// The intensity of the ambient light. 
	uint   nb_omnilights;			// The number of omni lights.
	float3 Id;						// The intensity of the directional light.
	uint   nb_spotlights;			// The number of spotlights.
	float3 d;						// The direction of the directional light in camera space.
};

struct OmniLight {
	float4 p;						// The position of the omni light in camera space.
	float3 I;						// The intensity of the omni light.
	float  distance_falloff_start;	// The distance at which intensity falloff starts.
	float  distance_falloff_end;	// The distance at which intensity falloff ends.
};

struct SpotLight {
	float4 p;						// The position of the spotlight in camera space.
	float3 I;						// The intensity of the spotlight.
	float  exponent_property;		// The exponent property of the spotlight.
	float3 d;						// The direction of the spotlight in camera space.
	float  distance_falloff_start;	// The distance at which intensity falloff starts.
	float  distance_falloff_end;	// The distance at which intensity falloff ends.
	float  cos_penumbra;			// The cosine of the penumbra angle at which intensity falloff starts.
	float  cos_umbra;				// The cosine of the umbra angle at which intensity falloff ends.
};

StructuredBuffer< OmniLight > omni_lights : register(b3);
StructuredBuffer< SpotLight > spot_lights : register(b4);

// Calculates the distance fall off at a given distance r.
float DistanceFalloff(float r, float r_start, float r_end) {
	return saturate((r_end - r) / (r_end - r_start));
}
// Calculates the angular fall off at a given angle theta.
float AngularFalloff(float cos_theta, float cos_penumbra, float cos_umbra, float s_exp) {
	float result;
	if (cos_theta >= cos_penumbra) {
		result = 1.0f;
	}
	else if (cos_theta <= cos_umbra) {
		result =  0.0f;
	}
	else {
		result = pow((cos_theta - cos_umbra) / (cos_penumbra - cos_umbra), s_exp);
	}
	return result;
}

// Calculates the maximum contribution of the given omni light on the given point.
float3 OmniLightMaxContribution(OmniLight light, float4 p) {
	const float r  = distance(light.p, p);
	const float df = DistanceFalloff(r, light.distance_falloff_start, light.distance_falloff_end);
	return df * light.I;
}
// Calculates the maximum contribution of the given spotlight on the given point.
float3 SpotLightMaxContribution(SpotLight light, float4 p, float3 l) {
	const float r  = distance(light.p, p);
	const float cos_theta = dot(light.d, -l);
	const float df = DistanceFalloff(r, light.distance_falloff_start, light.distance_falloff_end);
	const float af = AngularFalloff(cos_theta, light.cos_penumbra, light.cos_umbra, light.exponent_property);
	return df * af * light.I;
}

//-----------------------------------------------------------------------------
// Shading
//-----------------------------------------------------------------------------

// Calculates the Lambertian shading.
float4 LambertianBRDFShading(float4 p, float3 n, float2 tex) {

	float3 I_diffuse  = float3(0.0f, 0.0f, 0.0f);

	// Ambient light and directional light contribution
	float3 brdf = LambertianBRDF(n, -d);
	I_diffuse = Ia + brdf * Id;

	// Omni lights contribution
	for (uint i = 0; i < nb_omnilights; ++i) {
		const OmniLight light = omni_lights[i];
		const float3 l = normalize(light.p - p).xyz;
		const float3 I_light = OmniLightMaxContribution(light, p);
		
		brdf = LambertianBRDF(n, l);
		I_diffuse += brdf * I_light;
	}
	
	// Spotlights contribution
	for (uint j = 0; j < nb_spotlights; ++j) {
		const SpotLight light = spot_lights[j];
		const float3 l = normalize(light.p - p).xyz;
		const float3 I_light = SpotLightMaxContribution(light, p, l);
		
		brdf = LambertianBRDF(n, l);
		I_diffuse += brdf * I_light;
	}

	float4 I = float4(0.0f, 0.0f, 0.0f, dissolve);
	I.xyz = Kd * I_diffuse;
	I *= diffuse_texture_map.Sample(texture_sampler, tex);
	return I;
}
// Calculates the Phong BRDF shading.
float4 PhongBRDFShading(float4 p, float3 n, float2 tex) {

	float3 I_diffuse = float3(0.0f, 0.0f, 0.0f);
	float3 I_specular = float3(0.0f, 0.0f, 0.0f);

	// Ambient light and directional light contribution
	float3 brdf = LambertianBRDF(n, -d);
	I_diffuse = Ia + brdf * Id;

	// Omni lights contribution
	for (uint i = 0; i < nb_omnilights; ++i) {
		const OmniLight light = omni_lights[i];
		const float3 l = normalize(light.p - p).xyz;
		const float3 I_light = OmniLightMaxContribution(light, p);

		brdf = LambertianBRDF(n, l);
		I_diffuse += brdf * I_light;

		brdf = PhongBRDF(n, l);
		I_specular += brdf * I_light;
	}

	// Spotlights contribution
	for (uint j = 0; j < nb_spotlights; ++j) {
		const SpotLight light = spot_lights[j];
		const float3 l = normalize(light.p - p).xyz;
		const float3 I_light = SpotLightMaxContribution(light, p, l);

		brdf = LambertianBRDF(n, l);
		I_diffuse += brdf * I_light;

		brdf = PhongBRDF(n, l);
		I_specular += brdf * I_light;
	}

	float4 I = float4(0.0f, 0.0f, 0.0f, dissolve);
	I.xyz = Kd * I_diffuse;
	I *= diffuse_texture_map.Sample(texture_sampler, tex);
	I.xyz += Ks * I_specular;
	return I;
}
// Calculates the Blinn-Phong BRDF shading.
float4 BlinnPhongBRDFShading(float4 p, float3 n, float2 tex) {

	float3 I_diffuse = float3(0.0f, 0.0f, 0.0f);
	float3 I_specular = float3(0.0f, 0.0f, 0.0f);

	// Ambient light and directional light contribution
	float3 brdf = LambertianBRDF(n, -d);
	I_diffuse = Ia + brdf * Id;

	// Omni lights contribution
	for (uint i = 0; i < nb_omnilights; ++i) {
		const OmniLight light = omni_lights[i];
		const float3 l = normalize(light.p - p).xyz;
		const float3 I_light = OmniLightMaxContribution(light, p);

		brdf = LambertianBRDF(n, l);
		I_diffuse += brdf * I_light;

		brdf = BlinnPhongBRDF(n, l);
		I_specular += brdf * I_light;
	}

	// Spotlights contribution
	for (uint j = 0; j < nb_spotlights; ++j) {
		const SpotLight light = spot_lights[j];
		const float3 l = normalize(light.p - p).xyz;
		const float3 I_light = SpotLightMaxContribution(light, p, l);

		brdf = LambertianBRDF(n, l);
		I_diffuse += brdf * I_light;

		brdf = BlinnPhongBRDF(n, l);
		I_specular += brdf * I_light;
	}

	float4 I = float4(0.0f, 0.0f, 0.0f, dissolve);
	I.xyz = Kd * I_diffuse;
	I *= diffuse_texture_map.Sample(texture_sampler, tex);
	I.xyz += Ks * I_specular;
	return I;
}
// Calculates the Modified Blinn-Phong BRDF shading.
float4 ModifiedBlinnPhongBRDFShading(float4 p, float3 n, float2 tex) {

	float3 I_diffuse  = float3(0.0f, 0.0f, 0.0f);
	float3 I_specular = float3(0.0f, 0.0f, 0.0f);

	// Ambient light and directional light contribution
	float3 brdf = LambertianBRDF(n, -d);
	I_diffuse = Ia + brdf * Id;

	// Omni lights contribution
	for (uint i = 0; i < nb_omnilights; ++i) {
		const OmniLight light = omni_lights[i];
		const float3 l = normalize(light.p - p).xyz;
		const float3 I_light = OmniLightMaxContribution(light, p);

		brdf = LambertianBRDF(n, l);
		I_diffuse += brdf * I_light;

		brdf = ModifiedBlinnPhongBRDF(n, l);
		I_specular += brdf * I_light;
	}

	// Spotlights contribution
	for (uint j = 0; j < nb_spotlights; ++j) {
		const SpotLight light = spot_lights[j];
		const float3 l = normalize(light.p - p).xyz;
		const float3 I_light = SpotLightMaxContribution(light, p, l);

		brdf = LambertianBRDF(n, l);
		I_diffuse += brdf * I_light;

		brdf = ModifiedBlinnPhongBRDF(n, l);
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
struct VS_INPUT {
	float4 p   : POSITION;
	float3 n   : NORMAL;
	float2 tex : TEXCOORD0;
};

struct PS_INPUT {
	float4 p      : SV_POSITION;
	float4 p_view : POSITION;
	float3 n_view : NORMAL;
	float2 tex    : TEXCOORD0;
};

//-----------------------------------------------------------------------------
// Vertex Shader
//-----------------------------------------------------------------------------
PS_INPUT VS(VS_INPUT input) {
	PS_INPUT output = (PS_INPUT)0;
	output.p_view   = mul(input.p, model_to_world);
	output.p_view   = mul(output.p_view, world_to_view);
	output.p        = mul(output.p_view, view_to_projection);
	output.tex      = input.tex;
	output.n_view   = mul(input.n, (float3x3)world_to_view_inverse_transpose);
	return output;
}

//-----------------------------------------------------------------------------
// Pixel Shader
//-----------------------------------------------------------------------------
float4 PS(PS_INPUT input) : SV_Target {

	//return float4(float3(0.5f, 0.5f, 0.5f) + 0.5 * input.n_view, 0.0f);

	return PhongBRDFShading(input.p_view, input.n_view, input.tex);

	//const float4 I = float4(Kd, dissolve);
	//return diffuse_texture_map.Sample(texture_sampler, input.tex) * I;
}