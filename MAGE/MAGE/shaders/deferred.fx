//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#include "light.fx"
#include "math.fx"

//-----------------------------------------------------------------------------
// Constant Buffers
//-----------------------------------------------------------------------------
cbuffer PerFrame : register(b0) {
	// CAMERA
	// The projection values of the view-to-projection transformation matrix.
	// g_projection_values.x = 1 / view_to_projection00
	// g_projection_values.y = 1 / view_to_projection11
	// g_projection_values.z =  view_to_projection32
	// g_projection_values.w = -view_to_projection22
	float4 g_projection_values             : packoffset(c0);
	
	// LIGHTING
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
	
	// FOGGING
	// The distance at which intensity falloff starts due to fog.
	float g_fog_distance_falloff_start     : packoffset(c3.w);
	// The color of the fog.
	float3 g_fog_color                     : packoffset(c4);
	// The distance inverse range where intensity falloff occurs due to fog.
	float g_fog_distance_falloff_inv_range : packoffset(c4.w);

	// MATERIAL
	// The 1st BRDF dependent material coefficient start.
	// Ns    [(Modified) Phong/(Modified) Blinn-Phong]
	// alpha [Ward(-Duer)]
	// m     [Cook-Torrance]
	float g_mat1_start                       : packoffset(c5.x);
	// The 1st BRDF dependent material coefficient range.
	// Ns    [(Modified) Phong/(Modified) Blinn-Phong]
	// alpha [Ward(-Duer)]
	// m     [Cook-Torrance]
	float g_mat1_range                       : packoffset(c5.y);
	// The 2nd BRDF dependent material coefficient start.
	// R0    [Cook-Torrance]
	float g_mat2_start                       : packoffset(c5.z);
	// The 2nd BRDF dependent material coefficient range.
	// R0    [Cook-Torrance]
	float g_mat2_range                       : packoffset(c5.w);
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
#include "lighting.fx"

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
	const float4 diffuse  = g_diffuse_texture.Load(location);
	const float3 Kd       = diffuse.xyz;
	const float  mat2     = g_mat2_start + diffuse.w * g_mat2_range;

	// Load the specular data from the GBuffer specular texture.
	const float4 specular = g_specular_texture.Load(location);
	const float3 Ks       = specular.xyz;
	const float  mat1     = g_mat1_start + specular.w * g_mat1_range;

	return float4(BRDFShading(p_view, n_view, Kd, Ks, mat1, mat2), 1.0);
}