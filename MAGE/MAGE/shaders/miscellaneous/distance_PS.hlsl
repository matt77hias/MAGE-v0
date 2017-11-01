//-----------------------------------------------------------------------------
// Engine Configuration
//-----------------------------------------------------------------------------
// Defines			                      | Default
//-----------------------------------------------------------------------------
// MSAA_AS_SSAA                           | not defined

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#include "global.hlsli"

//-----------------------------------------------------------------------------
// Pixel Shader
//-----------------------------------------------------------------------------
#ifdef MSAA_AS_SSAA
float4 PS(PSInputPositionNormalTexture input, uint index : SV_SampleIndex) : SV_Target {
#else  // MSAA_AS_SSAA
float4 PS(PSInputPositionNormalTexture input) : SV_Target {
#endif // MSAA_AS_SSAA

	const float c = 1.0f - saturate(length(input.p_view) / 5.0f);
	return float4(c, c, c, 1.0f);
}