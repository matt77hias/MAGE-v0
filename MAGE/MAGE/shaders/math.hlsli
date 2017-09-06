#ifndef MAGE_HEADER_MATH
#define MAGE_HEADER_MATH

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------

/**
 Converts the given unsigned normalized value ([0,1] range) 
 to a signed normalized value ([-1,1] range).

 @pre			The given value is an unsigned normalized value 
				([0,1] range).
 @param[in]		x
				The unsigned normalized value ([0,1] range).
 @return		The signed normalized value ([-1,1] range).
 */
float UNORMtoSNORM(float x) {
	return 2.0f * x - 1.0f;
}

/**
 Converts the given unsigned normalized value ([0,1] range) 
 to a signed normalized value ([-1,1] range).

 @pre			The given value is an unsigned normalized value 
				([0,1] range).
 @param[in]		x
				The unsigned normalized value ([0,1] range).
 @return		The signed normalized value ([-1,1] range).
 */
float2 UNORMtoSNORM(float2 x) {
	return 2.0f * x - 1.0f;
}

/**
 Converts the given unsigned normalized value ([0,1] range) 
 to a signed normalized value ([-1,1] range).

 @pre			The given value is an unsigned normalized value 
				([0,1] range).
 @param[in]		x
				The unsigned normalized value ([0,1] range).
 @return		The signed normalized value ([-1,1] range).
 */
float3 UNORMtoSNORM(float3 x) {
	return 2.0f * x - 1.0f;
}

/**
 Converts the given unsigned normalized value ([0,1] range) 
 to a signed normalized value ([-1,1] range).

 @pre			The given value is an unsigned normalized value 
				([0,1] range).
 @param[in]		x
				The unsigned normalized value ([0,1] range).
 @return		The signed normalized value ([-1,1] range).
 */
float4 UNORMtoSNORM(float4 x) {
	return 2.0f * x - 1.0f;
}

/**
 Converts the given signed normalized value ([-1,1] range) 
 to an unsigned normalized value ([0,1] range).

 @pre			The given value is a signed normalized value 
				([-1,1] range).
 @param[in]		x
				The signed normalized value ([-1,1] range).
 @return		The unsigned normalized value ([0,1] range).
 */
float SNORMtoUNORM(float x) {
	return 0.5f * x + 0.5f;
}

/**
 Converts the given signed normalized value ([-1,1] range) 
 to an unsigned normalized value ([0,1] range).

 @pre			The given value is a signed normalized value 
				([-1,1] range).
 @param[in]		x
				The signed normalized value ([-1,1] range).
 @return		The unsigned normalized value ([0,1] range).
 */
float2 SNORMtoUNORM(float2 x) {
	return 0.5f * x + 0.5f;
}

/**
 Converts the given signed normalized value ([-1,1] range) 
 to an unsigned normalized value ([0,1] range).

 @pre			The given value is a signed normalized value 
				([-1,1] range).
 @param[in]		x
				The signed normalized value ([-1,1] range).
 @return		The unsigned normalized value ([0,1] range).
 */
float3 SNORMtoUNORM(float3 x) {
	return 0.5f * x + 0.5f;
}

/**
 Converts the given signed normalized value ([-1,1] range) 
 to an unsigned normalized value ([0,1] range).

 @pre			The given value is a signed normalized value 
				([-1,1] range).
 @param[in]		x
				The signed normalized value ([-1,1] range).
 @return		The unsigned normalized value ([0,1] range).
 */
float4 SNORMtoUNORM(float4 x) {
	return 0.5f * x + 0.5f;
}

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
	return UNORMtoSNORM(n);
}

/**
 Converts the given normal from the [-1,1] range to the [0,1] range.

 @pre			The given normal is in the [-1,1] range.
 @param[in]		n
				The normal in the [-1,1] range to convert.
 @return		The converted normal in the [0,1] range.
 */
float3 PackNormal(float3 n) {
	return SNORMtoUNORM(n);
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

/**
 Converts the given normalized dispatch thread id 
 to NDC coordinates.

 @pre			@a normalized_id is normalized 
				(i.e. in the [0,1] range).
 @param[in]		normalized_id
				The normalized dispatch thread id.
 @return		The NDC coordinates.
 */
float2 DispatchThreadIDtoNDC(float2 normalized_id) {
	// x: [0,1] -> [-1,1]
	// y: [0,1] -> [1,-1]
	return float2(2.0f, -2.0f) * normalized_id + float2(-1.0f, 1.0f);
}

#endif //MAGE_HEADER_MATH