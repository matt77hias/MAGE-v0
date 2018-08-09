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
	return Max(max(v.xy, v.zw));
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
	return Max(max(v.xy, v.zw));
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
	return Max(max(v.xy, v.zw));
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
	return Max(max(v.xy, v.zw));
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
	return Max(max(v.xy, v.zw));
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
	return Min(min(v.xy, v.zw));
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
	return Min(min(v.xy, v.zw));
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
	return Min(min(v.xy, v.zw));
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
	return Min(min(v.xy, v.zw));
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
	return Min(min(v.xy, v.zw));
}

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions: UNormToSNorm
//-----------------------------------------------------------------------------

/**
 Converts the given unsigned normalized value ([0,1] range) to a signed 
 normalized value ([-1,1] range).

 @pre			The given value is an unsigned normalized value ([0,1] range).
 @param[in]		v_unorm
				The unsigned normalized value ([0,1] range).
 @return		The signed normalized value ([-1,1] range).
 */
half UNormToSNorm(half v_unorm) {
	return 2.0h * v_unorm - 1.0h;
}

/**
 Converts the given unsigned normalized value ([0,1] range) to a signed 
 normalized value ([-1,1] range).

 @pre			The given value is an unsigned normalized value ([0,1] range).
 @param[in]		v_unorm
				The unsigned normalized value ([0,1] range).
 @return		The signed normalized value ([-1,1] range).
 */
half2 UNormToSNorm(half2 v_unorm) {
	return 2.0h * v_unorm - 1.0h;
}

/**
 Converts the given unsigned normalized value ([0,1] range) to a signed 
 normalized value ([-1,1] range).

 @pre			The given value is an unsigned normalized value ([0,1] range).
 @param[in]		v_unorm
				The unsigned normalized value ([0,1] range).
 @return		The signed normalized value ([-1,1] range).
 */
half3 UNormToSNorm(half3 v_unorm) {
	return 2.0h * v_unorm - 1.0h;
}

/**
 Converts the given unsigned normalized value ([0,1] range) to a signed 
 normalized value ([-1,1] range).

 @pre			The given value is an unsigned normalized value ([0,1] range).
 @param[in]		v_unorm
				The unsigned normalized value ([0,1] range).
 @return		The signed normalized value ([-1,1] range).
 */
half4 UNormToSNorm(half4 v_unorm) {
	return 2.0h * v_unorm - 1.0h;
}

/**
 Converts the given unsigned normalized value ([0,1] range) to a signed 
 normalized value ([-1,1] range).

 @pre			The given value is an unsigned normalized value ([0,1] range).
 @param[in]		v_unorm
				The unsigned normalized value ([0,1] range).
 @return		The signed normalized value ([-1,1] range).
 */
float UNormToSNorm(float v_unorm) {
	return 2.0f * v_unorm - 1.0f;
}

/**
 Converts the given unsigned normalized value ([0,1] range) to a signed 
 normalized value ([-1,1] range).

 @pre			The given value is an unsigned normalized value ([0,1] range).
 @param[in]		v_unorm
				The unsigned normalized value ([0,1] range).
 @return		The signed normalized value ([-1,1] range).
 */
float2 UNormToSNorm(float2 v_unorm) {
	return 2.0f * v_unorm - 1.0f;
}

/**
 Converts the given unsigned normalized value ([0,1] range) to a signed 
 normalized value ([-1,1] range).

 @pre			The given value is an unsigned normalized value ([0,1] range).
 @param[in]		v_unorm
				The unsigned normalized value ([0,1] range).
 @return		The signed normalized value ([-1,1] range).
 */
float3 UNormToSNorm(float3 v_unorm) {
	return 2.0f * v_unorm - 1.0f;
}

/**
 Converts the given unsigned normalized value ([0,1] range) to a signed 
 normalized value ([-1,1] range).

 @pre			The given value is an unsigned normalized value ([0,1] range).
 @param[in]		v_unorm
				The unsigned normalized value ([0,1] range).
 @return		The signed normalized value ([-1,1] range).
 */
float4 UNormToSNorm(float4 v_unorm) {
	return 2.0f * v_unorm - 1.0f;
}

/**
 Converts the given unsigned normalized value ([0,1] range) to a signed 
 normalized value ([-1,1] range).

 @pre			The given value is an unsigned normalized value ([0,1] range).
 @param[in]		v_unorm
				The unsigned normalized value ([0,1] range).
 @return		The signed normalized value ([-1,1] range).
 */
double UNormToSNorm(double v_unorm) {
	return 2.0l * v_unorm - 1.0l;
}

/**
 Converts the given unsigned normalized value ([0,1] range) to a signed 
 normalized value ([-1,1] range).

 @pre			The given value is an unsigned normalized value ([0,1] range).
 @param[in]		v_unorm
				The unsigned normalized value ([0,1] range).
 @return		The signed normalized value ([-1,1] range).
 */
double2 UNormToSNorm(double2 v_unorm) {
	return 2.0l * v_unorm - 1.0l;
}

/**
 Converts the given unsigned normalized value ([0,1] range) to a signed 
 normalized value ([-1,1] range).

 @pre			The given value is an unsigned normalized value ([0,1] range).
 @param[in]		v_unorm
				The unsigned normalized value ([0,1] range).
 @return		The signed normalized value ([-1,1] range).
 */
double3 UNormToSNorm(double3 v_unorm) {
	return 2.0l * v_unorm - 1.0l;
}

/**
 Converts the given unsigned normalized value ([0,1] range) to a signed 
 normalized value ([-1,1] range).

 @pre			The given value is an unsigned normalized value ([0,1] range).
 @param[in]		v_unorm
				The unsigned normalized value ([0,1] range).
 @return		The signed normalized value ([-1,1] range).
 */
double4 UNormToSNorm(double4 v_unorm) {
	return 2.0l * v_unorm - 1.0l;
}

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions: SNormToUNorm
//-----------------------------------------------------------------------------

/**
 Converts the given signed normalized value ([-1,1] range) to an unsigned 
 normalized value ([0,1] range).

 @pre			The given value is a signed normalized value ([-1,1] range).
 @param[in]		v_snorm
				The signed normalized value ([-1,1] range).
 @return		The unsigned normalized value ([0,1] range).
 */
half SNormToUNorm(half v_snorm) {
	return 0.5h * v_snorm + 0.5h;
}

/**
 Converts the given signed normalized value ([-1,1] range) to an unsigned 
 normalized value ([0,1] range).

 @pre			The given value is a signed normalized value ([-1,1] range).
 @param[in]		v_snorm
				The signed normalized value ([-1,1] range).
 @return		The unsigned normalized value ([0,1] range).
 */
half2 SNormToUNorm(half2 v_snorm) {
	return 0.5h * v_snorm + 0.5h;
}

/**
 Converts the given signed normalized value ([-1,1] range) to an unsigned 
 normalized value ([0,1] range).

 @pre			The given value is a signed normalized value ([-1,1] range).
 @param[in]		v_snorm
				The signed normalized value ([-1,1] range).
 @return		The unsigned normalized value ([0,1] range).
 */
half3 SNormToUNorm(half3 v_snorm) {
	return 0.5h * v_snorm + 0.5h;
}

/**
 Converts the given signed normalized value ([-1,1] range) to an unsigned 
 normalized value ([0,1] range).

 @pre			The given value is a signed normalized value ([-1,1] range).
 @param[in]		v_snorm
				The signed normalized value ([-1,1] range).
 @return		The unsigned normalized value ([0,1] range).
 */
half4 SNormToUNorm(half4 v_snorm) {
	return 0.5h * v_snorm + 0.5h;
}

/**
 Converts the given signed normalized value ([-1,1] range) to an unsigned 
 normalized value ([0,1] range).

 @pre			The given value is a signed normalized value ([-1,1] range).
 @param[in]		v_snorm
				The signed normalized value ([-1,1] range).
 @return		The unsigned normalized value ([0,1] range).
 */
float SNormToUNorm(float v_snorm) {
	return 0.5f * v_snorm + 0.5f;
}

/**
 Converts the given signed normalized value ([-1,1] range) to an unsigned 
 normalized value ([0,1] range).

 @pre			The given value is a signed normalized value ([-1,1] range).
 @param[in]		v_snorm
				The signed normalized value ([-1,1] range).
 @return		The unsigned normalized value ([0,1] range).
 */
float2 SNormToUNorm(float2 v_snorm) {
	return 0.5f * v_snorm + 0.5f;
}

/**
 Converts the given signed normalized value ([-1,1] range) to an unsigned 
 normalized value ([0,1] range).

 @pre			The given value is a signed normalized value ([-1,1] range).
 @param[in]		v_snorm
				The signed normalized value ([-1,1] range).
 @return		The unsigned normalized value ([0,1] range).
 */
float3 SNormToUNorm(float3 v_snorm) {
	return 0.5f * v_snorm + 0.5f;
}

/**
 Converts the given signed normalized value ([-1,1] range) to an unsigned 
 normalized value ([0,1] range).

 @pre			The given value is a signed normalized value ([-1,1] range).
 @param[in]		v_snorm
				The signed normalized value ([-1,1] range).
 @return		The unsigned normalized value ([0,1] range).
 */
float4 SNormToUNorm(float4 v_snorm) {
	return 0.5f * v_snorm + 0.5f;
}

/**
 Converts the given signed normalized value ([-1,1] range) to an unsigned 
 normalized value ([0,1] range).

 @pre			The given value is a signed normalized value ([-1,1] range).
 @param[in]		v_snorm
				The signed normalized value ([-1,1] range).
 @return		The unsigned normalized value ([0,1] range).
 */
double SNormToUNorm(double v_snorm) {
	return 0.5l * v_snorm + 0.5l;
}

/**
 Converts the given signed normalized value ([-1,1] range) to an unsigned 
 normalized value ([0,1] range).

 @pre			The given value is a signed normalized value ([-1,1] range).
 @param[in]		v_snorm
				The signed normalized value ([-1,1] range).
 @return		The unsigned normalized value ([0,1] range).
 */
double2 SNormToUNorm(double2 v_snorm) {
	return 0.5l * v_snorm + 0.5l;
}

/**
 Converts the given signed normalized value ([-1,1] range) to an unsigned 
 normalized value ([0,1] range).

 @pre			The given value is a signed normalized value ([-1,1] range).
 @param[in]		v_snorm
				The signed normalized value ([-1,1] range).
 @return		The unsigned normalized value ([0,1] range).
 */
double3 SNormToUNorm(double3 v_snorm) {
	return 0.5l * v_snorm + 0.5l;
}

/**
 Converts the given signed normalized value ([-1,1] range) to an unsigned 
 normalized value ([0,1] range).

 @pre			The given value is a signed normalized value ([-1,1] range).
 @param[in]		v_snorm
				The signed normalized value ([-1,1] range).
 @return		The unsigned normalized value ([0,1] range).
 */
double4 SNormToUNorm(double4 v_snorm) {
	return 0.5l * v_snorm + 0.5l;
}

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions: Packing/Unpacking
//-----------------------------------------------------------------------------

/**
 Unpacks the given @c uint (R16G16) to a @c float2.

 @param		u
			The @c uint (R16G16) to unpack.
 @return	The corresponding unpacked @c float2.
 */
float2 UnpackR16G16(uint u) {
	const float2 f = 0xFFFFu & uint2(u >> 16u, u);
	return f * (1.0f / 65535.0f);
}

/**
 Unpacks the given @c float2 to a @c uint (R16G16).

 @pre		@a f lies in [0.0,1.0]^2
 @param		u
			The @c float2 to pack.
 @return	The corresponding packed @c uint (R16G16).
 */
uint PackR16G16(float2 f) {
	const uint2 u = 65535.0f * f;
	return (u.x << 16u) | u.y;
}

/**
 Unpacks the given @c uint (R8G8B8A8) to a @c float4.

 @param		u
			The @c uint (R8G8B8A8) to unpack.
 @return	The corresponding unpacked @c float4.
 */
float4 UnpackR8G8B8A8(uint u) {
	const float4 f = 0xFFu & uint4(u >> 24u, u >> 16u, u >> 8u, u);
	return f * (1.0f / 255.0f);
}

/**
 Unpacks the given @c float4 to a @c uint (R8G8B8A8).

 @pre		@a f lies in [0.0,1.0]^4
 @param		u
			The @c float4 to pack.
 @return	The corresponding packed @c uint (R8G8B8A8).
 */
uint PackR8G8B8A8(float4 f) {
	const uint4 u = 255.0f * f;
	return (u.x << 24u) | (u.y << 16u) | (u.z << 8u) | u.w;
}

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions: Transformations
//-----------------------------------------------------------------------------

/**
 Apply the homogeneous divide on the given position expressed in projection 
 space.

 @param[in]		p_proj
				The position expressed in projection space.
 @return		The position expressed in projection space after the homogeneous 
				divide (i.e. the implicit w coordinate is equal to one).
 */
float3 HomogeneousDivide(float4 p_proj) {
	const float inv_w = 1.0f / p_proj.w;
	return p_proj.xyz * inv_w;
}

/**
 Converts the given (linear) z coordinate expressed in view space to the 
 corresponding (non-linear) z coordinate expressed in NDC space.

 @param[in]		p_view_z
				The (linear) z coordinate expressed in view space.
 @param[in]		projection_values
				The projection values of the view-to-projection matrix
				[view_to_projection22, view_to_projection32].
 @return		The (non-linear) z coordinate expressed in NDC space.
 */
float ViewZtoNDCZ(float p_view_z, float2 projection_values) {
	return projection_values.x + projection_values.y / p_view_z;
}

/**
 Converts the given position expressed in NDC space to the corresponding 
 position expressed in UV space.

 @param[in]		p_ndc_xy
				The position expressed in NDC space (x and y coordinates).
 @return		The position expressed in UV space.
 */
float2 NDCtoUV(float2 p_ndc_xy) {
	// [-1,1]^2 -> [0,1]x[1,0]
	return float2(0.5f, -0.5f) * p_ndc_xy + 0.5f;
}

/**
 Converts the given position expressed in UV space to the corresponding 
 position expressed in NDC space.

 @param[in]		p_uv
				The position expressed in UV space.
 @return		The position expressed in NDC space (x and y coordinates).
 */
float2 UVtoNDC(float2 p_uv) {
	// [0,1]^2 -> [-1,1]x[1,-1]
	return float2(2.0f, -2.0f) * p_uv + float2(-1.0f, 1.0f);
}

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions: Indexing
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
// Engine Declarations and Definitions: Trigonometry
//-----------------------------------------------------------------------------

/**
 Computes the sine of the given cosine.

 @param[in]		c
				The cosine.
 @return		The sine corresponding to the given cosine.
 */
float CosToSin(float c) {
	return sqrt(1.0f - sqr(c));
}

/**
 Computes the cosine of the given sine.

 @param[in]		s
				The sine.
 @return		The cosine corresponding to the given sine.
 */
float SinToCos(float s) {
	return sqrt(1.0f - sqr(s));
}

/**
 Computes the squared tangent from the given squared cosine.

 @param[in]		sqr_c
				The squared cosine.
 @return		The squared tangent corresponding to the given squared cosine.
 */
float SqrCosToSqrTan(float sqr_c) {
	return (1.0f - sqr_c) / sqr_c;
}

/**
 Computes the squared tangent from the given squared sine.

 @param[in]		sqr_s
				The squared sine.
 @return		The squared tangent corresponding to the given squared sine.
 */
float SqrSinToSqrTan(float sqr_s) {
	return sqr_s / (1.0f - sqr_s);
}

#endif // MAGE_HEADER_MATH
