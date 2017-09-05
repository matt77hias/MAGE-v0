//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#include "structures.hlsli"

//-----------------------------------------------------------------------------
// Vertex Shader
//-----------------------------------------------------------------------------
PSInputNDCPosition VS(uint id: SV_VertexID) {
	PSInputNDCPosition output;
	
	// v0 = (-1,-1, 0)
	// v1 = (-1, 3, 0)
	// v2 = ( 3,-1, 0)
	const float x = (float)(id / 2) * 4.0 - 1.0;
	const float y = (float)(id % 2) * 4.0 - 1.0;
	output.p      = float4(x, y, 0.0, 1.0);
	output.p_ndc  = float2(x, y);
	return output;
}