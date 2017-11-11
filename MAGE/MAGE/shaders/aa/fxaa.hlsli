//-----------------------------------------------------------------------------
// Engine Configuration
//-----------------------------------------------------------------------------
// Defines			                      | Default
//-----------------------------------------------------------------------------
// GROUP_SIZE                             | GROUP_SIZE_DEFAULT
// FXAA_GREEN_AS_LUMA                     | not defined

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#include "global.hlsli"
#include "tone_mapping.hlsli"

#define FXAA_PC               1
#define FXAA_HLSL_5           1
#define FXAA_QUALITY__PRESET 39
#include "aa\fxaa3_11.hlsli"

//-----------------------------------------------------------------------------
// SRVs
//-----------------------------------------------------------------------------
TEXTURE_2D(g_input_image_texture,      float4, SLOT_SRV_IMAGE);

//-----------------------------------------------------------------------------
// UAVs
//-----------------------------------------------------------------------------
RW_TEXTURE_2D(g_output_image_texture,  float4, SLOT_UAV_IMAGE);

//-----------------------------------------------------------------------------
// Compute Shader
//-----------------------------------------------------------------------------
#ifndef GROUP_SIZE
#define GROUP_SIZE GROUP_SIZE_DEFAULT
#endif

[numthreads(GROUP_SIZE, GROUP_SIZE, 1)]
void CS(uint3 thread_id : SV_DispatchThreadID) {

	const uint2 location = g_viewport_top_left + thread_id.xy;
	if (any(location >= g_display_resolution)) {
		return;
	}

	const FxaaTex fxaa_tex = { 
		g_linear_mirror_sampler, 
		g_input_image_texture 
	};

#pragma warning(push)
#pragma warning(disable : 4000)
	const float4 ldr = FxaaPixelShader(
		LocationToUV(location),                  // FxaaFloat2 pos
		0.0f,                                    // FxaaFloat4 fxaaConsolePosPos
		fxaa_tex,                                // FxaaTex tex
		fxaa_tex,                                // FxaaTex fxaaConsole360TexExpBiasNegOne
		fxaa_tex,                                // FxaaTex fxaaConsole360TexExpBiasNegTwo
		1.0f / g_display_resolution,             // FxaaFloat2 fxaaQualityRcpFrame
		0.0f,                                    // FxaaFloat4 fxaaConsoleRcpFrameOpt
		0.0f,                                    // FxaaFloat4 fxaaConsoleRcpFrameOpt2
		0.0f,                                    // FxaaFloat4 fxaaConsole360RcpFrameOpt2
		0.75f,                                   // FxaaFloat  fxaaQualitySubpix
		0.166f,                                  // FxaaFloat  fxaaQualityEdgeThreshold
		0.0833f,                                 // FxaaFloat  fxaaQualityEdgeThresholdMin
		8.0f,                                    // FxaaFloat  fxaaConsoleEdgeSharpness
		0.125f,                                  // FxaaFloat  fxaaConsoleEdgeThreshold
		0.05f,                                   // FxaaFloat  fxaaConsoleEdgeThresholdMin                         
		0.0f                                     // FxaaFloat4 fxaaConsole360ConstDir
	);
#pragma warning(pop)

	// Store the resolved radiance.
	g_output_image_texture[location] = InverseToneMap_Max3(ldr);
}