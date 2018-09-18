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

#include <filesystem>
#include <fmt\format.h>

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace fmt {

	template<>
	struct formatter< std::wstring_view, char > {

		template< typename ParseContextT >
		constexpr auto parse(ParseContextT& ctx) {
			return ctx.begin();
		}

		template< typename FormatContextT >
		auto format(const std::wstring_view& wstr, FormatContextT& ctx) {
			const internal::utf16_to_utf8 str(wstr);
			return format_to(ctx.begin(), str.c_str());
		}
	};

	template<>
	struct formatter< std::wstring, char > {

		template< typename ParseContextT >
		constexpr auto parse(ParseContextT& ctx) {
			return ctx.begin();
		}

		template< typename FormatContextT >
		auto format(const std::wstring& wstr, FormatContextT& ctx) {
			const internal::utf16_to_utf8 str(wstr);
			return format_to(ctx.begin(), str.c_str());
		}
	};

	template<>
	struct formatter< std::filesystem::path, char > {

		template< typename ParseContextT >
		constexpr auto parse(ParseContextT& ctx) {
			return ctx.begin();
		}

		template< typename FormatContextT >
		auto format(const std::filesystem::path& path, FormatContextT& ctx) {
			const internal::utf16_to_utf8 str(path.c_str());
			return format_to(ctx.begin(), str.c_str());
		}
	};

	template<>
	struct formatter< std::string_view, wchar_t > {

		template< typename ParseContextT >
		constexpr auto parse(ParseContextT& ctx) {
			return ctx.begin();
		}

		template< typename FormatContextT >
		auto format(const std::string_view& str, FormatContextT& ctx) {
			const internal::utf8_to_utf16 wstr(str);
			return format_to(ctx.begin(), wstr.c_str());
		}
	};

	template<>
	struct formatter< std::string, wchar_t > {

		template< typename ParseContextT >
		constexpr auto parse(ParseContextT& ctx) {
			return ctx.begin();
		}

		template< typename FormatContextT >
		auto format(const std::string& str, FormatContextT& ctx) {
			const internal::utf8_to_utf16 wstr(str);
			return format_to(ctx.begin(), wstr.c_str());
		}
	};

	template<>
	struct formatter< std::filesystem::path, wchar_t > {

		template< typename ParseContextT >
		constexpr auto parse(ParseContextT& ctx) {
			return ctx.begin();
		}

		template< typename FormatContextT >
		auto format(const std::filesystem::path& path, FormatContextT& ctx) {
			return format_to(ctx.begin(), path.c_str());
		}
	};

	template< typename T, std::size_t A >
	struct formatter< mage::Array< T, 2u, A > > {

		template< typename ParseContextT >
		constexpr auto parse(ParseContextT& ctx) {
			return ctx.begin();
		}

		template< typename FormatContextT >
		auto format(const mage::Array< T, 2u, A >& a, FormatContextT& ctx) {
			const auto [x, y] = a;
			return format_to(ctx.begin(), "{} {}", x, y);
		}
	};

	template< typename T, std::size_t A >
	struct formatter< mage::Array< T, 3u, A > > {

		template< typename ParseContextT >
		constexpr auto parse(ParseContextT& ctx) {
			return ctx.begin();
		}

		template< typename FormatContextT >
		auto format(const mage::Array< T, 3u, A >& a, FormatContextT& ctx) {
			const auto [x, y, z] = a;
			return format_to(ctx.begin(), "{} {} {}", x, y, z);
		}
	};

	template< typename T, std::size_t A >
	struct formatter< mage::Array< T, 4u, A > > {

		template< typename ParseContextT >
		constexpr auto parse(ParseContextT& ctx) {
			return ctx.begin();
		}

		template< typename FormatContextT >
		auto format(const mage::Array< T, 4u, A >& a, FormatContextT &ctx) {
			const auto [x, y, z, w] = a;
			return format_to(ctx.begin(), "{} {} {} {}", x, y, z, w);
		}
	};
}