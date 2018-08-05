//-----------------------------------------------------------------------------
// Engine Configuration
//-----------------------------------------------------------------------------
// Defines			                        | Default
//-----------------------------------------------------------------------------
// DISABLE_DITHERING                        | not defined
// DISABLE_GAMMA_CORRECTION                 | not defined
// DISABLE_TEMPORAL_DITHERING               | not defined

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#include "global.hlsli"
#include "color.hlsli"
#include "hash.hlsli"
#include "rng.hlsli"

//-----------------------------------------------------------------------------
// SRVs
//-----------------------------------------------------------------------------
TEXTURE_2D(g_image_texture, float4, SLOT_SRV_IMAGE);

//-----------------------------------------------------------------------------
// Pixel Shader
//-----------------------------------------------------------------------------
float4 PS(float4 input : SV_Position) : SV_Target {
	const  uint2 p_display = input.xy;
	const float4 ldr       = g_image_texture[p_display];
	
	#ifdef DISABLE_GAMMA_CORRECTION
	const float4 color     = ldr;
	#else  // DISABLE_GAMMA_CORRECTION
	const float4 color     = LinearToGamma(ldr, g_inv_gamma);
	#endif // DISABLE_GAMMA_CORRECTION

	#ifdef DISABLE_DITHERING
	const float4 output    = color;
	#else  // DISABLE_DITHERING
	
	#ifdef DISABLE_TEMPORAL_DITHERING
	const uint   key       = FlattenIndex(p_display, g_display_resolution);
	#else  // DISABLE_TEMPORAL_DITHERING
	const uint   key       = FlattenIndex(p_display, g_display_resolution)
		                   ^ asuint(g_time);
	#endif // DISABLE_TEMPORAL_DITHERING
	
	const float  noise     = UniformUintToFloat(Hash_Wang(key));
	const float4 output    = color + noise / 255.0f; // For 8 bit quantization.
	#endif // DISABLE_DITHERING

	return output;
}
