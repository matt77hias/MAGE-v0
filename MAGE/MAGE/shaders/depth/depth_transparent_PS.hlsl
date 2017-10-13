//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#include "global.hlsli"

//-----------------------------------------------------------------------------
// Constant Buffers
//-----------------------------------------------------------------------------
CBUFFER(PerDraw, SLOT_CBUFFER_PER_DRAW) {
	// MATERIAL
	// The alpha channel of the base color of the material.
	float g_base_color_a : packoffset(c0);
};

//-----------------------------------------------------------------------------
// SRVs
//-----------------------------------------------------------------------------
TEXTURE_2D(g_base_color_texture, float4, SLOT_SRV_BASE_COLOR);

//-----------------------------------------------------------------------------
// Pixel Shader
//-----------------------------------------------------------------------------
void PS(PSInputTexture input) {
	const float alpha = g_base_color_a
		* g_base_color_texture.Sample(g_linear_wrap_sampler, input.tex).a;
	clip(alpha - TRANSPARENCY_SHADOW_THRESHOLD);
}