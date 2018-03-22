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

	return L;
}

static const float3 g_cone_directions[] = {
	float3( 0.577350f,  0.577350f,  0.577350f),
	float3( 0.577350f, -0.577350f, -0.577350f),
	float3(-0.577350f,  0.577350f, -0.577350f),
	float3(-0.577350f, -0.577350f,  0.577350f),
	float3(-0.903007f, -0.182696f, -0.388844f),
	float3(-0.903007f,  0.182696f,  0.388844f),
	float3( 0.903007f, -0.182696f,  0.388844f),
	float3( 0.903007f,  0.182696f, -0.388844f),
	float3(-0.388844f, -0.903007f, -0.182696f),
	float3( 0.388844f, -0.903007f,  0.182696f),
	float3( 0.388844f,  0.903007f, -0.182696f),
	float3(-0.388844f,  0.903007f,  0.182696f),
	float3(-0.182696f, -0.388844f, -0.903007f),
	float3( 0.182696f,  0.388844f, -0.903007f),
	float3(-0.182696f,  0.388844f,  0.903007f),
	float3( 0.182696f, -0.388844f,  0.903007f)
};

float4 GetRadiance(float3 p, float3 n,
				   Texture3D< float4 > voxel_texture) {

	float4 L = 0.0f;

	Cone cone;

	// Obtain the cone's apex expressed in (expressed in normalized texture 
	// coordinates)
	cone.apex = WorldToVoxelUVW(p);
	// tan(g_pi/8) = sqrt(2) - 1
	cone.tan_aperture = 0.414213562f;

	const uint nb_cones = min(g_nb_cones, 16u);
	for (uint i = 0u; i < nb_cones; ++i) {

		//TODO: cosine-weighted sampling instead
		cone.d = reflect(g_cone_directions[i], n);
		cone.d *= 0.0f > dot(cone.d, n) ? -1.0f : 1.0f;
		
		L += GetRadiance(voxel_texture, cone);
	}

	L /= nb_cones;
	L.w = saturate(L.w);
	return L;
}

#endif //MAGE_HEADER_VCT