//-----------------------------------------------------------------------------
// Engine Configuration
//-----------------------------------------------------------------------------
// Defines			                      | Default
//-----------------------------------------------------------------------------
// MSAA                                   | not defined
// GROUP_SIZE                             | GROUP_SIZE_DEFAULT

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#include "global.hlsli"
#include "tone_mapping.hlsli"

//-----------------------------------------------------------------------------
// SRVs
//-----------------------------------------------------------------------------
TEXTURE_2D_MS(g_input_image_texture,   float4, SLOT_SRV_IMAGE);
TEXTURE_2D_MS(g_input_normal_texture,  float3, SLOT_SRV_NORMAL);
TEXTURE_2D_MS(g_input_depth_texture,   float,  SLOT_SRV_DEPTH);

//-----------------------------------------------------------------------------
// UAVs
//-----------------------------------------------------------------------------
RW_TEXTURE_2D(g_output_image_texture,  float4, SLOT_UAV_IMAGE);
RW_TEXTURE_2D(g_output_normal_texture, float3, SLOT_UAV_NORMAL);
RW_TEXTURE_2D(g_output_depth_texture,  float,  SLOT_UAV_DEPTH);

//-----------------------------------------------------------------------------
// Compute Shader
//-----------------------------------------------------------------------------

#if defined(MSAA) && defined(GROUP_SIZE)

struct Data {
	float4 ldr;
	float3 normal;
	float  depth;
};

groupshared Data data[MSAA * GROUP_SIZE * GROUP_SIZE];

[numthreads(MSAA, GROUP_SIZE, GROUP_SIZE)]
void CS(uint3 thread_id : SV_DispatchThreadID, 
	uint3 group_thread_id : SV_GroupThreadID,
	uint  group_index : SV_GroupIndex) {

	static const float weight = 1.0f / MSAA;

	const uint2 location = g_viewport_top_left + thread_id.yz;
	
	// Accessing a texture out of bounds, results in zeros. All threads in a 
	// MSAA tile have or do not have data available. Thus the averaging will
	// always be correct.

	// Collect and store the data in the group shared memory.
	data[group_index].ldr 
		= ToneMap_Max3(
			g_input_image_texture.sample[group_thread_id.x][location],
		    weight);
	data[group_index].normal 
		= g_input_normal_texture.sample[group_thread_id.x][location];
	data[group_index].depth 
		= g_input_depth_texture.sample[group_thread_id.x][location];

	// Sync all group shared memory accesses.
	GroupMemoryBarrierWithGroupSync();
	
	// Early termination.
	if (0 != group_thread_id.x) {
		return;
	}
	if (any(location >= g_display_resolution)) {
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
	for (uint i = group_index; i < group_index + MSAA; ++i) {
		ldr_sum    += data[i].ldr;
		normal_sum += data[i].normal;

#ifdef DISSABLE_INVERTED_Z_BUFFER
		depth = min(depth, data[i].depth);
#else  // DISSABLE_INVERTED_Z_BUFFER
		depth = max(depth, data[i].depth);
#endif // DISSABLE_INVERTED_Z_BUFFER
	}

	// Store the resolved radiance.
	g_output_image_texture[location]  = InverseToneMap_Max3(ldr_sum);
	// Store the resolved normal.
	g_output_normal_texture[location] = normalize(normal_sum);
	// Store the resolved depth.
	g_output_depth_texture[location]  = depth;
}

#else  // MSAA && GROUP_SIZE

#ifndef GROUP_SIZE
#define GROUP_SIZE GROUP_SIZE_DEFAULT
#endif

[numthreads(GROUP_SIZE, GROUP_SIZE, 1)]
void CS(uint3 thread_id : SV_DispatchThreadID) {

	const uint2 location = g_viewport_top_left + thread_id.xy;
	if (any(location >= g_display_resolution)) {
		return;
	}

	uint2 dim;
	uint nb_samples;
	g_input_image_texture.GetDimensions(dim.x, dim.y, nb_samples);

	const float weight = 1.0f / nb_samples;

	float4 ldr_sum    = 0.0f;
	float3 normal_sum = 0.0f;
#ifdef DISSABLE_INVERTED_Z_BUFFER
	float depth       = 1.0f;
#else  // DISSABLE_INVERTED_Z_BUFFER
	float depth       = 0.0f;
#endif // DISSABLE_INVERTED_Z_BUFFER

	// Resolve the (multi-sampled) radiance, normal and depth.
	for (uint i = 0; i < nb_samples; ++i) {
		ldr_sum += ToneMap_Max3(g_input_image_texture.sample[i][location], 
			                    weight);

		normal_sum += g_input_normal_texture.sample[i][location];

#ifdef DISSABLE_INVERTED_Z_BUFFER
		depth = min(depth, g_input_depth_texture.sample[i][location]);
#else  // DISSABLE_INVERTED_Z_BUFFER
		depth = max(depth, g_input_depth_texture.sample[i][location]);
#endif // DISSABLE_INVERTED_Z_BUFFER
	}

	// Store the resolved radiance.
	g_output_image_texture[location]  = InverseToneMap_Max3(ldr_sum);
	// Store the resolved normal.
	g_output_normal_texture[location] = normalize(normal_sum);
	// Store the resolved depth.
	g_output_depth_texture[location]  = depth;
}

#endif // MSAA && GROUP_SIZE