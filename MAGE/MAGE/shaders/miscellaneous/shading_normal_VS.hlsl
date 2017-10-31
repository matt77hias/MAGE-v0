//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#include "global.hlsli"

//-----------------------------------------------------------------------------
// Constant Buffers
//-----------------------------------------------------------------------------
CBUFFER(Model, SLOT_CBUFFER_MODEL) {
	// The object-to-view transformation matrix.
	float4x4 g_object_to_view  : packoffset(c0);
	// The object-to-world inverse transpose transformation matrix
	// = The normal-to-world transformation matrix.
	float4x4 g_normal_to_world : packoffset(c4);
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