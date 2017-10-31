//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#include "global.hlsli"
#include "normal_mapping.hlsli"

//-----------------------------------------------------------------------------
// Constant Buffers
//-----------------------------------------------------------------------------
CBUFFER(Model, SLOT_CBUFFER_MODEL) {
	// TRANSFORM
	// The object-to-view transformation matrix.
	float4x4 g_object_to_view          : packoffset(c0);
	// The object-to-view inverse transpose transformation matrix
	// = The normal-to-view transformation matrix.
	float4x4 g_normal_to_view          : packoffset(c4);
	// The texture transformation matrix.
	float4x4 g_texture_transform       : packoffset(c8);

	// MATERIAL
	// The base color of the material in linear space.
	float4 g_base_color                : packoffset(c12);
	// The roughness of the material.
	float  g_roughness                 : packoffset(c13.x);
	// The metalness of the material.
	float  g_metalness                 : packoffset(c13.y);
}

//-----------------------------------------------------------------------------
// SRVs
//-----------------------------------------------------------------------------
TEXTURE_2D(g_base_color_texture, float4, SLOT_SRV_BASE_COLOR);
TEXTURE_2D(g_material_texture,   float4, SLOT_SRV_MATERIAL);
TEXTURE_2D(g_normal_texture,     float2, SLOT_SRV_NORMAL);

//-----------------------------------------------------------------------------
// Definitions and Declarations
//-----------------------------------------------------------------------------

/**
 Return the base color of the material.

 @param[in]		tex
				The texture coordinates.
 @return		The base color of the material.
 */
float4 GetMaterialBaseColor(float2 tex) {
	// Obtain the base color of the material.
#ifdef DISSABLE_BASE_COLOR_TEXTURE
	return g_base_color;
#else  // DISSABLE_BASE_COLOR_TEXTURE
	return g_base_color * g_base_color_texture.Sample(g_linear_wrap_sampler, tex);
#endif // DISSABLE_BASE_COLOR_TEXTURE
}

/**
 Return the parameters of the material.

 @param[in]		tex
				The texture coordinates.
 @return		The parameters [roughness, metalness] of the material.
 */
float2 GetMaterialParameters(float2 tex) {
	// Obtain the material parameters of the material.
#ifdef DISSABLE_MATERIAL_TEXTURE
	return float2(g_roughness, g_metalness);
#else  // DISSABLE_MATERIAL_TEXTURE
	const float2 material 
		= g_material_texture.Sample(g_linear_wrap_sampler, tex).xy;
	return float2(g_roughness, g_metalness) * material;
#endif // DISSABLE_MATERIAL_TEXTURE
}

/**
 Return the view-space normal at the given hit point.

 @param[in]		p
				The view-space hit position.
 @param[in]		n
				The (unperturbed) view-space surface normal.
 @param[in]		tex
				The texture coordinates.
 @return		The view-space normal at the given hit point.
 */
float3 GetNormal(float3 p, float3 n, float2 tex) {
	// Obtain the view-space normal.
#ifdef TSNM
	// Obtain the tangent-space normal coefficients in the [-1,1] range. 
	const float3 c 
		= UnpackNormal(g_normal_texture.Sample(g_linear_wrap_sampler, tex));
	// Perturb the view-space normal.
	return PerturbNormal(p, normalize(n), tex, c);
#else  // TSNM
	// Normalize the view-space normal.
	return normalize(n);
#endif // TSNM
}