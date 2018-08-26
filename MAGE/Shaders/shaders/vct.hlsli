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

	//-------------------------------------------------------------------------
	// Member Methods
	//-------------------------------------------------------------------------

	/**
	 Computes the position at the given distance along the direction of this 
	 cone.

	 @param[in]		distance
					The distance along the direction of this cone.
	 @return		The position at the given distance along the direction of 
					this cone.
	 */
	float3 GetPosition(float distance) {
		return m_apex + distance * m_d;
	}
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

	/**
	 Computes the offset distance of this VCT configuration expressed in voxel 
	 UVW space.

	 @return		The offset distance of this VCT configuration expressed in 
					voxel UVW space.
	 */
	float GetOffsetDistance() {
		// The initial distance is equal to the voxel diagonal expressed in 
		// voxel UVW space (= sqrt(2)/m_grid_resolution) to avoid sampling the 
		// voxel containing a cone's apex or ray's origin.
		return 1.414213562f * m_grid_inv_resolution;
	}

	/**
	 Computes the MIP level of this VCT configuration associated with the given 
	 cone and distance along the direction of the cone.

	 @param[in]		cone
					The cone.
	 @param[in]		distance
					The distance along the direction of this cone expressed in 
					voxel UVW space.
	 @return		The MIP level of this VCT configuration associated with the 
					given cone and distance along the direction of the cone.
	 */
	float GetMIPLevel(Cone cone, float distance) {
		// Obtain the diameter (expressed in voxel UVW space).
		//
		//                     diameter/2
		// tan_half_aperture = ---------- <=> diameter = 2 tan_half_aperture distance
		//                      distance
		//
		const float diameter = max(m_grid_inv_resolution, 
								   2.0f * cone.m_tan_half_aperture * distance);
		
		// Obtain the MIP level.
		return log2(diameter * m_grid_resolution);
	}

	/**
	 Computes the (incoming) radiance and ambient occlusion of the given cone 
	 for this VCT configuration.

	 @param[in]		cone
					The cone.
	 @param[in]		max_cone_distances
					The maximum cone distances along the direction of the given 
					cone expressed in voxel UVW space for the (incoming) 
					radiance and ambient occlusion.
	 @return		The (incoming) radiance and ambient occlusion of the given 
					cone for this VCT configuration.
	 */
	float4 GetRadianceAndAO(Cone cone, float4 max_cone_distances) {
		float4 L = 0.0f;
		
		// Compute the initial distance to avoid sampling the voxel containing 
		// the cone's apex.
		float distance = GetOffsetDistance();
		// Compute the maximum cone distance.
		float max_cone_distance = Max(max_cone_distances);

		while (max_cone_distance > distance && 1.0f > L.w) {
			// Compute the MIP level.
			const float mip_level = GetMIPLevel(cone, distance);
			// Compute the position (expressed in voxel UVW space).
			const float3 p_uvw = cone.GetPosition(distance);

			[branch]
			if ((float)m_texture_max_mip_level <= mip_level
				|| any(p_uvw - saturate(p_uvw))) {
				break;
			}

			// Sample the radiance and alpha.
			const float4 L_step = m_texture.SampleLevel(m_sampler, p_uvw, mip_level);
			// Compute the radiance and alpha mask.
			const float4 mask = (max_cone_distances <= distance);

			// Update the accumulated radiance.
			L += (1.0f - L.w) * mask * L_step;

			// Update the marching distance.
			distance += m_cone_step;
		}

		return L;
	}

	/**
	 Computes the (incoming) radiance and ambient occlusion of the given cone
	 for this VCT configuration.

	 @param[in]		cone
					The cone.
	 @param[in]		max_cone_distances
					The maximum cone distance along the direction of the given
					cone expressed in voxel UVW space for the ambient occlusion.
	 @return		The (incoming) radiance and ambient occlusion of the given
					cone for this VCT configuration.
	 */
	float4 GetRadianceAndAO(Cone cone, float max_cone_distance) {
		const float4 max_cone_distances = { 
			m_max_cone_distance, 
			m_max_cone_distance, 
			m_max_cone_distance, 
			max_cone_distance
		};

		return GetRadianceAndAO(cone, max_cone_distances);
	}

	/**
	 Computes the (incoming) radiance of the given cone for this VCT 
	 configuration.

	 @param[in]		cone
					The cone.
	 @return		The (incoming) radiance of the given cone for this VCT 
					configuration.
	 */
	float3 GetRadiance(Cone cone) {
		return GetRadianceAndAO(cone, m_max_cone_distance).xyz;
	}

	/**
	 Computes the ambient occlusion of the given cone for this VCT 
	 configuration.

	 @param[in]		cone
					The cone.
	 @param[in]		max_cone_distance
					The maximum cone distance along the direction of the given
					cone expressed in voxel UVW space.
	 @return		The ambient occlusion of the given cone for this VCT 
					configuration.
	 */
	float GetAO(Cone cone, float max_cone_distance) {
		return GetRadianceAndAO(cone, max_cone_distance).w;
	}
};

/**
 The cones to trace for computing the (outgoing) diffuse radiance using voxel 
 cone tracing. The first three components represent the direction of the cone 
 over a hemisphere about the z-axis (expressed in tangent space). The last 
 component represents the weight of the cone (e.g cosine-weighted solid angle) 
 divided by pi. The aperture angle of each cone is equal to pi/3.
 */
static const float4 g_cones[] = {
	{ 0.000000f,  0.000000f, 1.0f, 0.25f },
	{ 0.000000f,  0.866025f, 0.5f, 0.15f },
	{ 0.823639f,  0.267617f, 0.5f, 0.15f },
	{ 0.509037f, -0.700629f, 0.5f, 0.15f },
	{-0.509037f, -0.700629f, 0.5f, 0.15f },
	{-0.823639f,  0.267617f, 0.5f, 0.15f },
};

/**
 Computes the (outgoing) diffuse radiance at the given surface position using 
 voxel cone tracing.

 @param[in]		p_uvw
				The surface position expressed in voxel UVW space.
 @param[in]		tangent_to_uvw
				The tangent UVW-to-voxel UVW space transformation matrix.
 @param[in]		material
				The material.
 @param[in]		config
				The VCT configuration.
 @return		The (outgoing) diffuse radiance at the given surface position 
				using voxel cone tracing.
 */
float3 GetDiffuseRadiance(float3 p_uvw, float3x3 tangent_to_uvw, 
						  Material material, VCTConfig config) {
	// Construct a cone.
	Cone cone;
	cone.m_apex = p_uvw;
	// tan(pi/6) = sqrt(3)/3
	cone.m_tan_half_aperture = 0.577350269f;

	float3 E = 0.0f;

	[unroll]
	for (uint i = 0u; i < 6u; ++i) {
		// Update the cone.
		const float3 d      = g_cones[i].xyz;
		const float  weight = g_cones[i].w;
		cone.m_d = normalize(mul(d, tangent_to_uvw));

		// Update the accumulated irradiance (divided by pi).
		E += weight * config.GetRadiance(cone);
	}

	// Apply a Lambertian BRDF (multiplied by pi).
	return (1.0f - material.m_metalness) * material.m_base_color * E;
}

/**
 Computes the (outgoing) specular radiance at the given surface position using 
 voxel cone tracing.

 @pre			@a n_world is normalized.
 @pre			@a v_world is normalized.
 @param[in]		p_uvw
				The surface position expressed in voxel UVW space.
 @param[in]		n_world
				The surface normal expressed in world space.
 @param[in]		v_world
				The view (hit-to-eye) direction expressed in world space.
 @param[in]		material
				The material.
 @param[in]		config
				The VCT configuration.
 @return		The (outgoing) specular radiance at the given surface position 
				using voxel cone tracing.
 */
float3 GetSpecularRadiance(float3 p_uvw, float3 n_world, float3 v_world, 
						   Material material, VCTConfig config) {
	
	// Compute the light (hit-to-light) direction.
	const float3 l_world = ReflectedDirection(n_world, v_world);
	const float3 l_uvw   = WorldToVoxelUVWDirection(l_world);
	
	// Construct a cone.
	const Cone cone = {
		p_uvw,
		l_uvw,
		abs(tan(material.m_roughness * g_pi_inv_2))
	};

	// Compute the radiance.
	const float3 L = config.GetRadiance(cone);
    
	// n_world = h_world
	const float  v_dot_h = sat_dot(v_world, n_world) + BRDF_DOT_EPSILON;
	const float3 F0      = lerp(g_dielectric_F0, material.m_base_color, material.m_metalness);
	const float3 F       = BRDF_F_FUNCTION(v_dot_h, F0);
	
	return F * L;
}

/**
 Computes the (outgoing) radiance at the given surface position using voxel 
 cone tracing.

 @pre			@a n_world is normalized.
 @pre			@a v_world is normalized.
 @param[in]		p_uvw
				The surface position expressed in voxel UVW space.
 @param[in]		n_world
				The surface normal expressed in world space.
 @param[in]		v_world
				The view (hit-to-eye) direction expressed in world space.
 @param[in]		material
				The material.
 @param[in]		config
				The VCT configuration.
 @return		The (outgoing) specular radiance at the given surface position
				using voxel cone tracing.
 */
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

/**
 Computes the ambient occlusion at the given surface position using voxel cone 
 tracing.

 @param[in]		p_uvw
				The surface position expressed in voxel UVW space.
 @param[in]		tangent_to_uvw
				The tangent UVW-to-voxel UVW space transformation matrix.
 @param[in]		max_cone_distance
				The maximum cone distance expressed in voxel UVW space.
 @param[in]		config
				The VCT configuration.
 @return		The ambient occlusion at the given surface position using voxel 
				cone tracing.
 */
float GetAO(float3 p_uvw, float3x3 tangent_to_uvw,
			float max_cone_distance, VCTConfig config) {

	// Construct a cone.
	Cone cone;
	cone.m_apex = p_uvw;
	// tan(pi/6) = sqrt(3)/3
	cone.m_tan_half_aperture = 0.577350269f;

	float ao = 0.0f;

	[unroll]
	for (uint i = 0u; i < 6u; ++i) {
		// Update the cone.
		const float3 d      = g_cones[i].xyz;
		const float  weight = g_cones[i].w;
		cone.m_d = normalize(mul(d, tangent_to_uvw));

		// Update the accumulated ambient occlusion.
		ao += weight * config.GetAO(cone, max_cone_distance);
	}

	return ao;
}

/**
 Computes the ambient occlusion at the given surface position using voxel cone
 tracing.

 @pre			@a n_world is normalized.
 @param[in]		p_uvw
				The surface position expressed in voxel UVW space.
 @param[in]		n_world
				The surface normal expressed in world space.
 @param[in]		max_cone_distance
				The maximum cone distance expressed in voxel UVW space.
 @param[in]		config
				The VCT configuration.
 @return		The ambient occlusion at the given surface position using voxel
				cone tracing.
 */
float GetAO(float3 p_uvw, float3 n_world, 
			float max_cone_distance, VCTConfig config) {

	const float3   n_uvw = WorldToVoxelUVWDirection(n_world);
	const float3x3 tangent_to_uvw = OrthonormalBasis(n_uvw);

	return GetAO(p_uvw, tangent_to_uvw, max_cone_distance, config);
}

#endif // MAGE_HEADER_VCT
