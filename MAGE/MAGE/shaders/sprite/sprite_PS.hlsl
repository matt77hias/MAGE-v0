//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#include "hlsl.hpp"
#include "structures.hlsli"

//-----------------------------------------------------------------------------
// Samplers and Textures
//-----------------------------------------------------------------------------
sampler g_sampler  : register(REG_S(SLOT_SAMPLER_DEFAULT));
Texture2D g_sprite : register(REG_T(SLOT_SRV_SPRITE));

//-----------------------------------------------------------------------------
// Pixel Shader
//-----------------------------------------------------------------------------
float4 PS(PSInputColorTexture input) : SV_Target {
	return g_sprite.Sample(g_sampler, input.tex) * input.color;
}