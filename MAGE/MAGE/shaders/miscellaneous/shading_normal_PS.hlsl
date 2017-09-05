//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#include "structures.hlsli"
#include "math.hlsli"

//-----------------------------------------------------------------------------
// Pixel Shader
//-----------------------------------------------------------------------------
float4 PS(PSInputPositionNormalTexture input) : SV_Target {
	// Normalize the view-space normal.
	const float3 n_view = normalize(input.n_view);
	
	// Converts the [-1,1] range to the [0,1] range.
	return float4(PackNormal(n_view), 1.0f);
}