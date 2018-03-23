//-----------------------------------------------------------------------------
// Engine Configuration
//-----------------------------------------------------------------------------
// Defines			                        | Default
//-----------------------------------------------------------------------------
// MSAA_AS_SSAA                             | not defined
// TONE_MAP_FUNCTION                        | ToneMap_Uncharted

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#include "global.hlsli"
#include "color.hlsli"
#include "tone_mapping.hlsli"

//-----------------------------------------------------------------------------
// SRVs
//-----------------------------------------------------------------------------
TEXTURE_2D(g_image_texture, float4, SLOT_SRV_IMAGE);

//-----------------------------------------------------------------------------
// Pixel Shader
//-----------------------------------------------------------------------------
#ifdef MSAA_AS_SSAA
float4 PS(float4 input : SV_Position, 
		  uint index   : SV_SampleIndex) : SV_Target {
#else  // MSAA_AS_SSAA
float4 PS(float4 input : SV_Position) : SV_Target {
#endif // MSAA_AS_SSAA

	const float4 hdr = g_image_texture[input.xy];
	const float4 ldr = saturate(TONE_MAP_FUNCTION(hdr));

	return LinearToGamma(ldr, g_inv_gamma);
}