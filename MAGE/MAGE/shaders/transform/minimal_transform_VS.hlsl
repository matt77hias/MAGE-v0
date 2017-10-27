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
	// The object-to-view inverse transpose transformation matrix
	// = The normal-to-view transformation matrix.
	float4x4 g_normal_to_view     : packoffset(c4);
	// The texture transformation matrix.
	float4x4 g_texture_transform  : packoffset(c8);
}

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#include "transform\transform.hlsli"
