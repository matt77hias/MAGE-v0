//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#include "structures.fx"
#include "light.fx"

//-----------------------------------------------------------------------------
// Scene
//-----------------------------------------------------------------------------

cbuffer Scene : register(b0) {
	// The world-to-view transformation matrix.
	float4x4 g_world_to_view					: packoffset(c0);
	// The view-to-projection transformation matrix.
	float4x4 g_view_to_projection				: packoffset(c4);
	
	// The intensity of the ambient light in the scene. 
	float3 g_Ia									: packoffset(c8);
	// The global flags.
	uint g_flags								: packoffset(c8.w);
	// The number of directional lights in the scene.
	uint g_nb_directional_lights				: packoffset(c9.x);
	// The number of omni lights in the scene.
	uint g_nb_omni_lights						: packoffset(c9.y);
	// The number of spotlights in the scene.
	uint g_nb_spot_lights						: packoffset(c9.z);
	
	// The distance at which intensity falloff starts due to fog.
	float g_fog_distance_falloff_start			: packoffset(c9.w);
	// The color of the fog.
	float3 g_fog_color							: packoffset(c10);
	// The distance range where intensity falloff occurs due to fog.
	float g_fog_distance_falloff_range			: packoffset(c10.w);
};

StructuredBuffer< DirectionalLight > g_directional_lights : register(t0);
StructuredBuffer< OmniLight > g_omni_lights               : register(t1);
StructuredBuffer< SpotLight > g_spot_lights               : register(t2);
sampler g_sampler										  : register(s0);

//-----------------------------------------------------------------------------
// Model
//-----------------------------------------------------------------------------
cbuffer Model : register(b1) {
	// The object-to-world transformation matrix.
	float4x4 g_object_to_world					: packoffset(c0);
	// The object-to-view inverse transpose transformation matrix.
	float4x4 g_object_to_view_inverse_transpose	: packoffset(c4);

	// The diffuse reflectivity + dissolve of the material
	float4 g_Kd									: packoffset(c8);
	// The specular reflectivity of the material.
	float3 g_Ks									: packoffset(c9);
	// The specular exponent of the material.
	float g_Ns									: packoffset(c9.w);
	// The extra material parameter of the material.
	float4 g_material_parameters				: packoffset(c10);
}

Texture2D g_diffuse_texture : register(t3);
Texture2D g_specular_texture : register(t4);
Texture2D g_normal_texture  : register(t5);

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#include "brdf.fx"
#include "normal_mapping.fx"

//-----------------------------------------------------------------------------
// Shading
//-----------------------------------------------------------------------------

// Calculates the BRDF shading.
float4 BRDFShading(float3 p, float3 n, float2 tex) {
	float4 I = g_Kd * g_diffuse_texture.Sample(g_sampler, tex);
	//clip(I.a - 0.1f);
	
	const float r_eye = length(p);

#ifndef DISSABLE_BRDFxCOS

	// Ambient light contribution
	float3 Id = g_Ia;
#ifdef SPECULAR_BRDFxCOS
	float3 Is = float3(0.0f, 0.0f, 0.0f);
#endif

	const float3 v = -p / r_eye;

	// Directional lights contribution
	for (uint i = 0; i < g_nb_directional_lights; ++i) {
		const DirectionalLight light = g_directional_lights[i];
		const float3 l        = -light.d;
		const float3 I_light  = light.I;

		const float fd = LambertianBRDFxCos(n, l);
		Id += fd * I_light;

#ifdef SPECULAR_BRDFxCOS
		const float fs = SPECULAR_BRDFxCOS(n, l, v);
		Is += fs * I_light;
#endif
	}

	// Omni lights contribution
	for (uint j = 0; j < g_nb_omni_lights; ++j) {
		const OmniLight light = g_omni_lights[j];
		const float3 d_light  = light.p - p;
		const float r_light   = length(d_light);
		const float3 l        = d_light / r_light;
		const float3 I_light  = OmniLightMaxContribution(light, r_light);

		const float fd = LambertianBRDFxCos(n, l);
		Id += fd * I_light;

#ifdef SPECULAR_BRDFxCOS
		const float fs = SPECULAR_BRDFxCOS(n, l, v);
		Is += fs * I_light;
#endif
	}

	// Spotlights contribution
	for (uint k = 0; k < g_nb_spot_lights; ++k) {
		const SpotLight light = g_spot_lights[k];
		const float3 d_light  = light.p - p;
		const float r_light   = length(d_light);
		const float3 l        = d_light / r_light;
		const float3 I_light  = SpotLightMaxContribution(light, r_light, l);

		const float fd = LambertianBRDFxCos(n, l);
		Id += fd * I_light;

#ifdef SPECULAR_BRDFxCOS
		const float fs = SPECULAR_BRDFxCOS(n, l, v);
		Is += fs * I_light;
#endif
	}

	I.xyz *= Id;
#ifdef SPECULAR_BRDFxCOS
	I.xyz += g_Ks * Is;
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

float4 TangentSpaceNormalMapping_PS(PSInputPositionNormalTexture input) : SV_Target {
	const float3 p_view = input.p_view.xyz;
	const float3 n0     = normalize(input.n_view);
	const float3 n_view = TangentSpaceNormalMapping_PerturbNormal(p_view, n0, input.tex);
	return BRDFShading(p_view, n_view, input.tex);
}

float4 ObjectSpaceNormalMapping_PS(PSInputPositionNormalTexture input) : SV_Target {
	const float3 p_view = input.p_view.xyz;
	const float3 n_view = ObjectSpaceNormalMapping_PerturbNormal(input.tex);
	return BRDFShading(p_view, n_view, input.tex);
}