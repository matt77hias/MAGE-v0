//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#include "structures.hlsli"

//-----------------------------------------------------------------------------
// Constant Buffers
//-----------------------------------------------------------------------------
cbuffer PerFrame : register(b1) {
	// The object-to-projection transformation matrix.
	float4x4 g_view_to_projection : packoffset(c0);
}

cbuffer PerDraw  : register(b2) {
	// The object-to-view transformation matrix.
	float4x4 g_object_to_view     : packoffset(c0);
}

//-----------------------------------------------------------------------------
// Vertex Shader
//-----------------------------------------------------------------------------
float4 VS(VSInputPositionNormalTexture input) : SV_Position {
        // g_object_to_view * g_view_to_projection: eliminates Z-fighting
	return mul(mul(float4(input.p, 1.0f), g_object_to_view), g_view_to_projection);
}
