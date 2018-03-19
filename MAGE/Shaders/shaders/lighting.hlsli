#ifndef MAGE_HEADER_LIGHTING
#define MAGE_HEADER_LIGHTING

//-----------------------------------------------------------------------------
// Engine Configuration
//-----------------------------------------------------------------------------
// Defines			                        | Default
//-----------------------------------------------------------------------------
// DISABLE_DIFFUSE_BRDF                     | not defined
// DISABLE_SPECULAR_BRDF                    | not defined
// BRDF_F_COMPONENT                         | F_Schlick
// BRDF_D_COMPONENT                         | D_GGX
// BRDF_G_COMPONENT                         | G_GXX
// BRDF_MINIMUM_ALPHA                       | 0.1f
// BRDF_DOT_EPSILON                         | 0.00001f
// LIGHT_DISTANCE_ATTENUATION_COMPONENT     | DistanceAttenuation
// LIGHT_ANGULAR_ATTENUATION_COMPONENT      | AngularAttenuation
// FOG_FACTOR_COMPONENT                     | FogFactor_Exponential
// BRDFxCOS_COMPONENT                       | not defined
// DISABLE_AMBIENT_LIGHT                    | not defined
// DISABLE_DIRECTIONAL_LIGHTS               | not defined
// DISABLE_OMNI_LIGHTS                      | not defined
// DISABLE_SPOT_LIGHTS                      | not defined
// DISABLE_SHADOW_MAPPING                   | not defined
// DISABLE_SHADOW_MAPPED_DIRECTIONAL_LIGHTS | not defined
// DISABLE_SHADOW_MAPPED_OMNI_LIGHTS        | not defined
// DISABLE_SHADOW_MAPPED_SPOT_LIGHTS        | not defined
// DISABLE_FOG                              | not defined
// DISABLE_VCT                              | not defined

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#include "global.hlsli"

#ifdef BRDFxCOS_COMPONENT
	#include "brdf.hlsli"
#endif // BRDFxCOS_COMPONENT

#include "light.hlsli"

#ifndef DISABLE_VCT
	#include "vct.hlsli"
#endif // DISABLE_VCT

//-----------------------------------------------------------------------------
// Constant Buffers
//-----------------------------------------------------------------------------
CBUFFER(LightBuffer, SLOT_CBUFFER_LIGHTING) {
	
	//-------------------------------------------------------------------------
	// Member Variables: Lights without Shadow Mapping
	//-------------------------------------------------------------------------

	// The number of directional lights in the scene.
	uint g_nb_directional_lights    : packoffset(c0.x);
	// The number of omni lights in the scene.
	uint g_nb_omni_lights           : packoffset(c0.y);
	// The number of spotlights in the scene.
	uint g_nb_spot_lights           : packoffset(c0.z);

	//-------------------------------------------------------------------------
	// Member Variables: Lights with Shadow Mapping
	//-------------------------------------------------------------------------

	// The number of shaodw mapped directional lights in the scene.
	uint g_nb_sm_directional_lights : packoffset(c1.x);
	// The number of shaodw mapped omni lights in the scene.
	uint g_nb_sm_omni_lights        : packoffset(c1.y);
	// The number of shaodw mapped spotlights in the scene.
	uint g_nb_sm_spot_lights        : packoffset(c1.z);

	//-------------------------------------------------------------------------
	// Member Variables: Ambient Light
	//-------------------------------------------------------------------------

	// The radiance of the ambient light in the scene. 
	float3 g_La                     : packoffset(c2);
}

//-----------------------------------------------------------------------------
// SRVs
//-----------------------------------------------------------------------------
#ifdef BRDFxCOS_COMPONENT

#ifndef DISABLE_DIRECTIONAL_LIGHTS
STRUCTURED_BUFFER(g_directional_lights, DirectionalLight, 
				  SLOT_SRV_DIRECTIONAL_LIGHTS);
#endif // DISABLE_DIRECTIONAL_LIGHTS

#ifndef DISABLE_OMNI_LIGHTS
STRUCTURED_BUFFER(g_omni_lights, OmniLight, 
				  SLOT_SRV_OMNI_LIGHTS);
#endif // DISABLE_OMNI_LIGHTS

#ifndef DISABLE_SPOT_LIGHTS
STRUCTURED_BUFFER(g_spot_lights, SpotLight, 
				  SLOT_SRV_SPOT_LIGHTS);
#endif // DISABLE_SPOT_LIGHTS

#ifndef DISABLE_SHADOW_MAPPING

#ifndef DISABLE_SHADOW_MAPPED_DIRECTIONAL_LIGHTS
STRUCTURED_BUFFER(g_sm_directional_lights, ShadowMappedDirectionalLight, 
				  SLOT_SRV_SHADOW_MAPPED_DIRECTIONAL_LIGHTS);
TEXTURE_2D_ARRAY(g_directional_sms, float, 
				 SLOT_SRV_DIRECTIONAL_SHADOW_MAPS);
#endif // DISABLE_SHADOW_MAPPED_DIRECTIONAL_LIGHTS

#ifndef DISABLE_SHADOW_MAPPED_OMNI_LIGHTS
STRUCTURED_BUFFER(g_sm_omni_lights, ShadowMappedOmniLight, 
				  SLOT_SRV_SHADOW_MAPPED_OMNI_LIGHTS);
TEXTURE_CUBE_ARRAY(g_omni_sms, float, 
				   SLOT_SRV_OMNI_SHADOW_MAPS);
#endif // DISABLE_SHADOW_MAPPED_OMNI_LIGHTS

#ifndef DISABLE_SHADOW_MAPPED_SPOT_LIGHTS
STRUCTURED_BUFFER(g_sm_spot_lights, ShadowMappedSpotLight, 
				  SLOT_SRV_SHADOW_MAPPED_SPOT_LIGHTS);
TEXTURE_2D_ARRAY(g_spot_sms, float, 
				 SLOT_SRV_SPOT_SHADOW_MAPS);
#endif // DISABLE_SHADOW_MAPPED_SPOT_LIGHTS

#endif // DISABLE_SHADOW_MAPPING

#ifndef DISABLE_VCT
TEXTURE_3D(g_voxel_texture, float4, SLOT_SRV_VOXEL_TEXTURE);
#endif // DISABLE_VCT

#endif // BRDFxCOS_COMPONENT

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------

float3 GetDirectRadiance(float3 p, float3 n, 
						 float3 base_color, float roughness, float metalness) {

	const float3 v_direction = GetCameraPosition() - p;
	const float  v_distance  = length(v_direction);

	#ifndef BRDFxCOS_COMPONENT
	float3 L = base_color;
	#else // BRDFxCOS_COMPONENT
	float3 L = 0.0f;

	#ifndef DISABLE_AMBIENT_LIGHT
	// Ambient light contribution
	L += g_La;
	#endif // DISABLE_AMBIENT_LIGHT

	const float inv_v_distance = 1.0f / v_distance;
	const float3 v = v_direction * inv_v_distance;

	#ifndef DISABLE_DIRECTIONAL_LIGHTS
	// Directional lights contribution
	for (uint i0 = 0u; i0 < g_nb_directional_lights; ++i0) {
		const DirectionalLight light = g_directional_lights[i0];
		
		float3 l, E;
		Contribution(light, l, E);

		L += E * BRDFxCOS_COMPONENT(n, l, v, base_color, roughness, metalness);
	}
	#endif // DISABLE_DIRECTIONAL_LIGHTS

	#ifndef DISABLE_OMNI_LIGHTS
	// Omni lights contribution
	for (uint i1 = 0u; i1 < g_nb_omni_lights; ++i1) {
		const OmniLight light = g_omni_lights[i1];
		
		float3 l, E;
		Contribution(light, p, l, E);

		L += E * BRDFxCOS_COMPONENT(n, l, v, base_color, roughness, metalness);
	}
	#endif // DISABLE_OMNI_LIGHTS

	#ifndef DISABLE_SPOT_LIGHTS
	// Spotlights contribution
	for (uint i2 = 0u; i2 < g_nb_spot_lights; ++i2) {
		const SpotLight light = g_spot_lights[i2];
		
		float3 l, E;
		Contribution(light, p, l, E);

		L += E * BRDFxCOS_COMPONENT(n, l, v, base_color, roughness, metalness);
	}
	#endif // DISABLE_SPOT_LIGHTS

	#ifndef DISABLE_SHADOW_MAPPING

	#ifndef DISABLE_SHADOW_MAPPED_DIRECTIONAL_LIGHTS
	// Directional lights with shadow mapping contribution
	for (uint i3 = 0u; i3 < g_nb_sm_directional_lights; ++i3) {
		const ShadowMappedDirectionalLight light = g_sm_directional_lights[i3];
		
		float3 l, E;
		Contribution(light, g_pcf_sampler, g_directional_sms, i3, p, l, E);

		L += E * BRDFxCOS_COMPONENT(n, l, v, base_color, roughness, metalness);
	}
	#endif // DISABLE_SHADOW_MAPPED_DIRECTIONAL_LIGHTS

	#ifndef DISABLE_SHADOW_MAPPED_OMNI_LIGHTS
	// Omni lights with shadow mapping contribution
	for (uint i4 = 0u; i4 < g_nb_sm_omni_lights; ++i4) {
		const ShadowMappedOmniLight light = g_sm_omni_lights[i4];
		
		float3 l, E;
		Contribution(light, g_pcf_sampler, g_omni_sms, i4, p, l, E);
		
		L += E * BRDFxCOS_COMPONENT(n, l, v, base_color, roughness, metalness);
	}
	#endif // DISABLE_SHADOW_MAPPED_OMNI_LIGHTS

	#ifndef DISABLE_SHADOW_MAPPED_SPOT_LIGHTS
	// Spotlights with shadow mapping contribution
	for (uint i5 = 0u; i5 < g_nb_sm_spot_lights; ++i5) {
		const ShadowMappedSpotLight light = g_sm_spot_lights[i5];
		
		float3 l, E;
		Contribution(light, g_pcf_sampler, g_spot_sms, i5, p, l, E);

		L += E * BRDFxCOS_COMPONENT(n, l, v, base_color, roughness, metalness);
	}
	#endif // DISABLE_SHADOW_MAPPED_SPOT_LIGHTS

	#endif // DISABLE_SHADOW_MAPPING

	#endif // BRDFxCOS_COMPONENT

	#ifndef DISABLE_FOG
	const float fog_factor = FOG_FACTOR_COMPONENT(v_distance, g_fog_density);
	L = lerp(g_fog_color, L, fog_factor);
	#endif // DISABLE_FOG
	
	return L;
}

float3 GetIndirectRadiance(float3 p) {
	#ifndef BRDFxCOS_COMPONENT
	return 0.0f;
	#else  // BRDFxCOS_COMPONENT

	#ifdef DISABLE_VCT
	return 0.0f;
	#else  // DISABLE_VCT
	const int3 s_index = WorldToVoxelIndex(p);
	return g_voxel_texture[s_index].xyz;
	#endif // DISABLE_VCT

	#endif // BRDFxCOS_COMPONENT
}

float3 GetRadiance(float3 p, float3 n,
				   float3 base_color, float roughness, float metalness) {

	#ifdef DISABLE_VCT
	const float3 L_direct   = GetDirectRadiance(p, n, base_color, 
												roughness, metalness);
	const float3 L_indirect = GetIndirectRadiance(p);
	
	return L_direct + L_indirect;
	#else  // DISABLE_VCT
	return GetIndirectRadiance(p); // debugging
	#endif // DISABLE_VCT
}

#endif //MAGE_HEADER_LIGHTING