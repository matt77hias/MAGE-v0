//-----------------------------------------------------------------------------
// Engine Configuration
//-----------------------------------------------------------------------------
// Defines			                        | Default
//-----------------------------------------------------------------------------
// GROUP_SIZE                               | GROUP_SIZE_3D_DEFAULT

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#include "global.hlsli"
#include "voxelization\voxel.hlsli"

//-----------------------------------------------------------------------------
// UAV
//-----------------------------------------------------------------------------
RW_STRUCTURED_BUFFER(voxel_grid, Voxel,  SLOT_UAV_VOXEL_BUFFER);
RW_TEXTURE_3D(voxel_texture,     float4, SLOT_UAV_VOXEL_TEXTURE);

//-----------------------------------------------------------------------------
// Compute Shader
//-----------------------------------------------------------------------------

#ifndef GROUP_SIZE
	#define GROUP_SIZE GROUP_SIZE_3D_DEFAULT
#endif

[numthreads(GROUP_SIZE, GROUP_SIZE, GROUP_SIZE)]
void CS(uint3 thread_id : SV_DispatchThreadID) {

	[branch]
	if (any(g_voxel_grid_resolution <= thread_id)) {
		return;
	}

	const uint flat_index = FlattenIndex(thread_id, g_voxel_grid_resolution);
	const uint encoded_L  = voxel_grid[flat_index].encoded_L;
	voxel_grid[flat_index].encoded_L = 0u;
	voxel_grid[flat_index].encoded_n = 0u;

	// If encoded_L is equal to the special value 0, representing an empty 
	// voxel, DecodeRadiance may not be called due to potential divisions by 0.
	const float4 L = (0u != encoded_L) 
		? float4(DecodeRadiance(encoded_L), 1.0f) : 0.0f;

	voxel_texture[thread_id] = L;
}