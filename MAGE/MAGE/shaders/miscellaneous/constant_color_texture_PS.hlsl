//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#include "structures.fx"

sampler g_sampler   : register(s0);
Texture2D g_texture : register(t0);

cbuffer Color : register(b0) {
	float4 g_color : packoffset(c0);
};

float4 PS(PSInputPositionNormalTexture input) : SV_Target{
	return g_color * g_texture.Sample(g_sampler, input.tex);
}