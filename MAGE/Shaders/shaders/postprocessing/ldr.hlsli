//-----------------------------------------------------------------------------
// Engine Configuration
//-----------------------------------------------------------------------------
// Defines			                        | Default
//-----------------------------------------------------------------------------
// DISABLE_TONE_MAPPING                     | not defined
// GROUP_SIZE                               | GROUP_SIZE_2D_DEFAULT
// TONE_MAP_FUNCTION                        | ToneMap_Uncharted

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#ifndef DISABLE_TONE_MAPPING
	#include "tone_mapping.hlsli"
#endif // DISABLE_TONE_MAPPING

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

//-----------------------------------------------------------------------------
// UAVs
//-----------------------------------------------------------------------------
RW_TEXTURE_2D(g_output_image_texture, float4, SLOT_UAV_IMAGE);

//-----------------------------------------------------------------------------
// Compute Shader
//-----------------------------------------------------------------------------
[numthreads(GROUP_SIZE, GROUP_SIZE, 1)]
void CS(uint3 thread_id : SV_DispatchThreadID) {
	const uint2 p_viewport = thread_id.xy;
	uint2 p_display;

	[branch]
	if (IsViewportOutOfBounds(p_viewport, p_display)) {
		return;
	}

	const float4 hdr = g_input_image_texture[p_display];

	#ifdef DISABLE_TONE_MAPPING
	const float4 ldr = hdr;
	#else  // DISABLE_TONE_MAPPING
	const float4 ldr = TONE_MAP_FUNCTION(hdr);
	#endif // DISABLE_TONE_MAPPING

	g_output_image_texture[p_display] = ldr;
}