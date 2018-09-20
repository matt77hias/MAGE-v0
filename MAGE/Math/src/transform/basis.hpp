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
		return { t, b, n, g_XMIdentityR3 };
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

		const auto [nx, ny, nz] = XMStore< F32x3 >(n);

		if (nz < -0.9999999f) {
			return { -g_XMIdentityR1, -g_XMIdentityR0, n, g_XMIdentityR3 };
		}

		const auto a0 = 1.0f / (1.0f + nz);
		const auto a1 = -nx * ny * a0;

		const XMVECTOR t = { 1.0f - nx * nx * a0, a1, -nx, 0.0f };
		const XMVECTOR b = { a1, 1.0f - ny * ny * a0, -ny, 0.0f };
		return { t, b, n, g_XMIdentityR3 };
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

		const auto [nx, ny, nz] = XMStore< F32x3 >(n);

		const auto s  = std::copysignf(1.0f, nz);
		const auto a0 = -1.0f / (s + nz);
		const auto a1 = nx * ny * a0;

		const XMVECTOR t = { 1.0f + s * nx * nx * a0, s * a1, -s * nx, 0.0f };
		const XMVECTOR b = { a1, s + ny * ny * a0, -ny, 0.0f };
		return { t, b, n, g_XMIdentityR3 };
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
