//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#include "structures.fx"

//-----------------------------------------------------------------------------
// Constant buffers
//-----------------------------------------------------------------------------
Texture2D texture_map : register(t0);
sampler texture_sampler : register(s0);

cbuffer cb_transform : register(b0) {
	// The object-to-projection transformation matrix.
	float4x4 transform : packoffset(c0);
}

//-----------------------------------------------------------------------------
// Vertex Shader
//-----------------------------------------------------------------------------
PSInputPositionColorTexture VS(VSInputPositionColorTexture input) {
	PSInputPositionColorTexture output = (PSInputPositionColorTexture)0;
	output.p     = mul(input.p, transform);
	output.color = input.color;
	output.tex   = input.tex;
	return output;
}

//-----------------------------------------------------------------------------
// Pixel Shader
//-----------------------------------------------------------------------------
float4 PS(PSInputPositionColorTexture input) : SV_Target {
	return texture_map.Sample(texture_sampler, input.tex) * input.color;
}