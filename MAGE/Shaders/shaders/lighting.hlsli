#ifndef MAGE_HEADER_LIGHTING
#define MAGE_HEADER_LIGHTING

//-----------------------------------------------------------------------------
// Engine Configuration
//-----------------------------------------------------------------------------
// Defines			                        | Default
//-----------------------------------------------------------------------------
// BRDF_DOT_EPSILON                         | 0.00001f
// BRDF_D_FUNCTION                          | D_GGX
// BRDF_FUNCTION                            | not defined
// BRDF_F_FUNCTION                          | F_Schlick
// BRDF_G_FUNCTION                          | G_GXX
// BRDF_MINIMUM_ALPHA                       | 0.1f
// DISABLE_BRDF_DIFFUSE                     | not defined
// DISABLE_BRDF_SPECULAR                    | not defined
// DISABLE_FOG                              | not defined
// DISABLE_LIGHTS_AMBIENT                   | not defined
// DISABLE_LIGHTS_DIRECTIONAL               | not defined
// DISABLE_LIGHTS_OMNI                      | not defined
// DISABLE_LIGHTS_SPOT                      | not defined
// DISABLE_LIGHTS_SHADOW_MAPPED             | not defined
// DISABLE_LIGHTS_SHADOW_MAPPED_DIRECTIONAL | not defined
// DISABLE_LIGHTS_SHADOW_MAPPED_OMNI        | not defined
// DISABLE_LIGHTS_SHADOW_MAPPED_SPOT        | not defined
// DISABLE_VCT                              | not defined
// FOG_FACTOR_FUNCTION                      | FogFactor_Exponential
// LIGHT_ANGULAR_ATTENUATION_FUNCTION       | AngularAttenuation
// LIGHT_DISTANCE_ATTENUATION_FUNCTION      | DistanceAttenuation

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#include "global.hlsli"
#include "light.hlsli"
#include "material.hlsli"

#ifdef BRDF_FUNCTION

	#ifndef DISABLE_VCT
		#include "vct.hlsli"
	#else  // DISABLE_VCT
		#include "brdf.hlsli"
	#endif // DISABLE_VCT

#endif // BRDF_FUNCTION

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
#ifdef BRDF_FUNCTION

#ifndef DISABLE_LIGHTS_DIRECTIONAL
STRUCTURED_BUFFER(g_directional_lights, DirectionalLight, 
				  SLOT_SRV_DIRECTIONAL_LIGHTS);
#endif // DISABLE_LIGHTS_DIRECTIONAL

#ifndef DISABLE_LIGHTS_OMNI
STRUCTURED_BUFFER(g_omni_lights, OmniLight, 
				  SLOT_SRV_OMNI_LIGHTS);
#endif // DISABLE_LIGHTS_OMNI

#ifndef DISABLE_LIGHTS_SPOT
STRUCTURED_BUFFER(g_spot_lights, SpotLight, 
				  SLOT_SRV_SPOT_LIGHTS);
#endif // DISABLE_LIGHTS_SPOT

#ifndef DISABLE_LIGHTS_SHADOW_MAPPED

#ifndef DISABLE_LIGHTS_SHADOW_MAPPED_DIRECTIONAL
STRUCTURED_BUFFER(g_sm_directional_lights, ShadowMappedDirectionalLight,
				  SLOT_SRV_SHADOW_MAPPED_DIRECTIONAL_LIGHTS);
TEXTURE_2D_ARRAY(g_directional_sms, float, 
				 SLOT_SRV_DIRECTIONAL_SHADOW_MAPS);
#endif // DISABLE_LIGHTS_SHADOW_MAPPED_DIRECTIONAL

#ifndef DISABLE_LIGHTS_SHADOW_MAPPED_OMNI
STRUCTURED_BUFFER(g_sm_omni_lights, ShadowMappedOmniLight, 
				  SLOT_SRV_SHADOW_MAPPED_OMNI_LIGHTS);
TEXTURE_CUBE_ARRAY(g_omni_sms, float, 
				   SLOT_SRV_OMNI_SHADOW_MAPS);
#endif // DISABLE_LIGHTS_SHADOW_MAPPED_OMNI

#ifndef DISABLE_LIGHTS_SHADOW_MAPPED_SPOT
STRUCTURED_BUFFER(g_sm_spot_lights, ShadowMappedSpotLight, 
				  SLOT_SRV_SHADOW_MAPPED_SPOT_LIGHTS);
TEXTURE_2D_ARRAY(g_spot_sms, float, 
				 SLOT_SRV_SPOT_SHADOW_MAPS);
#endif // DISABLE_LIGHTS_SHADOW_MAPPED_SPOT

#endif // DISABLE_LIGHTS_SHADOW_MAPPED

#ifndef DISABLE_VCT
TEXTURE_3D(g_voxel_texture, float4, SLOT_SRV_VOXEL_TEXTURE);
#endif // DISABLE_VCT

#endif // BRDF_FUNCTION

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------

#ifdef BRDF_FUNCTION

float3 GetRadiance(float3 p_world, float3 n_world, float3 v_world, 
				   Material material) {

	float3 L = 0.0f;

	#ifndef DISABLE_LIGHTS_AMBIENT
	// Indirect illumination: ambient lights
	L += g_La;
	#endif // DISABLE_LIGHTS_AMBIENT

	#ifndef DISABLE_LIGHTS_DIRECTIONAL
	// Direct illumination: directional lights
	for (uint i0 = 0u; i0 < g_nb_directional_lights; ++i0) {
		const DirectionalLight light = g_directional_lights[i0];
		
		// Compute the light (hit-to-light) direction and irradiance.
		float3 l_world, E;
		Contribution(light, p_world, l_world, E);
		// Compute the BRDF.
		const BRDF brdf = BRDF_FUNCTION(n_world, l_world, v_world, material);
		// Compute the cosine factor.
		const float n_dot_l = sat_dot(n_world, l_world);

		L += (brdf.diffuse + brdf.specular) * E * n_dot_l;
	}
	#endif // DISABLE_LIGHTS_DIRECTIONAL

	#ifndef DISABLE_LIGHTS_OMNI
	// Direct illumination: omni lights
	for (uint i1 = 0u; i1 < g_nb_omni_lights; ++i1) {
		const OmniLight light = g_omni_lights[i1];
		
		// Compute the light (hit-to-light) direction and irradiance.
		float3 l_world, E;
		Contribution(light, p_world, l_world, E);
		// Compute the BRDF.
		const BRDF brdf = BRDF_FUNCTION(n_world, l_world, v_world, material);
		// Compute the cosine factor.
		const float n_dot_l = sat_dot(n_world, l_world);

		L += (brdf.diffuse + brdf.specular) * E * n_dot_l;
	}
	#endif // DISABLE_LIGHTS_OMNI

	#ifndef DISABLE_LIGHTS_SPOT
	// Direct illumination: spotlights
	for (uint i2 = 0u; i2 < g_nb_spot_lights; ++i2) {
		const SpotLight light = g_spot_lights[i2];
		
		// Compute the light (hit-to-light) direction and irradiance.
		float3 l_world, E;
		Contribution(light, p_world, l_world, E);
		// Compute the BRDF.
		const BRDF brdf = BRDF_FUNCTION(n_world, l_world, v_world, material);
		// Compute the cosine factor.
		const float n_dot_l = sat_dot(n_world, l_world);

		L += (brdf.diffuse + brdf.specular) * E * n_dot_l;
	}
	#endif // DISABLE_LIGHTS_SPOT

	#ifndef DISABLE_LIGHTS_SHADOW_MAPPED

	#ifndef DISABLE_LIGHTS_SHADOW_MAPPED_DIRECTIONAL
	// Direct illumination: directional lights with shadow mapping
	for (uint i3 = 0u; i3 < g_nb_sm_directional_lights; ++i3) {
		const ShadowMappedDirectionalLight light = g_sm_directional_lights[i3];
		const ShadowMap shadow_map = { g_pcf_sampler, g_directional_sms, i3 };

		// Compute the light (hit-to-light) direction and irradiance.
		float3 l_world, E;
		Contribution(light, shadow_map, p_world, l_world, E);
		// Compute the BRDF.
		const BRDF brdf = BRDF_FUNCTION(n_world, l_world, v_world, material);
		// Compute the cosine factor.
		const float n_dot_l = sat_dot(n_world, l_world);

		L += (brdf.diffuse + brdf.specular) * E * n_dot_l;
	}
	#endif // DISABLE_LIGHTS_SHADOW_MAPPED_DIRECTIONAL

	#ifndef DISABLE_LIGHTS_SHADOW_MAPPED_OMNI
	// Direct illumination: omni lights with shadow mapping
	for (uint i4 = 0u; i4 < g_nb_sm_omni_lights; ++i4) {
		const ShadowMappedOmniLight light = g_sm_omni_lights[i4];
		const ShadowCubeMap shadow_cube_map = { g_pcf_sampler, g_omni_sms, i4 };

		// Compute the light (hit-to-light) direction and irradiance.
		float3 l_world, E;
		Contribution(light, shadow_cube_map, p_world, l_world, E);
		// Compute the BRDF.
		const BRDF brdf = BRDF_FUNCTION(n_world, l_world, v_world, material);
		// Compute the cosine factor.
		const float n_dot_l = sat_dot(n_world, l_world);

		L += (brdf.diffuse + brdf.specular) * E * n_dot_l;
	}
	#endif // DISABLE_LIGHTS_SHADOW_MAPPED_OMNI

	#ifndef DISABLE_LIGHTS_SHADOW_MAPPED_SPOT
	// Direct illumination: spotlights with shadow mapping
	for (uint i5 = 0u; i5 < g_nb_sm_spot_lights; ++i5) {
		const ShadowMappedSpotLight light = g_sm_spot_lights[i5];
		const ShadowMap shadow_map = { g_pcf_sampler, g_spot_sms, i5 };
		
		// Compute the light (hit-to-light) direction and irradiance.
		float3 l_world, E;
		Contribution(light, shadow_map, p_world, l_world, E);
		// Compute the BRDF.
		const BRDF brdf = BRDF_FUNCTION(n_world, l_world, v_world, material);
		// Compute the cosine factor.
		const float n_dot_l = sat_dot(n_world, l_world);

		L += (brdf.diffuse + brdf.specular) * E * n_dot_l;
	}
	#endif // DISABLE_LIGHTS_SHADOW_MAPPED_SPOT

	#endif // DISABLE_LIGHTS_SHADOW_MAPPED

	#ifndef DISABLE_VCT
	// Direct illumination: emissive surfaces
	// Indirect illumination: { directional, omni, spot } lights (with shadow mapping)

	const float3 p_uvw     = WorldToVoxelUVW(p_world);
	const VCTConfig config = {
		g_voxel_texture_max_mip_level,
		g_voxel_grid_resolution,
		g_voxel_grid_inv_resolution,
		g_cone_step_multiplier,
		g_max_cone_distance,
		g_linear_clamp_sampler,
		g_voxel_texture
	};

	L += GetRadiance(p_uvw, n_world, v_world, material, config);
	#endif // DISABLE_VCT

	return L;
}

#endif // BRDF_FUNCTION

float3 GetRadiance(float3 p_world, float3 n_world, Material material) {
	float3 L = 0.0f;

	const float3 v_direction    = GetCameraPosition() - p_world;
	const float  v_distance     = length(v_direction);

	#ifdef BRDF_FUNCTION
	const float  inv_v_distance = 1.0f / v_distance;
	const float3 v_world        = v_direction * inv_v_distance;

	L += GetRadiance(p_world, n_world, v_world, material);
	#else  // BRDF_FUNCTION
	L += material.base_color;
	#endif // BRDF_FUNCTION

	#ifndef DISABLE_FOG
	const float fog_factor = FOG_FACTOR_FUNCTION(v_distance, g_fog_density);
	L = lerp(g_fog_color, L, fog_factor);
	#endif // DISABLE_FOG

	return L;
}

#endif // MAGE_HEADER_LIGHTING