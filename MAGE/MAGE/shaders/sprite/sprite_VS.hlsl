//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#include "structures.fx"

//-----------------------------------------------------------------------------
// Constant buffers
//-----------------------------------------------------------------------------
cbuffer cb_transform : register(b0) {
	// The object-to-projection transformation matrix.
	float4x4 g_transform : packoffset(c0);
}

//-----------------------------------------------------------------------------
// Vertex Shader
//-----------------------------------------------------------------------------
PSInputPositionColorTexture VS(VSInputPositionColorTexture input) {
	PSInputPositionColorTexture output;
	output.p = mul(input.p, g_transform);
	output.color = input.color;
	output.tex = input.tex;
	return output;
}