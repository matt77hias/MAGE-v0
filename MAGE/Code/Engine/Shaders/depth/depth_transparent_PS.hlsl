//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#define DISABLE_TEXTURE_MATERIAL
#define DISABLE_TSNM
#include "forward\forward_input.hlsli"

//-----------------------------------------------------------------------------
// Pixel Shader
//-----------------------------------------------------------------------------
void PS(PSInputTexture input) {
	// Obtain the base color of the material.
	const float alpha = GetMaterialBaseColor(input.tex).a;

	clip(alpha - TRANSPARENCY_SHADOW_THRESHOLD);
}