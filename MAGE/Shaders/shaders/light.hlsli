#ifndef MAGE_HEADER_LIGHT
#define MAGE_HEADER_LIGHT

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#include "math.hlsli"

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions: Shadow (Cube) Maps
//-----------------------------------------------------------------------------

/**
 A struct of shadow maps.
 */
struct ShadowMap {

	//-------------------------------------------------------------------------
	// Member Variables
	//-------------------------------------------------------------------------

	/**
	 The PCF sampler comparison state of this shadow map.
	 */
	SamplerComparisonState m_pcf_sampler;

	/**
	 The array of shadow map textures containing the shadow map texture of this 
	 shadow map.
	 */
	Texture2DArray< float > m_maps;

	/**
	 The index into the array of shadow map textures corresponding to the 
	 shadow map texture of this shadow map.
	 */
	uint m_index;

	//-------------------------------------------------------------------------
	// Member Methods
	//-------------------------------------------------------------------------

	/**
	 Computes the shadow factor of this shadow map.

	 @param[in]		p_ndc
					The hit position expressed in light NDC space.
	 @return		The shadow factor of this shadow map corresponding to the 
					given hit position expressed in light NDC space.
	 */
	float ShadowFactor(float3 p_ndc) {
		const float3 location = { NDCtoUV(p_ndc.xy), m_index };

		return  m_maps.SampleCmpLevelZero(m_pcf_sampler, location, p_ndc.z);
	}
};

/**
 A struct of shadow cube maps.
 */
struct ShadowCubeMap {

	//-------------------------------------------------------------------------
	// Member Variables
	//-------------------------------------------------------------------------

	/**
	 The PCF sampler comparison state of this shadow cube map.
	 */
	SamplerComparisonState m_pcf_sampler;

	/**
	 The array of shadow cube map textures containing the shadow cube map 
	 texture of this shadow cube map.
	 */
	TextureCubeArray< float > m_maps;

	/**
	 The index into the array of shadow cube map textures corresponding to the 
	 shadow cube map texture of this shadow cube map.
	 */
	uint m_index;

	//-------------------------------------------------------------------------
	// Member Methods
	//-------------------------------------------------------------------------

	/**
	 Computes the shadow factor of this shadow cube map.

	 @param[in]		p_light
					The hit position expressed in light space.
	 @param[in]		projection_values
					The projection values of the light-to-projection matrix
					[light_to_projection22, light_to_projection32].
	 @return		The shadow factor of this shadow cube map corresponding to 
					the given hit position expressed in light space.
	 */
	float ShadowFactor(float3 p_light, float2 projection_values) {
		const float  p_light_z = Max(abs(p_light));
		const float  p_ndc_z   = ViewZtoNDCZ(p_light_z, projection_values);
		const float4 location  = { p_light, m_index };

		return m_maps.SampleCmpLevelZero(m_pcf_sampler, location, p_ndc_z);
	}
};

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions: Lights
//-----------------------------------------------------------------------------

/**
 A struct of point lights.
 */
struct PointLight {

	//-------------------------------------------------------------------------
	// Member Variables
	//-------------------------------------------------------------------------

	/**
	 The position of this point light expressed in world space.
	 */
	float3 m_p_world;

	/**
	 The inverse of the squared range of this point light expressed in inversed 
	 squared world space.
	 */
	float m_inv_sqr_range;

	//-------------------------------------------------------------------------
	// Member Methods
	//-------------------------------------------------------------------------

	/**
	 Computes the distance attenuation smoothing factor of the intensity of 
	 this point light.

	 @param[in]		sqr_distance
					The squared distance between the lit point and the center 
					of this point light expressed in squared world space.
	 @return		The distance attenuation smoothing factor of the intensity 
					of this point light for the given squared distance.
	 */
	float DistanceAttenuationSmoothingFactor(float sqr_distance) {
		// Frostbite's smoothing:
		//
		//         [    distance^2]^2
		// saturate[1 - ----------]
		//         [      range^2 ]

		return sqr(saturate(1.0f - sqr_distance * m_inv_sqr_range));
	}

	/**
	 Computes the distance attenuation of the intensity of this point light.

	 @param[in]		distance
					The distance between the lit point and the center of this 
					point light expressed in world space.
	 @return		The distance attenuation of the intensity of this point 
					light for the given distance.
	 */
	float DistanceAttenuation(float distance) {
		//                 1
		// df := -----------------------
		//       max(distance^2, 0.01^2)

		const float sqr_distance = sqr(distance);
		const float attenuation  = 1.0f / max(sqr_distance, 1e-4f);
		const float smoothing    = DistanceAttenuationSmoothingFactor(sqr_distance);
	
		return attenuation * smoothing;
	}
};

/**
 A struct of directional lights.
 */
struct DirectionalLight {

	//-------------------------------------------------------------------------
	// Member Variables
	//-------------------------------------------------------------------------

	/**
	 The (orthogonal) irradiance of this directional light.
	 */
	float3 m_E_ortho;
	uint   m_padding0;
	
	/**
	 The (normalized) negated direction of this directional light expressed 
	 in world space.
	 */
	float3 m_neg_d_world;
	uint   m_padding1;

	/**
	 The world-to-projection transformation matrix of this directional light.
	 */
	float4x4 m_world_to_projection;

	//-------------------------------------------------------------------------
	// Member Methods
	//-------------------------------------------------------------------------

	/**
	 Computes the (orthogonal) irradiance contribution of this directional 
	 light.

	 @param[in]		p_world
					The hit position expressed in world space.
	 @param[out]	l_world
					The (normalized) light (hit-to-light) direction expressed 
					in world space.
	 @param[out]	E_ortho
					The (orthogonal) irradiance contribution of this 
					directional light.
	 @param[in]		p_ndc
					The hit position expressed in light NDC space.
	 */
	void Contribution(float3 p_world, 
					  out float3 l_world, out float3 E_ortho, out float3 p_ndc) {
		
		const float4 p_proj = mul(float4(p_world, 1.0f), m_world_to_projection);
		p_ndc   = HomogeneousDivide(p_proj);
	
		l_world = m_neg_d_world;
		E_ortho = (any(1.0f < abs(p_ndc)) || 0.0f > p_ndc.z) ? 0.0f : m_E_ortho;
	}

	/**
	 Computes the (orthogonal) irradiance contribution of this directional 
	 light.

	 @param[in]		p_world
					The hit position expressed in world space.
	 @param[out]	l_world
					The (normalized) light (hit-to-light) direction expressed 
					in world space.
	 @param[out]	E_ortho
					The (orthogonal) irradiance contribution of this 
					directional light.
	 */
	void Contribution(float3 p_world, 
					  out float3 l_world, out float3 E_ortho) {

		float3 l_world0, E_ortho0, p_ndc;
		Contribution(p_world, l_world0, E_ortho0, p_ndc);

		l_world = l_world0;
		E_ortho = E_ortho0;
	}

	/**
	 Computes the (orthogonal) irradiance contribution of this directional 
	 light.

	 @param[in]		map
					The shadow map.
	 @param[in]		p_world
					The hit position expressed in world space.
	 @param[out]	l_world
					The (normalized) light (hit-to-light) direction expressed 
					in world space.
	 @param[out]	E_ortho
					The (orthogonal) irradiance contribution of this 
					directional light.
	 */
	void Contribution(ShadowMap map, float3 p_world,
					  out float3 l_world, out float3 E_ortho) {

		float3 l_world0, E_ortho0, p_ndc;
		Contribution(p_world, l_world0, E_ortho0, p_ndc);

		l_world = l_world0;

		const float shadow_factor = map.ShadowFactor(p_ndc);
		E_ortho = shadow_factor * E_ortho0;
	}
};

/**
 A struct of omni lights.
 */
struct OmniLight : PointLight {

	//-------------------------------------------------------------------------
	// Member Variables
	//-------------------------------------------------------------------------

	/**
	 The radiant intensity of this omni light.
	 */
	float3 m_I;
	uint   m_padding0;

	//-------------------------------------------------------------------------
	// Member Methods
	//-------------------------------------------------------------------------

	/**
	 Computes the (orthogonal) irradiance contribution of this omni light.

	 @param[in]		p_world
					The hit position expressed in world space.
	 @param[out]	l_world
					The (normalized) light (hit-to-light) direction expressed 
					in world space.
	 @param[out]	E_ortho
					The (orthogonal) irradiance contribution of this omni 
					light.
	 */
	void Contribution(float3 p_world, 
					  out float3 l_world, out float3 E_ortho) {

		const float3 l_direction    = m_p_world - p_world;
		const float  l_distance     = length(l_direction);
		const float  inv_l_distance = 1.0f / l_distance;
		l_world = l_direction * inv_l_distance;

		const float da = DistanceAttenuation(l_distance);
		E_ortho = da * m_I;
	}
};

/**
 A struct of spotlights.
 */
struct SpotLight : PointLight {

	//-------------------------------------------------------------------------
	// Member Variables
	//-------------------------------------------------------------------------

	/**
	 The radiant intensity of this spotlight.
	 */
	float3 m_I;

	/**
	 The cosine of the umbra angle of this spotlight.
	 */
	float m_cos_umbra;
	
	/**
	 The (normalized) negated direction of this spotlight expressed in world 
	 space.
	 */
	float3 m_neg_d_world;

	/**
	 The inverse of the cosine range of this spotlight.
	 cos_inv_range = 1 / (cos_penumbra - cos_umbra)
	 */
	float m_cos_inv_range;

	//-------------------------------------------------------------------------
	// Member Methods
	//-------------------------------------------------------------------------

	/**
	 Computes the angular intensity attenuation of this spotlight.

	 @param[in]		cos_theta
					The cosine of the angle between the direction from the 
					center of this spotlight to the lit point, and the 
					direction of this spotlight.
	 @return		The angular intensity attenuation.
	 */
	float AngularAttenuation(float cos_theta) {
		// Frostbite's smoothing: sqr
		return sqr(saturate((cos_theta - m_cos_umbra) * m_cos_inv_range));
	}

	/**
	 Computes the (orthogonal) irradiance contribution of this spotlight.

	 @param[in]		p_world
					The hit position expressed in world space.
	 @param[out]	l_world
					The (normalized) light (hit-to-light) direction expressed 
					in world space.
	 @param[out]	E_ortho
					The (orthogonal) irradiance contribution of this spotlight.
	 */
	void Contribution(float3 p_world, 
					  out float3 l_world, out float3 E_ortho) {

		const float3 l_direction    = m_p_world - p_world;
		const float  l_distance     = length(l_direction);
		const float  inv_l_distance = 1.0f / l_distance;
		l_world = l_direction * inv_l_distance;
	
		const float da        = DistanceAttenuation(l_distance);
		const float cos_theta = dot(m_neg_d_world, l_world);
		const float aa        = AngularAttenuation(cos_theta);
		E_ortho = aa * da * m_I;
	}
};

/**
 A struct of shadow mapped directional lights.
 */
typedef DirectionalLight ShadowMappedDirectionalLight;

/**
 A struct of shadow mapped omni lights.
 */
struct ShadowMappedOmniLight : OmniLight {
	
	//-------------------------------------------------------------------------
	// Member Variables
	//-------------------------------------------------------------------------

	/**
	 The world-to-light transformation matrix of this shadow mapped omni light.
	 */
	float4x4 m_world_to_light;

	/**
	 The projection values of the light-to-projection transformation matrix of 
	 this shadow mapped omni light.
	 projection_values.x = light_to_projection22
	 projection_values.y = light_to_projection32
	 */
	float2 m_projection_values;
	uint2  m_padding0;

	//-------------------------------------------------------------------------
	// Member Methods
	//-------------------------------------------------------------------------

	/**
	 Computes the (orthogonal) irradiance contribution of this omni light.

	 @param[in]		map
					The shadow cube map.
	 @param[in]		p_world
					The hit position expressed in world space.
	 @param[out]	l_world
					The (normalized) light (hit-to-light) direction expressed 
					in world space.
	 @param[out]	E_ortho
					The (orthogonal) irradiance contribution of this omni 
					light.
	 */
	void Contribution(ShadowCubeMap map, float3 p_world,
					  out float3 l_world, out float3 E_ortho) {

		float3 l_world0, E_ortho0;
		OmniLight::Contribution(p_world, l_world0, E_ortho0);

		l_world = l_world0;
		
		const float3 p_light = mul(float4(p_world, 1.0f), m_world_to_light).xyz;
		const float shadow_factor = map.ShadowFactor(p_light, m_projection_values);
		E_ortho = shadow_factor * E_ortho0;
	}
};

/**
 A struct of shadow mapped spotlights.
 */
struct ShadowMappedSpotLight : SpotLight {

	//-------------------------------------------------------------------------
	// Member Variables
	//-------------------------------------------------------------------------

	/**
	 The world-to-projection transformation matrix of this shadow mapped 
	 spotlight.
	 */
	float4x4 m_world_to_projection;

	//-------------------------------------------------------------------------
	// Member Methods
	//-------------------------------------------------------------------------

	/**
	 Computes the (orthogonal) irradiance contribution of this spotlight.

	 @param[in]		map
					The shadow map.
	 @param[in]		p_world
					The hit position expressed in world space.
	 @param[out]	l_world
					The (normalized) light (hit-to-light) direction expressed 
					in world space.
	 @param[out]	E_ortho
					The (orthogonal) irradiance contribution of this spotlight.
	 */
	void Contribution(ShadowMap map, float3 p_world,
					  out float3 l_world, out float3 E_ortho) {

		float3 l_world0, E_ortho0;
		SpotLight::Contribution(p_world, l_world0, E_ortho0);

		l_world = l_world0;

		const float4 p_proj = mul(float4(p_world, 1.0f), m_world_to_projection);
		const float3 p_ndc  = HomogeneousDivide(p_proj);
		const float shadow_factor = map.ShadowFactor(p_ndc);
		E_ortho = shadow_factor * E_ortho0;
	}
};

#endif // MAGE_HEADER_LIGHT