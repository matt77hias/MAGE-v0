//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#include "global.hlsli"

//-----------------------------------------------------------------------------
// SRVs
//-----------------------------------------------------------------------------
TEXTURE_2D(g_input_image_texture,     float4, SLOT_SRV_IMAGE);
TEXTURE_2D(g_depth_texture,           float,  SLOT_SRV_DEPTH);

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

float GetBlurFactor(float p_view_z) {
	return smoothstep(0.0f, g_lens_radius, abs(g_focal_length - p_view_z));
}

#ifndef GROUP_SIZE
#define GROUP_SIZE GROUP_SIZE_DEFAULT
#endif

[numthreads(GROUP_SIZE, GROUP_SIZE, 1)]
void CS(uint3 thread_id : SV_DispatchThreadID) {

	const uint2 location = g_viewport_top_left + thread_id.xy;
	if (any(location >= g_display_resolution)) {
		return;
	}

	const float p_view_z    = DepthToViewZ(g_depth_texture[location]);
	const float blur_factor = GetBlurFactor(p_view_z);
	if (blur_factor <= 0.0f) {
		return;
	}

	const float coc_radius = blur_factor * g_max_coc_radius;

	float4 hdr_sum = g_input_image_texture[location];
	float4 contribution_sum = 1.0f;

	[unroll]
	for (uint i = 0u; i < 12u; ++i) {
		const float2 location_i     = location + g_disk_offsets[i] * coc_radius;
		const float  p_view_z_i     = DepthToViewZ(g_depth_texture[location_i]);
		const float  blur_factor_i  = GetBlurFactor(p_view_z_i);
		const float  contribution_i = (p_view_z_i > p_view_z) ? 1.0f : blur_factor_i;

		hdr_sum          += contribution_i * g_input_image_texture[location_i];
		contribution_sum += contribution_i;
	}

	const float inv_contribution_sum = 1.0f / contribution_sum;
	g_output_image_texture[location] = hdr_sum * inv_contribution_sum;
}