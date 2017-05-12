#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "string\string.hpp"
#include "logging\error.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 Checks whether the given strings are equal.

	 @pre			@a str1 is not equal to @c nullptr.
	 @pre			@a str2 is not equal to @c nullptr.
	 @param[in]		str1
					A pointer to the first null-terminated byte string.
	 @param[in]		str2
					A pointer to the second null-terminated byte string.
	 @return		@c true if @a str1 is equal to @a str2.
					@c false otherwise.
	 */
	inline bool str_equals(const char *str1, const char *str2) noexcept {
		Assert(str1);
		Assert(str2);
		return strcmp(str1, str2) ? false : true;
	}

	/**
	 Checks whether the given strings are equal.

	 @pre			@a str1 is not equal to @c nullptr.
	 @pre			@a str2 is not equal to @c nullptr.
	 @param[in]		str1
					A pointer to the first null-terminated wide string.
	 @param[in]		str2
					A pointer to the second null-terminated wide string.
	 @return		@c true if @a str1 is equal to @a str2.
					@c false otherwise.
	 */
	inline bool str_equals(const wchar_t *str1, const wchar_t *str2) noexcept {
		Assert(str1);
		Assert(str2);
		return wcscmp(str1, str2) ? false : true;
	}

	/**
	 Checks whether the first given string contains the second given string.

	 @pre			@a str1 is not equal to @c nullptr.
	 @pre			@a str2 is not equal to @c nullptr.
	 @param[in]		str1
					A pointer to the null-terminated byte string to be scanned.
	 @param[in]		str2
					A pointer to the null-terminated byte string 
					containing the sequence of characters to match.
	 @return		@c true if @a str1 contains a substring @a str2.
					@c false otherwise.
	 */
	inline bool str_contains(const char *str1, const char *str2) noexcept {
		Assert(str1);
		Assert(str2);
		return strstr(str1, str2) ? true : false;
	}

	/**
	 Checks whether the first given string contains the second given string.

	 @pre			@a str1 is not equal to @c nullptr.
	 @pre			@a str2 is not equal to @c nullptr.
	 @param[in]		str1
					A pointer to the null-terminated wide string to be scanned.
	 @param[in]		str2
					A pointer to the null-terminated wide string 
					containing the sequence of characters to match.
	 @return		@c true if @a str1 contains a substring @a str2.
					@c false otherwise.
	 */
	inline bool str_contains(const wchar_t *str1, const wchar_t *str2) noexcept {
		Assert(str1);
		Assert(str2);
		return wcsstr(str1, str2) ? true : false;
	}

	/**
	 Checks whether the first given string contains the given character.

	 @pre			@a str is not equal to @c nullptr.
	 @param[in]		str
					A pointer to the null-terminated byte string to be scanned.
	 @param[in]		c
					The byte character to match.
	 @return		@c true if @a str contains a @a c.
					@c false otherwise.
	 */
	inline bool str_contains(const char *str, char c) noexcept {
		Assert(str);
		return strchr(str, (int)c) ? true : false;
	}

	/**
	 Checks whether the first given string contains the given character.

	 @pre			@a str is not equal to @c nullptr.
	 @param[in]		str
					A pointer to the null-terminated wide string to be scanned.
	 @param[in]		c
					The wide character to match.
	 @return		@c true if @a str contains a @a c.
					@c false otherwise.
	 */
	inline bool str_contains(const wchar_t *str, wchar_t c) noexcept {
		Assert(str);
		return wcschr(str, c) ? true : false;
	}

	/**
	 Finds the first occurrence of the given character in the given string
	 neglecting the usage of the given character in a custom escape sequence. 
	 
	 @pre			@a str is not equal to @c nullptr.
	 @param[in]		str
					A pointer to the null-terminated byte string to be scanned.
	 @param[in]		c
					The byte character to match.
	 @return		@c nullptr if @a str does not contain @a c.
	 @return		A pointer to the first occurrence of @a c in @a str.

	 */
	const char *str_escape_first(const char *str, char c) noexcept;

	/**
	 Finds the first occurrence of the given character in the given string
	 neglecting the usage of the given character in a custom escape sequence.

	 @pre			@a str is not equal to @c nullptr.
	 @param[in]		str
					A pointer to the null-terminated byte string to be scanned.
	 @param[in]		c
					The byte character to match.
	 @return		@c nullptr if @a str does not contain @a c.
	 @return		A pointer to the first occurrence of @a c in @a str.

	 */
	char *str_escape_first(char *str, char c) noexcept;

	/**
	 Finds the first occurrence of the given character in the given string
	 neglecting the usage of the given character in a custom escape sequence.

	 @pre			@a str is not equal to @c nullptr.
	 @param[in]		str
					A pointer to the null-terminated wide string to be scanned.
	 @param[in]		c
					The wide character to match.
	 @return		@c nullptr if @a str does not contain @a c.
	 @return		A pointer to the first occurrence of @a c in @a str.

	 */
	const wchar_t *str_escape_first(const wchar_t *str, wchar_t c) noexcept;

	/**
	 Finds the first occurrence of the given character in the given string
	 neglecting the usage of the given character in a custom escape sequence.

	 @pre			@a str is not equal to @c nullptr.
	 @param[in]		str
					A pointer to the null-terminated wide string to be scanned.
	 @param[in]		c
					The wide character to match.
	 @return		@c nullptr if @a str does not contain @a c.
	 @return		A pointer to the first occurrence of @a c in @a str.

	 */
	wchar_t *str_escape_first(wchar_t *str, wchar_t c) noexcept;

	/**
	 Reads characters from the given input string and stores them as a C string into @a str 
	 until (num-1) characters have been read or either a newline or the end-of-file is reached, 
	 whichever happens first.

	 A newline character makes @c sgets stop reading, but it is considered a valid character 
	 by the function and included in the string copied to @a str.

	 A terminating null character is automatically appended after the characters copied to @a str.
	 
	 @pre			@a str is not equal to @c nullptr.
	 @pre			@a input is not equal to @c nullptr.
	 @param[in]		str
					A pointer to the null-terminated byte string to copy to.
	 @param[in]		num
					Maximum number of characters to be copied into @a str 
					(including the terminating null-character).
	 @param[in]		input
					A pointer to a pointer to the input string.
	 @note			The @c sgets function is the byte string variant of @c fgets.
	 */
	char *str_gets(char *str, int num, const char **input) noexcept;

	/**
	 Reads characters from the given input string and stores them as a C string into @a str
	 until (num-1) characters have been read or either a newline or the end-of-file is reached,
	 whichever happens first.

	 A newline character makes @c sgets stop reading, but it is considered a valid character
	 by the function and included in the string copied to @a str.

	 A terminating null character is automatically appended after the characters copied to @a str.

	 @pre			@a str is not equal to @c nullptr.
	 @pre			@a input is not equal to @c nullptr.
	 @param[in]		str
					A pointer to the null-terminated wide string to copy to.
	 @param[in]		num
					Maximum number of characters to be copied into @a str 
					(including the terminating null-character).
	 @param[in]		input
					A pointer to a pointer to the input string.
	 @note			The @c sgets function is the wide string variant of @c fgets.
	 */
	wchar_t *str_gets(wchar_t *str, int num, const wchar_t **input) noexcept;

	/**
	 Converts the given byte string to a wide string.

	 @pre			@a str is not equal to @c nullptr.
	 @param[in]		str
					A pointer to the null-terminated byte string to copy.
	 @return		A pointer to the to the null-terminated wide string copy
					of the given null-terminated byte string.
	 */
	const wchar_t *str_convert(const char *str) noexcept;

	/**
	 Converts the given wide string to an byte string.

	 @pre			@a str is not equal to @c nullptr.
	 @param[in]		str
					A pointer to the null-terminated wide string to copy.
	 @return		A pointer to the to the null-terminated byte string copy
					of the given null-terminated wide string.
	 */
	const char *str_convert(const wchar_t *str) noexcept;

	/**
	 Converts the given byte string to a wide string.

	 @param[in]		str
					A reference to the byte string to copy.
	 @return		The wide string copy of the given byte string.
	 */
	const wstring str_convert(const string &str) noexcept;
	
	/**
	 Converts the given wide string to an byte string.

	 @param[in]		str
					A reference to the wide string to copy.
	 @return		The byte string copy of the given wide string.
	 */
	const string str_convert(const wstring &str) noexcept;
}