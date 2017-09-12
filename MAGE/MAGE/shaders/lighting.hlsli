#ifndef MAGE_HEADER_LIGHTING
#define MAGE_HEADER_LIGHTING

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#include "hlsl.hpp"
#include "brdf.hlsli"
#include "light.hlsli"

//-----------------------------------------------------------------------------
// Constant Buffers
//-----------------------------------------------------------------------------
cbuffer LightBuffer : register(REG_B(SLOT_CBUFFER_LIGHTING)) {
	// LIGHTING
	// The intensity of the ambient light in the scene. 
	float3 g_Ia                            : packoffset(c0);

	// The number of directional lights in the scene.
	uint g_nb_directional_lights           : packoffset(c1.x);
	// The number of omni lights in the scene.
	uint g_nb_omni_lights                  : packoffset(c1.y);
	// The number of spotlights in the scene.
	uint g_nb_spot_lights                  : packoffset(c1.z);

	// The number of directional lights with shadow mapping in the scene.
	uint g_nb_sm_directional_lights        : packoffset(c2.x);
	// The number of omni lights with shadow mapping in the scene.
	uint g_nb_sm_omni_lights               : packoffset(c2.y);
	// The number of spotlights with shadow mapping in the scene.
	uint g_nb_sm_spot_lights               : packoffset(c2.z);

	// FOGGING
	// The distance at which intensity falloff starts due to fog.
	float g_fog_distance_falloff_start     : packoffset(c2.w);
	// The color of the fog.
	float3 g_fog_color                     : packoffset(c3);
	// The distance inverse range where intensity falloff occurs due to fog.
	float g_fog_distance_falloff_inv_range : packoffset(c3.w);
}

//-----------------------------------------------------------------------------
// Structured Buffers
//-----------------------------------------------------------------------------
#ifndef DISSABLE_BRDFxCOS

#ifndef DISSABLE_DIRECTIONAL_LIGHTS
StructuredBuffer< DirectionalLight > g_directional_lights 
	: register(REG_T(SLOT_SRV_DIRECTIONAL_LIGHTS));
#endif // DISSABLE_DIRECTIONAL_LIGHTS

#ifndef DISSABLE_OMNI_LIGHTS
StructuredBuffer< OmniLight > g_omni_lights               
	: register(REG_T(SLOT_SRV_OMNI_LIGHTS));
#endif // DISSABLE_OMNI_LIGHTS

#ifndef DISSABLE_SPOT_LIGHTS
StructuredBuffer< SpotLight > g_spot_lights               
	: register(REG_T(SLOT_SRV_SPOT_LIGHTS));
#endif // DISSABLE_SPOT_LIGHTS

#ifndef DISSABLE_SHADOW_MAPPING

#ifndef DISSABLE_SHADOW_MAP_DIRECTIONAL_LIGHTS
StructuredBuffer< DirectionalLightWithShadowMapping > g_sm_directional_lights
	: register(REG_T(SLOT_SRV_SHADOW_MAP_DIRECTIONAL_LIGHTS));
Texture2DArray g_directional_sms
	: register(REG_T(SLOT_SRV_DIRECTIONAL_SHADOW_MAPS));
#endif // DISSABLE_SHADOW_MAP_DIRECTIONAL_LIGHTS

#ifndef DISSABLE_SHADOW_MAP_OMNI_LIGHTS
StructuredBuffer< OmniLightWithShadowMapping > g_sm_omni_lights
	: register(REG_T(SLOT_SRV_SHADOW_MAP_OMNI_LIGHTS));
TextureCubeArray g_omni_sms
	: register(REG_T(SLOT_SRV_OMNI_SHADOW_MAPS));
#endif // DISSABLE_SHADOW_MAP_OMNI_LIGHTS

#ifndef DISSABLE_SHADOW_MAP_SPOT_LIGHTS
StructuredBuffer< SpotLightWithShadowMapping > g_sm_spot_lights
	: register(REG_T(SLOT_SRV_SHADOW_MAP_SPOT_LIGHTS));
Texture2DArray g_spot_sms
	: register(REG_T(SLOT_SRV_SPOT_SHADOW_MAPS));
#endif // DISSABLE_SHADOW_MAP_SPOT_LIGHTS

#endif // DISSABLE_SHADOW_MAPPING

#endif // DISSABLE_BRDFxCOS

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------

#ifdef TWO_BRDF_COEFFICIENTS
#define BRDF_COEFFICIENTS mat1, mat2
#else  // TWO_BRDF_COEFFICIENTS
#define BRDF_COEFFICIENTS mat1
#endif // TWO_BRDF_COEFFICIENTS

// Calculates the BRDF shading.
float3 BRDFShading(float3 p, float3 n, float3 Kd, float3 Ks, float mat1, float mat2) {
	float3 I = Kd;
	const float r_eye = length(p);

#ifndef DISSABLE_BRDFxCOS

#ifdef DISSABLE_AMBIENT_LIGHT
	float3 Id = float3(0.0f, 0.0f, 0.0f);
#else  // DISSABLE_AMBIENT_LIGHT
	// Ambient light contribution
	float3 Id = g_Ia;
#endif // DISSABLE_AMBIENT_LIGHT

#ifdef SPECULAR_BRDFxCOS
	float3 Is = float3(0.0f, 0.0f, 0.0f);
#endif // SPECULAR_BRDFxCOS

	const float3 v = -p / r_eye;

#ifndef DISSABLE_DIRECTIONAL_LIGHTS
	// Directional lights contribution
	for (uint i0 = 0; i0 < g_nb_directional_lights; ++i0) {
		const DirectionalLight light = g_directional_lights[i0];
		const float3 l        = light.neg_d;
		const float3 I_light  = light.I;

		const float fd = LambertianBRDFxCos(n, l);
		Id += fd * I_light;

#ifdef SPECULAR_BRDFxCOS
		const float fs = SPECULAR_BRDFxCOS(n, l, v, BRDF_COEFFICIENTS);
		Is += fs * I_light;
#endif // SPECULAR_BRDFxCOS
	}
#endif // DISSABLE_DIRECTIONAL_LIGHTS

#ifndef DISSABLE_OMNI_LIGHTS
	// Omni lights contribution
	for (uint i1 = 0; i1 < g_nb_omni_lights; ++i1) {
		const OmniLight light = g_omni_lights[i1];
		const float3 d_light  = light.p - p;
		const float r_light   = length(d_light);
		const float3 l        = d_light / r_light;
		const float3 I_light  = MaxContribution(light, r_light);

		const float fd = LambertianBRDFxCos(n, l);
		Id += fd * I_light;

#ifdef SPECULAR_BRDFxCOS
		const float fs = SPECULAR_BRDFxCOS(n, l, v, BRDF_COEFFICIENTS);
		Is += fs * I_light;
#endif // SPECULAR_BRDFxCOS
	}
#endif // DISSABLE_OMNI_LIGHTS

#ifndef DISSABLE_SPOT_LIGHTS
	// Spotlights contribution
	for (uint i2 = 0; i2 < g_nb_spot_lights; ++i2) {
		const SpotLight light = g_spot_lights[i2];
		const float3 d_light  = light.p - p;
		const float r_light   = length(d_light);
		const float3 l        = d_light / r_light;
		const float3 I_light  = MaxContribution(light, r_light, l);

		const float fd = LambertianBRDFxCos(n, l);
		Id += fd * I_light;

#ifdef SPECULAR_BRDFxCOS
		const float fs = SPECULAR_BRDFxCOS(n, l, v, BRDF_COEFFICIENTS);
		Is += fs * I_light; // SPECULAR_BRDFxCOS
#endif
	}
#endif // DISSABLE_SPOT_LIGHTS

#ifndef DISSABLE_SHADOW_MAPPING

#ifndef DISSABLE_SHADOW_MAP_DIRECTIONAL_LIGHTS
	// Directional lights with shadow mapping contribution
	for (uint i3 = 0; i3 < g_nb_sm_directional_lights; ++i3) {
		const DirectionalLightWithShadowMapping sm_light = g_sm_directional_lights[i3];
		const DirectionalLight light = sm_light.light;
		const float3 l        = light.neg_d;
		const float3 I_light  = light.I;

		const float fd = LambertianBRDFxCos(n, l);
		Id += fd * I_light;

#ifdef SPECULAR_BRDFxCOS
		const float fs = SPECULAR_BRDFxCOS(n, l, v, BRDF_COEFFICIENTS);
		Is += fs * I_light;
#endif // SPECULAR_BRDFxCOS
	}
#endif // DISSABLE_SHADOW_MAP_DIRECTIONAL_LIGHTS

#ifndef DISSABLE_SHADOW_MAP_OMNI_LIGHTS
	// Omni lights with shadow mapping contribution
	for (uint i4 = 0; i4 < g_nb_sm_omni_lights; ++i4) {
		const OmniLightWithShadowMapping sm_light = g_sm_omni_lights[i4];
		const OmniLight light = sm_light.light;
		const float3 d_light  = light.p - p;
		const float r_light   = length(d_light);
		const float3 l        = d_light / r_light;
		const float3 I_light  = MaxContribution(light, r_light);

		const float fd = LambertianBRDFxCos(n, l);
		Id += fd * I_light;

#ifdef SPECULAR_BRDFxCOS
		const float fs = SPECULAR_BRDFxCOS(n, l, v, BRDF_COEFFICIENTS);
		Is += fs * I_light;
#endif // SPECULAR_BRDFxCOS
	}
#endif // DISSABLE_SHADOW_MAP_OMNI_LIGHTS

#ifndef DISSABLE_SHADOW_MAP_SPOT_LIGHTS
	// Spotlights with shadow mapping contribution
	for (uint i5 = 0; i5 < g_nb_sm_spot_lights; ++i5) {
		const SpotLightWithShadowMapping sm_light = g_sm_spot_lights[i5];
		const SpotLight light = sm_light.light;
		const float3 d_light  = light.p - p;
		const float r_light   = length(d_light);
		const float3 l        = d_light / r_light;
		const float3 I_light  = MaxContribution(light, r_light, l);

		const float fd = LambertianBRDFxCos(n, l);
		Id += fd * I_light;

#ifdef SPECULAR_BRDFxCOS
		const float fs = SPECULAR_BRDFxCOS(n, l, v, BRDF_COEFFICIENTS);
		Is += fs * I_light; // SPECULAR_BRDFxCOS
#endif
	}
#endif // DISSABLE_SHADOW_MAP_SPOT_LIGHTS

#endif // DISSABLE_SHADOW_MAPPING

	I *= Id;
#ifdef SPECULAR_BRDFxCOS
	I += Ks * Is;
#endif // SPECULAR_BRDFxCOS

#endif // DISSABLE_BRDFxCOS

#ifndef DISSABLE_FOG
	const float fog_factor = saturate((r_eye - g_fog_distance_falloff_start) * g_fog_distance_falloff_inv_range);
	I = lerp(I, g_fog_color, fog_factor);
#endif // DISSABLE_FOG
	
	return I;
}

#endif //MAGE_HEADER_LIGHTING