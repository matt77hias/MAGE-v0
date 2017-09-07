//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#include "hlsl.hpp"
#include "structures.hlsli"

//-----------------------------------------------------------------------------
// Samplers and Textures
//-----------------------------------------------------------------------------
sampler   g_sampler : register(REG_S(SLOT_SAMPLER_DEFAULT));
Texture2D g_texture : register(REG_T(SLOT_SRV_TEXTURE));

//-----------------------------------------------------------------------------
// Constant Buffers
//-----------------------------------------------------------------------------
cbuffer Color : register(REG_B(SLOT_CBUFFER_COLOR)) {
	float4 g_color : packoffset(c0);
};

//-----------------------------------------------------------------------------
// Pixel Shader
//-----------------------------------------------------------------------------
float4 PS(PSInputPositionNormalTexture input) : SV_Target{
	return g_color * g_texture.Sample(g_sampler, input.tex);
}