//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#include "global.hlsli"
#include "tone_mapping.hlsli"

//-----------------------------------------------------------------------------
// SRVs
//-----------------------------------------------------------------------------
TEXTURE_2D(g_image_texture, float4, SLOT_SRV_IMAGE);

//-----------------------------------------------------------------------------
// Pixel Shader
//-----------------------------------------------------------------------------
float4 PS(PSInputNDCPosition input) : SV_Target {
	const float4 hdr = g_image_texture[input.p.xy];
	const float4 ldr = saturate(float4(HDRtoLDR(hdr.xyz), hdr.w));
	return LinearToGamma(ldr);
}