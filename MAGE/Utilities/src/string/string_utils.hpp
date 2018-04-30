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

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	//-------------------------------------------------------------------------
	// Engine Declarations and Definitions: zstring, wzstring
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
	inline bool str_equals(NotNull< const_zstring > str1, 
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
	inline bool str_equals(NotNull< const_wzstring > str1, 
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
	inline bool str_contains(NotNull< const_zstring > str1,
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
	inline bool str_contains(NotNull< const_wzstring > str1,
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
	inline bool str_contains(NotNull< const_zstring > str, 
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
	inline bool str_contains(NotNull< const_wzstring > str, 
							 wchar_t c) noexcept {

		return wcschr(str, c) ? true : false;
	}

	/**
	 Finds the first occurrence of the given character in the given 
	 null-terminated string neglecting the usage of the given character in a 
	 custom escape sequence.

	 @param[in]		str
					The null-terminated string to be scanned.
	 @param[in]		c
					The byte character to match.
	 @return		@c nullptr if @a str does not contain @a c.
	 @return		A pointer to the first occurrence of @a c in @a str.

	 */
	[[nodiscard]]
	zstring str_escape_first(NotNull< zstring > str, 
							 char c) noexcept;

	/**
	 Finds the first occurrence of the given character in the given 
	 null-terminated string neglecting the usage of the given character in a 
	 custom escape sequence.

	 @param[in]		str
					The null-terminated string to be scanned.
	 @param[in]		c
					The byte character to match.
	 @return		@c nullptr if @a str does not contain @a c.
	 @return		A pointer to the first occurrence of @a c in @a str.

	 */
	[[nodiscard]]
	const_zstring str_escape_first(NotNull< const_zstring > str, 
								   char c) noexcept;

	/**
	 Finds the first occurrence of the given character in the given 
	 null-terminated string neglecting the usage of the given character in a 
	 custom escape sequence.

	 @param[in]		str
					The null-terminated string to be scanned.
	 @param[in]		c
					The wide character to match.
	 @return		@c nullptr if @a str does not contain @a c.
	 @return		A pointer to the first occurrence of @a c in @a str.

	 */
	[[nodiscard]]
	wzstring str_escape_first(NotNull< wzstring > str, 
							  wchar_t c) noexcept;

	/**
	 Finds the first occurrence of the given character in the given 
	 null-terminated string neglecting the usage of the given character in a 
	 custom escape sequence.

	 @param[in]		str
					The null-terminated string to be scanned.
	 @param[in]		c
					The wide character to match.
	 @return		@c nullptr if @a str does not contain @a c.
	 @return		A pointer to the first occurrence of @a c in @a str.

	 */
	[[nodiscard]]
	const_wzstring str_escape_first(NotNull< const_wzstring > str, 
									wchar_t c) noexcept;

	/**
	 Reads characters from the given input string and stores them into @a str 
	 until (@a num-1) characters have been read or either a newline or the 
	 null-terminating character is reached, whichever happens first.

	 A newline character makes @c sgets stop reading, but it is considered a 
	 valid character by the function and included in the string copied to 
	 @a str.

	 A null-terminating character is automatically appended after the 
	 characters copied to @a str.
	 
	 @param[in]		str
					A pointer to the string to copy to.
	 @param[in]		num
					Maximum number of characters to be copied into @a str 
					(including the terminating null-character).
	 @param[in]		input
					A pointer to a pointer to the input string.
	 @return		@c nullptr if the null-terminating character is reached.
	 @return		@a str.
	 @note			The @c sgets function is the string variant of @c fgets.
	 */
	[[nodiscard]] 
	zstring str_gets(NotNull< char* > str,
					 size_t num, 
					 NotNull< NotNull< const_zstring >* > input) noexcept;

	/**
	 Reads characters from the given input string and stores them into @a str 
	 until (@a num-1) characters have been read or either a newline or the 
	 null-terminating character is reached, whichever happens first.

	 A newline character makes @c sgets stop reading, but it is considered a 
	 valid character by the function and included in the string copied to 
	 @a str.

	 A null-terminating character is automatically appended after the 
	 characters copied to @a str.

	 @param[in]		str
					A pointer to the string to copy to.
	 @param[in]		num
					Maximum number of characters to be copied into @a str 
					(including the terminating null-character).
	 @param[in]		input
					A pointer to a pointer to the input string.
	 @return		@c nullptr if the null-terminating character is reached.
	 @return		@a str.
	 @note			The @c sgets function is the string variant of @c fgets.
	 */
	[[nodiscard]] 
	wzstring str_gets(NotNull< wchar_t* > str,
					  size_t num, 
					  NotNull< NotNull< const_wzstring >* > input) noexcept;

	#pragma endregion

	//-------------------------------------------------------------------------
	// Engine Declarations and Definitions: string, wstring
	//-------------------------------------------------------------------------
	#pragma region

	/**
	 Transforms the given string to lower case.

	 @param[in,out] str
					A reference to the string to transform.
	 */
	inline void TransformToLowerCase(string& str) {
		const auto f = [](char c) noexcept {
			return static_cast< char >(std::tolower(c));
		};
		std::transform(std::cbegin(str), std::cend(str), std::begin(str), f);
	}

	/**
	 Transforms the given string to lower case.

	 @param[in,out] str
					A reference to the string to transform.
	 */
	inline void TransformToLowerCase(wstring& str) {
		const auto f = [](wchar_t c) noexcept {
			return static_cast< wchar_t >(std::towlower(c));
		};
		std::transform(std::cbegin(str), std::cend(str), std::begin(str), f);
	}

	/**
	 Transforms the given string to upper case.

	 @param[in,out] str
					A reference to the string to transform.
	 */
	inline void TransformToUpperCase(string& str) {
		const auto f = [](char c) noexcept {
			return static_cast< char >(std::toupper(c));
		};
		std::transform(std::cbegin(str), std::cend(str), std::begin(str), f);
	}

	/**
	 Transforms the given string to upper case.

	 @param[in,out] str
					A reference to the string to transform.
	 */
	inline void TransformToUpperCase(wstring& str) {
		const auto f = [](wchar_t c) noexcept {
			return static_cast< wchar_t >(std::towupper(c));
		};
		std::transform(std::cbegin(str), std::cend(str), std::begin(str), f);
	}

	/**
	 Converts the given string to a wide string.

	 @param[in]		str
					A reference to the string to copy.
	 @return		The wide string copy of the given string.
	 */
	[[nodiscard]]
	const wstring str_convert(const string& str);
	
	/**
	 Converts the given wide string to a string.

	 @param[in]		str
					A reference to the wide string to copy.
	 @return		The string copy of the given wide string.
	 */
	[[nodiscard]]
	const string str_convert(const wstring& str);

	#pragma endregion
}