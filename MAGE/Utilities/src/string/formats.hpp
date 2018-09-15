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

	template<>
	struct formatter< mage::F32x2 > {

		template< typename ParseContextT >
		constexpr auto parse(ParseContextT &ctx) {
			return ctx.begin();
		}

		template< typename FormatContextT >
		auto format(const mage::F32x2& a, FormatContextT &ctx) {
			const auto [x, y] = a;
			return format_to(ctx.begin(), "{} {}", x, y);
		}
	};

	template<>
	struct formatter< mage::F32x3 > {

		template< typename ParseContextT >
		constexpr auto parse(ParseContextT &ctx) {
			return ctx.begin();
		}

		template< typename FormatContextT >
		auto format(const mage::F32x3& a, FormatContextT &ctx) {
			const auto [x, y, z] = a;
			return format_to(ctx.begin(), "{} {} {}", x, y, z);
		}
	};

	template<>
	struct formatter< mage::F32x4 > {

		template< typename ParseContextT >
		constexpr auto parse(ParseContextT &ctx) {
			return ctx.begin();
		}

		template< typename FormatContextT >
		auto format(const mage::F32x4& a, FormatContextT &ctx) {
			const auto [x, y, z, w] = a;
			return format_to(ctx.begin(), "{} {} {} {}", x, y, z, w);
		}
	};

	template<>
	struct formatter< mage::F64x2 > {

		template< typename ParseContextT >
		constexpr auto parse(ParseContextT &ctx) {
			return ctx.begin();
		}

		template< typename FormatContextT >
		auto format(const mage::F64x2& a, FormatContextT &ctx) {
			const auto [x, y] = a;
			return format_to(ctx.begin(), "{} {}", x, y);
		}
	};

	template<>
	struct formatter< mage::F64x3 > {

		template< typename ParseContextT >
		constexpr auto parse(ParseContextT &ctx) {
			return ctx.begin();
		}

		template< typename FormatContextT >
		auto format(const mage::F64x3& a, FormatContextT &ctx) {
			const auto [x, y, z] = a;
			return format_to(ctx.begin(), "{} {} {}", x, y, z);
		}
	};

	template<>
	struct formatter< mage::F64x4 > {

		template< typename ParseContextT >
		constexpr auto parse(ParseContextT &ctx) {
			return ctx.begin();
		}

		template< typename FormatContextT >
		auto format(const mage::F32x4& a, FormatContextT &ctx) {
			const auto [x, y, z, w] = a;
			return format_to(ctx.begin(), "{} {} {} {}", x, y, z, w);
		}
	};

	template<>
	struct formatter< mage::S8x2 > {

		template< typename ParseContextT >
		constexpr auto parse(ParseContextT &ctx) {
			return ctx.begin(); 
		}

		template< typename FormatContextT >
		auto format(const mage::S8x2& a, FormatContextT &ctx) {
			const auto [x, y] = a;
			return format_to(ctx.begin(), "{} {}", x, y);
		}
	};

	template<>
	struct formatter< mage::S8x3 > {

		template< typename ParseContextT >
		constexpr auto parse(ParseContextT &ctx) {
			return ctx.begin();
		}

		template< typename FormatContextT >
		auto format(const mage::S8x3& a, FormatContextT &ctx) {
			const auto [x, y, z] = a;
			return format_to(ctx.begin(), "{} {} {}", x, y, z);
		}
	};

	template<>
	struct formatter< mage::S8x4 > {

		template< typename ParseContextT >
		constexpr auto parse(ParseContextT &ctx) {
			return ctx.begin();
		}

		template< typename FormatContextT >
		auto format(const mage::S8x4& a, FormatContextT &ctx) {
			const auto [x, y, z, w] = a;
			return format_to(ctx.begin(), "{} {} {} {}", x, y, z, w);
		}
	};

	template<>
	struct formatter< mage::S16x2 > {

		template< typename ParseContextT >
		constexpr auto parse(ParseContextT &ctx) {
			return ctx.begin();
		}

		template< typename FormatContextT >
		auto format(const mage::S16x2& a, FormatContextT &ctx) {
			const auto [x, y] = a;
			return format_to(ctx.begin(), "{} {}", x, y);
		}
	};

	template<>
	struct formatter< mage::S16x3 > {

		template< typename ParseContextT >
		constexpr auto parse(ParseContextT &ctx) {
			return ctx.begin();
		}

		template< typename FormatContextT >
		auto format(const mage::S16x3& a, FormatContextT &ctx) {
			const auto [x, y, z] = a;
			return format_to(ctx.begin(), "{} {} {}", x, y, z);
		}
	};

	template<>
	struct formatter< mage::S16x4 > {

		template< typename ParseContextT >
		constexpr auto parse(ParseContextT &ctx) {
			return ctx.begin();
		}

		template< typename FormatContextT >
		auto format(const mage::S16x4& a, FormatContextT &ctx) {
			const auto [x, y, z, w] = a;
			return format_to(ctx.begin(), "{} {} {} {}", x, y, z, w);
		}
	};

	template<>
	struct formatter< mage::S32x2 > {

		template< typename ParseContextT >
		constexpr auto parse(ParseContextT &ctx) {
			return ctx.begin();
		}

		template< typename FormatContextT >
		auto format(const mage::S32x2& a, FormatContextT &ctx) {
			const auto [x, y] = a;
			return format_to(ctx.begin(), "{} {}", x, y);
		}
	};

	template<>
	struct formatter< mage::S32x3 > {

		template< typename ParseContextT >
		constexpr auto parse(ParseContextT &ctx) {
			return ctx.begin();
		}

		template< typename FormatContextT >
		auto format(const mage::S32x3& a, FormatContextT &ctx) {
			const auto [x, y, z] = a;
			return format_to(ctx.begin(), "{} {} {}", x, y, z);
		}
	};

	template<>
	struct formatter< mage::S32x4 > {

		template< typename ParseContextT >
		constexpr auto parse(ParseContextT &ctx) {
			return ctx.begin();
		}

		template< typename FormatContextT >
		auto format(const mage::S32x4& a, FormatContextT &ctx) {
			const auto [x, y, z, w] = a;
			return format_to(ctx.begin(), "{} {} {} {}", x, y, z, w);
		}
	};

	template<>
	struct formatter< mage::S64x2 > {

		template< typename ParseContextT >
		constexpr auto parse(ParseContextT &ctx) {
			return ctx.begin();
		}

		template< typename FormatContextT >
		auto format(const mage::S64x2& a, FormatContextT &ctx) {
			const auto [x, y] = a;
			return format_to(ctx.begin(), "{} {}", x, y);
		}
	};

	template<>
	struct formatter< mage::S64x3 > {

		template< typename ParseContextT >
		constexpr auto parse(ParseContextT &ctx) {
			return ctx.begin();
		}

		template< typename FormatContextT >
		auto format(const mage::S64x3& a, FormatContextT &ctx) {
			const auto [x, y, z] = a;
			return format_to(ctx.begin(), "{} {} {}", x, y, z);
		}
	};

	template<>
	struct formatter< mage::S64x4 > {

		template< typename ParseContextT >
		constexpr auto parse(ParseContextT &ctx) {
			return ctx.begin();
		}

		template< typename FormatContextT >
		auto format(const mage::S32x4& a, FormatContextT &ctx) {
			const auto [x, y, z, w] = a;
			return format_to(ctx.begin(), "{} {} {} {}", x, y, z, w);
		}
	};

	template<>
	struct formatter< mage::U8x2 > {

		template< typename ParseContextT >
		constexpr auto parse(ParseContextT &ctx) {
			return ctx.begin(); 
		}

		template< typename FormatContextT >
		auto format(const mage::U8x2& a, FormatContextT &ctx) {
			const auto [x, y] = a;
			return format_to(ctx.begin(), "{} {}", x, y);
		}
	};

	template<>
	struct formatter< mage::U8x3 > {

		template< typename ParseContextT >
		constexpr auto parse(ParseContextT &ctx) {
			return ctx.begin();
		}

		template< typename FormatContextT >
		auto format(const mage::U8x3& a, FormatContextT &ctx) {
			const auto [x, y, z] = a;
			return format_to(ctx.begin(), "{} {} {}", x, y, z);
		}
	};

	template<>
	struct formatter< mage::U8x4 > {

		template< typename ParseContextT >
		constexpr auto parse(ParseContextT &ctx) {
			return ctx.begin();
		}

		template< typename FormatContextT >
		auto format(const mage::U8x4& a, FormatContextT &ctx) {
			const auto [x, y, z, w] = a;
			return format_to(ctx.begin(), "{} {} {} {}", x, y, z, w);
		}
	};

	template<>
	struct formatter< mage::U16x2 > {

		template< typename ParseContextT >
		constexpr auto parse(ParseContextT &ctx) {
			return ctx.begin();
		}

		template< typename FormatContextT >
		auto format(const mage::U16x2& a, FormatContextT &ctx) {
			const auto [x, y] = a;
			return format_to(ctx.begin(), "{} {}", x, y);
		}
	};

	template<>
	struct formatter< mage::U16x3 > {

		template< typename ParseContextT >
		constexpr auto parse(ParseContextT &ctx) {
			return ctx.begin();
		}

		template< typename FormatContextT >
		auto format(const mage::U16x3& a, FormatContextT &ctx) {
			const auto [x, y, z] = a;
			return format_to(ctx.begin(), "{} {} {}", x, y, z);
		}
	};

	template<>
	struct formatter< mage::U16x4 > {

		template< typename ParseContextT >
		constexpr auto parse(ParseContextT &ctx) {
			return ctx.begin();
		}

		template< typename FormatContextT >
		auto format(const mage::U16x4& a, FormatContextT &ctx) {
			const auto [x, y, z, w] = a;
			return format_to(ctx.begin(), "{} {} {} {}", x, y, z, w);
		}
	};

	template<>
	struct formatter< mage::U32x2 > {

		template< typename ParseContextT >
		constexpr auto parse(ParseContextT &ctx) {
			return ctx.begin();
		}

		template< typename FormatContextT >
		auto format(const mage::U32x2& a, FormatContextT &ctx) {
			const auto [x, y] = a;
			return format_to(ctx.begin(), "{} {}", x, y);
		}
	};

	template<>
	struct formatter< mage::U32x3 > {

		template< typename ParseContextT >
		constexpr auto parse(ParseContextT &ctx) {
			return ctx.begin();
		}

		template< typename FormatContextT >
		auto format(const mage::U32x3& a, FormatContextT &ctx) {
			const auto [x, y, z] = a;
			return format_to(ctx.begin(), "{} {} {}", x, y, z);
		}
	};

	template<>
	struct formatter< mage::U32x4 > {

		template< typename ParseContextT >
		constexpr auto parse(ParseContextT &ctx) {
			return ctx.begin();
		}

		template< typename FormatContextT >
		auto format(const mage::U32x4& a, FormatContextT &ctx) {
			const auto [x, y, z, w] = a;
			return format_to(ctx.begin(), "{} {} {} {}", x, y, z, w);
		}
	};

	template<>
	struct formatter< mage::U64x2 > {

		template< typename ParseContextT >
		constexpr auto parse(ParseContextT &ctx) {
			return ctx.begin();
		}

		template< typename FormatContextT >
		auto format(const mage::U64x2& a, FormatContextT &ctx) {
			const auto [x, y] = a;
			return format_to(ctx.begin(), "{} {}", x, y);
		}
	};

	template<>
	struct formatter< mage::U64x3 > {

		template< typename ParseContextT >
		constexpr auto parse(ParseContextT &ctx) {
			return ctx.begin();
		}

		template< typename FormatContextT >
		auto format(const mage::U64x3& a, FormatContextT &ctx) {
			const auto [x, y, z] = a;
			return format_to(ctx.begin(), "{} {} {}", x, y, z);
		}
	};

	template<>
	struct formatter< mage::U64x4 > {

		template< typename ParseContextT >
		constexpr auto parse(ParseContextT &ctx) {
			return ctx.begin();
		}

		template< typename FormatContextT >
		auto format(const mage::U32x4& a, FormatContextT &ctx) {
			const auto [x, y, z, w] = a;
			return format_to(ctx.begin(), "{} {} {} {}", x, y, z, w);
		}
	};
}