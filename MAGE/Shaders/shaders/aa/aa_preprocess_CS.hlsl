//-----------------------------------------------------------------------------
// Engine Configuration
//-----------------------------------------------------------------------------
// Defines			                     | Default
//-----------------------------------------------------------------------------
// PRESERVE_ALPHA                        | not defined

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#include "global.hlsli"
#include "tone_mapping.hlsli"

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

#ifndef GROUP_SIZE
	#define GROUP_SIZE GROUP_SIZE_2D_DEFAULT
#endif

[numthreads(GROUP_SIZE, GROUP_SIZE, 1)]
void CS(uint3 thread_id : SV_DispatchThreadID) {

	const uint2 p_display = g_viewport_top_left + thread_id.xy;

	[branch]
	if (any(p_display >= g_display_resolution)) {
		return;
	}

	#ifdef PRESERVE_ALPHA

	const float4 hdr = g_input_image_texture[p_display];
	const float4 ldr = ToneMap_Max3(hdr);

	// Store the resolved radiance.
	g_output_image_texture[p_display] = ldr;

	#else  // PRESERVE_ALPHA

	const float3 hdr = g_input_image_texture[p_display].xyz;
	const float3 ldr = ToneMap_Max3(hdr);
	const float luminance = Luminance(hdr);

	// Store the resolved radiance.
	// The alpha channel contains the luminance (needed for FXAA).
	g_output_image_texture[p_display] = float4(ldr, luminance);

	#endif // PRESERVE_ALPHA
}