#ifndef MAGE_HEADER_NORMAL_MAPPING
#define MAGE_HEADER_NORMAL_MAPPING

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#include "math.hlsli"

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------

/**
 Calculates the TBN coordinate frame.

 @pre			@a n is normalized.
 @param[in]		p
				The view-space position.
 @param[in]		n
				The view-space normal to perturb.
 @param[in]		tex
				The texture coordinates.
 */
float3x3 CalculateTBN(float3 p, float3 n, float2 tex) {
	// Calculates the edge differences.
	const float3 dp_dj = ddx(p);
	const float3 dp_di = ddy(p);
	const float2 dtex_dj = ddx(tex);
	const float2 dtex_di = ddy(tex);

	// Solve the linear system of equations to obtain
	// the cotangents t and b.
	const float3 dp_di_ortho = cross(dp_di, n);
	const float3 dp_dj_ortho = cross(n, dp_dj);
	// Calculate the gradient of texture coordinate u as a function of p.
	const float3 t = dtex_dj.x * dp_di_ortho + dtex_di.x * dp_dj_ortho;
	// Calculate the gradient of texture coordinate v as a function of p.
	const float3 b = dtex_dj.y * dp_di_ortho + dtex_di.y * dp_dj_ortho;

	// Construct a scale-invariant frame.
	const float inv_det = rsqrt(max(dot(t, t), dot(b, b)));
	const float3x3 TBN  = { t * inv_det, b * inv_det, n };

	return TBN;
}

/**
 Returns the perturbed normal.

 @pre			@a n is normalized.
 @param[in]		p
				The view-space position.
 @param[in]		n
				The view-space normal to perturb.
 @param[in]		tex
				The texture coordinates.
 @param[in]		c
				The tangent-space coefficients.
 */
float3 PerturbNormal(
	float3 p, float3 n, float2 tex, float3 c) {

	const float3x3 TBN = CalculateTBN(p, n, tex);

	return normalize(mul(c, TBN));
}



#endif // MAGE_HEADER_NORMAL_MAPPING