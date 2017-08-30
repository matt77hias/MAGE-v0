//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#include "math.fx"
#include "structures.fx"

//-----------------------------------------------------------------------------
// Constant Buffers
//-----------------------------------------------------------------------------
cbuffer PerFrame : register(b0) {
	// The view-to-projection transformation matrix.
	float4x4 g_view_to_projection      : packoffset(c0);
};

cbuffer PerDraw : register(b1) {
	// The object-to-view transformation matrix.
	float4x4 g_object_to_view          : packoffset(c0);
	// The object-to-view inverse transpose transformation matrix
	// = The normal-to-view transformation matrix.
	float4x4 g_normal_to_view          : packoffset(c4);
	// The texture transformation matrix.
	float4x4 g_texture_transform       : packoffset(c8);
	// The diffuse reflectivity + dissolve of the material
	float4 g_Kd                        : packoffset(c12);
	// The specular reflectivity of the material.
	float3 g_Ks                        : packoffset(c13);
	// The normalized specular exponent of the material.
	float g_Ns_norm                    : packoffset(c13.w);
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
PSOutputDeferred Basic_PS(PSInputPositionNormalTexture input) {
	const float3 n_view = normalize(input.n_view);
	
	PSOutputDeferred output;
	output.n_view   = BiasX2(n_view);
	output.Kd       = g_Kd * g_diffuse_texture.Sample( g_sampler, input.tex);
	output.KsNs.xyz = g_Ks * g_specular_texture.Sample(g_sampler, input.tex).xyz;
	output.KsNs.w   = g_Ns_norm;
	return output;
}

PSOutputDeferred TangentSpaceNormalMapping_PS(PSInputPositionNormalTexture input) {
	const float3 n0     = normalize(input.n_view);
	const float3 n_view = TangentSpaceNormalMapping_PerturbNormal(input.p_view, n0, input.tex2);
	
	PSOutputDeferred output;
	output.n_view   = BiasX2(n_view);
	output.Kd       = g_Kd * g_diffuse_texture.Sample( g_sampler, input.tex);
	output.KsNs.xyz = g_Ks * g_specular_texture.Sample(g_sampler, input.tex).xyz;
	output.KsNs.w   = g_Ns_norm;
	return output;
}