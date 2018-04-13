#ifndef MAGE_HEADER_VCT
#define MAGE_HEADER_VCT

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#include "global.hlsli"
#include "basis.hlsli"
#include "material.hlsli"

//-----------------------------------------------------------------------------
// SRVs
//-----------------------------------------------------------------------------
TEXTURE_3D(g_voxel_texture, float4, SLOT_SRV_VOXEL_TEXTURE);

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------

struct Cone {
	// The apex of the cone (expressed in normalized texture coordinates).
	float3 apex;
	// The direction of the cone.
	float3 d;
	// The tangent of the half aperture angle of the cone.
	float  tan_half_aperture;
};

float3 GetVCTRadiance(Cone cone) {
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
								   2.0f * cone.tan_half_aperture * distance);
		
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
			= g_voxel_texture.SampleLevel(g_linear_clamp_sampler, uvw, mip_level);

		// Perform blending.
		const float inv_alpha = 1.0f - L.w;
		L += inv_alpha * L_voxel;

		distance += g_cone_step_multiplier * diameter;
	}

	return L.xyz;
}

/**
 The cones to trace for voxel cone tracing. The first three components 
 represent the direction of the cone over a hemisphere about the z-axis. The 
 last component represents the weight of the cone (solid angle/pdf). The cones 
 are obtained after cosine-weighted hemisphere sampling. The aperture angle is 
 equal to pi/3.
 */
static const float4 g_cones[] = {
	float4( 0.000000f,  0.000000f, 1.0f, 0.785398163f),
	float4( 0.000000f,  0.866025f, 0.5f, 0.471238898f),
	float4( 0.823639f,  0.267617f, 0.5f, 0.471238898f),
	float4( 0.509037f, -0.700629f, 0.5f, 0.471238898f),
	float4(-0.509037f, -0.700629f, 0.5f, 0.471238898f),
	float4(-0.823639f,  0.267617f, 0.5f, 0.471238898f)
};

float3 GetVCTRadiance(float3 v, float3 p, float3 n, Material material) {

	float3 L = 0.0f;

	Cone cone;
	// Obtain the cone's apex expressed in (expressed in normalized texture 
	// coordinates)
	cone.apex = WorldToVoxelUVW(p);
	// tan(pi/6) = sqrt(3)/3
	cone.tan_half_aperture = 0.577350269f;

	const float3x3 tangent_to_world = OrthonormalBasis(n);

	const uint nb_cones = min(g_nb_cones, 6u);
	for (uint i = 0u; i < nb_cones; ++i) {
		const float3 d      = g_cones[i].xyz;
		const float  weight = g_cones[i].w;

		cone.d = normalize(mul(d, tangent_to_world));

		L += BRDF_FUNCTION(n, cone.d, v, material) * GetVCTRadiance(cone) * weight;
	}

	return L;
}

#endif //MAGE_HEADER_VCT
