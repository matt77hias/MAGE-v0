#ifndef MAGE_HEADER_MATH
#define MAGE_HEADER_MATH

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------

/**
 Converts the given normal from the [0,1] range to the [-1,1] range.

 @pre			The given normal is in the [0,1] range.
 @param[in]		n
				The normal in the [0,1] range to convert.
 @return		The converted normal in the [-1,1] range.
 @note			If the given normal was normalized before packing,
				the converted normal will be normalized after unpacking.
 */
float3 UnpackNormal(float3 n) {
	return 2.0f * n - 1.0f;
}

/**
 Converts the given normal from the [-1,1] range to the [0,1] range.

 @pre			The given normal is in the [-1,1] range.
 @param[in]		n
				The normal in the [-1,1] range to convert.
 @return		The converted normal in the [0,1] range.
 */
float3 PackNormal(float3 n) {
	return 0.5f * n + 0.5f;
}

/**
 Converts the given (non-linear) NDC z-coordinate to 
 the (linear) view z-coordinate.

 @param[in]		p_ndc_z
				The NDC z-coordinate.
 @param[in]		The projection values 
				[view_projection32, -view_projection22].
 @return		The (linear) view z-coordinate.
 */
float NDCZtoViewZ(float p_ndc_z, float2 projection_values) {
	return projection_values.x / (p_ndc_z + projection_values.y);
}

/**
 Converts the given NDC coordinates to view coordinates.

 @param[in]		p_ndc
				The NDC coordinates.
 @param[in]		The projection values 
				[1/view_projection00, 1/view_projection11, 
				view_projection32, -view_projection22].
 @return		The view coordinates.
 */
float3 NDCtoView(float3 p_ndc, float4 projection_values) {
	const float p_view_z = NDCZtoViewZ(p_ndc.z, projection_values.zw);
	return float3(p_ndc.xy * projection_values.xy, 1.0f) * p_view_z;
}

#endif //MAGE_HEADER_MATH