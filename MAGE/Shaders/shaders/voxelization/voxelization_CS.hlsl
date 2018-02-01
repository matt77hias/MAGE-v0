//-----------------------------------------------------------------------------
// Engine Configuration
//-----------------------------------------------------------------------------
// Defines			                         | Default
//-----------------------------------------------------------------------------
// GROUP_SIZE                                | 4

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#include "global.hlsli"
#include "voxelization\voxel.hlsli"

//-----------------------------------------------------------------------------
// UAV
//-----------------------------------------------------------------------------
RW_STRUCTURED_BUFFER(voxel_grid, Voxel, SLOT_UAV_VOXEL_BUFFER);
RW_TEXTURE_3D(voxel_texture, float4, SLOT_UAV_VOXEL_TEXTURE);

//-----------------------------------------------------------------------------
// Compute Shader
//-----------------------------------------------------------------------------

#ifndef GROUP_SIZE
	#define GROUP_SIZE 4
#endif

[numthreads(GROUP_SIZE, GROUP_SIZE, GROUP_SIZE)]
void CS(uint3 thread_id : SV_DispatchThreadID) {

	if (any(thread_id >= g_voxel_grid_resolution)) {
		return;
	}

	const uint flat_index = FlattenIndex(thread_id, g_voxel_grid_resolution);

	const float3 L = DecodeRadiance(voxel_grid[flat_index].encoded_L);
	voxel_grid[flat_index].encoded_L = 0u;
	voxel_grid[flat_index].encoded_n = 0u;
	
	voxel_texture[thread_id] = float4(L, 1.0f);
}