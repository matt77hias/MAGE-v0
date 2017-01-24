#pragma once

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 Checks whether the given string are equal.

	 @param[in]		str1
					A pointer to the string to be scanned.
	 @param[in]		str2
					A pointer to the string containing the sequence of characters to match.
	 @return		@c true if @a str1 is equal to @a str2.
					@c false otherwise.
	 */
	inline bool str_equals(const char *str1, const char *str2) {
		return (strcmp(str1, str2) == 0) ? true : false;
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
		return (strstr(str1, str2) == nullptr) ? true : false;
	}
}