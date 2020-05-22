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

	// Obtain the world space coodinates.
	const float3 p_camera = SSDisplayToCamera(input.xy, input.z);
	const float3 p_world  = CameraToWorld(p_camera);

	// Sample the cube map.
	return float4(g_sky.Sample(g_linear_wrap_sampler, p_world), 1.0f);
}