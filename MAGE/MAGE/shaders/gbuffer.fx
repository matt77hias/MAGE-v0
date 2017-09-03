//-----------------------------------------------------------------------------
// Constant Buffers
//-----------------------------------------------------------------------------
cbuffer PerFrame : register(b1) {
	// CAMERA
	// The view-to-projection transformation matrix.
	float4x4 g_view_to_projection      : packoffset(c0);
};

cbuffer PerDraw : register(b2) {
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
// Samplers
//-----------------------------------------------------------------------------
sampler g_sampler : register(s0);

//-----------------------------------------------------------------------------
// Textures
//-----------------------------------------------------------------------------
Texture2D g_diffuse_texture  : register(t0);
Texture2D g_specular_texture : register(t1);
Texture2D g_normal_texture   : register(t2);

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#include "transform.fx"
#include "normal_mapping.fx"

//-----------------------------------------------------------------------------
// Pixel Shaders
//-----------------------------------------------------------------------------
OMInputDeferred PS(PSInputPositionNormalTexture input) {

#ifdef TSNM
	const float3 n0     = normalize(input.n_view);
	const float3 n_view = TangentSpaceNormalMapping_PerturbNormal(input.p_view, n0, input.tex2);
#else  // TSNM
	const float3 n_view = normalize(input.n_view);
#endif // TSNM
	
	OMInputDeferred output;
	// [-1,1] -> [0,1]
	output.normal.xyz   = InverseBiasX2(n_view);
	
#ifdef DISSABLE_DIFFUSE_REFLECTIVITY_TEXTURE
	output.diffuse.xyz = g_Kd;
#else  // DISSABLE_DIFFUSE_REFLECTIVITY_TEXTURE
	output.diffuse.xyz  = g_Kd * g_diffuse_texture.Sample(g_sampler, input.tex).xyz;
#endif // DISSABLE_DIFFUSE_REFLECTIVITY_TEXTURE

	output.diffuse.w    = g_mat2_norm;
	
#ifdef DISSABLE_SPECULAR_REFLECTIVITY_TEXTURE
	output.specular.xyz = g_Ks;
#else  // DISSABLE_SPECULAR_REFLECTIVITY_TEXTURE
	output.specular.xyz = g_Ks * g_specular_texture.Sample(g_sampler, input.tex).xyz;
#endif // DISSABLE_SPECULAR_REFLECTIVITY_TEXTURE
	
	output.specular.w   = g_mat1_norm;

	return output;
}