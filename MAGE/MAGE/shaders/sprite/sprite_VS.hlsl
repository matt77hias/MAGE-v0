//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#include "structures.hlsli"

//-----------------------------------------------------------------------------
// Constant buffers
//-----------------------------------------------------------------------------
cbuffer PerFrame : register(b0) {
	// The object-to-projection transformation matrix.
	float4x4 g_object_to_projection : packoffset(c0);
}

//-----------------------------------------------------------------------------
// Vertex Shader
//-----------------------------------------------------------------------------
PSInputColorTexture VS(VSInputPositionColorTexture input) {
	PSInputColorTexture output;
	output.p     = mul(float4(input.p, 1.0f), g_object_to_projection);
	output.color = input.color;
	output.tex   = input.tex;
	return output;
}