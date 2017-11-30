#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "utils\type\types.hpp"

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
	// String Conversion Utilities: Complete String
	//-------------------------------------------------------------------------
#pragma region

	/**
	 Converts the given string to a @c bool (@c true or @c false).

	 @param[in]		str
					A pointer to the null-terminated byte string to convert.
	 @param[out]	result
					A reference to the @c bool represented by the string 
					@a str.
	 @return		A token result indicating whether the conversion
					of the given string @a str to a @c bool succeeded or not.
	 */
	TokenResult StringToBool(const char *str, bool &result) noexcept;

	/**
	 Converts the given string to a @c S8.

	 @param[in]		str
					A pointer to the null-terminated byte string to convert.
	 @param[out]	result
					A reference to the @c S8 represented by the string 
					@a str.
	 @return		A token result indicating whether the conversion
					of the given string @a str to a @c S8 succeeded or not.
	 */
	TokenResult StringToS8(const char *str, S8 &result) noexcept;

	/**
	 Converts the given string to an @c U8.

	 @param[in]		str
					A pointer to the null-terminated byte string to convert.
	 @param[out]	result
					A reference to the @c U8 represented by the string 
					@a str.
	 @return		A token result indicating whether the conversion
					of the given string @a str to an @c U8 succeeded or not.
	 */
	TokenResult StringToU8(const char *str, U8 &result) noexcept;

	/**
	 Converts the given string to a @c S16.

	 @param[in]		str
					A pointer to the null-terminated byte string to convert.
	 @param[out]	result
					A reference to the @c S16 represented by the string 
					@a str.
	 @return		A token result indicating whether the conversion
					of the given string @a str to a @c S16 succeeded or not.
	 */
	TokenResult StringToS16(const char *str, S16 &result) noexcept;

	/**
	 Converts the given string to an @c U16.

	 @param[in]		str
					A pointer to the null-terminated byte string to convert.
	 @param[out]	result
					A reference to the @c U16 represented by the string 
					@a str.
	 @return		A token result indicating whether the conversion
					of the given string @a str to an @c U16 succeeded or not.
	 */
	TokenResult StringToU16(const char *str, U16 &result) noexcept;

	/**
	 Converts the given string to a @c S32.

	 @param[in]		str
					A pointer to the null-terminated byte string to convert.
	 @param[out]	result
					A reference to the @c S32 represented by the string 
					@a str.
	 @return		A token result indicating whether the conversion
					of the given string @a str to a @c S32 succeeded or not.
	 */
	TokenResult StringToS32(const char *str, S32 &result) noexcept;

	/**
	 Converts the given string to an @c U32.

	 @param[in]		str
					A pointer to the null-terminated byte string to convert.
	 @param[out]	result
					A reference to the @c U32 represented by the string 
					@a str.
	 @return		A token result indicating whether the conversion
					of the given string @a str to an @c U32 succeeded or not.
	 */
	TokenResult StringToU32(const char *str, U32 &result) noexcept;

	/**
	 Converts the given string to a @c S64.

	 @param[in]		str
					A pointer to the null-terminated byte string to convert.
	 @param[out]	result
					A reference to the @c S64 represented by the string 
					@a str.
	 @return		A token result indicating whether the conversion
					of the given string @a str to a @c S64 succeeded or not.
	 */
	TokenResult StringToS64(const char *str, S64 &result) noexcept;

	/**
	 Converts the given string to an @c U64.

	 @param[in]		str
					A pointer to the null-terminated byte string to convert.
	 @param[out]	result
					A reference to the @c U64 represented by the string 
					@a str.
	 @return		A token result indicating whether the conversion
					of the given string @a str to an @c U64 succeeded or not.
	 */
	TokenResult StringToU64(const char *str, U64 &result) noexcept;

	/**
	 Converts the given string to a @c F32.

	 @param[in]		str
					A pointer to the null-terminated byte string to convert.
	 @param[out]	result
					A reference to the @c F32 represented by the string 
					@a str.
	 @return		A token result indicating whether the conversion
					of the given string @a str to a @c F32 succeeded or not.
	 */
	TokenResult StringToF32(const char *str, F32 &result) noexcept;

	/**
	 Converts the given string to a @c F64.

	 @param[in]		str
					A pointer to the null-terminated byte string to convert.
	 @param[out]	result
					A reference to the @c F64 represented by the string 
					@a str.
	 @return		A token result indicating whether the conversion
					of the given string @a str to a @c F64 succeeded or not.
	 */
	TokenResult StringToF64(const char *str, F64 &result) noexcept;

#pragma endregion

	//-------------------------------------------------------------------------
	// String Conversion Utilities: Substring
	//-------------------------------------------------------------------------
#pragma region

	/**
	 Converts the given string to a @c bool (@c true or @c false).

	 @pre			@a end is not equal to @c nullptr if @a begin is not equal 
					to @c nullptr.
	 @param[in]		begin
					A pointer to the begin (inclusive) of the string to 
					convert.
	 @param[in]		end
					A pointer to the end (exclusive) of the string to convert.
	 @param[out]	result
					A reference to the @c bool represented by the string 
					@a str.
	 @return		A token result indicating whether the conversion
					of the given string @a str to a @c bool succeeded or not.
	 */
	TokenResult StringToBool(
		const char *begin, const char *end, bool &result) noexcept;
	
	/**
	 Converts the given string to a @c S8.

	 @pre			@a end is not equal to @c nullptr if @a begin is not equal 
					to @c nullptr.
	 @param[in]		begin
					A pointer to the begin (inclusive) of the string to 
					convert.
	 @param[in]		end
					A pointer to the end (exclusive) of the string to convert.
	 @param[out]	result
					A reference to the @c S8 represented by the string 
					@a str.
	 @return		A token result indicating whether the conversion
					of the given string @a str to a @c S8 succeeded or not.
	 */
	TokenResult StringToS8(
		const char *begin, const char *end, S8 &result) noexcept;
	
	/**
	 Converts the given string to an @c U8.

	 @pre			@a end is not equal to @c nullptr if @a begin is not equal 
					to @c nullptr.
	 @param[in]		begin
					A pointer to the begin (inclusive) of the string to 
					convert.
	 @param[in]		end
					A pointer to the end (exclusive) of the string to convert.
	 @param[out]	result
					A reference to the @c U8 represented by the string 
					@a str.
	 @return		A token result indicating whether the conversion
					of the given string @a str to an @c U8 succeeded or not.
	 */
	TokenResult StringToU8(
		const char *begin, const char *end, U8 &result) noexcept;
	
	/**
	 Converts the given string to a @c S16.

	 @pre			@a end is not equal to @c nullptr if @a begin is not equal 
					to @c nullptr.
	 @param[in]		begin
					A pointer to the begin (inclusive) of the string to 
					convert.
	 @param[in]		end
					A pointer to the end (exclusive) of the string to convert.
	 @param[out]	result
					A reference to the @c S16 represented by the string 
					@a str.
	 @return		A token result indicating whether the conversion
					of the given string @a str to a @c S16 succeeded or not.
	 */
	TokenResult StringToS16(
		const char *begin, const char *end, S16 &result) noexcept;
	
	/**
	 Converts the given string to an @c U16.

	 @pre			@a end is not equal to @c nullptr if @a begin is not equal 
					to @c nullptr.
	 @param[in]		begin
					A pointer to the begin (inclusive) of the string to 
					convert.
	 @param[in]		end
					A pointer to the end (exclusive) of the string to convert.
	 @param[out]	result
					A reference to the @c U16 represented by the string 
					@a str.
	 @return		A token result indicating whether the conversion
					of the given string @a str to an @c U16 succeeded or not.
	 */
	TokenResult StringToU16(
		const char *begin, const char *end, U16 &result) noexcept;
	
	/**
	 Converts the given string to a @c S32.

	 @pre			@a end is not equal to @c nullptr if @a begin is not equal 
					to @c nullptr.
	 @param[in]		begin
					A pointer to the begin (inclusive) of the string to 
					convert.
	 @param[in]		end
					A pointer to the end (exclusive) of the string to convert.
	 @param[out]	result
					A reference to the @c S32 represented by the string 
					@a str.
	 @return		A token result indicating whether the conversion
					of the given string @a str to a @c S32 succeeded or not.
	 */
	TokenResult StringToS32(
		const char *begin, const char *end, S32 &result) noexcept;
	
	/**
	 Converts the given string to an @c U32.

	 @pre			@a end is not equal to @c nullptr if @a begin is not equal 
					to @c nullptr.
	 @param[in]		begin
					A pointer to the begin (inclusive) of the string to 
					convert.
	 @param[in]		end
					A pointer to the end (exclusive) of the string to convert.
	 @param[out]	result
					A reference to the @c U32 represented by the string 
					@a str.
	 @return		A token result indicating whether the conversion
					of the given string @a str to an @c U32 succeeded or not.
	 */
	TokenResult StringToU32(
		const char *begin, const char *end, U32 &result) noexcept;
	
	/**
	 Converts the given string to a @c S64.

	 @pre			@a end is not equal to @c nullptr if @a begin is not equal 
					to @c nullptr.
	 @param[in]		begin
					A pointer to the begin (inclusive) of the string to 
					convert.
	 @param[in]		end
					A pointer to the end (exclusive) of the string to convert.
	 @param[out]	result
					A reference to the @c S64 represented by the string 
					@a str.
	 @return		A token result indicating whether the conversion
					of the given string @a str to a @c S64 succeeded or not.
	 */
	TokenResult StringToS64(
		const char *begin, const char *end, S64 &result) noexcept;
	
	/**
	 Converts the given string to an @c U64.

	 @pre			@a end is not equal to @c nullptr if @a begin is not equal 
					to @c nullptr.
	 @param[in]		begin
					A pointer to the begin (inclusive) of the string to 
					convert.
	 @param[in]		end
					A pointer to the end (exclusive) of the string to convert.
	 @param[out]	result
					A reference to the @c U64 represented by the string 
					@a str.
	 @return		A token result indicating whether the conversion
					of the given string @a str to an @c U64 succeeded or not.
	 */
	TokenResult StringToU64(
		const char *begin, const char *end, U64 &result) noexcept;
	
	/**
	 Converts the given string to a @c F32.

	 @pre			@a end is not equal to @c nullptr if @a begin is not equal 
					to @c nullptr.
	 @param[in]		begin
					A pointer to the begin (inclusive) of the string to 
					convert.
	 @param[in]		end
					A pointer to the end (exclusive) of the string to convert.
	 @param[out]	result
					A reference to the @c F32 represented by the string 
					@a str.
	 @return		A token result indicating whether the conversion
					of the given string @a str to a @c F32 succeeded or not.
	 */
	TokenResult StringToF32(
		const char *begin, const char *end, F32 &result) noexcept;
	
	/**
	 Converts the given string to a @c F64.

	 @pre			@a end is not equal to @c nullptr if @a begin is not equal 
					to @c nullptr.
	 @param[in]		begin
					A pointer to the begin (inclusive) of the string to 
					convert.
	 @param[in]		end
					A pointer to the end (exclusive) of the string to convert.
	 @param[out]	result
					A reference to the @c F64 represented by the string 
					@a str.
	 @return		A token result indicating whether the conversion
					of the given string @a str to a @c F64 succeeded or not.
	 */
	TokenResult StringToF64(
		const char *begin, const char *end, F64 &result) noexcept;

#pragma endregion

	//-------------------------------------------------------------------------
	// String Conversion Utilities: String Prefix
	//-------------------------------------------------------------------------
#pragma region

	/**
	 Converts the prefix of the given string @a str to a @c S8.

	 @param[in]		str
					A pointer to the null-terminated byte string to convert.
	 @param[out]	result
					A reference to the @c S8 represented by the prefix of the 
					given string @a str.
	 @return		A token result indicating whether the conversion of the 
					prefix of the given string @a str to a @c S8 succeeded or 
					not.
	 */
	TokenResult StringPrefixToS8(const char *str, S8 &result) noexcept;

	/**
	 Converts the prefix of the given string @a str to an @c U8.

	 @param[in]		str
					A pointer to the null-terminated byte string to convert.
	 @param[out]	result
					A reference to the @c U8 represented by the prefix of the 
					given string @a str.
	 @return		A token result indicating whether the conversion of the 
					prefix of the given string @a str to an @c U8 succeeded or 
					not.
	 */
	TokenResult StringPrefixToU8(const char *str, U8 &result) noexcept;

	/**
	 Converts the prefix of the given string @a str to a @c S16.

	 @param[in]		str
					A pointer to the null-terminated byte string to convert.
	 @param[out]	result
					A reference to the @c S16 represented by the prefix of the 
					given string @a str.
	 @return		A token result indicating whether the conversion of the 
					prefix of the given string @a str to a @c S16 succeeded or 
					not.
	 */
	TokenResult StringPrefixToS16(const char *str, S16 &result) noexcept;

	/**
	 Converts the prefix of the given string @a str to an @c U16.

	 @param[in]		str
					A pointer to the null-terminated byte string to convert.
	 @param[out]	result
					A reference to the @c U16 represented by the prefix of the 
					given string @a str.
	 @return		A token result indicating whether the conversion of the 
					prefix of the given string @a str to an @c U16 succeeded or 
					not.
	 */
	TokenResult StringPrefixToU16(const char *str, U16 &result) noexcept;

	/**
	 Converts the prefix of the given string @a str to a @c S32.

	 @param[in]		str
					A pointer to the null-terminated byte string to convert.
	 @param[out]	result
					A reference to the @c S32 represented by the prefix of the 
					given string @a str.
	 @return		A token result indicating whether the conversion of the 
					prefix of the given string @a str to a @c S32 succeeded or 
					not.
	 */
	TokenResult StringPrefixToS32(const char *str, S32 &result) noexcept;

	/**
	 Converts the prefix of the given string @a str to an @c U32.

	 @param[in]		str
					A pointer to the null-terminated byte string to convert.
	 @param[out]	result
					A reference to the @c U32 represented by the prefix of the 
					given string @a str.
	 @return		A token result indicating whether the conversion of the 
					prefix of the given string @a str to an @c U32 succeeded or 
					not.
	 */
	TokenResult StringPrefixToU32(const char *str, U32 &result) noexcept;

	/**
	 Converts the prefix of the given string @a str to a @c S64.

	 @param[in]		str
					A pointer to the null-terminated byte string to convert.
	 @param[out]	result
					A reference to the @c S64 represented by the prefix of the 
					given string @a str.
	 @return		A token result indicating whether the conversion of the 
					prefix of the given string @a str to a @c S64 succeeded or 
					not.
	 */
	TokenResult StringPrefixToS64(const char *str, S64 &result) noexcept;

	/**
	 Converts the prefix of the given string @a str to an @c U64.

	 @param[in]		str
					A pointer to the null-terminated byte string to convert.
	 @param[out]	result
					A reference to the @c U64 represented by the prefix of the 
					given string @a str.
	 @return		A token result indicating whether the conversion of the 
					prefix of the given string @a str to an @c U64 succeeded or 
					not.
	 */
	TokenResult StringPrefixToU64(const char *str, U64 &result) noexcept;

	/**
	 Converts the prefix of the given string @a str to a @c F32.

	 @param[in]		str
					A pointer to the null-terminated byte string to convert.
	 @param[out]	result
					A reference to the @c F32 represented by the prefix of the 
					given string @a str.
	 @return		A token result indicating whether the conversion of the 
					prefix of the given string @a str to a @c F32 succeeded or 
					not.
	 */
	TokenResult StringPrefixToF32(const char *str, F32 &result) noexcept;

	/**
	 Converts the prefix of the given string @a str to a @c F64.

	 @param[in]		str
					A pointer to the null-terminated byte string to convert.
	 @param[out]	result
					A reference to the @c F64 represented by the prefix of the 
					given string @a str.
	 @return		A token result indicating whether the conversion of the 
					prefix of the given string @a str to a @c F64 succeeded or 
					not.
	 */
	TokenResult StringPrefixToF64(const char *str, F64 &result) noexcept;

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
					A pointer to the null-terminated byte string.
					If @a str is equal to @c nullptr,
					reading continues from the beginning of @a str.
					Otherwise, reading continues from the current position.
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
	 Reads and converts the next token in the given string to a string.

	 @pre			@a str or @a context is not equal to @c nullptr.
	 @pre			@a delimiters is not equal to @c nullptr.
	 @param[in]		str
					A pointer to the null-terminated byte string.
					If @a str is equal to @c nullptr,
					reading continues from the beginning of @a str.
					Otherwise, reading continues from the current position.
	 @param[in,out] context
					A pointer to the current position int he given string 
					@a str.
	 @param[out]	result
					A reference to the string represented by the next 
					token in the given string @a str.
	 @param[in]		delimiters
					A pointer to the null-terminated byte string containing 
					the delimiting characters.
	 @return		A token result indicating whether the conversion of the 
					next token in the given string to a string succeeded or 
					not.
	 */
	TokenResult ReadString(char *str, char **context, string &result, 
		const char *delimiters = g_default_delimiters);
	
	/**
	 Reads and converts the next token in the given string to a quoted string.

	 @pre			@a str or @a context is not equal to @c nullptr.
	 @pre			@a delimiters is not equal to @c nullptr.
	 @pre			The quote '"' may not be delimiter.
	 @param[in]		str
					A pointer to the null-terminated byte string.
					If @a str is equal to @c nullptr,
					reading continues from the beginning of @a str.
					Otherwise, reading continues from the current position.
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
	 Reads and converts the next token in the given string to a @c bool 
	 (@c true or @c false).

	 @pre			@a str or @a context is not equal to @c nullptr.
	 @pre			@a delimiters is not equal to @c nullptr.
	 @param[in]		str
					A pointer to the null-terminated byte string.
					If @a str is equal to @c nullptr,
					reading continues from the beginning of @a str.
					Otherwise, reading continues from the current position.
	 @param[in,out] context
					A pointer to the current position int he given string 
					@a str.
	 @param[out]	result
					A reference to the @c bool represented by the next 
					token in the given string @a str.
	 @param[in]		delimiters
					A pointer to the null-terminated byte string containing 
					the delimiting characters.
	 @return		A token result indicating whether the conversion of the 
					next token in the given string to a @c bool succeeded or not.
	 */
	TokenResult ReadBool(char *str, char **context, bool &result, 
		const char *delimiters = g_default_delimiters) noexcept;
	
	/**
	 Reads and converts the next token in the given string to a @c S8.

	 @pre			@a str or @a context is not equal to @c nullptr.
	 @pre			@a delimiters is not equal to @c nullptr.
	 @param[in]		str
					A pointer to the null-terminated byte string.
					If @a str is equal to @c nullptr,
					reading continues from the beginning of @a str.
					Otherwise, reading continues from the current position.
	 @param[in,out] context
					A pointer to the current position int he given string 
					@a str.
	 @param[out]	result
					A reference to the @c S8 represented by the next 
					token in the given string @a str.
	 @param[in]		delimiters
					A pointer to the null-terminated byte string containing 
					the delimiting characters.
	 @return		A token result indicating whether the conversion of the 
					next token in the given string to a @c S8 succeeded or not.
	 */
	TokenResult ReadS8(char *str, char **context, S8 &result, 
		const char *delimiters = g_default_delimiters) noexcept;
	
	/**
	 Reads and converts the next token in the given string to an @c U8.

	 @pre			@a str or @a context is not equal to @c nullptr.
	 @pre			@a delimiters is not equal to @c nullptr.
	 @param[in]		str
					A pointer to the null-terminated byte string.
					If @a str is equal to @c nullptr,
					reading continues from the beginning of @a str.
					Otherwise, reading continues from the current position.
	 @param[in,out] context
					A pointer to the current position int he given string 
					@a str.
	 @param[out]	result
					A reference to the @c U8 represented by the next 
					token in the given string @a str.
	 @param[in]		delimiters
					A pointer to the null-terminated byte string containing 
					the delimiting characters.
	 @return		A token result indicating whether the conversion of the 
					next token in the given string to an @c U8 succeeded or not.
	 */
	TokenResult ReadU8(char *str, char **context, U8 &result, 
		const char *delimiters = g_default_delimiters) noexcept;
	
	/**
	 Reads and converts the next token in the given string to a @c S16.

	 @pre			@a str or @a context is not equal to @c nullptr.
	 @pre			@a delimiters is not equal to @c nullptr.
	 @param[in]		str
					A pointer to the null-terminated byte string.
					If @a str is equal to @c nullptr,
					reading continues from the beginning of @a str.
					Otherwise, reading continues from the current position.
	 @param[in,out] context
					A pointer to the current position int he given string 
					@a str.
	 @param[out]	result
					A reference to the @c S16 represented by the next 
					token in the given string @a str.
	 @param[in]		delimiters
					A pointer to the null-terminated byte string containing 
					the delimiting characters.
	 @return		A token result indicating whether the conversion of the 
					next token in the given string to a @c S16 succeeded or not.
	 */
	TokenResult ReadS16(char *str, char **context, S16 &result, 
		const char *delimiters = g_default_delimiters) noexcept;
	
	/**
	 Reads and converts the next token in the given string to an @c U16.

	 @pre			@a str or @a context is not equal to @c nullptr.
	 @pre			@a delimiters is not equal to @c nullptr.
	 @param[in]		str
					A pointer to the null-terminated byte string.
					If @a str is equal to @c nullptr,
					reading continues from the beginning of @a str.
					Otherwise, reading continues from the current position.
	 @param[in,out] context
					A pointer to the current position int he given string 
					@a str.
	 @param[out]	result
					A reference to the @c U16 represented by the next 
					token in the given string @a str.
	 @param[in]		delimiters
					A pointer to the null-terminated byte string containing 
					the delimiting characters.
	 @return		A token result indicating whether the conversion of the 
					next token in the given string to an @c U16 succeeded or not.
	 */
	TokenResult ReadU16(char *str, char **context, U16 &result, 
		const char *delimiters = g_default_delimiters) noexcept;
	
	/**
	 Reads and converts the next token in the given string to a @c S32.

	 @pre			@a str or @a context is not equal to @c nullptr.
	 @pre			@a delimiters is not equal to @c nullptr.
	 @param[in]		str
					A pointer to the null-terminated byte string.
					If @a str is equal to @c nullptr,
					reading continues from the beginning of @a str.
					Otherwise, reading continues from the current position.
	 @param[in,out] context
					A pointer to the current position int he given string 
					@a str.
	 @param[out]	result
					A reference to the @c S32 represented by the next 
					token in the given string @a str.
	 @param[in]		delimiters
					A pointer to the null-terminated byte string containing 
					the delimiting characters.
	 @return		A token result indicating whether the conversion of the 
					next token in the given string to a @c S32 succeeded or not.
	 */
	TokenResult ReadS32(char *str, char **context, S32 &result, 
		const char *delimiters = g_default_delimiters) noexcept;
	
	/**
	 Reads and converts the next token in the given string to an @c U32.

	 @pre			@a str or @a context is not equal to @c nullptr.
	 @pre			@a delimiters is not equal to @c nullptr.
	 @param[in]		str
					A pointer to the null-terminated byte string.
					If @a str is equal to @c nullptr,
					reading continues from the beginning of @a str.
					Otherwise, reading continues from the current position.
	 @param[in,out] context
					A pointer to the current position int he given string 
					@a str.
	 @param[out]	result
					A reference to the @c U32 represented by the next 
					token in the given string @a str.
	 @param[in]		delimiters
					A pointer to the null-terminated byte string containing 
					the delimiting characters.
	 @return		A token result indicating whether the conversion of the 
					next token in the given string to an @c U32 succeeded or not.
	 */
	TokenResult ReadU32(char *str, char **context, U32 &result, 
		const char *delimiters = g_default_delimiters) noexcept;
	
	/**
	 Reads and converts the next token in the given string to a @c S64.

	 @pre			@a str or @a context is not equal to @c nullptr.
	 @pre			@a delimiters is not equal to @c nullptr.
	 @param[in]		str
					A pointer to the null-terminated byte string.
					If @a str is equal to @c nullptr,
					reading continues from the beginning of @a str.
					Otherwise, reading continues from the current position.
	 @param[in,out] context
					A pointer to the current position int he given string 
					@a str.
	 @param[out]	result
					A reference to the @c S64 represented by the next 
					token in the given string @a str.
	 @param[in]		delimiters
					A pointer to the null-terminated byte string containing 
					the delimiting characters.
	 @return		A token result indicating whether the conversion of the 
					next token in the given string to a @c S64 succeeded or not.
	 */
	TokenResult ReadS64(char *str, char **context, S64 &result, 
		const char *delimiters = g_default_delimiters) noexcept;
	
	/**
	 Reads and converts the next token in the given string to an @c U64.

	 @pre			@a str or @a context is not equal to @c nullptr.
	 @pre			@a delimiters is not equal to @c nullptr.
	 @param[in]		str
					A pointer to the null-terminated byte string.
					If @a str is equal to @c nullptr,
					reading continues from the beginning of @a str.
					Otherwise, reading continues from the current position.
	 @param[in,out] context
					A pointer to the current position int he given string 
					@a str.
	 @param[out]	result
					A reference to the @c U64 represented by the next 
					token in the given string @a str.
	 @param[in]		delimiters
					A pointer to the null-terminated byte string containing 
					the delimiting characters.
	 @return		A token result indicating whether the conversion of the 
					next token in the given string to an @c U64 succeeded or not.
	 */
	TokenResult ReadU64(char *str, char **context, U64 &result, 
		const char *delimiters = g_default_delimiters) noexcept;
	
	/**
	 Reads and converts the next token in the given string to a @c F32.

	 @pre			@a str or @a context is not equal to @c nullptr.
	 @pre			@a delimiters is not equal to @c nullptr.
	 @param[in]		str
					A pointer to the null-terminated byte string.
					If @a str is equal to @c nullptr,
					reading continues from the beginning of @a str.
					Otherwise, reading continues from the current position.
	 @param[in,out] context
					A pointer to the current position int he given string 
					@a str.
	 @param[out]	result
					A reference to the @c F32 represented by the next 
					token in the given string @a str.
	 @param[in]		delimiters
					A pointer to the null-terminated byte string containing 
					the delimiting characters.
	 @return		A token result indicating whether the conversion of the 
					next token in the given string to a @c F32 succeeded or not.
	 */
	TokenResult ReadF32(char *str, char **context, F32 &result, 
		const char *delimiters = g_default_delimiters) noexcept;
	
	/**
	 Reads and converts the next token in the given string to a @c F64.

	 @pre			@a str or @a context is not equal to @c nullptr.
	 @pre			@a delimiters is not equal to @c nullptr.
	 @param[in]		str
					A pointer to the null-terminated byte string.
					If @a str is equal to @c nullptr,
					reading continues from the beginning of @a str.
					Otherwise, reading continues from the current position.
	 @param[in,out] context
					A pointer to the current position int he given string 
					@a str.
	 @param[out]	result
					A reference to the @c F64 represented by the next 
					token in the given string @a str.
	 @param[in]		delimiters
					A pointer to the null-terminated byte string containing 
					the delimiting characters.
	 @return		A token result indicating whether the conversion of the 
					next token in the given string to a @c F64 succeeded or not.
	 */
	TokenResult ReadF64(char *str, char **context, F64 &result, 
		const char *delimiters = g_default_delimiters) noexcept;
	
	/**
	 Reads and converts the next token in the given string to a @c F32x2.

	 @pre			@a str or @a context is not equal to @c nullptr.
	 @pre			@a delimiters is not equal to @c nullptr.
	 @param[in]		str
					A pointer to the null-terminated byte string.
					If @a str is equal to @c nullptr,
					reading continues from the beginning of @a str.
					Otherwise, reading continues from the current position.
	 @param[in,out] context
					A pointer to the current position int he given string 
					@a str.
	 @param[out]	result
					A reference to the @c F32x2 represented by the next 
					token in the given string @a str.
	 @param[in]		delimiters
					A pointer to the null-terminated byte string containing 
					the delimiting characters.
	 @return		A token result indicating whether the conversion of the 
					next token in the given string to a @c F32x2 succeeded 
					or not.
	 */
	TokenResult ReadF32x2(char *str, char **context, F32x2 &result, 
		const char *delimiters = g_default_delimiters) noexcept;
	
	/**
	 Reads and converts the next token in the given string to a @c F32x3.

	 @pre			@a str or @a context is not equal to @c nullptr.
	 @pre			@a delimiters is not equal to @c nullptr.
	 @param[in]		str
					A pointer to the null-terminated byte string.
					If @a str is equal to @c nullptr,
					reading continues from the beginning of @a str.
					Otherwise, reading continues from the current position.
	 @param[in,out] context
					A pointer to the current position int he given string 
					@a str.
	 @param[out]	result
					A reference to the @c F32x3 represented by the next 
					token in the given string @a str.
	 @param[in]		delimiters
					A pointer to the null-terminated byte string containing 
					the delimiting characters.
	 @return		A token result indicating whether the conversion of the 
					next token in the given string to a @c F32x3 succeeded 
					or not.
	 */
	TokenResult ReadF32x3(char *str, char **context, F32x3 &result, 
		const char *delimiters = g_default_delimiters) noexcept;

	/**
	 Reads and converts the next token in the given string to a @c F32x4.

	 @pre			@a str or @a context is not equal to @c nullptr.
	 @pre			@a delimiters is not equal to @c nullptr.
	 @param[in]		str
					A pointer to the null-terminated byte string.
					If @a str is equal to @c nullptr, 
					reading continues from the beginning of @a str. 
					Otherwise, reading continues from the current position.
	 @param[in,out] context
					A pointer to the current position int he given string 
					@a str.
	 @param[out]	result
					A reference to the @c F32x4 represented by the next 
					token in the given string @a str.
	 @param[in]		delimiters
					A pointer to the null-terminated byte string containing 
					the delimiting characters.
	 @return		A token result indicating whether the conversion of the 
					next token in the given string to a @c F32x4 succeeded 
					or not.
	*/
	TokenResult ReadF32x4(char *str, char **context, F32x4 &result, 
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
	 Checks whether the next token in the given string represents a string.

	 @pre			@a str is not equal to @c nullptr.
	 @pre			@a delimiters is not equal to @c nullptr.
	 @param[in]		str
					A pointer to the null-terminated byte string.
	 @param[in]		delimiters
					A pointer to the null-terminated byte string containing the 
					delimiting characters.
	 @return		A token result indicating whether the conversion
					of the next token in the given string to a string succeeds 
					or not.
	 */
	TokenResult HasString(const char *str, 
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
					of the next token in the given string to a quoted string succeeds 
					or not.
	 */
	TokenResult HasQuotedString(const char *str, 
		const char *delimiters = g_default_delimiters) noexcept;

	/**
	 Checks whether the next token in the given string represents a @c bool.

	 @pre			@a str is not equal to @c nullptr.
	 @pre			@a delimiters is not equal to @c nullptr.
	 @param[in]		str
					A pointer to the null-terminated byte string.
	 @param[in]		delimiters
					A pointer to the null-terminated byte string containing the 
					delimiting characters.
	 @return		A token result indicating whether the conversion
					of the next token in the given string to a @c bool succeeds 
					or not.
	 */
	TokenResult HasBool(const char *str, 
		const char *delimiters = g_default_delimiters) noexcept;

	/**
	 Checks whether the next token in the given string represents an @c U8.

	 @pre			@a str is not equal to @c nullptr.
	 @pre			@a delimiters is not equal to @c nullptr.
	 @param[in]		str
					A pointer to the null-terminated byte string.
	 @param[in]		delimiters
					A pointer to the null-terminated byte string containing the 
					delimiting characters.
	 @return		A token result indicating whether the conversion
					of the next token in the given string to a @c S8 succeeds 
					or not.
	 */
	TokenResult HasS8(const char *str, 
		const char *delimiters = g_default_delimiters) noexcept;

	/**
	 Checks whether the next token in the given string represents an @c U8.

	 @pre			@a str is not equal to @c nullptr.
	 @pre			@a delimiters is not equal to @c nullptr.
	 @param[in]		str
					A pointer to the null-terminated byte string.
	 @param[in]		delimiters
					A pointer to the null-terminated byte string containing the 
					delimiting characters.
	 @return		A token result indicating whether the conversion
					of the next token in the given string to an @c U8 succeeds 
					or not.
	 */
	TokenResult HasU8(const char *str, 
		const char *delimiters = g_default_delimiters) noexcept;

	/**
	 Checks whether the next token in the given string represents a @c S16.

	 @pre			@a str is not equal to @c nullptr.
	 @pre			@a delimiters is not equal to @c nullptr.
	 @param[in]		str
					A pointer to the null-terminated byte string.
	 @param[in]		delimiters
					A pointer to the null-terminated byte string containing the 
					delimiting characters.
	 @return		A token result indicating whether the conversion
					of the next token in the given string to a @c S16 succeeds 
					or not.
	 */
	TokenResult HasS16(const char *str, 
		const char *delimiters = g_default_delimiters) noexcept;

	/**
	 Checks whether the next token in the given string represents an @c U16.

	 @pre			@a str is not equal to @c nullptr.
	 @pre			@a delimiters is not equal to @c nullptr.
	 @param[in]		str
					A pointer to the null-terminated byte string.
	 @param[in]		delimiters
					A pointer to the null-terminated byte string containing the 
					delimiting characters.
	 @return		A token result indicating whether the conversion
					of the next token in the given string to an @c U16 succeeds 
					or not.
	 */
	TokenResult HasU16(const char *str, 
		const char *delimiters = g_default_delimiters) noexcept;

	/**
	 Checks whether the next token in the given string represents a @c S32.

	 @pre			@a str is not equal to @c nullptr.
	 @pre			@a delimiters is not equal to @c nullptr.
	 @param[in]		str
					A pointer to the null-terminated byte string.
	 @param[in]		delimiters
					A pointer to the null-terminated byte string containing the 
					delimiting characters.
	 @return		A token result indicating whether the conversion
					of the next token in the given string to a @c S32 succeeds 
					or not.
	 */
	TokenResult HasS32(const char *str, 
		const char *delimiters = g_default_delimiters) noexcept;

	/**
	 Checks whether the next token in the given string represents an @c U32 .

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
	TokenResult HasU32(const char *str, 
		const char *delimiters = g_default_delimiters) noexcept;

	/**
	 Checks whether the next token in the given string represents a @c S64.

	 @pre			@a str is not equal to @c nullptr.
	 @pre			@a delimiters is not equal to @c nullptr.
	 @param[in]		str
					A pointer to the null-terminated byte string.
	 @param[in]		delimiters
					A pointer to the null-terminated byte string containing the 
					delimiting characters.
	 @return		A token result indicating whether the conversion
					of the next token in the given string to a @c S64 succeeds 
					or not.
	 */
	TokenResult HasS64(const char *str, 
		const char *delimiters = g_default_delimiters) noexcept;

	/**
	 Checks whether the next token in the given string represents an @c U64.

	 @pre			@a str is not equal to @c nullptr.
	 @pre			@a delimiters is not equal to @c nullptr.
	 @param[in]		str
					A pointer to the null-terminated byte string.
	 @param[in]		delimiters
					A pointer to the null-terminated byte string containing the 
					delimiting characters.
	 @return		A token result indicating whether the conversion
					of the next token in the given string to an @c U64 succeeds 
					or not.
	 */
	TokenResult HasU64(const char *str, 
		const char *delimiters = g_default_delimiters) noexcept;

	/**
	 Checks whether the next token in the given string represents a @c F32.

	 @pre			@a str is not equal to @c nullptr.
	 @pre			@a delimiters is not equal to @c nullptr.
	 @param[in]		str
					A pointer to the null-terminated byte string.
	 @param[in]		delimiters
					A pointer to the null-terminated byte string containing the 
					delimiting characters.
	 @return		A token result indicating whether the conversion
					of the next token in the given string to a @c F32 succeeds 
					or not.
	 */
	TokenResult HasF32(const char *str, 
		const char *delimiters = g_default_delimiters) noexcept;

	/**
	 Checks whether the next token in the given string represents a @c F64.

	 @pre			@a str is not equal to @c nullptr.
	 @pre			@a delimiters is not equal to @c nullptr.
	 @param[in]		str
					A pointer to the null-terminated byte string.
	 @param[in]		delimiters
					A pointer to the null-terminated byte string containing the 
					delimiting characters.
	 @return		A token result indicating whether the conversion
					of the next token in the given string to a @c F64 succeeds 
					or not.
	 */
	TokenResult HasF64(const char *str, 
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
	char *SkipDelimiters(
		char *str, const char *delimiters = g_default_delimiters) noexcept;

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
	const char *SkipDelimiters(
		const char *str, const char *delimiters = g_default_delimiters) noexcept;

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
	char *GotoDelimiters(
		char *str, const char *delimiters = g_default_delimiters) noexcept;

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
	const char *GotoDelimiters(
		const char *str, const char *delimiters = g_default_delimiters) noexcept;

#pragma endregion
}