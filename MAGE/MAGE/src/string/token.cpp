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
	// String Conversion Utilities: Complete String
	//-------------------------------------------------------------------------
#pragma region

	TokenResult StringToBool(const char *str, bool &result) noexcept {
		if (!str) {
			return TokenResult::None;
		}

		if (str_equals(str, "true")) {
			result = true;
			return TokenResult::Valid;
		}
		
		result = false;
		return (str_equals(str, "false")) ? TokenResult::Valid : TokenResult::Invalid;
	}
	
	TokenResult StringToI8(const char *str, i8 &result) noexcept {
		if (!str) {
			return TokenResult::None;
		}

		char *inner_context = nullptr;
		result = static_cast< i8 >(strtol(str, &inner_context, 10));
		return (*inner_context == '\0') ? TokenResult::Valid : TokenResult::Invalid;
	}
	
	TokenResult StringToU8(const char *str, u8 &result) noexcept {
		if (!str) {
			return TokenResult::None;
		}

		char *inner_context = nullptr;
		result = static_cast< u8 >(strtoul(str, &inner_context, 10));
		return (*inner_context == '\0') ? TokenResult::Valid : TokenResult::Invalid;
	}
	
	TokenResult StringToI16(const char *str, i16 &result) noexcept {
		if (!str) {
			return TokenResult::None;
		}

		char *inner_context = nullptr;
		result = static_cast< i16 >(strtol(str, &inner_context, 10));
		return (*inner_context == '\0') ? TokenResult::Valid : TokenResult::Invalid;
	}
	
	TokenResult StringToU16(const char *str, u16 &result) noexcept {
		if (!str) {
			return TokenResult::None;
		}

		char *inner_context = nullptr;
		result = static_cast< u16 >(strtoul(str, &inner_context, 10));
		return (*inner_context == '\0') ? TokenResult::Valid : TokenResult::Invalid;
	}

	TokenResult StringToI32(const char *str, i32 &result) noexcept {
		if (!str) {
			return TokenResult::None;
		}

		char *inner_context = nullptr;
		result = static_cast< i32 >(strtol(str, &inner_context, 10));
		return (*inner_context == '\0') ? TokenResult::Valid : TokenResult::Invalid;
	}
	
	TokenResult StringToU32(const char *str, u32 &result) noexcept {
		if (!str) {
			return TokenResult::None;
		}

		char *inner_context = nullptr;
		result = static_cast< u32 >(strtoul(str, &inner_context, 10));
		return (*inner_context == '\0') ? TokenResult::Valid : TokenResult::Invalid;
	}
	
	TokenResult StringToI64(const char *str, i64 &result) noexcept {
		if (!str) {
			return TokenResult::None;
		}

		char *inner_context = nullptr;
		result = static_cast< i64 >(strtoll(str, &inner_context, 10));
		return (*inner_context == '\0') ? TokenResult::Valid : TokenResult::Invalid;
	}
	
	TokenResult StringToU64(const char *str, u64 &result) noexcept {
		if (!str) {
			return TokenResult::None;
		}

		char *inner_context = nullptr;
		result = static_cast< u64 >(strtoull(str, &inner_context, 10));
		return (*inner_context == '\0') ? TokenResult::Valid : TokenResult::Invalid;
	}
	
	TokenResult StringToFloat(const char *str, float &result) noexcept {
		if (!str) {
			return TokenResult::None;
		}

		char *inner_context = nullptr;
		result = strtof(str, &inner_context);
		return (*inner_context == '\0') ? TokenResult::Valid : TokenResult::Invalid;
	}
	
	TokenResult StringToDouble(const char *str, double &result) noexcept {
		if (!str) {
			return TokenResult::None;
		}

		char *inner_context = nullptr;
		result = strtod(str, &inner_context);
		return (*inner_context == '\0') ? TokenResult::Valid : TokenResult::Invalid;
	}
	
#pragma endregion

	//-------------------------------------------------------------------------
	// String Conversion Utilities: Substring
	//-------------------------------------------------------------------------
#pragma region

	TokenResult StringToBool(const char *begin, const char *end, bool &result) noexcept {
		if (!begin) {
			return TokenResult::None;
		}

		Assert(end);

		if (end - begin == 4) {
			if ((*begin != 't') || 
				(*(begin + 1) != 'r') || 
				(*(begin + 2) != 'u') || 
				(*(begin + 3) != 'e')) {
				result = false;
				return TokenResult::Invalid;
			}

			result = true;
			return TokenResult::Valid;
		} 
		
		if (end - begin == 5) {
			if ((*begin != 'f') ||
				(*(begin + 1) != 'a') ||
				(*(begin + 2) != 'l') ||
				(*(begin + 3) != 's') ||
				(*(begin + 4) != 'e')) {
				result = false;
				return TokenResult::Invalid;
			}

			result = false;
			return TokenResult::Valid;
		}
		
		result = false;
		return TokenResult::Invalid;
	}
	
	TokenResult StringToI8(const char *begin, const char *end, i8 &result) noexcept {
		if (!begin) {
			return TokenResult::None;
		}

		Assert(end);

		char *inner_context = nullptr;
		result = static_cast< i8 >(strtol(begin, &inner_context, 10));
		return (inner_context == end) ? TokenResult::Valid : TokenResult::Invalid;
	}
	
	TokenResult StringToU8(const char *begin, const char *end, u8 &result) noexcept {
		if (!begin) {
			return TokenResult::None;
		}

		Assert(end);

		char *inner_context = nullptr;
		result = static_cast< u8 >(strtoul(begin, &inner_context, 10));
		return (inner_context == end) ? TokenResult::Valid : TokenResult::Invalid;
	}
	
	TokenResult StringToI16(const char *begin, const char *end, i16 &result) noexcept {
		if (!begin) {
			return TokenResult::None;
		}

		Assert(end);

		char *inner_context = nullptr;
		result = static_cast< i16 >(strtol(begin, &inner_context, 10));
		return (inner_context == end) ? TokenResult::Valid : TokenResult::Invalid;
	}
	
	TokenResult StringToU16(const char *begin, const char *end, u16 &result) noexcept {
		if (!begin) {
			return TokenResult::None;
		}

		Assert(end);

		char *inner_context = nullptr;
		result = static_cast< u16 >(strtoul(begin, &inner_context, 10));
		return (inner_context == end) ? TokenResult::Valid : TokenResult::Invalid;
	}
	
	TokenResult StringToI32(const char *begin, const char *end, i32 &result) noexcept {
		if (!begin) {
			return TokenResult::None;
		}

		Assert(end);

		char *inner_context = nullptr;
		result = static_cast< i32 >(strtol(begin, &inner_context, 10));
		return (inner_context == end) ? TokenResult::Valid : TokenResult::Invalid;
	}
	
	TokenResult StringToU32(const char *begin, const char *end, u32 &result) noexcept {
		if (!begin) {
			return TokenResult::None;
		}

		Assert(end);

		char *inner_context = nullptr;
		result = static_cast< u32 >(strtoul(begin, &inner_context, 10));
		return (inner_context == end) ? TokenResult::Valid : TokenResult::Invalid;
	}
	
	TokenResult StringToI64(const char *begin, const char *end, i64 &result) noexcept {
		if (!begin) {
			return TokenResult::None;
		}

		Assert(end);

		char *inner_context = nullptr;
		result = static_cast< i64 >(strtoll(begin, &inner_context, 10));
		return (inner_context == end) ? TokenResult::Valid : TokenResult::Invalid;
	}
	
	TokenResult StringToU64(const char *begin, const char *end, u64 &result) noexcept {
		if (!begin) {
			return TokenResult::None;
		}

		Assert(end);

		char *inner_context = nullptr;
		result = static_cast< u64 >(strtoull(begin, &inner_context, 10));
		return (inner_context == end) ? TokenResult::Valid : TokenResult::Invalid;
	}
	
	TokenResult StringToFloat(const char *begin, const char *end, float &result) noexcept {
		if (!begin) {
			return TokenResult::None;
		}

		Assert(end);

		char *inner_context = nullptr;
		result = strtof(begin, &inner_context);
		return (inner_context == end) ? TokenResult::Valid : TokenResult::Invalid;
	}
	
	TokenResult StringToDouble(const char *begin, const char *end, double &result) noexcept {
		if (!begin) {
			return TokenResult::None;
		}

		Assert(end);

		char *inner_context = nullptr;
		result = strtod(begin, &inner_context);
		return (inner_context == end) ? TokenResult::Valid : TokenResult::Invalid;
	}

#pragma endregion

	//-------------------------------------------------------------------------
	// String Conversion Utilities: String Prefix
	//-------------------------------------------------------------------------
#pragma region

	TokenResult StringPrefixToI8(const char *str, i8 &result) noexcept {
		if (!str) {
			return TokenResult::None;
		}

		char *inner_context = nullptr;
		result = static_cast< i8 >(strtol(str, &inner_context, 10));
		return (inner_context != str) ? TokenResult::Valid : TokenResult::Invalid;
	}
	
	TokenResult StringPrefixToU8(const char *str, u8 &result) noexcept {
		if (!str) {
			return TokenResult::None;
		}

		char *inner_context = nullptr;
		result = static_cast< u8 >(strtoul(str, &inner_context, 10));
		return (inner_context != str) ? TokenResult::Valid : TokenResult::Invalid;
	}
	
	TokenResult StringPrefixToI16(const char *str, i16 &result) noexcept {
		if (!str) {
			return TokenResult::None;
		}

		char *inner_context = nullptr;
		result = static_cast< i16 >(strtol(str, &inner_context, 10));
		return (inner_context != str) ? TokenResult::Valid : TokenResult::Invalid;
	}
	
	TokenResult StringPrefixToU16(const char *str, u16 &result) noexcept {
		if (!str) {
			return TokenResult::None;
		}

		char *inner_context = nullptr;
		result = static_cast< u16 >(strtoul(str, &inner_context, 10));
		return (inner_context != str) ? TokenResult::Valid : TokenResult::Invalid;
	}
	
	TokenResult StringPrefixToI32(const char *str, i32 &result) noexcept {
		if (!str) {
			return TokenResult::None;
		}

		char *inner_context = nullptr;
		result = static_cast< i32 >(strtol(str, &inner_context, 10));
		return (inner_context != str) ? TokenResult::Valid : TokenResult::Invalid;
	}
	
	TokenResult StringPrefixToU32(const char *str, u32 &result) noexcept {
		if (!str) {
			return TokenResult::None;
		}

		char *inner_context = nullptr;
		result = static_cast< u32>(strtoul(str, &inner_context, 10));
		return (inner_context != str) ? TokenResult::Valid : TokenResult::Invalid;
	}
	
	TokenResult StringPrefixToI64(const char *str, i64 &result) noexcept {
		if (!str) {
			return TokenResult::None;
		}

		char *inner_context = nullptr;
		result = static_cast< i64 >(strtoll(str, &inner_context, 10));
		return (inner_context != str) ? TokenResult::Valid : TokenResult::Invalid;
	}
	
	TokenResult StringPrefixToU64(const char *str, u64 &result) noexcept {
		if (!str) {
			return TokenResult::None;
		}

		char *inner_context = nullptr;
		result = static_cast< u64 >(strtoull(str, &inner_context, 10));
		return (inner_context != str) ? TokenResult::Valid : TokenResult::Invalid;
	}
	
	TokenResult StringPrefixToFloat(const char *str, float &result) noexcept {
		if (!str) {
			return TokenResult::None;
		}

		char *inner_context = nullptr;
		result = strtof(str, &inner_context);
		return (inner_context != str) ? TokenResult::Valid : TokenResult::Invalid;
	}
	
	TokenResult StringPrefixToDouble(const char *str, double &result) noexcept {
		if (!str) {
			return TokenResult::None;
		}

		char *inner_context = nullptr;
		result = strtod(str, &inner_context);
		return (inner_context != str) ? TokenResult::Valid : TokenResult::Invalid;
	}

#pragma endregion

	//-------------------------------------------------------------------------
	// Parsing Utilities: Reading
	//-------------------------------------------------------------------------
#pragma region

	TokenResult ReadChars(char *str, char **context, char **result, const char *delimiters) noexcept {
		Assert(str || context);
		Assert(result);
		Assert(delimiters);
		
		*result = strtok_s(str, delimiters, context);
		if (!result) {
			return TokenResult::None;
		}

		return TokenResult::Valid;
	}
	
	TokenResult ReadString(char *str, char **context, string &result, const char *delimiters) {
		Assert(str || context);
		Assert(delimiters);
		
		const char *token = strtok_s(str, delimiters, context);
		if (!token) {
			return TokenResult::None;
		}
		
		result = token;

		return TokenResult::Valid;
	}
	
	TokenResult ReadQuotedString(char *str, char **context, string &result, const char *delimiters) {
		Assert(str || context);
		Assert(delimiters);
		
		char *start = (str) ? SkipDelimiters(str, delimiters) : SkipDelimiters(*context, delimiters);
		if (!start) {
			return TokenResult::None;
		}

		char *first_quote = str_escape_first(start, '"');
		if (!first_quote) {
			return TokenResult::Invalid;
		}
		char *last_quote = str_escape_first(first_quote + 1, '"');
		if (!last_quote) {
			return TokenResult::Invalid;
		}

		if (!str_contains(delimiters, *(last_quote + 1))) {
			return TokenResult::Invalid;
		}

		*last_quote = '\0';
		result = first_quote + 1;
		*context = last_quote + 1;
		return TokenResult::Valid;
	}
	
	TokenResult ReadBool(char *str, char **context, bool &result, const char *delimiters) noexcept {
		Assert(str || context);
		Assert(delimiters);
		
		const char *token = strtok_s(str, delimiters, context);
		return StringToBool(token, result);
	}
	
	TokenResult ReadI8(char *str, char **context, i8 &result, const char *delimiters) noexcept {
		Assert(str || context);
		Assert(delimiters);
		
		const char *token = strtok_s(str, delimiters, context);
		return StringToI8(token, result);
	}
	
	TokenResult ReadU8(char *str, char **context, u8 &result, const char *delimiters) noexcept {
		Assert(str || context);
		Assert(delimiters);
		
		const char *token = strtok_s(str, delimiters, context);
		return StringToU8(token, result);
	}
	
	TokenResult ReadI16(char *str, char **context, i16 &result, const char *delimiters) noexcept {
		Assert(str || context);
		Assert(delimiters);
		
		const char *token = strtok_s(str, delimiters, context);
		return StringToI16(token, result);
	}
	
	TokenResult ReadU16(char *str, char **context, u16 &result, const char *delimiters) noexcept {
		Assert(str || context);
		Assert(delimiters);
		
		const char *token = strtok_s(str, delimiters, context);
		return StringToU16(token, result);
	}
	
	TokenResult ReadI32(char *str, char **context, i32 &result, const char *delimiters) noexcept {
		Assert(str || context);
		Assert(delimiters);
		
		const char *token = strtok_s(str, delimiters, context);
		return StringToI32(token, result);
	}
	
	TokenResult ReadU32(char *str, char **context, u32 &result, const char *delimiters) noexcept {
		Assert(str || context);
		Assert(delimiters);
		
		const char *token = strtok_s(str, delimiters, context);
		return StringToU32(token, result);
	}
	
	TokenResult ReadI64(char *str, char **context, i64 &result, const char *delimiters) noexcept {
		Assert(str || context);
		Assert(delimiters);
		
		const char *token = strtok_s(str, delimiters, context);
		return StringToI64(token, result);
	}
	
	TokenResult ReadU64(char *str, char **context, u64 &result, const char *delimiters) noexcept {
		Assert(str || context);
		Assert(delimiters);
		
		const char *token = strtok_s(str, delimiters, context);
		return StringToU64(token, result);
	}
	
	TokenResult ReadFloat(char *str, char **context, float &result, const char *delimiters) noexcept {
		Assert(str || context);
		Assert(delimiters);
		
		const char *token = strtok_s(str, delimiters, context);
		return StringToFloat(token, result);
	}
	
	TokenResult ReadDouble(char *str, char **context, double &result, const char *delimiters) noexcept {
		Assert(str || context);
		Assert(delimiters);
		
		const char *token = strtok_s(str, delimiters, context);
		return StringToDouble(token, result);
	}
	
	TokenResult ReadFloat2(char *str, char **context, XMFLOAT2 &result, const char *delimiters) noexcept {
		Assert(str || context);
		Assert(delimiters);
		
		const TokenResult token_result_x = ReadFloat(str, context, result.x, delimiters);
		if (token_result_x != TokenResult::Valid) {
			return token_result_x;
		}

		const TokenResult token_result_y = ReadFloat(str, context, result.y, delimiters);
		if (token_result_y != TokenResult::Valid) {
			return token_result_y;
		}
		
		return TokenResult::Valid;
	}
	
	TokenResult ReadFloat3(char *str, char **context, XMFLOAT3 &result, const char *delimiters) noexcept {
		Assert(str || context);
		Assert(delimiters);
		
		const TokenResult token_result_x = ReadFloat(str, context, result.x, delimiters);
		if (token_result_x != TokenResult::Valid) {
			return token_result_x;
		}

		const TokenResult token_result_y = ReadFloat(str, context, result.y, delimiters);
		if (token_result_y != TokenResult::Valid) {
			return token_result_y;
		}

		const TokenResult token_result_z = ReadFloat(str, context, result.z, delimiters);
		if (token_result_z != TokenResult::Valid) {
			return token_result_z;
		}

		return TokenResult::Valid;
	}
	
	TokenResult ReadFloat4(char *str, char **context, XMFLOAT4 &result, const char *delimiters) noexcept {
		Assert(str || context);
		Assert(delimiters);
		
		const TokenResult token_result_x = ReadFloat(str, context, result.x, delimiters);
		if (token_result_x != TokenResult::Valid) {
			return token_result_x;
		}

		const TokenResult token_result_y = ReadFloat(str, context, result.y, delimiters);
		if (token_result_y != TokenResult::Valid) {
			return token_result_y;
		}

		const TokenResult token_result_z = ReadFloat(str, context, result.z, delimiters);
		if (token_result_z != TokenResult::Valid) {
			return token_result_z;
		}

		const TokenResult token_result_w = ReadFloat(str, context, result.w, delimiters);
		if (token_result_w != TokenResult::Valid) {
			return token_result_w;
		}

		return TokenResult::Valid;
	}

#pragma endregion

	//-------------------------------------------------------------------------
	// Parsing Utilities: Peaking
	//-------------------------------------------------------------------------
#pragma region

	TokenResult HasChars(const char *str, const char *delimiters) noexcept {
		Assert(str);
		Assert(delimiters);
		
		const char *start = SkipDelimiters(str, delimiters);
		return (start) ? TokenResult::Valid : TokenResult::None;
	}
	
	TokenResult HasString(const char *str, const char *delimiters) noexcept {
		Assert(str);
		Assert(delimiters);

		return HasChars(str, delimiters);
	}
	
	TokenResult HasQuotedString(const char *str, const char *delimiters) noexcept {
		Assert(str);
		Assert(delimiters);
		
		const char *start = SkipDelimiters(str, delimiters);
		if (!start) {
			return TokenResult::None;
		}
		
		const char *first_quote = str_escape_first(start, '"');
		if (!first_quote) {
			return TokenResult::Invalid;
		}
		const char *last_quote = str_escape_first(first_quote + 1, '"');
		if (!last_quote) {
			return TokenResult::Invalid;
		}
		
		return str_contains(delimiters, *(last_quote + 1)) ? TokenResult::Valid : TokenResult::Invalid;
	}
	
	TokenResult HasBool(const char *str, const char *delimiters) noexcept {
		Assert(str);
		Assert(delimiters);
		
		const char *start = SkipDelimiters(str, delimiters);
		if (!start) {
			return TokenResult::None;
		}
		const char *end = GotoDelimiters(start, delimiters);

		bool result;
		return StringToBool(start, end, result);
	}
	
	TokenResult HasI8(const char *str, const char *delimiters) noexcept {
		Assert(str);
		Assert(delimiters);
		
		const char *start = SkipDelimiters(str, delimiters);
		if (!start) {
			return TokenResult::None;
		}
		const char *end = GotoDelimiters(start, delimiters);

		i8 result;
		return StringToI8(start, end, result);
	}
	
	TokenResult HasU8(const char *str, const char *delimiters) noexcept {
		Assert(str);
		Assert(delimiters);
		
		const char *start = SkipDelimiters(str, delimiters);
		if (!start) {
			return TokenResult::None;
		}
		const char *end = GotoDelimiters(start, delimiters);

		u8 result;
		return StringToU8(start, end, result);
	}
	
	TokenResult HasI16(const char *str, const char *delimiters) noexcept {
		Assert(str);
		Assert(delimiters);
		
		const char *start = SkipDelimiters(str, delimiters);
		if (!start) {
			return TokenResult::None;
		}
		const char *end = GotoDelimiters(start, delimiters);

		i16 result;
		return StringToI16(start, end, result);
	}
	
	TokenResult HasU16(const char *str, const char *delimiters) noexcept {
		Assert(str);
		Assert(delimiters);
		
		const char *start = SkipDelimiters(str, delimiters);
		if (!start) {
			return TokenResult::None;
		}
		const char *end = GotoDelimiters(start, delimiters);

		u16 result;
		return StringToU16(start, end, result);
	}
	
	TokenResult HasI32(const char *str, const char *delimiters) noexcept {
		Assert(str);
		Assert(delimiters);
		
		const char *start = SkipDelimiters(str, delimiters);
		if (!start) {
			return TokenResult::None;
		}
		const char *end = GotoDelimiters(start, delimiters);

		i32 result;
		return StringToI32(start, end, result);
	}
	
	TokenResult HasU32(const char *str, const char *delimiters) noexcept {
		Assert(str);
		Assert(delimiters);
		
		const char *start = SkipDelimiters(str, delimiters);
		if (!start) {
			return TokenResult::None;
		}
		const char *end = GotoDelimiters(start, delimiters);

		u32 result;
		return StringToU32(start, end, result);
	}
	
	TokenResult HasI64(const char *str, const char *delimiters) noexcept {
		Assert(str);
		Assert(delimiters);
		
		const char *start = SkipDelimiters(str, delimiters);
		if (!start) {
			return TokenResult::None;
		}
		const char *end = GotoDelimiters(start, delimiters);

		i64 result;
		return StringToI64(start, end, result);
	}
	
	TokenResult HasU64(const char *str, const char *delimiters) noexcept {
		Assert(str);
		Assert(delimiters);
		
		const char *start = SkipDelimiters(str, delimiters);
		if (!start) {
			return TokenResult::None;
		}
		const char *end = GotoDelimiters(start, delimiters);

		u64 result;
		return StringToU64(start, end, result);
	}
	
	TokenResult HasFloat(const char *str, const char *delimiters) noexcept {
		Assert(str);
		Assert(delimiters);
		
		const char *start = SkipDelimiters(str, delimiters);
		if (!start) {
			return TokenResult::None;
		}
		const char *end = GotoDelimiters(start, delimiters);

		float result;
		return StringToFloat(start, end, result);
	}
	
	TokenResult HasDouble(const char *str, const char *delimiters) noexcept {
		Assert(str);
		Assert(delimiters);
		
		const char *start = SkipDelimiters(str, delimiters);
		if (!start) {
			return TokenResult::None;
		}
		const char *end = GotoDelimiters(start, delimiters);

		double result;
		return StringToDouble(start, end, result);
	}

#pragma endregion

	//-------------------------------------------------------------------------
	// Parsing Utilities: Advancing
	//-------------------------------------------------------------------------
#pragma region

	char *SkipDelimiters(char *str, const char *delimiters) noexcept {
		Assert(str);
		Assert(delimiters);

		while (*str != '\0' && str_contains(delimiters, *str)) {
			++str;
		}
		
		return (*str != '\0') ? str : nullptr;
	}
	
	const char *SkipDelimiters(const char *str, const char *delimiters) noexcept {
		Assert(str);
		Assert(delimiters);
		
		while (*str != '\0' && str_contains(delimiters, *str)) {
			++str;
		}
		
		return (*str != '\0') ? str : nullptr;
	}
	
	char *GotoDelimiters(char *str, const char *delimiters) noexcept {
		Assert(str);
		Assert(delimiters);
		
		while (*str != '\0' && !str_contains(delimiters, *str)) {
			++str;
		}
		
		return (*str != '\0') ? str : nullptr;
	}
	
	const char *GotoDelimiters(const char *str, const char *delimiters) noexcept {
		Assert(str);
		Assert(delimiters);
		
		while (*str != '\0' && !str_contains(delimiters, *str)) {
			++str;
		}
		
		return (*str != '\0') ? str : nullptr;
	}

#pragma endregion
}