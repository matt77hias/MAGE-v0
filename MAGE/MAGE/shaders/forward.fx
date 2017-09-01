//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#include "light.fx"

//-----------------------------------------------------------------------------
// Constant Buffers
//-----------------------------------------------------------------------------
cbuffer PerFrame : register(b0) {
	// The view-to-projection transformation matrix.
	float4x4 g_view_to_projection          : packoffset(c0);
	
	// The intensity of the ambient light in the scene. 
	float3 g_Ia                            : packoffset(c4);
	// The global flags.
	uint g_flags                           : packoffset(c4.w);
	// The number of directional lights in the scene.
	uint g_nb_directional_lights           : packoffset(c5.x);
	// The number of omni lights in the scene.
	uint g_nb_omni_lights                  : packoffset(c5.y);
	// The number of spotlights in the scene.
	uint g_nb_spot_lights                  : packoffset(c5.z);
	
	// The distance at which intensity falloff starts due to fog.
	float g_fog_distance_falloff_start     : packoffset(c5.w);
	// The color of the fog.
	float3 g_fog_color                     : packoffset(c6);
	// The distance inverse range where intensity falloff occurs due to fog.
	float g_fog_distance_falloff_inv_range : packoffset(c6.w);
};

cbuffer PerDraw : register(b1) {
	// The object-to-view transformation matrix.
	float4x4 g_object_to_view              : packoffset(c0);
	// The object-to-view inverse transpose transformation matrix
	// = The normal-to-view transformation matrix.
	float4x4 g_normal_to_view              : packoffset(c4);
	// The texture transformation matrix.
	float4x4 g_texture_transform           : packoffset(c8);
	// The diffuse reflectivity + dissolve of the material
	float4 g_Kd                            : packoffset(c12);
	// The specular reflectivity of the material.
	float3 g_Ks                            : packoffset(c13);
	// The specular exponent of the material.
	float g_Ns                             : packoffset(c13.w);
	// The extra material parameter of the material.
	float4 g_material_parameters           : packoffset(c14);
}

//-----------------------------------------------------------------------------
// Samplers
//-----------------------------------------------------------------------------
sampler g_sampler : register(s0);

//-----------------------------------------------------------------------------
// Structured Buffers
//-----------------------------------------------------------------------------
StructuredBuffer< DirectionalLight > g_directional_lights : register(t0);
StructuredBuffer< OmniLight > g_omni_lights               : register(t1);
StructuredBuffer< SpotLight > g_spot_lights               : register(t2);

//-----------------------------------------------------------------------------
// Textures
//-----------------------------------------------------------------------------
Texture2D g_diffuse_texture  : register(t3);
Texture2D g_specular_texture : register(t4);
Texture2D g_normal_texture   : register(t5);

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#include "transform.fx"
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
		const float3 l        = light.neg_d;
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
	const float fog_factor = saturate((r_eye - g_fog_distance_falloff_start) * g_fog_distance_falloff_inv_range);
	I.xyz = lerp(I.xyz, g_fog_color, fog_factor);
#endif
	
	return I;
}

//-----------------------------------------------------------------------------
// Pixel Shaders
//-----------------------------------------------------------------------------
float4 PS(PSInputPositionNormalTexture input) : SV_Target {
#ifdef TSNM
	const float3 n0     = normalize(input.n_view);
	const float3 n_view = TangentSpaceNormalMapping_PerturbNormal(input.p_view, n0, input.tex2);
#else
	const float3 n_view = normalize(input.n_view);
#endif
	return BRDFShading(input.p_view, n_view, input.tex);
}