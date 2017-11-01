//-----------------------------------------------------------------------------
// Engine Configuration
//-----------------------------------------------------------------------------
// Defines			                      | Default
//-----------------------------------------------------------------------------
// SSAA_X                                 | not defined
// SSAA_Y                                 | not defined
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

// Note: GameBuffer and PrimaryCameraBuffer should reflect the display and 
//       camera viewport after resolving SSAA (i.e. output instead of input).

#ifndef GROUP_SIZE
#define GROUP_SIZE GROUP_SIZE_DEFAULT
#endif

#if defined(SSAA_X) && defined(SSAA_Y)

struct Data {
	float4 ldr;
	float3 normal;
	float  depth;
};

groupshared Data data[GROUP_SIZE][GROUP_SIZE];

[numthreads(GROUP_SIZE, GROUP_SIZE, 1)]
void CS(uint3 thread_id : SV_DispatchThreadID, 
	uint3 group_thread_id : SV_GroupThreadID) {
	
	const uint2 input_location  = g_viewport_top_left * uint2(SSAA_X, SSAA_Y)
		                          + thread_id.xy;

	// Accessing a texture out of bounds, results in zeros. All threads in a 
	// SSAA tile have or do not have data available. Thus the averaging will
	// always be correct.

	// Collect and store the data in the group shared memory.
	const float4 hdr = g_input_image_texture[input_location];
	data[group_thread_id.x][group_thread_id.y].ldr 
		= saturate(TONE_MAP_COMPONENT(hdr));
	data[group_thread_id.x][group_thread_id.y].normal 
		= g_input_normal_texture[input_location];
	data[group_thread_id.x][group_thread_id.y].depth 
		= g_input_depth_texture[input_location];

	// Sync all group shared memory accesses.
	GroupMemoryBarrierWithGroupSync();

	// Early termination.
	const uint2 sample_index = group_thread_id.xy % uint2(SSAA_X, SSAA_Y);
	if (any(0 != sample_index)) {
		return;
	}
	// No need to check the output location.

	float4 ldr_sum    = 0.0f;
	float3 normal_sum = 0.0f;
#ifdef DISSABLE_INVERTED_Z_BUFFER
	float depth       = 1.0f;
#else  // DISSABLE_INVERTED_Z_BUFFER
	float depth       = 0.0f;
#endif // DISSABLE_INVERTED_Z_BUFFER
	
	// Resolve the (multi-sampled) radiance, normal and depth.
	[unroll]
	for (uint i = 0, x = group_thread_id.x; i < SSAA_X; ++i, ++x) {
		[unroll]
		for (uint j = 0, y = group_thread_id.y; j < SSAA_Y; ++j, ++y) {
			ldr_sum    += data[x][y].ldr;
			normal_sum += data[x][y].normal;

#ifdef DISSABLE_INVERTED_Z_BUFFER
			depth = min(depth, data[x][y].depth);
#else  // DISSABLE_INVERTED_Z_BUFFER
			depth = max(depth, data[x][y].depth);
#endif // DISSABLE_INVERTED_Z_BUFFER
		}
	}

	static const float inv_nb_samples = 1.0f / (SSAA_X * SSAA_Y);

	const uint2 output_location = g_viewport_top_left 
		                          + thread_id.xy / uint2(SSAA_X, SSAA_Y);

	// Store the resolved radiance.
	g_output_image_texture[output_location] 
		= INVERSE_TONE_MAP_COMPONENT(ldr_sum * inv_nb_samples);
	// Store the resolved normal.
	g_output_normal_texture[output_location] = normalize(normal_sum);
	// Store the resolved depth.
	g_output_depth_texture[output_location]  = depth;
}

#else  // SSAA_X && SSAA_Y

[numthreads(GROUP_SIZE, GROUP_SIZE, 1)]
void CS(uint3 thread_id : SV_DispatchThreadID) {

	const uint2 output_location = g_viewport_top_left + thread_id.xy;
	if (any(output_location >= g_display_resolution)) {
		return;
	}

	uint2 input_dim;
	g_input_image_texture.GetDimensions(input_dim.x, input_dim.y);

	const uint2 nb_samples     = g_display_resolution / input_dim;
	const uint2 input_location = output_location * nb_samples;

	float4 ldr_sum    = 0.0f;
	float3 normal_sum = 0.0f;
#ifdef DISSABLE_INVERTED_Z_BUFFER
	float depth       = 1.0f;
#else  // DISSABLE_INVERTED_Z_BUFFER
	float depth       = 0.0f;
#endif // DISSABLE_INVERTED_Z_BUFFER

	// Resolve the (super-sampled) radiance, normal and depth.
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
	g_output_image_texture[output_location] 
		= INVERSE_TONE_MAP_COMPONENT(ldr_sum * inv_nb_samples);
	// Store the resolved normal.
	g_output_normal_texture[output_location] = normalize(normal_sum);
	// Store the resolved depth.
	g_output_depth_texture[output_location]  = depth;
}

#endif