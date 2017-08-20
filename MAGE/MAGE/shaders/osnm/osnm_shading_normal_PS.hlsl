#include "basic.fx"

float4 PS(PSInputPositionNormalTexture input) : SV_Target {
	const float3 n_view = ObjectSpaceNormalMapping_PerturbNormal(input.tex);
	return float4(InverseBiasX2(n_view), 1.0f);
}