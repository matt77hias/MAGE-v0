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

	// Normalize the view-space normal.
	const float3 n_view = normalize(input.n_view);
	
	// Converts the [-1,1] range to the [0,1] range.
	return float4(SNORMtoUNORM(n_view), 1.0f);
}