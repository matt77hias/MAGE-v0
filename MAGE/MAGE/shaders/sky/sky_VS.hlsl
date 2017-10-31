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
// Vertex Shader
//-----------------------------------------------------------------------------

// Number of vertices: 240
// Topology: D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST

PSInputWorldPosition VS(uint vertex_id : SV_VertexID) {
	PSInputWorldPosition output;
	
	// The position of the icosphere in world space is used for sampling the 
	// sky dome cube map. The position of the icosphere in world space is 
	// reinterpreted as a direction in world space, which after transformating
	// to view space becomes a direction in view space, which can again be
	// reinterpreted as a position of another icosphere in view space. This way
	// the icosphere will always fully cover the camera view.

	output.p_world = g_icosphere[vertex_id];
	
	const float3 p_view  = mul(output.p_world, (float3x3)g_world_to_view);
	const float4 p_proj  = mul(float4(p_view.xy, 
		                              g_sky_dome_z_scale * p_view.z, 
		                              1.0f), 
		                       g_view_to_projection);

#ifdef DISSABLE_INVERTED_Z_BUFFER
	output.p = p_proj.xyww;
#else  // DISSABLE_INVERTED_Z_BUFFER
	output.p = float4(p_proj.xy, 0.0f, p_proj.w);
#endif // DISSABLE_INVERTED_Z_BUFFER

	return output;
}