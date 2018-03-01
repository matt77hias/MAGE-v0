#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "type\types.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// System Includes
//-----------------------------------------------------------------------------
#pragma region

#include <directxmath.h>
namespace mage {
	using namespace DirectX;
}

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	[[nodiscard]] 
	inline const XMMATRIX XM_CALLCONV 
		XMMatrixTranslation(FXMVECTOR translation) noexcept {

		return XMMatrixTranslationFromVector(translation);
	}

	[[nodiscard]] 
	inline const XMMATRIX XM_CALLCONV 
		XMMatrixInverseTranslation(FXMVECTOR translation) noexcept {
		
		return XMMatrixTranslation(-translation);
	}

	[[nodiscard]] 
	inline const XMVECTOR XM_CALLCONV 
		XMQuaternionRotationRollPitchYaw(FXMVECTOR rotation) noexcept {

		return XMQuaternionRotationRollPitchYawFromVector(rotation);
	}

	[[nodiscard]] 
	inline const XMVECTOR XM_CALLCONV 
		XMQuaternionInverseRotationRollPitchYaw(FXMVECTOR rotation) noexcept {

		return XMQuaternionInverse(XMQuaternionRotationRollPitchYaw(rotation));
	}

	[[nodiscard]] 
	inline const XMMATRIX XM_CALLCONV 
		XMMatrixRotationRollPitchYaw(FXMVECTOR rotation) noexcept {

		return XMMatrixRotationRollPitchYawFromVector(rotation);
	}

	[[nodiscard]] 
	inline const XMMATRIX XM_CALLCONV 
		XMMatrixInverseRotationRollPitchYaw(FXMVECTOR rotation) noexcept {

		return XMMatrixTranspose(XMMatrixRotationRollPitchYaw(rotation));
	}

	[[nodiscard]] 
	inline const XMMATRIX XM_CALLCONV 
		XMMatrixScaling(FXMVECTOR scale) noexcept {

		return XMMatrixScalingFromVector(scale);
	}

	[[nodiscard]] 
	inline const XMMATRIX XM_CALLCONV 
		XMMatrixInverseScaling(FXMVECTOR scale) noexcept {

		return XMMatrixScaling(XMVectorReciprocal(scale));
	}

	[[nodiscard]] 
	inline const XMMATRIX XM_CALLCONV 
		XMMatrixAffineTransformation(FXMVECTOR scale, 
			                         FXMVECTOR rotation, 
			                         FXMVECTOR translation) noexcept {

		// Scale . Rotation . Translation
		auto transformation  = XMMatrixRotationRollPitchYaw(rotation);
		transformation.r[0] *= XMVectorGetX(scale);
		transformation.r[1] *= XMVectorGetY(scale);
		transformation.r[2] *= XMVectorGetZ(scale);
		transformation.r[3]  = XMVectorSetW(translation, 1.0f);
		return transformation;
	}

	[[nodiscard]] 
	inline const XMMATRIX XM_CALLCONV 
		XMMatrixInverseAffineTransformation(FXMVECTOR scale, 
			                                FXMVECTOR rotation, 
			                                FXMVECTOR translation) noexcept {

		// Translation . Rotation . Scale
		auto transformation  = XMMatrixInverseRotationRollPitchYaw(rotation);
		const auto t         = XMVector3TransformCoord(-translation, transformation);
		const auto s         = XMVectorSetW(XMVectorReciprocal(scale), 1.0f);
		transformation.r[0] *= s;
		transformation.r[1] *= s;
		transformation.r[2] *= s;
		transformation.r[3]  = s * t;
		return transformation;
	}

	[[nodiscard]] 
	inline const XMMATRIX XM_CALLCONV 
		XMMatrixAffineTransformation2D(FXMVECTOR scale, 
			                           F32       rotation, 
			                           FXMVECTOR translation) noexcept {

		// Scale . Rotation . Translation
		auto transformation  = XMMatrixRotationZ(rotation);
		transformation.r[0] *= XMVectorGetX(scale);
		transformation.r[1] *= XMVectorGetY(scale);
		transformation.r[3]  = XMVectorSetW(translation, 1.0f);
		return transformation;
	}

	[[nodiscard]] 
	inline const XMMATRIX XM_CALLCONV 
		XMMatrixOffsetAffineTransformation2D(FXMVECTOR offset,
			                                 FXMVECTOR scale, 
			                                 F32       rotation,
			                                 FXMVECTOR translation) noexcept {

		// Inverse Offset Translation . Scale . Rotation . Translation
		auto transformation = XMMatrixAffineTransformation2D(scale,
			                                                 rotation, 
			                                                 translation);
		transformation.r[3] = XMVector3TransformCoord(-offset, transformation);
		return transformation;
	}
}