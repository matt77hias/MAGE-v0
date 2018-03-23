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
	const float alpha = g_base_color.a 
		* g_base_color_texture.Sample(g_linear_wrap_sampler, input.tex).a;
	clip(alpha - TRANSPARENCY_SHADOW_THRESHOLD);
}