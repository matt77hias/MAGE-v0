//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#include "gbuffer_input.hlsli"
#include "transform.hlsli"
#include "lighting.hlsli"

//-----------------------------------------------------------------------------
// Pixel Shader
//-----------------------------------------------------------------------------
float4 PS(PSInputPositionNormalTexture input) : SV_Target {
	// Obtain the base color of the material.
	const float4 base_color = GetMaterialBaseColor(input.tex);

	clip(base_color.w - TRANSPARENCY_SKIP_THRESHOLD);

	// Obtain the material parameters [roughness, metalness] of the material.
	const float2 material   = GetMaterialParameters(input.tex);
	// Obtain the view-space normal.
	const float3 n_view     = GetNormal(input.p_view, input.n_view, input.tex2);

	// Calculate the pixel radiance.
	const float3 L = BRDFShading(input.p_view, n_view, 
		                         base_color.xyz, material.x, material.y);

	return float4(L, base_color.w);
}