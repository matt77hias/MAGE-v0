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

static const float4 g_cones[] = {
	float4( 0.000000f,  0.000000f, 1.0f, 0.785398163f),
	float4( 0.000000f,  0.866025f, 0.5f, 0.471238898f),
	float4( 0.823639f,  0.267617f, 0.5f, 0.471238898f),
	float4( 0.509037f, -0.700629f, 0.5f, 0.471238898f),
	float4(-0.509037f, -0.700629f, 0.5f, 0.471238898f),
	float4(-0.823639f,  0.267617f, 0.5f, 0.471238898f)
};

float4 GetRadiance(float3 v, float3 p, float3 n, 
				   float3 base_color, float roughness, float metalness, 
				   Texture3D< float4 > voxel_texture) {

	float4 L = 0.0f;

	Cone cone;
	// Obtain the cone's apex expressed in (expressed in normalized texture 
	// coordinates)
	cone.apex = WorldToVoxelUVW(p);
	// tan(pi/3) = sqrt(3)
	cone.tan_aperture = 1.732050808f;

	//TODO: refactor to separate method
	const float3 n_ortho = (0.1f < abs(n.x)) ? float3(0.0f, 1.0f, 0.0f) 
		                                     : float3(1.0f, 0.0f, 0.0f);
	const float3 t = normalize(cross(n_ortho, n));
	const float3 b = cross(n, t);
	const float3x3 TBN = { t, b, n };

	const uint nb_cones = min(g_nb_cones, 16u);
	for (uint i = 0u; i < nb_cones; ++i) {
		const float3 d      = g_cones[i].xyz;
		const float  weight = g_cones[i].w;

		cone.d = normalize(mul(d, TBN));

		L += weight * GetRadiance(voxel_texture, cone) 
			* float4(BRDFxCOS_COMPONENT(n, cone.d, v, base_color, roughness, metalness), 1.0f);
	}

	L.w = saturate(L.w);
	
	return L;
}

#endif //MAGE_HEADER_VCT