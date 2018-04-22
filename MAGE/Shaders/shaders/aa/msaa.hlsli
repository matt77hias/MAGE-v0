#ifndef MAGE_HEADER_MSAA
#define MAGE_HEADER_MSAA

//-----------------------------------------------------------------------------
// Engine Configuration
//-----------------------------------------------------------------------------
// Defines			                        | Default
//-----------------------------------------------------------------------------
// DISABLE_INVERTED_Z_BUFFER                | not defined

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#include "normal.hlsli"
#include "tone_mapping.hlsli"

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
struct InputTexturesMSAA {
	Texture2DMS< float4 > image;
	Texture2DMS< float2 > normal;
	Texture2DMS< float  > depth;
};

struct OutputTexturesMSAA {
	RWTexture2D< float4 > image;
	RWTexture2D< float2 > normal;
	RWTexture2D< float  > depth;
};

void ResolveMSAA(uint2 p_display, 
				 uint  nb_samples, 
				 float weight,
				 InputTexturesMSAA input_textures, 
				 OutputTexturesMSAA output_textures) {

	float4 ldr        = 0.0f;
	float3 normal_sum = 0.0f;
	#ifdef DISABLE_INVERTED_Z_BUFFER
	float depth       = 1.0f;
	#else  // DISABLE_INVERTED_Z_BUFFER
	float depth       = 0.0f;
	#endif // DISABLE_INVERTED_Z_BUFFER

	// Resolve the (multi-sampled) radiance, normal and depth.
	for (uint i = 0u; i < nb_samples; ++i) {
		
		const float4 hdr = input_textures.image.sample[i][p_display];
		ldr += ToneMap_Max3(hdr, weight);

		const float2 encoded_n = input_textures.normal.sample[i][p_display];
		normal_sum += NORMAL_DECODE_FUNCTION(encoded_n);

		#ifdef DISABLE_INVERTED_Z_BUFFER
		depth = min(depth, input_textures.depth.sample[i][p_display]);
		#else  // DISABLE_INVERTED_Z_BUFFER
		depth = max(depth, input_textures.depth.sample[i][p_display]);
		#endif // DISABLE_INVERTED_Z_BUFFER
	}

	const float4 hdr       = InverseToneMap_Max3(ldr);
	const float3 n         = normalize(normal_sum);
	const float2 encoded_n = NORMAL_ENCODE_FUNCTION(n);

	// Store the resolved radiance.
	output_textures.image[p_display]  = hdr;
	// Store the resolved normal.
	output_textures.normal[p_display] = encoded_n;
	// Store the resolved depth.
	output_textures.depth[p_display]  = depth;
}

#endif // MAGE_HEADER_MSAA