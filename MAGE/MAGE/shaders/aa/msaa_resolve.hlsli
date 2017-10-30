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

#ifndef GROUP_SIZE
#define GROUP_SIZE GROUP_SIZE_DEFAULT
#endif

[numthreads(GROUP_SIZE, GROUP_SIZE, 1)]
void CS(uint3 thread_id : SV_DispatchThreadID) {

	const uint2 location = thread_id.xy;

	uint2 output_dim;
	uint nb_samples;
	g_input_image_texture.GetDimensions(output_dim.x, output_dim.y, nb_samples);
	if (any(location >= output_dim)) {
		return;
	}

	// Resolve the (multi-sampled) radiance, normal and depth.
	float4 ldr_sum    = 0.0f;
	float3 normal_sum = 0.0f;
	float  depth      = Z_FAR;
	for (uint i = 0; i < nb_samples; ++i) {

		const float4 hdr = g_input_image_texture.sample[i][location];
		ldr_sum += saturate(TONE_MAP_COMPONENT(hdr));

		normal_sum += g_input_normal_texture.sample[i][location];

		// Non-inverted Z-buffer: 
		// output.p = min(depth, g_input_depth_texture.sample[i][location]);
		depth = max(depth, g_input_depth_texture.sample[i][location]);
	}

	const float inv_nb_samples = 1.0f / nb_samples;

	// Store the resolved radiance.
	g_output_image_texture[location]  = INVERSE_TONE_MAP_COMPONENT(ldr_sum * inv_nb_samples);
	// Store the resolved normal.
	g_output_normal_texture[location] = normalize(normal_sum);
	// Store the resolved depth.
	g_output_depth_texture[location]  = depth;
}