//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#include "structures.hlsli"
#include "normal_mapping.hlsli"

//-----------------------------------------------------------------------------
// Samplers and Textures
//-----------------------------------------------------------------------------
sampler g_sampler          : register(s0);
Texture2D g_normal_texture : register(t0);

//-----------------------------------------------------------------------------
// Pixel Shader
//-----------------------------------------------------------------------------
float4 PS(PSInputPositionNormalTexture input) : SV_Target {
	const float3 c      = BiasX2(g_normal_texture.Sample(g_sampler, input.tex2).xyz);
	const float3 n0     = normalize(input.n_view);
	const float3 n_view = TangentSpaceNormalMapping_PerturbNormal(input.p_view, n0, input.tex2, c);
	
	return float4(InverseBiasX2(n_view), 1.0f);
}