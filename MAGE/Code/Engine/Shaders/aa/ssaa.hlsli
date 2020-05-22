#ifndef MAGE_HEADER_SSAA
#define MAGE_HEADER_SSAA

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
struct InputTexturesSSAA {
	Texture2D< float4 > m_image;
	Texture2D< float2 > m_normal;
	Texture2D< float  > m_depth;
};

struct OutputTexturesSSAA {
	RWTexture2D< float4 > m_image;
	RWTexture2D< float2 > m_normal;
	RWTexture2D< float  > m_depth;
};

void ResolveSSAA(uint2 p_display,
				 uint2 nb_samples,
				 float weight,
				 InputTexturesSSAA input_textures,
				 OutputTexturesSSAA output_textures) {

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

			const float4 hdr = input_textures.m_image[p_ss_display_ij];
			ldr += AA_TONE_MAP_FUNCTION(hdr, weight);

			const float2 encoded_n = input_textures.m_normal[p_ss_display_ij];
			normal_sum += NORMAL_DECODE_FUNCTION(encoded_n);

			#ifdef DISABLE_INVERTED_Z_BUFFER
			depth = min(depth, input_textures.m_depth[p_ss_display_ij]);
			#else  // DISABLE_INVERTED_Z_BUFFER
			depth = max(depth, input_textures.m_depth[p_ss_display_ij]);
			#endif // DISABLE_INVERTED_Z_BUFFER
		}
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

#endif // MAGE_HEADER_SSAA