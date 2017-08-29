//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#include "structures.fx"
#include "light.fx"

//-----------------------------------------------------------------------------
// Constant Buffers
//-----------------------------------------------------------------------------
cbuffer PerFrame : register(b0) {
	// The view-to-projection transformation matrix.
	float4x4 g_view_to_projection      : packoffset(c0);
	
	// The intensity of the ambient light in the scene. 
	float3 g_Ia                        : packoffset(c4);
	// The global flags.
	uint g_flags                       : packoffset(c4.w);
	// The number of directional lights in the scene.
	uint g_nb_directional_lights       : packoffset(c5.x);
	// The number of omni lights in the scene.
	uint g_nb_omni_lights              : packoffset(c5.y);
	// The number of spotlights in the scene.
	uint g_nb_spot_lights              : packoffset(c5.z);
	
	// The distance at which intensity falloff starts due to fog.
	float g_fog_distance_falloff_start : packoffset(c5.w);
	// The color of the fog.
	float3 g_fog_color                 : packoffset(c6);
	// The distance range where intensity falloff occurs due to fog.
	float g_fog_distance_falloff_range : packoffset(c6.w);
};

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
Texture2D g_p_view       : register(t3);
Texture2D g_n_view       : register(t4);
Texture2D g_Kd_texture   : register(t5);
Texture2D g_KsNs_texture : register(t6);

// Work In Progress