//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
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
	// The specular exponent of the material.
	float g_Ns                         : packoffset(c13.w);
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
#include "normal_mapping.fx"

//-----------------------------------------------------------------------------
// Vertex Shader
//-----------------------------------------------------------------------------
PSInputPositionNormalTexture VS(VSInputPositionNormalTexture input) {
	PSInputPositionNormalTexture output;
	output.p      = mul(float4(input.p, 1.0f), g_object_to_view);
	output.p_view = output.p.xyz;
	output.p      = mul(output.p, g_view_to_projection);
	output.n_view = normalize(mul(input.n, (float3x3)g_normal_to_view));
	output.tex    = mul(float3(input.tex, 1.0f), (float3x3)g_texture_transform).xy;
	output.tex2   = input.tex;
	return output;
}

//-----------------------------------------------------------------------------
// Pixel Shaders
//-----------------------------------------------------------------------------
PSOutputDeferred Basic_PS(PSInputPositionNormalTexture input) {
	PSOutputDeferred output;
	output.p_view   = input.p_view;
	output.n_view   = normalize(input.n_view);
	output.Kd       = g_Kd * g_diffuse_texture.Sample( g_sampler, input.tex);
	output.KsNs.xyz = g_Ks * g_specular_texture.Sample(g_sampler, input.tex).xyz;
	output.KsNs.w   = g_Ns;
	return output;
}

PSOutputDeferred TangentSpaceNormalMapping_PS(PSInputPositionNormalTexture input) {
	const float3 n0 = normalize(input.n_view);
	
	PSOutputDeferred output;
	output.p_view   = input.p_view;
	output.n_view   = TangentSpaceNormalMapping_PerturbNormal(input.p_view, n0, input.tex2);
	output.Kd       = g_Kd * g_diffuse_texture.Sample( g_sampler, input.tex);
	output.KsNs.xyz = g_Ks * g_specular_texture.Sample(g_sampler, input.tex).xyz;
	output.KsNs.w   = g_Ns;
	return output;
}