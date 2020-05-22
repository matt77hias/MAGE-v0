#ifndef MAGE_HEADER_AA
#define MAGE_HEADER_AA

//-----------------------------------------------------------------------------
// Engine Configuration
//-----------------------------------------------------------------------------
// Defines			                        | Default
//-----------------------------------------------------------------------------
// AA_INVERSE_TONE_MAP_FUNCTION             | InverseToneMap_Max3
// AA_TONE_MAP_FUNCTION                     | ToneMap_Max3
// PRESERVE_ALPHA                           | not defined

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#include "tone_mapping.hlsli"

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
void PreprocessAA(uint2 p_display,
				  Texture2D< float4 > input_image,
				  RWTexture2D< float4 > output_image) {

	#ifdef PRESERVE_ALPHA

	const float4 hdr = input_image[p_display];
	const float4 ldr = AA_TONE_MAP_FUNCTION(hdr);

	// Store the resolved radiance.
	output_image[p_display] = ldr;

	#else  // PRESERVE_ALPHA

	const float3 hdr = input_image[p_display].xyz;
	const float3 ldr = AA_TONE_MAP_FUNCTION(hdr);
	const float luminance = Luminance(hdr);

	// Store the resolved radiance.
	// The alpha channel contains the luminance (needed for FXAA).
	output_image[p_display] = float4(ldr, luminance);

	#endif // PRESERVE_ALPHA
}

#endif // MAGE_HEADER_AA