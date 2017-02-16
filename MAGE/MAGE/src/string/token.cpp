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
		result = (unsigned int)strtoul(str, &inner_context, 10);
		return (*inner_context == '\0') ? valid_token : invalid_token;
	}

	TokenResult StringToUnsignedInt(const char *str, unsigned int &result) {
		if (!str) {
			return no_token;
		}

		char *inner_context = nullptr;
		result = (int)strtol(str, &inner_context, 10);
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

	TokenResult StringToFloat(const char *str, float &result) {
		if (!str) {
			return no_token;
		}

		char *inner_context = nullptr;
		result = (float)strtof(str, &inner_context);
		return (*inner_context == '\0') ? valid_token : invalid_token;
	}

	TokenResult StringToDouble(const char *str, double &result) {
		if (!str) {
			return no_token;
		}

		char *inner_context = nullptr;
		result = strtof(str, &inner_context);
		return (*inner_context == '\0') ? valid_token : invalid_token;
	}

	TokenResult StringPrefixToInt(const char *str, int &result) {
		if (!str) {
			return no_token;
		}

		char *inner_context = nullptr;
		result = (unsigned int)strtoul(str, &inner_context, 10);
		return (inner_context != str) ? valid_token : invalid_token;
	}

	TokenResult StringPrefixToUnsignedInt(const char *str, unsigned int &result) {
		if (!str) {
			return no_token;
		}

		char *inner_context = nullptr;
		result = (int)strtol(str, &inner_context, 10);
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

	TokenResult StringPrefixToFloat(const char *str, float &result) {
		if (!str) {
			return no_token;
		}

		char *inner_context = nullptr;
		result = (float)strtof(str, &inner_context);
		return (inner_context != str) ? valid_token : invalid_token;
	}

	TokenResult StringPrefixToDouble(const char *str, double &result) {
		if (!str) {
			return no_token;
		}

		char *inner_context = nullptr;
		result = strtof(str, &inner_context);
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

	TokenResult ReadFloat(char *str, char **context, float &result, const char *delimiters) {
		const char *token = strtok_s(str, delimiters, context);
		return StringToFloat(token, result);
	}

	TokenResult ReadDouble(char *str, char **context, double &result, const char *delimiters) {
		const char *token = strtok_s(str, delimiters, context);
		return StringToDouble(token, result);
	}

	TokenResult ReadFloat2(char *str, char **context, XMFLOAT2 &result, const char *delimiters) {
		const TokenResult parse_result_x = ReadFloat(str, context, result.x, delimiters);
		const TokenResult parse_result_y = ReadFloat(str, context, result.y, delimiters);

		if (parse_result_x == invalid_token 
			|| parse_result_y == invalid_token) {
			return invalid_token;
		}
		if (parse_result_x == no_token 
			|| parse_result_y == no_token) {
			return no_token;
		}
		return valid_token;
	}

	TokenResult ReadFloat3(char *str, char **context, XMFLOAT3 &result, const char *delimiters) {
		const TokenResult parse_result_x = ReadFloat(str, context, result.x, delimiters);
		const TokenResult parse_result_y = ReadFloat(str, context, result.y, delimiters);
		const TokenResult parse_result_z = ReadFloat(str, context, result.z, delimiters);

		if (parse_result_x == invalid_token 
			|| parse_result_y == invalid_token 
			|| parse_result_z == invalid_token) {
			return invalid_token;
		}
		if (parse_result_x == no_token 
			|| parse_result_y == no_token 
			|| parse_result_z == no_token) {
			return no_token;
		}
		return valid_token;
	}

	TokenResult ReadFloat4(char *str, char **context, XMFLOAT4 &result, const char *delimiters) {
		const TokenResult parse_result_x = ReadFloat(str, context, result.x, delimiters);
		const TokenResult parse_result_y = ReadFloat(str, context, result.y, delimiters);
		const TokenResult parse_result_z = ReadFloat(str, context, result.z, delimiters);
		const TokenResult parse_result_w = ReadFloat(str, context, result.w, delimiters);

		if (parse_result_x == invalid_token 
			|| parse_result_y == invalid_token 
			|| parse_result_z == invalid_token 
			|| parse_result_w == invalid_token) {
			return invalid_token;
		}
		if (parse_result_x == no_token 
			|| parse_result_y == no_token 
			|| parse_result_z == no_token 
			|| parse_result_w == no_token) {
			return no_token;
		}
		return valid_token;
	}
}