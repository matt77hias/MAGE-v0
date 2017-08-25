//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#include "structures.fx"

//-----------------------------------------------------------------------------
// Constant buffers
//-----------------------------------------------------------------------------
Texture2D g_texture : register(t0);
sampler g_sampler : register(s0);

cbuffer cb_transform : register(b0) {
	// The object-to-projection transformation matrix.
	float4x4 g_transform : packoffset(c0);
}

//-----------------------------------------------------------------------------
// Vertex Shader
//-----------------------------------------------------------------------------
PSInputPositionColorTexture VS(VSInputPositionColorTexture input) {
	PSInputPositionColorTexture output;
	output.p     = mul(input.p, g_transform);
	output.color = input.color;
	output.tex   = input.tex;
	return output;
}

//-----------------------------------------------------------------------------
// Pixel Shader
//-----------------------------------------------------------------------------
float4 PS(PSInputPositionColorTexture input) : SV_Target {
	return g_texture.Sample(g_sampler, input.tex) * input.color;
}