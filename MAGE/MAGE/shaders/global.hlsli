#ifndef MAGE_HEADER_GLOBAL
#define MAGE_HEADER_GLOBAL

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#include "hlsl.hpp"
#include "hlsl_syntax.hlsli"
#include "math.hlsli"
#include "structures.hlsli"

//-----------------------------------------------------------------------------
// Samplers
//-----------------------------------------------------------------------------
SAMPLER_STATE(g_variable_sampler0,          SLOT_SAMPLER_VARIABLE_0);
SAMPLER_STATE(g_variable_sampler1,          SLOT_SAMPLER_VARIABLE_1);
SAMPLER_STATE(g_variable_sampler2,          SLOT_SAMPLER_VARIABLE_2);
SAMPLER_STATE(g_variable_sampler3,          SLOT_SAMPLER_VARIABLE_3);

SAMPLER_STATE(g_point_wrap_sampler,         SLOT_SAMPLER_POINT_WRAP);
SAMPLER_STATE(g_point_clamp_sampler,        SLOT_SAMPLER_POINT_CLAMP);
SAMPLER_STATE(g_point_mirror_sampler,       SLOT_SAMPLER_POINT_MIRROR);
SAMPLER_STATE(g_linear_wrap_sampler,        SLOT_SAMPLER_LINEAR_WRAP);
SAMPLER_STATE(g_linear_clamp_sampler,       SLOT_SAMPLER_LINEAR_CLAMP);
SAMPLER_STATE(g_linear_mirror_sampler,      SLOT_SAMPLER_LINEAR_MIRROR);
SAMPLER_STATE(g_anisotropic_wrap_sampler,   SLOT_SAMPLER_ANISOTROPIC_WRAP);
SAMPLER_STATE(g_anisotropic_clamp_sampler,  SLOT_SAMPLER_ANISOTROPIC_CLAMP);
SAMPLER_STATE(g_anisotropic_mirror_sampler, SLOT_SAMPLER_ANISOTROPIC_MIRROR);

SAMPLER_COMPARISON_STATE(g_pcf_sampler,     SLOT_SAMPLER_PCF);

//-----------------------------------------------------------------------------
// Constant Buffers 
//-----------------------------------------------------------------------------

CBUFFER(Game, SLOT_CBUFFER_GAME) {
	// The resolution of the display.
	// g_display_resolution.x = the display width
	// g_display_resolution.y = the display height
	uint2  g_display_resolution                  : packoffset(c0);
	// The inverse of the resolution of the display minus 1.
	// g_display_inv_resolution_minus1.x = 1 / (g_display_resolution.x - 1)
	// g_display_inv_resolution_minus1.y = 1 / (g_display_resolution.y - 1)
	float2 g_display_inv_resolution_minus1       : packoffset(c0.z);
	// The resolution of the super-sampled display.
	// g_ss_display_resolution.x = the super-sampled display width
	// g_ss_display_resolution.y = the super-sampled display height
	uint2  g_ss_display_resolution               : packoffset(c1);
	// The inverse of the resolution of the super-sampled display minus 1.
	// g_ss_display_inv_resolution_minus1.x = 1 / (g_ss_display_resolution.x - 1)
	// g_ss_display_inv_resolution_minus1.y = 1 / (g_ss_display_resolution.y - 1)
	float2 g_ss_display_inv_resolution_minus1    : packoffset(c1.z);

	// The gamma exponent used for gamma recovery.
	// C  = pow(C', g_gamma)
	float g_gamma                                : packoffset(c2);
	// The inverse of the gamma exponent used for gamma correction.
	// C' = pow(C, g_inv_gamma) = pow(C, 1/g_gamma)
	float g_inv_gamma                            : packoffset(c2.y);
};

CBUFFER(PrimaryCamera, SLOT_CBUFFER_PRIMARY_CAMERA) {
	// The camera-view-to-camera-projection transformation matrix.
	float4x4 g_view_to_projection                : packoffset(c0);
	// The camera-projection-to-camera-view transformation matrix.
	float4x4 g_projection_to_view                : packoffset(c4);
	// The world-to-camera-view transformation matrix.
	float4x4 g_world_to_view                     : packoffset(c8);
	// The camera-view-to-world transformation matrix.
	float4x4 g_view_to_world                     : packoffset(c12);
	
	// The top left corner of the camera viewport.
	uint2    g_viewport_top_left                 : packoffset(c16);
	// The resolution of the camera viewport.
	// g_viewport_resolution.x = the viewport width
	// g_viewport_resolution.y = the viewport height
	uint2    g_viewport_resolution               : packoffset(c16.z);
	// The top left corner of the super-sampled camera viewport.
	uint2    g_ss_viewport_top_left              : packoffset(c17);
	// The resolution of the super-sampled camera viewport.
	// g_ss_viewport_resolution.x = the super-sampled viewport width
	// g_ss_viewport_resolution.y = the super-sampled viewport height
	uint2    g_ss_viewport_resolution            : packoffset(c17.z);
	// The inverse of the resolution of the camera viewport minus 1.
	// g_viewport_inv_resolution_minus1.x = 1 / (g_viewport_resolution.x - 1)
	// g_viewport_inv_resolution_minus1.y = 1 / (g_viewport_resolution.y - 1)
	float2   g_viewport_inv_resolution_minus1    : packoffset(c18);
	// The inverse of the resolution of the super-sampled camera viewport minus 1.
	// g_ss_viewport_inv_resolution_minus1.x = 1 / (g_ss_viewport_resolution.x - 1)
	// g_ss_viewport_inv_resolution_minus1.y = 1 / (g_ss_viewport_resolution.y - 1)
	float2   g_ss_viewport_inv_resolution_minus1 : packoffset(c18.z);
}

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions: Transform Utilities
//-----------------------------------------------------------------------------

/**
 Converts the given display location to UV coorcinates.

 @pre			@a location is non-normalized 
				(i.e. in the [0,g_display_resolution.x-1] by 
				[0,g_display_resolution.y-1] range).
 @param[in]		location
				The display location.
 @return		The UV coordinates.
 */
float2 LocationToUV(float2 location) {
	return LocationToUV(location, g_display_inv_resolution_minus1);
}

/**
 Converts the given super-sampled display location to UV coorcinates.

 @pre			@a location is non-normalized 
				(i.e. in the [0,g_ss_display_resolution.x-1] by 
				[0,g_ss_display_resolution.y-1] range).
 @param[in]		location
				The super-sampled display location.
 @return		The UV coordinates.
 */
float2 SSLocationToUV(float2 location) {
	return LocationToUV(location, g_ss_display_inv_resolution_minus1);
}

/**
 Converts the given viewport dispatch thread id to NDC coordinates.

 @pre			@a id is non-normalized 
				(i.e. in the [0,g_viewport_resolution.x-1] by 
				[0,g_viewport_resolution.y-1] range).
 @param[in]		id
				The non-normalized viewport dispatch thread id.
 @return		The NDC coordinates.
 */
float2 DispatchThreadIDtoNDC(float2 id) {
	const float2 uv = LocationToUV(id, g_viewport_inv_resolution_minus1);
	return UVtoNDC(uv);
}

/**
 Converts the given super-sampled viewport dispatch thread id to NDC coordinates.

 @pre			@a id is non-normalized 
				(i.e. in the [0,g_ss_viewport_resolution.x-1] by 
				[0,g_ss_viewport_resolution.y-1] range).
 @param[in]		id
				The non-normalized super-sampled viewport dispatch thread id.
 @return		The NDC coordinates.
 */
float2 SSDispatchThreadIDtoNDC(float2 id) {
	const float2 uv = LocationToUV(id, g_ss_viewport_inv_resolution_minus1);
	return UVtoNDC(uv);
}

#endif // MAGE_HEADER_GLOBAL