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
	float2(-0.326212f, -0.40581f),
	float2(-0.840144f, -0.07358f),
	float2(-0.840144f,  0.457137f),
	float2(-0.203345f,  0.620716f),
	float2( 0.96234f,  -0.194983f),
	float2( 0.473434f, -0.480026f),
	float2( 0.519456f,  0.767022f),
	float2( 0.185461f, -0.893124f),
	float2( 0.507431f,  0.064425f),
	float2( 0.89642f,   0.412458f),
	float2(-0.32194f,  -0.932615f),
	float2(-0.791559f, -0.59771f)
};

float GetBlurFactor(float p_view_z) {
	return smoothstep(0.0f, g_lens_radius, abs(p_view_z - g_focal_length));
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
	if (p_view_z <= g_focal_length) {
		return;
	}

	const float coc_radius = blur_factor * g_max_coc_radius;

	float4 hdr_sum = g_input_image_texture[location];
	float  contribution_sum = 1.0f;

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