//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#include "global.hlsli"

//-----------------------------------------------------------------------------
// Constant Buffers
//-----------------------------------------------------------------------------
cbuffer PerFrame : register(REG_B(SLOT_CBUFFER_PER_FRAME)) {
	// The view-to-projection transformation matrix.
	float4x4 g_view_to_projection : packoffset(c0);
}

cbuffer PerDraw  : register(REG_B(SLOT_CBUFFER_PER_DRAW)) {
	// The object-to-view transformation matrix.
	float4x4 g_object_to_view     : packoffset(c0);
	// The texture transformation matrix.
	float4x4 g_texture_transform  : packoffset(c4);
}

//-----------------------------------------------------------------------------
// Vertex Shader
//-----------------------------------------------------------------------------
PSInputTexture VS(VSInputPositionNormalTexture input) {
	PSInputTexture output;
	// g_object_to_view * g_view_to_projection: eliminates Z-fighting
	output.p   = mul(mul(float4(input.p, 1.0f), g_object_to_view), g_view_to_projection);
	output.tex = mul(float3(input.tex, 1.0f), (float3x3)g_texture_transform).xy;
	return output;
}