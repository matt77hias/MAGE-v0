//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------
#include "global.hlsli"
#include "primitive\line_cube.hlsli"

//-----------------------------------------------------------------------------
// Constant Buffers
//-----------------------------------------------------------------------------
CBUFFER(Model, SLOT_CBUFFER_MODEL) {
	// The cube-to-camera transformation matrix.
	float4x4 g_cube_to_camera : packoffset(c0);
}

//-----------------------------------------------------------------------------
// Vertex Shader
//-----------------------------------------------------------------------------

// Number of vertices: 24
// Topology: D3D11_PRIMITIVE_TOPOLOGY_LINELIST

float4 VS(uint vertex_id : SV_VertexID) : SV_Position {
	const float3 p_camera = mul(float4(g_line_cube[vertex_id], 1.0f), 
	                            g_cube_to_camera).xyz;
	const float4 p_proj   = mul(float4(p_camera, 1.0f), g_camera_to_projection);
	return p_proj;
}