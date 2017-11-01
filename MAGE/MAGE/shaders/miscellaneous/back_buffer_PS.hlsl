//-----------------------------------------------------------------------------
// Engine Configuration
//-----------------------------------------------------------------------------
// Defines			                      | Default
//-----------------------------------------------------------------------------
// MSAA_AS_SSAA                           | not defined

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#include "global.hlsli"
#include "tone_mapping.hlsli"
#include "color.hlsli"

//-----------------------------------------------------------------------------
// SRVs
//-----------------------------------------------------------------------------
TEXTURE_2D(g_image_texture, float4, SLOT_SRV_IMAGE);

//-----------------------------------------------------------------------------
// Pixel Shader
//-----------------------------------------------------------------------------
#ifdef MSAA_AS_SSAA
float4 PS(PSInputNDCPosition input, uint index : SV_SampleIndex) : SV_Target {
#else  // MSAA_AS_SSAA
float4 PS(PSInputNDCPosition input) : SV_Target {
#endif // MSAA_AS_SSAA

	const float4 hdr = g_image_texture[input.p.xy];
	const float4 ldr = saturate(TONE_MAP_COMPONENT(hdr));
	return LinearToGamma(ldr, g_inv_gamma);
}