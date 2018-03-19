#ifndef MAGE_HEADER_VCT
#define MAGE_HEADER_VCT

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#include "global.hlsli"

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------

static const float XXX = 1.0f;

struct Cone {
	float3 d; 
	float tan_aperture;
};

float4 GetRadiance(float3 p, Texture3D< float4 > voxel_texture, Cone cone) {
	float4 L        = 0.0f;
	float  distance = g_voxel_size;

	// A maximum distance enables early termination in large voxel grids.
	const float max_distance = 100.0f * g_voxel_size;
	while (max_distance > distance && 1.0f > L.w) {

		//                 radius
		// tan_aperture = -------- <=> 2 . radius = 2 . tan_aperture . distance
		//                distance
		//
		// Normalization:
		// size of 1 texel/voxel expressed in world space = g_voxel_size
		const float texel_diameter 
			= max(1.0f, 2.0f * cone.tan_aperture * distance * g_voxel_inv_size);
		
		// Obtain the MIP level.
		const float  mip_level = log2(texel_diameter);
		// Obtain the target position expressed in world space.
		const float3 target = p + distance * cone.d;
		// Obtain the UVW texture coordinates.
		const float3 uvw = WorldToVoxelUVW(target);

		[branch]
		if (any(uvw - saturate(uvw)) || XXX <= mip_level) {
			break;
		}

		// Obtain the radiance.
		const float4 L_mip_level 
			= voxel_texture.SampleLevel(g_linear_clamp_sampler, uvw, mip_level);

		// Perform blending.
		const float inv_alpha = 1.0f - L.w;
		L.xyz += inv_alpha * L_mip_level.xyz;
		L.w   += inv_alpha * L_mip_level.w;

		distance += g_voxel_size;
	}
}

float4 GetRadiance(float3 p, float3 n,
				   Texture3D< float4 > voxel_texture) {

	return 0.0f;

}

#endif //MAGE_HEADER_VCT