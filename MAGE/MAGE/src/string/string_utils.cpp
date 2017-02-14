//-----------------------------------------------------------------------------
// System Includes
//-----------------------------------------------------------------------------
#pragma region

#include <AtlBase.h>
#include <atlconv.h>

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "string\string_utils.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {
	
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

	wchar_t *str_convert(const char *str) {
		return CA2W(str);
	}

	char *str_convert(const wchar_t *str) {
		return CW2A(str);
	}

	wstring str_convert(const string &str) {
		return wstring(CA2W(str.c_str()));
	}

	string str_convert(const wstring &str) {
		return string(CW2A(str.c_str()));
	}
}