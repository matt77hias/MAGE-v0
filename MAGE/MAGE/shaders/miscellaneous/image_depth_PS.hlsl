//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#include "global.hlsli"

//-----------------------------------------------------------------------------
// SRVs
//-----------------------------------------------------------------------------
TEXTURE_2D(g_image_texture, float4, SLOT_SRV_IMAGE);
TEXTURE_2D(g_depth_texture, float,  SLOT_SRV_DEPTH);

//-----------------------------------------------------------------------------
// Pixel Shader
//-----------------------------------------------------------------------------
OMInputColorDepth PS(PSInputNDCPosition input) {
	OMInputColorDepth output;
	output.color = g_image_texture[input.p.xy];
	output.depth = g_depth_texture[input.p.xy];
	return output;
}