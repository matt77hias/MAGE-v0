//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#include "global.hlsli"
#include "normal_mapping.hlsli"

//-----------------------------------------------------------------------------
// Textures
//-----------------------------------------------------------------------------
Texture2D g_normal_texture : register(REG_T(SLOT_SRV_NORMAL));

//-----------------------------------------------------------------------------
// Pixel Shader
//-----------------------------------------------------------------------------
float4 PS(PSInputPositionNormalTexture input) : SV_Target {
	// Obtain the tangent-space normal coefficients in the [-1,1] range.
	const float3 c      = UNORMtoSNORM(g_normal_texture.Sample(g_variable_sampler0, input.tex2).xyz);
	// Normalize the view-space normal.
	const float3 n0     = normalize(input.n_view);
	// Perturb the view-space normal.
	const float3 n_view = PerturbNormal(input.p_view, n0, input.tex2, c);
	
	// Converts the [-1,1] range to the [0,1] range.
	return float4(SNORMtoUNORM(n_view), 1.0f);
}