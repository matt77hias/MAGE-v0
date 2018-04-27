//-----------------------------------------------------------------------------
// Engine Configuration
//-----------------------------------------------------------------------------
// Defines			                        | Default
//-----------------------------------------------------------------------------
// MSAA_AS_SSAA                             | not defined

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
float4 PS(float4 input : SV_Position, uint index : SV_SampleIndex) : SV_Target {
#else  // MSAA_AS_SSAA
float4 PS(float4 input : SV_Position) : SV_Target {
#endif // MSAA_AS_SSAA

	// Obtain the NDC space coodinates.
	const float2 p_ss_display  = input.xy;
	const float2 p_ss_viewport = SSDisplayToSSViewport(p_ss_display);
	const float2 p_ndc_xy      = UVtoNDC(SSViewportToUV(p_ss_viewport));
	const float3 p_ndc         = { p_ndc_xy, input.z };
	// Obtain the world space coordinates.
	const float3 p_world       = NDCToWorld(p_ndc);
	// Sample the cube map.
	return float4(g_sky.Sample(g_linear_wrap_sampler, p_world), 1.0f);
}