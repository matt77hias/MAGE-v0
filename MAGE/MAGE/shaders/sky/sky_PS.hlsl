//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#include "global.hlsli"

//-----------------------------------------------------------------------------
// Constant Buffers
//-----------------------------------------------------------------------------
CBUFFER(PerFrame, SLOT_CBUFFER_PER_FRAME) {
	// CAMERA
	// The projection values of the view-to-projection transformation matrix.
	// g_projection_values.x = 1 / view_to_projection00
	// g_projection_values.y = 1 / view_to_projection11
	// g_projection_values.z =  view_to_projection32
	// g_projection_values.w = -view_to_projection22
	float4 g_projection_values : packoffset(c0);
	// The view-to-world transformation matrix.
	float4x4 g_view_to_world   : packoffset(c1);
}

//-----------------------------------------------------------------------------
// SRVs
//-----------------------------------------------------------------------------
TEXTURE_CUBE(g_sky, float4, SLOT_SRV_TEXTURE);

//-----------------------------------------------------------------------------
// Pixel Shader
//-----------------------------------------------------------------------------
float4 PS(PSInputNDCPosition input) : SV_Target{
	// Obtain the NDC space coodinates.
	const float3 p_ndc    = float3(input.p_ndc, 1.0f);
	// Obtain the view space coodinates.
	const float3 p_view   = NDCtoView(p_ndc, g_projection_values);
	// Obtain the world space coordinates.
	const float3 p_world  = mul(p_view, (float3x3)g_view_to_world);
	// Sample the cube map.
	const float3 gc_color = g_sky.Sample(g_linear_wrap_sampler, p_world).xyz;
	const float3 color    = InverseGammaCorrect(gc_color);

	return float4(color, 1.0f);
}