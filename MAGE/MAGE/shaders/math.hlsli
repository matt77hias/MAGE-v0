#ifndef MAGE_HEADER_MATH
#define MAGE_HEADER_MATH

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions: Constants
//-----------------------------------------------------------------------------

/**
 The constant value pi.
 */
static const float g_pi = 3.141592654f;

/**
 The constant value 2 pi.
 */
static const float g_2pi = 6.283185307f;

/**
 The constant value 1/pi.
 */
static const float g_inv_pi = 0.318309886f;

/**
 The constant value 1/(2 pi).
 */
static const float g_inv_2pi = 0.159154943f;

/**
 The constant value pi/2.
 */
static const float g_pi_inv_2 = 1.570796327f;

/**
 The constant value pi/4.
 */
static const float g_pi_inv_4 = 0.785398163f;

/**
 The constant value sqrt(2/pi).
 */
static const float g_sqrt_2_inv_pi = 0.7978845608f;

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions: HasNaNs
//-----------------------------------------------------------------------------

/**
 Checks if the given vector contains NANs or QNANs.

 @param[in]		v
				The vector.
 @return		@c true if the given vector contains at least one NAN or QNAN.
				@c false otherwise.
 */
bool HasNaNs(float2 v) {
	const bool2 result = isnan(v);
	return result.x && result.y;
}

/**
 Checks if the given vector contains NANs or QNANs.

 @param[in]		v
				The vector.
 @return		@c true if the given vector contains at least one NAN or QNAN.
				@c false otherwise.
 */
bool HasNaNs(float3 v) {
	const bool3 result = isnan(v);
	return result.x && result.y && result.z;
}

/**
 Checks if the given vector contains NANs or QNANs.

 @param[in]		v
				The vector.
 @return		@c true if the given vector contains at least one NAN or QNAN.
				@c false otherwise.
 */
bool HasNaNs(float4 v) {
	const bool4 result = isnan(v);
	return result.x && result.y && result.z && result.w;
}

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions: HasInfs
//-----------------------------------------------------------------------------

/**
 Checks if the given vector contains infinite components.

 @param[in]		v
				The vector.
 @return		@c true if the given vector contains at least one infinite 
				component. @c false otherwise.
 */
bool HasInfs(float2 v) {
	const bool2 result = isinf(v);
	return result.x && result.y;
}

/**
 Checks if the given vector contains infinite components.

 @param[in]		v
				The vector.
 @return		@c true if the given vector contains at least one infinite 
				component. @c false otherwise.
 */
bool HasInfs(float3 v) {
	const bool3 result = isinf(v);
	return result.x && result.y && result.z;
}

/**
 Checks if the given vector contains infinite components.

 @param[in]		v
				The vector.
 @return		@c true if the given vector contains at least one infinite 
				component. @c false otherwise.
 */
bool HasInfs(float4 v) {
	const bool4 result = isinf(v);
	return result.x && result.y && result.z && result.w;
}

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions: sqr
//-----------------------------------------------------------------------------

/**
 Calculates the square of the given value.

 @param[in]		v
				The value.
 @return		The square of the given value.
 */
float sqr(float v) {
	return v * v;
}

/**
 Calculates the square of the given value.

 @param[in]		v
				The value.
 @return		The square of the given value.
 */
float2 sqr(float2 v) {
	return v * v;
}

/**
 Calculates the square of the given value.

 @param[in]		v
				The value.
 @return		The square of the given value.
 */
float3 sqr(float3 v) {
	return v * v;
}

/**
 Calculates the square of the given value.

 @param[in]		v
				The value.
 @return		The square of the given value.
 */
float4 sqr(float4 v) {
	return v * v;
}

/**
 Calculates the square of the given value.

 @param[in]		v
				The value.
 @return		The square of the given value.
 */
uint sqr(uint v) {
	return v * v;
}

/**
 Calculates the square of the given value.

 @param[in]		v
				The value.
 @return		The square of the given value.
 */
uint2 sqr(uint2 v) {
	return v * v;
}

/**
 Calculates the square of the given value.

 @param[in]		v
				The value.
 @return		The square of the given value.
 */
uint3 sqr(uint3 v) {
	return v * v;
}

/**
 Calculates the square of the given value.

 @param[in]		v
				The value.
 @return		The square of the given value.
 */
uint4 sqr(uint4 v) {
	return v * v;
}

/**
 Calculates the square of the given value.

 @param[in]		v
				The value.
 @return		The square of the given value.
 */
int sqr(int v) {
	return v * v;
}

/**
 Calculates the square of the given value.

 @param[in]		v
				The value.
 @return		The square of the given value.
 */
int2 sqr(int2 v) {
	return v * v;
}

/**
 Calculates the square of the given value.

 @param[in]		v
				The value.
 @return		The square of the given value.
 */
int3 sqr(int3 v) {
	return v * v;
}

/**
 Calculates the square of the given value.

 @param[in]		v
				The value.
 @return		The square of the given value.
 */
int4 sqr(int4 v) {
	return v * v;
}

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions: Max
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
 Returns the maximum component value of the given value.

 @param[in]		v
				The value.
 @return		The maximum component value of the given value.
 */
int Max(int2 v) {
	return max(v.x, v.y);
}

/**
 Returns the maximum component value of the given value.

 @param[in]		v
				The value.
 @return		The maximum component value of the given value.
 */
int Max(int3 v) {
	return max(v.x, max(v.y, v.z));
}

/**
 Returns the maximum component value of the given value.

 @param[in]		v
				The value.
 @return		The maximum component value of the given value.
 */
int Max(int4 v) {
	return max(max(v.x, v.y), max(v.z, v.w));
}

/**
 Returns the maximum component value of the given value.

 @param[in]		v
				The value.
 @return		The maximum component value of the given value.
 */
uint Max(uint2 v) {
	return max(v.x, v.y);
}

/**
 Returns the maximum component value of the given value.

 @param[in]		v
				The value.
 @return		The maximum component value of the given value.
 */
uint Max(uint3 v) {
	return max(v.x, max(v.y, v.z));
}

/**
 Returns the maximum component value of the given value.

 @param[in]		v
				The value.
 @return		The maximum component value of the given value.
 */
uint Max(uint4 v) {
	return max(max(v.x, v.y), max(v.z, v.w));
}

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions: Min
//-----------------------------------------------------------------------------

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
 Returns the minimum component value of the given value.

 @param[in]		v
				The value.
 @return		The minimum component value of the given value.
 */
int Min(int2 v) {
	return min(v.x, v.y);
}

/**
 Returns the minimum component value of the given value.

 @param[in]		v
				The value.
 @return		The minimum component value of the given value.
 */
int Min(int3 v) {
	return min(v.x, min(v.y, v.z));
}

/**
 Returns the minimum component value of the given value.

 @param[in]		v
				The value.
 @return		The minimum component value of the given value.
 */
int Min(int4 v) {
	return min(min(v.x, v.y), min(v.z, v.w));
}

/**
 Returns the minimum component value of the given value.

 @param[in]		v
				The value.
 @return		The minimum component value of the given value.
 */
uint Min(uint2 v) {
	return min(v.x, v.y);
}

/**
 Returns the minimum component value of the given value.

 @param[in]		v
				The value.
 @return		The minimum component value of the given value.
 */
uint Min(uint3 v) {
	return min(v.x, min(v.y, v.z));
}

/**
 Returns the minimum component value of the given value.

 @param[in]		v
				The value.
 @return		The minimum component value of the given value.
 */
uint Min(uint4 v) {
	return min(min(v.x, v.y), min(v.z, v.w));
}

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions: UNORMtoSNORM
//-----------------------------------------------------------------------------

/**
 Converts the given unsigned normalized value ([0,1] range) to a signed 
 normalized value ([-1,1] range).

 @pre			The given value is an unsigned normalized value ([0,1] range).
 @param[in]		v
				The unsigned normalized value ([0,1] range).
 @return		The signed normalized value ([-1,1] range).
 */
float UNORMtoSNORM(float v) {
	return 2.0f * v - 1.0f;
}

/**
 Converts the given unsigned normalized value ([0,1] range) to a signed 
 normalized value ([-1,1] range).

 @pre			The given value is an unsigned normalized value ([0,1] range).
 @param[in]		v
				The unsigned normalized value ([0,1] range).
 @return		The signed normalized value ([-1,1] range).
 */
float2 UNORMtoSNORM(float2 v) {
	return 2.0f * v - 1.0f;
}

/**
 Converts the given unsigned normalized value ([0,1] range) to a signed 
 normalized value ([-1,1] range).

 @pre			The given value is an unsigned normalized value ([0,1] range).
 @param[in]		v
				The unsigned normalized value ([0,1] range).
 @return		The signed normalized value ([-1,1] range).
 */
float3 UNORMtoSNORM(float3 v) {
	return 2.0f * v - 1.0f;
}

/**
 Converts the given unsigned normalized value ([0,1] range) to a signed 
 normalized value ([-1,1] range).

 @pre			The given value is an unsigned normalized value ([0,1] range).
 @param[in]		x
				The unsigned normalized value ([0,1] range).
 @return		The signed normalized value ([-1,1] range).
 */
float4 UNORMtoSNORM(float4 v) {
	return 2.0f * v - 1.0f;
}

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions: SNORMtoUNORM
//-----------------------------------------------------------------------------

/**
 Converts the given signed normalized value ([-1,1] range) to an unsigned 
 normalized value ([0,1] range).

 @pre			The given value is a signed normalized value ([-1,1] range).
 @param[in]		x
				The signed normalized value ([-1,1] range).
 @return		The unsigned normalized value ([0,1] range).
 */
float SNORMtoUNORM(float v) {
	return 0.5f * v + 0.5f;
}

/**
 Converts the given signed normalized value ([-1,1] range) to an unsigned 
 normalized value ([0,1] range).

 @pre			The given value is a signed normalized value ([-1,1] range).
 @param[in]		v
				The signed normalized value ([-1,1] range).
 @return		The unsigned normalized value ([0,1] range).
 */
float2 SNORMtoUNORM(float2 v) {
	return 0.5f * v + 0.5f;
}

/**
 Converts the given signed normalized value ([-1,1] range) to an unsigned 
 normalized value ([0,1] range).

 @pre			The given value is a signed normalized value ([-1,1] range).
 @param[in]		v
				The signed normalized value ([-1,1] range).
 @return		The unsigned normalized value ([0,1] range).
 */
float3 SNORMtoUNORM(float3 v) {
	return 0.5f * v + 0.5f;
}

/**
 Converts the given signed normalized value ([-1,1] range) to an unsigned 
 normalized value ([0,1] range).

 @pre			The given value is a signed normalized value ([-1,1] range).
 @param[in]		v
				The signed normalized value ([-1,1] range).
 @return		The unsigned normalized value ([0,1] range).
 */
float4 SNORMtoUNORM(float4 v) {
	return 0.5f * v + 0.5f;
}

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions: Normal Utilities
//-----------------------------------------------------------------------------

/**
 Converts the given normal from the [0,1] range to the [-1,1] range.

 The z component will be positive and will be calculated from the x and y 
 components.

 @pre			The given normal is in the [0,1] range.
 @param[in]		n
				The normal in the [0,1] range to convert.
 @return		The converted normal in the [-1,1] range.
 */
float3 UnpackNormal(float2 n) {
	const float2 c_xy = UNORMtoSNORM(n);
	const float  c_z  = sqrt(1.0f - dot(c_xy, c_xy));
	return float3(c_xy, c_z);
}

/**
 Converts the given normal from the [0,1] range to the [-1,1] range.

 @pre			The given normal is in the [0,1] range.
 @param[in]		n
				The normal in the [0,1] range to convert.
 @return		The converted normal in the [-1,1] range.
 @post			If the given normal was normalized before packing, the converted 
				normal will be normalized after unpacking.
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

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions: Transform Utilities
//-----------------------------------------------------------------------------

/**
 Converts the given (linear) view z-coordinate to the (non-linear) NDC 
 z-coordinate.

 @param[in]		p_view_z
				The (linear) view z-coordinate.
 @param[in]		projection_values
				The projection values [view_projection22, view_projection32].
 @return		The (non-linear) NDC z-coordinate.
 */
float ViewZtoNDCZ(float p_view_z, float2 projection_values) {
	return projection_values.x + projection_values.y / p_view_z;
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
 Converts the given normalized dispatch thread id to NDC coordinates.

 @pre			@a normalized_id is normalized (i.e. in the [0,1] range).
 @param[in]		normalized_id
				The normalized dispatch thread id.
 @return		The NDC coordinates.
 */
float2 NormalizedDispatchThreadIDtoNDC(float2 normalized_id) {
	// x: [0,1] -> [-1,1]
	// y: [0,1] -> [1,-1]
	return float2(2.0f, -2.0f) * normalized_id + float2(-1.0f, 1.0f);
}

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions: Gamma Utilities
//-----------------------------------------------------------------------------

/**
 Converts the given spectrum from linear space to gamma space.

 @pre			All components of @a rgb must be non-negative.
 @param[in]		rgb
				The RGB spectrum in linear space.
 @param[in]		inv_gamma
				The inverse of the gamma exponent.
 @return		The RGB spectrum in gamma space.
 */
float3 LinearToGamma(float3 rgb, float inv_gamma) {
	return pow(abs(rgb), inv_gamma);
}

/**
 Converts the given spectrum from linear space to gamma space.

 @pre			All components of @a rgba must be non-negative.
 @param[in]		rgba
				The RGBA spectrum in linear space.
 @param[in]		inv_gamma
				The inverse of the gamma exponent.
 @return		The RGBA spectrum in gamma space.
 @note			The alpha channel of the given RGBA spectrum is preserved.
 */
float4 LinearToGamma(float4 rgba, float inv_gamma) {
	return float4(LinearToGamma(rgba.xyz, inv_gamma), rgba.w);
}

/**
 Converts the given spectrum from gamma space to linear space.

 @pre			All components of @a rgb must be non-negative.
 @param[in]		rgba
				The RGB spectrum in gamma space.
 @param[in]		inv_gamma
				The gamma exponent.
 @return		The RGB spectrum in linear space.
 */
float3 GammaToLinear(float3 rgb, float gamma) {
	return pow(abs(rgb), gamma);
}

/**
 Converts the given spectrum from gamma space to linear space.

 @pre			All components of @a rgba must be non-negative.
 @param[in]		rgba
				The RGBA spectrum in linear space.
 @param[in]		inv_gamma
				The gamma exponent.
 @return		The RGBA spectrum in gamma space.
 @note			The alpha channel of the given RGBA spectrum is preserved.
 */
float4 GammaToLinear(float4 rgba, float gamma) {
	return float4(GammaToLinear(rgba.xyz, gamma), rgba.w);
}

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions: Indexing Utilities
//-----------------------------------------------------------------------------

/**
 Flattens the given index.

 @param[in]		index
				The 2D index.
 @param[in]		count
				The number of y elements per x element.
 @return		The flattened 1D index corresponding to the given 2D index
				using x->y ordering.
 */
uint FlattenIndex(uint2 index, uint count) {
	return index.x * count + index.y;
}

/**
 Flattens the given index.

 @param[in]		index
				The 3D index.
 @param[in]		count
				The number of y elements per x element.
				The number of z elements per y element.
 @return		The flattened 1D index corresponding to the given 3D index
				using x->y->z ordering.
 */
uint FlattenIndex(uint3 index, uint2 count) {
	return FlattenIndex(index.xy, count.x) * count.y + index.z;
}

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions: Trigonometric Utilities
//-----------------------------------------------------------------------------

/**
 Calculates the squared tangent from the given squared cosine.

 @param[in]		sqr_cos
				The squared cosine.
 @return		The squared tangent corresponding to the given squared cosine.
 */
float SqrCosToSqrTan(float sqr_cos) {
	return (1.0f - sqr_cos) / sqr_cos;
}

/**
 Calculates the squared tangent from the given squared sine.

 @param[in]		sqr_sin
				The squared sine.
 @return		The squared tangent corresponding to the given squared sine.
 */
float SqrSinToSqrTan(float sqr_sin) {
	return sqr_sin / (1.0f - sqr_sin);
}

#endif //MAGE_HEADER_MATH