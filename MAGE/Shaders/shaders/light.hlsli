#ifndef MAGE_HEADER_LIGHT
#define MAGE_HEADER_LIGHT

//-----------------------------------------------------------------------------
// Engine Configuration
//-----------------------------------------------------------------------------
// Defines			                        | Default
//-----------------------------------------------------------------------------
// LIGHT_DISTANCE_ATTENUATION_COMPONENT     | DistanceAttenuation
// LIGHT_ANGULAR_ATTENUATION_COMPONENT      | AngularAttenuation
// FOG_FACTOR_COMPONENT                     | FogFactor_Exponential

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#include "math.hlsli"

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------

/**
 A struct of directional lights.
 */
struct DirectionalLight {
	// The radiance of this directional light.
	float3 L;
	uint padding0;
	// The (normalized) negated direction of this directional light expressed 
	// in world space.
	float3 neg_d;
	uint padding1;
};

/**
 A struct of omni lights.
 */
struct OmniLight {
	// The position of this omni light expressed in world space.
	float3 p;
	// The inverse squared range of this omni light.
	float inv_sqr_range;
	// The radiant intensity of this omni light.
	float3 I;
	uint padding0;
};

/**
 A struct of spotlights.
 */
struct SpotLight {
	// The position of this omni light expressed in world space.
	float3 p;
	// The inverse squared range of this spotlight.
	float inv_sqr_range;
	// The radiant intensity of this spotlight.
	float3 I;
	// The cosine of the umbra angle of this spotlight.
	float cos_umbra;
	// The (normalized) negated direction of this directional light expressed 
	// in world space.
	float3 neg_d;
	// The cosine inverse range of this spotlight.
	// cos_inv_range = 1 / (cos_penumbra - cos_umbra)
	float cos_inv_range;
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
	// The projection values of the light-to-projection transformation matrix.
	// projection_values.x = light_to_projection22
	// projection_values.y = light_to_projection32
	float2 projection_values;
	uint2 padding0;
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
 Calculates the distance intensity attenuation smoothing factor of a light.

 @param[in]		sqr_distance
				The squared distance between the lit point and the center of 
				the light.
 @param[in]		inv_sqr_range
				The inverse squared range of the light.
 @return		The distance intensity attenuation smoothing factor.
 */
float DistanceAttenuationSmoothingFactor(float sqr_distance, float inv_sqr_range) {
	// Frostbite's smoothing:
	//
	//         [    distance^2]^2
	// saturate[1 - ----------]
	//         [      range^2 ]

	return sqr(saturate(1.0f - sqr_distance * inv_sqr_range));
}

/**
 Calculates the distance intensity attenuation of a light.

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
 Calculates the angular intensity attenuation of a light.

 @param[in]		cos_theta
				The cosine of the angle between the direction from the center 
				of the light to the lit point, and the light direction.
 @param[in]		cos_umbra
				The cosine of the umbra angle of the light.
 @param[in]		cos_inv_range
				The cosine inverse range of the light.
 @return		The angular intensity attenuation.
 */
float AngularAttenuation(float cos_theta, float cos_umbra, float cos_inv_range) {
	// Frostbite's smoothing: sqr
	return sqr(saturate((cos_theta - cos_umbra) * cos_inv_range));
}

#ifndef LIGHT_DISTANCE_ATTENUATION_COMPONENT
	#define LIGHT_DISTANCE_ATTENUATION_COMPONENT DistanceAttenuation
#endif // LIGHT_DISTANCE_ATTENUATION_COMPONENT

#ifndef LIGHT_ANGULAR_ATTENUATION_COMPONENT
	#define LIGHT_ANGULAR_ATTENUATION_COMPONENT AngularAttenuation
#endif // LIGHT_ANGULAR_ATTENUATION_COMPONENT

/**
 Calculates the radiance contribution of the given directional light.

 @param[in]		light
				The directional light.
 @param[out]	l
				The light (hit-to-light) direction expressed in world space.
 @param[out]	L
				The radiance contribution of the given directional light.
 */
void Contribution(DirectionalLight light, out float3 l, out float3 L) {
	l = light.neg_d;
	L = light.L;
}

/**
 Calculates the intensity contribution of the given omni light.

 @param[in]		light
				The omni light.
 @param[in]		p
				The hit position expressed in world space.
 @param[out]	l
				The light (hit-to-light) direction expressed in world space.
 @param[out]	L
				The radiance contribution of the given omni light.
 */
void Contribution(OmniLight light, float3 p, out float3 l, out float3 L) {
	const float3 l_direction    = light.p - p;
	const float  l_distance     = length(l_direction);
	const float  inv_l_distance = 1.0f / l_distance;
	l = l_direction * inv_l_distance;

	const float da = LIGHT_DISTANCE_ATTENUATION_COMPONENT(l_distance,
														  light.inv_sqr_range);
	L = da * light.I;
}

/**
 Calculates the intensity contribution of the given spotlight.

 @param[in]		light
				The spotlight.
 @param[in]		p
				The hit position expressed in world space.
 @param[out]	l
				The light (hit-to-light) direction expressed in world space.
 @param[out]	L
				The radiance contribution of the given spotlight.
 */
void Contribution(SpotLight light, float3 p, out float3 l, out float3 L) {
	const float3 l_direction    = light.p - p;
	const float  l_distance     = length(l_direction);
	const float  inv_l_distance = 1.0f / l_distance;
	l = l_direction * inv_l_distance;
	
	const float da = LIGHT_DISTANCE_ATTENUATION_COMPONENT(l_distance,
														  light.inv_sqr_range);
	const float cos_theta = dot(light.neg_d, l);
	const float aa = LIGHT_ANGULAR_ATTENUATION_COMPONENT(cos_theta, 
														 light.cos_umbra, 
														 light.cos_inv_range);
	L = aa * da * light.I;
}

/**
 Calculates the shadow factor.

 @pre			@a shadow_maps must contain a shadow map at index @a index.
 @param[in]		pcf_sampler
				The PCF sampler comparison state.
 @param[in]		shadow_maps
				The array of shadow maps.
 @param[in]		index
				The index into the array of shadow maps.
 @param[in]		p_ndc
				The hit position expressed in light NDC space.
 @return		The shadow factor.
 */
float ShadowFactor(SamplerComparisonState pcf_sampler, 
				   Texture2DArray< float > shadow_maps, uint index, 
				   float3 p_ndc) {

	const float3 location = float3(NDCtoUV(p_ndc.xy), index);

	return shadow_maps.SampleCmpLevelZero(pcf_sampler, location, p_ndc.z);
}

/**
 Calculates the shadow factor.

 @pre			@a shadow_maps must contain a shadow cube map at index @a index.
 @param[in]		pcf_sampler
				The PCF sampler comparison state.
 @param[in]		shadow_maps
				The array of shadow cube maps.
 @param[in]		index
				The index into the array of shadow cube maps.
 @param[in]		p_light
				The hit position expressed in light space.
 @param[in]		projection_values
				The projection values of the light-to-projection matrix
				[light_to_projection22, light_to_projection32].
 @return		The shadow factor.
 */
float ShadowFactor(SamplerComparisonState pcf_sampler, 
				   TextureCubeArray< float > shadow_maps, uint index, 
				   float3 p_light, float2 projection_values) {

	const float  p_light_z = Max(abs(p_light));
	const float  p_ndc_z   = ViewZtoNDCZ(p_light_z, projection_values);
	const float4 location  = float4(p_light, index);

	return shadow_maps.SampleCmpLevelZero(pcf_sampler, location, p_ndc_z);
}

/**
 Calculates the radiance contribution of the given directional light.

 @pre			@a shadow_maps must contain a shadow map at index @a index.
 @param[in]		light
				The directional light.
 @param[in]		pcf_sampler
				The PCF sampler comparison state.
 @param[in]		shadow_maps
				The array of shadow maps.
 @param[in]		index
				The light index into the array of shadow maps.
 @param[in]		p
				The hit position expressed in world space.
 @param[out]	l
				The light (hit-to-light) direction expressed in world space.
 @param[out]	L
				The radiance contribution.
 */
void Contribution(ShadowMappedDirectionalLight light, 
				  SamplerComparisonState pcf_sampler, 
				  Texture2DArray< float > shadow_maps, uint index, 
				  float3 p, out float3 l, out float3 L) {

	float3 l0, L0;
	Contribution(light.light, l0, L0);

	l = l0;
	const float4 p_proj = mul(float4(p, 1.0f), light.world_to_projection);
	const float3 p_ndc  = HomogeneousDivide(p_proj);
	L = L0 * ShadowFactor(pcf_sampler, shadow_maps, index, p_ndc);
}

/**
 Calculates the intensity contribution of the given omni light.

 @pre			@a shadow_maps must contain a shadow cube map at index @a index.
 @param[in]		light
				The omni light.
 @param[in]		pcf_sampler
				The PCF sampler comparison state.
 @param[in]		shadow_maps
				The array of shadow cube maps.
 @param[in]		index
				The light index into the array of shadow cube maps.
 @param[in]		p
				The hit position expressed in world space.
 @param[out]	l
				The light (hit-to-light) direction expressed in world space.
 @param[out]	L
				The radiance contribution.
 */
void Contribution(ShadowMappedOmniLight light, 
				  SamplerComparisonState pcf_sampler, 
				  TextureCubeArray< float > shadow_maps, uint index, 
				  float3 p, out float3 l, out float3 L) {

	float3 l0, L0;
	Contribution(light.light, p, l0, L0);

	l = l0;
	const float3 p_light = p - light.light.p;
	L = L0 * ShadowFactor(pcf_sampler, shadow_maps, index, 
						  p_light, light.projection_values);
}

/**
 Calculates the intensity contribution of the given spotlight.

 @pre			@a shadow_maps must contain a shadow map at index @a index.
 @param[in]		light
				The spotlight.
 @param[in]		pcf_sampler
				The PCF sampler comparison state.
 @param[in]		shadow_maps
				The array of shadow maps.
 @param[in]		index
				The light index into the array of shadow maps.
 @param[in]		p
				The hit position expressed in world space.
 @param[out]	l
				The light (hit-to-light) direction expressed in world space.
 @param[out]	L
				The radiance contribution.
 */
void Contribution(ShadowMappedSpotLight light, 
				  SamplerComparisonState pcf_sampler, 
				  Texture2DArray< float > shadow_maps, uint index, 
				  float3 p, out float3 l, out float3 L) {

	float3 l0, L0;
	Contribution(light.light, p, l0, L0);

	l = l0;
	const float4 p_proj = mul(float4(p, 1.0f), light.world_to_projection);
	const float3 p_ndc  = HomogeneousDivide(p_proj);
	L = L0 * ShadowFactor(pcf_sampler, shadow_maps, index, p_ndc);
}

/**
 Calculates the exponential fog factor.

 @param[in]		distance
				The distance between the lit point and the eye.
 @param[in]		density
				The density of the fog.
 @return		The exponential fog factor.
 */
float FogFactor_Exponential(float distance, float density) {
	return exp(-distance * density);
}

#ifndef FOG_FACTOR_COMPONENT
	#define FOG_FACTOR_COMPONENT FogFactor_Exponential
#endif // FOG_FACTOR_COMPONENT

#endif //MAGE_HEADER_LIGHT