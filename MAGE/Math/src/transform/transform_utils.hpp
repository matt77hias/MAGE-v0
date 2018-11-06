#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "math_utils.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	[[nodiscard]]
	inline const XMMATRIX XM_CALLCONV
		GetTranslationMatrix(FXMVECTOR translation) noexcept {

		return XMMatrixTranslationFromVector(translation);
	}

	[[nodiscard]]
	inline const XMMATRIX XM_CALLCONV
		GetInverseTranslationMatrix(FXMVECTOR translation) noexcept {

		return GetTranslationMatrix(-translation);
	}

	[[nodiscard]]
	inline const XMVECTOR XM_CALLCONV
		GetRollPitchYawQuaternion(FXMVECTOR rotation) noexcept {

		// Rz (Roll) . Rx (Pitch) . Ry (Yaw)
		return XMQuaternionRotationRollPitchYawFromVector(rotation);
	}

	[[nodiscard]]
	inline const XMVECTOR XM_CALLCONV
		GetInverseRollPitchYawQuaternion(FXMVECTOR rotation) noexcept {

		// Ry (Yaw) . Rx (Pitch) . Rz (Roll)
		return XMQuaternionInverse(GetRollPitchYawQuaternion(rotation));
	}

	[[nodiscard]]
	inline const XMMATRIX XM_CALLCONV
		GetRollPitchYawMatrix(FXMVECTOR rotation) noexcept {

		return XMMatrixRotationRollPitchYawFromVector(rotation);
	}

	[[nodiscard]]
	inline const XMMATRIX XM_CALLCONV
		GetInverseRollPitchYawMatrix(FXMVECTOR rotation) noexcept {

		return XMMatrixTranspose(GetRollPitchYawMatrix(rotation));
	}

	[[nodiscard]]
	inline const XMMATRIX XM_CALLCONV
		GetScalingMatrix(FXMVECTOR scale) noexcept {

		return XMMatrixScalingFromVector(scale);
	}

	[[nodiscard]]
	inline const XMMATRIX XM_CALLCONV
		GetScalingMatrix(F32 scale) noexcept {

		return GetScalingMatrix(XMLoad(F32x3(scale)));
	}

	[[nodiscard]]
	inline const XMMATRIX XM_CALLCONV
		GetInverseScalingMatrix(FXMVECTOR scale) noexcept {

		return GetScalingMatrix(XMVectorReciprocal(scale));
	}

	[[nodiscard]]
	inline const XMMATRIX XM_CALLCONV
		GetInverseScalingMatrix(F32 scale) noexcept {

		return GetInverseScalingMatrix(XMLoad(F32x3(scale)));
	}

	[[nodiscard]]
	inline const XMMATRIX XM_CALLCONV
		GetAffineTransformationMatrix(FXMVECTOR scale,
									  FXMVECTOR rotation,
									  FXMVECTOR translation) noexcept {

		// Scale . Rotation . Translation
		//
		//   [ Sx 0  0  0 ] [ R00 R01 R02 0 ] [ 1  0  0  0 ]
		// = [ 0  Sy 0  0 ] [ R10 R11 R12 0 ] [ 0  1  0  0 ]
		//   [ 0  0  Sz 0 ] [ R20 R21 R22 0 ] [ 0  0  1  0 ]
		//   [ 0  0  0  1 ] [ 0   0   0   1 ] [ Tx Ty Tz 1 ]
		//
		//   [ Sx.R00 Sx.R01 Sx.R02 0 ]   [ Sx*R0, ]
		// = [ Sy.R10 Sy.R11 Sy.R12 0 ] = [ Sy*R1, ]
		//   [ Sz.R20 Sz.R21 Sz.R22 0 ]   [ Sz*R2, ]
		//   [ Tx     Ty     Tz     1 ]   [ T    1 ]

		auto transformation = GetRollPitchYawMatrix(rotation);
		transformation.r[0u] *= XMVectorGetX(scale);
		transformation.r[1u] *= XMVectorGetY(scale);
		transformation.r[2u] *= XMVectorGetZ(scale);
		transformation.r[3u] = XMVectorSetW(translation, 1.0f);
		return transformation;
	}

	[[nodiscard]]
	inline const XMMATRIX XM_CALLCONV
		GetAffineTransformationMatrix(F32       scale,
									  FXMVECTOR rotation,
									  FXMVECTOR translation) noexcept {
		
		return GetAffineTransformationMatrix(XMLoad(F32x3(scale)),
											 rotation,
											 translation);
	}

	[[nodiscard]]
	inline const XMMATRIX XM_CALLCONV
		GetInverseAffineTransformationMatrix(FXMVECTOR scale,
											 FXMVECTOR rotation,
											 FXMVECTOR translation) noexcept {

		// Translation . Rotation . Scale
		//
		//   [ 1   0   0   0 ] [ R00' R01' R02' 0 ] [ Sx' 0   0   0 ]
		// = [ 0   1   0   0 ] [ R10' R11' R12' 0 ] [ 0   Sy' 0   0 ]
		//   [ 0   0   1   0 ] [ R20' R21' R22' 0 ] [ 0   0   Sz' 0 ]
		//   [ Tx' Ty' Tz' 1 ] [ 0    0    0    1 ] [ 0   0   0   1 ]
		//
		//   [   R00'.Sx    R01'.Sy    R02'.Sz 0 ]   [ R0,'*S   ]
		// = [   R10'.Sx    R11'.Sy    R12'.Sz 0 ] = [ R1,'*S   ]
		//   [   R20'.Sx    R21'.Sy    R22'.Sz 0 ]   [ R2,'*S   ]
		//   [ R,0'.T.Sx  R,1'.T.Sy  R,2'.T.Sz 1 ]   [ R [T*S 1]]

		auto transformation = GetInverseRollPitchYawMatrix(rotation);
		const auto t = XMVector3TransformCoord(-translation, transformation);
		const auto s = XMVectorSetW(XMVectorReciprocal(scale), 1.0f);
		transformation.r[0u] *= s;
		transformation.r[1u] *= s;
		transformation.r[2u] *= s;
		transformation.r[3u] = s * t;
		return transformation;
	}

	[[nodiscard]]
	inline const XMMATRIX XM_CALLCONV
		GetInverseAffineTransformationMatrix(F32       scale,
											 FXMVECTOR rotation,
											 FXMVECTOR translation) noexcept {

		return GetInverseAffineTransformationMatrix(XMLoad(F32x3(scale)),
													rotation,
													translation);
	}

	[[nodiscard]]
	inline const XMMATRIX XM_CALLCONV
		GetAffineTransformationMatrix(FXMVECTOR scale,
									  F32       rotation,
									  FXMVECTOR translation) noexcept {

		// Scale . Rotation . Translation
		//
		//   [ Sx 0  0  0 ] [ R00 R01 0 0 ] [ 1  0  0  0 ]
		// = [ 0  Sy 0  0 ] [ R10 R11 0 0 ] [ 0  1  0  0 ]
		//   [ 0  0  _  0 ] [ 0   0   1 0 ] [ 0  0  1  0 ]
		//   [ 0  0  0  1 ] [ 0   0   0 1 ] [ Tx Ty _  1 ]
		//
		//   [ Sx.R00 Sx.R01 0 0 ]   [ Sx*R0,  ]
		// = [ Sy.R10 Sy.R11 0 0 ] = [ Sy*R1,  ]
		//   [ 0      0      _ 0 ]   [ 0 0 _ 0 ]
		//   [ Tx     Ty     0 1 ]   [ T   _ 1 ]

		auto transformation  = XMMatrixRotationZ(rotation);
		transformation.r[0u] *= XMVectorGetX(scale);
		transformation.r[1u] *= XMVectorGetY(scale);
		transformation.r[3u]  = XMVectorSetW(translation, 1.0f);
		return transformation;
	}

	[[nodiscard]]
	inline const XMMATRIX XM_CALLCONV
		GetAffineTransformationMatrix(FXMVECTOR offset,
									  FXMVECTOR scale,
									  F32       rotation,
									  FXMVECTOR translation) noexcept {

		// Inverse Offset Translation . Scale . Rotation . Translation
		auto transformation  = GetAffineTransformationMatrix(scale,
															 rotation,
															 translation);
		transformation.r[3u] = XMVector3TransformCoord(-offset, transformation);
		return transformation;
	}
}