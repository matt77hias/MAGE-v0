#ifndef MAGE_HEADER_AA
#define MAGE_HEADER_AA

//-----------------------------------------------------------------------------
// Engine Configuration
//-----------------------------------------------------------------------------
// Defines			                        | Default
//-----------------------------------------------------------------------------
// FXAA                                     | not defined
// MSAA                                     | not defined
// PRESERVE_ALPHA                           | not defined
// SSAA                                     | not defined

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#include "math.hlsli"
#include "tone_mapping.hlsli"

#ifdef FXAA
	#define FXAA_PC               1
	#define FXAA_HLSL_5           1
	#define FXAA_QUALITY__PRESET 39
	#include "aa\fxaa3_11.hlsli"
#endif // FXAA

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions: PreprocessAA
//-----------------------------------------------------------------------------
void PreprocessAA(uint2 p_display,
				  Texture2D< float4 > input_image,
				  RWTexture2D< float4 > output_image) {
	
	#ifdef PRESERVE_ALPHA

	const float4 hdr = input_image[p_display];
	const float4 ldr = ToneMap_Max3(hdr);

	// Store the resolved radiance.
	output_image[p_display] = ldr;

	#else  // PRESERVE_ALPHA

	const float3 hdr = input_image[p_display].xyz;
	const float3 ldr = ToneMap_Max3(hdr);
	const float luminance = Luminance(hdr);

	// Store the resolved radiance.
	// The alpha channel contains the luminance (needed for FXAA).
	output_image[p_display] = float4(ldr, luminance);

	#endif // PRESERVE_ALPHA
}

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions: FXAA
//-----------------------------------------------------------------------------
#ifdef FXAA

void ApplyFXAA(uint2 p_display,
			   float2 display_inv_resolution, 
			   SamplerState input_sampler, 
			   Texture2D< float4 > input_image, 
			   RWTexture2D< float4 > output_image) {

	const float2 uv = (p_display + 0.5f) * display_inv_resolution;
	const FxaaTex fxaa_tex = { input_sampler, input_image };

	const float4 ldr = FxaaPixelShader(
		uv,                     // FxaaFloat2 pos
		0.0f,                   // FxaaFloat4 fxaaConsolePosPos
		fxaa_tex,               // FxaaTex    tex
		fxaa_tex,               // FxaaTex    fxaaConsole360TexExpBiasNegOne
		fxaa_tex,               // FxaaTex    fxaaConsole360TexExpBiasNegTwo
		display_inv_resolution, // FxaaFloat2 fxaaQualityRcpFrame
		0.0f,                   // FxaaFloat4 fxaaConsoleRcpFrameOpt
		0.0f,                   // FxaaFloat4 fxaaConsoleRcpFrameOpt2
		0.0f,                   // FxaaFloat4 fxaaConsole360RcpFrameOpt2
		0.75f,                  // FxaaFloat  fxaaQualitySubpix
		0.166f,                 // FxaaFloat  fxaaQualityEdgeThreshold
		0.0833f,                // FxaaFloat  fxaaQualityEdgeThresholdMin
		8.0f,                   // FxaaFloat  fxaaConsoleEdgeSharpness
		0.125f,                 // FxaaFloat  fxaaConsoleEdgeThreshold
		0.05f,                  // FxaaFloat  fxaaConsoleEdgeThresholdMin                         
		0.0f                    // FxaaFloat4 fxaaConsole360ConstDir
	);
	
	const float4 hdr = InverseToneMap_Max3(ldr);

	// Store the resolved radiance.
	output_image[p_display] = hdr;
}

#endif // FXAA

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions: MSAA
//-----------------------------------------------------------------------------
#ifdef MSAA

struct InputTexturesMSAA {
	Texture2DMS< float4 > image;
	Texture2DMS< float3 > normal;
	Texture2DMS< float  > depth;
};

struct OutputTexturesMSAA {
	RWTexture2D< float4 > image;
	RWTexture2D< float3 > normal;
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

		normal_sum += input_textures.normal.sample[i][p_display];

		#ifdef DISABLE_INVERTED_Z_BUFFER
		depth = min(depth, input_textures.depth.sample[i][p_display]);
		#else  // DISABLE_INVERTED_Z_BUFFER
		depth = max(depth, input_textures.depth.sample[i][p_display]);
		#endif // DISABLE_INVERTED_Z_BUFFER
	}

	const float4 hdr    = InverseToneMap_Max3(ldr);
	const float3 normal = normalize(normal_sum);

	// Store the resolved radiance.
	output_textures.image[p_display]  = hdr;
	// Store the resolved normal.
	output_textures.normal[p_display] = normal;
	// Store the resolved depth.
	output_textures.depth[p_display]  = depth;
}

#endif // MSAA

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions: SSAA
//-----------------------------------------------------------------------------
#ifdef SSAA

struct InputTexturesSSAA {
	Texture2D< float4 > image;
	Texture2D< float3 > normal;
	Texture2D< float  > depth;
};

struct OutputTexturesSSAA {
	RWTexture2D< float4 > image;
	RWTexture2D< float3 > normal;
	RWTexture2D< float  > depth;
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
			
			const float4 hdr = input_textures.image[p_ss_display_ij];
			ldr += ToneMap_Max3(hdr, weight);
			
			normal_sum += input_textures.normal[p_ss_display_ij];
			
			#ifdef DISABLE_INVERTED_Z_BUFFER
			depth = min(depth, input_textures.depth[p_ss_display_ij]);
			#else  // DISABLE_INVERTED_Z_BUFFER
			depth = max(depth, input_textures.depth[p_ss_display_ij]);
			#endif // DISABLE_INVERTED_Z_BUFFER
		}
	}

	const float4 hdr    = InverseToneMap_Max3(ldr);
	const float3 normal = normalize(normal_sum);

	// Store the resolved radiance.
	output_textures.image[p_display]  = hdr;
	// Store the resolved normal.
	output_textures.normal[p_display] = normal;
	// Store the resolved depth.
	output_textures.depth[p_display]  = depth;
}

#endif // SSAA

#endif // MAGE_HEADER_AA