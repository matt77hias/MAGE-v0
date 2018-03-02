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

	TokenResult ReadQuotedString(zstring str, zstring* context, string& result,
								 NotNull< const_zstring > delimiters) noexcept {
		
		Assert(str || context);
		
		const auto start = (str) ? SkipDelimiters(NotNull< zstring >(str), 
												  delimiters)
			                     : SkipDelimiters(NotNull< zstring >(*context), 
												  delimiters);
		if (!start) {
			return TokenResult::None;
		}

		const auto first_quote = str_escape_first(NotNull< zstring >(start), 
												  '"');
		if (!first_quote) {
			return TokenResult::Invalid;
		}
		const auto last_quote  = str_escape_first(NotNull< zstring >(first_quote + 1), 
												  '"');
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

	TokenResult ContainsQuotedString(NotNull< zstring > str,
									 NotNull< const_zstring > delimiters) noexcept {
		
		const auto start = SkipDelimiters(str, delimiters);
		if (!start) {
			return TokenResult::None;
		}
		
		const auto first_quote = str_escape_first(NotNull< zstring >(start), 
												  '"');
		if (!first_quote) {
			return TokenResult::Invalid;
		}
		const auto last_quote  = str_escape_first(NotNull< zstring >(first_quote + 1), 
												  '"');
		if (!last_quote) {
			return TokenResult::Invalid;
		}
		
		return str_contains(delimiters, *(last_quote + 1)) ? TokenResult::Valid 
			                                               : TokenResult::Invalid;
	}

	#pragma endregion

	//-------------------------------------------------------------------------
	// Parsing Utilities: Advancing
	//-------------------------------------------------------------------------
	#pragma region

	[[nodiscard]]
	zstring SkipDelimiters(NotNull< zstring > str, 
						   NotNull< const_zstring > delimiters) noexcept {

		char* buffer = str;
		while ('\0' != *buffer && str_contains(delimiters, *buffer)) {
			++buffer;
		}
		
		return ('\0' != *buffer) ? buffer : nullptr;
	}
	
	[[nodiscard]]
	const_zstring SkipDelimiters(NotNull< const_zstring > str, 
								 NotNull< const_zstring > delimiters) noexcept {
		
		const char* buffer = str;
		while ('\0' != *buffer && str_contains(delimiters, *buffer)) {
			++buffer;
		}
		
		return ('\0' != *buffer) ? buffer : nullptr;
	}
	
	[[nodiscard]]
	zstring GotoDelimiters(NotNull< zstring > str, 
						   NotNull< const_zstring > delimiters) noexcept {

		char* buffer = str;
		while ('\0' != *buffer && !str_contains(delimiters, *buffer)) {
			++buffer;
		}
		
		return ('\0' != *buffer) ? buffer : nullptr;
	}
	
	[[nodiscard]]
	const_zstring GotoDelimiters(NotNull< const_zstring > str, 
								 NotNull< const_zstring > delimiters) noexcept {

		const char* buffer = str;
		while ('\0' != *buffer && !str_contains(delimiters, *buffer)) {
			++buffer;
		}
		
		return ('\0' != *buffer) ? buffer : nullptr;
	}

	#pragma endregion
}