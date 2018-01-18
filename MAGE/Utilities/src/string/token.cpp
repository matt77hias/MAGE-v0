//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "string\token.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	//-------------------------------------------------------------------------
	// Parsing Utilities: Reading
	//-------------------------------------------------------------------------
	#pragma region

	TokenResult ReadQuotedString(char *str, char **context, string &result, 
		                         const char *delimiters) {
		
		Assert(str || context);
		Assert(delimiters);
		
		char * const start = (str) ?
			SkipDelimiters(str, delimiters) : SkipDelimiters(*context, delimiters);
		if (!start) {
			return TokenResult::None;
		}

		char * const first_quote = str_escape_first(start, '"');
		if (!first_quote) {
			return TokenResult::Invalid;
		}
		char * const last_quote = str_escape_first(first_quote + 1, '"');
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
	
	#pragma endregion

	//-------------------------------------------------------------------------
	// Parsing Utilities: Peaking
	//-------------------------------------------------------------------------
	#pragma region

	TokenResult ContainsQuotedString(const char *str, const char *delimiters) noexcept {
		Assert(str);
		Assert(delimiters);
		
		const char * const start = SkipDelimiters(str, delimiters);
		if (!start) {
			return TokenResult::None;
		}
		
		const char * const first_quote = str_escape_first(start, '"');
		if (!first_quote) {
			return TokenResult::Invalid;
		}
		const char * const last_quote = str_escape_first(first_quote + 1, '"');
		if (!last_quote) {
			return TokenResult::Invalid;
		}
		
		return str_contains(delimiters, *(last_quote + 1)) ? 
			TokenResult::Valid : TokenResult::Invalid;
	}

	#pragma endregion

	//-------------------------------------------------------------------------
	// Parsing Utilities: Advancing
	//-------------------------------------------------------------------------
	#pragma region

	[[nodiscard]] char *
		SkipDelimiters(char *str, const char *delimiters) noexcept {
		
		Assert(str);
		Assert(delimiters);

		while ('\0' != *str && str_contains(delimiters, *str)) {
			++str;
		}
		
		return ('\0' != *str) ? str : nullptr;
	}
	
	[[nodiscard]] const char *
		SkipDelimiters(const char *str, const char *delimiters) noexcept {
		
		Assert(str);
		Assert(delimiters);
		
		while ('\0' != *str && str_contains(delimiters, *str)) {
			++str;
		}
		
		return ('\0' != *str) ? str : nullptr;
	}
	
	[[nodiscard]] char *
		GotoDelimiters(char *str, const char *delimiters) noexcept {
		
		Assert(str);
		Assert(delimiters);
		
		while (*str != '\0' && !str_contains(delimiters, *str)) {
			++str;
		}
		
		return (*str != '\0') ? str : nullptr;
	}
	
	[[nodiscard]] const char *
		GotoDelimiters(const char *str, const char *delimiters) noexcept {
		
		Assert(str);
		Assert(delimiters);
		
		while (*str != '\0' && !str_contains(delimiters, *str)) {
			++str;
		}
		
		return (*str != '\0') ? str : nullptr;
	}

	#pragma endregion
}