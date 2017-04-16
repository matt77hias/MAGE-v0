//--------------------------------------------------------------------------------------
// Constant buffers
//--------------------------------------------------------------------------------------
Texture2D diffuse_texture_map : register(t0);
sampler texture_sampler : register(s0);

cbuffer cb_transform : register(b0) {
	matrix model_to_world;
	matrix world_to_view;
	matrix world_to_view_inverse_transpose;
	matrix view_to_projection;
}

cbuffer cb_material :  register(b1) {
	// Ambient reflectivity.
	//float4 ca;
	// Diffuse reflectivity.
	float4 cd;
}

cbuffer cb_light : register(b2) {
	// Light position (in view space coordinates).
	float4 light_p_view;
	float4 light_I;
}

//-----------------------------------------------------------------------------
// Input structures
//-----------------------------------------------------------------------------
struct VS_INPUT {
	float4 p   : POSITION;
	float3 n   : NORMAL;
	float2 tex : TEXCOORD0;
};

struct PS_INPUT {
	float4 p      : SV_POSITION;
	float4 p_view : POSITION;
	float3 n_view : NORMAL;
	float2 tex    : TEXCOORD0;
};

//-----------------------------------------------------------------------------
// Vertex Shader
//-----------------------------------------------------------------------------
PS_INPUT VS(VS_INPUT input) {
	PS_INPUT output = (PS_INPUT)0;
	output.p_view   = mul(input.p, model_to_world);
	output.p_view   = mul(output.p_view, world_to_view);
	output.p        = mul(output.p_view, view_to_projection);
	output.tex      = input.tex;
	output.n_view   = mul(input.n, (float3x3)world_to_view_inverse_transpose);
	return output;
}

//-----------------------------------------------------------------------------
// Pixel Shader
//-----------------------------------------------------------------------------
float4 PS(PS_INPUT input) : SV_Target {
	return diffuse_texture_map.Sample(texture_sampler, input.tex) * cd;
	//const float3 l_view = normalize(light_p_view - input.p_view);
	//return ca + cd * saturate(dot(input.n_view, l_view));
	//return float4(1.0f, 1.0f, 0.0f, 1.0f);
}