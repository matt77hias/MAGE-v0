//--------------------------------------------------------------------------------------
// Constant buffers
//--------------------------------------------------------------------------------------
//Texture2D diffuse_texture : register(t0);
//SamplerState linear_sample : register(s0);

cbuffer cb_camera : register(b0) {
	matrix world_to_view;
	matrix view_to_projection;
};

cbuffer cb_model : register(b1) {
	matrix model_to_world;
}

//-----------------------------------------------------------------------------
// Input structures
//-----------------------------------------------------------------------------
struct VS_INPUT {
	float4 p : POSITION;
	float3 n : NORMAL;
	float2 tex : TEXCOORD0;
};

struct PS_INPUT {
	float4 p : SV_POSITION;
	float2 tex : TEXCOORD0;
};

//-----------------------------------------------------------------------------
// Vertex Shader
//-----------------------------------------------------------------------------
PS_INPUT VS(VS_INPUT input) {
	PS_INPUT output = (PS_INPUT)0;
	output.p = mul(input.p, model_to_world);
	output.p = mul(output.p, world_to_view);
	output.p = mul(output.p, view_to_projection);
	output.tex = input.tex;
	return output;
}

//-----------------------------------------------------------------------------
// Pixel Shader
//-----------------------------------------------------------------------------
float4 PS(PS_INPUT input) : SV_Target{
	//return diffuse_texture.Sample(linear_sample, input.tex);
	return float4(1.0f, 1.0f, 0.0f, 1.0f);
}