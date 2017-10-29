//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#include "forward\forward_input.hlsli"
#include "transform\transform.hlsli"
#include "lighting.hlsli"

//-----------------------------------------------------------------------------
// Pixel Shader
//-----------------------------------------------------------------------------
OMInputForward PS(PSInputPositionNormalTexture input) {
	// Obtain the base color of the material.
	const float4 base_color = GetMaterialBaseColor(input.tex);

#ifdef ENABLE_TRANSPARENCY
	clip(base_color.w - TRANSPARENCY_SKIP_THRESHOLD);
#else
	clip(base_color.w - TRANSPARENCY_THRESHOLD);
#endif

	// Obtain the material parameters [roughness, metalness] of the material.
	const float2 material   = GetMaterialParameters(input.tex);
	// Obtain the view-space normal.
	const float3 n_view     = GetNormal(input.p_view, input.n_view, input.tex2);

	// Calculate the pixel radiance.
	const float3 L = BRDFShading(input.p_view, n_view, 
		                         base_color.xyz, material.x, material.y);

	OMInputForward output;
	// Store the color.
	output.color      = float4(L, base_color.w);
	// Pack and store the view-space normal.
#pragma warning(push)
#pragma warning(disable : 3578)
	output.normal.xyz = PackNormal(n_view);
#pragma warning(pop)
								
	return output;
}