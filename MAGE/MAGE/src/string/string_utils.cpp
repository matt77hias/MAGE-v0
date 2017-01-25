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
	
	char *sgets(char *str, int num, const char **input) {
		const char *next = *input;
		int  num_read = 0;
		while (num_read + 1 < num && *next) {
			// '\n' terminates the line but is included
			const int is_new_line = (*next == '\n');

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
}