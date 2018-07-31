#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "string\string.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// System Includes
//-----------------------------------------------------------------------------
#pragma region

#include <algorithm>
#include <cctype>
#include <cwctype>
#include <optional>

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	//-------------------------------------------------------------------------
	// StringEquals, StringContains
	//-------------------------------------------------------------------------
	#pragma region

	/**
	 Checks whether the given null-terminated strings are equal.

	 @param[in]		str1
					The first null-terminated string.
	 @param[in]		str2
					The second null-terminated string.
	 @return		@c true if @a str1 is equal to @a str2. @c false otherwise.
	 */
	[[nodiscard]]
	inline bool StringEquals(NotNull< const_zstring > str1, 
							 NotNull< const_zstring > str2) noexcept {
		
		return strcmp(str1, str2) ? false : true;
	}

	/**
	 Checks whether the given null-terminated strings are equal.

	 @param[in]		str1
					The first null-terminated string.
	 @param[in]		str2
					The second null-terminated string.
	 @return		@c true if @a str1 is equal to @a str2. @c false otherwise.
	 */
	[[nodiscard]]
	inline bool StringEquals(NotNull< const_wzstring > str1, 
							 NotNull< const_wzstring > str2) noexcept {
		
		return wcscmp(str1, str2) ? false : true;
	}

	/**
	 Checks whether the first given null-terminated string contains the second 
	 given null-terminated string.

	 @param[in]		str1
					The null-terminated string to be scanned.
	 @param[in]		str2
					The null-terminated string containing the sequence of 
					characters to match.
	 @return		@c true if @a str1 contains a substring @a str2. @c false 
					otherwise.
	 */
	[[nodiscard]]
	inline bool StringContains(NotNull< const_zstring > str1, 
							   NotNull< const_zstring > str2) noexcept {

		return strstr(str1, str2) ? true : false;
	}

	/**
	 Checks whether the first given null-terminated string contains the second 
	 given null-terminated string.

	 @param[in]		str1
					The null-terminated string to be scanned.
	 @param[in]		str2
					The null-terminated string containing the sequence of 
					characters to match.
	 @return		@c true if @a str1 contains a substring @a str2. @c false 
					otherwise.
	 */
	[[nodiscard]]
	inline bool StringContains(NotNull< const_wzstring > str1,
							   NotNull< const_wzstring > str2) noexcept {
		
		return wcsstr(str1, str2) ? true : false;
	}

	/**
	 Checks whether the given null-terminated string contains the given character.

	 @param[in]		str
					The null-terminated string to be scanned.
	 @param[in]		c
					The byte character to match.
	 @return		@c true if @a str contains a @a c. @c false otherwise.
	 */
	[[nodiscard]]
	inline bool StringContains(NotNull< const_zstring > str, 
							   char c) noexcept {

		return strchr(str, static_cast< int >(c)) ? true : false;
	}

	/**
	 Checks whether the given null-terminated string contains the given character.

	 @param[in]		str
					The null-terminated string to be scanned.
	 @param[in]		c
					The wide character to match.
	 @return		@c true if @a str contains a @a c. @c false otherwise.
	 */
	[[nodiscard]]
	inline bool StringContains(NotNull< const_wzstring > str, 
							   wchar_t c) noexcept {

		return wcschr(str, c) ? true : false;
	}

	#pragma endregion

	//-------------------------------------------------------------------------
	// String Conversions
	//-------------------------------------------------------------------------
	#pragma region

	/**
	 Converts the given string range to a @c T value.

	 @tparam		T
					The data type.
	 @param[in]		first
					A pointer to the begin (inclusive) of the string to 
					convert.
	 @param[in]		last
					A pointer to the end (exclusive) of the string to convert.
	 @return		A @c T value if the the conversion of the given string 
					range succeeded.
	 */
	template< typename T >
	[[nodiscard]]
	const std::optional< T > StringTo(NotNull< const char* > first, 
									  NotNull< const char* > last) noexcept;
	
	/**
	 Converts the given string to a @c T value.

	 @tparam		T
					The data type.
	 @param[in]		str
					A pointer to the null-terminated string to convert.
	 @return		A @c T value if the the conversion of the given string 
					succeeded.
	 */
	template< typename T >
	[[nodiscard]]
	const std::optional< T > StringTo(NotNull< const_zstring > str) noexcept;

	/**
	 Converts the prefix of the string to a @c T value.

	 @tparam		T
					The data type.
	 @param[in]		str
					A pointer to the null-terminated string to convert.
	 @return		A @c T value if the the conversion of the prefix of the 
					given string succeeded.
	 */
	template< typename T >
	[[nodiscard]]
	const std::optional< T > StringPrefixTo(NotNull< const_zstring > str) noexcept;

	#pragma endregion

	//-------------------------------------------------------------------------
	// Inter-string Conversions
	//-------------------------------------------------------------------------
	#pragma region

	/**
	 Converts the given string to a wide string.

	 @param[in]		str
					A reference to the string to copy.
	 @return		The wide string copy of the given string.
	 */
	[[nodiscard]]
	const std::wstring StringToWString(const std::string& str);
	
	/**
	 Converts the given wide string to a string.

	 @param[in]		str
					A reference to the wide string to copy.
	 @return		The string copy of the given wide string.
	 */
	[[nodiscard]]
	const std::string WStringToString(const std::wstring& str);

	#pragma endregion

	//-------------------------------------------------------------------------
	// Transformations
	//-------------------------------------------------------------------------
	#pragma region

	/**
	 Transforms the given string to lower case.

	 @param[in,out] str
					A reference to the string to transform.
	 */
	inline void TransformToLowerCase(std::string& str) {
		using std::begin;
		using std::cbegin;
		using std::cend;

		constexpr auto f = [](char c) noexcept {
			return static_cast< char >(std::tolower(c));
		};
		std::transform(cbegin(str), cend(str), begin(str), f);
	}

	/**
	 Transforms the given string to lower case.

	 @param[in,out] str
					A reference to the string to transform.
	 */
	inline void TransformToLowerCase(std::wstring& str) {
		using std::begin;
		using std::cbegin;
		using std::cend;
		
		constexpr auto f = [](wchar_t c) noexcept {
			return static_cast< wchar_t >(std::towlower(c));
		};
		std::transform(cbegin(str), cend(str), begin(str), f);
	}

	/**
	 Transforms the given string to upper case.

	 @param[in,out] str
					A reference to the string to transform.
	 */
	inline void TransformToUpperCase(std::string& str) {
		using std::begin;
		using std::cbegin;
		using std::cend;
		
		constexpr auto f = [](char c) noexcept {
			return static_cast< char >(std::toupper(c));
		};
		std::transform(cbegin(str), cend(str), begin(str), f);
	}

	/**
	 Transforms the given string to upper case.

	 @param[in,out] str
					A reference to the string to transform.
	 */
	inline void TransformToUpperCase(std::wstring& str) {
		using std::begin;
		using std::cbegin;
		using std::cend;
		
		constexpr auto f = [](wchar_t c) noexcept {
			return static_cast< wchar_t >(std::towupper(c));
		};
		std::transform(cbegin(str), cend(str), begin(str), f);
	}

	#pragma endregion
}

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "string\string_utils.tpp"

#pragma endregion