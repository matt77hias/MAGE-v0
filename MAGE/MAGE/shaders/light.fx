struct OmniLight {
	// The position of the omni light in camera space.
	float4 p;
	// The intensity of the omni light.
	float3 I;
	// The distance at which intensity falloff starts.
	float distance_falloff_start;
	// The distance at which intensity falloff ends.
	float distance_falloff_end;
	uint padding[3];
};

struct SpotLight {
	// The position of the spotlight in camera space.
	float4 p;
	// The intensity of the spotlight.
	float3 I;
	// The exponent property of the spotlight.
	float exponent_property;
	// The direction of the spotlight in camera space.
	float3 d;
	// The distance at which intensity falloff starts.
	float distance_falloff_start;
	// The distance at which intensity falloff ends.
	float distance_falloff_end;
	// The cosine of the penumbra angle at which intensity falloff starts.
	float cos_penumbra;
	// The cosine of the umbra angle at which intensity falloff ends.
	float cos_umbra;
	uint padding;
};

// Calculates the distance fall off at a given distance r.
float DistanceFalloff(float r, float r_start, float r_end) {
	return saturate((r_end - r) / (r_end - r_start));
}

// Calculates the angular fall off at a given angle theta.
float AngularFalloff(float cos_theta, float cos_penumbra, float cos_umbra, float s_exp) {
	return pow(saturate((cos_theta - cos_umbra) / (cos_penumbra - cos_umbra)), s_exp);
}

// Calculates the maximum contribution of the given omni light on the given point.
float3 OmniLightMaxContribution(OmniLight light, float3 p) {
	const float r = distance(light.p.xyz, p);
	const float df = DistanceFalloff(r, light.distance_falloff_start, light.distance_falloff_end);
	return df * light.I;
}

// Calculates the maximum contribution of the given spotlight on the given point.
float3 SpotLightMaxContribution(SpotLight light, float3 p, float3 l) {
	const float r = distance(light.p.xyz, p);
	const float cos_theta = dot(light.d, -l);
	const float df = DistanceFalloff(r, light.distance_falloff_start, light.distance_falloff_end);
	const float af = AngularFalloff(cos_theta, light.cos_penumbra, light.cos_umbra, light.exponent_property);
	return df * af * light.I;
}