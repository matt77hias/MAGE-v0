#include "basic.fx"

float4 PS(PSInputPositionNormalTexture input) : SV_Target {
	const float3 p_view = input.p_view.xyz;
	const float c = 1.0f - saturate(length(p_view) / 5.0f);
	return float4(c, c, c, 1.0f);
}