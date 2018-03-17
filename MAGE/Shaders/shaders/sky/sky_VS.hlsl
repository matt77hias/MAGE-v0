//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------
#include "global.hlsli"
#include "primitive\icosphere.hlsli"

//-----------------------------------------------------------------------------
// Vertex Shader
//-----------------------------------------------------------------------------

// Number of vertices: 240
// Topology: D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST

PSInputWorldPosition VS(uint vertex_id : SV_VertexID) {
	PSInputWorldPosition output;
	
	// The position of the icosphere in world space is used for sampling the 
	// sky dome cube map. This position is reinterpreted as a direction in world 
	// space, which after transforming to camera space, becomes a direction in 
	// camera space, which can again be reinterpreted as a position of another 
	// icosphere in camera space. This latter position ensures that the 
	// icosphere will always fully cover the camera viewport.

	output.p_world = g_icosphere[vertex_id];
	
	const float3 p_camera = mul(output.p_world, (float3x3)g_world_to_camera);
	const float4 p_proj   = mul(float4(p_camera.xy,
									   g_sky_dome_scale_z * p_camera.z,
									   1.0f), 
								g_camera_to_projection);

	#ifdef DISABLE_INVERTED_Z_BUFFER
	output.p = p_proj.xyww;
	#else  // DISABLE_INVERTED_Z_BUFFER
	output.p = float4(p_proj.xy, 0.0f, p_proj.w);
	#endif // DISABLE_INVERTED_Z_BUFFER

	return output;
}