#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "string\string_utils.hpp"

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
		typename ParseContextT::iterator parse(ParseContextT& ctx) {
			return ctx.begin();
		}

		template< typename FormatContextT >
		auto format(const std::wstring_view& wstr, FormatContextT& ctx) {
			const mage::UTF16toUTF8 str(wstr);
			// An explicit formatting string is provided to avoid clashes with
			// the string.
			return format_to(ctx.begin(), "{}", std::string_view(str));
		}
	};

	template<>
	struct formatter< std::wstring, char > {

		template< typename ParseContextT >
		typename ParseContextT::iterator parse(ParseContextT& ctx) {
			return ctx.begin();
		}

		template< typename FormatContextT >
		auto format(const std::wstring& wstr, FormatContextT& ctx) {
			const mage::UTF16toUTF8 str(wstr);
			// An explicit formatting string is provided to avoid clashes with
			// the string.
			return format_to(ctx.begin(), "{}", std::string_view(str));
		}
	};

	template<>
	struct formatter< std::filesystem::path, char > {

		template< typename ParseContextT >
		typename ParseContextT::iterator parse(ParseContextT& ctx) {
			return ctx.begin();
		}

		template< typename FormatContextT >
		auto format(const std::filesystem::path& path, FormatContextT& ctx) {
			const mage::UTF16toUTF8 str(path.c_str());
			// An explicit formatting string is provided to avoid clashes with
			// the string.
			return format_to(ctx.begin(), "{}", std::string_view(str));
		}
	};

	template<>
	struct formatter< std::string_view, wchar_t > {

		template< typename ParseContextT >
		typename ParseContextT::iterator parse(ParseContextT& ctx) {
			return ctx.begin();
		}

		template< typename FormatContextT >
		auto format(const std::string_view& str, FormatContextT& ctx) {
			const mage::UTF8toUTF16 wstr(str);
			// An explicit formatting string is provided to avoid clashes with
			// the string.
			return format_to(ctx.begin(), L"{}", std::wstring_view(wstr));
		}
	};

	template<>
	struct formatter< std::string, wchar_t > {

		template< typename ParseContextT >
		typename ParseContextT::iterator parse(ParseContextT& ctx) {
			return ctx.begin();
		}

		template< typename FormatContextT >
		auto format(const std::string& str, FormatContextT& ctx) {
			const mage::UTF8toUTF16 wstr(str);
			// An explicit formatting string is provided to avoid clashes with
			// the string.
			return format_to(ctx.begin(), L"{}", std::wstring_view(wstr));
		}
	};

	template<>
	struct formatter< std::filesystem::path, wchar_t > {

		template< typename ParseContextT >
		typename ParseContextT::iterator parse(ParseContextT& ctx) {
			return ctx.begin();
		}

		template< typename FormatContextT >
		auto format(const std::filesystem::path& path, FormatContextT& ctx) {
			// An explicit formatting string is provided to avoid clashes with
			// the string.
			return format_to(ctx.begin(), L"{}", path.c_str());
		}
	};

	template< typename T, std::size_t N >
	struct formatter< std::array< T, N > > {

		template< typename ParseContextT >
		typename ParseContextT::iterator parse(ParseContextT& ctx) {
			return ctx.begin();
		}

		template< typename FormatContextT >
		auto format(const std::array< T, N >& a, FormatContextT& ctx) {
			if (a.empty()) {
				return ctx;
			}

			auto it = format_to(ctx.begin(), "{}", a[0]);
			for (std::size_t i = 1u; i < N; ++i) {
				it = format_to(it, " {}", a[i]);
			}
			return it;
		}
	};

	template< typename T, std::size_t N, std::size_t A >
	struct formatter< mage::Array< T, N, A > > {

		template< typename ParseContextT >
		typename ParseContextT::iterator parse(ParseContextT& ctx) {
			return ctx.begin();
		}

		template< typename FormatContextT >
		auto format(const mage::Array< T, N, A >& a, FormatContextT& ctx) {
			auto it = format_to(ctx.begin(), "{}", a[0]);
			for (std::size_t i = 1u; i < N; ++i) {
				it = format_to(it, " {}", a[i]);
			}
			return it;
		}
	};

	template< typename T1, typename T2 >
	struct formatter< std::pair< T1, T2 > > {

		template< typename ParseContextT >
		typename ParseContextT::iterator parse(ParseContextT& ctx) {
			return ctx.begin();
		}

		template< typename FormatContextT >
		auto format(const std::pair< T1, T2 >& a, FormatContextT& ctx) {
			return format_to(ctx.begin(), "{} {}", a.first, a.second);
		}
	};

	template< typename T, typename Allocator >
	struct formatter< std::vector< T, Allocator > > {

		template< typename ParseContextT >
		typename ParseContextT::iterator parse(ParseContextT& ctx) {
			return ctx.begin();
		}

		template< typename FormatContextT >
		auto format(const std::vector< T, Allocator >& a, FormatContextT& ctx) {
			if (a.empty()) {
				return ctx;
			}

			auto it = format_to(ctx.begin(), "{}", a[0]);
			for (std::size_t i = 1u; i < a.size(); ++i) {
				it = format_to(it, " {}", a[i]);
			}
			return it;
		}
	};
}