#ifndef MAGE_HEADER_MATH
#define MAGE_HEADER_MATH

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------

/**
 Returns the maximum component value of the given value.

 @param[in]		v
				The value.
 @return		The maximum component value of the given value.
 */
float Max(float2 v) {
	return max(v.x, v.y);
}

/**
 Returns the maximum component value of the given value.

 @param[in]		v
				The value.
 @return		The maximum component value of the given value.
 */
float Max(float3 v) {
	return max(v.x, max(v.y, v.z));
}

/**
 Returns the maximum component value of the given value.

 @param[in]		v
				The value.
 @return		The maximum component value of the given value.
 */
float Max(float4 v) {
	return max(max(v.x, v.y), max(v.z, v.w));
}

/**
 Returns the minimum component value of the given value.

 @param[in]		v
				The value.
 @return		The minimum component value of the given value.
 */
float Min(float2 v) {
	return min(v.x, v.y);
}

/**
 Returns the minimum component value of the given value.

 @param[in]		v
				The value.
 @return		The minimum component value of the given value.
 */
float Min(float3 v) {
	return min(v.x, min(v.y, v.z));
}

/**
 Returns the minimum component value of the given value.

 @param[in]		v
				The value.
 @return		The minimum component value of the given value.
 */
float Min(float4 v) {
	return min(min(v.x, v.y), min(v.z, v.w));
}

/**
 Converts the given unsigned normalized value ([0,1] range) 
 to a signed normalized value ([-1,1] range).

 @pre			The given value is an unsigned normalized value 
				([0,1] range).
 @param[in]		v
				The unsigned normalized value ([0,1] range).
 @return		The signed normalized value ([-1,1] range).
 */
float UNORMtoSNORM(float v) {
	return 2.0f * v - 1.0f;
}

/**
 Converts the given unsigned normalized value ([0,1] range) 
 to a signed normalized value ([-1,1] range).

 @pre			The given value is an unsigned normalized value 
				([0,1] range).
 @param[in]		v
				The unsigned normalized value ([0,1] range).
 @return		The signed normalized value ([-1,1] range).
 */
float2 UNORMtoSNORM(float2 v) {
	return 2.0f * v - 1.0f;
}

/**
 Converts the given unsigned normalized value ([0,1] range) 
 to a signed normalized value ([-1,1] range).

 @pre			The given value is an unsigned normalized value 
				([0,1] range).
 @param[in]		v
				The unsigned normalized value ([0,1] range).
 @return		The signed normalized value ([-1,1] range).
 */
float3 UNORMtoSNORM(float3 v) {
	return 2.0f * v - 1.0f;
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
float4 UNORMtoSNORM(float4 v) {
	return 2.0f * v - 1.0f;
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
float SNORMtoUNORM(float v) {
	return 0.5f * v + 0.5f;
}

/**
 Converts the given signed normalized value ([-1,1] range) 
 to an unsigned normalized value ([0,1] range).

 @pre			The given value is a signed normalized value 
				([-1,1] range).
 @param[in]		v
				The signed normalized value ([-1,1] range).
 @return		The unsigned normalized value ([0,1] range).
 */
float2 SNORMtoUNORM(float2 v) {
	return 0.5f * v + 0.5f;
}

/**
 Converts the given signed normalized value ([-1,1] range) 
 to an unsigned normalized value ([0,1] range).

 @pre			The given value is a signed normalized value 
				([-1,1] range).
 @param[in]		v
				The signed normalized value ([-1,1] range).
 @return		The unsigned normalized value ([0,1] range).
 */
float3 SNORMtoUNORM(float3 v) {
	return 0.5f * v + 0.5f;
}

/**
 Converts the given signed normalized value ([-1,1] range) 
 to an unsigned normalized value ([0,1] range).

 @pre			The given value is a signed normalized value 
				([-1,1] range).
 @param[in]		v
				The signed normalized value ([-1,1] range).
 @return		The unsigned normalized value ([0,1] range).
 */
float4 SNORMtoUNORM(float4 v) {
	return 0.5f * v + 0.5f;
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
 Converts the given (linear) view z-coordinate to 
 the (non-linear) NDC z-coordinate.

 @param[in]		p_view_z
				The (linear) view z-coordinate.
 @param[in]		The projection values 
				[view_projection22, view_projection32].
 @return		The (non-linear) NDC z-coordinate.
 */
float ViewZtoNDCZ(float p_view_z, float2 projection_values) {
	return projection_values.x + projection_values.y / p_view_z;
}

/**
 Converts the given (non-linear) NDC z-coordinate to 
 the (linear) view z-coordinate.

 @param[in]		p_ndc_z
				The (non-linear) NDC z-coordinate.
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
 Converts the given NDC coordinates to UV coordinates.

 @param[in]		p_ndc_xy
				The NDC x and y coordinate.
 @return		The UV coordinates.
 */
float2 NDCtoUV(float2 p_ndc_xy) {
	// x: [-1,1] -> [0,1]
	// y: [-1,1] -> [1,0]
	return float2(0.5f, -0.5f) * p_ndc_xy + 0.5f;
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