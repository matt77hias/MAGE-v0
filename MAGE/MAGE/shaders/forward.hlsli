//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#include "gbuffer_input.hlsli"
#include "normal_mapping.hlsli"
#include "transform.hlsli"
#include "lighting.hlsli"

//-----------------------------------------------------------------------------
// Pixel Shader
//-----------------------------------------------------------------------------
float4 PS(PSInputPositionNormalTexture input) : SV_Target {

#ifdef TSNM
	// Obtain the tangent-space normal coefficients in the [-1,1] range. 
	const float3 c      = UnpackNormal(
		g_normal_texture.Sample(g_linear_wrap_sampler, input.tex2));
	// Normalize the view-space normal.
	const float3 n0     = normalize(input.n_view);
	// Perturb the view-space normal.
	const float3 n_view = PerturbNormal(input.p_view, n0, input.tex2, c);
#else  // TSNM
	// Normalize the view-space normal.
	const float3 n_view = normalize(input.n_view);
#endif // TSNM

	// Obtain the base color of the material.
#ifdef DISSABLE_BASE_COLOR_TEXTURE
	const float4 base_color = g_base_color;
#else  // DISSABLE_BASE_COLOR_TEXTURE
	const float4 base_color = g_base_color
		* g_base_color_texture.Sample(g_linear_wrap_sampler, input.tex);
#endif // DISSABLE_BASE_COLOR_TEXTURE

	// Obtain the material parameters of the material.
#ifdef DISSABLE_MATERIAL_TEXTURE
	const float  roughness  = g_roughness;
	const float  metalness  = g_metalness;
#else  // DISSABLE_MATERIAL_TEXTURE
	const float2 material   = 
		g_material_texture.Sample(g_linear_wrap_sampler, input.tex).xy;
	const float  roughness  = g_roughness * material.x;
	const float  metalness  = g_metalness * material.y;
#endif // DISSABLE_MATERIAL_TEXTURE

	// Calculate the pixel radiance.
	const float3 L = BRDFShading(input.p_view, n_view, 
		                         base_color.xyz, roughness, metalness);

	return float4(L, base_color.w);
}