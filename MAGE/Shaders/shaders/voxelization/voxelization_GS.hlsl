//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#include "global.hlsli"

//-----------------------------------------------------------------------------
// Geometry Shader
//-----------------------------------------------------------------------------
[maxvertexcount(3)]
void GS(triangle GSInputPositionNormalTexture input[3],
	    inout TriangleStream< PSInputPositionNormalTexture > output_stream) {

	// Calculate the dominant direction of the surface normal.
	// 
	// Face normal based on the triangle edges:
	// normalize(cross(input[1].p_world - input[0].p_world, 
	//                 input[2].p_world - input[0].p_world))
	// 
	// Normalization is not needed (i.e. uniform scaling):
	// cross(input[1].p_world - input[0].p_world, 
	//       input[2].p_world - input[0].p_world))
	// 
	// ~ abs(sum of shading normals)
	const float3 abs_n = abs(input[0].n_world 
						   + input[1].n_world 
						   + input[2].n_world);
	const uint axis_xy = (abs_n.x > abs_n.y)        ? 0u : 1u;
	const uint axis    = (abs_n.z > abs_n[axis_xy]) ? 2u : axis_xy;
	
	PSInputPositionNormalTexture output[3];

	// Project the triangle in the dominant direction for rasterization (p),
	// but not for lighting (p_world).
	[unroll]
	for (uint i = 0u; i < 3u; ++i) {

		[flatten]
		switch (axis) {
		case 0u:
			output[i].p.xy = input[i].p_world.yz - g_voxel_grid_center.yz;
			break;
		case 1u:
			output[i].p.xy = input[i].p_world.zx - g_voxel_grid_center.zx;
			break;
		default:
			output[i].p.xy = input[i].p_world.xy - g_voxel_grid_center.xy;
			break;
		}

		// [m_world] * [voxels/m_world] -> [voxels]
		// [voxels]  * [2 m_ndc/voxels] -> [-1,1]
		output[i].p.xy        *= g_voxel_inv_size * 2.0f * g_voxel_grid_inv_resolution;
		#ifdef DISABLE_INVERTED_Z_BUFFER
		output[i].p.zw         = { 0.0f, 1.0f }
		#else  // DISABLE_INVERTED_Z_BUFFER
		output[i].p.zw         = { 1.0f, 1.0f };
		#endif // DISABLE_INVERTED_Z_BUFFER
		output[i].p_world      = input[i].p_world;
		output[i].n_world      = input[i].n_world;
		output[i].tex_material = input[i].tex_material;
		output[i].tex_geometry = input[i].tex_geometry;

		// Output a vertex.
		output_stream.Append(output[i]);
	}
	
	// End the current triangle strip.
	output_stream.RestartStrip();
}
