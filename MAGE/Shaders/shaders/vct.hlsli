#ifndef MAGE_HEADER_VCT
#define MAGE_HEADER_VCT

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#include "material.hlsli"

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

struct VCTConfig {
	uint  voxel_texture_max_mip_level;
	uint  voxel_grid_resolution;
	float voxel_grid_inv_resolution;
	float cone_step_multiplier;
	float max_cone_distance;
	SamplerState voxel_sampler;
	Texture3D< float4 > voxel_texture;
};

float3 GetVCTRadiance(Cone cone, VCTConfig config) {
	float4 L = 0.0f;

	// Set the initial distance to the voxel diagonal (expressed in normalized 
	// texture coordinates) (= sqrt(2)/g_voxel_grid_resolution) to avoid 
	// sampling the voxel containing the given position.
	float distance = 1.414213562f * config.voxel_grid_inv_resolution;

	while (config.max_cone_distance > distance && 1.0f > L.w) {

		// Obtain the diameter (expressed in normalized texture coordinates).
		//
		//                     diameter/2
		// tan_half_aperture = ---------- <=> diameter = 2 tan_half_aperture distance
		//                      distance
		//
		const float diameter = max(config.voxel_grid_inv_resolution,
								   2.0f * cone.tan_half_aperture * distance);
		
		// Obtain the MIP level.
		const float mip_level = log2(diameter * config.voxel_grid_resolution);
		
		// Obtain the position (expressed in normalized texture coordinates).
		const float3 uvw = cone.apex + distance * cone.d;
		
		[branch]
		if ((float)config.voxel_texture_max_mip_level <= mip_level
			|| any(uvw - saturate(uvw))) {
			break;
		}

		// Obtain the radiance.
		const float4 L_voxel 
			= config.voxel_texture.SampleLevel(config.voxel_sampler, uvw, mip_level);

		// Perform blending.
		const float inv_alpha = 1.0f - L.w;
		L += inv_alpha * L_voxel;

		distance += config.cone_step_multiplier;
		//distance *= (1.0f + config.cone_step_multiplier);
		//distance += config.cone_step_multiplier * diameter;
	}

	return L.xyz;
}

/**
 The cones to trace for computing the diffuse indirect illumination using voxel 
 cone tracing. The first three components represent the direction of the cone 
 over a hemisphere about the z-axis. The last component represents the weight 
 of the cone (e.g cosine-weighted solid angle) divided by pi. The cone aperture 
 angle is equal to pi/3.
 */
static const float4 g_cones[] = {
	{ 0.000000f,  0.000000f, 1.0f, 0.25f },
	{ 0.000000f,  0.866025f, 0.5f, 0.15f },
	{ 0.823639f,  0.267617f, 0.5f, 0.15f },
	{ 0.509037f, -0.700629f, 0.5f, 0.15f },
	{-0.509037f, -0.700629f, 0.5f, 0.15f },
	{-0.823639f,  0.267617f, 0.5f, 0.15f },
};

float3 GetVCTRadiance(float3 uvw, float3x3 tangent_to_world, 
					  Material material, VCTConfig config) {
	float3 L = 0.0f;

	Cone cone;
	// Obtain the cone's apex expressed in (expressed in normalized texture 
	// coordinates)
	cone.apex = uvw;
	// tan(pi/6) = sqrt(3)/3
	cone.tan_half_aperture = 0.577350269f;

	[unroll]
	for (uint i = 0u; i < 6u; ++i) {
		const float3 d      = g_cones[i].xyz;
		const float  weight = g_cones[i].w;

		cone.d = normalize(mul(d, tangent_to_world));

		L += weight * GetVCTRadiance(cone, config);
	}

	return material.base_color * L;
}

#endif // MAGE_HEADER_VCT
