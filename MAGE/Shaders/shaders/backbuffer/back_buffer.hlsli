//-----------------------------------------------------------------------------
// Engine Configuration
//-----------------------------------------------------------------------------
// Defines			                        | Default
//-----------------------------------------------------------------------------
// DISABLE_DITHERING                        | not defined
// DISABLE_GAMMA_CORRECTION                 | not defined
// DISABLE_TONE_MAPPING                     | not defined
// TONE_MAP_FUNCTION                        | ToneMap_Uncharted

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#include "global.hlsli"
#include "color.hlsli"
#include "rng.hlsli"
#include "tone_mapping.hlsli"

//-----------------------------------------------------------------------------
// SRVs
//-----------------------------------------------------------------------------
TEXTURE_2D(g_image_texture, float4, SLOT_SRV_IMAGE);

//-----------------------------------------------------------------------------
// Pixel Shader
//-----------------------------------------------------------------------------
float4 PS(float4 input : SV_Position) : SV_Target {
	const float4 hdr    = g_image_texture[input.xy];
	
	#ifdef DISABLE_TONE_MAPPING
	const float4 ldr    = hdr;
	#else  // DISABLE_TONE_MAPPING
	const float4 ldr    = TONE_MAP_FUNCTION(hdr);
	#endif // DISABLE_TONE_MAPPING

<<<<<<< HEAD
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
	const float4 output = color + noise * 0.00390625;
	#endif // DISABLE_DITHERING

	return output;
=======
	const float4 hdr    = g_image_texture[input.xy];
	const float4 ldr    = saturate(TONE_MAP_FUNCTION(hdr));
	const float4 color  = LinearToGamma(ldr, g_inv_gamma);

	const float2 uv     = ViewportToUV(input.xy);
	const float4 dither = frac(sin((uv.x + uv.y) * 199.0f) * 123.0f) * 0.00390625;

	return color + frac(sin((uv.x + uv.y) * 199.0f) * 123.0f) *0.00390625; // color + dither;
>>>>>>> 014ddfa21e361fa15a660eae77cc2365836a414d
}