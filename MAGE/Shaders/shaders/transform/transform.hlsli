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
 Transform the given vertex input structure.

 @param[in]		input
				The vertex input structure.
 @param[in]		object_to_view
				The object-to-view transformation matrix.
 @param[in]		view_to_projection
				The view-to-projection transformation matrix.
 @param[in]		normal_to_view
				The normal-to-view transformation matrix.
 @return		The pixel shader input structure. 
 */
PSInputPositionNormalTexture Transform(VSInputPositionNormalTexture input,
	                                   float4x4 object_to_view, 
	                                   float4x4 view_to_projection, 
	                                   float3x3 normal_to_view) {

	PSInputPositionNormalTexture output;
	output.p      = mul(float4(input.p, 1.0f), object_to_view);
	output.p_view = output.p.xyz;
	output.p      = mul(output.p, view_to_projection);
	output.n_view = normalize(mul(input.n, normal_to_view));
	output.tex    = input.tex;
	output.tex2   = input.tex;
	return output;
}

/**
 Transform the given vertex input structure.

 @param[in]		input
				The vertex input structure.
 @param[in]		object_to_view
				The object-to-view transformation matrix.
 @param[in]		view_to_projection
				The view-to-projection transformation matrix.
 @param[in]		normal_to_view
				The normal-to-view transformation matrix.
 @param[in]		texture_transform
				The texture transformation matrix.
 @return		The pixel shader input structure. 
 */
PSInputPositionNormalTexture Transform(VSInputPositionNormalTexture input,
	                                   float4x4 object_to_view, 
	                                   float4x4 view_to_projection, 
	                                   float3x3 normal_to_view, 
	                                   float4x4 texture_transform) {

	PSInputPositionNormalTexture output;
	output.p      = mul(float4(input.p, 1.0f), object_to_view);
	output.p_view = output.p.xyz;
	output.p      = mul(output.p, view_to_projection);
	output.n_view = normalize(mul(input.n, normal_to_view));
	output.tex    = mul(float4(input.tex, 0.0f, 1.0f), texture_transform).xy;
	output.tex2   = input.tex;
	return output;
}

/**
 Transform the given vertex input structure.

 @param[in]		input
				The vertex input structure.
 @param[in]		object_to_view
				The object-to-view transformation matrix.
 @param[in]		normal_to_view
				The normal-to-view transformation matrix.
 @param[in]		texture_transform
				The texture transformation matrix.
 @return		The geometry shader input structure. 
 */
GSInputPositionNormalTexture Transform(VSInputPositionNormalTexture input,
	                                   float4x4 object_to_view, 
	                                   float3x3 normal_to_view, 
	                                   float4x4 texture_transform) {

	GSInputPositionNormalTexture output;
	output.p_view = mul(float4(input.p, 1.0f), object_to_view).xyz;
	output.n_view = normalize(mul(input.n, normal_to_view));
	output.tex    = mul(float4(input.tex, 0.0f, 1.0f), texture_transform).xy;
	output.tex2   = input.tex;
	return output;
}

#endif // MAGE_HEADER_TRANSFORM