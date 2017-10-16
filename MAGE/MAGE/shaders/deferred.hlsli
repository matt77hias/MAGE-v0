//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#include "deferred_input.hlsli"
#include "lighting.hlsli"

//-----------------------------------------------------------------------------
// Pixel Shader
//-----------------------------------------------------------------------------
float4 PS(PSInputNDCPosition input) : SV_Target {

	const float2 location = input.p.xy;

	// Obtain the base color of the material.
	const float3 base_color = GammaToLinear(GetGBufferMaterialBaseColor(location));
	// Obtain the parameters of the material.
	const float2 material   = GetGBufferMaterialParameters(location);
	// Obtain the view-space normal.
	const float3 n_view     = GetGBufferNormal(location);
	// Obtain the view-space hit position.
	const float3 p_view     = GetGBufferPosition(location, input.p_ndc);

	// Calculate the pixel radiance.
	const float3 L = BRDFShading(p_view, n_view, 
		                         base_color, material.x, material.y);

	return (material.x) ? float4(L, 1.0f) : float4(0.0f, 0.0f, 0.0f, 1.0f);
}