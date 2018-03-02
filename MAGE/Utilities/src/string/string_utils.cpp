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

#include <AtlBase.h>
#include <atlconv.h>

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {
	
	[[nodiscard]]
	zstring str_escape_first(NotNull< zstring > str, char c) noexcept {
		auto input = str;
		while (true) {
			auto result = strchr(input, static_cast< int >(c));
			
			if (nullptr == result) {
				// No match found.
				return nullptr;
			}
			if (str == result) {
				// Current match is not escaped (first character).
				return result;
			}
			if ('\\' != *(result - 1)) {
				// Current match is not escaped.
				return result;
			}

			// Continue search (current match is escaped).
			input = result + 1;
		}
	}

	[[nodiscard]]
	const_zstring str_escape_first(NotNull< const_zstring > str, 
								   char c) noexcept {
		auto input = str;
		while (true) {
			const auto result = strchr(input, static_cast< int >(c));

			if (nullptr == result) {
				// No match found.
				return nullptr;
			}
			if (str == result) {
				// Current match is not escaped (first character).
				return result;
			}
			if ('\\' != *(result - 1)) {
				// Current match is not escaped.
				return result;
			}

			// Continue search (current match is escaped).
			input = result + 1;
		}
	}

	[[nodiscard]]
	wzstring str_escape_first(NotNull< wzstring > str, wchar_t c) noexcept {
		auto input = str;
		while (true) {
			auto result = wcschr(input, c);

			if (nullptr == result) {
				// No match found.
				return nullptr;
			}
			if (str == result) {
				// Current match is not escaped (first character).
				return result;
			}
			if (L'\\' != *(result - 1)) {
				// Current match is not escaped.
				return result;
			}

			// Continue search (current match is escaped).
			input = result + 1;
		}
	}

	[[nodiscard]]
	const_wzstring str_escape_first(NotNull< const_wzstring > str, 
									wchar_t c) noexcept {
		auto input = str;
		while (true) {
			const auto result = wcschr(input, c);

			if (nullptr == result) {
				// No match found.
				return nullptr;
			}
			if (str == result) {
				// Current match is not escaped (first character).
				return result;
			}
			if (L'\\' != *(result - 1)) {
				// Current match is not escaped.
				return result;
			}

			// Continue search (current match is escaped).
			input = result + 1;
		}
	}

	[[nodiscard]]
	zstring str_gets(NotNull< char* > str,
					 size_t num,
					 NotNull< NotNull< const_zstring >* > input) noexcept {

		char* buffer     = str;
		const char* next = *input;
		size_t num_read  = 0u;
		
		while (num_read + 1u < num && *next) {
			// '\n' terminates the line but is included.
			const auto is_new_line = ('\n' == *next);

			*buffer++ = *next++;
			++num_read;

			if (is_new_line) {
				break;
			}
		}

		if (0u == num_read) {
			// "eof"
			return nullptr;
		}

		*str   = '\0';
		*input = next;
		return str;
	}

	[[nodiscard]]
	wzstring str_gets(NotNull< wchar_t* > str,
					  size_t num,
					  NotNull< NotNull< const_wzstring >* > input) noexcept {

		wchar_t* buffer     = str;
		const wchar_t* next = *input;
		size_t num_read     = 0u;
		
		while (num_read + 1u < num && *next) {
			// '\n' terminates the line but is included.
			const auto is_new_line = (L'\n' == *next);

			*buffer++ = *next++;
			++num_read;

			if (is_new_line) {
				break;
			}
		}

		if (0u == num_read) {
			// "eof"
			return nullptr;
		}

		*str   = L'\0';
		*input = next;
		return str;
	}

	[[nodiscard]]
	const wstring str_convert(const string& str) {
		return wstring(CA2W(str.c_str()));
	}

	[[nodiscard]]
	const string str_convert(const wstring& str) {
		return string(CW2A(str.c_str()));
	}
}