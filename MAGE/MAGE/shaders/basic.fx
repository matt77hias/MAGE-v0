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
	float4x4 g_object_to_world					: packoffset(c0);
	// The world-to-view transformation matrix.
	float4x4 g_world_to_view					: packoffset(c4);
	// The object-to-view inverse transpose transformation matrix.
	float4x4 g_object_to_view_inverse_transpose	: packoffset(c8);
	// The view-to-projection transformation matrix.
	float4x4 g_view_to_projection				: packoffset(c12);
}

//-----------------------------------------------------------------------------
// Materials
//-----------------------------------------------------------------------------
Texture2D g_diffuse_texture : register(t0);
Texture2D g_normal_texture  : register(t4);
sampler g_sampler			: register(s0);

cbuffer Material : register(b1) {
	// The diffuse reflectivity + dissolve of the material
	float4 g_Kd									: packoffset(c0);
	// The specular reflectivity of the material.
	float3 g_Ks									: packoffset(c1);
	// The specular exponent of the material.
	float g_Ns									: packoffset(c1.w);
	// The extra material parameter of the material.
	float4 g_material_parameters				: packoffset(c2);
};

//-----------------------------------------------------------------------------
// Scene
//-----------------------------------------------------------------------------

cbuffer Scene : register(b2) {
	// The intensity of the ambient light. 
	float3 g_Ia									: packoffset(c0);
	// The number of omni lights.
	uint g_nb_omnilights						: packoffset(c0.w);
	// The intensity of the directional light.
	float3 g_Id									: packoffset(c1);
	// The number of spotlights.
	uint g_nb_spotlights						: packoffset(c1.w);
	// The direction of the directional light in camera-space coordinates.
	float3 g_d									: packoffset(c2);
	// The distance at which intensity falloff starts due to fog.
	float g_fog_distance_falloff_start			: packoffset(c2.w);
	// The color of the fog.
	float3 g_fog_color							: packoffset(c3);
	// The distance range where intensity falloff occurs due to fog.
	float g_fog_distance_falloff_range			: packoffset(c3.w);
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
	float4 I = g_Kd * g_diffuse_texture.Sample(g_sampler, tex);
	//clip(I.a - 0.1f);
	
	const float r_eye = length(p);

#ifndef DISSABLE_BRDFxCOS
	// Ambient light and directional light contribution
	float3 brdf_cos = LambertianBRDFxCos(n, -g_d);
	float3 I_diffuse = g_Ia + brdf_cos * g_Id;
#ifdef SPECULAR_BRDFxCOS
	float3 I_specular = float3(0.0f, 0.0f, 0.0f);
#endif

	const float3 v = -p / r_eye;

	// Omni lights contribution
	for (uint i = 0; i < g_nb_omnilights; ++i) {
		const OmniLight light = omni_lights[i];
		const float3 d_light  = light.p.xyz - p;
		const float r_light   = length(d_light);
		const float3 l        = d_light / r_light;
		const float3 I_light  = OmniLightMaxContribution(light, r_light);

		brdf_cos = LambertianBRDFxCos(n, l);
		I_diffuse  += brdf_cos * I_light;

#ifdef SPECULAR_BRDFxCOS
		brdf_cos = SPECULAR_BRDFxCOS(n, l, v);
		I_specular += brdf_cos * I_light;
#endif
	}

	// Spotlights contribution
	for (uint j = 0; j < g_nb_spotlights; ++j) {
		const SpotLight light = spot_lights[j];
		const float3 d_light  = light.p.xyz - p;
		const float r_light   = length(d_light);
		const float3 l        = d_light / r_light;
		const float3 I_light  = SpotLightMaxContribution(light, r_light, l);

		brdf_cos = LambertianBRDFxCos(n, l);
		I_diffuse  += brdf_cos * I_light;

#ifdef SPECULAR_BRDFxCOS
		brdf_cos = SPECULAR_BRDFxCOS(n, l, v);
		I_specular += brdf_cos * I_light;
#endif
	}

	I.xyz *= I_diffuse;
#ifdef SPECULAR_BRDFxCOS
	I.xyz += g_Ks * I_specular;
#endif
#endif

#ifndef DISSABLE_FOG
	const float fog_factor = saturate((r_eye - g_fog_distance_falloff_start) / g_fog_distance_falloff_range);
	I.xyz = lerp(I.xyz, g_fog_color, fog_factor);
#endif
	
	return I;
}

//-----------------------------------------------------------------------------
// Vertex Shaders
//-----------------------------------------------------------------------------

PSInputPositionNormalTexture Transform_VS(VSInputPositionNormalTexture input) {
	PSInputPositionNormalTexture output = (PSInputPositionNormalTexture)0;
	output.p_view = mul(input.p, g_object_to_world);
	output.p_view = mul(output.p_view, g_world_to_view);
	output.p      = mul(output.p_view, g_view_to_projection);
	output.tex    = input.tex;
	output.n_view = normalize(mul(input.n, (float3x3)g_object_to_view_inverse_transpose));
	return output;
}

PSInputPositionNormalTexture Normal_VS(VSInputPositionNormalTexture input) {
	PSInputPositionNormalTexture output = (PSInputPositionNormalTexture)0;
	output.p_view = mul(input.p, g_object_to_world);
	output.p_view = mul(output.p_view, g_world_to_view);
	output.p      = mul(output.p_view, g_view_to_projection);
	output.n_view = input.n;
	return output;
}

//-----------------------------------------------------------------------------
// Pixel Shaders
//-----------------------------------------------------------------------------

float4 Basic_PS(PSInputPositionNormalTexture input) : SV_Target {
	const float3 p_view = input.p_view.xyz;
	const float3 n_view = normalize(input.n_view);
	return BRDFShading(p_view, n_view, input.tex);
}
float4 Basic_Normal_PS(PSInputPositionNormalTexture input) : SV_Target {
	const float3 n_view = normalize(input.n_view);
	return float4(InverseBiasX2(n_view), 1.0f);
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
	return float4(InverseBiasX2(n_view), 1.0f);
}

float4 ObjectSpaceNormalMapping_PS(PSInputPositionNormalTexture input) : SV_Target {
	const float3 p_view = input.p_view.xyz;
	const float3 n_view = ObjectSpaceNormalMapping_PerturbNormal(input.tex);
	return BRDFShading(p_view, n_view, input.tex);
}
float4 ObjectSpaceNormalMapping_Normal_PS(PSInputPositionNormalTexture input) : SV_Target {
	const float3 n_view = ObjectSpaceNormalMapping_PerturbNormal(input.tex);
	return float4(InverseBiasX2(n_view), 1.0f);
}

float4 Distance_PS(PSInputPositionNormalTexture input) : SV_Target{
	const float3 p_view = input.p_view.xyz;
	const float c = 1.0f - saturate(length(p_view) / 5.0f);
	return float4(c, c, c, 1.0f);
}