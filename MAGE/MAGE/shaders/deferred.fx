//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#include "light.fx"

//-----------------------------------------------------------------------------
// Constant Buffers
//-----------------------------------------------------------------------------
cbuffer PerFrame : register(b0) {
	// The projection values of the view-to-projection transformation matrix.
	// g_projection_values.x = 1 / view_to_projection00
	// g_projection_values.y = 1 / view_to_projection11
	// g_projection_values.z =  view_to_projection32
	// g_projection_values.w = -view_to_projection22
	float4 g_projection_values             : packoffset(c0);
	
	// The intensity of the ambient light in the scene. 
	float3 g_Ia                            : packoffset(c1);
	// The global flags.
	uint g_flags                           : packoffset(c1.w);
	// The number of directional lights in the scene.
	uint g_nb_directional_lights           : packoffset(c2.x);
	// The number of omni lights in the scene.
	uint g_nb_omni_lights                  : packoffset(c2.y);
	// The number of spotlights in the scene.
	uint g_nb_spot_lights                  : packoffset(c3.z);
	
	// The distance at which intensity falloff starts due to fog.
	float g_fog_distance_falloff_start     : packoffset(c3.w);
	// The color of the fog.
	float3 g_fog_color                     : packoffset(c4);
	// The distance inverse range where intensity falloff occurs due to fog.
	float g_fog_distance_falloff_inv_range : packoffset(c4.w);

	// The specular exponent start of the materials.
	float g_Ns_start                       : packoffset(c5.x);
	// The specular exponent range of the materials.
	float g_Ns_range                       : packoffset(c5.y);
};

//-----------------------------------------------------------------------------
// Samplers
//-----------------------------------------------------------------------------
sampler g_sampler : register(s0);

//-----------------------------------------------------------------------------
// Structured Buffers
//-----------------------------------------------------------------------------
StructuredBuffer< DirectionalLight > g_directional_lights : register(t0);
StructuredBuffer< OmniLight > g_omni_lights               : register(t1);
StructuredBuffer< SpotLight > g_spot_lights               : register(t2);

//-----------------------------------------------------------------------------
// Textures
//-----------------------------------------------------------------------------
Texture2D g_normal_texture   : register(t4);
Texture2D g_diffuse_texture  : register(t5);
Texture2D g_specular_texture : register(t6);
Texture2D g_depth_texture    : register(t7);

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#include "math.fx"
#include "brdf.fx"

//-----------------------------------------------------------------------------
// Shading
//-----------------------------------------------------------------------------

// Calculates the BRDF shading.
float4 BRDFShading(float3 p, float3 n, float4 Kd, float3 Ks, float Ns) {
	float4 I = Kd;
	//clip(I.a - 0.1f);
	
	const float r_eye = length(p);

#ifndef DISSABLE_BRDFxCOS

	// Ambient light contribution
	float3 Id = g_Ia;
#ifdef SPECULAR_BRDFxCOS
	float3 Is = float3(0.0f, 0.0f, 0.0f);
#endif

	const float3 v = -p / r_eye;

	// Directional lights contribution
	for (uint i = 0; i < g_nb_directional_lights; ++i) {
		const DirectionalLight light = g_directional_lights[i];
		const float3 l        = light.neg_d;
		const float3 I_light  = light.I;

		const float fd = LambertianBRDFxCos(n, l);
		Id += fd * I_light;

#ifdef SPECULAR_BRDFxCOS
		const float fs = SPECULAR_BRDFxCOS(n, l, v, Ns);
		Is += fs * I_light;
#endif
	}

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
		const float fs = SPECULAR_BRDFxCOS(n, l, v, Ns);
		Is += fs * I_light;
#endif
	}

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
		const float fs = SPECULAR_BRDFxCOS(n, l, v, Ns);
		Is += fs * I_light;
#endif
	}

	I.xyz *= Id;
#ifdef SPECULAR_BRDFxCOS
	I.xyz += Ks * Is;
#endif
#endif

#ifndef DISSABLE_FOG
	const float fog_factor = saturate((r_eye - g_fog_distance_falloff_start) * g_fog_distance_falloff_inv_range);
	I.xyz = lerp(I.xyz, g_fog_color, fog_factor);
#endif
	
	return I;
}

//-----------------------------------------------------------------------------
// Vertex Shader
//-----------------------------------------------------------------------------
PSInputPositionTexture VS(VSInputPositionTexture input) {
	PSInputPosition output;
	output.p   = float4(input.p, 1.0f);
	output.tex = input.tex;
	return output;
}

//-----------------------------------------------------------------------------
// Pixel Shaders
//-----------------------------------------------------------------------------
float4 PS(PSInputPositionTexture input) : SV_Target {
	// location := (u, v, mipmap level)
	const float3 location = float3(input.tex, 0.0f);
	
	// Load the depth from the GBuffer depth texture.
	const float  depth    = g_depth_texture.Load(location).x;
	const float3 p_ndc    = float3(input.p.xy, depth);
	const float3 p_view   = NDCToView(input.p.xyz, g_projection_values);

	// Load the normal from the GBuffer normal texture.
	const float3 normal   = g_normal_texture.Load(location).xyz;
	// [0,1] -> [-1,1]
	const float3 n_view   = BiasX2(normal);

	// Load the diffuse data from the GBuffer diffuse texture.
	const float4 Kd       = g_diffuse_texture.Load(location);

	// Load the specular data from the GBuffer specular texture.
	const float4 specular = g_specular_texture.Load(location);
	const float3 Ks       = specular.xyz;
	// Denormalize the specular exponent.
	const float Ns        = g_Ns_start + specular.w * g_Ns_range;

	return BRDFShading(p_view, n_view, Kd, Ks, Ns);
}