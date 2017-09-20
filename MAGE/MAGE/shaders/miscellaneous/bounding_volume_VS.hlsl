//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------
#include "global.hlsli"

//-----------------------------------------------------------------------------
// Constant Buffers
//-----------------------------------------------------------------------------
cbuffer PerDraw : register(REG_B(SLOT_CBUFFER_PER_DRAW)) {
	// The object-to-projection transformation matrix.
	float4x4 g_object_to_projection : packoffset(c0);
}

//-----------------------------------------------------------------------------
// Vertex Shader
//-----------------------------------------------------------------------------
float4 VS(VSInputPosition input) : SV_Position {
	return mul(float4(input.p, 1.0f), g_object_to_projection);
}