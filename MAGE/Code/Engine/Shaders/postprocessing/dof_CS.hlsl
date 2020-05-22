//-----------------------------------------------------------------------------
// Engine Configuration
//-----------------------------------------------------------------------------
// Defines			                        | Default
//-----------------------------------------------------------------------------
// GROUP_SIZE                               | GROUP_SIZE_2D_DEFAULT

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#include "global.hlsli"

//-----------------------------------------------------------------------------
// Engine Defines
//-----------------------------------------------------------------------------
#ifndef GROUP_SIZE
	#define GROUP_SIZE GROUP_SIZE_2D_DEFAULT
#endif

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
	{ -0.326212f, -0.405810f },
	{ -0.840144f, -0.073580f },
	{ -0.840144f,  0.457137f },
	{ -0.203345f,  0.620716f },
	{  0.962340f, -0.194983f },
	{  0.473434f, -0.480026f },
	{  0.519456f,  0.767022f },
	{  0.185461f, -0.893124f },
	{  0.507431f,  0.064425f },
	{  0.896420f,  0.412458f },
	{ -0.321940f, -0.932615f },
	{ -0.791559f, -0.597710f }
};

float GetCircleOfConfusionRadius(float p_camera_z) {
	const float magnification = g_focal_length / (g_focus_distance - g_focal_length);
	// Compute the CoC radius in camera space.
	const float CoC_radius = g_aperture_radius * abs(p_camera_z - g_focus_distance)
		                   / p_camera_z;
	// Compute the CoC radius in display|viewport space.
	return CoC_radius * magnification;
}

//float GetBlurFactor(float p_camera_z) {
//	return smoothstep(0.0f, g_lens_radius, abs(p_camera_z - g_focal_length));
//}

[numthreads(GROUP_SIZE, GROUP_SIZE, 1)]
void CS(uint3 thread_id : SV_DispatchThreadID) {
	const uint2 p_viewport = thread_id.xy;
	uint2 p_display;

	[branch]
	if (IsViewportOutOfBounds(p_viewport, p_display)) {
		return;
	}

	const float p_camera_z  = DepthToCameraZ(g_depth_texture[p_display]);
	const float CoC_radius  = GetCircleOfConfusionRadius(p_camera_z);
	float4 hdr_sum          = g_input_image_texture[p_display];
	float  contribution_sum = 1.0f;

	[unroll]
	for (uint i = 0u; i < 12u; ++i) {
		const float2 p_display_i    = p_display + g_disk_offsets[i] * 20.0f * CoC_radius;
		const float  p_camera_z_i   = DepthToCameraZ(g_depth_texture[p_display_i]);
		const float  CoC_radius_i   = GetCircleOfConfusionRadius(p_camera_z_i);

		const float  a = 1.0f; // abs(p_camera_z_i - p_camera_z) < CoC_radius_i; // In Bokeh circle?
		const float  b = 1.0f; // (p_camera_z_i >= p_camera_z);                  // Is behind?

		hdr_sum          += (a * b) * g_input_image_texture[p_display_i];
		contribution_sum += (a * b);
	}

	const float inv_contribution_sum = 1.0f / contribution_sum;
	g_output_image_texture[p_display] = hdr_sum * inv_contribution_sum;
}