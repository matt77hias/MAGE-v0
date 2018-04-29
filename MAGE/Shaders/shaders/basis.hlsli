#ifndef MAGE_HEADER_BASIS
#define MAGE_HEADER_BASIS

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------

/**
 Calculates an orthonormal basis from a given unit vector with the method of 
 Hughes and Möller.

 @pre			@a n is normalized.
 @param[in]		n
				A basis vector of the orthonormal basis.
 @return		An orthonormal basis.
 */
float3x3 OrthonormalBasis_HughesMoller(float3 n) {
	const float3 abs_n   = abs(n);
	const float3 n_ortho = (abs_n.x > abs_n.z) ? float3(-n.y,  n.x, 0.0f)
		                                       : float3(1.0f, -n.z,  n.y);
	const float3 t = normalize(cross(n_ortho, n));
	const float3 b = cross(n, t);

	return float3x3(t, b, n);
}

/**
 Calculates an orthonormal basis from a given unit vector with the method of 
 Duff, Burgess, Christensen, Hery, Kensler, Liani and Villemin.

 @pre			@a n is normalized.
 @param[in]		n
				A basis vector of the orthonormal basis.
 @return		An orthonormal basis.
 */
float3x3 OrthonormalBasis_Duff(float3 n) {
	const float  s  = (0.0f > n.z) ? -1.0f : 1.0f;
	const float  a0 = -1.0f / (s + n.z);
	const float  a1 = n.x * n.y * a0;

	const float3 t  = { 1.0f + s * n.x * n.x * a0, s * a1, -s * n.x };
	const float3 b  = { a1, s + n.y * n.y * a0, -n.y };

	return float3x3(t, b, n);
}

/**
 Calculates an orthonormal basis from a given unit vector with the method.

 @pre			@a n is normalized.
 @param[in]		n
				A basis vector of the orthonormal basis.
 @return		An orthonormal basis.
 */
float3x3 OrthonormalBasis(float3 n) {
	return OrthonormalBasis_Duff(n);
}

#endif // MAGE_HEADER_BASIS