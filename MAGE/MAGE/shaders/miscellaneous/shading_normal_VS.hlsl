//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#include "global.hlsli"

//-----------------------------------------------------------------------------
// Constant Buffers
//-----------------------------------------------------------------------------
CBUFFER(PerFrame, SLOT_CBUFFER_PER_FRAME) {
	// The view-to-projection transformation matrix.
	float4x4 g_view_to_projection : packoffset(c0);
};

CBUFFER(PerDraw, SLOT_CBUFFER_PER_DRAW) {
	// The object-to-view transformation matrix.
	float4x4 g_object_to_view     : packoffset(c0);
	// The object-to-world inverse transpose transformation matrix
	// = The normal-to-world transformation matrix.
	float4x4 g_normal_to_world    : packoffset(c4);
}

//-----------------------------------------------------------------------------
// Vertex Shader
//-----------------------------------------------------------------------------
PSInputPositionNormalTexture VS(VSInputPositionNormalTexture input) {
	PSInputPositionNormalTexture output;
	output.p      = mul(float4(input.p, 1.0f), g_object_to_view);
	output.p_view = output.p.xyz;
	output.p      = mul(output.p, g_view_to_projection);
	output.n_view = normalize(mul(input.n, (float3x3)g_normal_to_world));
	output.tex    = input.tex;
	output.tex2   = input.tex;
	return output;
}