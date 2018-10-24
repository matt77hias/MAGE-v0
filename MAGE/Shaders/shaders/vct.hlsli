#ifndef MAGE_HEADER_VCT
#define MAGE_HEADER_VCT

// Shading is performed in voxel UVW space.

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
		// which is in [m_grid_inv_resolution,inf]
		const float diameter = max(m_grid_inv_resolution,
								   2.0f * cone.m_tan_half_aperture * distance);

		// Obtain the MIP level in [1,inf]
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
		float4 L     = 0.0f;
		float  alpha = 0.0f;

		// Compute the initial distance to avoid sampling the voxel containing
		// the cone's apex.
		float distance = GetOffsetDistance();
		// Compute the maximum cone distance.
		float max_cone_distance = Max(max_cone_distances);

		while (max_cone_distance > distance && 1.0f > alpha) {
			// Compute the MIP level.
			const float mip_level = GetMIPLevel(cone, distance);
			// Compute the position (expressed in voxel UVW space).
			const float3 p_uvw = cone.GetPosition(distance);

			[branch]
			if ((float)m_texture_max_mip_level <= mip_level
				|| any(p_uvw - saturate(p_uvw))) {
				break;
			}

			// Sample the radiance and ambient occlusion.
			const float4 L_step = m_texture.SampleLevel(m_sampler, p_uvw, mip_level);
			// Compute the radiance and ambient occlusion mask.
			const float4 mask = (max_cone_distances >= distance);

			// Update the accumulated radiance and ambient occlusion.
			const float weight = (1.0f - alpha) * L_step.w;
			L     += weight * mask * float4(L_step.xyz, 1.0f);
			alpha += weight;

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
	 @return		The (incoming) radiance and ambient occlusion of the given
					cone for this VCT configuration.
	 */
	float4 GetRadianceAndAO(Cone cone) {
		return GetRadianceAndAO(cone, m_max_cone_distance);
	}

	/**
	 Computes the (incoming) radiance of the given cone for this VCT
	 configuration.

	 @param[in]		cone
					The cone.
	 @param[in]		max_cone_distance
					The maximum cone distance along the direction of the given
					cone expressed in voxel UVW space.
	 @return		The (incoming) radiance of the given cone for this VCT
					configuration.
	 */
	float3 GetRadiance(Cone cone, float max_cone_distance) {
		return GetRadianceAndAO(cone, max_cone_distance).xyz;
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
		return GetRadiance(cone, m_max_cone_distance);
	}

	/**
	 Computes the (incoming) ambient occlusion of the given cone for this VCT
	 configuration.

	 @param[in]		cone
					The cone.
	 @param[in]		max_cone_distance
					The maximum cone distance along the direction of the given
					cone expressed in voxel UVW space.
	 @return		The (incoming) ambient occlusion of the given cone for this
					VCT configuration.
	 */
	float GetAO(Cone cone, float max_cone_distance) {
		return GetRadianceAndAO(cone, max_cone_distance).w;
	}

	/**
	 Computes the (incoming) ambient occlusion of the given cone for this VCT
	 configuration.

	 @param[in]		cone
					The cone.
	 @return		The (incoming) ambient occlusion of the given cone for this
					VCT configuration.
	 */
	float GetAO(Cone cone) {
		return GetAO(cone, m_max_cone_distance);
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

 @pre			@a n_uvw is normalized.
 @param[in]		p_uvw
				The surface position expressed in voxel UVW space.
 @param[in]		n_uvw
				The surface normal expressed in voxel UVW space.
 @param[in]		material
				The material.
 @param[in]		config
				The VCT configuration.
 @return		The (outgoing) diffuse radiance at the given surface position
				using voxel cone tracing.
 */
float3 GetDiffuseRadiance(float3 p_uvw, float3 n_uvw,
						  Material material, VCTConfig config) {

	const float3x3 tangent_to_uvw = OrthonormalBasis(n_uvw);

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

 @pre			@a n_uvw is normalized.
 @pre			@a v_uvw is normalized.
 @param[in]		p_uvw
				The surface position expressed in voxel UVW space.
 @param[in]		n_uvw
				The surface normal expressed in voxel UVW space.
 @param[in]		v_uvw
				The view (hit-to-eye) direction expressed in voxel UVW space.
 @param[in]		material
				The material.
 @param[in]		config
				The VCT configuration.
 @return		The (outgoing) specular radiance at the given surface position
				using voxel cone tracing.
 */
float3 GetSpecularRadiance(float3 p_uvw, float3 n_uvw, float3 v_uvw,
						   Material material, VCTConfig config) {

	// Compute the light (hit-to-light) direction.
	const float3 l_uvw = ReflectedDirection(n_uvw, v_uvw);

	const float3x3 tangent_to_uvw = OrthonormalBasis(l_uvw);
	const float3x3 uvw_to_tangent = transpose(tangent_to_uvw);

	const float3 n_tangent = mul(n_uvw, uvw_to_tangent);
	const float3 v_tangent = mul(v_uvw, uvw_to_tangent);

	const float  n_dot_v = sat_dot(n_uvw, v_uvw) + BRDF_DOT_EPSILON;
	
	const float  nxy    = 0.5f * (n_tangent.x + n_tangent.y);
	const float  nz     = n_tangent.z;
	const float  vxy    = 0.5f * (v_tangent.x + v_tangent.y);
	const float  vz     = v_tangent.z;
	const float  a      = 1.0f + vz;
	const float  a2     = sqr(a);
	const float  b      = nz + n_dot_v;
	const float  alpha  = RoughnessToAlpha(material.m_roughness);
	const float  alpha2 = sqr(alpha);
	const float  sigma2 = (alpha2 * a2 * b) 
		                / ((1.0f - alpha2) * (2.0f*a*nxy*vxy + 2.0f*a2*nz - a*b*vz - 1.5f*b*sqr(vxy)));
	
	//     alpha/2    is in [0,pi/2]
	// sin(alpha/2)   is in [0,1]
	// sin(alpha/2)^2 is in [0,1]
	const float sin2_half_aperture = saturate(abs(sigma2));
	// tan(alpha/2)^2 is in [0,inf]
	// tan(alpha/2)   is in [0,inf]
	const float tan2_half_aperture = SqrSinToSqrTan(sin2_half_aperture);

	// Construct a cone.
	const Cone cone = { p_uvw, l_uvw, sqrt(tan2_half_aperture) };

	// Compute the radiance.
	const float3 L = config.GetRadiance(cone);

	return F0_Specular(material) * L;
}

/**
 Computes the (outgoing) radiance at the given surface position using voxel
 cone tracing.

 @pre			@a n_uvw is normalized.
 @pre			@a v_uvw is normalized.
 @param[in]		p_uvw
				The surface position expressed in voxel UVW space.
 @param[in]		n_uvw
				The surface normal expressed in voxel UVW space.
 @param[in]		v_uvw
				The view (hit-to-eye) direction expressed in voxel UVW space.
 @param[in]		material
				The material.
 @param[in]		config
				The VCT configuration.
 @return		The (outgoing) specular radiance at the given surface position
				using voxel cone tracing.
 */
float3 GetRadiance(float3 p_uvw, float3 n_uvw, float3 v_uvw,
				   Material material, VCTConfig config) {

	float3 L = 0.0f;

	#ifndef DISABLE_BRDF_DIFFUSE
	L += GetDiffuseRadiance( p_uvw, n_uvw,        material, config);
	#endif // DISABLE_BRDF_DIFFUSE

	#ifndef DISABLE_BRDF_SPECULAR
	L += GetSpecularRadiance(p_uvw, n_uvw, v_uvw, material, config);
	#endif // DISABLE_BRDF_SPECULAR

	return L;
}

/**
 Computes the ambient occlusion at the given surface position using voxel cone
 tracing.

 @pre			@a n_uvw is normalized.
 @param[in]		p_uvw
				The surface position expressed in voxel UVW space.
 @param[in]		n_uvw
				The surface normal expressed in voxel UVW space.
 @param[in]		max_cone_distance
				The maximum cone distance expressed in voxel UVW space.
 @param[in]		config
				The VCT configuration.
 @return		The ambient occlusion at the given surface position using voxel
				cone tracing.
 */
float GetAO(float3 p_uvw, float3 n_uvw,
			float max_cone_distance, VCTConfig config) {

	const float3x3 tangent_to_uvw = OrthonormalBasis(n_uvw);

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

#endif // MAGE_HEADER_VCT
