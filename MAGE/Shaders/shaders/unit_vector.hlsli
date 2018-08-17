#ifndef MAGE_HEADER_UNIT_VECTOR
#define MAGE_HEADER_UNIT_VECTOR

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#include "math.hlsli"

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------

/**
 Encodes the given unit vector from the [-1,1] range to the [0,1] range using a 
 XYZ encoding.

 @pre			@a u is unit vectorized.
 @param[in]		u
				The unit vector in the [-1,1] range to convert.
 @return		The encoded unit vector in the [0,1] range.
 */
float3 EncodeUnitVector_XYZ(float3 u) {
	return SNormToUNorm(u);
}

/**
 Decodes the given unit vector from the [0,1] range to the [-1,1] range using a 
 XYZ decoding.

 @param[in]		e_unorm
				The encoded unit vector in the [0,1] range to convert.
 @return		The decoded unit vector in the [-1,1] range.
 */
float3 DecodeUnitVector_XYZ(float3 e_unorm) {
	return UNormToSNorm(e_unorm);
}

/**
 Encodes the given unit vector from the [-1,1] range to the [0,1] range using a 
 XY encoding.

 @pre			@a u is unit vectorized.
 @param[in]		u
				The unit vector in the [-1,1] range to convert.
 @return		The encoded unit vector in the [0,1] range.
 */
float2 EncodeUnitVector_XY(float3 u) {
	return EncodeUnitVector_XYZ(u).xy;
}

/**
 Decodes the given unit vector from the [0,1] range to the [-1,1] range using a 
 XY decoding.

 The z component will be positive and will be calculated from the x and y
 components.

 @param[in]		e_unorm
				The encoded unit vector in the [0,1] range to convert.
 @return		The decoded unit vector in the [-1,1] range.
 */
float3 DecodeUnitVector_XY(float2 e_unorm) {
	const float2 u_xy = UNormToSNorm(e_unorm);
	const float  u_z  = sqrt(1.0f - dot(u_xy, u_xy));
	return float3(u_xy, u_z);
}

/**
 Encodes the given unit vector from the [-1,1] range to the [0,1] range using a 
 spherical encoding.

 @pre			@a u is unit vectorized.
 @param[in]		u
				The unit vector in the [-1,1] range to convert.
 @return		The encoded unit vector in the [0,1] range.
 */
float2 EncodeUnitVector_Spherical(float3 u) {
	const float  phi       = all(0.0f == u.xy) ? 0.0f : atan2(u.y, u.x);
	const float  cos_theta = u.z;
	const float2 e_snorm   = { phi * g_inv_pi, cos_theta };
	return SNormToUNorm(e_snorm);
}

/**
 Decodes the given unit vector from the [0,1] range to the [-1,1] range using a 
 spherical decoding.

 @param[in]		e_unorm
				The encoded unit vector in the [0,1] range to convert.
 @return		The decoded unit vector in the [-1,1] range.
 */
float3 DecodeUnitVector_Spherical(float2 e_unorm) {
	const float2 e_snorm = UNormToSNorm(e_unorm);

	const float phi = e_snorm.x * g_pi;
	float sin_phi;
	float cos_phi;
	sincos(phi, sin_phi, cos_phi);

	const float cos_theta = e_snorm.y;
	const float sin_theta = CosToSin(cos_theta);

	return float3(cos_phi * sin_theta, 
				  sin_phi * sin_theta, 
				  cos_theta);
}

/**
 Encodes the given unit vector from the [-1,1] range to the [0,1] range using a 
 spheremap encoding.

 @pre			@a u is unit vectorized.
 @param[in]		u
				The unit vector in the [-1,1] range to convert.
 @return		The encoded unit vector in the [0,1] range.
 */
float2 EncodeUnitVector_SphereMap(float3 u) {
	const float2 e_snorm = normalize(u.xy) * sqrt(SNormToUNorm(-u.z));
	return SNormToUNorm(e_snorm);
}

/**
 Decodes the given unit vector from the [0,1] range to the [-1,1] range using a 
 spheremap decoding.

 @param[in]		e_unorm
				The encoded unit vector in the [0,1] range to convert.
 @return		The decoded unit vector in the [-1,1] range.
 */
float3 DecodeUnitVector_SphereMap(float2 e_unorm) {
	const float2 e_snorm = UNormToSNorm(e_unorm);
	const float4 e0      = { e_snorm, 1.0f, -1.0f};
	const float  l       = dot(e0.xyz, -e0.xyw);
	return 2.0f * float3(e0.xy * sqrt(l), l - 0.5f);
}

float2 OctahedronWrap(float2 v) {
	return (1.0f - abs(v.yx)) * (0.0f <= v.xy ? 1.0f : -1.0f);
}

/**
 Encodes the given unit vector from the [-1,1] range to the [0,1] range using a 
 octahedron encoding.

 @pre			@a u is unit vectorized.
 @param[in]		u
				The unit vector in the [-1,1] range to convert.
 @return		The encoded unit vector in the [0,1] range.
 */
float2 EncodeUnitVector_Octahedron(float3 u) {
	const float3 abs_u   = abs(u);
	const float3 u0      = u / (abs_u.x + abs_u.y + abs_u.z);
	const float2 e_snorm = (0.0f <= u0.z) ? u0.xy : OctahedronWrap(u0.xy);
	return SNormToUNorm(e_snorm);
}

/**
 Decodes the given unit vector from the [0,1] range to the [-1,1] range using a 
 octahedron decoding.

 @param[in]		e_unorm
				The encoded unit vector in the [0,1] range to convert.
 @return		The decoded unit vector in the [-1,1] range.
 */
float3 DecodeUnitVector_Octahedron(float2 e_unorm) {
	const float2 e_snorm = UNormToSNorm(e_unorm);
	const float3 e0      = { e_snorm.x, e_snorm.y, 
		                     1.0f - abs(e_snorm.x) - abs(e_snorm.y) };
	const float  s       = saturate(-e0.z);
	const float2 u_xy    = e0.xy + (0.0f <= e0.xy ? -s : s);
	return normalize(float3(u_xy, e0.z));
}

#endif // MAGE_HEADER_UNIT_VECTOR
