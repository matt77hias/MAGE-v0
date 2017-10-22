//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#include "gbuffer_input.hlsli"
#include "transform.hlsli"

//-----------------------------------------------------------------------------
// Pixel Shader
//-----------------------------------------------------------------------------
OMInputDeferred PS(PSInputPositionNormalTexture input) {
	// Obtain the base color of the material.
	const float4 base_color = GetMaterialBaseColor(input.tex);

	clip(base_color.w - TRANSPARENCY_THRESHOLD);

	OMInputDeferred output;
	// Store the base color of the material.
	output.base_color.xyz = base_color.xyz;
	// Store the material parameters [roughness, metalness] of the material.
	output.material.xy    = GetMaterialParameters(input.tex);
	// Pack and store the view-space normal.
	output.normal.xyz     = PackNormal(
								GetNormal(input.p_view, input.n_view, input.tex2));
	return output;
}