//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#include "global.hlsli"
#include "transform\transform.hlsli"

//-----------------------------------------------------------------------------
// SRVs
//-----------------------------------------------------------------------------
TEXTURE_3D(g_voxel_texture, float4, SLOT_SRV_VOXEL_TEXTURE);

//-----------------------------------------------------------------------------
// Vertex Shader
//-----------------------------------------------------------------------------
GSInputPositionColor VS(uint flat_index : SV_VERTEXID) {

	const uint3 index = UnflattenIndex(flat_index, 
									   uint3(g_voxel_grid_resolution, 
											 g_voxel_grid_resolution, 
											 g_voxel_grid_resolution));

	GSInputPositionColor output;
	output.p_world = VoxelIndexToWorld(index);
	output.color   = g_voxel_texture[index];

	return output;
}