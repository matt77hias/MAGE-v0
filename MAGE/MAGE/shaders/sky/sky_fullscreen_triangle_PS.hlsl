//-----------------------------------------------------------------------------
// Engine Configuration
//-----------------------------------------------------------------------------
// Defines			                      | Default
//-----------------------------------------------------------------------------
// MSAA_AS_SSAA                           | not defined

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#include "global.hlsli"

//-----------------------------------------------------------------------------
// SRVs
//-----------------------------------------------------------------------------
TEXTURE_CUBE(g_sky, float3, SLOT_SRV_TEXTURE);

//-----------------------------------------------------------------------------
// Pixel Shader
//-----------------------------------------------------------------------------
#ifdef MSAA_AS_SSAA
	float4 PS(PSInputNDCPosition input, uint index : SV_SampleIndex) : SV_Target {
#else  // MSAA_AS_SSAA
	float4 PS(PSInputNDCPosition input) : SV_Target {
#endif // MSAA_AS_SSAA

	// Obtain the projection space coodinates.
	const float4 p_proj = float4(input.p_ndc, 1.0f);
	// Obtain the view space coodinates.
	const float4 view   = mul(p_proj, g_projection_to_view);
	const float  inv_view_w = 1.0f / view.w;
	const float3 p_view = view.xyz * inv_view_w;
	// Obtain the world space coordinates.
	const float3 p_world  = mul(p_view, (float3x3)g_view_to_world);
	// Sample the cube map.
	return float4(g_sky.Sample(g_linear_wrap_sampler, p_world), 1.0f);
}