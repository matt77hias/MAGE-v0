//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------
#include "global.hlsli"
#include "primitive\line_cube.hlsli"
#include "transform\transform.hlsli"

//-----------------------------------------------------------------------------
// Constant Buffers
//-----------------------------------------------------------------------------
CBUFFER(Model, SLOT_CBUFFER_MODEL) {

	/**
	 The cube-to-world transformation matrix.
	 */
	float4x4 g_cube_to_world : packoffset(c0);
}

//-----------------------------------------------------------------------------
// Vertex Shader
//-----------------------------------------------------------------------------

// Number of vertices: 24
// Topology: D3D11_PRIMITIVE_TOPOLOGY_LINELIST

float4 VS(uint vertex_id : SV_VertexID) : SV_Position {
	return Transform(g_line_cube[vertex_id],
	                 g_cube_to_world,
					 g_world_to_camera,
					 g_camera_to_projection);
}