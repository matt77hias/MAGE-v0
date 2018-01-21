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
	
	[[nodiscard]] char *
		str_escape_first(char *str, char c) noexcept {
		
		Assert(str);
		
		auto *input = str;
		while (true) {
			auto *result = strchr(input, static_cast< int >(c));
			
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

	[[nodiscard]] const char *
		str_escape_first(const char *str, char c) noexcept {
		
		Assert(str);
		
		const auto *input = str;
		while (true) {
			const auto *result = strchr(input, static_cast< int >(c));

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

	[[nodiscard]] wchar_t *
		str_escape_first(wchar_t *str, wchar_t c) noexcept {
		
		Assert(str);
		
		auto *input = str;
		while (true) {
			auto *result = wcschr(input, c);

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

	[[nodiscard]] const wchar_t *
		str_escape_first(const wchar_t *str, wchar_t c) noexcept {
		
		Assert(str);
		
		const auto *input = str;
		while (true) {
			const auto *result = wcschr(input, c);

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

	[[nodiscard]] char *
		str_gets(char *str, size_t num, const char **input) noexcept {
		
		Assert(str);
		Assert(input);
		
		const auto *next = *input;
		size_t num_read = 0u;
		while (num_read + 1u < num && *next) {
			// '\n' terminates the line but is included.
			const bool is_new_line = ('\n' == *next);

			*str++ = *next++;
			++num_read;

			if (is_new_line) {
				break;
			}
		}

		if (0u == num_read) {
			// "eof"
			return nullptr;
		}

		*str = '\0';
		*input = next;
		return str;
	}

	[[nodiscard]] wchar_t *
		str_gets(wchar_t *str, size_t num, const wchar_t **input) noexcept {
		
		Assert(str);
		Assert(input);
		
		const auto *next = *input;
		size_t num_read = 0u;
		while (num_read + 1u < num && *next) {
			// '\n' terminates the line but is included.
			const bool is_new_line = (L'\n' == *next);

			*str++ = *next++;
			++num_read;

			if (is_new_line) {
				break;
			}
		}

		if (0u == num_read) {
			// "eof"
			return nullptr;
		}

		*str = L'\0';
		*input = next;
		return str;
	}

	[[nodiscard]] const wstring str_convert(const string &str) {
		return wstring(CA2W(str.c_str()));
	}

	[[nodiscard]] const string str_convert(const wstring &str) {
		return string(CW2A(str.c_str()));
	}
}