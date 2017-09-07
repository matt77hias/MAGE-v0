//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#include "hlsl.hpp"
#include "normal_mapping.hlsli"

//-----------------------------------------------------------------------------
// Constant Buffers
//-----------------------------------------------------------------------------
cbuffer PerFrame : register(REG_B(SLOT_CBUFFER_PER_FRAME)) {
	// CAMERA
	// The view-to-projection transformation matrix.
	float4x4 g_view_to_projection      : packoffset(c0);
};

cbuffer PerDraw  : register(REG_B(SLOT_CBUFFER_PER_DRAW)) {
	// TRANSFORM
	// The object-to-view transformation matrix.
	float4x4 g_object_to_view          : packoffset(c0);
	// The object-to-view inverse transpose transformation matrix
	// = The normal-to-view transformation matrix.
	float4x4 g_normal_to_view          : packoffset(c4);
	// The texture transformation matrix.
	float4x4 g_texture_transform       : packoffset(c8);
	
	// MATERIAL
	// The diffuse reflectivity of the material
	float3 g_Kd                        : packoffset(c12);
	// The 2nd BRDF dependent normalized material coefficient.
	// R0    [Cook-Torrance]
	float g_mat2_norm                  : packoffset(c12.w);
	// The specular reflectivity of the material.
	float3 g_Ks                        : packoffset(c13);
	// The 1st BRDF dependent normalized material coefficient.
	// Ns    [(Modified) Phong/(Modified) Blinn-Phong]
	// alpha [Ward(-Duer)]
	// m     [Cook-Torrance]
	float g_mat1_norm                  : packoffset(c13.w);
}

//-----------------------------------------------------------------------------
// Samplers and Textures
//-----------------------------------------------------------------------------
sampler   g_sampler          : register(REG_S(SLOT_SAMPLER_DEFAULT));
Texture2D g_diffuse_texture  : register(REG_T(SLOT_SRV_DIFFUSE));
Texture2D g_specular_texture : register(REG_T(SLOT_SRV_SPECULAR));
Texture2D g_normal_texture   : register(REG_T(SLOT_SRV_NORMAL));

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#include "transform.hlsli"

//-----------------------------------------------------------------------------
// Pixel Shader
//-----------------------------------------------------------------------------
OMInputDeferred PS(PSInputPositionNormalTexture input) {

#ifdef TSNM
	// Obtain the tangent-space normal coefficients in the [-1,1] range. 
	const float3 c      = UNORMtoSNORM(g_normal_texture.Sample(g_sampler, input.tex2).xyz);
	// Normalize the view-space normal.
	const float3 n0     = normalize(input.n_view);
	// Perturb the view-space normal.
	const float3 n_view = PerturbNormal(input.p_view, n0, input.tex2, c);
#else  // TSNM
	// Normalize the view-space normal.
	const float3 n_view = normalize(input.n_view);
#endif // TSNM
	
	OMInputDeferred output;
	
	// Pack the view-space normal: [-1,1] -> [0,1]
	output.normal.xyz   = PackNormal(n_view);
	
	// Pack the diffuse reflectivity of the material.
#ifdef DISSABLE_DIFFUSE_REFLECTIVITY_TEXTURE
	output.diffuse.xyz  = g_Kd;
#else  // DISSABLE_DIFFUSE_REFLECTIVITY_TEXTURE
	output.diffuse.xyz  = g_Kd * g_diffuse_texture.Sample(g_sampler, input.tex).xyz;
#endif // DISSABLE_DIFFUSE_REFLECTIVITY_TEXTURE

	// Pack the 2nd BRDF dependent normalized material coefficient.
	output.diffuse.w    = g_mat2_norm;
	
	// Pack the specular reflectivity of the material.
#ifdef DISSABLE_SPECULAR_REFLECTIVITY_TEXTURE
	output.specular.xyz = g_Ks;
#else  // DISSABLE_SPECULAR_REFLECTIVITY_TEXTURE
	output.specular.xyz = g_Ks * g_specular_texture.Sample(g_sampler, input.tex).xyz;
#endif // DISSABLE_SPECULAR_REFLECTIVITY_TEXTURE
	
	// Pack the 1st BRDF dependent normalized material coefficient.
	output.specular.w   = g_mat1_norm;

	return output;
}