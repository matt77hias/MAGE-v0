#ifndef MAGE_HEADER_NORMAL
#define MAGE_HEADER_NORMAL

//-----------------------------------------------------------------------------
// Engine Configuration
//-----------------------------------------------------------------------------
// Defines			                        | Default
//-----------------------------------------------------------------------------
// NORMAL_DECODE_FUNCTION                   | DecodeUnitVector_Octahedron
// NORMAL_ENCODE_FUNCTION                   | EncodeUnitVector_Octahedron
// TSNM_DECODE_FUNCTION                     | DecodeUnitVector_XY
// TSNM_ENCODE_FUNCTION                     | EncodeUnitVector_XY

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#include "unit_vector.hlsli"

//-----------------------------------------------------------------------------
// Engine Defines
//-----------------------------------------------------------------------------

#ifndef NORMAL_ENCODE_FUNCTION
	#define NORMAL_ENCODE_FUNCTION EncodeUnitVector_Octahedron
#endif // NORMAL_ENCODE_FUNCTION

#ifndef NORMAL_DECODE_FUNCTION
	#define NORMAL_DECODE_FUNCTION DecodeUnitVector_Octahedron
#endif // NORMAL_DECODE_FUNCTION

#ifndef TSNM_ENCODE_FUNCTION
	#define TSNM_ENCODE_FUNCTION EncodeUnitVector_XY
#endif // TSNM_ENCODE_FUNCTION

#ifndef TSNM_DECODE_FUNCTION
	#define TSNM_DECODE_FUNCTION DecodeUnitVector_XY
#endif // TSNM_DECODE_FUNCTION

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