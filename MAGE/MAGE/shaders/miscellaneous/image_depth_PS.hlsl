//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#include "global.hlsli"

//-----------------------------------------------------------------------------
// Textures
//-----------------------------------------------------------------------------
Texture2D g_image_texture : register(REG_T(SLOT_SRV_IMAGE));
Texture2D g_depth_texture : register(REG_T(SLOT_SRV_DEPTH));

//-----------------------------------------------------------------------------
// Pixel Shader
//-----------------------------------------------------------------------------
OMInputColorDepth PS(PSInputNDCPosition input) {
	OMInputColorDepth output;
	output.color = g_image_texture[input.p.xy];
	output.depth = g_depth_texture[input.p.xy].x;
	return output;
}