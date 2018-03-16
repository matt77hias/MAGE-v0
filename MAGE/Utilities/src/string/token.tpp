#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "logging\error.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	//-------------------------------------------------------------------------
	// String Conversion Utilities: Complete String
	//-------------------------------------------------------------------------
	#pragma region

	template<>
	inline TokenResult StringTo(const_zstring str, bool& result) noexcept {
		if (!str) {
			return TokenResult::None;
		}

		if (str_equals(str, "true")) {
			result = true;
			return TokenResult::Valid;
		}
		
		result = false;
		return (str_equals(str, "false")) ? TokenResult::Valid 
			                              : TokenResult::Invalid;
	}
	
	template<>
	inline TokenResult StringTo(const_zstring str, S8& result) noexcept {
		if (!str) {
			return TokenResult::None;
		}

		char* inner_context = nullptr;
		result = static_cast< S8 >(strtol(str, &inner_context, 10));
		return ('\0' == *inner_context) ? TokenResult::Valid 
			                            : TokenResult::Invalid;
	}
	
	template<>
	inline TokenResult StringTo(const_zstring str, U8& result) noexcept {
		if (!str) {
			return TokenResult::None;
		}

		char* inner_context = nullptr;
		result = static_cast< U8 >(strtoul(str, &inner_context, 10));
		return ('\0' == *inner_context) ? TokenResult::Valid 
			                            : TokenResult::Invalid;
	}
	
	template<>
	inline TokenResult StringTo(const_zstring str, S16& result) noexcept {
		if (!str) {
			return TokenResult::None;
		}

		char* inner_context = nullptr;
		result = static_cast< S16 >(strtol(str, &inner_context, 10));
		return ('\0' == *inner_context) ? TokenResult::Valid 
			                            : TokenResult::Invalid;
	}
	
	template<>
	inline TokenResult StringTo(const_zstring str, U16& result) noexcept {
		if (!str) {
			return TokenResult::None;
		}

		char* inner_context = nullptr;
		result = static_cast< U16 >(strtoul(str, &inner_context, 10));
		return ('\0' == *inner_context) ? TokenResult::Valid 
			                            : TokenResult::Invalid;
	}

	template<>
	inline TokenResult StringTo(const_zstring str, S32& result) noexcept {
		if (!str) {
			return TokenResult::None;
		}

		char* inner_context = nullptr;
		result = static_cast< S32 >(strtol(str, &inner_context, 10));
		return ('\0' == *inner_context) ? TokenResult::Valid 
			                            : TokenResult::Invalid;
	}
	
	template<>
	inline TokenResult StringTo(const_zstring str, U32& result) noexcept {
		if (!str) {
			return TokenResult::None;
		}

		char* inner_context = nullptr;
		result = static_cast< U32 >(strtoul(str, &inner_context, 10));
		return ('\0' == *inner_context) ? TokenResult::Valid 
			                            : TokenResult::Invalid;
	}
	
	template<>
	inline TokenResult StringTo(const_zstring str, S64& result) noexcept {
		if (!str) {
			return TokenResult::None;
		}

		char* inner_context = nullptr;
		result = static_cast< S64 >(strtoll(str, &inner_context, 10));
		return ('\0' == *inner_context) ? TokenResult::Valid 
			                            : TokenResult::Invalid;
	}
	
	template<>
	inline TokenResult StringTo(const_zstring str, U64& result) noexcept {
		if (!str) {
			return TokenResult::None;
		}

		char* inner_context = nullptr;
		result = static_cast< U64 >(strtoull(str, &inner_context, 10));
		return ('\0' == *inner_context) ? TokenResult::Valid 
			                            : TokenResult::Invalid;
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
	
	#pragma endregion

	//-------------------------------------------------------------------------
	// String Conversion Utilities: Substring
	//-------------------------------------------------------------------------
	#pragma region

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
		
		result = false;
		return TokenResult::Invalid;
	}
	
	template<>
	inline TokenResult StringTo(const_zstring begin, const_zstring end,
								S8& result) noexcept {

		if (!begin || !end) {
			return TokenResult::None;
		}

		char* inner_context = nullptr;
		result = static_cast< S8 >(strtol(begin, &inner_context, 10));
		return (end == inner_context) ? TokenResult::Valid 
			                          : TokenResult::Invalid;
	}
	
	template<>
	inline TokenResult StringTo(const_zstring begin, const_zstring end,
								U8& result) noexcept {

		if (!begin || !end) {
			return TokenResult::None;
		}

		char* inner_context = nullptr;
		result = static_cast< U8 >(strtoul(begin, &inner_context, 10));
		return (end == inner_context) ? TokenResult::Valid 
			                          : TokenResult::Invalid;
	}
	
	template<>
	inline TokenResult StringTo(const_zstring begin, const_zstring end,
								S16& result) noexcept {

		if (!begin || !end) {
			return TokenResult::None;
		}

		char* inner_context = nullptr;
		result = static_cast< S16 >(strtol(begin, &inner_context, 10));
		return (end == inner_context) ? TokenResult::Valid 
			                          : TokenResult::Invalid;
	}
	
	template<>
	inline TokenResult StringTo(const_zstring begin, const_zstring end,
								U16& result) noexcept {

		if (!begin || !end) {
			return TokenResult::None;
		}

		char* inner_context = nullptr;
		result = static_cast< U16 >(strtoul(begin, &inner_context, 10));
		return (end == inner_context) ? TokenResult::Valid 
			                          : TokenResult::Invalid;
	}
	
	template<>
	inline TokenResult StringTo(const_zstring begin, const_zstring end,
								S32& result) noexcept {

		if (!begin || !end) {
			return TokenResult::None;
		}

		char* inner_context = nullptr;
		result = static_cast< S32 >(strtol(begin, &inner_context, 10));
		return (end == inner_context) ? TokenResult::Valid 
			                          : TokenResult::Invalid;
	}
	
	template<>
	inline TokenResult StringTo(const_zstring begin, const_zstring end,
								U32& result) noexcept {

		if (!begin || !end) {
			return TokenResult::None;
		}

		char* inner_context = nullptr;
		result = static_cast< U32 >(strtoul(begin, &inner_context, 10));
		return (end == inner_context) ? TokenResult::Valid 
			                          : TokenResult::Invalid;
	}
	
	template<>
	inline TokenResult StringTo(const_zstring begin, const_zstring end,
								S64& result) noexcept {

		if (!begin || !end) {
			return TokenResult::None;
		}

		char* inner_context = nullptr;
		result = static_cast< S64 >(strtoll(begin, &inner_context, 10));
		return (end == inner_context) ? TokenResult::Valid 
			                          : TokenResult::Invalid;
	}
	
	template<>
	inline TokenResult StringTo(const_zstring begin, const_zstring end,
								U64& result) noexcept {

		if (!begin || !end) {
			return TokenResult::None;
		}

		char* inner_context = nullptr;
		result = static_cast< U64 >(strtoull(begin, &inner_context, 10));
		return (end == inner_context) ? TokenResult::Valid 
			                          : TokenResult::Invalid;
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

	#pragma endregion

	//-------------------------------------------------------------------------
	// String Conversion Utilities: String Prefix
	//-------------------------------------------------------------------------
	#pragma region

	template<>
	inline TokenResult StringPrefixTo(const_zstring str, S8& result) noexcept {
		if (!str) {
			return TokenResult::None;
		}

		char* inner_context = nullptr;
		result = static_cast< S8 >(strtol(str, &inner_context, 10));
		return (str != inner_context) ? TokenResult::Valid 
			                          : TokenResult::Invalid;
	}
	
	template<>
	inline TokenResult StringPrefixTo(const_zstring str, U8& result) noexcept {
		if (!str) {
			return TokenResult::None;
		}

		char* inner_context = nullptr;
		result = static_cast< U8 >(strtoul(str, &inner_context, 10));
		return (str != inner_context) ? TokenResult::Valid 
			                          : TokenResult::Invalid;
	}
	
	template<>
	inline TokenResult StringPrefixTo(const_zstring str, S16& result) noexcept {
		if (!str) {
			return TokenResult::None;
		}

		char* inner_context = nullptr;
		result = static_cast< S16 >(strtol(str, &inner_context, 10));
		return (str != inner_context) ? TokenResult::Valid 
			                          : TokenResult::Invalid;
	}
	
	template<>
	inline TokenResult StringPrefixTo(const_zstring str, U16& result) noexcept {
		if (!str) {
			return TokenResult::None;
		}

		char* inner_context = nullptr;
		result = static_cast< U16 >(strtoul(str, &inner_context, 10));
		return (str != inner_context) ? TokenResult::Valid 
			                          : TokenResult::Invalid;
	}
	
	template<>
	inline TokenResult StringPrefixTo(const_zstring str, S32& result) noexcept {
		if (!str) {
			return TokenResult::None;
		}

		char* inner_context = nullptr;
		result = static_cast< S32 >(strtol(str, &inner_context, 10));
		return (str != inner_context) ? TokenResult::Valid 
			                          : TokenResult::Invalid;
	}
	
	template<>
	inline TokenResult StringPrefixTo(const_zstring str, U32& result) noexcept {
		if (!str) {
			return TokenResult::None;
		}

		char* inner_context = nullptr;
		result = static_cast< U32>(strtoul(str, &inner_context, 10));
		return (str != inner_context) ? TokenResult::Valid 
			                          : TokenResult::Invalid;
	}
	
	template<>
	inline TokenResult StringPrefixTo(const_zstring str, S64& result) noexcept {
		if (!str) {
			return TokenResult::None;
		}

		char* inner_context = nullptr;
		result = static_cast< S64 >(strtoll(str, &inner_context, 10));
		return (str != inner_context) ? TokenResult::Valid 
			                          : TokenResult::Invalid;
	}
	
	template<>
	inline TokenResult StringPrefixTo(const_zstring str, U64& result) noexcept {
		if (!str) {
			return TokenResult::None;
		}

		char* inner_context = nullptr;
		result = static_cast< U64 >(strtoull(str, &inner_context, 10));
		return (str != inner_context) ? TokenResult::Valid 
			                          : TokenResult::Invalid;
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
		
		// read the x component.
		{
			const auto tr = Read< F32 >(str, context, result.m_x, delimiters);
			if (TokenResult::Valid != tr) {
				return tr;
			}
		}

		// read the y component.
		{
			const auto tr = Read< F32 >(str, context, result.m_y, delimiters);
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
		
		// read the x component.
		{
			const auto tr = Read< F32 >(str, context, result.m_x, delimiters);
			if (TokenResult::Valid != tr) {
				return tr;
			}
		}

		// read the y component.
		{
			const auto tr = Read< F32 >(str, context, result.m_y, delimiters);
			if (TokenResult::Valid != tr) {
				return tr;
			}
		}

		// read the z component.
		{
			const auto tr = Read< F32 >(str, context, result.m_z, delimiters);
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
		
		// read the x component.
		{
			const auto tr = Read< F32 >(str, context, result.m_x, delimiters);
			if (TokenResult::Valid != tr) {
				return tr;
			}
		}

		// read the y component.
		{
			const auto tr = Read< F32 >(str, context, result.m_y, delimiters);
			if (TokenResult::Valid != tr) {
				return tr;
			}
		}

		// read the z component.
		{
			const auto tr = Read< F32 >(str, context, result.m_z, delimiters);
			if (TokenResult::Valid != tr) {
				return tr;
			}
		}

		// read the w component.
		{
			const auto tr = Read< F32 >(str, context, result.m_w, delimiters);
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