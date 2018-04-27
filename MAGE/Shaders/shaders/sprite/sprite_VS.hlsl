//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#include "global.hlsli"

//-----------------------------------------------------------------------------
// Vertex Shader
//-----------------------------------------------------------------------------
PSInputColorTexture VS(VSInputPositionColorTexture input) {
	PSInputColorTexture output;
	output.p.xy  = UVtoNDC(DisplayToUV(input.p.xy));
	output.p.zw  = { input.p.z, 1.0f };
	output.color = input.color;
	output.tex   = input.tex;
	return output;
}