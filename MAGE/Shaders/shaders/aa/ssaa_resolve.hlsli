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
#include "tone_mapping.hlsli"

//-----------------------------------------------------------------------------
// SRVs
//-----------------------------------------------------------------------------
TEXTURE_2D(g_input_image_texture,      float4, SLOT_SRV_IMAGE);
TEXTURE_2D(g_input_normal_texture,     float3, SLOT_SRV_NORMAL);
TEXTURE_2D(g_input_depth_texture,      float,  SLOT_SRV_DEPTH);

//-----------------------------------------------------------------------------
// UAVs
//-----------------------------------------------------------------------------
RW_TEXTURE_2D(g_output_image_texture,  float4, SLOT_UAV_IMAGE);
RW_TEXTURE_2D(g_output_normal_texture, float3, SLOT_UAV_NORMAL);
RW_TEXTURE_2D(g_output_depth_texture,  float,  SLOT_UAV_DEPTH);

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

	uint2 input_dim;
	g_input_image_texture.GetDimensions(input_dim.x, input_dim.y);
	uint2 output_dim;
	g_output_image_texture.GetDimensions(output_dim.x, output_dim.y);

	const uint2 nb_samples   = input_dim / output_dim;
	const float weight       = 1.0f / (nb_samples.x * nb_samples.y);
	const uint2 p_ss_display = p_display * nb_samples;
	
	float4 ldr        = 0.0f;
	float3 normal_sum = 0.0f;
	#ifdef DISABLE_INVERTED_Z_BUFFER
	float depth       = 1.0f;
	#else  // DISABLE_INVERTED_Z_BUFFER
	float depth       = 0.0f;
	#endif // DISABLE_INVERTED_Z_BUFFER

	// Resolve the (super-sampled) radiance, normal and depth.
	for (uint i = 0u; i < nb_samples.x; ++i) {
		for (uint j = 0u; j < nb_samples.y; ++j) {

			const uint2 p_ss_display_ij = p_ss_display + uint2(i,j);
			
			const float4 hdr = g_input_image_texture[p_ss_display_ij];
			ldr += ToneMap_Max3(hdr, weight);
			
			normal_sum += g_input_normal_texture[p_ss_display_ij];
			
			#ifdef DISABLE_INVERTED_Z_BUFFER
			depth = min(depth, g_input_depth_texture[p_ss_display_ij]);
			#else  // DISABLE_INVERTED_Z_BUFFER
			depth = max(depth, g_input_depth_texture[p_ss_display_ij]);
			#endif // DISABLE_INVERTED_Z_BUFFER
		}
	}

	const float4 hdr    = InverseToneMap_Max3(ldr);
	const float3 normal = normalize(normal_sum);

	// Store the resolved radiance.
	g_output_image_texture[p_display]  = hdr;
	// Store the resolved normal.
	g_output_normal_texture[p_display] = normal;
	// Store the resolved depth.
	g_output_depth_texture[p_display]  = depth;
}