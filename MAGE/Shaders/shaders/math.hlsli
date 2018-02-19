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
// Engine Declarations and Definitions: sqr
//-----------------------------------------------------------------------------

/**
 Calculates the square of the given value.

 @param[in]		v
				The value.
 @return		The square of the given value.
 */
half sqr(half v) {
	return v * v;
}

/**
 Calculates the square of the given value.

 @param[in]		v
				The value.
 @return		The square of the given value.
 */
half2 sqr(half2 v) {
	return v * v;
}

/**
 Calculates the square of the given value.

 @param[in]		v
				The value.
 @return		The square of the given value.
 */
half3 sqr(half3 v) {
	return v * v;
}

/**
 Calculates the square of the given value.

 @param[in]		v
				The value.
 @return		The square of the given value.
 */
half4 sqr(half4 v) {
	return v * v;
}

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
double sqr(double v) {
	return v * v;
}

/**
 Calculates the square of the given value.

 @param[in]		v
				The value.
 @return		The square of the given value.
 */
double2 sqr(double2 v) {
	return v * v;
}

/**
 Calculates the square of the given value.

 @param[in]		v
				The value.
 @return		The square of the given value.
 */
double3 sqr(double3 v) {
	return v * v;
}

/**
 Calculates the square of the given value.

 @param[in]		v
				The value.
 @return		The square of the given value.
 */
double4 sqr(double4 v) {
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

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions: Max
//-----------------------------------------------------------------------------

/**
 Returns the maximum component value of the given value.

 @param[in]		v
				The value.
 @return		The maximum component value of the given value.
 */
half Max(half2 v) {
	return max(v.x, v.y);
}

/**
 Returns the maximum component value of the given value.

 @param[in]		v
				The value.
 @return		The maximum component value of the given value.
 */
half Max(half3 v) {
	return max(v.x, max(v.y, v.z));
}

/**
 Returns the maximum component value of the given value.

 @param[in]		v
				The value.
 @return		The maximum component value of the given value.
 */
half Max(half4 v) {
	return max(max(v.x, v.y), max(v.z, v.w));
}

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
double Max(double2 v) {
	return max(v.x, v.y);
}

/**
 Returns the maximum component value of the given value.

 @param[in]		v
				The value.
 @return		The maximum component value of the given value.
 */
double Max(double3 v) {
	return max(v.x, max(v.y, v.z));
}

/**
 Returns the maximum component value of the given value.

 @param[in]		v
				The value.
 @return		The maximum component value of the given value.
 */
double Max(double4 v) {
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
half Min(half2 v) {
	return min(v.x, v.y);
}

/**
 Returns the minimum component value of the given value.

 @param[in]		v
				The value.
 @return		The minimum component value of the given value.
 */
half Min(half3 v) {
	return min(v.x, min(v.y, v.z));
}

/**
 Returns the minimum component value of the given value.

 @param[in]		v
				The value.
 @return		The minimum component value of the given value.
 */
half Min(half4 v) {
	return min(min(v.x, v.y), min(v.z, v.w));
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
 Returns the minimum component value of the given value.

 @param[in]		v
				The value.
 @return		The minimum component value of the given value.
 */
double Min(double2 v) {
	return min(v.x, v.y);
}

/**
 Returns the minimum component value of the given value.

 @param[in]		v
				The value.
 @return		The minimum component value of the given value.
 */
double Min(double3 v) {
	return min(v.x, min(v.y, v.z));
}

/**
 Returns the minimum component value of the given value.

 @param[in]		v
				The value.
 @return		The minimum component value of the given value.
 */
double Min(double4 v) {
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
half UNORMtoSNORM(half v) {
	return 2.0h * v - 1.0h;
}

/**
 Converts the given unsigned normalized value ([0,1] range) to a signed 
 normalized value ([-1,1] range).

 @pre			The given value is an unsigned normalized value ([0,1] range).
 @param[in]		v
				The unsigned normalized value ([0,1] range).
 @return		The signed normalized value ([-1,1] range).
 */
half2 UNORMtoSNORM(half2 v) {
	return 2.0h * v - 1.0h;
}

/**
 Converts the given unsigned normalized value ([0,1] range) to a signed 
 normalized value ([-1,1] range).

 @pre			The given value is an unsigned normalized value ([0,1] range).
 @param[in]		v
				The unsigned normalized value ([0,1] range).
 @return		The signed normalized value ([-1,1] range).
 */
half3 UNORMtoSNORM(half3 v) {
	return 2.0h * v - 1.0h;
}

/**
 Converts the given unsigned normalized value ([0,1] range) to a signed 
 normalized value ([-1,1] range).

 @pre			The given value is an unsigned normalized value ([0,1] range).
 @param[in]		x
				The unsigned normalized value ([0,1] range).
 @return		The signed normalized value ([-1,1] range).
 */
half4 UNORMtoSNORM(half4 v) {
	return 2.0h * v - 1.0h;
}

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

/**
 Converts the given unsigned normalized value ([0,1] range) to a signed 
 normalized value ([-1,1] range).

 @pre			The given value is an unsigned normalized value ([0,1] range).
 @param[in]		v
				The unsigned normalized value ([0,1] range).
 @return		The signed normalized value ([-1,1] range).
 */
double UNORMtoSNORM(double v) {
	return 2.0l * v - 1.0l;
}

/**
 Converts the given unsigned normalized value ([0,1] range) to a signed 
 normalized value ([-1,1] range).

 @pre			The given value is an unsigned normalized value ([0,1] range).
 @param[in]		v
				The unsigned normalized value ([0,1] range).
 @return		The signed normalized value ([-1,1] range).
 */
double2 UNORMtoSNORM(double2 v) {
	return 2.0l * v - 1.0l;
}

/**
 Converts the given unsigned normalized value ([0,1] range) to a signed 
 normalized value ([-1,1] range).

 @pre			The given value is an unsigned normalized value ([0,1] range).
 @param[in]		v
				The unsigned normalized value ([0,1] range).
 @return		The signed normalized value ([-1,1] range).
 */
double3 UNORMtoSNORM(double3 v) {
	return 2.0l * v - 1.0l;
}

/**
 Converts the given unsigned normalized value ([0,1] range) to a signed 
 normalized value ([-1,1] range).

 @pre			The given value is an unsigned normalized value ([0,1] range).
 @param[in]		x
				The unsigned normalized value ([0,1] range).
 @return		The signed normalized value ([-1,1] range).
 */
double4 UNORMtoSNORM(double4 v) {
	return 2.0l * v - 1.0l;
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
half SNORMtoUNORM(half v) {
	return 0.5h * v + 0.5h;
}

/**
 Converts the given signed normalized value ([-1,1] range) to an unsigned 
 normalized value ([0,1] range).

 @pre			The given value is a signed normalized value ([-1,1] range).
 @param[in]		v
				The signed normalized value ([-1,1] range).
 @return		The unsigned normalized value ([0,1] range).
 */
half2 SNORMtoUNORM(half2 v) {
	return 0.5h * v + 0.5h;
}

/**
 Converts the given signed normalized value ([-1,1] range) to an unsigned 
 normalized value ([0,1] range).

 @pre			The given value is a signed normalized value ([-1,1] range).
 @param[in]		v
				The signed normalized value ([-1,1] range).
 @return		The unsigned normalized value ([0,1] range).
 */
half3 SNORMtoUNORM(half3 v) {
	return 0.5h * v + 0.5h;
}

/**
 Converts the given signed normalized value ([-1,1] range) to an unsigned 
 normalized value ([0,1] range).

 @pre			The given value is a signed normalized value ([-1,1] range).
 @param[in]		v
				The signed normalized value ([-1,1] range).
 @return		The unsigned normalized value ([0,1] range).
 */
half4 SNORMtoUNORM(half4 v) {
	return 0.5h * v + 0.5h;
}

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

/**
 Converts the given signed normalized value ([-1,1] range) to an unsigned 
 normalized value ([0,1] range).

 @pre			The given value is a signed normalized value ([-1,1] range).
 @param[in]		x
				The signed normalized value ([-1,1] range).
 @return		The unsigned normalized value ([0,1] range).
 */
double SNORMtoUNORM(double v) {
	return 0.5l * v + 0.5l;
}

/**
 Converts the given signed normalized value ([-1,1] range) to an unsigned 
 normalized value ([0,1] range).

 @pre			The given value is a signed normalized value ([-1,1] range).
 @param[in]		v
				The signed normalized value ([-1,1] range).
 @return		The unsigned normalized value ([0,1] range).
 */
double2 SNORMtoUNORM(double2 v) {
	return 0.5l * v + 0.5l;
}

/**
 Converts the given signed normalized value ([-1,1] range) to an unsigned 
 normalized value ([0,1] range).

 @pre			The given value is a signed normalized value ([-1,1] range).
 @param[in]		v
				The signed normalized value ([-1,1] range).
 @return		The unsigned normalized value ([0,1] range).
 */
double3 SNORMtoUNORM(double3 v) {
	return 0.5l * v + 0.5l;
}

/**
 Converts the given signed normalized value ([-1,1] range) to an unsigned 
 normalized value ([0,1] range).

 @pre			The given value is a signed normalized value ([-1,1] range).
 @param[in]		v
				The signed normalized value ([-1,1] range).
 @return		The unsigned normalized value ([0,1] range).
 */
double4 SNORMtoUNORM(double4 v) {
	return 0.5l * v + 0.5l;
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
 Converts the given (linear) z coordinate expressed in shading space to the 
 corresponding (non-linear) z coordinate expressed in NDC space.

 @param[in]		p_z
				The (linear) z coordinate expressed in shading space.
 @param[in]		proj_values
				The projection values of the shading-to-projection matrix
				[shading_to_projection22, shading_to_projection32].
 @return		The (non-linear) z coordinate expressed in NDC space.
 */
float ShadingZtoNDCZ(float p_z, float2 proj_values) {
	return proj_values.x + proj_values.y / p_z;
}

/**
 Converts the given NDC coordinates to UV coordinates.

 @param[in]		p_ndc_xy
				The NDC x and y coordinate.
 @return		The UV u and v coordinates.
 */
float2 NDCtoUV(float2 p_ndc_xy) {
	// x: [-1,1] -> [0,1]
	// y: [-1,1] -> [1,0]
	return float2(0.5f, -0.5f) * p_ndc_xy + 0.5f;
}

/**
 Converts the given UV coordinates to NDC coordinates.

 @param[in]		uv
				The UV u and v coordinates.
 @return		The NDC x and y coordinate.
 */
float2 UVtoNDC(float2 uv) {
	// x: [0,1] -> [-1,1]
	// y: [0,1] -> [1,-1]
	return float2(2.0f, -2.0f) * uv + float2(-1.0f, 1.0f);
}

/**
 Converts the given display coordinates to UV coordinates.

 @param[in]		p_display
				The display coordinates.
 @param[in]		inv_display_resolution_minus1
				The inverse of the display resolution minus 1 
				[1/(display_resolution.x-1), 1/(display_resolution.y-1)].
 @return		The UV u and v coordinates.
 */
float2 DisplayToUV(float2 p_display, float2 inv_display_resolution_minus1) {
	// x: [0,resolution.x-1] -> [0,1]
	// y: [0,resolution.y-1] -> [0,1]
	return p_display * inv_display_resolution_minus1;
}

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions: Indexing Utilities
//-----------------------------------------------------------------------------

/**
 Flattens the given index.

 @param[in]		index
				The 2D index.
 @param[in]		count
				The number of elements in each dimension.
 @return		The flattened 1D index corresponding to the given 2D index
				using y->x ordering.
 */
uint FlattenIndex(uint2 index, uint2 count) {
	return index.y * count.x + index.x;
}

/**
 Flattens the given index.

 @param[in]		index
				The 3D index.
 @param[in]		count
				The number of elements in each dimension.
 @return		The flattened 1D index corresponding to the given 3D index
				using z->y->x ordering.
 */
uint FlattenIndex(uint3 index, uint3 count) {
	return FlattenIndex(index.xy, count.xy) * count.y + index.z;
}

/**
 Unflattens the given index.

 @param[in]		index
				The flattened 1D index.
 @param[in]		count
				The number of elements in each dimension.
 @return		The 2D index corresponding to the given flattened 1D index
				using y->x ordering.
 */
uint2 UnflattenIndex(uint index, uint2 count) {
	return uint2(index % count.x, index / count.x);
}

/**
 Unflattens the given index.

 @param[in]		index
				The flattened 1D index.
 @param[in]		count
				The number of elements in each dimension.
 @return		The 3D index corresponding to the given flattened 1D index
				using z->y->x ordering.
 */
uint3 UnflattenIndex(uint index, uint3 count) {
	const uint slice_z = count.x * count.y;
	return uint3(UnflattenIndex(index % slice_z, count.xy), index / slice_z);
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