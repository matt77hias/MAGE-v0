//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#include "gbuffer_input.hlsli"
#include "normal_mapping.hlsli"
#include "transform.hlsli"

//-----------------------------------------------------------------------------
// Pixel Shader
//-----------------------------------------------------------------------------
OMInputDeferred PS(PSInputPositionNormalTexture input) {

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
	
	OMInputDeferred output;
	
	// Pack the base color of the material.
#ifdef DISSABLE_BASE_COLOR_TEXTURE
	output.base_color.xyz  = g_base_color.xyz;
#else  // DISSABLE_BASE_COLOR_TEXTURE
	output.base_color.xyz  = g_base_color.xyz
		* g_base_color_texture.Sample(g_linear_wrap_sampler, input.tex).xyz;
#endif // DISSABLE_BASE_COLOR_TEXTURE

	// Pack the material parameters of the material.
#ifdef DISSABLE_MATERIAL_TEXTURE
	output.material.x      = g_roughness;
	output.material.y      = g_metalness;
#else  // DISSABLE_MATERIAL_TEXTURE
	const float2 material  =
		g_material_texture.Sample(g_linear_wrap_sampler, input.tex).xy;
	output.material.x      = g_roughness * material.x;
	output.material.y      = g_metalness * material.y;
#endif // DISSABLE_MATERIAL_TEXTURE
	
	// Pack the view-space normal: [-1,1] -> [0,1]
	output.normal.xyz = PackNormal(n_view);

	return output;
}