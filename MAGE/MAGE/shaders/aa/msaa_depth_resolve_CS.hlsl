//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#include "global.hlsli"

//-----------------------------------------------------------------------------
// SRVs
//-----------------------------------------------------------------------------
TEXTURE_2D_MS(g_input,  float, SLOT_SRV_DEPTH);

//-----------------------------------------------------------------------------
// UAVs
//-----------------------------------------------------------------------------
RW_TEXTURE_2D(g_output, float, SLOT_UAV_IMAGE);

//-----------------------------------------------------------------------------
// Compute Shader
//-----------------------------------------------------------------------------

#ifndef GROUP_SIZE
#define GROUP_SIZE GROUP_SIZE_DEFAULT
#endif

[numthreads(GROUP_SIZE, GROUP_SIZE, 1)]
void CS(uint3 thread_id : SV_DispatchThreadID) {

	const uint2 location = thread_id.xy;

	uint2 dim;
	uint nb_samples;
	g_input.GetDimensions(dim.x, dim.y, nb_samples);
	if (any(location >= dim)) {
		return;
	}

	// Resolve the (multi-sampled) depth.
	float depth = 0.0f;
	for (uint i = 0; i < nb_samples; ++i) {
		depth = max(depth, g_input.sample[i][location]);
	}

	// Store the resolved depth.
	g_output[location] = depth;
}