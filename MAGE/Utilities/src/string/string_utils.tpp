#pragma once

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	template< typename T >
	[[nodiscard]]
	inline const std::optional< T > StringTo(NotNull< const char* > first,
											 NotNull< const char* > last) noexcept {
		T result = {};
		
		using std::from_chars;
		const auto [ptr, error_code] = from_chars(first, last, result);
		
		if (last != ptr
			|| std::errc::invalid_argument    == error_code
			|| std::errc::result_out_of_range == error_code) {

			return {};
		}
		else {
			return result;
		}
	}

	template<>
	[[nodiscard]]
	inline const std::optional< bool > StringTo(NotNull< const char* > first,
												NotNull< const char* > last) noexcept {
		const char* const cfirst = first;
		const char* const clast  = last;
		
		if ((  4 == clast - cfirst)  && 
			('t' == *cfirst)       && 
			('r' == *(cfirst + 1)) && 
			('u' == *(cfirst + 2)) && 
			('e' == *(cfirst + 3))) {
			
			return true;
		} 
		
		if ((  5 == clast - cfirst)  && 
			('f' == *cfirst)       && 
			('a' == *(cfirst + 1)) && 
			('l' == *(cfirst + 2)) && 
			('s' == *(cfirst + 3)) && 
			('e' == *(cfirst + 4))) {
				
			return false;
		}
		
		return {};
	}
	
	template< typename T >
	[[nodiscard]]
	inline const std::optional< T > StringTo(NotNull< const_zstring > str) noexcept {
		const char* const cstr = str;
		return StringTo< T >(str, NotNull< const_zstring >(cstr + std::strlen(cstr)));
	}

	template< typename T >
	[[nodiscard]]
	inline const std::optional< T > StringPrefixTo(NotNull< const_zstring > str) noexcept {
		T result = {};

		using std::from_chars;
		const auto [ptr, error_code] = from_chars(str, str + std::strlen(str), result);

		if (str == *ptr
			|| std::errc::invalid_argument    == error_code
			|| std::errc::result_out_of_range == error_code) {

			return {};
		}
		else {
			return result;
		}
	}
}