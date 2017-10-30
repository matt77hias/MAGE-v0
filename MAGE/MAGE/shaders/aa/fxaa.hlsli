//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#include "global.hlsli"
#include "tone_mapping.hlsli"

#define FXAA_PC               1
#define FXAA_HLSL_5           1
#define FXAA_QUALITY__PRESET 13
#define FXAA_GREEN_AS_LUMA    1
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

	const uint2 location = thread_id.xy;

	uint2 dim;
	g_output_image_texture.GetDimensions(dim.x, dim.y);
	if (any(location >= dim)) {
		return;
	}

	const FxaaTex fxaa_tex = { 
		g_linear_clamp_sampler, 
		g_input_image_texture 
	};

	const float4 ldr = FxaaPixelShader(
		NormalizeDispatchThreadID(location), // FxaaFloat2 pos
		FxaaFloat4(0.0f, 0.0f, 0.0f, 0.0f),  // FxaaFloat4 fxaaConsolePosPos
		fxaa_tex,                            // FxaaTex tex
		fxaa_tex,                            // FxaaTex fxaaConsole360TexExpBiasNegOne
		fxaa_tex,                            // FxaaTex fxaaConsole360TexExpBiasNegTwo
		float2(1.0f / dim.x, 1.0f / dim.y),  // FxaaFloat2 fxaaQualityRcpFrame
		FxaaFloat4(0.0f, 0.0f, 0.0f, 0.0f),  // FxaaFloat4 fxaaConsoleRcpFrameOpt
		FxaaFloat4(0.0f, 0.0f, 0.0f, 0.0f),  // FxaaFloat4 fxaaConsoleRcpFrameOpt2
		FxaaFloat4(0.0f, 0.0f, 0.0f, 0.0f),  // FxaaFloat4 fxaaConsole360RcpFrameOpt2
		0.75f,                               // FxaaFloat  fxaaQualitySubpix
		0.166f,                              // FxaaFloat  fxaaQualityEdgeThreshold
		0.0833f,                             // FxaaFloat  fxaaQualityEdgeThresholdMin
		8.0f,                                // FxaaFloat  fxaaConsoleEdgeSharpness
		0.125f,                              // FxaaFloat  fxaaConsoleEdgeThreshold
		0.05f,                               // FxaaFloat  fxaaConsoleEdgeThresholdMin                         
		FxaaFloat4(0.0f, 0.0f, 0.0f, 0.0f)   // FxaaFloat4 fxaaConsole360ConstDir
	);

	// Store the resolved radiance.
	g_output_image_texture[location] = INVERSE_TONE_MAP_COMPONENT(ldr);
}