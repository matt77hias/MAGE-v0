#pragma once

//-----------------------------------------------------------------------------
// System Includes
//-----------------------------------------------------------------------------
#pragma region

#include "type\types.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// System Includes
//-----------------------------------------------------------------------------
#pragma region

#include <fmt\format.h>

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace fmt {

	template< typename T, size_t A >
	struct formatter< mage::Array< T, 2u, A > > {

		template< typename ParseContextT >
		constexpr auto parse(ParseContextT &ctx) {
			return ctx.begin();
		}

		template< typename FormatContextT >
		auto format(const mage::Array< T, 2u, A >& a, FormatContextT &ctx) {
			const auto [x, y] = a;
			return format_to(ctx.begin(), "{} {}", x, y);
		}
	};

	template< typename T, size_t A >
	struct formatter< mage::Array< T, 3u, A > > {

		template< typename ParseContextT >
		constexpr auto parse(ParseContextT &ctx) {
			return ctx.begin();
		}

		template< typename FormatContextT >
		auto format(const mage::Array< T, 3u, A >& a, FormatContextT &ctx) {
			const auto [x, y, z] = a;
			return format_to(ctx.begin(), "{} {} {}", x, y, z);
		}
	};

	template< typename T, size_t A >
	struct formatter< mage::Array< T, 4u, A > > {

		template< typename ParseContextT >
		constexpr auto parse(ParseContextT &ctx) {
			return ctx.begin();
		}

		template< typename FormatContextT >
		auto format(const mage::Array< T, 4u, A >& a, FormatContextT &ctx) {
			const auto [x, y, z, w] = a;
			return format_to(ctx.begin(), "{} {} {} {}", x, y, z, w);
		}
	};
}