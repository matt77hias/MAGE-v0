//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------
#include "global.hlsli"
#include "primitive\line_cube.hlsli"

//-----------------------------------------------------------------------------
// Constant Buffers
//-----------------------------------------------------------------------------
CBUFFER(PerDraw, SLOT_CBUFFER_PER_DRAW) {
	// The object-to-projection transformation matrix.
	float4x4 g_object_to_projection : packoffset(c0);
}

//-----------------------------------------------------------------------------
// Vertex Shader
//-----------------------------------------------------------------------------

// Number of vertices: 24
// Topology: D3D11_PRIMITIVE_TOPOLOGY_LINELIST

float4 VS(uint vertex_id: SV_VertexID) : SV_Position {
	return mul(float4(g_line_cube[vertex_id], 1.0f), g_object_to_projection);
}