#ifndef MAGE_HEADER_LIGHTING
#define MAGE_HEADER_LIGHTING

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#include "brdf.hlsli"
#include "light.hlsli"

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

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------

#ifdef TWO_BRDF_COEFFICIENTS
#define BRDF_COEFFICIENTS mat1, mat2
#else  // TWO_BRDF_COEFFICIENTS
#define BRDF_COEFFICIENTS mat1
#endif // TWO_BRDF_COEFFICIENTS

// Calculates the BRDF shading.
float3 BRDFShading(float3 p, float3 n, float3 Kd, float3 Ks, float mat1, float mat2) {
	float3 I = Kd;
	const float r_eye = length(p);

#ifndef DISSABLE_BRDFxCOS

#ifdef DISSABLE_AMBIENT_LIGHT
	float3 Id = float3(0.0f, 0.0f, 0.0f);
#else  // DISSABLE_AMBIENT_LIGHT
	// Ambient light contribution
	float3 Id = g_Ia;
#endif // DISSABLE_AMBIENT_LIGHT

#ifdef SPECULAR_BRDFxCOS
	float3 Is = float3(0.0f, 0.0f, 0.0f);
#endif // SPECULAR_BRDFxCOS

	const float3 v = -p / r_eye;

#ifndef DISSABLE_DIRECTIONAL_LIGHTS
	// Directional lights contribution
	for (uint i = 0; i < g_nb_directional_lights; ++i) {
		const DirectionalLight light = g_directional_lights[i];
		const float3 l        = light.neg_d;
		const float3 I_light  = light.I;

		const float fd = LambertianBRDFxCos(n, l);
		Id += fd * I_light;

#ifdef SPECULAR_BRDFxCOS
		const float fs = SPECULAR_BRDFxCOS(n, l, v, BRDF_COEFFICIENTS);
		Is += fs * I_light;
#endif // SPECULAR_BRDFxCOS
	}
#endif // DISSABLE_DIRECTIONAL_LIGHTS

#ifndef DISSABLE_OMNI_LIGHTS
	// Omni lights contribution
	for (uint j = 0; j < g_nb_omni_lights; ++j) {
		const OmniLight light = g_omni_lights[j];
		const float3 d_light  = light.p - p;
		const float r_light   = length(d_light);
		const float3 l        = d_light / r_light;
		const float3 I_light  = OmniLightMaxContribution(light, r_light);

		const float fd = LambertianBRDFxCos(n, l);
		Id += fd * I_light;

#ifdef SPECULAR_BRDFxCOS
		const float fs = SPECULAR_BRDFxCOS(n, l, v, BRDF_COEFFICIENTS);
		Is += fs * I_light;
#endif // SPECULAR_BRDFxCOS
	}
#endif // DISSABLE_OMNI_LIGHTS

#ifndef DISSABLE_SPOT_LIGHTS
	// Spotlights contribution
	for (uint k = 0; k < g_nb_spot_lights; ++k) {
		const SpotLight light = g_spot_lights[k];
		const float3 d_light  = light.p - p;
		const float r_light   = length(d_light);
		const float3 l        = d_light / r_light;
		const float3 I_light  = SpotLightMaxContribution(light, r_light, l);

		const float fd = LambertianBRDFxCos(n, l);
		Id += fd * I_light;

#ifdef SPECULAR_BRDFxCOS
		const float fs = SPECULAR_BRDFxCOS(n, l, v, BRDF_COEFFICIENTS);
		Is += fs * I_light; // SPECULAR_BRDFxCOS
#endif
	}
#endif // DISSABLE_SPOT_LIGHTS

	I *= Id;
#ifdef SPECULAR_BRDFxCOS
	I += Ks * Is;
#endif // SPECULAR_BRDFxCOS

#endif // DISSABLE_BRDFxCOS

#ifndef DISSABLE_FOG
	const float fog_factor = saturate((r_eye - g_fog_distance_falloff_start) * g_fog_distance_falloff_inv_range);
	I = lerp(I, g_fog_color, fog_factor);
#endif // DISSABLE_FOG
	
	return I;
}

#endif //MAGE_HEADER_LIGHTING