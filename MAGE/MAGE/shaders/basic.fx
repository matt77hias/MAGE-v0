//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#include "structures.fx"
#include "light.fx"

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
	// The first material parameter of the material.
	float material_param1						: packoffset(c2.x);
	// The second material parameter of the material.
	float material_param2						: packoffset(c2.y);
	// The thirth material parameter of the material.
	float material_param3						: packoffset(c2.z);
	// The fourth material parameter of the material.
	float material_param4						: packoffset(c2.w);
};

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

#include "brdf.fx"
#include "normal_mapping.fx"

StructuredBuffer< OmniLight > omni_lights : register(t1);
StructuredBuffer< SpotLight > spot_lights : register(t2);

//-----------------------------------------------------------------------------
// Shading
//-----------------------------------------------------------------------------

// Calculates the BRDF shading.
float4 BRDFShading(float3 p, float3 n, float2 tex) {
	float4 I = float4(Kd, dissolve) * diffuse_texture_map.Sample(texture_sampler, tex);
	clip(I.a - 0.1f);

	// Ambient light and directional light contribution
	float3 brdf = LambertianBRDF(n, -d);
	float3 I_diffuse = Ia + brdf * Id;
#ifdef SPECULAR_BRDF
	float3 I_specular = float3(0.0f, 0.0f, 0.0f);
#endif

	const float3 v = normalize(-p);

	// Omni lights contribution
	for (uint i = 0; i < nb_omnilights; ++i) {
		const OmniLight light = omni_lights[i];
		const float3 l = normalize(light.p.xyz - p);
		const float3 I_light = OmniLightMaxContribution(light, p);

		brdf = LambertianBRDF(n, l);
		I_diffuse  += brdf * I_light;

#ifdef SPECULAR_BRDF
		brdf = SPECULAR_BRDF(n, l, v);
		I_specular += brdf * I_light;
#endif
	}

	// Spotlights contribution
	for (uint j = 0; j < nb_spotlights; ++j) {
		const SpotLight light = spot_lights[j];
		const float3 l = normalize(light.p.xyz - p);
		const float3 I_light = SpotLightMaxContribution(light, p, l);

		brdf = LambertianBRDF(n, l);
		I_diffuse  += brdf * I_light;

#ifdef SPECULAR_BRDF
		brdf = SPECULAR_BRDF(n, l, v);
		I_specular += brdf * I_light;
#endif
	}

	I.xyz *= I_diffuse;
#ifdef SPECULAR_BRDF
	I.xyz += Ks * I_specular;
#endif
	return I;
}

//-----------------------------------------------------------------------------
// Vertex Shaders
//-----------------------------------------------------------------------------

PSInputPositionNormalTexture Transform_VS(VSInputPositionNormalTexture input) {
	PSInputPositionNormalTexture output = (PSInputPositionNormalTexture)0;
	output.p_view = mul(input.p, object_to_world);
	output.p_view = mul(output.p_view, world_to_view);
	output.p      = mul(output.p_view, view_to_projection);
	output.tex    = input.tex;
	// Normalization in PS after interpolation
	output.n_view = mul(input.n, (float3x3)object_to_view_inverse_transpose);
	return output;
}

PSInputPositionNormalTexture Normal_VS(VSInputPositionNormalTexture input) {
	PSInputPositionNormalTexture output = (PSInputPositionNormalTexture)0;
	output.p_view = mul(input.p, object_to_world);
	output.p_view = mul(output.p_view, world_to_view);
	output.p      = mul(output.p_view, view_to_projection);
	output.n_view = input.n;
	return output;
}

//-----------------------------------------------------------------------------
// Pixel Shaders
//-----------------------------------------------------------------------------

float4 Emissive_PS(PSInputPositionNormalTexture input) : SV_Target {
	return float4(Kd, dissolve) * diffuse_texture_map.Sample(texture_sampler, input.tex);
}

float4 Basic_PS(PSInputPositionNormalTexture input) : SV_Target {
	const float3 p_view = input.p_view.xyz;
	const float3 n_view = normalize(input.n_view);
	return BRDFShading(p_view, n_view, input.tex);
}
float4 Basic_Normal_PS(PSInputPositionNormalTexture input) : SV_Target {
	const float3 n_view = normalize(input.n_view);
	return float4(0.5f + 0.5f * n_view, 1.0f);
}

float4 TangentSpaceNormalMapping_PS(PSInputPositionNormalTexture input) : SV_Target {
	const float3 p_view = input.p_view.xyz;
	const float3 n0     = normalize(input.n_view);
	const float3 n_view = TangentSpaceNormalMapping_PerturbNormal(p_view, n0, input.tex);
	return BRDFShading(p_view, n_view, input.tex);
}
float4 TangentSpaceNormalMapping_Normal_PS(PSInputPositionNormalTexture input) : SV_Target {
	const float3 p_view = input.p_view.xyz;
	const float3 n0     = normalize(input.n_view);
	const float3 n_view = TangentSpaceNormalMapping_PerturbNormal(p_view, n0, input.tex);
	return float4(0.5f + 0.5f * n_view, 1.0f);
}

float4 ObjectSpaceNormalMapping_PS(PSInputPositionNormalTexture input) : SV_Target {
	const float3 p_view = input.p_view.xyz;
	const float3 n_view = ObjectSpaceNormalMapping_PerturbNormal(input.tex);
	return BRDFShading(p_view, n_view, input.tex);
}
float4 ObjectSpaceNormalMapping_Normal_PS(PSInputPositionNormalTexture input) : SV_Target {
	const float3 p_view = input.p_view.xyz;
	const float3 n_view = ObjectSpaceNormalMapping_PerturbNormal(input.tex);
	return float4(0.5f + 0.5f * n_view, 1.0f);
}

float4 Distance_PS(PSInputPositionNormalTexture input) : SV_Target{
	const float3 p_view = input.p_view.xyz;
	const float c = 1.0f - saturate(length(p_view) / 5.0f);
	return float4(c, c, c, 1.0f);
}