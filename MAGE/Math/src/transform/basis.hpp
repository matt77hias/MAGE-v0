#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "math.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 Calculates an orthonormal basis from a given unit vector with the method 
	 of Hughes and Möller.

	 @pre			The given vector is normalized.
	 @param[in]		n
					The first basis vector of the orthonormal basis.
	 @param[out]	b1
					The second basis vector of the orthonormal basis.
	 @param[out]	b2
					The third basis vector of the orthonormal basis.
	 */
	inline void XM_CALLCONV OrthonormalBasis_HughesMoller(FXMVECTOR n, 
		                                                  XMVECTOR& b1, 
		                                                  XMVECTOR& b2) noexcept {
		const auto abs_n = XMVectorAbs(n);
		const auto u     = (XMVectorGetX(abs_n) > XMVectorGetZ(abs_n))
			? XMVectorSet(-XMVectorGetY(n), XMVectorGetX(n), 0.0f, 0.0f)
			: XMVectorSet(0.0f, -XMVectorGetZ(n), XMVectorGetY(n), 0.0f);
		b2 = XMVector3Normalize(u);
		b1 = XMVector3Cross(b2, n);
	}

	/**
	 Calculates an orthonormal basis from a given unit vector with the method 
	 of Frisvad.

	 @pre			The given vector is normalized.
	 @param[in]		n
					The first basis vector of the orthonormal basis.
	 @param[out]	b1
					The second basis vector of the orthonormal basis.
	 @param[out]	b2
					The third basis vector of the orthonormal basis.
	 */
	inline void XM_CALLCONV OrthonormalBasis_Frisvad(FXMVECTOR n, 
		                                             XMVECTOR& b1, 
		                                             XMVECTOR& b2) noexcept {
		const auto nf = XMStore< F32x3 >(n);

		if (nf[2] < -0.9999999f) {
			b1 = XMVectorSet( 0.0f, -1.0f, 0.0f, 0.0f);
			b2 = XMVectorSet(-1.0f,  0.0f, 0.0f, 0.0f);
			return;
		}

		const auto a = 1.0f / (1.0f + nf[2]);
		const auto b = -nf[0] * nf[1] * a;
		b1 = XMVectorSet(1.0f - nf[0] * nf[0] * a, b, -nf[0], 0.0f);
		b2 = XMVectorSet(b, 1.0f - nf[1] * nf[1] * a, -nf[1], 0.0f);
	}

	/**
	 Calculates an orthonormal basis from a given unit vector with the method 
	 of Duff, Burgess, Christensen, Hery, Kensler, Liani and Villemin.

	 @pre			The given vector is normalized.
	 @param[in]		n
					The first basis vector of the orthonormal basis.
	 @param[out]	b1
					The second basis vector of the orthonormal basis.
	 @param[out]	b2
					The third basis vector of the orthonormal basis.
	 */
	inline void XM_CALLCONV OrthonormalBasis_Duff(FXMVECTOR n, 
		                                          XMVECTOR& b1, 
		                                          XMVECTOR& b2) noexcept {
		const auto nf = XMStore< F32x3 >(n);

		const auto s = copysignf(1.0f, nf[2]);
		const auto a = -1.0f / (s + nf[2]);
		const auto b = nf[0] * nf[1] * a;
		b1 = XMVectorSet(1.0f + s * nf[0] * nf[0] * a, s * b, -s * nf[0], 0.0f);
		b2 = XMVectorSet(b, s + nf[1] * nf[1] * a, -nf[1], 0.0f);
	}

	/**
	 Calculates an orthonormal basis from a given unit vector.

	 @pre			The given vector is normalized.
	 @param[in]		n
					The first basis vector of the orthonormal basis.
	 @param[out]	b1
					The second basis vector of the orthonormal basis.
	 @param[out]	b2
					The third basis vector of the orthonormal basis.
	 */
	inline void XM_CALLCONV OrthonormalBasis(FXMVECTOR n, 
		                                     XMVECTOR& b1, 
		                                     XMVECTOR& b2) noexcept {
		OrthonormalBasis_Duff(n, b1, b2);
	}
}
