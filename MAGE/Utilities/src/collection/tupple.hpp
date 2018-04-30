#pragma once

//-----------------------------------------------------------------------------
// System Includes
//-----------------------------------------------------------------------------
#pragma region

#include <array>
#include <tuple>
#include <utility>

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	namespace details {

		template< typename T, size_t...I >
		constexpr decltype(auto) ArrayToTupple(const std::array< T, sizeof...(I) >& a, 
											   std::index_sequence< I... >) noexcept {
			return std::make_tuple(a[I]...);
		}
	}

	template< typename T, size_t N >
	constexpr decltype(auto) ArrayToTupple(const std::array< T, N >& a) noexcept {
		return details::ArrayToTupple(a, std::make_index_sequence< N >());
	}

	template< typename... Ts >
	constexpr decltype(auto) ArgsToTuple(Ts&&... args) noexcept {
		return std::make_tuple(std::forward< Ts >(args)...);
	}
}