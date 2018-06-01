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

	 @pre			@a n is normalized.
	 @param[in]		n
					A basis vector of the orthonormal basis.
	 @return		An orthonormal basis (i.e. object-to-world transformation).
	 */
	[[nodiscard]]
	inline const XMMATRIX XM_CALLCONV 
		OrthonormalBasis_HughesMoller(FXMVECTOR n) noexcept {
		const auto abs_n   = XMVectorAbs(n);
		const auto n_ortho = (XMVectorGetX(abs_n) > XMVectorGetZ(abs_n))
			? XMVectorSet(-XMVectorGetY(n), XMVectorGetX(n), 0.0f, 0.0f)
			: XMVectorSet(0.0f, -XMVectorGetZ(n), XMVectorGetY(n), 0.0f);
		
		const auto t = XMVector3Normalize(XMVector3Cross(n_ortho, n));
		const auto b = XMVector3Cross(n, t);
		return XMMATRIX(t, b, n, g_XMIdentityR3);
	}

	/**
	 Calculates an orthonormal basis from a given unit vector with the method 
	 of Frisvad.

	 @pre			@a n is normalized.
	 @param[in]		n
					A basis vector of the orthonormal basis.
	 @return		An orthonormal basis (i.e. object-to-world transformation).
	 */
	[[nodiscard]]
	inline const XMMATRIX XM_CALLCONV 
		OrthonormalBasis_Frisvad(FXMVECTOR n) noexcept {
		const auto nf = XMStore< F32x3 >(n);

		if (nf[2] < -0.9999999f) {
			const auto t = XMVectorSet( 0.0f, -1.0f, 0.0f, 0.0f);
			const auto b = XMVectorSet(-1.0f,  0.0f, 0.0f, 0.0f);
			return XMMATRIX(t, b, n, g_XMIdentityR3);
		}

		const auto a0 = 1.0f / (1.0f + nf[2]);
		const auto a1 = -nf[0] * nf[1] * a0;

		const auto t  = XMVectorSet(1.0f - nf[0] * nf[0] * a0, a1, -nf[0], 0.0f);
		const auto b  = XMVectorSet(a1, 1.0f - nf[1] * nf[1] * a0, -nf[1], 0.0f);
		return XMMATRIX(t, b, n, g_XMIdentityR3);
	}

	/**
	 Calculates an orthonormal basis from a given unit vector with the method 
	 of Duff, Burgess, Christensen, Hery, Kensler, Liani and Villemin.

	 @pre			@a n is normalized.
	 @param[in]		n
					A basis vector of the orthonormal basis.
	 @return		An orthonormal basis (i.e. object-to-world transformation).
	 */
	[[nodiscard]]
	inline const XMMATRIX XM_CALLCONV 
		OrthonormalBasis_Duff(FXMVECTOR n) noexcept {
		const auto nf = XMStore< F32x3 >(n);

		const auto s  = copysignf(1.0f, nf[2]);
		const auto a0 = -1.0f / (s + nf[2]);
		const auto a1 = nf[0] * nf[1] * a0;

		const auto t  = XMVectorSet(1.0f + s * nf[0] * nf[0] * a0, s * a1, -s * nf[0], 0.0f);
		const auto b  = XMVectorSet(a1, s + nf[1] * nf[1] * a0, -nf[1], 0.0f);
		return XMMATRIX(t, b, n, g_XMIdentityR3);
	}

	/**
	 Calculates an orthonormal basis from a given unit vector.

	 @pre			@a n is normalized.
	 @param[in]		n
					A basis vector of the orthonormal basis.
	 @return		An orthonormal basis (i.e. object-to-world transformation).
	 */
	[[nodiscard]]
	inline const XMMATRIX XM_CALLCONV 
		OrthonormalBasis(FXMVECTOR n) noexcept {
		return OrthonormalBasis_Duff(n);
	}
}
