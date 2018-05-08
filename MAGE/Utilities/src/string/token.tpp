#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "logging\error.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// System Includes
//-----------------------------------------------------------------------------
#pragma region

#include <charconv>

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	//-------------------------------------------------------------------------
	// String Conversion Utilities
	//-------------------------------------------------------------------------
	#pragma region

	template< typename DataT >
	inline TokenResult StringTo(const_zstring str, DataT& result) noexcept {
		if (!str) {
			return TokenResult::None;
		}

		using std::from_chars;
		const auto r = from_chars(str, nullptr, result);
		
		if ('\0' != *r.ptr
			|| std::errc::invalid_argument    == r.ec
			|| std::errc::result_out_of_range == r.ec) {

			return TokenResult::Invalid;
		}
		else {
			return TokenResult::Valid;
		}
	}

	template<>
	inline TokenResult StringTo(const_zstring str, bool& result) noexcept {
		if (!str) {
			return TokenResult::None;
		}

		if (str_equals(str, "true")) {
			result = true;
			return TokenResult::Valid;
		}
		
		if (str_equals(str, "false")) {
			result = false;
			return TokenResult::Valid;
		}
		
		return TokenResult::Invalid;
	}
	
	template<>
	inline TokenResult StringTo(const_zstring str, F32& result) noexcept {
		if (!str) {
			return TokenResult::None;
		}

		char* inner_context = nullptr;
		result = strtof(str, &inner_context);
		return ('\0' == *inner_context) ? TokenResult::Valid 
			                            : TokenResult::Invalid;
	}
	
	template<>
	inline TokenResult StringTo(const_zstring str, F64& result) noexcept {
		if (!str) {
			return TokenResult::None;
		}

		char* inner_context = nullptr;
		result = strtod(str, &inner_context);
		return ('\0' == *inner_context) ? TokenResult::Valid 
			                            : TokenResult::Invalid;
	}
	
	template< typename DataT >
	inline TokenResult StringTo(const_zstring begin, const_zstring end, 
								DataT& result) noexcept {

		if (!begin || !end) {
			return TokenResult::None;
		}

		using std::from_chars;
		const auto r = from_chars(begin, end, result);
		
		if (end != r.ptr
			|| std::errc::invalid_argument    == r.ec
			|| std::errc::result_out_of_range == r.ec) {

			return TokenResult::Invalid;
		}
		else {
			return TokenResult::Valid;
		}
	}

	template<>
	inline TokenResult StringTo(const_zstring begin, const_zstring end,
								bool& result) noexcept {
		if (!begin || !end) {
			return TokenResult::None;
		}

		if ((  4 == end - begin)  && 
			('t' == *begin)       && 
			('r' == *(begin + 1)) && 
			('u' == *(begin + 2)) && 
			('e' == *(begin + 3))) {
			
			result = true;
			return TokenResult::Valid;
		} 
		
		if ((  5 == end - begin)  && 
			('f' == *begin)       && 
			('a' == *(begin + 1)) && 
			('l' == *(begin + 2)) && 
			('s' == *(begin + 3)) && 
			('e' == *(begin + 4))) {
				
			result = false;
			return TokenResult::Valid;
		}
		
		return TokenResult::Invalid;
	}
	
	template<>
	inline TokenResult StringTo(const_zstring begin, const_zstring end,
								F32& result) noexcept {

		if (!begin || !end) {
			return TokenResult::None;
		}

		char* inner_context = nullptr;
		result = strtof(begin, &inner_context);
		return (end == inner_context) ? TokenResult::Valid 
			                          : TokenResult::Invalid;
	}
	
	template<>
	inline TokenResult StringTo(const_zstring begin, const_zstring end,
								F64& result) noexcept {

		if (!begin || !end) {
			return TokenResult::None;
		}

		char* inner_context = nullptr;
		result = strtod(begin, &inner_context);
		return (end == inner_context) ? TokenResult::Valid 
			                          : TokenResult::Invalid;
	}

	template< typename DataT >
	inline TokenResult StringPrefixTo(const_zstring str, DataT& result) noexcept {
		if (!str) {
			return TokenResult::None;
		}

		using std::from_chars;
		const auto r = from_chars(str, nullptr, result);

		if (str == *r.ptr
			|| std::errc::invalid_argument    == r.ec
			|| std::errc::result_out_of_range == r.ec) {

			return TokenResult::Invalid;
		}
		else {
			return TokenResult::Valid;
		}
	}

	template<>
	inline TokenResult StringPrefixTo(const_zstring str, F32& result) noexcept {
		if (!str) {
			return TokenResult::None;
		}

		char* inner_context = nullptr;
		result = strtof(str, &inner_context);
		return (str != inner_context) ? TokenResult::Valid 
			                          : TokenResult::Invalid;
	}
	
	template<>
	inline TokenResult StringPrefixTo(const_zstring str, F64& result) noexcept {
		if (!str) {
			return TokenResult::None;
		}

		char* inner_context = nullptr;
		result = strtod(str, &inner_context);
		return (str != inner_context) ? TokenResult::Valid 
			                          : TokenResult::Invalid;
	}

	#pragma endregion

	//-------------------------------------------------------------------------
	// Parsing Utilities: Reading
	//-------------------------------------------------------------------------
	#pragma region

	inline TokenResult ReadChars(zstring str, zstring* context, 
								 NotNull< zstring* > result,
								 NotNull< const_zstring > delimiters) noexcept {
		
		Assert(str || context);
		
		*result = strtok_s(str, delimiters, context);
		return result ? TokenResult::Valid : TokenResult::None;
	}
	
	template< typename DataT >
	inline TokenResult Read(zstring str, zstring* context, DataT& result,
							NotNull< const_zstring > delimiters) noexcept {
		
		Assert(str || context);
		
		const auto* const token = strtok_s(str, delimiters, context);
		return StringTo< DataT >(token, result);
	}

	template<>
	inline TokenResult Read(zstring str, zstring* context, string& result,
							NotNull< const_zstring > delimiters) noexcept {

		Assert(str || context);

		const auto* const token = strtok_s(str, delimiters, context);
		if (!token) {
			return TokenResult::None;
		}

		// Copy assignment forced to be noexcept.
		result = token;

		return TokenResult::Valid;
	}

	template<>
	inline TokenResult Read(zstring str, zstring* context, F32x2& result,
							NotNull< const_zstring > delimiters) noexcept {
		
		Assert(str || context);
		
		// Read the x component.
		{
			const auto tr = Read< F32 >(str, context, result[0], delimiters);
			if (TokenResult::Valid != tr) {
				return tr;
			}
		}

		// Read the y component.
		{
			const auto tr = Read< F32 >(str, context, result[1], delimiters);
			if (TokenResult::Valid != tr) {
				return tr;
			}
		}

		return TokenResult::Valid;
	}
	
	template<>
	inline TokenResult Read(zstring str, zstring* context, F32x3& result,
							NotNull< const_zstring > delimiters) noexcept {
		
		Assert(str || context);
		
		// Read the x component.
		{
			const auto tr = Read< F32 >(str, context, result[0], delimiters);
			if (TokenResult::Valid != tr) {
				return tr;
			}
		}

		// Read the y component.
		{
			const auto tr = Read< F32 >(str, context, result[1], delimiters);
			if (TokenResult::Valid != tr) {
				return tr;
			}
		}

		// Read the z component.
		{
			const auto tr = Read< F32 >(str, context, result[2], delimiters);
			if (TokenResult::Valid != tr) {
				return tr;
			}
		}

		return TokenResult::Valid;
	}
	
	template<>
	inline TokenResult Read(zstring str, zstring* context, F32x4& result,
							NotNull< const_zstring > delimiters) noexcept {
		
		Assert(str || context);
		
		// Read the x component.
		{
			const auto tr = Read< F32 >(str, context, result[0], delimiters);
			if (TokenResult::Valid != tr) {
				return tr;
			}
		}

		// Read the y component.
		{
			const auto tr = Read< F32 >(str, context, result[1], delimiters);
			if (TokenResult::Valid != tr) {
				return tr;
			}
		}

		// Read the z component.
		{
			const auto tr = Read< F32 >(str, context, result[2], delimiters);
			if (TokenResult::Valid != tr) {
				return tr;
			}
		}

		// Read the w component.
		{
			const auto tr = Read< F32 >(str, context, result[3], delimiters);
			if (TokenResult::Valid != tr) {
				return tr;
			}
		}

		return TokenResult::Valid;
	}

	#pragma endregion

	//-------------------------------------------------------------------------
	// Parsing Utilities: Peaking
	//-------------------------------------------------------------------------
	#pragma region

	inline TokenResult ContainsChars(NotNull< zstring > str,
									 NotNull< const_zstring > delimiters) noexcept {

		const auto start = SkipDelimiters(str, delimiters);
		return (start) ? TokenResult::Valid : TokenResult::None;
	}
	
	template< typename DataT >
	TokenResult Contains(NotNull< zstring > str, 
						 NotNull< const_zstring > delimiters) noexcept {

		const auto start = SkipDelimiters(str, delimiters);
		if (!start) {
			return TokenResult::None;
		}
		
		const auto end = GotoDelimiters(NotNull< zstring >(start), delimiters);

		DataT result;
		return StringTo< DataT >(start, end, result);
	}

	template<>
	inline TokenResult Contains< string >(NotNull< zstring > str,
										  NotNull< const_zstring > delimiters) noexcept {
		
		return ContainsChars(str, delimiters);
	}
	
	#pragma endregion
}