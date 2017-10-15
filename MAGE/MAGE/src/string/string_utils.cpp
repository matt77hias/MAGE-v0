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
	
	const char *str_escape_first(const char *str, char c) noexcept {
		Assert(str);
		
		const char *input = str;
		while (true) {
			const char *result = strchr(input, static_cast< int >(c));

			if (!result) {
				// No match found.
				return nullptr;
			}
			if (result == str) {
				// Current match is not escaped (first character).
				return result;
			}
			if (*(result - 1) != '\\') {
				// Current match is not escaped.
				return result;
			}

			// Continue search (current match is escaped).
			input = result + 1;
		}
	}

	char *str_escape_first(char *str, char c) noexcept {
		Assert(str);
		
		char *input = str;
		while (true) {
			char *result = strchr(input, static_cast< int >(c));
			
			if (!result) {
				// No match found.
				return nullptr;
			}
			if (result == str) {
				// Current match is not escaped (first character).
				return result;
			}
			if (*(result - 1) != '\\') {
				// Current match is not escaped.
				return result;
			}

			// Continue search (current match is escaped).
			input = result + 1;
		}
	}

	const wchar_t *str_escape_first(const wchar_t *str, wchar_t c) noexcept {
		Assert(str);
		
		const wchar_t *input = str;
		while (true) {
			const wchar_t *result = wcschr(input, c);

			if (!result) {
				// No match found.
				return nullptr;
			}
			if (result == str) {
				// Current match is not escaped (first character).
				return result;
			}
			if (*(result - 1) != L'\\') {
				// Current match is not escaped.
				return result;
			}

			// Continue search (current match is escaped).
			input = result + 1;
		}
	}

	wchar_t *str_escape_first(wchar_t *str, wchar_t c) noexcept {
		Assert(str);
		
		wchar_t *input = str;
		while (true) {
			wchar_t *result = wcschr(input, c);

			if (!result) {
				// No match found.
				return nullptr;
			}
			if (result == str) {
				// Current match is not escaped (first character).
				return result;
			}
			if (*(result - 1) != L'\\') {
				// Current match is not escaped.
				return result;
			}

			// Continue search (current match is escaped).
			input = result + 1;
		}
	}

	char *str_gets(char *str, size_t num, const char **input) noexcept {
		Assert(str);
		Assert(input);
		
		const char *next = *input;
		size_t num_read = 0u;
		while (num_read + 1u < num && *next) {
			// '\n' terminates the line but is included.
			const bool is_new_line = (*next == '\n');

			*str++ = *next++;
			++num_read;

			if (is_new_line) {
				break;
			}
		}

		if (num_read == 0u) {
			// "eof"
			return nullptr;
		}

		*str = '\0';
		*input = next;
		return str;
	}

	wchar_t *str_gets(wchar_t *str, size_t num, const wchar_t **input) noexcept {
		Assert(str);
		Assert(input);
		
		const wchar_t *next = *input;
		size_t num_read = 0u;
		while (num_read + 1u < num && *next) {
			// '\n' terminates the line but is included.
			const bool is_new_line = (*next == L'\n');

			*str++ = *next++;
			++num_read;

			if (is_new_line) {
				break;
			}
		}

		if (num_read == 0u) {
			// "eof"
			return nullptr;
		}

		*str = L'\0';
		*input = next;
		return str;
	}

	const wstring str_convert(const string &str) {
		return wstring(CA2W(str.c_str()));
	}

	const string str_convert(const wstring &str) {
		return string(CW2A(str.c_str()));
	}
}