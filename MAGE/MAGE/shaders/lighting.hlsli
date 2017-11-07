#ifndef MAGE_HEADER_LIGHTING
#define MAGE_HEADER_LIGHTING

//-----------------------------------------------------------------------------
// Engine Configuration
//-----------------------------------------------------------------------------
// Defines			                      | Default
//-----------------------------------------------------------------------------
// DISSABLE_DIFFUSE_BRDF                  | not defined
// DISSABLE_SPECULAR_BRDF                 | not defined
// BRDF_F_COMPONENT                       | F_Schlick
// BRDF_D_COMPONENT                       | D_GGX
// BRDF_G_COMPONENT                       | G_GXX
// LIGHT_DISTANCE_ATTENUATION_COMPONENT   | DistanceAttenuation
// LIGHT_ANGULAR_ATTENUATION_COMPONENT    | AngularAttenuation
// FOG_FACTOR_COMPONENT                   | FogFactor_Exponential
// BRDFxCOS                               | not defined
// DISSABLE_AMBIENT_LIGHT                 | not defined
// DISSABLE_DIRECTIONAL_LIGHTS            | not defined
// DISSABLE_OMNI_LIGHTS                   | not defined
// DISSABLE_SPOT_LIGHTS                   | not defined
// DISSABLE_SHADOW_MAPPING                | not defined
// DISSABLE_SHADOW_MAP_DIRECTIONAL_LIGHTS | not defined
// DISSABLE_SHADOW_MAP_OMNI_LIGHTS        | not defined
// DISSABLE_SHADOW_MAP_SPOT_LIGHTS        | not defined
// DISSABLE_FOG                           | not defined

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#include "global.hlsli"
#include "brdf.hlsli"
#include "light.hlsli"

//-----------------------------------------------------------------------------
// Constant Buffers
//-----------------------------------------------------------------------------
CBUFFER(LightBuffer, SLOT_CBUFFER_LIGHTING) {
	// The radiance of the ambient light in the scene. 
	float3 g_La                     : packoffset(c0);
	uint g_padding0                 : packoffset(c0.w);
	// The color of the fog in linear space.
	float3 g_fog_color              : packoffset(c1);
	// The density of the fog.
	float g_fog_density             : packoffset(c1.w);

	// The number of directional lights in the scene.
	uint g_nb_directional_lights    : packoffset(c2.x);
	// The number of omni lights in the scene.
	uint g_nb_omni_lights           : packoffset(c2.y);
	// The number of spotlights in the scene.
	uint g_nb_spot_lights           : packoffset(c2.z);

	// The number of directional lights with shadow mapping in the scene.
	uint g_nb_sm_directional_lights : packoffset(c3.x);
	// The number of omni lights with shadow mapping in the scene.
	uint g_nb_sm_omni_lights        : packoffset(c3.y);
	// The number of spotlights with shadow mapping in the scene.
	uint g_nb_sm_spot_lights        : packoffset(c3.z);
}

//-----------------------------------------------------------------------------
// SRVs
//-----------------------------------------------------------------------------
#ifdef BRDFxCOS

#ifndef DISSABLE_DIRECTIONAL_LIGHTS
STRUCTURED_BUFFER(
	g_directional_lights, DirectionalLight, 
	SLOT_SRV_DIRECTIONAL_LIGHTS);
#endif // DISSABLE_DIRECTIONAL_LIGHTS

#ifndef DISSABLE_OMNI_LIGHTS
STRUCTURED_BUFFER(
	g_omni_lights, OmniLight, 
	SLOT_SRV_OMNI_LIGHTS);
#endif // DISSABLE_OMNI_LIGHTS

#ifndef DISSABLE_SPOT_LIGHTS
STRUCTURED_BUFFER(
	g_spot_lights, SpotLight, 
	SLOT_SRV_SPOT_LIGHTS);
#endif // DISSABLE_SPOT_LIGHTS

#ifndef DISSABLE_SHADOW_MAPPING

#ifndef DISSABLE_SHADOW_MAP_DIRECTIONAL_LIGHTS
STRUCTURED_BUFFER(
	g_sm_directional_lights, DirectionalLightWithShadowMapping, 
	SLOT_SRV_SHADOW_MAP_DIRECTIONAL_LIGHTS);
TEXTURE_2D_ARRAY(
	g_directional_sms, float, 
	SLOT_SRV_DIRECTIONAL_SHADOW_MAPS);
#endif // DISSABLE_SHADOW_MAP_DIRECTIONAL_LIGHTS

#ifndef DISSABLE_SHADOW_MAP_OMNI_LIGHTS
STRUCTURED_BUFFER(
	g_sm_omni_lights, OmniLightWithShadowMapping, 
	SLOT_SRV_SHADOW_MAP_OMNI_LIGHTS);
TEXTURE_CUBE_ARRAY(
	g_omni_sms, float, 
	SLOT_SRV_OMNI_SHADOW_MAPS);
#endif // DISSABLE_SHADOW_MAP_OMNI_LIGHTS

#ifndef DISSABLE_SHADOW_MAP_SPOT_LIGHTS
STRUCTURED_BUFFER(
	g_sm_spot_lights, SpotLightWithShadowMapping, 
	SLOT_SRV_SHADOW_MAP_SPOT_LIGHTS);
TEXTURE_2D_ARRAY(
	g_spot_sms, float, 
	SLOT_SRV_SPOT_SHADOW_MAPS);
#endif // DISSABLE_SHADOW_MAP_SPOT_LIGHTS

#endif // DISSABLE_SHADOW_MAPPING

#endif // BRDFxCOS

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------

// Calculates the BRDF shading.
float3 BRDFShading(float3 p, float3 n, 
	float3 base_color, float roughness, float metalness) {

	const float r_eye = length(p);

#ifndef BRDFxCOS
	float3 L = base_color;
#else // BRDFxCOS
	float3 L = float3(0.0f, 0.0f, 0.0f);

#ifndef DISSABLE_AMBIENT_LIGHT
	// Ambient light contribution
	L += g_La;
#endif // DISSABLE_AMBIENT_LIGHT

	const float3 v = -p / r_eye;

#ifndef DISSABLE_DIRECTIONAL_LIGHTS
	// Directional lights contribution
	for (uint i0 = 0u; i0 < g_nb_directional_lights; ++i0) {
		const DirectionalLight light = g_directional_lights[i0];
		
		float3 l, L_light;
		Contribution(light, l, L_light);

		L += L_light * BRDFxCOS(n, l, v, base_color, roughness, metalness);
	}
#endif // DISSABLE_DIRECTIONAL_LIGHTS

#ifndef DISSABLE_OMNI_LIGHTS
	// Omni lights contribution
	for (uint i1 = 0u; i1 < g_nb_omni_lights; ++i1) {
		const OmniLight light = g_omni_lights[i1];
		
		float3 l, I_light;
		Contribution(light, p, l, I_light);

		L += I_light * BRDFxCOS(n, l, v, base_color, roughness, metalness);
	}
#endif // DISSABLE_OMNI_LIGHTS

#ifndef DISSABLE_SPOT_LIGHTS
	// Spotlights contribution
	for (uint i2 = 0u; i2 < g_nb_spot_lights; ++i2) {
		const SpotLight light = g_spot_lights[i2];
		
		float3 l, I_light;
		Contribution(light, p, l, I_light);

		L += I_light * BRDFxCOS(n, l, v, base_color, roughness, metalness);
	}
#endif // DISSABLE_SPOT_LIGHTS

#ifndef DISSABLE_SHADOW_MAPPING

#ifndef DISSABLE_SHADOW_MAP_DIRECTIONAL_LIGHTS
	// Directional lights with shadow mapping contribution
	for (uint i3 = 0u; i3 < g_nb_sm_directional_lights; ++i3) {
		const DirectionalLightWithShadowMapping light = g_sm_directional_lights[i3];
		
		float3 l, L_light;
		Contribution(light, g_pcf_sampler, g_directional_sms, i3, p, l, L_light);

		L += L_light * BRDFxCOS(n, l, v, base_color, roughness, metalness);
	}
#endif // DISSABLE_SHADOW_MAP_DIRECTIONAL_LIGHTS

#ifndef DISSABLE_SHADOW_MAP_OMNI_LIGHTS
	// Omni lights with shadow mapping contribution
	for (uint i4 = 0u; i4 < g_nb_sm_omni_lights; ++i4) {
		const OmniLightWithShadowMapping light = g_sm_omni_lights[i4];
		
		float3 l, I_light;
		Contribution(light, g_pcf_sampler, g_omni_sms, i4, p, l, I_light);
		
		L += I_light * BRDFxCOS(n, l, v, base_color, roughness, metalness);
	}
#endif // DISSABLE_SHADOW_MAP_OMNI_LIGHTS

#ifndef DISSABLE_SHADOW_MAP_SPOT_LIGHTS
	// Spotlights with shadow mapping contribution
	for (uint i5 = 0u; i5 < g_nb_sm_spot_lights; ++i5) {
		const SpotLightWithShadowMapping light = g_sm_spot_lights[i5];
		
		float3 l, I_light;
		Contribution(light, g_pcf_sampler, g_spot_sms, i5, p, l, I_light);

		L += I_light * BRDFxCOS(n, l, v, base_color, roughness, metalness);
	}
#endif // DISSABLE_SHADOW_MAP_SPOT_LIGHTS

#endif // DISSABLE_SHADOW_MAPPING

#endif // BRDFxCOS

#ifndef DISSABLE_FOG
	const float fog_factor = FOG_FACTOR_COMPONENT(r_eye, g_fog_density);
	L = lerp(g_fog_color, L, fog_factor);
#endif // DISSABLE_FOG
	
	return L;
}

#endif //MAGE_HEADER_LIGHTING