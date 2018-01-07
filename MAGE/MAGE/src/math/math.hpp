#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "utils\type\types.hpp"

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

	//-------------------------------------------------------------------------
	// DirectXMath Extensions
	//-------------------------------------------------------------------------
	#pragma region

	inline const XMMATRIX XM_CALLCONV XMMatrixTranslation(
		FXMVECTOR translation) noexcept {

		return XMMatrixTranslationFromVector(translation);
	}

	inline const XMMATRIX XM_CALLCONV XMMatrixInverseTranslation(
		FXMVECTOR translation) noexcept {
		
		return XMMatrixTranslation(-translation);
	}

	inline const XMVECTOR XM_CALLCONV XMQuaternionRotationRollPitchYaw(
		FXMVECTOR rotation) noexcept {

		return XMQuaternionRotationRollPitchYawFromVector(rotation);
	}

	inline const XMVECTOR XM_CALLCONV XMQuaternionInverseRotationRollPitchYaw(
		FXMVECTOR rotation) noexcept {

		return XMQuaternionInverse(XMQuaternionRotationRollPitchYaw(rotation));
	}

	inline const XMMATRIX XM_CALLCONV XMMatrixRotationRollPitchYaw(
		FXMVECTOR rotation) noexcept {

		return XMMatrixRotationRollPitchYawFromVector(rotation);
	}

	inline const XMMATRIX XM_CALLCONV XMMatrixInverseRotationRollPitchYaw(
		FXMVECTOR rotation) noexcept {

		return XMMatrixTranspose(XMMatrixRotationRollPitchYaw(rotation));
	}

	inline const XMMATRIX XM_CALLCONV XMMatrixScaling(
		FXMVECTOR scale) noexcept {

		return XMMatrixScalingFromVector(scale);
	}

	inline const XMMATRIX XM_CALLCONV XMMatrixInverseScaling(
		FXMVECTOR scale) noexcept {

		return XMMatrixScaling(XMVectorReciprocal(scale));
	}

	inline const XMMATRIX XM_CALLCONV XMMatrixAffineTransformation(
		FXMVECTOR scale, FXMVECTOR rotation, FXMVECTOR translation) noexcept {

		// Scale . Rotation . Translation
		XMMATRIX transformation = XMMatrixRotationRollPitchYaw(rotation);
		transformation.r[0]    *= XMVectorGetX(scale);
		transformation.r[1]    *= XMVectorGetY(scale);
		transformation.r[2]    *= XMVectorGetZ(scale);
		transformation.r[3]     = XMVectorSetW(translation, 1.0f);
		return transformation;
	}

	inline const XMMATRIX XM_CALLCONV XMMatrixInverseAffineTransformation(
		FXMVECTOR scale, FXMVECTOR rotation, FXMVECTOR translation) noexcept {

		// Translation . Rotation . Scale
		XMMATRIX transformation = XMMatrixInverseRotationRollPitchYaw(rotation);
		transformation.r[3]     = XMVector3TransformCoord(-translation, transformation);
		const XMVECTOR v        = XMVectorSetW(XMVectorReciprocal(scale), 1.0f);
		transformation.r[0]    *= v;
		transformation.r[1]    *= v;
		transformation.r[2]    *= v;
		transformation.r[3]    *= v;
		return transformation;
	}

	#pragma endregion

	//-------------------------------------------------------------------------
	// Type Checks
	//-------------------------------------------------------------------------
	#pragma region

	static_assert(sizeof(F32x2) == sizeof(XMFLOAT2),
		"MAGE/DirectX type mismatch");

	static_assert(sizeof(F32x3) == sizeof(XMFLOAT3),
		"MAGE/DirectX type mismatch");

	static_assert(sizeof(F32x4) == sizeof(XMFLOAT4),
		"MAGE/DirectX type mismatch");

	static_assert(sizeof(F32x2A) == sizeof(XMFLOAT2A),
		"MAGE/DirectX type mismatch");

	static_assert(sizeof(F32x3A) == sizeof(XMFLOAT3A),
		"MAGE/DirectX type mismatch");

	static_assert(sizeof(F32x4A) == sizeof(XMFLOAT4A),
		"MAGE/DirectX type mismatch");

	static_assert(sizeof(S32x2) == sizeof(XMINT2),
		"MAGE/DirectX type mismatch");

	static_assert(sizeof(S32x3) == sizeof(XMINT3),
		"MAGE/DirectX type mismatch");

	static_assert(sizeof(S32x4) == sizeof(XMINT4),
		"MAGE/DirectX type mismatch");

	static_assert(sizeof(U32x2) == sizeof(XMUINT2),
		"MAGE/DirectX type mismatch");

	static_assert(sizeof(U32x3) == sizeof(XMUINT3),
		"MAGE/DirectX type mismatch");

	static_assert(sizeof(U32x4) == sizeof(XMUINT4),
		"MAGE/DirectX type mismatch");

	#pragma endregion

	//-------------------------------------------------------------------------
	// Loading Floating Point Vectors
	//-------------------------------------------------------------------------
	#pragma region

	inline const XMVECTOR XM_CALLCONV XMLoadFloat2(const F32x2 *src) noexcept {
		return XMLoadFloat2(reinterpret_cast< const XMFLOAT2 * >(src));
	}

	inline const XMVECTOR XM_CALLCONV XMLoadFloat3(const F32x3 *src) noexcept {
		return XMLoadFloat3(reinterpret_cast< const XMFLOAT3 * >(src));
	}

	inline const XMVECTOR XM_CALLCONV XMLoadFloat4(const F32x4 *src) noexcept {
		return XMLoadFloat4(reinterpret_cast< const XMFLOAT4 * >(src));
	}
	
	inline const XMVECTOR XM_CALLCONV XMLoadFloat2A(const F32x2A *src) noexcept {
		return XMLoadFloat2A(reinterpret_cast< const XMFLOAT2A * >(src));
	}

	inline const XMVECTOR XM_CALLCONV XMLoadFloat3A(const F32x3A *src) noexcept {
		return XMLoadFloat3A(reinterpret_cast< const XMFLOAT3A * >(src));
	}

	inline const XMVECTOR XM_CALLCONV XMLoadFloat4A(const F32x4A *src) noexcept {
		return XMLoadFloat4A(reinterpret_cast< const XMFLOAT4A * >(src));
	}

	#pragma endregion

	//-------------------------------------------------------------------------
	// Loading Signed Integer Vectors
	//-------------------------------------------------------------------------
	#pragma region

	inline const XMVECTOR XM_CALLCONV XMLoadSInt2(const S32x2 *src) noexcept {
		return XMLoadSInt2(reinterpret_cast< const XMINT2 * >(src));
	}

	inline const XMVECTOR XM_CALLCONV XMLoadSInt3(const S32x3 *src) noexcept {
		return XMLoadSInt3(reinterpret_cast< const XMINT3 * >(src));
	}

	inline const XMVECTOR XM_CALLCONV XMLoadSInt4(const S32x4 *src) noexcept {
		return XMLoadSInt4(reinterpret_cast< const XMINT4 * >(src));
	}

	#pragma endregion

	//-------------------------------------------------------------------------
	// Loading Unsigned Integer Vectors
	//-------------------------------------------------------------------------
	#pragma region

	inline const XMVECTOR XM_CALLCONV XMLoadUInt2(const U32x2 *src) noexcept {
		return XMLoadUInt2(reinterpret_cast< const XMUINT2 * >(src));
	}
	
	inline const XMVECTOR XM_CALLCONV XMLoadUInt3(const U32x3 *src) noexcept {
		return XMLoadUInt3(reinterpret_cast< const XMUINT3 * >(src));
	}
	
	inline const XMVECTOR XM_CALLCONV XMLoadUInt4(const U32x4 *src) noexcept {
		return XMLoadUInt4(reinterpret_cast< const XMUINT4 * >(src));
	}

	#pragma endregion

	//-------------------------------------------------------------------------
	// Storing Floating Point Vectors
	//-------------------------------------------------------------------------
	#pragma region

	inline void XM_CALLCONV XMStoreFloat2(F32x2 *dst, FXMVECTOR v) noexcept {
		XMStoreFloat2(reinterpret_cast< XMFLOAT2 * >(dst), v);
	}

	inline void XM_CALLCONV XMStoreFloat3(F32x3 *dst, FXMVECTOR v) noexcept {
		XMStoreFloat3(reinterpret_cast< XMFLOAT3 * >(dst), v);
	}

	inline void XM_CALLCONV XMStoreFloat4(F32x4 *dst, FXMVECTOR v) noexcept {
		XMStoreFloat4(reinterpret_cast< XMFLOAT4 * >(dst), v);
	}
	
	inline void XM_CALLCONV XMStoreFloat2A(F32x2A *dst, FXMVECTOR v) noexcept {
		XMStoreFloat2A(reinterpret_cast< XMFLOAT2A * >(dst), v);
	}
	
	inline void XM_CALLCONV XMStoreFloat3A(F32x3A *dst, FXMVECTOR v) noexcept {
		XMStoreFloat3A(reinterpret_cast< XMFLOAT3A * >(dst), v);
	}
	
	inline void XM_CALLCONV XMStoreFloat4A(F32x4A *dst, FXMVECTOR v) noexcept {
		XMStoreFloat4A(reinterpret_cast< XMFLOAT4A * >(dst), v);
	}

	#pragma endregion

	//-------------------------------------------------------------------------
	// Storing Signed Integer Vectors
	//-------------------------------------------------------------------------
	#pragma region

	inline void XM_CALLCONV XMStoreSInt2(S32x2 *dst, FXMVECTOR v) noexcept {
		XMStoreSInt2(reinterpret_cast< XMINT2 * >(dst), v);
	}

	inline void XM_CALLCONV XMStoreSInt3(S32x3 *dst, FXMVECTOR v) noexcept {
		XMStoreSInt3(reinterpret_cast< XMINT3 * >(dst), v);
	}

	inline void XM_CALLCONV XMStoreSInt4(S32x4 *dst, FXMVECTOR v) noexcept {
		XMStoreSInt4(reinterpret_cast< XMINT4 * >(dst), v);
	}

	#pragma endregion

	//-------------------------------------------------------------------------
	// Storing Unsigned Integer Vectors
	//-------------------------------------------------------------------------
	#pragma region

	inline void XM_CALLCONV XMStoreUInt2(U32x2 *dst, FXMVECTOR v) noexcept {
		XMStoreUInt2(reinterpret_cast< XMUINT2 * >(dst), v);
	}

	inline void XM_CALLCONV XMStoreUInt3(U32x3 *dst, FXMVECTOR v) noexcept {
		XMStoreUInt3(reinterpret_cast< XMUINT3 * >(dst), v);
	}

	inline void XM_CALLCONV XMStoreUInt4(U32x4 *dst, FXMVECTOR v) noexcept {
		XMStoreUInt4(reinterpret_cast< XMUINT4 * >(dst), v);
	}

	#pragma endregion
}