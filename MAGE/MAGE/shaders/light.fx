#ifndef MAGE_HEADER_LIGHT
#define MAGE_HEADER_LIGHT

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------

struct DirectionalLight {
	// The intensity of this spotlight .
	float3 I;
	uint padding0;
	// The (normalized) negated direction of this spotlight in camera-space coordinates.
	float3 neg_d;
	uint padding1;
};

struct OmniLight {
	// The position of this omni light in camera-space coordinates.
	float3 p;
	//  The distance at which intensity falloff ends of this omni light.
	float distance_falloff_end;
	// The intensity of this omni light.
	float3 I;
	// The distance inverse range where intensity falloff occurs of this omni light.
	// distance_falloff_range     = distance_falloff_end - distance_falloff_start
	// distance_falloff_inv_range = 1 / distance_falloff_range
	float distance_falloff_inv_range;
};

struct SpotLight {
	// The position of this spotlight in camera-space coordinates.
	float3 p;
	uint padding0;
	// The intensity of this spotlight .
	float3 I;
	uint padding1;
	// The (normalized) negated direction of this spotlight in camera-space coordinates.
	float3 neg_d;
	// The exponent property of this spotlight.
	float exponent_property;
	// The distance at which intensity falloff ends of this spotlight.
	float distance_falloff_end;
	// The distance inverse range where intensity falloff occurs of this spotlight.
	// distance_falloff_range     = distance_falloff_end - distance_falloff_start
	// distance_falloff_inv_range = 1 / distance_falloff_range
	float distance_falloff_inv_range;
	// The cosine of the umbra angle at which intensity falloff ends of this spotlight.
	float cos_umbra;
	// The cosine inverse range where intensity falloff occurs of this spotlight.
	// cos_range     = cos_penumbra - cos_umbra
	// cos_inv_range = 1 / cos_range
	float cos_inv_range;
};

// Calculates the distance fall off at a given distance r.
float DistanceFalloff(float r, float r_end, float r_inv_range) {
	return saturate((r_end - r) * r_inv_range);
}

// Calculates the angular fall off at a given angle theta.
float AngularFalloff(float cos_theta, float cos_umbra, float cos_inv_range, float s_exp) {
	return pow(saturate((cos_theta - cos_umbra) * cos_inv_range), s_exp);
}

// Calculates the maximum contribution of the given omni light for given distance r.
float3 OmniLightMaxContribution(OmniLight light, float r) {
	const float df = DistanceFalloff(r, light.distance_falloff_end, light.distance_falloff_inv_range);
	return df * light.I;
}

// Calculates the maximum contribution of the given spotlight for given distance r and l.
float3 SpotLightMaxContribution(SpotLight light, float r, float3 l) {
	const float cos_theta = dot(light.neg_d, l);
	const float df = DistanceFalloff(r, light.distance_falloff_end, light.distance_falloff_inv_range);
	const float af = AngularFalloff(cos_theta, light.cos_umbra, light.cos_inv_range, light.exponent_property);
	return df * af * light.I;
}

//-----------------------------------------------------------------------------
// Constant Buffers
//-----------------------------------------------------------------------------
cbuffer LightBuffer : register(b0) {
	// LIGHTING
	// The intensity of the ambient light in the scene. 
	float3 g_Ia                            : packoffset(c0);
	// The global flags.
	uint g_flags                           : packoffset(c0.w);
	// The number of directional lights in the scene.
	uint g_nb_directional_lights           : packoffset(c1.x);
	// The number of omni lights in the scene.
	uint g_nb_omni_lights                  : packoffset(c1.y);
	// The number of spotlights in the scene.
	uint g_nb_spot_lights                  : packoffset(c1.z);
	
	// FOGGING
	// The distance at which intensity falloff starts due to fog.
	float g_fog_distance_falloff_start     : packoffset(c1.w);
	// The color of the fog.
	float3 g_fog_color                     : packoffset(c2);
	// The distance inverse range where intensity falloff occurs due to fog.
	float g_fog_distance_falloff_inv_range : packoffset(c2.w);
}

//-----------------------------------------------------------------------------
// Structured Buffers
//-----------------------------------------------------------------------------
StructuredBuffer< DirectionalLight > g_directional_lights : register(t0);
StructuredBuffer< OmniLight > g_omni_lights               : register(t1);
StructuredBuffer< SpotLight > g_spot_lights               : register(t2);

#endif //MAGE_HEADER_LIGHT