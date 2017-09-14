//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#include "hlsl.hpp"
#include "structures.hlsli"

//-----------------------------------------------------------------------------
// Constant Buffers
//-----------------------------------------------------------------------------
cbuffer Dissolve : register(REG_B(SLOT_CBUFFER_PER_DRAW)) {
	float g_dissolve : packoffset(c0);
};

//-----------------------------------------------------------------------------
// Samplers and Textures
//-----------------------------------------------------------------------------
sampler   g_sampler          : register(REG_S(SLOT_SAMPLER_DEFAULT));
Texture2D g_diffuse_texture  : register(REG_T(SLOT_SRV_DIFFUSE));

//-----------------------------------------------------------------------------
// Pixel Shader
//-----------------------------------------------------------------------------
void PS(PSInputTexture input) {
	const float a = g_dissolve * g_diffuse_texture.Sample(g_sampler, input.tex).a;
	clip(a - TRANSPARENCY_THRESHOLD);
}