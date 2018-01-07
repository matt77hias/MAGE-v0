//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#include "global.hlsli"

//-----------------------------------------------------------------------------
// Constant buffers
//-----------------------------------------------------------------------------
CBUFFER(SecondaryCamera, SLOT_CBUFFER_SECONDARY_CAMERA) {
	// The object-to-projection transformation matrix.
	float4x4 g_object_to_projection2 : packoffset(c0);
}

//-----------------------------------------------------------------------------
// Vertex Shader
//-----------------------------------------------------------------------------
PSInputColorTexture VS(VSInputPositionColorTexture input) {
	PSInputColorTexture output;
	output.p     = mul(float4(input.p, 1.0f), g_object_to_projection2);
	output.color = input.color;
	output.tex   = input.tex;
	return output;
}