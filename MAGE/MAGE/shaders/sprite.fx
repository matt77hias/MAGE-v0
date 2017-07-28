//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#include "structures.fx"

//-----------------------------------------------------------------------------
// Constant buffers
//-----------------------------------------------------------------------------
Texture2D texture_map : register(t0);
sampler texture_sampler : register(s0);

cbuffer cb_transform : register(b0) {
	// The object-to-projection transformation matrix.
	float4x4 transform : packoffset(c0);
}

//-----------------------------------------------------------------------------
// Input structures
//-----------------------------------------------------------------------------

struct PS_INPUT {
	float4 p     : SV_POSITION;
	float4 color : COLOR0;
	float2 tex   : TEXCOORD0;
};

//-----------------------------------------------------------------------------
// Vertex Shader
//-----------------------------------------------------------------------------
PS_INPUT VS(VSInputPositionColorTexture input) {
	PS_INPUT output = (PS_INPUT)0;
	output.p        = mul(input.p, transform);
	output.color    = input.color;
	output.tex      = input.tex;
	return output;
}

//-----------------------------------------------------------------------------
// Pixel Shader
//-----------------------------------------------------------------------------
float4 PS(PS_INPUT input) : SV_Target {
	return texture_map.Sample(texture_sampler, input.tex) * input.color;
}