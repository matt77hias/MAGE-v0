//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "utils\string\token.hpp"
#include "utils\string\string_utils.hpp"

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
		return (str_equals(str, "false")) ? 
			TokenResult::Valid : TokenResult::Invalid;
	}
	
	TokenResult StringToS8(const char *str, S8 &result) noexcept {
		if (!str) {
			return TokenResult::None;
		}

		char *inner_context = nullptr;
		result = static_cast< S8 >(strtol(str, &inner_context, 10));
		return ('\0' == *inner_context) ?
			TokenResult::Valid : TokenResult::Invalid;
	}
	
	TokenResult StringToU8(const char *str, U8 &result) noexcept {
		if (!str) {
			return TokenResult::None;
		}

		char *inner_context = nullptr;
		result = static_cast< U8 >(strtoul(str, &inner_context, 10));
		return ('\0' == *inner_context) ? 
			TokenResult::Valid : TokenResult::Invalid;
	}
	
	TokenResult StringToS16(const char *str, S16 &result) noexcept {
		if (!str) {
			return TokenResult::None;
		}

		char *inner_context = nullptr;
		result = static_cast< S16 >(strtol(str, &inner_context, 10));
		return ('\0' == *inner_context) ? 
			TokenResult::Valid : TokenResult::Invalid;
	}
	
	TokenResult StringToU16(const char *str, U16 &result) noexcept {
		if (!str) {
			return TokenResult::None;
		}

		char *inner_context = nullptr;
		result = static_cast< U16 >(strtoul(str, &inner_context, 10));
		return ('\0' == *inner_context) ? 
			TokenResult::Valid : TokenResult::Invalid;
	}

	TokenResult StringToS32(const char *str, S32 &result) noexcept {
		if (!str) {
			return TokenResult::None;
		}

		char *inner_context = nullptr;
		result = static_cast< S32 >(strtol(str, &inner_context, 10));
		return ('\0' == *inner_context) ? 
			TokenResult::Valid : TokenResult::Invalid;
	}
	
	TokenResult StringToU32(const char *str, U32 &result) noexcept {
		if (!str) {
			return TokenResult::None;
		}

		char *inner_context = nullptr;
		result = static_cast< U32 >(strtoul(str, &inner_context, 10));
		return ('\0' == *inner_context) ? 
			TokenResult::Valid : TokenResult::Invalid;
	}
	
	TokenResult StringToS64(const char *str, S64 &result) noexcept {
		if (!str) {
			return TokenResult::None;
		}

		char *inner_context = nullptr;
		result = static_cast< S64 >(strtoll(str, &inner_context, 10));
		return ('\0' == *inner_context) ? 
			TokenResult::Valid : TokenResult::Invalid;
	}
	
	TokenResult StringToU64(const char *str, U64 &result) noexcept {
		if (!str) {
			return TokenResult::None;
		}

		char *inner_context = nullptr;
		result = static_cast< U64 >(strtoull(str, &inner_context, 10));
		return ('\0' == *inner_context) ? 
			TokenResult::Valid : TokenResult::Invalid;
	}
	
	TokenResult StringToF32(const char *str, F32 &result) noexcept {
		if (!str) {
			return TokenResult::None;
		}

		char *inner_context = nullptr;
		result = strtof(str, &inner_context);
		return ('\0' == *inner_context) ? 
			TokenResult::Valid : TokenResult::Invalid;
	}
	
	TokenResult StringToF64(const char *str, F64 &result) noexcept {
		if (!str) {
			return TokenResult::None;
		}

		char *inner_context = nullptr;
		result = strtod(str, &inner_context);
		return ('\0' == *inner_context) ? 
			TokenResult::Valid : TokenResult::Invalid;
	}
	
#pragma endregion

	//-------------------------------------------------------------------------
	// String Conversion Utilities: Substring
	//-------------------------------------------------------------------------
#pragma region

	TokenResult StringToBool(
		const char *begin, const char *end, bool &result) noexcept {
		
		if (!begin) {
			return TokenResult::None;
		}

		Assert(end);

		if (4 == end - begin) {
			if (('t' != *begin) || 
				('r' != *(begin + 1)) || 
				('u' != *(begin + 2)) || 
				('e' != *(begin + 3))) {
				
				result = false;
				return TokenResult::Invalid;
			}

			result = true;
			return TokenResult::Valid;
		} 
		
		if (5 == end - begin) {
			if (('f' != *begin) ||
				('a' != *(begin + 1)) ||
				('l' != *(begin + 2)) ||
				('s' != *(begin + 3)) ||
				('e' != *(begin + 4))) {
				
				result = false;
				return TokenResult::Invalid;
			}

			result = false;
			return TokenResult::Valid;
		}
		
		result = false;
		return TokenResult::Invalid;
	}
	
	TokenResult StringToS8(
		const char *begin, const char *end, S8 &result) noexcept {
		
		if (!begin) {
			return TokenResult::None;
		}

		Assert(end);

		char *inner_context = nullptr;
		result = static_cast< S8 >(strtol(begin, &inner_context, 10));
		return (end == inner_context) ? TokenResult::Valid : TokenResult::Invalid;
	}
	
	TokenResult StringToU8(
		const char *begin, const char *end, U8 &result) noexcept {
		
		if (!begin) {
			return TokenResult::None;
		}

		Assert(end);

		char *inner_context = nullptr;
		result = static_cast< U8 >(strtoul(begin, &inner_context, 10));
		return (end == inner_context) ? TokenResult::Valid : TokenResult::Invalid;
	}
	
	TokenResult StringToS16(
		const char *begin, const char *end, S16 &result) noexcept {
		
		if (!begin) {
			return TokenResult::None;
		}

		Assert(end);

		char *inner_context = nullptr;
		result = static_cast< S16 >(strtol(begin, &inner_context, 10));
		return (end == inner_context) ? TokenResult::Valid : TokenResult::Invalid;
	}
	
	TokenResult StringToU16(
		const char *begin, const char *end, U16 &result) noexcept {
		
		if (!begin) {
			return TokenResult::None;
		}

		Assert(end);

		char *inner_context = nullptr;
		result = static_cast< U16 >(strtoul(begin, &inner_context, 10));
		return (end == inner_context) ? TokenResult::Valid : TokenResult::Invalid;
	}
	
	TokenResult StringToS32(
		const char *begin, const char *end, S32 &result) noexcept {
		
		if (!begin) {
			return TokenResult::None;
		}

		Assert(end);

		char *inner_context = nullptr;
		result = static_cast< S32 >(strtol(begin, &inner_context, 10));
		return (end == inner_context) ? TokenResult::Valid : TokenResult::Invalid;
	}
	
	TokenResult StringToU32(
		const char *begin, const char *end, U32 &result) noexcept {
		
		if (!begin) {
			return TokenResult::None;
		}

		Assert(end);

		char *inner_context = nullptr;
		result = static_cast< U32 >(strtoul(begin, &inner_context, 10));
		return (end == inner_context) ? TokenResult::Valid : TokenResult::Invalid;
	}
	
	TokenResult StringToS64(
		const char *begin, const char *end, S64 &result) noexcept {
		
		if (!begin) {
			return TokenResult::None;
		}

		Assert(end);

		char *inner_context = nullptr;
		result = static_cast< S64 >(strtoll(begin, &inner_context, 10));
		return (end == inner_context) ? TokenResult::Valid : TokenResult::Invalid;
	}
	
	TokenResult StringToU64(
		const char *begin, const char *end, U64 &result) noexcept {
		
		if (!begin) {
			return TokenResult::None;
		}

		Assert(end);

		char *inner_context = nullptr;
		result = static_cast< U64 >(strtoull(begin, &inner_context, 10));
		return (end == inner_context) ? TokenResult::Valid : TokenResult::Invalid;
	}
	
	TokenResult StringToF32(
		const char *begin, const char *end, F32 &result) noexcept {
		
		if (!begin) {
			return TokenResult::None;
		}

		Assert(end);

		char *inner_context = nullptr;
		result = strtof(begin, &inner_context);
		return (end == inner_context) ? TokenResult::Valid : TokenResult::Invalid;
	}
	
	TokenResult StringToF64(
		const char *begin, const char *end, F64 &result) noexcept {
		
		if (!begin) {
			return TokenResult::None;
		}

		Assert(end);

		char *inner_context = nullptr;
		result = strtod(begin, &inner_context);
		return (end == inner_context) ? TokenResult::Valid : TokenResult::Invalid;
	}

#pragma endregion

	//-------------------------------------------------------------------------
	// String Conversion Utilities: String Prefix
	//-------------------------------------------------------------------------
#pragma region

	TokenResult StringPrefixToS8(const char *str, S8 &result) noexcept {
		if (!str) {
			return TokenResult::None;
		}

		char *inner_context = nullptr;
		result = static_cast< S8 >(strtol(str, &inner_context, 10));
		return (str != inner_context) ? 
			TokenResult::Valid : TokenResult::Invalid;
	}
	
	TokenResult StringPrefixToU8(const char *str, U8 &result) noexcept {
		if (!str) {
			return TokenResult::None;
		}

		char *inner_context = nullptr;
		result = static_cast< U8 >(strtoul(str, &inner_context, 10));
		return (str != inner_context) ? 
			TokenResult::Valid : TokenResult::Invalid;
	}
	
	TokenResult StringPrefixToS16(const char *str, S16 &result) noexcept {
		if (!str) {
			return TokenResult::None;
		}

		char *inner_context = nullptr;
		result = static_cast< S16 >(strtol(str, &inner_context, 10));
		return (str != inner_context) ? 
			TokenResult::Valid : TokenResult::Invalid;
	}
	
	TokenResult StringPrefixToU16(const char *str, U16 &result) noexcept {
		if (!str) {
			return TokenResult::None;
		}

		char *inner_context = nullptr;
		result = static_cast< U16 >(strtoul(str, &inner_context, 10));
		return (str != inner_context) ? 
			TokenResult::Valid : TokenResult::Invalid;
	}
	
	TokenResult StringPrefixToS32(const char *str, S32 &result) noexcept {
		if (!str) {
			return TokenResult::None;
		}

		char *inner_context = nullptr;
		result = static_cast< S32 >(strtol(str, &inner_context, 10));
		return (str != inner_context) ? 
			TokenResult::Valid : TokenResult::Invalid;
	}
	
	TokenResult StringPrefixToU32(const char *str, U32 &result) noexcept {
		if (!str) {
			return TokenResult::None;
		}

		char *inner_context = nullptr;
		result = static_cast< U32>(strtoul(str, &inner_context, 10));
		return (str != inner_context) ? 
			TokenResult::Valid : TokenResult::Invalid;
	}
	
	TokenResult StringPrefixToS64(const char *str, S64 &result) noexcept {
		if (!str) {
			return TokenResult::None;
		}

		char *inner_context = nullptr;
		result = static_cast< S64 >(strtoll(str, &inner_context, 10));
		return (str != inner_context) ? 
			TokenResult::Valid : TokenResult::Invalid;
	}
	
	TokenResult StringPrefixToU64(const char *str, U64 &result) noexcept {
		if (!str) {
			return TokenResult::None;
		}

		char *inner_context = nullptr;
		result = static_cast< U64 >(strtoull(str, &inner_context, 10));
		return (str != inner_context) ? 
			TokenResult::Valid : TokenResult::Invalid;
	}
	
	TokenResult StringPrefixToF32(const char *str, F32 &result) noexcept {
		if (!str) {
			return TokenResult::None;
		}

		char *inner_context = nullptr;
		result = strtof(str, &inner_context);
		return (str != inner_context) ? 
			TokenResult::Valid : TokenResult::Invalid;
	}
	
	TokenResult StringPrefixToF64(const char *str, F64 &result) noexcept {
		if (!str) {
			return TokenResult::None;
		}

		char *inner_context = nullptr;
		result = strtod(str, &inner_context);
		return (str != inner_context) ? 
			TokenResult::Valid : TokenResult::Invalid;
	}

#pragma endregion

	//-------------------------------------------------------------------------
	// Parsing Utilities: Reading
	//-------------------------------------------------------------------------
#pragma region

	TokenResult ReadChars(char *str, char **context, 
		char **result, const char *delimiters) noexcept {
		
		Assert(str || context);
		Assert(result);
		Assert(delimiters);
		
		*result = strtok_s(str, delimiters, context);
		if (!result) {
			return TokenResult::None;
		}

		return TokenResult::Valid;
	}
	
	TokenResult ReadString(char *str, char **context, 
		string &result, const char *delimiters) {
		
		Assert(str || context);
		Assert(delimiters);
		
		const char *token = strtok_s(str, delimiters, context);
		if (!token) {
			return TokenResult::None;
		}
		
		result = token;

		return TokenResult::Valid;
	}
	
	TokenResult ReadQuotedString(char *str, char **context, 
		string &result, const char *delimiters) {
		
		Assert(str || context);
		Assert(delimiters);
		
		char *start = (str) ? 
			SkipDelimiters(str, delimiters) : SkipDelimiters(*context, delimiters);
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
	
	TokenResult ReadBool(char *str, char **context, 
		bool &result, const char *delimiters) noexcept {
		
		Assert(str || context);
		Assert(delimiters);
		
		const char *token = strtok_s(str, delimiters, context);
		return StringToBool(token, result);
	}
	
	TokenResult ReadS8(char *str, char **context, 
		S8 &result, const char *delimiters) noexcept {
		
		Assert(str || context);
		Assert(delimiters);
		
		const char *token = strtok_s(str, delimiters, context);
		return StringToS8(token, result);
	}
	
	TokenResult ReadU8(char *str, char **context, 
		U8 &result, const char *delimiters) noexcept {
		
		Assert(str || context);
		Assert(delimiters);
		
		const char *token = strtok_s(str, delimiters, context);
		return StringToU8(token, result);
	}
	
	TokenResult ReadS16(char *str, char **context, 
		S16 &result, const char *delimiters) noexcept {
		
		Assert(str || context);
		Assert(delimiters);
		
		const char *token = strtok_s(str, delimiters, context);
		return StringToS16(token, result);
	}
	
	TokenResult ReadU16(char *str, char **context, 
		U16 &result, const char *delimiters) noexcept {
		
		Assert(str || context);
		Assert(delimiters);
		
		const char *token = strtok_s(str, delimiters, context);
		return StringToU16(token, result);
	}
	
	TokenResult ReadS32(char *str, char **context, 
		S32 &result, const char *delimiters) noexcept {
		
		Assert(str || context);
		Assert(delimiters);
		
		const char *token = strtok_s(str, delimiters, context);
		return StringToS32(token, result);
	}
	
	TokenResult ReadU32(char *str, char **context, 
		U32 &result, const char *delimiters) noexcept {
		
		Assert(str || context);
		Assert(delimiters);
		
		const char *token = strtok_s(str, delimiters, context);
		return StringToU32(token, result);
	}
	
	TokenResult ReadS64(char *str, char **context, 
		S64 &result, const char *delimiters) noexcept {
		
		Assert(str || context);
		Assert(delimiters);
		
		const char *token = strtok_s(str, delimiters, context);
		return StringToS64(token, result);
	}
	
	TokenResult ReadU64(char *str, char **context, 
		U64 &result, const char *delimiters) noexcept {
		
		Assert(str || context);
		Assert(delimiters);
		
		const char *token = strtok_s(str, delimiters, context);
		return StringToU64(token, result);
	}
	
	TokenResult ReadFloat(char *str, char **context, 
		F32 &result, const char *delimiters) noexcept {
		
		Assert(str || context);
		Assert(delimiters);
		
		const char *token = strtok_s(str, delimiters, context);
		return StringToF32(token, result);
	}
	
	TokenResult ReadDouble(char *str, char **context, 
		F64 &result, const char *delimiters) noexcept {
		
		Assert(str || context);
		Assert(delimiters);
		
		const char *token = strtok_s(str, delimiters, context);
		return StringToF64(token, result);
	}
	
	TokenResult ReadFloat2(char *str, char **context, 
		XMFLOAT2 &result, const char *delimiters) noexcept {
		
		Assert(str || context);
		Assert(delimiters);
		
		const TokenResult token_result_x 
			= ReadFloat(str, context, result.x, delimiters);
		if (token_result_x != TokenResult::Valid) {
			return token_result_x;
		}

		const TokenResult token_result_y 
			= ReadFloat(str, context, result.y, delimiters);
		if (token_result_y != TokenResult::Valid) {
			return token_result_y;
		}
		
		return TokenResult::Valid;
	}
	
	TokenResult ReadFloat3(char *str, char **context, 
		XMFLOAT3 &result, const char *delimiters) noexcept {
		
		Assert(str || context);
		Assert(delimiters);
		
		const TokenResult token_result_x 
			= ReadFloat(str, context, result.x, delimiters);
		if (token_result_x != TokenResult::Valid) {
			return token_result_x;
		}

		const TokenResult token_result_y 
			= ReadFloat(str, context, result.y, delimiters);
		if (token_result_y != TokenResult::Valid) {
			return token_result_y;
		}

		const TokenResult token_result_z
			= ReadFloat(str, context, result.z, delimiters);
		if (token_result_z != TokenResult::Valid) {
			return token_result_z;
		}

		return TokenResult::Valid;
	}
	
	TokenResult ReadFloat4(char *str, char **context, 
		XMFLOAT4 &result, const char *delimiters) noexcept {
		
		Assert(str || context);
		Assert(delimiters);
		
		const TokenResult token_result_x 
			= ReadFloat(str, context, result.x, delimiters);
		if (token_result_x != TokenResult::Valid) {
			return token_result_x;
		}

		const TokenResult token_result_y 
			= ReadFloat(str, context, result.y, delimiters);
		if (token_result_y != TokenResult::Valid) {
			return token_result_y;
		}

		const TokenResult token_result_z 
			= ReadFloat(str, context, result.z, delimiters);
		if (token_result_z != TokenResult::Valid) {
			return token_result_z;
		}

		const TokenResult token_result_w 
			= ReadFloat(str, context, result.w, delimiters);
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
		
		return str_contains(delimiters, *(last_quote + 1)) ? 
			TokenResult::Valid : TokenResult::Invalid;
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
	
	TokenResult HasS8(const char *str, const char *delimiters) noexcept {
		Assert(str);
		Assert(delimiters);
		
		const char *start = SkipDelimiters(str, delimiters);
		if (!start) {
			return TokenResult::None;
		}
		const char *end = GotoDelimiters(start, delimiters);

		S8 result;
		return StringToS8(start, end, result);
	}
	
	TokenResult HasU8(const char *str, const char *delimiters) noexcept {
		Assert(str);
		Assert(delimiters);
		
		const char *start = SkipDelimiters(str, delimiters);
		if (!start) {
			return TokenResult::None;
		}
		const char *end = GotoDelimiters(start, delimiters);

		U8 result;
		return StringToU8(start, end, result);
	}
	
	TokenResult HasS16(const char *str, const char *delimiters) noexcept {
		Assert(str);
		Assert(delimiters);
		
		const char *start = SkipDelimiters(str, delimiters);
		if (!start) {
			return TokenResult::None;
		}
		const char *end = GotoDelimiters(start, delimiters);

		S16 result;
		return StringToS16(start, end, result);
	}
	
	TokenResult HasU16(const char *str, const char *delimiters) noexcept {
		Assert(str);
		Assert(delimiters);
		
		const char *start = SkipDelimiters(str, delimiters);
		if (!start) {
			return TokenResult::None;
		}
		const char *end = GotoDelimiters(start, delimiters);

		U16 result;
		return StringToU16(start, end, result);
	}
	
	TokenResult HasS32(const char *str, const char *delimiters) noexcept {
		Assert(str);
		Assert(delimiters);
		
		const char *start = SkipDelimiters(str, delimiters);
		if (!start) {
			return TokenResult::None;
		}
		const char *end = GotoDelimiters(start, delimiters);

		S32 result;
		return StringToS32(start, end, result);
	}
	
	TokenResult HasU32(const char *str, const char *delimiters) noexcept {
		Assert(str);
		Assert(delimiters);
		
		const char *start = SkipDelimiters(str, delimiters);
		if (!start) {
			return TokenResult::None;
		}
		const char *end = GotoDelimiters(start, delimiters);

		U32 result;
		return StringToU32(start, end, result);
	}
	
	TokenResult HasS64(const char *str, const char *delimiters) noexcept {
		Assert(str);
		Assert(delimiters);
		
		const char *start = SkipDelimiters(str, delimiters);
		if (!start) {
			return TokenResult::None;
		}
		const char *end = GotoDelimiters(start, delimiters);

		S64 result;
		return StringToS64(start, end, result);
	}
	
	TokenResult HasU64(const char *str, const char *delimiters) noexcept {
		Assert(str);
		Assert(delimiters);
		
		const char *start = SkipDelimiters(str, delimiters);
		if (!start) {
			return TokenResult::None;
		}
		const char *end = GotoDelimiters(start, delimiters);

		U64 result;
		return StringToU64(start, end, result);
	}
	
	TokenResult HasF32(const char *str, const char *delimiters) noexcept {
		Assert(str);
		Assert(delimiters);
		
		const char *start = SkipDelimiters(str, delimiters);
		if (!start) {
			return TokenResult::None;
		}
		const char *end = GotoDelimiters(start, delimiters);

		F32 result;
		return StringToF32(start, end, result);
	}
	
	TokenResult HasF64(const char *str, const char *delimiters) noexcept {
		Assert(str);
		Assert(delimiters);
		
		const char *start = SkipDelimiters(str, delimiters);
		if (!start) {
			return TokenResult::None;
		}
		const char *end = GotoDelimiters(start, delimiters);

		F64 result;
		return StringToF64(start, end, result);
	}

#pragma endregion

	//-------------------------------------------------------------------------
	// Parsing Utilities: Advancing
	//-------------------------------------------------------------------------
#pragma region

	char *SkipDelimiters(char *str, const char *delimiters) noexcept {
		Assert(str);
		Assert(delimiters);

		while ('\0' != *str && str_contains(delimiters, *str)) {
			++str;
		}
		
		return ('\0' != *str) ? str : nullptr;
	}
	
	const char *SkipDelimiters(const char *str, const char *delimiters) noexcept {
		Assert(str);
		Assert(delimiters);
		
		while ('\0' != *str && str_contains(delimiters, *str)) {
			++str;
		}
		
		return ('\0' != *str) ? str : nullptr;
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