//-----------------------------------------------------------------------------
// Requires global variable: g_object_to_view
// Requires global variable: g_view_to_projection
// Requires global variable: g_normal_to_view
// Requires global variable: g_texture_transform
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#include "structures.hlsli"

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