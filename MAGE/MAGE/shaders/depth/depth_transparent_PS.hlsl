//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#include "global.hlsli"

//-----------------------------------------------------------------------------
// Constant Buffers
//-----------------------------------------------------------------------------
CBUFFER(PerDraw, SLOT_CBUFFER_PER_DRAW) {
	// The dissolve of the material.
	float g_dissolve : packoffset(c0);
};

//-----------------------------------------------------------------------------
// SRVs
//-----------------------------------------------------------------------------
TEXTURE_2D(g_diffuse_texture, float4, SLOT_SRV_DIFFUSE);

//-----------------------------------------------------------------------------
// Pixel Shader
//-----------------------------------------------------------------------------
void PS(PSInputTexture input) {
	const float a = g_dissolve * g_diffuse_texture.Sample(g_linear_wrap_sampler, input.tex).a;
	clip(a - TRANSPARENCY_THRESHOLD);
}