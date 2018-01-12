#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "string\string_utils.hpp"
#include "type\types.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 A pointer to the null-terminated byte string containing the default 
	 delimiters:
		1. space character;
		2. tab character;
		3. end of line (EOL) character;
		4. carriage return (CR) character.
	 */
	const char * const g_default_delimiters = " \t\n\r";

	/**
	 An enumeration of the different token results.
	 
	 This contains: 
	 @c Valid, 
	 @c None and 
	 @c Invalid.
	 */
	enum struct [[nodiscard]] TokenResult {
		Valid,	// The parsed token is valid (matches the expected token type).
		None,	// No token can be parsed (independent of the token type).
		Invalid	// The parsed token is invalid (matches the expected token 
		        // type).
	};

	//-------------------------------------------------------------------------
	// String Conversion Utilities
	//-------------------------------------------------------------------------
	#pragma region

	/**
	 Reads a @c DataT element from the given string.

	 @tparam		DataT
					The data type.
	 @param[in]		str
					A pointer to the null-terminated byte string to convert.
	 @param[out]	result
					A reference to the @c DataT element represented by the 
					given string @a str.
	 @return		A token result indicating whether the conversion of the 
					given string @a str to a @c DataT element succeeded or not.
	 */
	template< typename DataT >
	TokenResult StringTo(const char *str, DataT &result) noexcept;

	#pragma endregion

	//-------------------------------------------------------------------------
	// String Conversion Utilities: Substring
	//-------------------------------------------------------------------------
	#pragma region

	/**
	 Reads a @c DataT element from the given string.

	 @pre			@a end is not equal to @c nullptr if @a begin is not equal 
					to @c nullptr.
	 @tparam		DataT
					The data type.
	 @param[in]		begin
					A pointer to the begin (inclusive) of the string to 
					convert.
	 @param[in]		end
					A pointer to the end (exclusive) of the string to convert.
	 @param[out]	result
					A reference to the @c DataT element represented by the 
					given string @a str.
	 @return		A token result indicating whether the conversion of the 
					given string @a str to a @c DataT element succeeded or not.
	 */
	template< typename DataT >
	TokenResult StringTo(const char *begin, const char *end, DataT &result) noexcept;
	
	#pragma endregion

	//-------------------------------------------------------------------------
	// String Conversion Utilities: String Prefix
	//-------------------------------------------------------------------------
	#pragma region

	/**
	 Reads a @c DataT element from the prefix of the given string.

	 @tparam		DataT
					The data type.
	 @param[in]		str
					A pointer to the null-terminated byte string to convert.
	 @param[out]	result
					A reference to the @c DataT element represented by the 
					prefix of the given string @a str.
	 @return		A token result indicating whether the conversion of the 
					prefix of the given string @a str to a @c DataT element 
					succeeded or not.
	 */
	template< typename DataT >
	TokenResult StringPrefixTo(const char *str, DataT &result) noexcept;

	#pragma endregion

	//-------------------------------------------------------------------------
	// Parsing Utilities: Reading
	//-------------------------------------------------------------------------
	#pragma region

	/**
	 Reads and converts the next token in the given string to (non-delimiting) 
	 characters.

	 @pre			@a str or @a context is not equal to @c nullptr.
	 @pre			@a result is not equal to @c nullptr.
	 @pre			@a delimiters is not equal to @c nullptr.
	 @param[in]		str
					A pointer to the null-terminated byte string. If @a str is 
					equal to @c nullptr, reading continues from the beginning 
					of @a str. Otherwise, reading continues from the current 
					position.
	 @param[in,out] context
					A pointer to the current position int he given string 
					@a str.
	 @param[out]	result
					A pointer to the pointer to the characters represented by 
					the next token in the given string @a str.
	 @param[in]		delimiters
					A pointer to the null-terminated byte string containing 
					the delimiting characters.
	 @return		A token result indicating whether the conversion of the 
					next token in the given string to characters succeeded or 
					not.
	 */
	TokenResult ReadChars(char *str, char **context, char **result, 
		const char *delimiters = g_default_delimiters) noexcept;
	
	/**
	 Reads and converts the next token in the given string to a quoted string.

	 @pre			@a str or @a context is not equal to @c nullptr.
	 @pre			@a delimiters is not equal to @c nullptr.
	 @pre			The quote '"' may not be delimiter.
	 @param[in]		str
					A pointer to the null-terminated byte string. If @a str is 
					equal to @c nullptr, reading continues from the beginning 
					of @a str. Otherwise, reading continues from the current 
					position.
	 @param[in,out] context
					A pointer to the current position int he given string 
					@a str.
	 @param[out]	result
					A reference to the quoted string represented by the next 
					token in the given string @a str.
	 @param[in]		delimiters
					A pointer to the null-terminated byte string containing 
					the delimiting characters.
	 @return		A token result indicating whether the conversion of the 
					next token in the given string to a quoted string succeeded 
					or not.
	 */
	TokenResult ReadQuotedString(char *str, char **context, string &result, 
		const char *delimiters = g_default_delimiters);
	
	/**
	 Reads and converts the next token in the given string to a @c DataT 
	 element.

	 @pre			@a str or @a context is not equal to @c nullptr.
	 @pre			@a delimiters is not equal to @c nullptr.
	 @tparam		DataT
					The data type.
	 @param[in]		str
					A pointer to the null-terminated byte string. If @a str is 
					equal to @c nullptr, reading continues from the beginning 
					of @a str. Otherwise, reading continues from the current 
					position.
	 @param[in,out] context
					A pointer to the current position in the given string 
					@a str.
	 @param[out]	result
					A reference to the @c DataT element represented by the next 
					token in the given string @a str.
	 @param[in]		delimiters
					A pointer to the null-terminated byte string containing 
					the delimiting characters.
	 @return		A token result indicating whether the conversion of the 
					next token in the given string to a @c DataT element 
					succeeded or not.
	 */
	template< typename DataT >
	TokenResult Read(char *str, char **context, DataT &result,
		const char *delimiters = g_default_delimiters) noexcept;
	
	#pragma endregion

	//-------------------------------------------------------------------------
	// Parsing Utilities: Peaking
	//-------------------------------------------------------------------------
	#pragma region

	/**
	 Checks whether the next token in the given string represents 
	 (non-delimiting) characters.
	 
	 @pre			@a str is not equal to @c nullptr.
	 @pre			@a delimiters is not equal to @c nullptr.
	 @param[in]		str
					A pointer to the null-terminated byte string.
	 @param[in]		delimiters
					A pointer to the null-terminated byte string containing the 
					delimiting characters.
	 @return		A token result indicating whether the conversion
					of the next token in the given string to an @c U32 succeeds 
					or not.
	 */
	TokenResult HasChars(const char *str, 
		const char *delimiters = g_default_delimiters) noexcept;

	/**
	 Checks whether the next token in the given string represents a quoted 
	 string.

	 @pre			@a str is not equal to @c nullptr.
	 @pre			@a delimiters is not equal to @c nullptr.
	 @pre			The quote '"' may not be delimiter.
	 @param[in]		str
					A pointer to the null-terminated byte string.
	 @param[in]		delimiters
					A pointer to the null-terminated byte string containing the 
					delimiting characters.
	 @return		A token result indicating whether the conversion
					of the next token in the given string to a quoted string 
					succeeds or not.
	 */
	TokenResult HasQuotedString(const char *str, 
		const char *delimiters = g_default_delimiters) noexcept;

	/**
	 Checks whether the next token in the given string represents a @c DataT 
	 element.

	 @pre			@a str is not equal to @c nullptr.
	 @pre			@a delimiters is not equal to @c nullptr.
	 @tparam		DataT
					The data type.
	 @param[in]		str
					A pointer to the null-terminated byte string.
	 @param[in]		delimiters
					A pointer to the null-terminated byte string containing the 
					delimiting characters.
	 @return		A token result indicating whether the conversion of the 
					next token in the given string to a @c DataT element 
					succeeds or not.
	 */
	template< typename DataT >
	TokenResult Contains(const char *str, 
		const char *delimiters = g_default_delimiters) noexcept;

	#pragma endregion

	//-------------------------------------------------------------------------
	// Parsing Utilities: Advancing
	//-------------------------------------------------------------------------
	#pragma region

	/**
	 Advances to the first non-delimiting character in the given string.

	 @pre			@a str is not equal to @c nullptr.
	 @pre			@a delimiters is not equal to @c nullptr.
	 @param[in]		str
					A pointer to the null-terminated byte string.
	 @param[in]		delimiters
					A pointer to the null-terminated byte string containing the 
					delimiting characters.
	 @return		@c nullptr if the end of string character is reached.
	 @return		A pointer to the first non-delimiting character in the 
					given string.
	 */
	char *SkipDelimiters(char *str, 
		const char *delimiters = g_default_delimiters) noexcept;

	/**
	 Advances to the first non-delimiting character in the given string.

	 @pre			@a str is not equal to @c nullptr.
	 @pre			@a delimiters is not equal to @c nullptr.
	 @param[in]		str
					A pointer to the null-terminated byte string.
	 @param[in]		delimiters
					A pointer to the null-terminated byte string containing the 
					delimiting characters.
	 @return		@c nullptr if the end of string character is reached.
	 @return		A pointer to the first non-delimiting character in the 
					given string.
	 */
	const char *SkipDelimiters(const char *str, 
		const char *delimiters = g_default_delimiters) noexcept;

	/**
	 Advances to the first delimiting character in the given string.

	 @pre			@a str is not equal to @c nullptr.
	 @pre			@a delimiters is not equal to @c nullptr.
	 @param[in]		str
					A pointer to the null-terminated byte string.
	 @param[in]		delimiters
					A pointer to the null-terminated byte string containing the 
					delimiting characters.
	 @return		@c nullptr if the end of string character is reached.
	 @return		A pointer to the first delimiting character in the 
					given string.
	 */
	char *GotoDelimiters(char *str, 
		const char *delimiters = g_default_delimiters) noexcept;

	/**
	 Advances to the first delimiting character in the given string.

	 @pre			@a str is not equal to @c nullptr.
	 @pre			@a delimiters is not equal to @c nullptr.
	 @param[in]		str
					A pointer to the null-terminated byte string.
	 @param[in]		delimiters
					A pointer to the null-terminated byte string containing the 
					delimiting characters.
	 @return		@c nullptr if the end of string character is reached.
	 @return		A pointer to the first delimiting character in the 
					given string.
	 */
	const char *GotoDelimiters(const char *str, 
		const char *delimiters = g_default_delimiters) noexcept;

	#pragma endregion
}

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "string\token.tpp"

#pragma endregion