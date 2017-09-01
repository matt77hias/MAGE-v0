//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#include "light.fx"

//-----------------------------------------------------------------------------
// Constant Buffers
//-----------------------------------------------------------------------------
cbuffer PerFrame : register(b0) {
	// CAMERA
	// The view-to-projection transformation matrix.
	float4x4 g_view_to_projection          : packoffset(c0);
	
	// LIGHTING
	// The intensity of the ambient light in the scene. 
	float3 g_Ia                            : packoffset(c4);
	// The global flags.
	uint g_flags                           : packoffset(c4.w);
	// The number of directional lights in the scene.
	uint g_nb_directional_lights           : packoffset(c5.x);
	// The number of omni lights in the scene.
	uint g_nb_omni_lights                  : packoffset(c5.y);
	// The number of spotlights in the scene.
	uint g_nb_spot_lights                  : packoffset(c5.z);
	
	// FOGGING
	// The distance at which intensity falloff starts due to fog.
	float g_fog_distance_falloff_start     : packoffset(c5.w);
	// The color of the fog.
	float3 g_fog_color                     : packoffset(c6);
	// The distance inverse range where intensity falloff occurs due to fog.
	float g_fog_distance_falloff_inv_range : packoffset(c6.w);
};

cbuffer PerDraw : register(b1) {
	// TRANSFORM
	// The object-to-view transformation matrix.
	float4x4 g_object_to_view              : packoffset(c0);
	// The object-to-view inverse transpose transformation matrix
	// = The normal-to-view transformation matrix.
	float4x4 g_normal_to_view              : packoffset(c4);
	// The texture transformation matrix.
	float4x4 g_texture_transform           : packoffset(c8);
	
	// MATERIAL
	// The diffuse reflectivity + dissolve of the material
	float4 g_Kd                            : packoffset(c12);
	// The specular reflectivity of the material.
	float3 g_Ks                            : packoffset(c13);
	// The 1st BRDF dependent material coefficient.
	// Ns    [(Modified) Phong/(Modified) Blinn-Phong]
	// alpha [Ward(-Duer)]
	// m     [Cook-Torrance]
	float g_mat1                           : packoffset(c13.w);
	// The 2nd BRDF dependent material coefficient.
	// R0    [Cook-Torrance]
	float g_mat2                           : packoffset(c14.x);
	uint3 g_padding                        : packoffset(c14.y);
}

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
Texture2D g_diffuse_texture  : register(t3);
Texture2D g_specular_texture : register(t4);
Texture2D g_normal_texture   : register(t5);

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#include "transform.fx"
#include "normal_mapping.fx"
#include "lighting.fx"

//-----------------------------------------------------------------------------
// Pixel Shaders
//-----------------------------------------------------------------------------
float4 PS(PSInputPositionNormalTexture input) : SV_Target {

#ifdef TSNM
	const float3 n0     = normalize(input.n_view);
	const float3 n_view = TangentSpaceNormalMapping_PerturbNormal(input.p_view, n0, input.tex2);
#else
	const float3 n_view = normalize(input.n_view);
#endif // TSNM

	const float4 Kd = g_Kd * g_diffuse_texture.Sample( g_sampler, input.tex);
#ifdef SPECULAR_BRDFxCOS
	const float3 Ks = g_Ks * g_specular_texture.Sample(g_sampler, input.tex).xyz;
#else
	const float3 Ks = float3(0.0f, 0.0f, 0.0f);
#endif // SPECULAR_BRDFxCOS

	return float4(BRDFShading(input.p_view, n_view, Kd.xyz, Ks, g_mat1, g_mat2), Kd.w);
}