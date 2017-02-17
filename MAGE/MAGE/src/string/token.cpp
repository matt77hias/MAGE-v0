//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "string\token.hpp"
#include "string\string_utils.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	//-------------------------------------------------------------------------
	// Conversion Utilities
	//-------------------------------------------------------------------------

	TokenResult StringToBool(const char *str, bool &result) {
		if (!str) {
			return no_token;
		}

		if (str_equals(str, "true")) {
			result = true;
			return valid_token;
		}
		
		result = false;
		return (str_equals(str, "false")) ? valid_token : invalid_token;
	}
	TokenResult StringToInt(const char *str, int &result) {
		if (!str) {
			return no_token;
		}

		char *inner_context = nullptr;
		result = (int)strtol(str, &inner_context, 10);
		return (*inner_context == '\0') ? valid_token : invalid_token;
	}
	TokenResult StringToUnsignedInt(const char *str, unsigned int &result) {
		if (!str) {
			return no_token;
		}

		char *inner_context = nullptr;
		result = (unsigned int)strtoul(str, &inner_context, 10);
		return (*inner_context == '\0') ? valid_token : invalid_token;
	}
	TokenResult StringToLong(const char *str, long &result) {
		if (!str) {
			return no_token;
		}

		char *inner_context = nullptr;
		result = strtol(str, &inner_context, 10);
		return (*inner_context == '\0') ? valid_token : invalid_token;
	}
	TokenResult StringToUnsignedLong(const char *str, unsigned long &result) {
		if (!str) {
			return no_token;
		}

		char *inner_context = nullptr;
		result = strtoul(str, &inner_context, 10);
		return (*inner_context == '\0') ? valid_token : invalid_token;
	}
	TokenResult StringToLongLong(const char *str, long long &result) {
		if (!str) {
			return no_token;
		}

		char *inner_context = nullptr;
		result = strtoll(str, &inner_context, 10);
		return (*inner_context == '\0') ? valid_token : invalid_token;
	}
	TokenResult StringToUnsignedLongLong(const char *str, unsigned long long &result) {
		if (!str) {
			return no_token;
		}

		char *inner_context = nullptr;
		result = strtoull(str, &inner_context, 10);
		return (*inner_context == '\0') ? valid_token : invalid_token;
	}
	TokenResult StringToFloat(const char *str, float &result) {
		if (!str) {
			return no_token;
		}

		char *inner_context = nullptr;
		result = strtof(str, &inner_context);
		return (*inner_context == '\0') ? valid_token : invalid_token;
	}
	TokenResult StringToDouble(const char *str, double &result) {
		if (!str) {
			return no_token;
		}

		char *inner_context = nullptr;
		result = strtod(str, &inner_context);
		return (*inner_context == '\0') ? valid_token : invalid_token;
	}
	
	TokenResult StringToBool(const char *begin, const char *end, bool &result) {
		if (!begin) {
			return no_token;
		}

		if (end - begin == 4) {
			if ((*begin != 't') || 
				(*(begin + 1) != 'r') || 
				(*(begin + 2) != 'u') || 
				(*(begin + 3) != 'e')) {
				result = false;
				return invalid_token;
			}

			result = true;
			return valid_token;
		} 
		
		if (end - begin == 5) {
			if ((*begin != 'f') ||
				(*(begin + 1) != 'a') ||
				(*(begin + 2) != 'l') ||
				(*(begin + 3) != 's') ||
				(*(begin + 4) != 'e')) {
				result = false;
				return invalid_token;
			}

			result = false;
			return valid_token;
		}
		
		result = false;
		return invalid_token;
	}
	TokenResult StringToInt(const char *begin, const char *end, int &result) {
		if (!begin) {
			return no_token;
		}

		char *inner_context = nullptr;
		result = (int)strtol(begin, &inner_context, 10);
		return (inner_context == end) ? valid_token : invalid_token;
	}
	TokenResult StringToUnsignedInt(const char *begin, const char *end, unsigned int &result) {
		if (!begin) {
			return no_token;
		}

		char *inner_context = nullptr;
		result = (unsigned int)strtoul(begin, &inner_context, 10);
		return (inner_context == end) ? valid_token : invalid_token;
	}
	TokenResult StringToLong(const char *begin, const char *end, long &result) {
		if (!begin) {
			return no_token;
		}

		char *inner_context = nullptr;
		result = strtol(begin, &inner_context, 10);
		return (inner_context == end) ? valid_token : invalid_token;
	}
	TokenResult StringToUnsignedLong(const char *begin, const char *end, unsigned long &result) {
		if (!begin) {
			return no_token;
		}

		char *inner_context = nullptr;
		result = strtoul(begin, &inner_context, 10);
		return (inner_context == end) ? valid_token : invalid_token;
	}
	TokenResult StringToLongLong(const char *begin, const char *end, long long &result) {
		if (!begin) {
			return no_token;
		}

		char *inner_context = nullptr;
		result = strtoll(begin, &inner_context, 10);
		return (inner_context == end) ? valid_token : invalid_token;
	}
	TokenResult StringToUnsignedLongLong(const char *begin, const char *end, unsigned long long &result) {
		if (!begin) {
			return no_token;
		}

		char *inner_context = nullptr;
		result = strtoull(begin, &inner_context, 10);
		return (inner_context == end) ? valid_token : invalid_token;
	}
	TokenResult StringToFloat(const char *begin, const char *end, float &result) {
		if (!begin) {
			return no_token;
		}

		char *inner_context = nullptr;
		result = strtof(begin, &inner_context);
		return (inner_context == end) ? valid_token : invalid_token;
	}
	TokenResult StringToDouble(const char *begin, const char *end, double &result) {
		if (!begin) {
			return no_token;
		}

		char *inner_context = nullptr;
		result = strtod(begin, &inner_context);
		return (inner_context == end) ? valid_token : invalid_token;
	}

	TokenResult StringPrefixToInt(const char *str, int &result) {
		if (!str) {
			return no_token;
		}

		char *inner_context = nullptr;
		result = (int)strtol(str, &inner_context, 10);
		return (inner_context != str) ? valid_token : invalid_token;
	}
	TokenResult StringPrefixToUnsignedInt(const char *str, unsigned int &result) {
		if (!str) {
			return no_token;
		}

		char *inner_context = nullptr;
		result = (unsigned int)strtoul(str, &inner_context, 10);
		return (inner_context != str) ? valid_token : invalid_token;
	}
	TokenResult StringPrefixToLong(const char *str, long &result) {
		if (!str) {
			return no_token;
		}

		char *inner_context = nullptr;
		result = strtol(str, &inner_context, 10);
		return (inner_context != str) ? valid_token : invalid_token;
	}
	TokenResult StringPrefixToUnsignedLong(const char *str, unsigned long &result) {
		if (!str) {
			return no_token;
		}

		char *inner_context = nullptr;
		result = strtoul(str, &inner_context, 10);
		return (inner_context != str) ? valid_token : invalid_token;
	}
	TokenResult StringPrefixToLongLong(const char *str, long long &result) {
		if (!str) {
			return no_token;
		}

		char *inner_context = nullptr;
		result = strtoll(str, &inner_context, 10);
		return (inner_context != str) ? valid_token : invalid_token;
	}
	TokenResult StringPrefixToUnsignedLongLong(const char *str, unsigned long long &result) {
		if (!str) {
			return no_token;
		}

		char *inner_context = nullptr;
		result = strtoull(str, &inner_context, 10);
		return (inner_context != str) ? valid_token : invalid_token;
	}
	TokenResult StringPrefixToFloat(const char *str, float &result) {
		if (!str) {
			return no_token;
		}

		char *inner_context = nullptr;
		result = strtof(str, &inner_context);
		return (inner_context != str) ? valid_token : invalid_token;
	}
	TokenResult StringPrefixToDouble(const char *str, double &result) {
		if (!str) {
			return no_token;
		}

		char *inner_context = nullptr;
		result = strtod(str, &inner_context);
		return (inner_context != str) ? valid_token : invalid_token;
	}

	//-------------------------------------------------------------------------
	// Parsing Utilities
	//-------------------------------------------------------------------------

	TokenResult ReadChars(char *str, char **context, char **result, const char *delimiters) {
		*result = strtok_s(str, delimiters, context);
		if (!result) {
			return no_token;
		}

		return valid_token;
	}
	TokenResult ReadString(char *str, char **context, string &result, const char *delimiters) {
		const char *token = strtok_s(str, delimiters, context);
		if (!token) {
			return no_token;
		}
		
		result = token;

		return valid_token;
	}
	TokenResult ReadQuotedString(char *str, char **context, string &result, const char *delimiters) {
		char *start = (str) ? SkipDelimiters(str, delimiters) : SkipDelimiters(*context, delimiters);
		if (!start) {
			return no_token;
		}

		char *first_quote = strchr(start, '"');
		if (!first_quote) {
			return invalid_token;
		}
		char *last_quote = strchr(first_quote + 1, '"');
		if (!last_quote) {
			return invalid_token;
		}

		if (!str_contains(delimiters, *(last_quote + 1))) {
			return invalid_token;
		}

		*last_quote = '\0';
		result = first_quote + 1;
		*context = last_quote + 1;
		return valid_token;
	}
	TokenResult ReadBool(char *str, char **context, bool &result, const char *delimiters) {
		const char *token = strtok_s(str, delimiters, context);
		return StringToBool(token, result);
	}
	TokenResult ReadInt(char *str, char **context, int &result, const char *delimiters) {
		const char *token = strtok_s(str, delimiters, context);
		return StringToInt(token, result);
	}
	TokenResult ReadUnsignedInt(char *str, char **context, unsigned int &result, const char *delimiters) {
		const char *token = strtok_s(str, delimiters, context);
		return StringToUnsignedInt(token, result);
	}
	TokenResult ReadLong(char *str, char **context, long &result, const char *delimiters) {
		const char *token = strtok_s(str, delimiters, context);
		return StringToLong(token, result);
	}
	TokenResult ReadUnsignedLong(char *str, char **context, unsigned long &result, const char *delimiters) {
		const char *token = strtok_s(str, delimiters, context);
		return StringToUnsignedLong(token, result);
	}
	TokenResult ReadLongLong(char *str, char **context, long long &result, const char *delimiters) {
		const char *token = strtok_s(str, delimiters, context);
		return StringToLongLong(token, result);
	}
	TokenResult ReadUnsignedLongLong(char *str, char **context, unsigned long long &result, const char *delimiters) {
		const char *token = strtok_s(str, delimiters, context);
		return StringToUnsignedLongLong(token, result);
	}
	TokenResult ReadFloat(char *str, char **context, float &result, const char *delimiters) {
		const char *token = strtok_s(str, delimiters, context);
		return StringToFloat(token, result);
	}
	TokenResult ReadDouble(char *str, char **context, double &result, const char *delimiters) {
		const char *token = strtok_s(str, delimiters, context);
		return StringToDouble(token, result);
	}
	TokenResult ReadFloat2(char *str, char **context, XMFLOAT2 &result, const char *delimiters) {
		const TokenResult token_result_x = ReadFloat(str, context, result.x, delimiters);
		if (token_result_x != valid_token) {
			return token_result_x;
		}

		const TokenResult token_result_y = ReadFloat(str, context, result.y, delimiters);
		if (token_result_y != valid_token) {
			return token_result_y;
		}
		
		return valid_token;
	}
	TokenResult ReadFloat3(char *str, char **context, XMFLOAT3 &result, const char *delimiters) {
		const TokenResult token_result_x = ReadFloat(str, context, result.x, delimiters);
		if (token_result_x != valid_token) {
			return token_result_x;
		}

		const TokenResult token_result_y = ReadFloat(str, context, result.y, delimiters);
		if (token_result_y != valid_token) {
			return token_result_y;
		}

		const TokenResult token_result_z = ReadFloat(str, context, result.z, delimiters);
		if (token_result_z != valid_token) {
			return token_result_z;
		}

		return valid_token;
	}
	TokenResult ReadFloat4(char *str, char **context, XMFLOAT4 &result, const char *delimiters) {
		const TokenResult token_result_x = ReadFloat(str, context, result.x, delimiters);
		if (token_result_x != valid_token) {
			return token_result_x;
		}

		const TokenResult token_result_y = ReadFloat(str, context, result.y, delimiters);
		if (token_result_y != valid_token) {
			return token_result_y;
		}

		const TokenResult token_result_z = ReadFloat(str, context, result.z, delimiters);
		if (token_result_z != valid_token) {
			return token_result_z;
		}

		const TokenResult token_result_w = ReadFloat(str, context, result.w, delimiters);
		if (token_result_w != valid_token) {
			return token_result_w;
		}

		return valid_token;
	}

	TokenResult HasChars(const char *str, const char *delimiters) {
		const char *start = SkipDelimiters(str, delimiters);
		return (start) ? valid_token : no_token;
	}
	TokenResult HasString(const char *str, const char *delimiters) {
		return HasChars(str, delimiters);
	}
	TokenResult HasQuotedString(const char *str, const char *delimiters) {
		const char *start = SkipDelimiters(str, delimiters);
		if (!start) {
			return no_token;
		}
		
		const char *first_quote = strchr(start, '"');
		if (!first_quote) {
			return invalid_token;
		}
		const char *last_quote = strchr(first_quote + 1, '"');
		if (!last_quote) {
			return invalid_token;
		}
		
		return str_contains(delimiters, *(last_quote + 1)) ? valid_token : invalid_token;
	}
	TokenResult HasBool(const char *str, const char *delimiters) {
		const char *start = SkipDelimiters(str, delimiters);
		if (!start) {
			return no_token;
		}
		const char *end = GotoDelimiters(start, delimiters);

		bool result;
		return StringToBool(start, end, result);
	}
	TokenResult HasInt(const char *str, const char *delimiters) {
		const char *start = SkipDelimiters(str, delimiters);
		if (!start) {
			return no_token;
		}
		const char *end = GotoDelimiters(start, delimiters);

		int result;
		return StringToInt(start, end, result);
	}
	TokenResult HasUnsignedInt(const char *str, const char *delimiters) {
		const char *start = SkipDelimiters(str, delimiters);
		if (!start) {
			return no_token;
		}
		const char *end = GotoDelimiters(start, delimiters);

		unsigned int result;
		return StringToUnsignedInt(start, end, result);
	}
	TokenResult HasLong(const char *str, const char *delimiters) {
		const char *start = SkipDelimiters(str, delimiters);
		if (!start) {
			return no_token;
		}
		const char *end = GotoDelimiters(start, delimiters);

		long result;
		return StringToLong(start, end, result);
	}
	TokenResult HasUnsignedLong(const char *str, const char *delimiters) {
		const char *start = SkipDelimiters(str, delimiters);
		if (!start) {
			return no_token;
		}
		const char *end = GotoDelimiters(start, delimiters);

		unsigned long result;
		return StringToUnsignedLong(start, end, result);
	}
	TokenResult HasLongLong(const char *str, const char *delimiters) {
		const char *start = SkipDelimiters(str, delimiters);
		if (!start) {
			return no_token;
		}
		const char *end = GotoDelimiters(start, delimiters);

		long long result;
		return StringToLongLong(start, end, result);
	}
	TokenResult HasUnsignedLongLong(const char *str, const char *delimiters) {
		const char *start = SkipDelimiters(str, delimiters);
		if (!start) {
			return no_token;
		}
		const char *end = GotoDelimiters(start, delimiters);

		unsigned long long result;
		return StringToUnsignedLongLong(start, end, result);
	}
	TokenResult HasFloat(const char *str, const char *delimiters) {
		const char *start = SkipDelimiters(str, delimiters);
		if (!start) {
			return no_token;
		}
		const char *end = GotoDelimiters(start, delimiters);

		float result;
		return StringToFloat(start, end, result);
	}
	TokenResult HasDouble(const char *str, const char *delimiters) {
		const char *start = SkipDelimiters(str, delimiters);
		if (!start) {
			return no_token;
		}
		const char *end = GotoDelimiters(start, delimiters);

		double result;
		return StringToDouble(start, end, result);
	}

	char *SkipDelimiters(char *str, const char *delimiters) {
		while (*str != '\0' && str_contains(delimiters, *str)) {
			++str;
		}
		return (*str != '\0') ? str : nullptr;
	}
	const char *SkipDelimiters(const char *str, const char *delimiters) {
		while (*str != '\0' && str_contains(delimiters, *str)) {
			++str;
		}
		return (*str != '\0') ? str : nullptr;
	}
	char *GotoDelimiters(char *str, const char *delimiters) {
		while (*str != '\0' && !str_contains(delimiters, *str)) {
			++str;
		}
		return (*str != '\0') ? str : nullptr;
	}
	const char *GotoDelimiters(const char *str, const char *delimiters) {
		while (*str != '\0' && !str_contains(delimiters, *str)) {
			++str;
		}
		return (*str != '\0') ? str : nullptr;
	}
}