//-----------------------------------------------------------------------------
// Engine Configuration
//-----------------------------------------------------------------------------
// Defines			                      | Default
//-----------------------------------------------------------------------------
// DISSABLE_BASE_COLOR_TEXTURE            | not defined
// DISSABLE_MATERIAL_TEXTURE              | not defined
// TSNM                                   | not defined

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#include "forward\forward_input.hlsli"

//-----------------------------------------------------------------------------
// Pixel Shader
//-----------------------------------------------------------------------------
OMInputDeferred PS(PSInputPositionNormalTexture input) {
	// Obtain the base color of the material.
	const float4 base_color = GetMaterialBaseColor(input.tex);

	clip(base_color.w - TRANSPARENCY_THRESHOLD);

	OMInputDeferred output;
#pragma warning(push)
#pragma warning(disable : 3578)
	// Store the base color of the material.
	output.base_color.xyz = base_color.xyz;
	// Store the material parameters [roughness, metalness] of the material.
	output.material.xy    = GetMaterialParameters(input.tex);
	// Pack and store the view-space normal.
	output.normal.xyz     = PackNormal(
								GetNormal(input.p_view, input.n_view, input.tex2));
#pragma warning(pop)
	return output;
}