//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#include "structures.fx"

cbuffer Color : register(b0) {
	float4 g_color : packoffset(c0);
};

float4 PS(PSInputPositionNormalTexture input) : SV_Target {
	return g_color;
}