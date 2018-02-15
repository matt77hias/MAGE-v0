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
	// normalize(cross(input[1].p_view - input[0].p_view, 
	//                 input[2].p_view - input[0].p_view))
	// Normalization is not needed (i.e. uniform scaling):
	const float3 abs_n = abs(cross(input[1].p_view - input[0].p_view, 
		                           input[2].p_view - input[0].p_view));
	const uint dir_xy = (abs_n.x > abs_n.y)       ? 0u : 1u;
	const uint dir    = (abs_n.z > abs_n[dir_xy]) ? 2u : dir_xy;
	
	PSInputPositionNormalTexture output[3];

	// Project the triangle in the dominant direction for rasterization (p),
	// but not for lighting (p_view).
	[unroll]
	for (uint i = 0u; i < 3u; ++i) {

		[flatten]
		if (0u == dir) {
			output[i].p.xy = input[i].p_view.yz;
		} 
		else if (1u == dir) {
			output[i].p.xy = input[i].p_view.zx;
		}
		else {
			output[i].p.xy = input[i].p_view.xy;
		}

		// [m_view] * [voxels/m_view] -> [voxels]
		output[i].p.xy  *= g_voxel_inv_size;
		#ifdef DISABLE_INVERTED_Z_BUFFER
		output[i].p.zw   = float2(0.0f, 1.0f);
		#else  // DISABLE_INVERTED_Z_BUFFER
		output[i].p.zw   = float2(1.0f, 1.0f);
		#endif // DISABLE_INVERTED_Z_BUFFER
		output[i].p_view = input[i].p_view;
		output[i].n_view = input[i].n_view;
		output[i].tex    = input[i].tex;
		output[i].tex2   = input[i].tex2;
	}
	
	// For each projected triangle, a slightly larger bounding triangle ensures 
	// that any projected triangle touching a pixel will necessarily touch the 
	// center of this pixel and thus will get a fragment emitted by the rasterizer.
	const float2 delta_10 = normalize(output[1].p.xy - output[0].p.xy);
	const float2 delta_21 = normalize(output[2].p.xy - output[1].p.xy);
	const float2 delta_02 = normalize(output[0].p.xy - output[2].p.xy);
	// [voxels] * [2 m_ndc/voxels] -> [-1,1]
	const float voxel_to_ndc = 2.0f * g_voxel_grid_inv_resolution;
	// Move vertices for conservative rasterization.
	output[0].p.xy = (output[0].p.xy /*+ normalize(delta_02 - delta_10)*/) * voxel_to_ndc;
	output[1].p.xy = (output[1].p.xy /*+ normalize(delta_10 - delta_21)*/) * voxel_to_ndc;
	output[2].p.xy = (output[2].p.xy /*+ normalize(delta_21 - delta_02)*/) * voxel_to_ndc;
	
	// Output a triangle strip of three vertices.
	[unroll]
	for (uint j = 0u; j < 3u; ++j) {
		// Output a vertex.
		output_stream.Append(output[j]);
	}

	// End the current triangle strip.
	output_stream.RestartStrip();
}