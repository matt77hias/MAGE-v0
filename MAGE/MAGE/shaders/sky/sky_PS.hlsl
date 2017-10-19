//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#include "global.hlsli"

//-----------------------------------------------------------------------------
// Constant Buffers
//-----------------------------------------------------------------------------
CBUFFER(PerFrame, SLOT_CBUFFER_PER_FRAME) {
	// CAMERA
	// The projection-to-view transformation matrix.
	float4x4 g_projection_to_view : packoffset(c0);
	// The view-to-world transformation matrix.
	float4x4 g_view_to_world      : packoffset(c4);
}

//-----------------------------------------------------------------------------
// SRVs
//-----------------------------------------------------------------------------
TEXTURE_CUBE(g_sky, float4, SLOT_SRV_TEXTURE);

//-----------------------------------------------------------------------------
// Pixel Shader
//-----------------------------------------------------------------------------
float4 PS(PSInputNDCPosition input) : SV_Target {
	// Obtain the projection space coodinates.
	const float4 p_proj = float4(input.p_ndc, 1.0f, 1.0f);
	// Obtain the view space coodinates.
	const float4 view   = mul(p_proj, g_projection_to_view);
	const float  inv_view_w = 1.0f / view.w;
	const float3 p_view = view.xyz * inv_view_w;
	// Obtain the world space coordinates.
	const float3 p_world  = mul(p_view, (float3x3)g_view_to_world);
	// Sample the cube map.
	const float3 gc_color = g_sky.Sample(g_linear_wrap_sampler, p_world).xyz;

	return float4(GammaToLinear(gc_color), 1.0f);
}