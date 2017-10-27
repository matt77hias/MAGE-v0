//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------
#include "global.hlsli"
#include "primitive\icosphere.hlsli"

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------

/**
 The scaling factor of the z component of sky domes.
 */
static const float g_sky_dome_z_scale = 1.5f;

//-----------------------------------------------------------------------------
// Constant Buffers
//-----------------------------------------------------------------------------
CBUFFER(PerDraw, SLOT_CBUFFER_PER_FRAME) {
	// The world-to-projection transformation matrix.
	float4x4 g_world_to_view      : packoffset(c0);
	// The view-to-projection transformation matrix.
	float4x4 g_view_to_projection : packoffset(c4);
}

//-----------------------------------------------------------------------------
// Vertex Shader
//-----------------------------------------------------------------------------

// Number of vertices: 240
// Topology: D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST

PSInputWorldPosition VS(uint vertex_id : SV_VertexID) {
	PSInputWorldPosition output;
	
	output.p_world = g_icosphere[vertex_id];
	
	const float3 p_view  = mul(output.p_world, (float3x3)g_world_to_view);
	const float4 p_proj  = mul(float4(p_view.xy, 
		                              g_sky_dome_z_scale * p_view.z, 
		                              1.0f), 
		                       g_view_to_projection);

	// Non-inverted Z-buffer: output.p = p_proj.xyww;
	output.p       = float4(p_proj.xy, 0.0f, p_proj.w);

	return output;
}