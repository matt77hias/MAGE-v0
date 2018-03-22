#ifndef MAGE_HEADER_VCT
#define MAGE_HEADER_VCT

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#include "global.hlsli"

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------

struct Cone {
	float3 apex;
	float3 d; 
	float  tan_aperture;
};

float4 GetRadiance(Texture3D< float4 > voxel_texture, Cone cone) {
	float4 L = 0.0f;

	// Set the initial distance to the voxel diagonal (expressed in normalized 
	// texture coordinates) (= sqrt(2)/g_voxel_grid_resolution) to avoid 
	// sampling the voxel containing the given position.
	float distance = 1.414213562f * g_voxel_grid_inv_resolution;

	while (g_max_cone_distance > distance && 1.0f > L.w) {

		// Obtain the diameter (expressed in normalized texture coordinates).
		//
		//                diameter/2
		// tan_aperture = ---------- <=> diameter = 2 . tan_aperture . distance
		//                 distance
		//
		const float diameter = max(g_voxel_grid_inv_resolution, 
								   2.0f * cone.tan_aperture * distance);
		
		// Obtain the MIP level.
		const float mip_level = log2(diameter * g_voxel_grid_resolution);
		
		// Obtain the position (expressed in normalized texture coordinates).
		const float3 uvw = cone.apex + distance * cone.d;
		
		[branch]
		if ((float)g_voxel_texture_max_mip_level <= mip_level 
			|| any(uvw - saturate(uvw))) {
			break;
		}

		// Obtain the radiance.
		const float4 L_voxel 
			= voxel_texture.SampleLevel(g_linear_clamp_sampler, uvw, mip_level);

		// Perform blending.
		const float inv_alpha = 1.0f - L.w;
		L += inv_alpha * L_voxel;

		distance += g_cone_step_multiplier * diameter;
	}
}

float4 GetRadiance(float3 p, float3 n,
				   Texture3D< float4 > voxel_texture) {

	// Obtain the cone's apex expressed in (expressed in normalized texture 
	// coordinates)
	const float3 apex = WorldToVoxelUVW(p);




	return 0.0f;

}

#endif //MAGE_HEADER_VCT