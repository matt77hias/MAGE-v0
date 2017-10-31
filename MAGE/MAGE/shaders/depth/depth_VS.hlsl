//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#include "global.hlsli"

//-----------------------------------------------------------------------------
// Constant Buffers
//-----------------------------------------------------------------------------
CBUFFER(SecondaryCamera, SLOT_CBUFFER_SECONDARY_CAMERA) {
	// The view-to-projection transformation matrix.
	float4x4 g_view2_to_projection2 : packoffset(c0);
}

CBUFFER(Model, SLOT_CBUFFER_MODEL) {
	// The object-to-view transformation matrix.
	float4x4 g_object_to_view2      : packoffset(c0);
}

//-----------------------------------------------------------------------------
// Vertex Shader
//-----------------------------------------------------------------------------
float4 VS(VSInputPositionNormalTexture input) : SV_Position {
    // g_object_to_view * g_view_to_projection: eliminates Z-fighting
	return mul(mul(float4(input.p, 1.0f), 
	           g_object_to_view2), g_view2_to_projection2);
}
