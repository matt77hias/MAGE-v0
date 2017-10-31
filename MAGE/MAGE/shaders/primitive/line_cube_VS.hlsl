//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------
#include "global.hlsli"
#include "primitive\line_cube.hlsli"

//-----------------------------------------------------------------------------
// Constant Buffers
//-----------------------------------------------------------------------------
CBUFFER(Model, SLOT_CBUFFER_MODEL) {
	// The object-to-view transformation matrix.
	float4x4 g_object_to_view : packoffset(c0);
}

//-----------------------------------------------------------------------------
// Vertex Shader
//-----------------------------------------------------------------------------

// Number of vertices: 24
// Topology: D3D11_PRIMITIVE_TOPOLOGY_LINELIST

float4 VS(uint vertex_id : SV_VertexID) : SV_Position {
	return mul(mul(float4(g_line_cube[vertex_id], 1.0f), 
	           g_object_to_view), g_view_to_projection);
}