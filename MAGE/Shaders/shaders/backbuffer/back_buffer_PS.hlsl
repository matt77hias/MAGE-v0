//-----------------------------------------------------------------------------
// Engine Configuration
//-----------------------------------------------------------------------------
// Defines			                        | Default
//-----------------------------------------------------------------------------
// DISABLE_DITHERING                        | not defined
// DISABLE_GAMMA_CORRECTION                 | not defined

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#include "global.hlsli"
#include "color.hlsli"
#include "rng.hlsli"

//-----------------------------------------------------------------------------
// SRVs
//-----------------------------------------------------------------------------
TEXTURE_2D(g_image_texture, float4, SLOT_SRV_IMAGE);

//-----------------------------------------------------------------------------
// Pixel Shader
//-----------------------------------------------------------------------------
float4 PS(float4 input : SV_Position) : SV_Target {
	const float4 ldr    = g_image_texture[input.xy];
	
	#ifdef DISABLE_GAMMA_CORRECTION
	const float4 color  = ldr;
	#else  // DISABLE_GAMMA_CORRECTION
	const float4 color  = LinearToGamma(ldr, g_inv_gamma);
	#endif // DISABLE_GAMMA_CORRECTION

	#ifdef DISABLE_DITHERING
	const float4 output = color;
	#else  // DISABLE_DITHERING
	const uint   seed   = FlattenIndex((uint2)input.xy, g_viewport_resolution);
	const float  noise  = UniformFloat(seed);
	const float4 output = color + noise / 255.0f;
	#endif // DISABLE_DITHERING

	return output;
}