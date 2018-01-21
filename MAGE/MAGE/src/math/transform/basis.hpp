#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "math\math.hpp"

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
		                                                  XMVECTOR &b1, 
		                                                  XMVECTOR &b2) noexcept {

		const auto u = (fabs(XMVectorGetX(n)) > fabs(XMVectorGetZ(n)))
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
		                                             XMVECTOR &b1, 
		                                             XMVECTOR &b2) noexcept {
		F32x3 nf;
		XMStoreFloat3(&nf, n);

		if (nf.m_z < -0.9999999f) {
			b1 = XMVectorSet( 0.0f, -1.0f, 0.0f, 0.0f);
			b2 = XMVectorSet(-1.0f,  0.0f, 0.0f, 0.0f);
			return;
		}

		const auto a = 1.0f / (1.0f + nf.m_z);
		const auto b = -nf.m_x * nf.m_y * a;
		b1 = XMVectorSet(1.0f - nf.m_x * nf.m_x * a, 
			             b, 
			             -nf.m_x, 0.0f);
		b2 = XMVectorSet(b, 
			             1.0f - nf.m_y * nf.m_y * a, 
			             -nf.m_y, 0.0f);
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
		                                          XMVECTOR &b1, 
		                                          XMVECTOR &b2) noexcept {
		F32x3 nf;
		XMStoreFloat3(&nf, n);

		const auto sign = copysignf(1.0f, nf.m_z);
		const auto a = -1.0f / (sign + nf.m_z);
		const auto b = nf.m_x * nf.m_y * a;
		b1 = XMVectorSet(1.0f + sign * nf.m_x * nf.m_x * a, 
			             sign * b, 
			             -sign * nf.m_x, 0.0f);
		b2 = XMVectorSet(b, sign + nf.m_y * nf.m_y * a, 
			             -nf.m_y, 
			             0.0f);
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
		                                     XMVECTOR &b1, 
		                                     XMVECTOR &b2) noexcept {
		OrthonormalBasis_Duff(n, b1, b2);
	}
}
