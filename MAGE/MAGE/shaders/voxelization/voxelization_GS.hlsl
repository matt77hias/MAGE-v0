//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#include "global.hlsli"

//TODO move to buffer
static const float3 g_voxel_grid_center         = 0.0f;
static const float  g_voxel_grid_size           = 1.0f;
static const float  g_voxel_grid_inv_size       = 1.0f;
static const uint   g_voxel_grid_resolution     = 256u;
static const float  g_voxel_grid_inv_resolution = 1.0f / 256.0f; // pixel/texel size

//-----------------------------------------------------------------------------
// Geometry Shader
//-----------------------------------------------------------------------------
[maxvertexcount(3)]
void GS(triangle PSInputPositionNormalTexture input[3],
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
	for (uint i = 0; i < 3; ++i) {
		output[i].p.xyz = input[i].p_view.xyz - g_voxel_grid_center;
	
		[flatten]
		if (dir == 0) {
			output[i].p.xy = output[i].p.yz;
		} else if (dir == 1) {
			output[i].p.xy = output[i].p.zx;
		}

		// [m] * [voxels/m] * [1/voxels]
		output[i].p.xy  *= (g_voxel_grid_inv_size * g_voxel_grid_inv_resolution);
		output[i].p.zw   = float2(Z_NEAR, 1.0f);
		output[i].p_view = input[i].p_view;
		output[i].n_view = input[i].n_view;
		output[i].tex    = input[i].tex;
		output[i].tex2   = input[i].tex2;
	}
	
	// Move vertices for conservative rasterization.
	const float2 delta_10 = normalize(output[1].p.xy - output[0].p.xy);
	const float2 delta_21 = normalize(output[2].p.xy - output[1].p.xy);
	const float2 delta_02 = normalize(output[0].p.xy - output[2].p.xy);

	output[0].p.xy += normalize(delta_02 - delta_10) * g_voxel_grid_inv_resolution;
	output[1].p.xy += normalize(delta_10 - delta_21) * g_voxel_grid_inv_resolution;
	output[2].p.xy += normalize(delta_21 - delta_02) * g_voxel_grid_inv_resolution;

	// Output a triangle strip of three vertices.
	[unroll]
	for (uint j = 0; j < 3; ++j) {
		// Output a vertex.
		output_stream.Append(output[j]);
	}

	// End the current triangle strip.
	output_stream.RestartStrip();
}