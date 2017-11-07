//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#include "global.hlsli"

//-----------------------------------------------------------------------------
// SRVs
//-----------------------------------------------------------------------------
TEXTURE_2D(g_input_image_texture,     float4, SLOT_SRV_IMAGE);

//-----------------------------------------------------------------------------
// UAVs
//-----------------------------------------------------------------------------
RW_TEXTURE_2D(g_output_image_texture, float4, SLOT_UAV_IMAGE);

//-----------------------------------------------------------------------------
// Compute Shader
//-----------------------------------------------------------------------------

static const float2 g_disk_offsets[12] = {
	float2(-0.163106, -0.202905),
	float2(-0.420072, -0.036790),
	float2(-0.420072,  0.228568),
	float2(-0.101673,  0.310358),
	float2( 0.481170, -0.097492),
	float2( 0.236717, -0.240013),
	float2( 0.259728,  0.383511),
	float2( 0.092730, -0.446562),
	float2( 0.253715,  0.032212),
	float2( 0.448210,  0.206229),
	float2(-0.160970, -0.466307),
	float2(-0.395779, -0.298855)
};

#ifndef GROUP_SIZE
#define GROUP_SIZE GROUP_SIZE_DEFAULT
#endif

[numthreads(GROUP_SIZE, GROUP_SIZE, 1)]
void CS(uint3 thread_id : SV_DispatchThreadID) {

	const uint2 location = g_viewport_top_left + thread_id.xy;
	if (any(location >= g_display_resolution)) {
		return;
	}

	//[unroll]
	//for (uint i = 0u, i < 12u; ++i) {
	//	const float2 offset_location = location + g_disk_offsets[i];
	//	const float2 uv_location     = LocationToUV(offset_location);
	//}

	g_output_image_texture[location] = 0.0f;
}