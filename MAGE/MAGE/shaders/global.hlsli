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
	// The display resolution.
	// g_resolution.x = the display width
	// g_resolution.y = the display height
	float2 g_resolution            : packoffset(c0);
	// The inverse of the display resolution minus 1.
	// g_inv_resolution_minus1.x = 1 / (g_resolution.x - 1)
	// g_inv_resolution_minus1.y = 1 / (g_resolution.y - 1)
	float2 g_inv_resolution_minus1 : packoffset(c0.z);
	// The gamma exponent used for gamma recovery.
	// C  = pow(C', g_gamma)
	float g_gamma                  : packoffset(c1);
	// The inverse of the gamma exponent used for gamma correction.
	// C' = pow(C, g_inv_gamma) = pow(C, 1/g_gamma)
	float g_inv_gamma              : packoffset(c1.y);
};

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions: Transform Utilities
//-----------------------------------------------------------------------------

/**
 Normalizes the given dispatch thread id.

 @pre			@a id is non-normalized 
				(i.e. in the [0,g_resolution.x-1] x [0,g_resolution.y-1] range).
 @param[in]		id
				The non-normalized dispatch thread id.
 @return		The normalized dispatch thread id corresponding to the given 
				non-normalized dispatch thread id.
 */
float2 NormalizeDispatchThreadID(uint2 id) {
	// x: [0,g_resolution.x-1] -> [0,1]
	// y: [0,g_resolution.y-1] -> [0,1]
	return id * g_inv_resolution_minus1;
}

/**
 Converts the given dispatch thread id to NDC coordinates.

 @pre			@a id is non-normalized 
				(i.e. in the [0,g_resolution.x-1] x [0,g_resolution.y-1] range).
 @param[in]		id
				The non-normalized dispatch thread id.
 @return		The NDC coordinates.
 */
float2 DispatchThreadIDtoNDC(uint2 id) {
	return NormalizedDispatchThreadIDtoNDC(NormalizeDispatchThreadID(id));
}

#endif // MAGE_HEADER_GLOBAL