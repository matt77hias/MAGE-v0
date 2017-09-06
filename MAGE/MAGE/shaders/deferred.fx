//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#include "structures.hlsli"
#include "lighting.hlsli"
#include "math.hlsli"

//-----------------------------------------------------------------------------
// Constant Buffers
//-----------------------------------------------------------------------------
cbuffer PerFrame : register(b1) {
	// CAMERA
	// The projection values of the view-to-projection transformation matrix.
	// g_projection_values.x = 1 / view_to_projection00
	// g_projection_values.y = 1 / view_to_projection11
	// g_projection_values.z =  view_to_projection32
	// g_projection_values.w = -view_to_projection22
	float4 g_projection_values : packoffset(c0);
	
	// MATERIAL
	// The 1st BRDF dependent material coefficient start.
	// Ns    [(Modified) Phong/(Modified) Blinn-Phong]
	// alpha [Ward(-Duer)]
	// m     [Cook-Torrance]
	float g_mat1_start         : packoffset(c1.x);
	// The 1st BRDF dependent material coefficient range.
	// Ns    [(Modified) Phong/(Modified) Blinn-Phong]
	// alpha [Ward(-Duer)]
	// m     [Cook-Torrance]
	float g_mat1_range         : packoffset(c1.y);
	// The 2nd BRDF dependent material coefficient start.
	// R0    [Cook-Torrance]
	float g_mat2_start         : packoffset(c1.z);
	// The 2nd BRDF dependent material coefficient range.
	// R0    [Cook-Torrance]
	float g_mat2_range         : packoffset(c1.w);
};

//-----------------------------------------------------------------------------
// Textures
//-----------------------------------------------------------------------------
Texture2D g_normal_texture   : register(t3);
Texture2D g_diffuse_texture  : register(t4);
Texture2D g_specular_texture : register(t5);
Texture2D g_depth_texture    : register(t6);

//-----------------------------------------------------------------------------
// Pixel Shader
//-----------------------------------------------------------------------------
float4 PS(PSInputNDCPosition input) : SV_Target {

	// Load the depth from the GBuffer depth texture.
	const float  depth    = g_depth_texture[input.p.xy].x;
	// Obtain the NDC space coodinates.
	const float3 p_ndc    = float3(input.p_ndc, depth);
	// Obtain the view space coodinates.
	const float3 p_view   = NDCtoView(p_ndc, g_projection_values);

	// Load the normal from the GBuffer normal texture.
	const float3 normal   = g_normal_texture[input.p.xy].xyz;
	// Unpack the view-space normal: [0,1] -> [-1,1]
	const float3 n_view   = UnpackNormal(normal);

	// Load the diffuse data from the GBuffer diffuse texture.
	const float4 diffuse  = g_diffuse_texture[input.p.xy];
	// Unpack the diffuse reflectivity of the material.
	const float3 Kd       = diffuse.xyz;
	// Unpack the 2nd BRDF dependent normalized material coefficient.
	const float  mat2     = g_mat2_start + diffuse.w * g_mat2_range;

	// Load the specular data from the GBuffer specular texture.
	const float4 specular = g_specular_texture[input.p.xy];
	// Unpack the specular reflectivity of the material.
	const float3 Ks       = specular.xyz;
	// Unpack the 1st BRDF dependent normalized material coefficient.
	const float  mat1     = g_mat1_start + specular.w * g_mat1_range;

	return float4(BRDFShading(p_view, n_view, Kd, Ks, mat1, mat2), 1.0f);
}