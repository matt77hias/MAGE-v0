//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------
#include "global.hlsli"
#include "primitive\icosphere.hlsli"

//-----------------------------------------------------------------------------
// Constant Buffers
//-----------------------------------------------------------------------------
CBUFFER(PerDraw, SLOT_CBUFFER_PER_FRAME) {
	// The world-to-projection transformation matrix.
	float4x4 g_world_to_projection : packoffset(c0);
}

//-----------------------------------------------------------------------------
// Vertex Shader
//-----------------------------------------------------------------------------

// Number of vertices: 240
// Topology: D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST

PSInputWorldPosition VS(uint vertex_id : SV_VertexID) {
	PSInputWorldPosition output;
	
	output.p_world = 100.0f * g_icosphere[vertex_id];
	output.p       = mul(float4(output.p_world, 1.0f), g_world_to_projection);

	return output;
}