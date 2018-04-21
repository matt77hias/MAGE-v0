#ifndef MAGE_HEADER_FXAA
#define MAGE_HEADER_FXAA

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#include "tone_mapping.hlsli"

#define FXAA_PC               1
#define FXAA_HLSL_5           1
#define FXAA_QUALITY__PRESET 39
#include "aa\fxaa3_11.hlsli"

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
void ApplyFXAA(uint2 p_display,
			   float2 display_inv_resolution, 
			   SamplerState input_sampler, 
			   Texture2D< float4 > input_image, 
			   RWTexture2D< float4 > output_image) {

	const float2 uv = ((float2)p_display + 0.5f) * display_inv_resolution;
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

#endif // MAGE_HEADER_FXAA