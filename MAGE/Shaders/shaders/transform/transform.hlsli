#ifndef MAGE_HEADER_TRANSFORM
#define MAGE_HEADER_TRANSFORM

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#include "structures.hlsli"

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions 
//-----------------------------------------------------------------------------

/**
 Transforms the given position from object to projection space.

 @param[in]		p_object
				The position expressed in object space. 
 @param[in]		object_to_world
				The object-to-world transformation matrix.
 @param[in]		world_to_view
				The world-to-view transformation matrix.
 @param[in]		view_to_projection
				The view-to-projection transformation matrix.
 @return		The position expressed in projection space. 
 */
float4 Transform(float3 p_object,
				 float4x4 object_to_world,
				 float4x4 world_to_view,
				 float4x4 view_to_projection) {

	// The same transform sequence is used to eliminate Z-fighting.
	const float3 p_world = mul(float4(p_object, 1.0f), object_to_world).xyz;
	const float3 p_view  = mul(float4(p_world,  1.0f), world_to_view).xyz;
	const float4 p_proj  = mul(float4(p_view,   1.0f), view_to_projection);
	
	return p_proj;
}

/**
 Transforms the given texture coordinates.

 @param[in]		tex
				The texture coordinates.
 @param[in]		texture_transform
				The texture transformation matrix.
 @return		The transformed texture coordinates.
 */
float2 Transform(float2 tex,
				 float4x4 texture_transform) {

	return mul(float4(tex, 0.0f, 1.0f), texture_transform).xy;
}

/**
 Transforms the given vertex input structure.

 @param[in]		input
				The vertex input structure.
 @param[in]		object_to_world
				The object-to-world transformation matrix.
 @param[in]		world_to_view
				The world-to-view transformation matrix.
 @param[in]		view_to_projection
				The view-to-projection transformation matrix.
 @param[in]		normal_to_world
				The normal-to-world transformation matrix.
 @param[in]		texture_transform
				The texture transformation matrix.
 @return		The pixel shader input structure. 
 */
PSInputPositionNormalTexture Transform(VSInputPositionNormalTexture input, 
									   float4x4 object_to_world, 
									   float4x4 world_to_view, 
									   float4x4 view_to_projection, 
									   float3x3 normal_to_world, 
									   float4x4 texture_transform) {
	
	PSInputPositionNormalTexture output;
	
	output.p_world      = mul(float4(input.p, 1.0f), object_to_world).xyz;
	const float3 p_view = mul(float4(p_world, 1.0f), world_to_view).xyz;
	output.p            = mul(float4(p_view,  1.0f), view_to_projection);
	output.n_world      = normalize(mul(input.n, normal_to_world));
	output.tex_material = Transform(input.tex, texture_transform);
	output.tex_geometry = input.tex;

	return output;
}

/**
 Transforms the given vertex input structure.

 @param[in]		input
				The vertex input structure.
 @param[in]		object_to_world
				The object-to-world transformation matrix.
 @param[in]		world_to_view
				The world-to-view transformation matrix.
 @param[in]		view_to_projection
				The view-to-projection transformation matrix.
 @param[in]		normal_to_world
				The normal-to-world transformation matrix.
 @param[in]		texture_transform
				The texture transformation matrix.
 @return		The geometry shader input structure. 
 */
GSInputPositionNormalTexture Transform(VSInputPositionNormalTexture input, 
									   float4x4 object_to_world, 
									   float3x3 normal_to_world,
									   float4x4 texture_transform) {

	GSInputPositionNormalTexture output;
	
	output.p_world      = mul(float4(input.p, 1.0f), object_to_world).xyz;
	output.n_world      = normalize(mul(input.n, normal_to_world));
	output.tex_material = Transform(input.tex, texture_transform);
	output.tex_geometry = input.tex;

	return output;
}

#endif // MAGE_HEADER_TRANSFORM