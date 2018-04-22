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
#include "aa\msaa.hlsli"

//-----------------------------------------------------------------------------
// Engine Defines
//-----------------------------------------------------------------------------
#ifndef GROUP_SIZE
	#define GROUP_SIZE GROUP_SIZE_2D_DEFAULT
#endif

//-----------------------------------------------------------------------------
// SRVs
//-----------------------------------------------------------------------------
TEXTURE_2D_MS(g_input_image_texture,   float4, SLOT_SRV_IMAGE);
TEXTURE_2D_MS(g_input_normal_texture,  float2, SLOT_SRV_NORMAL);
TEXTURE_2D_MS(g_input_depth_texture,   float,  SLOT_SRV_DEPTH);

//-----------------------------------------------------------------------------
// UAVs
//-----------------------------------------------------------------------------
RW_TEXTURE_2D(g_output_image_texture,  float4, SLOT_UAV_IMAGE);
RW_TEXTURE_2D(g_output_normal_texture, float2, SLOT_UAV_NORMAL);
RW_TEXTURE_2D(g_output_depth_texture,  float,  SLOT_UAV_DEPTH);

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

	uint2 dim;
	uint nb_samples;
	g_input_image_texture.GetDimensions(dim.x, dim.y, nb_samples);
	const float weight = 1.0f / nb_samples;
	
	const InputTexturesMSAA  input_textures  = {
		g_input_image_texture,
		g_input_normal_texture,
		g_input_depth_texture,
	};
	const OutputTexturesMSAA output_textures = {
		g_output_image_texture,
		g_output_normal_texture,
		g_output_depth_texture,
	};

	ResolveMSAA(p_display, nb_samples, weight, input_textures, output_textures);
}