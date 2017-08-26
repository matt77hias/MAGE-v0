//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#include "structures.fx"

//-----------------------------------------------------------------------------
// Scene
//-----------------------------------------------------------------------------

cbuffer Scene : register(b0) {
	// The world-to-view transformation matrix.
	float4x4 g_world_to_view					: packoffset(c0);
	// The view-to-projection transformation matrix.
	float4x4 g_view_to_projection				: packoffset(c4);
};

//-----------------------------------------------------------------------------
// Model
//-----------------------------------------------------------------------------

cbuffer Model : register(b1) {
	// The object-to-world transformation matrix.
	float4x4 g_object_to_world					: packoffset(c0);
	// The object-to-view inverse transpose transformation matrix.
	float4x4 g_object_to_view_inverse_transpose	: packoffset(c4);
}

//-----------------------------------------------------------------------------
// Vertex Shader
//-----------------------------------------------------------------------------

PSInputPositionNormalTexture VS(VSInputPositionNormalTexture input) {
	PSInputPositionNormalTexture output;
	output.p      = mul(input.p, g_object_to_world);
	output.p      = mul(output.p, g_world_to_view);
	output.p_view = output.p.xyz;
	output.p      = mul(output.p, g_view_to_projection);
	output.tex    = input.tex;
	output.n_view = input.n;
	return output;
}