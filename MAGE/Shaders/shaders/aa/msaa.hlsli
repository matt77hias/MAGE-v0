#ifndef MAGE_HEADER_MSAA
#define MAGE_HEADER_MSAA

//-----------------------------------------------------------------------------
// Engine Configuration
//-----------------------------------------------------------------------------
// Defines			                        | Default
//-----------------------------------------------------------------------------
// AA_INVERSE_TONE_MAP_FUNCTION             | InverseToneMap_Max3
// AA_TONE_MAP_FUNCTION                     | ToneMap_Max3
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
	Texture2DMS< float4 > m_image;
	Texture2DMS< float2 > m_normal;
	Texture2DMS< float  > m_depth;
};

struct OutputTexturesMSAA {
	RWTexture2D< float4 > m_image;
	RWTexture2D< float2 > m_normal;
	RWTexture2D< float  > m_depth;
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

		const float4 hdr = input_textures.m_image.sample[i][p_display];
		ldr += AA_TONE_MAP_FUNCTION(hdr, weight);

		const float2 encoded_n = input_textures.m_normal.sample[i][p_display];
		normal_sum += NORMAL_DECODE_FUNCTION(encoded_n);

		#ifdef DISABLE_INVERTED_Z_BUFFER
		depth = min(depth, input_textures.m_depth.sample[i][p_display]);
		#else  // DISABLE_INVERTED_Z_BUFFER
		depth = max(depth, input_textures.m_depth.sample[i][p_display]);
		#endif // DISABLE_INVERTED_Z_BUFFER
	}

	const float4 hdr       = AA_INVERSE_TONE_MAP_FUNCTION(ldr);
	const float3 n         = normalize(normal_sum);
	const float2 encoded_n = NORMAL_ENCODE_FUNCTION(n);

	// Store the resolved radiance.
	output_textures.m_image[p_display]  = hdr;
	// Store the resolved normal.
	output_textures.m_normal[p_display] = encoded_n;
	// Store the resolved depth.
	output_textures.m_depth[p_display]  = depth;
}

#endif // MAGE_HEADER_MSAA