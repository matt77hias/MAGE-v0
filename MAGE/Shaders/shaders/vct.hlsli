#ifndef MAGE_HEADER_VCT
#define MAGE_HEADER_VCT

//-----------------------------------------------------------------------------
// Engine Configuration
//-----------------------------------------------------------------------------
// Defines			                        | Default
//-----------------------------------------------------------------------------
// BRDF_DOT_EPSILON                         | 1e-5f
// BRDF_D_FUNCTION                          | D_GGX
// BRDF_F_FUNCTION                          | F_Schlick
// BRDF_FUNCTION                            | not defined
// BRDF_MINIMUM_ALPHA                       | 1e-1f
// BRDF_V_FUNCTION                          | G_GXX
// DISABLE_BRDF_DIFFUSE                     | not defined
// DISABLE_BRDF_SPECULAR                    | not defined

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#include "basis.hlsli"
#include "brdf.hlsli"

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------

/**
 A struct of cones.
 */
struct Cone {

	//-------------------------------------------------------------------------
	// Member Variables
	//-------------------------------------------------------------------------

	/**
	 The apex of the cone.
	 */
	float3 m_apex;

	/**
	 The (normalized) direction of the cone.
	 */
	float3 m_d;

	/**
	 The tangent of the half aperture angle of the cone.
	 */
	float m_tan_half_aperture;
};

/**
 A struct of VCT configurations.
 */
struct VCTConfig {

	//-------------------------------------------------------------------------
	// Member Variables
	//-------------------------------------------------------------------------

	/**
	 The maximum mip level of the voxel texture of this VCT configuration.
	 */
	uint m_texture_max_mip_level;

	/**
	 The resolution of the voxel grid for all dimensions of this VCT 
	 configuration.
	 */
	uint m_grid_resolution;

	/**
	 The inverse resolution of the voxel grid for all dimensions of this VCT 
	 configuration.
	 */
	float m_grid_inv_resolution;

	/**
	 The cone step expressed of this VCT configuration in voxel UVW space.
	 */
	float m_cone_step;

	/**
	 The maximal cone distance of this VCT configuration expressed in voxel 
	 UVW space.
	 */
	float m_max_cone_distance;

	/**
	 The voxel texture sampler of this VCT configuration.
	 */
	SamplerState m_sampler;

	/**
	 The texture of this VCT configuration.
	 */
	Texture3D< float4 > m_texture;

	//-------------------------------------------------------------------------
	// Member Methods
	//-------------------------------------------------------------------------

	float3 GetRadiance(Cone cone) {
		float4 L = 0.0f;

		// Set the initial distance to the voxel diagonal (expressed in voxel  
		// UVW space) (= sqrt(2)/m_grid_resolution) to avoid sampling the voxel 
		// containing the apex of the given cone.
		float distance = 1.414213562f * m_grid_inv_resolution;

		while (m_max_cone_distance > distance && 1.0f > L.w) {

			// Obtain the diameter (expressed in voxel UVW space).
			//
			//                     diameter/2
			// tan_half_aperture = ---------- <=> diameter = 2 tan_half_aperture distance
			//                      distance
			//
			const float diameter = max(m_grid_inv_resolution,
									   2.0f * cone.m_tan_half_aperture * distance);
		
			// Obtain the MIP level.
			const float mip_level = log2(diameter * m_grid_resolution);
		
			// Obtain the position (expressed in voxel UVW space).
			const float3 p_uvw = cone.m_apex + distance * cone.m_d;
		
			[branch]
			if ((float)m_texture_max_mip_level <= mip_level 
				|| any(p_uvw - saturate(p_uvw))) {
				break;
			}

			// Obtain the radiance.
			const float4 Li = m_texture.SampleLevel(m_sampler, p_uvw, mip_level);

			// Update the accumulated radiance.
			const float inv_alpha = 1.0f - L.w;
			L += inv_alpha * Li;

			// Update the marching distance.
			distance += m_cone_step;
		}

		return L.xyz;
	}
};

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

float3 GetDiffuseRadiance(float3 p_uvw, float3x3 tangent_to_uvw, 
						  Material material, VCTConfig config) {
	float3 E = 0.0f;

	// Construct a cone.
	Cone cone;
	cone.m_apex = p_uvw;
	// tan(pi/6) = sqrt(3)/3
	cone.m_tan_half_aperture = 0.577350269f;

	[unroll]
	for (uint i = 0u; i < 6u; ++i) {
		// Update the cone.
		const float3 d      = g_cones[i].xyz;
		const float  weight = g_cones[i].w;
		cone.m_d = normalize(mul(d, tangent_to_uvw));

		// Compute the radiance.
		const float3 Li = config.GetRadiance(cone);

		E += weight * Li;
	}

	// Apply a Lambertian BRDF (multiplied by pi).
	return (1.0f - material.m_metalness) * material.m_base_color * E;
}

float3 GetSpecularRadiance(float3 p_uvw, float3 n_world, float3 v_world, 
						   Material material, VCTConfig config) {
	
	// Compute the light (hit-to-light) direction.
	const float3 l_world = ReflectedDirection(n_world, v_world);
	const float3 l_uvw = WorldToVoxelUVWDirection(l_world);
	
	// Construct a cone.
	const Cone cone = {
		p_uvw,
		l_uvw,
		abs(tan(material.m_roughness * g_pi_inv_2))
	};

	// Compute the radiance.
	const float3 L = config.GetRadiance(cone);

	const float3 h       = HalfDirection(l_world, v_world);
	const float  v_dot_h = sat_dot(v_world, h) + BRDF_DOT_EPSILON;
	const float3 F0      = lerp(g_dielectric_F0, material.m_base_color, material.m_metalness);
	const float3 F       = BRDF_F_FUNCTION(v_dot_h, F0);
	
	return F * L;
}

float3 GetRadiance(float3 p_uvw, float3 n_world, float3 v_world, 
				   Material material, VCTConfig config) {

	const float3   n_uvw          = WorldToVoxelUVWDirection(n_world);
	const float3x3 tangent_to_uvw = OrthonormalBasis(n_uvw);

	float3 L = 0.0f;
	
	#ifndef DISABLE_BRDF_DIFFUSE
	L += GetDiffuseRadiance( p_uvw, tangent_to_uvw,   material, config);
	#endif // DISABLE_BRDF_DIFFUSE

	#ifndef DISABLE_BRDF_SPECULAR
	L += GetSpecularRadiance(p_uvw, n_world, v_world, material, config);
	#endif // DISABLE_BRDF_SPECULAR

	return L;
}

#endif // MAGE_HEADER_VCT
