//-----------------------------------------------------------------------------
// Engine Configuration
//-----------------------------------------------------------------------------
// Defines			                        | Default
//-----------------------------------------------------------------------------
// DISABLE_BASE_COLOR_TEXTURE               | not defined
// DISABLE_MATERIAL_TEXTURE                 | not defined
// DISABLE_TSNM                             | not defined

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#include "global.hlsli"

#ifndef DISABLE_TSNM
	#include "normal_mapping.hlsli"
#endif // DISABLE_TSNM

//-----------------------------------------------------------------------------
// Constant Buffers
//-----------------------------------------------------------------------------
CBUFFER(Model, SLOT_CBUFFER_MODEL) {
	// TRANSFORM
	// The object-to-world transformation matrix.
	float4x4 g_object_to_world         : packoffset(c0);
	// The object-to-world inverse transpose transformation matrix
	// = The normal-to-world transformation matrix.
	float4x4 g_normal_to_world         : packoffset(c4);
	// The texture transformation matrix.
	float4x4 g_texture_transform       : packoffset(c8);

	// MATERIAL
	// The base color of the material in linear space.
	float4 g_base_color                : packoffset(c12);
	// The (linear) roughness of the material.
	float  g_roughness                 : packoffset(c13.x);
	// The (linear) metalness of the material.
	float  g_metalness                 : packoffset(c13.y);
}

//-----------------------------------------------------------------------------
// SRVs
//-----------------------------------------------------------------------------
#ifndef DISABLE_BASE_COLOR_TEXTURE
	TEXTURE_2D(g_base_color_texture, float4, SLOT_SRV_BASE_COLOR);
#endif // DISABLE_BASE_COLOR_TEXTURE

#ifndef DISABLE_MATERIAL_TEXTURE
	TEXTURE_2D(g_material_texture,   float4, SLOT_SRV_MATERIAL);
#endif // DISABLE_MATERIAL_TEXTURE

#ifndef DISABLE_TSNM
	TEXTURE_2D(g_normal_texture,     float2, SLOT_SRV_NORMAL);
#endif // DISABLE_TSNM

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
	#ifdef DISABLE_BASE_COLOR_TEXTURE
	return g_base_color;
	#else  // DISABLE_BASE_COLOR_TEXTURE
	const float4 base_color = g_base_color_texture.Sample(g_linear_wrap_sampler,
														  tex);
	return g_base_color * base_color;
	#endif // DISABLE_BASE_COLOR_TEXTURE
}

/**
 Returns the parameters of the material.

 @param[in]		tex
				The texture coordinates.
 @return		The parameters [roughness, metalness] of the material.
 */
float2 GetMaterialParameters(float2 tex) {
	// Obtain the material parameters of the material.
	#ifdef DISABLE_MATERIAL_TEXTURE
	return float2(g_roughness, g_metalness);
	#else  // DISABLE_MATERIAL_TEXTURE
	const float2 material = g_material_texture.Sample(g_linear_wrap_sampler, 
													  tex).xy;
	return float2(g_roughness, g_metalness) * material;
	#endif // DISABLE_MATERIAL_TEXTURE
}

/**
 Returns the surface normal at the given surface position.

 @param[in]		p
				The surface position expressed in world space.
 @param[in]		n
				The (unperturbed) surface normal expressed in world space.
 @param[in]		tex
				The texture coordinates.
 @return		The (perturbed) surface normal expressed in world space.
 */
float3 GetNormal(float3 p, float3 n, float2 tex) {
	// Obtain the normal expressed in world space.
	#ifdef DISABLE_TSNM
	return normalize(n);
	#else  // DISABLE_TSNM
	// Obtain the normal expressed in tangent space.
	const float3 n_tangent = UnpackNormal(
		g_normal_texture.Sample(g_linear_wrap_sampler, tex));
	// Perturb the normal expressed in world space.
	return PerturbNormal(p, normalize(n), tex, n_tangent);
	#endif // DISABLE_TSNM
}