//-----------------------------------------------------------------------------
// Engine Configuration
//-----------------------------------------------------------------------------
// Defines			                      | Default
//-----------------------------------------------------------------------------
// TONE_MAP_COMPONENT                     | ToneMap_Reinhard
// INVERSE_TONE_MAP_COMPONENT             | InverseToneMap_Reinhard

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
#define GROUP_SIZE GROUP_SIZE_DEFAULT
#endif

[numthreads(GROUP_SIZE, GROUP_SIZE, 1)]
void CS(uint3 thread_id : SV_DispatchThreadID) {

	const uint2 output_location = g_viewport_top_left + thread_id.xy;
	if (any(output_location >= g_display_resolution)) {
		return;
	}

	uint2 output_dim;
	g_output_image_texture.GetDimensions(output_dim.x, output_dim.y);

	const uint2 nb_samples     = g_viewport_resolution / output_dim;
	const uint2 input_location = output_location * nb_samples;

	// Resolve the (super-sampled) radiance, normal and depth.
	float4 ldr_sum    = 0.0f;
	float3 normal_sum = 0.0f;
#ifdef DISSABLE_INVERTED_Z_BUFFER
	float depth       = 1.0f;
#else  // DISSABLE_INVERTED_Z_BUFFER
	float depth       = 0.0f;
#endif // DISSABLE_INVERTED_Z_BUFFER
	for (uint i = 0; i < nb_samples.x; ++i) {
		for (uint j = 0; j < nb_samples.y; ++j) {

			const uint2 location = input_location + uint2(i,j);

			const float4 hdr = g_input_image_texture[location];
			ldr_sum += saturate(TONE_MAP_COMPONENT(hdr));

			normal_sum += g_input_normal_texture[location];

#ifdef DISSABLE_INVERTED_Z_BUFFER
			depth = min(depth, g_input_depth_texture[input_location]);
#else  // DISSABLE_INVERTED_Z_BUFFER
			depth = max(depth, g_input_depth_texture[location]);
#endif // DISSABLE_INVERTED_Z_BUFFER
		}
	}

	const float inv_nb_samples = 1.0f / (nb_samples.x * nb_samples.y);

	// Store the resolved radiance.
	g_output_image_texture[output_location]  = INVERSE_TONE_MAP_COMPONENT(ldr_sum * inv_nb_samples);
	// Store the resolved normal.
	g_output_normal_texture[output_location] = normalize(normal_sum);
	// Store the resolved depth.
	g_output_depth_texture[output_location]  = depth;
}