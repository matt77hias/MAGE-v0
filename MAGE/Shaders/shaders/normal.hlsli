#ifndef MAGE_HEADER_NORMAL
#define MAGE_HEADER_NORMAL

//-----------------------------------------------------------------------------
// Engine Configuration
//-----------------------------------------------------------------------------
// Defines			                        | Default
//-----------------------------------------------------------------------------
// NORMAL_DECODE_FUNCTION                   | DecodeNormal_Octahedron
// NORMAL_ENCODE_FUNCTION                   | EncodeNormal_Octahedron
// TSNM_DECODE_FUNCTION                     | DecodeNormal_XY
// TSNM_ENCODE_FUNCTION                     | EncodeNormal_XY

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#include "math.hlsli"

//-----------------------------------------------------------------------------
// Engine Defines
//-----------------------------------------------------------------------------

#ifndef NORMAL_ENCODE_FUNCTION
	#define NORMAL_ENCODE_FUNCTION EncodeNormal_Octahedron
#endif // NORMAL_ENCODE_FUNCTION

#ifndef NORMAL_DECODE_FUNCTION
	#define NORMAL_DECODE_FUNCTION DecodeNormal_Octahedron
#endif // NORMAL_DECODE_FUNCTION

#ifndef TSNM_ENCODE_FUNCTION
	#define TSNM_ENCODE_FUNCTION EncodeNormal_XY
#endif // TSNM_ENCODE_FUNCTION

#ifndef TSNM_DECODE_FUNCTION
	#define TSNM_DECODE_FUNCTION DecodeNormal_XY
#endif // TSNM_DECODE_FUNCTION

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions: Normal Encoding/Decoding
//-----------------------------------------------------------------------------

/**
 Encodes the given normal from the [0,1] range to the [-1,1] range using a XYZ 
 encoding.

 @pre			@a n is normalized.
 @param[in]		n
				The normal in the [0,1] range to convert.
 @return		The encoded normal in the [-1,1] range.
 */
float3 EncodeNormal_XYZ(float3 n) {
	return SNORMtoUNORM(n);
}

/**
 Decodes the given normal from the [0,1] range to the [-1,1] range using a XYZ 
 decoding.

 @param[in]		n_unorm
				The normal in the [0,1] range to convert.
 @return		The decoded normal in the [-1,1] range.
 */
float3 DecodeNormal_XYZ(float3 n_unorm) {
	return UNORMtoSNORM(n_unorm);
}

/**
 Encodes the given normal from the [0,1] range to the [-1,1] range using a XY 
 encoding.

 @pre			@a n is normalized.
 @param[in]		n
				The normal in the [0,1] range to convert.
 @return		The encoded normal in the [-1,1] range.
 */
float2 EncodeNormal_XY(float3 n) {
	return EncodeNormal_XYZ(n).xy;
}

/**
 Decodes the given normal from the [0,1] range to the [-1,1] range using a XY 
 decoding.

 The z component will be positive and will be calculated from the x and y
 components.

 @param[in]		n_unorm
				The normal in the [0,1] range to convert.
 @return		The decoded normal in the [-1,1] range.
 */
float3 DecodeNormal_XY(float2 n_unorm) {
	const float2 n_xy = UNORMtoSNORM(n_unorm);
	const float  n_z  = sqrt(1.0f - dot(n_xy, n_xy));
	return float3(n_xy, n_z);
}

/**
 Encodes the given normal from the [0,1] range to the [-1,1] range using a 
 spherical encoding.

 @pre			@a n is normalized.
 @param[in]		n
				The normal in the [0,1] range to convert.
 @return		The encoded normal in the [-1,1] range.
 */
float2 EncodeNormal_Spherical(float3 n) {
	const float phi       = atan2(n.y, n.x);
	const float cos_theta = n.z;
	return SNORMtoUNORM(float2(phi * g_inv_pi, cos_theta));
}

/**
 Decodes the given normal from the [0,1] range to the [-1,1] range using a 
 spherical decoding.

 @param[in]		n_unorm
				The normal in the [0,1] range to convert.
 @return		The decoded normal in the [-1,1] range.
 */
float3 DecodeNormal_Spherical(float2 n_unorm) {
	const float2 n_snorm = UNORMtoSNORM(n_unorm);

	const float phi = n_snorm.x * g_pi;
	float sin_phi;
	float cos_phi;
	sincos(phi, sin_phi, cos_phi);

	const float cos_theta = n_snorm.y;
	const float sin_theta = CosToSin(cos_theta);

	return float3(cos_phi * sin_theta, 
				  sin_phi * sin_theta, 
				  cos_theta);
}

/**
 Encodes the given normal from the [0,1] range to the [-1,1] range using a 
 spheremap encoding.

 @pre			@a n is normalized.
 @param[in]		n
				The normal in the [0,1] range to convert.
 @return		The encoded normal in the [-1,1] range.
 */
float2 EncodeNormal_SphereMap(float3 n) {
	const float2 n_snorm = normalize(n.xy) * sqrt(SNORMtoUNORM(-n.z));
	return SNORMtoUNORM(n_snorm);
}

/**
 Decodes the given normal from the [0,1] range to the [-1,1] range using a 
 spheremap decoding.

 @param[in]		n_unorm
				The normal in the [0,1] range to convert.
 @return		The encoded normal in the [-1,1] range.
 */
float3 DecodeNormal_SphereMap(float2 n_unorm) {
	const float2 n_snorm = UNORMtoSNORM(n_unorm);
	const float4 n0      = float4(n_snorm, 1.0f, -1.0f);
	const float  l       = dot(n0.xyz, -n0.xyw);
	return 2.0f * float3(n0.xy * sqrt(l), l - 0.5f);
}

float2 OctahedronWrap(float2 v) {
	return (1.0f - abs(v.yx)) * (0.0f <= v.xy ? 1.0f : -1.0f);
}

/**
 Encodes the given normal from the [0,1] range to the [-1,1] range using a 
 octahedron encoding.

 @pre			@a n is normalized.
 @param[in]		n
				The normal in the [0,1] range to convert.
 @return		The encoded normal in the [-1,1] range.
 */
float2 EncodeNormal_Octahedron(float3 n) {
	const float3 abs_n   = abs(n);
	const float3 n0      = n / (abs_n.x + abs_n.y + abs_n.z);
	const float2 n_snorm = (0.0f <= n0.z) ? n0.xy : OctahedronWrap(n0.xy);
	return SNORMtoUNORM(n_snorm);
}

/**
 Decodes the given normal from the [0,1] range to the [-1,1] range using a 
 octahedron decoding.

 @param[in]		n_unorm
				The normal in the [0,1] range to convert.
 @return		The encoded normal in the [-1,1] range.
 */
float3 DecodeNormal_Octahedron(float2 n_unorm) {
	const float2 n_snorm = UNORMtoSNORM(n_unorm);
	const float3 n0      = float3(n_snorm.x, n_snorm.y, 
								  1.0f - abs(n_snorm.x) - abs(n_snorm.y));
	const float  t       = saturate(-n0.z);
	const float2 c_xy    = n0.xy + (0.0f <= n0.xy ? -t : t);
	return normalize(float3(c_xy, n0.z));
}

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions: Normal Mapping
//-----------------------------------------------------------------------------

// The input arguments (p and n) for applying tangent space normal mapping must 
// be expressed in the same coordinate system which can be chosen arbitrarily.

/**
 Computes the tangent-to-shading transformation matrix.

 @pre			@a n is normalized.
 @param[in]		p
				The surface position expressed in shading space.
 @param[in]		n
				The surface normal to perturb expressed in shading space.
 @param[in]		tex
				The texture coordinates.
 @return		The tangent-to-shading transformation matrix.
 */
float3x3 TangentToShadingMatrix(float3 p, float3 n, float2 tex) {
	// Calculates the edge differences.
	const float3 dp_dj   = ddx(p);
	const float3 dp_di   = ddy(p);
	const float2 dtex_dj = ddx(tex);
	const float2 dtex_di = ddy(tex);

	// Solve the linear system of equations to obtain the cotangents t and b.
	const float3 dp_di_ortho = cross(dp_di, n);
	const float3 dp_dj_ortho = cross(n, dp_dj);
	// Calculate the gradient of texture coordinate u as a function of p.
	const float3 t = dtex_dj.x * dp_di_ortho + dtex_di.x * dp_dj_ortho;
	// Calculate the gradient of texture coordinate v as a function of p.
	const float3 b = dtex_dj.y * dp_di_ortho + dtex_di.y * dp_dj_ortho;

	// Construct a scale-invariant frame.
	const float inv_det = rsqrt(max(dot(t, t), dot(b, b)));
	const float3x3 tangent_to_shading = { t * inv_det, b * inv_det, n };

	return tangent_to_shading;
}

/**
 Calculates the perturbed surface normal.

 @pre			@a n is normalized.
 @pre			@a n_tangent is normalized.
 @param[in]		p
				The surface position expressed in shading space.
 @param[in]		n
				The surface normal to perturb expressed in shading space.
 @param[in]		tex
				The texture coordinates.
 @param[in]		n_tangent
				The surface normal expressed in tangent space.
 @return		The perturbed surface normal expressed in shading space.
 */
float3 PerturbNormal(float3 p, float3 n, float2 tex, float3 n_tangent) {
	// Calculates the tangent-to-shading transformation matrix.
	const float3x3 tangent_to_shading = TangentToShadingMatrix(p, n, tex);
	return normalize(mul(n_tangent, tangent_to_shading));
}

#endif // MAGE_HEADER_NORMAL