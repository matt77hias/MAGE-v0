//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#include "global.hlsli"

//-----------------------------------------------------------------------------
// Vertex Shader
//-----------------------------------------------------------------------------
PSInputColorTexture VS(VSInputPositionColorTexture input) {
	PSInputColorTexture output;
	
	// .x: [0, g_display_resolution.x] -> [-1,1]
	// .y: [0, g_display_resolution.y] -> [1,-1]
	output.p.xy  = float2(2.0f, -2.0f) * input.p.xy / g_display_resolution 
		         + float2(-1.0f, 1.0f);
	output.p.zw  = float2(input.p.z, 1.0f);
	output.color = input.color;
	output.tex   = input.tex;
	return output;
}