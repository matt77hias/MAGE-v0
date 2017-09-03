//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#include "structures.fx"

//-----------------------------------------------------------------------------
// Constant buffers
//-----------------------------------------------------------------------------
cbuffer PerFrame : register(b0) {
	// The object-to-projection transformation matrix.
	float4x4 g_transform : packoffset(c0);
}

//-----------------------------------------------------------------------------
// Vertex Shader
//-----------------------------------------------------------------------------
PSInputColorTexture VS(VSInputPositionColorTexture input) {
	PSInputColorTexture output;
	output.p     = mul(float4(input.p, 1.0f), g_transform);
	output.color = input.color;
	output.tex   = input.tex;
	return output;
}