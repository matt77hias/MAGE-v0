#pragma once

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	template<>
	[[nodiscard]] constexpr DXGI_FORMAT GetIndexFormat< U16 >() noexcept {
		return DXGI_FORMAT_R16_UINT;
	}

	template< typename IndexT >
	[[nodiscard]] constexpr DXGI_FORMAT GetIndexFormat< U32 >() noexcept {
		return DXGI_FORMAT_R32_UINT;
	}
}