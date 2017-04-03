#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "string\string.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 Checks whether the given strings are equal.

	 @param[in]		str1
					A pointer to the first string.
	 @param[in]		str2
					A pointer to the second string.
	 @return		@c true if @a str1 is equal to @a str2.
					@c false otherwise.
	 */
	inline bool str_equals(const char *str1, const char *str2) {
		return strcmp(str1, str2) ? false : true;
	}

	/**
	 Checks whether the given strings are equal.

	 @param[in]		str1
					A pointer to the first string.
	 @param[in]		str2
					A pointer to the second string.
	 @return		@c true if @a str1 is equal to @a str2.
					@c false otherwise.
	 */
	inline bool str_equals(const wchar_t *str1, const wchar_t *str2) {
		return wcscmp(str1, str2) ? false : true;
	}

	/**
	 Checks whether the first given string contains the second given string.

	 @param[in]		str1
					A pointer to the string to be scanned.
	 @param[in]		str2
					A pointer to the string containing the sequence of characters to match.
	 @return		@c true if @a str1 contains a substring @a str2.
					@c false otherwise.
	 */
	inline bool str_contains(const char *str1, const char *str2) {
		return strstr(str1, str2) ? true : false;
	}

	/**
	 Checks whether the first given string contains the second given string.

	 @param[in]		str1
					A pointer to the string to be scanned.
	 @param[in]		str2
					A pointer to the string containing the sequence of characters to match.
	 @return		@c true if @a str1 contains a substring @a str2.
					@c false otherwise.
	 */
	inline bool str_contains(const wchar_t *str1, const wchar_t *str2) {
		return wcsstr(str1, str2) ? true : false;
	}

	/**
	 Checks whether the first given string contains the given character.

	 @param[in]		str
					A pointer to the string to be scanned.
	 @param[in]		c
					The character to match.
	 @return		@c true if @a str contains a @a c.
					@c false otherwise.
	 */
	inline bool str_contains(const char *str, char c) {
		return strchr(str, (int)c) ? true : false;
	}

	/**
	 Checks whether the first given string contains the given character.

	 @param[in]		str
					A pointer to the string to be scanned.
	 @param[in]		c
					The character to match.
	 @return		@c true if @a str contains a @a c.
					@c false otherwise.
	 */
	inline bool str_contains(const wchar_t *str, wchar_t c) {
		return wcschr(str, c) ? true : false;
	}

	/**
	 Finds the first occurrence of the given character in the given string
	 neglecting the usage of the given character in a custom escape sequence. 
	 
	 @param[in]		str
					A pointer to the string to be scanned.
	 @param[in]		c
					The character to match.
	 @return		@c nullptr if @a str does not contain @a c.
	 @return		A pointer to the first occurrence of @a c in @a str.

	 */
	const char *str_escape_first(const char *str, char c);

	/**
	 Finds the first occurrence of the given character in the given string
	 neglecting the usage of the given character in a custom escape sequence.

	 @param[in]		str
					A pointer to the string to be scanned.
	 @param[in]		c
					The character to match.
	 @return		@c nullptr if @a str does not contain @a c.
	 @return		A pointer to the first occurrence of @a c in @a str.

	 */
	char *str_escape_first(char *str, char c);

	/**
	 Finds the first occurrence of the given character in the given string
	 neglecting the usage of the given character in a custom escape sequence.

	 @param[in]		str
					A pointer to the string to be scanned.
	 @param[in]		c
					The character to match.
	 @return		@c nullptr if @a str does not contain @a c.
	 @return		A pointer to the first occurrence of @a c in @a str.

	 */
	const wchar_t *str_escape_first(const wchar_t *str, wchar_t c);

	/**
	 Finds the first occurrence of the given character in the given string
	 neglecting the usage of the given character in a custom escape sequence.

	 @param[in]		str
					A pointer to the string to be scanned.
	 @param[in]		c
					The character to match.
	 @return		@c nullptr if @a str does not contain @a c.
	 @return		A pointer to the first occurrence of @a c in @a str.

	 */
	wchar_t *str_escape_first(wchar_t *str, wchar_t c);

	/**
	 Reads characters from the given input string and stores them as a C string into @a str 
	 until (num-1) characters have been read or either a newline or the end-of-file is reached, 
	 whichever happens first.

	 A newline character makes @c sgets stop reading, but it is considered a valid character 
	 by the function and included in the string copied to @a str.

	 A terminating null character is automatically appended after the characters copied to @a str.
	 
	 @param[in]		str
					A pointer to the string to copy to.
	 @param[in]		num
					Maximum number of characters to be copied into @a str 
					(including the terminating null-character).
	 @param[in]		input
					A pointer to a pointer to the input string.
	 @note			The @c sgets function is the string variant of @c fgets.
	 */
	char *str_gets(char *str, int num, const char **input);

	/**
	 Reads characters from the given input string and stores them as a C string into @a str
	 until (num-1) characters have been read or either a newline or the end-of-file is reached,
	 whichever happens first.

	 A newline character makes @c sgets stop reading, but it is considered a valid character
	 by the function and included in the string copied to @a str.

	 A terminating null character is automatically appended after the characters copied to @a str.

	 @param[in]		str
					A pointer to the string to copy to.
	 @param[in]		num
					Maximum number of characters to be copied into @a str 
					(including the terminating null-character).
	 @param[in]		input
					A pointer to a pointer to the input string.
	 @note			The @c sgets function is the string variant of @c fgets.
	 */
	wchar_t *str_gets(wchar_t *str, int num, const wchar_t **input);

	/**
	 Converts the given ANSI string to a Wide string.

	 @param[in]		str
					A pointer to the string to copy.
	 @return		A pointer to the copy.
	 */
	wchar_t *str_convert(const char *str);

	/**
	 Converts the given Wide string to an ANSI string.

	 @param[in]		str
					A pointer to the string to copy.
	 @return		A pointer to the copy.
	 */
	char *str_convert(const wchar_t *str);

	/**
	 Converts the given ANSI string to a Wide string.

	 @param[in]		str
					A reference to the string to copy.
	 @return		The copy.
	 */
	const wstring str_convert(const string &str);
	
	/**
	 Converts the given Wide string to an ANSI string.

	 @param[in]		str
					A reference to the string to copy.
	 @return		The copy.
	 */
	const string str_convert(const wstring &str);
}