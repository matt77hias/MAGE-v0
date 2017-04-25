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
	
	const char *str_escape_first(const char *str, char c) {
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

	char *str_escape_first(char *str, char c) {
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

	const wchar_t *str_escape_first(const wchar_t *str, wchar_t c) {
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

	wchar_t *str_escape_first(wchar_t *str, wchar_t c) {
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

	char *str_gets(char *str, int num, const char **input) {
		const char *next = *input;
		int num_read = 0;
		while (num_read + 1 < num && *next) {
			// '\n' terminates the line but is included
			const bool is_new_line = (*next == '\n');

			*str++ = *next++;
			++num_read;

			if (is_new_line) {
				break;
			}
		}

		if (num_read == 0) {
			// "eof"
			return nullptr;
		}

		*str = '\0';
		*input = next;
		return str;
	}

	wchar_t *str_gets(wchar_t *str, int num, const wchar_t **input) {
		const wchar_t *next = *input;
		int num_read = 0;
		while (num_read + 1 < num && *next) {
			// '\n' terminates the line but is included
			const bool is_new_line = (*next == L'\n');

			*str++ = *next++;
			++num_read;

			if (is_new_line) {
				break;
			}
		}

		if (num_read == 0) {
			// "eof"
			return nullptr;
		}

		*str = L'\0';
		*input = next;
		return str;
	}

	const wchar_t *str_convert(const char *str) {
		return CA2W(str);
	}

	const char *str_convert(const wchar_t *str) {
		return CW2A(str);
	}
}