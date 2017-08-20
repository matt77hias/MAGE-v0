#include "basic.fx"

float4 PS(PSInputPositionNormalTexture input) : SV_Target {
	return g_diffuse_texture.Sample(g_sampler, input.tex);
}