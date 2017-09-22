//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#include "global.hlsli"
#include "normal_mapping.hlsli"

//-----------------------------------------------------------------------------
// Constant Buffers
//-----------------------------------------------------------------------------
CBUFFER(PerFrame, SLOT_CBUFFER_PER_FRAME) {
	// CAMERA
	// The view-to-projection transformation matrix.
	float4x4 g_view_to_projection      : packoffset(c0);
};

CBUFFER(PerDraw, SLOT_CBUFFER_PER_DRAW) {
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
// SRVs
//-----------------------------------------------------------------------------
TEXTURE_2D(g_diffuse_texture,  float4, SLOT_SRV_DIFFUSE);
TEXTURE_2D(g_specular_texture, float4, SLOT_SRV_SPECULAR);
TEXTURE_2D(g_normal_texture,   float3, SLOT_SRV_NORMAL);

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
	const float3 c      = UNORMtoSNORM(g_normal_texture.Sample(g_linear_wrap_sampler, input.tex2));
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
	output.diffuse.xyz  = g_Kd * g_diffuse_texture.Sample(g_linear_wrap_sampler, input.tex).xyz;
#endif // DISSABLE_DIFFUSE_REFLECTIVITY_TEXTURE

	// Pack the 2nd BRDF dependent normalized material coefficient.
	output.diffuse.w    = g_mat2_norm;
	
	// Pack the specular reflectivity of the material.
#ifdef DISSABLE_SPECULAR_REFLECTIVITY_TEXTURE
	output.specular.xyz = g_Ks;
#else  // DISSABLE_SPECULAR_REFLECTIVITY_TEXTURE
	output.specular.xyz = g_Ks * g_specular_texture.Sample(g_linear_wrap_sampler, input.tex).xyz;
#endif // DISSABLE_SPECULAR_REFLECTIVITY_TEXTURE
	
	// Pack the 1st BRDF dependent normalized material coefficient.
	output.specular.w   = g_mat1_norm;

	return output;
}