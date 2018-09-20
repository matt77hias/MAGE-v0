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

	//-------------------------------------------------------------------------
	// Type Checks
	//-------------------------------------------------------------------------
	#pragma region

	static_assert(sizeof(F32x2) == sizeof(XMFLOAT2),
				  "MAGE/DirectXMath type mismatch");

	static_assert(sizeof(F32x3) == sizeof(XMFLOAT3),
				  "MAGE/DirectXMath type mismatch");

	static_assert(sizeof(F32x4) == sizeof(XMFLOAT4),
				  "MAGE/DirectXMath type mismatch");

	static_assert(sizeof(F32x2A) == sizeof(XMFLOAT2A),
				  "MAGE/DirectXMath type mismatch");

	static_assert(sizeof(F32x3A) == sizeof(XMFLOAT3A),
				  "MAGE/DirectXMath type mismatch");

	static_assert(sizeof(F32x4A) == sizeof(XMFLOAT4A),
				  "MAGE/DirectXMath type mismatch");

	static_assert(sizeof(S32x2) == sizeof(XMINT2),
				  "MAGE/DirectXMath type mismatch");

	static_assert(sizeof(S32x3) == sizeof(XMINT3),
				  "MAGE/DirectXMath type mismatch");

	static_assert(sizeof(S32x4) == sizeof(XMINT4),
				  "MAGE/DirectXMath type mismatch");

	static_assert(sizeof(U32x2) == sizeof(XMUINT2),
				  "MAGE/DirectXMath type mismatch");

	static_assert(sizeof(U32x3) == sizeof(XMUINT3),
				  "MAGE/DirectXMath type mismatch");

	static_assert(sizeof(U32x4) == sizeof(XMUINT4),
				  "MAGE/DirectXMath type mismatch");

	#pragma endregion

	//-------------------------------------------------------------------------
	// Loading Vectors
	//-------------------------------------------------------------------------
	#pragma region

	[[nodiscard]]
	inline const XMVECTOR XM_CALLCONV XMLoad(F32 src) noexcept {
		return XMLoadFloat(&src);
	}

	[[nodiscard]]
	inline const XMVECTOR XM_CALLCONV XMLoad(const F32x2& src) noexcept {
		return XMLoadFloat2(reinterpret_cast< const XMFLOAT2* >(&src));
	}

	[[nodiscard]]
	inline const XMVECTOR XM_CALLCONV XMLoad(const F32x3& src) noexcept {
		return XMLoadFloat3(reinterpret_cast< const XMFLOAT3* >(&src));
	}

	[[nodiscard]]
	inline const XMVECTOR XM_CALLCONV XMLoad(const F32x4& src) noexcept {
		return XMLoadFloat4(reinterpret_cast< const XMFLOAT4* >(&src));
	}

	[[nodiscard]]
	inline const XMVECTOR XM_CALLCONV XMLoad(const F32x2A& src) noexcept {
		return XMLoadFloat2A(reinterpret_cast< const XMFLOAT2A* >(&src));
	}

	[[nodiscard]]
	inline const XMVECTOR XM_CALLCONV XMLoad(const F32x3A& src) noexcept {
		return XMLoadFloat3A(reinterpret_cast< const XMFLOAT3A* >(&src));
	}

	[[nodiscard]]
	inline const XMVECTOR XM_CALLCONV XMLoad(const F32x4A& src) noexcept {
		return XMLoadFloat4A(reinterpret_cast< const XMFLOAT4A* >(&src));
	}

	[[nodiscard]]
	inline const XMVECTOR XM_CALLCONV XMLoad(const S32x2& src) noexcept {
		return XMLoadSInt2(reinterpret_cast< const XMINT2* >(&src));
	}

	[[nodiscard]]
	inline const XMVECTOR XM_CALLCONV XMLoad(const S32x3& src) noexcept {
		return XMLoadSInt3(reinterpret_cast< const XMINT3* >(&src));
	}

	[[nodiscard]]
	inline const XMVECTOR XM_CALLCONV XMLoad(const S32x4& src) noexcept {
		return XMLoadSInt4(reinterpret_cast< const XMINT4* >(&src));
	}

	[[nodiscard]]
	inline const XMVECTOR XM_CALLCONV XMLoad(U32 src) noexcept {
		return XMLoadInt(&src);
	}

	[[nodiscard]]
	inline const XMVECTOR XM_CALLCONV XMLoad(const U32x2& src) noexcept {
		return XMLoadUInt2(reinterpret_cast< const XMUINT2* >(&src));
	}

	[[nodiscard]]
	inline const XMVECTOR XM_CALLCONV XMLoad(const U32x3& src) noexcept {
		return XMLoadUInt3(reinterpret_cast< const XMUINT3* >(&src));
	}

	[[nodiscard]]
	inline const XMVECTOR XM_CALLCONV XMLoad(const U32x4& src) noexcept {
		return XMLoadUInt4(reinterpret_cast< const XMUINT4* >(&src));
	}

	[[nodiscard]]
	inline const XMVECTOR XM_CALLCONV XMLoad(const RECT& src) noexcept {
		const auto v = XMLoadInt4(reinterpret_cast< const U32* >(&src));
		return XMConvertVectorIntToFloat(v, 0);
	}

	#pragma endregion

	//-------------------------------------------------------------------------
	// Storing Vectors
	//-------------------------------------------------------------------------
	#pragma region

	template< typename T >
	[[nodiscard]]
	const T XM_CALLCONV XMStore(FXMVECTOR src) noexcept;

	template<>
	[[nodiscard]]
	inline const F32 XM_CALLCONV XMStore(FXMVECTOR src) noexcept {
		F32 dst;
		XMStoreFloat(&dst, src);
		return dst;
	}

	template<>
	[[nodiscard]]
	inline const F32x2 XM_CALLCONV XMStore(FXMVECTOR src) noexcept {
		F32x2 dst;
		XMStoreFloat2(reinterpret_cast< XMFLOAT2* >(&dst), src);
		return dst;
	}

	template<>
	[[nodiscard]]
	inline const F32x3 XM_CALLCONV XMStore(FXMVECTOR src) noexcept {
		F32x3 dst;
		XMStoreFloat3(reinterpret_cast< XMFLOAT3* >(&dst), src);
		return dst;
	}

	template<>
	[[nodiscard]]
	inline const F32x4 XM_CALLCONV XMStore(FXMVECTOR src) noexcept {
		F32x4 dst;
		XMStoreFloat4(reinterpret_cast< XMFLOAT4* >(&dst), src);
		return dst;
	}

	template<>
	[[nodiscard]]
	inline const F32x2A XM_CALLCONV XMStore(FXMVECTOR src) noexcept {
		F32x2A dst;
		XMStoreFloat2A(reinterpret_cast< XMFLOAT2A* >(&dst), src);
		return dst;
	}

	template<>
	[[nodiscard]]
	inline const F32x3A XM_CALLCONV XMStore(FXMVECTOR src) noexcept {
		F32x3A dst;
		XMStoreFloat3A(reinterpret_cast< XMFLOAT3A* >(&dst), src);
		return dst;
	}

	template<>
	[[nodiscard]]
	inline const F32x4A XM_CALLCONV XMStore(FXMVECTOR src) noexcept {
		F32x4A dst;
		XMStoreFloat4A(reinterpret_cast< XMFLOAT4A* >(&dst), src);
		return dst;
	}

	template<>
	[[nodiscard]]
	inline const S32x2 XM_CALLCONV XMStore(FXMVECTOR src) noexcept {
		S32x2 dst;
		XMStoreSInt2(reinterpret_cast< XMINT2* >(&dst), src);
		return dst;
	}

	template<>
	[[nodiscard]]
	inline const S32x3 XM_CALLCONV XMStore(FXMVECTOR src) noexcept {
		S32x3 dst;
		XMStoreSInt3(reinterpret_cast< XMINT3* >(&dst), src);
		return dst;
	}

	template<>
	[[nodiscard]]
	inline const S32x4 XM_CALLCONV XMStore(FXMVECTOR src) noexcept {
		S32x4 dst;
		XMStoreSInt4(reinterpret_cast< XMINT4* >(&dst), src);
		return dst;
	}

	template<>
	[[nodiscard]]
	inline const U32 XM_CALLCONV XMStore(FXMVECTOR src) noexcept {
		U32 dst;
		XMStoreInt(&dst, src);
		return dst;
	}

	template<>
	[[nodiscard]]
	inline const U32x2 XM_CALLCONV XMStore(FXMVECTOR src) noexcept {
		U32x2 dst;
		XMStoreUInt2(reinterpret_cast< XMUINT2* >(&dst), src);
		return dst;
	}

	template<>
	[[nodiscard]]
	inline const U32x3 XM_CALLCONV XMStore(FXMVECTOR src) noexcept {
		U32x3 dst;
		XMStoreUInt3(reinterpret_cast< XMUINT3* >(&dst), src);
		return dst;
	}

	template<>
	[[nodiscard]]
	inline const U32x4 XM_CALLCONV XMStore(FXMVECTOR src) noexcept {
		U32x4 dst;
		XMStoreUInt4(reinterpret_cast< XMUINT4* >(&dst), src);
		return dst;
	}

	#pragma endregion
}