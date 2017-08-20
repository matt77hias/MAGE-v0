#include "basic.fx"

float4 PS(PSInputPositionNormalTexture input) : SV_Target {
	return g_Kd;
}