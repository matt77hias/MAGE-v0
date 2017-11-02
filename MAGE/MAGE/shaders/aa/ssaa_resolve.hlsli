//-----------------------------------------------------------------------------
// Engine Configuration
//-----------------------------------------------------------------------------
// Defines			                      | Default
//-----------------------------------------------------------------------------
// SSAA                                   | not defined
// GROUP_SIZE                             | GROUP_SIZE_DEFAULT

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#include "global.hlsli"
#include "tone_mapping\tone_mapping.hlsli"

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

#if defined(SSAA) && defined(GROUP_SIZE) && defined(GROUP_SIZE)

struct Data {
	float4 ldr;
	float3 normal;
	float  depth;
};

groupshared Data data[SSAA * SSAA * GROUP_SIZE * GROUP_SIZE];

[numthreads((SSAA * SSAA), GROUP_SIZE, GROUP_SIZE)]
void CS(uint3 thread_id : SV_DispatchThreadID,
	uint3 group_thread_id : SV_GroupThreadID,
	uint  group_index : SV_GroupIndex) {

	static const float weight = 1.0f / (SSAA * SSAA);

	const uint2 output_location = g_viewport_top_left + thread_id.yz;
	const uint2 input_location  = output_location * SSAA 
		+ uint2(group_thread_id.x % SSAA, group_thread_id.x / SSAA);
	
	// Accessing a texture out of bounds, results in zeros. All threads in a 
	// SSAA tile have or do not have data available. Thus the averaging will
	// always be correct.

	// Collect and store the data in the group shared memory.
	data[group_index].ldr    = ToneMap_Max3(
		                       g_input_image_texture[input_location], 
		                       weight);
	data[group_index].normal = g_input_normal_texture[input_location];
	data[group_index].depth  = g_input_depth_texture[input_location];

	// Sync all group shared memory accesses.
	GroupMemoryBarrierWithGroupSync();

	// Early termination.
	if (0 != group_thread_id.x) {
		return;
	}
	if (any(output_location >= g_display_resolution)) {
		return;
	}
	
	float4 ldr_sum    = 0.0f;
	float3 normal_sum = 0.0f;
#ifdef DISSABLE_INVERTED_Z_BUFFER
	float depth       = 1.0f;
#else  // DISSABLE_INVERTED_Z_BUFFER
	float depth       = 0.0f;
#endif // DISSABLE_INVERTED_Z_BUFFER
	
	// Resolve the (multi-sampled) radiance, normal and depth.
	[unroll]
	for (uint i = group_index; i < group_index + (SSAA * SSAA); ++i) {
		ldr_sum    += data[i].ldr;
		normal_sum += data[i].normal;

#ifdef DISSABLE_INVERTED_Z_BUFFER
		depth = min(depth, data[i].depth);
#else  // DISSABLE_INVERTED_Z_BUFFER
		depth = max(depth, data[i].depth);
#endif // DISSABLE_INVERTED_Z_BUFFER
	}

	// Store the resolved radiance.
	g_output_image_texture[output_location]  = InverseToneMap_Max3(ldr_sum);
	// Store the resolved normal.
	g_output_normal_texture[output_location] = normalize(normal_sum);
	// Store the resolved depth.
	g_output_depth_texture[output_location]  = depth;
}

#else  // SSAA && GROUP_SIZE && GROUP_SIZE

#ifndef GROUP_SIZE
#define GROUP_SIZE GROUP_SIZE_DEFAULT
#endif

[numthreads(GROUP_SIZE, GROUP_SIZE, 1)]
void CS(uint3 thread_id : SV_DispatchThreadID) {

	const uint2 output_location = g_viewport_top_left + thread_id.xy;
	if (any(output_location >= g_display_resolution)) {
		return;
	}

	uint2 input_dim;
	g_input_image_texture.GetDimensions(input_dim.x, input_dim.y);

	const uint2 nb_samples     = g_display_resolution / input_dim;
	const float weight         = 1.0f / (nb_samples.x * nb_samples.y);
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

			ldr_sum += ToneMap_Max3(g_input_image_texture[location],
				                    weight);

			normal_sum += g_input_normal_texture[location];

#ifdef DISSABLE_INVERTED_Z_BUFFER
			depth = min(depth, g_input_depth_texture[location]);
#else  // DISSABLE_INVERTED_Z_BUFFER
			depth = max(depth, g_input_depth_texture[location]);
#endif // DISSABLE_INVERTED_Z_BUFFER
		}
	}

	// Store the resolved radiance.
	g_output_image_texture[output_location]  = InverseToneMap_Max3(ldr_sum);
	// Store the resolved normal.
	g_output_normal_texture[output_location] = normalize(normal_sum);
	// Store the resolved depth.
	g_output_depth_texture[output_location]  = depth;
}

#endif // SSAA && GROUP_SIZE && GROUP_SIZE