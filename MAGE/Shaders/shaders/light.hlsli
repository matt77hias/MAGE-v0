#ifndef MAGE_HEADER_LIGHT
#define MAGE_HEADER_LIGHT

//-----------------------------------------------------------------------------
// Engine Configuration
//-----------------------------------------------------------------------------
// Defines			                        | Default
//-----------------------------------------------------------------------------
// FOG_FACTOR_FUNCTION                      | FogFactor_Exponential
// LIGHT_ANGULAR_ATTENUATION_FUNCTION       | AngularAttenuation
// LIGHT_DISTANCE_ATTENUATION_FUNCTION      | DistanceAttenuation

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#include "math.hlsli"

//-----------------------------------------------------------------------------
// Engine Defines
//-----------------------------------------------------------------------------

#ifndef LIGHT_DISTANCE_ATTENUATION_FUNCTION
	#define LIGHT_DISTANCE_ATTENUATION_FUNCTION DistanceAttenuation
#endif // LIGHT_DISTANCE_ATTENUATION_FUNCTION

#ifndef LIGHT_ANGULAR_ATTENUATION_FUNCTION
	#define LIGHT_ANGULAR_ATTENUATION_FUNCTION AngularAttenuation
#endif // LIGHT_ANGULAR_ATTENUATION_FUNCTION

#ifndef FOG_FACTOR_FUNCTION
	#define FOG_FACTOR_FUNCTION FogFactor_Exponential
#endif // FOG_FACTOR_FUNCTION

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions: Attenuation
//-----------------------------------------------------------------------------

/**
 Computes the distance intensity attenuation smoothing factor of a light.

 @param[in]		sqr_distance
				The squared distance between the lit point and the center of 
				the light.
 @param[in]		inv_sqr_range
				The inverse squared range of the light.
 @return		The distance intensity attenuation smoothing factor.
 */
float DistanceAttenuationSmoothingFactor(float sqr_distance, 
										 float inv_sqr_range) {
	// Frostbite's smoothing:
	//
	//         [    distance^2]^2
	// saturate[1 - ----------]
	//         [      range^2 ]

	return sqr(saturate(1.0f - sqr_distance * inv_sqr_range));
}

/**
 Computes the distance intensity attenuation of a light.

 @param[in]		distance
				The distance between the lit point and the center of the light.
 @param[in]		inv_sqr_range
				The inverse squared range of the light.
 @return		The distance intensity attenuation.
 */
float DistanceAttenuation(float distance, float inv_sqr_range) {
	//                 1
	// df := -----------------------
	//       max(distance^2, 0.01^2)

	const float sqr_distance = sqr(distance);
	const float attenuation  = 1.0f / max(sqr_distance, 0.0001f);
	const float smoothing    = DistanceAttenuationSmoothingFactor(sqr_distance, inv_sqr_range);
	
	return attenuation * smoothing;
}

/**
 Computes the angular intensity attenuation of a light.

 @param[in]		cos_theta
				The cosine of the angle between the direction from the center 
				of the light to the lit point, and the light direction.
 @param[in]		cos_umbra
				The cosine of the umbra angle of the light.
 @param[in]		cos_inv_range
				The cosine inverse range of the light.
 @return		The angular intensity attenuation.
 */
float AngularAttenuation(float cos_theta, 
						 float cos_umbra, 
						 float cos_inv_range) {

	// Frostbite's smoothing: sqr
	return sqr(saturate((cos_theta - cos_umbra) * cos_inv_range));
}

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions: Shadow (Cube) Maps
//-----------------------------------------------------------------------------

/**
 A struct of shadow maps.
 */
struct ShadowMap {
	// The PCF sampler comparison state.
	SamplerComparisonState pcf_sampler;
	// The array of shadow maps.
	Texture2DArray< float > maps;
	// The index into the array of shadow maps.
	uint index;
};

/**
 A struct of shadow cube maps.
 */
struct ShadowCubeMap {
	// The PCF sampler comparison state.
	SamplerComparisonState pcf_sampler;
	// The array of shadow cube maps.
	TextureCubeArray< float > maps;
	// The index into the array of shadow cube maps.
	uint index;
};

/**
 Computes the shadow factor.

 @pre			@a shadow_maps must contain a shadow map at index @a index.
 @param[in]		shadow_map
				The shadow map.
 @param[in]		p_ndc
				The hit position expressed in light NDC space.
 @return		The shadow factor.
 */
float ShadowFactor(ShadowMap shadow_map, float3 p_ndc) {
	const float3 location = float3(NDCtoUV(p_ndc.xy), shadow_map.index);

	return shadow_map.maps
		.SampleCmpLevelZero(shadow_map.pcf_sampler, location, p_ndc.z);
}

/**
 Computes the shadow factor.

 @pre			@a shadow_maps must contain a shadow cube map at index @a index.
 @param[in]		shadow_cube_map
				The shadow cube map.
 @param[in]		p_light
				The hit position expressed in light space.
 @param[in]		projection_values
				The projection values of the light-to-projection matrix
				[light_to_projection22, light_to_projection32].
 @return		The shadow factor.
 */
float ShadowFactor(ShadowCubeMap shadow_cube_map, float3 p_light, 
				   float2 projection_values) {

	const float  p_light_z = Max(abs(p_light));
	const float  p_ndc_z   = ViewZtoNDCZ(p_light_z, projection_values);
	const float4 location  = float4(p_light, shadow_cube_map.index);

	return shadow_cube_map.maps
		.SampleCmpLevelZero(shadow_cube_map.pcf_sampler, location, p_ndc_z);
}

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions: Lights
//-----------------------------------------------------------------------------

/**
 A struct of directional lights.
 */
struct DirectionalLight {
	// The (orthogonal) irradiance of this directional light.
	float3 E;
	uint   padding0;
	// The (normalized) negated direction of this directional light expressed 
	// in world space.
	float3 neg_d;
	uint   padding1;
};

/**
 A struct of omni lights.
 */
struct OmniLight {
	// The position of this omni light expressed in world space.
	float3 p;
	// The inverse squared range of this omni light.
	float  inv_sqr_range;
	// The radiant intensity of this omni light.
	float3 I;
	uint   padding0;
};

/**
 A struct of spotlights.
 */
struct SpotLight {
	// The position of this omni light expressed in world space.
	float3 p;
	// The inverse squared range of this spotlight.
	float  inv_sqr_range;
	// The radiant intensity of this spotlight.
	float3 I;
	// The cosine of the umbra angle of this spotlight.
	float  cos_umbra;
	// The (normalized) negated direction of this directional light expressed 
	// in world space.
	float3 neg_d;
	// The cosine inverse range of this spotlight.
	// cos_inv_range = 1 / (cos_penumbra - cos_umbra)
	float  cos_inv_range;
};

/**
 A struct of shadow mapped directional lights.
 */
struct ShadowMappedDirectionalLight {
	// The directional light.
	DirectionalLight light;
	// The world-to-projection transformation matrix.
	float4x4 world_to_projection;
};

/**
 A struct of shadow mapped omni lights.
 */
struct ShadowMappedOmniLight {
	// The omni light.
	OmniLight light;
	// The world-to-light transformation matrix.
	float4x4 world_to_light;
	// The projection values of the light-to-projection transformation matrix.
	// projection_values.x = light_to_projection22
	// projection_values.y = light_to_projection32
	float2   projection_values;
	uint2    padding0;
};

/**
 A struct of shadow mapped spotlights.
 */
struct ShadowMappedSpotLight {
	// The spotlight.
	SpotLight light;
	// The world-to-projection transformation matrix.
	float4x4 world_to_projection;
};

/**
 Computes the irradiance contribution of the given directional light.

 @param[in]		light
				The directional light.
 @param[out]	l
				The light (hit-to-light) direction expressed in world space.
 @param[out]	E
				The (orthogonal) irradiance contribution of the given 
				directional light.
 */
void Contribution(DirectionalLight light, out float3 l, out float3 E) {
	l = light.neg_d;
	E = light.E;
}

/**
 Computes the irradiance contribution of the given omni light.

 @param[in]		light
				The omni light.
 @param[in]		p
				The hit position expressed in world space.
 @param[out]	l
				The light (hit-to-light) direction expressed in world space.
 @param[out]	E
				The (orthogonal) irradiance contribution of the given omni 
				light.
 */
void Contribution(OmniLight light, float3 p, out float3 l, out float3 E) {
	const float3 l_direction    = light.p - p;
	const float  l_distance     = length(l_direction);
	const float  inv_l_distance = 1.0f / l_distance;
	l = l_direction * inv_l_distance;

	const float da = LIGHT_DISTANCE_ATTENUATION_FUNCTION(l_distance, 
														 light.inv_sqr_range);
	E = da * light.I;
}

/**
 Computes the irradiance contribution of the given spotlight.

 @param[in]		light
				The spotlight.
 @param[in]		p
				The hit position expressed in world space.
 @param[out]	l
				The light (hit-to-light) direction expressed in world space.
 @param[out]	E
				The (orthogonal) irradiance contribution of the given 
				spotlight.
 */
void Contribution(SpotLight light, float3 p, out float3 l, out float3 E) {
	const float3 l_direction    = light.p - p;
	const float  l_distance     = length(l_direction);
	const float  inv_l_distance = 1.0f / l_distance;
	l = l_direction * inv_l_distance;
	
	const float da = LIGHT_DISTANCE_ATTENUATION_FUNCTION(l_distance, 
														 light.inv_sqr_range);
	const float cos_theta = dot(light.neg_d, l);
	const float aa = LIGHT_ANGULAR_ATTENUATION_FUNCTION(cos_theta, 
														light.cos_umbra, 
														light.cos_inv_range);
	E = aa * da * light.I;
}

/**
 Computes the irradiance contribution of the given directional light.

 @pre			@a shadow_maps must contain a shadow map at index @a index.
 @param[in]		light
				The directional light.
 @param[in]		shadow_map
				The shadow map.
 @param[in]		p
				The hit position expressed in world space.
 @param[out]	l
				The light (hit-to-light) direction expressed in world space.
 @param[out]	E
				The (orthogonal) irradiance contribution of the given 
				directional light.
 */
void Contribution(ShadowMappedDirectionalLight light, ShadowMap shadow_map,
				  float3 p, out float3 l, out float3 E) {

	float3 l0, E0;
	Contribution(light.light, l0, E0);

	l = l0;
	const float4 p_proj = mul(float4(p, 1.0f), light.world_to_projection);
	const float3 p_ndc  = HomogeneousDivide(p_proj);
	E = E0 * ShadowFactor(shadow_map, p_ndc);
}

/**
 Computes the irradiance contribution of the given omni light.

 @pre			@a shadow_maps must contain a shadow cube map at index @a index.
 @param[in]		light
				The omni light.
 @param[in]		shadow_cube_map
				The shadow cube map.
 @param[in]		p
				The hit position expressed in world space.
 @param[out]	l
				The light (hit-to-light) direction expressed in world space.
 @param[out]	E
				The (orthogonal) irradiance contribution of the given omni 
				light.
 */
void Contribution(ShadowMappedOmniLight light, ShadowCubeMap shadow_cube_map,
				  float3 p, out float3 l, out float3 E) {

	float3 l0, E0;
	Contribution(light.light, p, l0, E0);

	l = l0;
	const float3 p_light = mul(float4(p, 1.0f), light.world_to_light).xyz;
	E = E0 * ShadowFactor(shadow_cube_map, p_light, light.projection_values);
}

/**
 Computes the irradiance contribution of the given spotlight.

 @pre			@a shadow_maps must contain a shadow map at index @a index.
 @param[in]		light
				The spotlight.
 @param[in]		shadow_map
				The shadow map.
 @param[in]		p
				The hit position expressed in world space.
 @param[out]	l
				The light (hit-to-light) direction expressed in world space.
 @param[out]	E
				The (orthogonal) irradiance contribution of the given 
				spotlight.
 */
void Contribution(ShadowMappedSpotLight light, ShadowMap shadow_map,
				  float3 p, out float3 l, out float3 E) {

	float3 l0, E0;
	Contribution(light.light, p, l0, E0);

	l = l0;
	const float4 p_proj = mul(float4(p, 1.0f), light.world_to_projection);
	const float3 p_ndc  = HomogeneousDivide(p_proj);
	E = E0 * ShadowFactor(shadow_map, p_ndc);
}

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions: Fog
//-----------------------------------------------------------------------------

/**
 Computes the exponential fog factor.

 @param[in]		distance
				The distance between the lit point and the eye.
 @param[in]		density
				The density of the fog.
 @return		The exponential fog factor.
 */
float FogFactor_Exponential(float distance, float density) {
	return exp(-distance * density);
}

#endif // MAGE_HEADER_LIGHT