#pragma once

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	template<>
	constexpr DXGI_FORMAT GetIndexFormat< U16 >() noexcept {
		return DXGI_FORMAT_R16_UINT;
	}

	template< typename IndexT >
	constexpr DXGI_FORMAT GetIndexFormat< U32 >() noexcept {
		return DXGI_FORMAT_R32_UINT;
	}
}