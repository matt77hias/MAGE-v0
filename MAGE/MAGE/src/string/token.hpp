#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "string\string.hpp"
#include "math\math.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// System Includes
//-----------------------------------------------------------------------------
#pragma region

#include <stdint.h>

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 A pointer to the null-terminated byte string containing the default delimiters:
		1. space character;
		2. tab character;
		3. end of line (EOL) character;
		4. carriage return (CR) character.
	 */
	const char * const mage_default_delimiters = " \t\n\r";

	/**
	 An enumeration of the different token results.
	 
	 This contains: 
	 @c TokenResult_Valid, 
	 @c TokenResult_None and 
	 @c TokenResult_Invalid.
	 */
	enum TokenResult {
		TokenResult_Valid,		// The parsed token is valid (matches the expected token type).
		TokenResult_None,		// No token can be parsed (independent of the token type).
		TokenResult_Invalid		// The parsed token is invalid (matches the expected token type).
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
					A reference to the @c bool represented by the string @a str.
	 @return		A token result indicating whether the conversion
					of the given string @a str to a @c bool succeeded or not.
	 */
	TokenResult StringToBool(const char *str, bool &result) noexcept;

	/**
	 Converts the given string to a @c int8_t.

	 @param[in]		str
					A pointer to the null-terminated byte string to convert.
	 @param[out]	result
					A reference to the @c int8_t represented by the string @a str.
	 @return		A token result indicating whether the conversion
					of the given string @a str to a @c int8_t succeeded or not.
	 */
	TokenResult StringToInt8(const char *str, int8_t &result) noexcept;

	/**
	 Converts the given string to a @c uint8_t.

	 @param[in]		str
					A pointer to the null-terminated byte string to convert.
	 @param[out]	result
					A reference to the @c uint8_t represented by the string @a str.
	 @return		A token result indicating whether the conversion
					of the given string @a str to a @c uint8_t succeeded or not.
	 */
	TokenResult StringToUInt8(const char *str, uint8_t &result) noexcept;

	/**
	 Converts the given string to a @c int16_t.

	 @param[in]		str
					A pointer to the null-terminated byte string to convert.
	 @param[out]	result
					A reference to the @c int16_t represented by the string @a str.
	 @return		A token result indicating whether the conversion
					of the given string @a str to a @c int16_t succeeded or not.
	 */
	TokenResult StringToInt16(const char *str, int16_t &result) noexcept;

	/**
	 Converts the given string to a @c uint16_t.

	 @param[in]		str
					A pointer to the null-terminated byte string to convert.
	 @param[out]	result
					A reference to the @c uint16_t represented by the string @a str.
	 @return		A token result indicating whether the conversion
					of the given string @a str to a @c uint16_t succeeded or not.
	 */
	TokenResult StringToUInt16(const char *str, uint16_t &result) noexcept;

	/**
	 Converts the given string to a @c int32_t.

	 @param[in]		str
					A pointer to the null-terminated byte string to convert.
	 @param[out]	result
					A reference to the @c int32_t represented by the string @a str.
	 @return		A token result indicating whether the conversion
					of the given string @a str to a @c int32_t succeeded or not.
	 */
	TokenResult StringToInt32(const char *str, int32_t &result) noexcept;

	/**
	 Converts the given string to a @c uint32_t.

	 @param[in]		str
					A pointer to the null-terminated byte string to convert.
	 @param[out]	result
					A reference to the @c uint32_t represented by the string @a str.
	 @return		A token result indicating whether the conversion
					of the given string @a str to a @c uint32_t succeeded or not.
	 */
	TokenResult StringToUInt32(const char *str, uint32_t &result) noexcept;

	/**
	 Converts the given string to a @c int64_t.

	 @param[in]		str
					A pointer to the null-terminated byte string to convert.
	 @param[out]	result
					A reference to the @c int64_t represented by the string @a str.
	 @return		A token result indicating whether the conversion
					of the given string @a str to a @c int64_t succeeded or not.
	 */
	TokenResult StringToInt64(const char *str, int64_t &result) noexcept;

	/**
	 Converts the given string to a @c uint64_t.

	 @param[in]		str
					A pointer to the null-terminated byte string to convert.
	 @param[out]	result
					A reference to the @c uint64_t represented by the string @a str.
	 @return		A token result indicating whether the conversion
					of the given string @a str to a @c uint64_t succeeded or not.
	 */
	TokenResult StringToUInt64(const char *str, uint64_t &result) noexcept;

	/**
	 Converts the given string to a @c float.

	 @param[in]		str
					A pointer to the null-terminated byte string to convert.
	 @param[out]	result
					A reference to the @c float represented by the string @a str.
	 @return		A token result indicating whether the conversion
					of the given string @a str to a @c float succeeded or not.
	 */
	TokenResult StringToFloat(const char *str, float &result) noexcept;

	/**
	 Converts the given string to a @c double.

	 @param[in]		str
					A pointer to the null-terminated byte string to convert.
	 @param[out]	result
					A reference to the @c double represented by the string @a str.
	 @return		A token result indicating whether the conversion
					of the given string @a str to a @c double succeeded or not.
	 */
	TokenResult StringToDouble(const char *str, double &result) noexcept;

#pragma endregion

	//-------------------------------------------------------------------------
	// String Conversion Utilities: Substring
	//-------------------------------------------------------------------------
#pragma region

	/**
	 Converts the given string to a @c bool (@c true or @c false).

	 @pre			@a end is not equal to @c nullptr 
					if @a begin is not equal to @c nullptr.
	 @param[in]		begin
					A pointer to the begin (inclusive) of the string to convert.
	 @param[in]		end
					A pointer to the end (exclusive) of the string to convert.
	 @param[out]	result
					A reference to the @c bool represented by the string @a str.
	 @return		A token result indicating whether the conversion
					of the given string @a str to a @c bool succeeded or not.
	 */
	TokenResult StringToBool(const char *begin, const char *end, bool &result) noexcept;
	
	/**
	 Converts the given string to a @c int8_t.

	 @pre			@a end is not equal to @c nullptr 
					if @a begin is not equal to @c nullptr.
	 @param[in]		begin
					A pointer to the begin (inclusive) of the string to convert.
	 @param[in]		end
					A pointer to the end (exclusive) of the string to convert.
	 @param[out]	result
					A reference to the @c int8_t represented by the string @a str.
	 @return		A token result indicating whether the conversion
					of the given string @a str to a @c int8_t succeeded or not.
	 */
	TokenResult StringToInt8(const char *begin, const char *end, int8_t &result) noexcept;
	
	/**
	 Converts the given string to a @c uint8_t.

	 @pre			@a end is not equal to @c nullptr 
					if @a begin is not equal to @c nullptr.
	 @param[in]		begin
					A pointer to the begin (inclusive) of the string to convert.
	 @param[in]		end
					A pointer to the end (exclusive) of the string to convert.
	 @param[out]	result
					A reference to the @c uint8_t represented by the string @a str.
	 @return		A token result indicating whether the conversion
					of the given string @a str to a @c uint8_t succeeded or not.
	 */
	TokenResult StringToUInt8(const char *begin, const char *end, uint8_t &result) noexcept;
	
	/**
	 Converts the given string to a @c int16_t.

	 @pre			@a end is not equal to @c nullptr 
					if @a begin is not equal to @c nullptr.
	 @param[in]		begin
					A pointer to the begin (inclusive) of the string to convert.
	 @param[in]		end
					A pointer to the end (exclusive) of the string to convert.
	 @param[out]	result
					A reference to the @c int16_t represented by the string @a str.
	 @return		A token result indicating whether the conversion
					of the given string @a str to a @c int16_t succeeded or not.
	 */
	TokenResult StringToInt16(const char *begin, const char *end, int16_t &result) noexcept;
	
	/**
	 Converts the given string to a @c uint16_t.

	 @pre			@a end is not equal to @c nullptr 
					if @a begin is not equal to @c nullptr.
	 @param[in]		begin
					A pointer to the begin (inclusive) of the string to convert.
	 @param[in]		end
					A pointer to the end (exclusive) of the string to convert.
	 @param[out]	result
					A reference to the @c uint16_t represented by the string @a str.
	 @return		A token result indicating whether the conversion
					of the given string @a str to a @c uint16_t succeeded or not.
	 */
	TokenResult StringToUInt16(const char *begin, const char *end, uint16_t &result) noexcept;
	
	/**
	 Converts the given string to a @c int32_t.

	 @pre			@a end is not equal to @c nullptr 
					if @a begin is not equal to @c nullptr.
	 @param[in]		begin
					A pointer to the begin (inclusive) of the string to convert.
	 @param[in]		end
					A pointer to the end (exclusive) of the string to convert.
	 @param[out]	result
					A reference to the @c int32_t represented by the string @a str.
	 @return		A token result indicating whether the conversion
					of the given string @a str to a @c int32_t succeeded or not.
	 */
	TokenResult StringToInt32(const char *begin, const char *end, int32_t &result) noexcept;
	
	/**
	 Converts the given string to a @c uint32_t.

	 @pre			@a end is not equal to @c nullptr 
					if @a begin is not equal to @c nullptr.
	 @param[in]		begin
					A pointer to the begin (inclusive) of the string to convert.
	 @param[in]		end
					A pointer to the end (exclusive) of the string to convert.
	 @param[out]	result
					A reference to the @c uint32_t represented by the string @a str.
	 @return		A token result indicating whether the conversion
					of the given string @a str to a @c uint32_t succeeded or not.
	 */
	TokenResult StringToUInt32(const char *begin, const char *end, uint32_t &result) noexcept;
	
	/**
	 Converts the given string to a @c int64_t.

	 @pre			@a end is not equal to @c nullptr 
					if @a begin is not equal to @c nullptr.
	 @param[in]		begin
					A pointer to the begin (inclusive) of the string to convert.
	 @param[in]		end
					A pointer to the end (exclusive) of the string to convert.
	 @param[out]	result
					A reference to the @c int64_t represented by the string @a str.
	 @return		A token result indicating whether the conversion
					of the given string @a str to a @c int64_t succeeded or not.
	 */
	TokenResult StringToInt64(const char *begin, const char *end, int64_t &result) noexcept;
	
	/**
	 Converts the given string to a @c uint64_t.

	 @pre			@a end is not equal to @c nullptr 
					if @a begin is not equal to @c nullptr.
	 @param[in]		begin
					A pointer to the begin (inclusive) of the string to convert.
	 @param[in]		end
					A pointer to the end (exclusive) of the string to convert.
	 @param[out]	result
					A reference to the @c uint64_t represented by the string @a str.
	 @return		A token result indicating whether the conversion
					of the given string @a str to a @c uint64_t succeeded or not.
	 */
	TokenResult StringToUInt64(const char *begin, const char *end, uint64_t &result) noexcept;
	
	/**
	 Converts the given string to a @c float.

	 @pre			@a end is not equal to @c nullptr 
					if @a begin is not equal to @c nullptr.
	 @param[in]		begin
					A pointer to the begin (inclusive) of the string to convert.
	 @param[in]		end
					A pointer to the end (exclusive) of the string to convert.
	 @param[out]	result
					A reference to the @c float represented by the string @a str.
	 @return		A token result indicating whether the conversion
					of the given string @a str to a @c float succeeded or not.
	 */
	TokenResult StringToFloat(const char *begin, const char *end, float &result) noexcept;
	
	/**
	 Converts the given string to a @c double.

	 @pre			@a end is not equal to @c nullptr 
					if @a begin is not equal to @c nullptr.
	 @param[in]		begin
					A pointer to the begin (inclusive) of the string to convert.
	 @param[in]		end
					A pointer to the end (exclusive) of the string to convert.
	 @param[out]	result
					A reference to the @c double represented by the string @a str.
	 @return		A token result indicating whether the conversion
					of the given string @a str to a @c double succeeded or not.
	 */
	TokenResult StringToDouble(const char *begin, const char *end, double &result) noexcept;

#pragma endregion

	//-------------------------------------------------------------------------
	// String Conversion Utilities: String Prefix
	//-------------------------------------------------------------------------
#pragma region

	/**
	 Converts the prefix of the given string @a str to a @c int8_t.

	 @param[in]		str
					A pointer to the null-terminated byte string to convert.
	 @param[out]	result
					A reference to the @c int8_t represented by the prefix of the given string @a str.
	 @return		A token result indicating whether the conversion of the prefix 
					of the given string @a str to a @c int8_t succeeded or not.
	 */
	TokenResult StringPrefixToInt8(const char *str, int8_t &result) noexcept;

	/**
	 Converts the prefix of the given string @a str to a @c uint8_t.

	 @param[in]		str
					A pointer to the null-terminated byte string to convert.
	 @param[out]	result
					A reference to the @c uint8_t represented by the prefix of the given string @a str.
	 @return		A token result indicating whether the conversion of the prefix 
					of the given string @a str to a @c uint8_t succeeded or not.
	 */
	TokenResult StringPrefixToUInt8(const char *str, uint8_t &result) noexcept;

	/**
	 Converts the prefix of the given string @a str to a @c int16_t.

	 @param[in]		str
					A pointer to the null-terminated byte string to convert.
	 @param[out]	result
					A reference to the @c int16_t represented by the prefix of the given string @a str.
	 @return		A token result indicating whether the conversion of the prefix 
					of the given string @a str to a @c int16_t succeeded or not.
	 */
	TokenResult StringPrefixToInt16(const char *str, int16_t &result) noexcept;

	/**
	 Converts the prefix of the given string @a str to a @c uint16_t.

	 @param[in]		str
					A pointer to the null-terminated byte string to convert.
	 @param[out]	result
					A reference to the @c uint16_t represented by the prefix of the given string @a str.
	 @return		A token result indicating whether the conversion of the prefix 
					of the given string @a str to a @c uint16_t succeeded or not.
	 */
	TokenResult StringPrefixToUInt16(const char *str, uint16_t &result) noexcept;

	/**
	 Converts the prefix of the given string @a str to a @c int32_t.

	 @param[in]		str
					A pointer to the null-terminated byte string to convert.
	 @param[out]	result
					A reference to the @c int32_t represented by the prefix of the given string @a str.
	 @return		A token result indicating whether the conversion of the prefix 
					of the given string @a str to a @c int32_t succeeded or not.
	 */
	TokenResult StringPrefixToInt32(const char *str, int32_t &result) noexcept;

	/**
	 Converts the prefix of the given string @a str to a @c uint32_t.

	 @param[in]		str
					A pointer to the null-terminated byte string to convert.
	 @param[out]	result
					A reference to the @c uint32_t represented by the prefix of the given string @a str.
	 @return		A token result indicating whether the conversion of the prefix 
					of the given string @a str to a @c uint32_t succeeded or not.
	 */
	TokenResult StringPrefixToUInt32(const char *str, uint32_t &result) noexcept;

	/**
	 Converts the prefix of the given string @a str to a @c int64_t.

	 @param[in]		str
					A pointer to the null-terminated byte string to convert.
	 @param[out]	result
					A reference to the @c int64_t represented by the prefix of the given string @a str.
	 @return		A token result indicating whether the conversion of the prefix 
					of the given string @a str to a @c int64_t succeeded or not.
	 */
	TokenResult StringPrefixToInt64(const char *str, int64_t &result) noexcept;

	/**
	 Converts the prefix of the given string @a str to a @c uint64_t.

	 @param[in]		str
					A pointer to the null-terminated byte string to convert.
	 @param[out]	result
					A reference to the @c uint64_t represented by the prefix of the given string @a str.
	 @return		A token result indicating whether the conversion of the prefix 
					of the given string @a str to a @c uint64_t succeeded or not.
	 */
	TokenResult StringPrefixToUInt64(const char *str, uint64_t &result) noexcept;

	/**
	 Converts the prefix of the given string @a str to a @c float.

	 @param[in]		str
					A pointer to the null-terminated byte string to convert.
	 @param[out]	result
					A reference to the @c float represented by the prefix of the given string @a str.
	 @return		A token result indicating whether the conversion of the prefix 
					of the given string @a str to a @c float succeeded or not.
	 */
	TokenResult StringPrefixToFloat(const char *str, float &result) noexcept;

	/**
	 Converts the prefix of the given string @a str to a @c double.

	 @param[in]		str
					A pointer to the null-terminated byte string to convert.
	 @param[out]	result
					A reference to the @c double represented by the prefix of the given string @a str.
	 @return		A token result indicating whether the conversion of the prefix 
					of the given string @a str to a @c double succeeded or not.
	 */
	TokenResult StringPrefixToDouble(const char *str, double &result) noexcept;

#pragma endregion

	//-------------------------------------------------------------------------
	// Parsing Utilities: Reading
	//-------------------------------------------------------------------------
#pragma region

	/**
	 Reads and converts the next token in the given string to (non-delimiting) characters.

	 @pre			@a str or @a context is not equal to @c nullptr.
	 @pre			@a result is not equal to @c nullptr.
	 @pre			@a delimiters is not equal to @c nullptr.
	 @param[in]		str
					A pointer to the null-terminated byte string.
					If @a str is equal to @c nullptr,
					reading continues from the beginning of @a str.
					Otherwise, reading continues from the current position.
	 @param[in,out] context
					A pointer to the current position int he given string @a str.
	 @param[out]	result
					A pointer to the pointer to the characters represented by the next token in the given string @a str.
	 @param[in]		delimiters
					A pointer to the null-terminated byte string containing the delimiting characters.
	 @return		A token result indicating whether the conversion
					of the next token in the given string to characters succeeded or not.
	 */
	TokenResult ReadChars(char *str, char **context, char **result, const char *delimiters = mage_default_delimiters) noexcept;
	
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
					A pointer to the current position int he given string @a str.
	 @param[out]	result
					A reference to the string represented by the next token in the given string @a str.
	 @param[in]		delimiters
					A pointer to the null-terminated byte string containing the delimiting characters.
	 @return		A token result indicating whether the conversion
					of the next token in the given string to a string succeeded or not.
	 */
	TokenResult ReadString(char *str, char **context, string &result, const char *delimiters = mage_default_delimiters);
	
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
					A pointer to the current position int he given string @a str.
	 @param[out]	result
					A reference to the quoted string represented by the next token in the given string @a str.
	 @param[in]		delimiters
					A pointer to the null-terminated byte string containing the delimiting characters.
	 @return		A token result indicating whether the conversion
					of the next token in the given string to a quoted string succeeded or not.
	 */
	TokenResult ReadQuotedString(char *str, char **context, string &result, const char *delimiters = mage_default_delimiters);
	
	/**
	 Reads and converts the next token in the given string to a @c bool (@c true or @c false).

	 @pre			@a str or @a context is not equal to @c nullptr.
	 @pre			@a delimiters is not equal to @c nullptr.
	 @param[in]		str
					A pointer to the null-terminated byte string.
					If @a str is equal to @c nullptr,
					reading continues from the beginning of @a str.
					Otherwise, reading continues from the current position.
	 @param[in,out] context
					A pointer to the current position int he given string @a str.
	 @param[out]	result
					A reference to the @c bool represented by the next token in the given string @a str.
	 @param[in]		delimiters
					A pointer to the null-terminated byte string containing the delimiting characters.
	 @return		A token result indicating whether the conversion
					of the next token in the given string to a @c bool succeeded or not.
	 */
	TokenResult ReadBool(char *str, char **context, bool &result, const char *delimiters = mage_default_delimiters) noexcept;
	
	/**
	 Reads and converts the next token in the given string to a @c int8_t.

	 @pre			@a str or @a context is not equal to @c nullptr.
	 @pre			@a delimiters is not equal to @c nullptr.
	 @param[in]		str
					A pointer to the null-terminated byte string.
					If @a str is equal to @c nullptr,
					reading continues from the beginning of @a str.
					Otherwise, reading continues from the current position.
	 @param[in,out] context
					A pointer to the current position int he given string @a str.
	 @param[out]	result
					A reference to the @c int8_t represented by the next token in the given string @a str.
	 @param[in]		delimiters
					A pointer to the null-terminated byte string containing the delimiting characters.
	 @return		A token result indicating whether the conversion
					of the next token in the given string to a @c int8_t succeeded or not.
	 */
	TokenResult ReadInt8(char *str, char **context, int8_t &result, const char *delimiters = mage_default_delimiters) noexcept;
	
	/**
	 Reads and converts the next token in the given string to a @c uint8_t.

	 @pre			@a str or @a context is not equal to @c nullptr.
	 @pre			@a delimiters is not equal to @c nullptr.
	 @param[in]		str
					A pointer to the null-terminated byte string.
					If @a str is equal to @c nullptr,
					reading continues from the beginning of @a str.
					Otherwise, reading continues from the current position.
	 @param[in,out] context
					A pointer to the current position int he given string @a str.
	 @param[out]	result
					A reference to the @c uint8_t represented by the next token in the given string @a str.
	 @param[in]		delimiters
					A pointer to the null-terminated byte string containing the delimiting characters.
	 @return		A token result indicating whether the conversion
					of the next token in the given string to a @c uint8_t succeeded or not.
	 */
	TokenResult ReadUInt8(char *str, char **context, uint8_t &result, const char *delimiters = mage_default_delimiters) noexcept;
	
	/**
	 Reads and converts the next token in the given string to a @c int16_t.

	 @pre			@a str or @a context is not equal to @c nullptr.
	 @pre			@a delimiters is not equal to @c nullptr.
	 @param[in]		str
					A pointer to the null-terminated byte string.
					If @a str is equal to @c nullptr,
					reading continues from the beginning of @a str.
					Otherwise, reading continues from the current position.
	 @param[in,out] context
					A pointer to the current position int he given string @a str.
	 @param[out]	result
					A reference to the @c int16_t represented by the next token in the given string @a str.
	 @param[in]		delimiters
					A pointer to the null-terminated byte string containing the delimiting characters.
	 @return		A token result indicating whether the conversion
					of the next token in the given string to a @c int16_t succeeded or not.
	 */
	TokenResult ReadInt16(char *str, char **context, int16_t &result, const char *delimiters = mage_default_delimiters) noexcept;
	
	/**
	 Reads and converts the next token in the given string to a @c uint16_t.

	 @pre			@a str or @a context is not equal to @c nullptr.
	 @pre			@a delimiters is not equal to @c nullptr.
	 @param[in]		str
					A pointer to the null-terminated byte string.
					If @a str is equal to @c nullptr,
					reading continues from the beginning of @a str.
					Otherwise, reading continues from the current position.
	 @param[in,out] context
					A pointer to the current position int he given string @a str.
	 @param[out]	result
					A reference to the @c uint16_t represented by the next token in the given string @a str.
	 @param[in]		delimiters
					A pointer to the null-terminated byte string containing the delimiting characters.
	 @return		A token result indicating whether the conversion
					of the next token in the given string to a @c uint16_t succeeded or not.
	 */
	TokenResult ReadUInt16(char *str, char **context, uint16_t &result, const char *delimiters = mage_default_delimiters) noexcept;
	
	/**
	 Reads and converts the next token in the given string to a @c int32_t.

	 @pre			@a str or @a context is not equal to @c nullptr.
	 @pre			@a delimiters is not equal to @c nullptr.
	 @param[in]		str
					A pointer to the null-terminated byte string.
					If @a str is equal to @c nullptr,
					reading continues from the beginning of @a str.
					Otherwise, reading continues from the current position.
	 @param[in,out] context
					A pointer to the current position int he given string @a str.
	 @param[out]	result
					A reference to the @c int32_t represented by the next token in the given string @a str.
	 @param[in]		delimiters
					A pointer to the null-terminated byte string containing the delimiting characters.
	 @return		A token result indicating whether the conversion
					of the next token in the given string to a @c int32_t succeeded or not.
	 */
	TokenResult ReadInt32(char *str, char **context, int32_t &result, const char *delimiters = mage_default_delimiters) noexcept;
	
	/**
	 Reads and converts the next token in the given string to a @c uint32_t.

	 @pre			@a str or @a context is not equal to @c nullptr.
	 @pre			@a delimiters is not equal to @c nullptr.
	 @param[in]		str
					A pointer to the null-terminated byte string.
					If @a str is equal to @c nullptr,
					reading continues from the beginning of @a str.
					Otherwise, reading continues from the current position.
	 @param[in,out] context
					A pointer to the current position int he given string @a str.
	 @param[out]	result
					A reference to the @c uint32_t represented by the next token in the given string @a str.
	 @param[in]		delimiters
					A pointer to the null-terminated byte string containing the delimiting characters.
	 @return		A token result indicating whether the conversion
					of the next token in the given string to a @c uint32_t succeeded or not.
	 */
	TokenResult ReadUInt32(char *str, char **context, uint32_t &result, const char *delimiters = mage_default_delimiters) noexcept;
	
	/**
	 Reads and converts the next token in the given string to a @c int64_t.

	 @pre			@a str or @a context is not equal to @c nullptr.
	 @pre			@a delimiters is not equal to @c nullptr.
	 @param[in]		str
					A pointer to the null-terminated byte string.
					If @a str is equal to @c nullptr,
					reading continues from the beginning of @a str.
					Otherwise, reading continues from the current position.
	 @param[in,out] context
					A pointer to the current position int he given string @a str.
	 @param[out]	result
					A reference to the @c int64_t represented by the next token in the given string @a str.
	 @param[in]		delimiters
					A pointer to the null-terminated byte string containing the delimiting characters.
	 @return		A token result indicating whether the conversion
					of the next token in the given string to a @c int64_t succeeded or not.
	 */
	TokenResult ReadInt64(char *str, char **context, int64_t &result, const char *delimiters = mage_default_delimiters) noexcept;
	
	/**
	 Reads and converts the next token in the given string to a @c uint64_t.

	 @pre			@a str or @a context is not equal to @c nullptr.
	 @pre			@a delimiters is not equal to @c nullptr.
	 @param[in]		str
					A pointer to the null-terminated byte string.
					If @a str is equal to @c nullptr,
					reading continues from the beginning of @a str.
					Otherwise, reading continues from the current position.
	 @param[in,out] context
					A pointer to the current position int he given string @a str.
	 @param[out]	result
					A reference to the @c uint64_t represented by the next token in the given string @a str.
	 @param[in]		delimiters
					A pointer to the null-terminated byte string containing the delimiting characters.
	 @return		A token result indicating whether the conversion
					of the next token in the given string to a @c uint64_t succeeded or not.
	 */
	TokenResult ReadUInt64(char *str, char **context, uint64_t &result, const char *delimiters = mage_default_delimiters) noexcept;
	
	/**
	 Reads and converts the next token in the given string to a @c float.

	 @pre			@a str or @a context is not equal to @c nullptr.
	 @pre			@a delimiters is not equal to @c nullptr.
	 @param[in]		str
					A pointer to the null-terminated byte string.
					If @a str is equal to @c nullptr,
					reading continues from the beginning of @a str.
					Otherwise, reading continues from the current position.
	 @param[in,out] context
					A pointer to the current position int he given string @a str.
	 @param[out]	result
					A reference to the @c float represented by the next token in the given string @a str.
	 @param[in]		delimiters
					A pointer to the null-terminated byte string containing the delimiting characters.
	 @return		A token result indicating whether the conversion
					of the next token in the given string to a @c float succeeded or not.
	 */
	TokenResult ReadFloat(char *str, char **context, float &result, const char *delimiters = mage_default_delimiters) noexcept;
	
	/**
	 Reads and converts the next token in the given string to a @c double.

	 @pre			@a str or @a context is not equal to @c nullptr.
	 @pre			@a delimiters is not equal to @c nullptr.
	 @param[in]		str
					A pointer to the null-terminated byte string.
					If @a str is equal to @c nullptr,
					reading continues from the beginning of @a str.
					Otherwise, reading continues from the current position.
	 @param[in,out] context
					A pointer to the current position int he given string @a str.
	 @param[out]	result
					A reference to the @c double represented by the next token in the given string @a str.
	 @param[in]		delimiters
					A pointer to the null-terminated byte string containing the delimiting characters.
	 @return		A token result indicating whether the conversion
					of the next token in the given string to a @c double succeeded or not.
	 */
	TokenResult ReadDouble(char *str, char **context, double &result, const char *delimiters = mage_default_delimiters) noexcept;
	
	/**
	 Reads and converts the next token in the given string to a @c XMFLOAT2.

	 @pre			@a str or @a context is not equal to @c nullptr.
	 @pre			@a delimiters is not equal to @c nullptr.
	 @param[in]		str
					A pointer to the null-terminated byte string.
					If @a str is equal to @c nullptr,
					reading continues from the beginning of @a str.
					Otherwise, reading continues from the current position.
	 @param[in,out] context
					A pointer to the current position int he given string @a str.
	 @param[out]	result
					A reference to the @c XMFLOAT2 represented by the next token in the given string @a str.
	 @param[in]		delimiters
					A pointer to the null-terminated byte string containing the delimiting characters.
	 @return		A token result indicating whether the conversion
					of the next token in the given string to a @c XMFLOAT2 succeeded or not.
	 */
	TokenResult ReadFloat2(char *str, char **context, XMFLOAT2 &result, const char *delimiters = mage_default_delimiters) noexcept;
	
	/**
	 Reads and converts the next token in the given string to a @c XMFLOAT3.

	 @pre			@a str or @a context is not equal to @c nullptr.
	 @pre			@a delimiters is not equal to @c nullptr.
	 @param[in]		str
					A pointer to the null-terminated byte string.
					If @a str is equal to @c nullptr,
					reading continues from the beginning of @a str.
					Otherwise, reading continues from the current position.
	 @param[in,out] context
					A pointer to the current position int he given string @a str.
	 @param[out]	result
					A reference to the @c XMFLOAT3 represented by the next token in the given string @a str.
	 @param[in]		delimiters
					A pointer to the null-terminated byte string containing the delimiting characters.
	 @return		A token result indicating whether the conversion
					of the next token in the given string to a @c XMFLOAT3 succeeded or not.
	 */
	TokenResult ReadFloat3(char *str, char **context, XMFLOAT3 &result, const char *delimiters = mage_default_delimiters) noexcept;

	/**
	 Reads and converts the next token in the given string to a @c XMFLOAT4.

	 @pre			@a str or @a context is not equal to @c nullptr.
	 @pre			@a delimiters is not equal to @c nullptr.
	 @param[in]		str
					A pointer to the null-terminated byte string.
					If @a str is equal to @c nullptr, 
					reading continues from the beginning of @a str. 
					Otherwise, reading continues from the current position.
	 @param[in,out] context
					A pointer to the current position int he given string @a str.
	 @param[out]	result
					A reference to the @c XMFLOAT4 represented by the next token in the given string @a str.
	 @param[in]		delimiters
					A pointer to the null-terminated byte string containing the delimiting characters.
	 @return		A token result indicating whether the conversion
					of the next token in the given string to a @c XMFLOAT4 succeeded or not.
	*/
	TokenResult ReadFloat4(char *str, char **context, XMFLOAT4 &result, const char *delimiters = mage_default_delimiters) noexcept;

#pragma endregion

	//-------------------------------------------------------------------------
	// Parsing Utilities: Peaking
	//-------------------------------------------------------------------------
#pragma region

	/**
	 Checks whether the next token in the given string represents (non-delimiting) characters.
	 
	 @pre			@a str is not equal to @c nullptr.
	 @pre			@a delimiters is not equal to @c nullptr.
	 @param[in]		str
					A pointer to the null-terminated byte string.
	 @param[in]		delimiters
					A pointer to the null-terminated byte string containing the delimiting characters.
	 @return		A token result indicating whether the conversion
					of the next token in the given string to a @c uint32_t succeeds or not.
	 */
	TokenResult HasChars(const char *str, const char *delimiters = mage_default_delimiters) noexcept;

	/**
	 Checks whether the next token in the given string represents a string.

	 @pre			@a str is not equal to @c nullptr.
	 @pre			@a delimiters is not equal to @c nullptr.
	 @param[in]		str
					A pointer to the null-terminated byte string.
	 @param[in]		delimiters
					A pointer to the null-terminated byte string containing the delimiting characters.
	 @return		A token result indicating whether the conversion
					of the next token in the given string to a string succeeds or not.
	 */
	TokenResult HasString(const char *str, const char *delimiters = mage_default_delimiters) noexcept;

	/**
	 Checks whether the next token in the given string represents a quoted string.

	 @pre			@a str is not equal to @c nullptr.
	 @pre			@a delimiters is not equal to @c nullptr.
	 @pre			The quote '"' may not be delimiter.
	 @param[in]		str
					A pointer to the null-terminated byte string.
	 @param[in]		delimiters
					A pointer to the null-terminated byte string containing the delimiting characters.
	 @return		A token result indicating whether the conversion
					of the next token in the given string to a quoted string succeeds or not.
	 */
	TokenResult HasQuotedString(const char *str, const char *delimiters = mage_default_delimiters) noexcept;

	/**
	 Checks whether the next token in the given string represents a @c bool.

	 @pre			@a str is not equal to @c nullptr.
	 @pre			@a delimiters is not equal to @c nullptr.
	 @param[in]		str
					A pointer to the null-terminated byte string.
	 @param[in]		delimiters
					A pointer to the null-terminated byte string containing the delimiting characters.
	 @return		A token result indicating whether the conversion
					of the next token in the given string to a @c bool succeeds or not.
	 */
	TokenResult HasBool(const char *str, const char *delimiters = mage_default_delimiters) noexcept;

	/**
	 Checks whether the next token in the given string represents a @c uint8_t.

	 @pre			@a str is not equal to @c nullptr.
	 @pre			@a delimiters is not equal to @c nullptr.
	 @param[in]		str
					A pointer to the null-terminated byte string.
	 @param[in]		delimiters
					A pointer to the null-terminated byte string containing the delimiting characters.
	 @return		A token result indicating whether the conversion
					of the next token in the given string to a @c int8_t succeeds or not.
	 */
	TokenResult HasInt8(const char *str, const char *delimiters = mage_default_delimiters) noexcept;

	/**
	 Checks whether the next token in the given string represents a @c uint8_t.

	 @pre			@a str is not equal to @c nullptr.
	 @pre			@a delimiters is not equal to @c nullptr.
	 @param[in]		str
					A pointer to the null-terminated byte string.
	 @param[in]		delimiters
					A pointer to the null-terminated byte string containing the delimiting characters.
	 @return		A token result indicating whether the conversion
					of the next token in the given string to a @c uint8_t succeeds or not.
	 */
	TokenResult HasUInt8(const char *str, const char *delimiters = mage_default_delimiters) noexcept;

	/**
	 Checks whether the next token in the given string represents a @c int16_t.

	 @pre			@a str is not equal to @c nullptr.
	 @pre			@a delimiters is not equal to @c nullptr.
	 @param[in]		str
					A pointer to the null-terminated byte string.
	 @param[in]		delimiters
					A pointer to the null-terminated byte string containing the delimiting characters.
	 @return		A token result indicating whether the conversion
					of the next token in the given string to a @c int16_t succeeds or not.
	 */
	TokenResult HasInt16(const char *str, const char *delimiters = mage_default_delimiters) noexcept;

	/**
	 Checks whether the next token in the given string represents a @c uint16_t.

	 @pre			@a str is not equal to @c nullptr.
	 @pre			@a delimiters is not equal to @c nullptr.
	 @param[in]		str
					A pointer to the null-terminated byte string.
	 @param[in]		delimiters
					A pointer to the null-terminated byte string containing the delimiting characters.
	 @return		A token result indicating whether the conversion
					of the next token in the given string to a @c uint16_t succeeds or not.
	 */
	TokenResult HasUInt16(const char *str, const char *delimiters = mage_default_delimiters) noexcept;

	/**
	 Checks whether the next token in the given string represents a @c int32_t.

	 @pre			@a str is not equal to @c nullptr.
	 @pre			@a delimiters is not equal to @c nullptr.
	 @param[in]		str
					A pointer to the null-terminated byte string.
	 @param[in]		delimiters
					A pointer to the null-terminated byte string containing the delimiting characters.
	 @return		A token result indicating whether the conversion
					of the next token in the given string to a @c int32_t succeeds or not.
	 */
	TokenResult HasInt32(const char *str, const char *delimiters = mage_default_delimiters) noexcept;

	/**
	 Checks whether the next token in the given string represents a @c uint32_t .

	 @pre			@a str is not equal to @c nullptr.
	 @pre			@a delimiters is not equal to @c nullptr.
	 @param[in]		str
					A pointer to the null-terminated byte string.
	 @param[in]		delimiters
					A pointer to the null-terminated byte string containing the delimiting characters.
	 @return		A token result indicating whether the conversion
					of the next token in the given string to a @c uint32_t succeeds or not.
	 */
	TokenResult HasUInt32(const char *str, const char *delimiters = mage_default_delimiters) noexcept;

	/**
	 Checks whether the next token in the given string represents a @c int64_t.

	 @pre			@a str is not equal to @c nullptr.
	 @pre			@a delimiters is not equal to @c nullptr.
	 @param[in]		str
					A pointer to the null-terminated byte string.
	 @param[in]		delimiters
					A pointer to the null-terminated byte string containing the delimiting characters.
	 @return		A token result indicating whether the conversion
					of the next token in the given string to a @c int64_t succeeds or not.
	 */
	TokenResult HasInt64(const char *str, const char *delimiters = mage_default_delimiters) noexcept;

	/**
	 Checks whether the next token in the given string represents a @c uint64_t.

	 @pre			@a str is not equal to @c nullptr.
	 @pre			@a delimiters is not equal to @c nullptr.
	 @param[in]		str
					A pointer to the null-terminated byte string.
	 @param[in]		delimiters
					A pointer to the null-terminated byte string containing the delimiting characters.
	 @return		A token result indicating whether the conversion
					of the next token in the given string to a @c uint64_t succeeds or not.
	 */
	TokenResult HasUInt64(const char *str, const char *delimiters = mage_default_delimiters) noexcept;

	/**
	 Checks whether the next token in the given string represents a @c float.

	 @pre			@a str is not equal to @c nullptr.
	 @pre			@a delimiters is not equal to @c nullptr.
	 @param[in]		str
					A pointer to the null-terminated byte string.
	 @param[in]		delimiters
					A pointer to the null-terminated byte string containing the delimiting characters.
	 @return		A token result indicating whether the conversion
					of the next token in the given string to a @c float succeeds or not.
	 */
	TokenResult HasFloat(const char *str, const char *delimiters = mage_default_delimiters) noexcept;

	/**
	 Checks whether the next token in the given string represents a @c double.

	 @pre			@a str is not equal to @c nullptr.
	 @pre			@a delimiters is not equal to @c nullptr.
	 @param[in]		str
					A pointer to the null-terminated byte string.
	 @param[in]		delimiters
					A pointer to the null-terminated byte string containing the delimiting characters.
	 @return		A token result indicating whether the conversion
					of the next token in the given string to a @c double succeeds or not.
	 */
	TokenResult HasDouble(const char *str, const char *delimiters = mage_default_delimiters) noexcept;

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
					A pointer to the null-terminated byte string containing the delimiting characters.
	 @return		@c nullptr if the end of string character is reached.
	 @return		A pointer to the first non-delimiting character in the given string.
	 */
	char *SkipDelimiters(char *str, const char *delimiters = mage_default_delimiters) noexcept;

	/**
	 Advances to the first non-delimiting character in the given string.

	 @pre			@a str is not equal to @c nullptr.
	 @pre			@a delimiters is not equal to @c nullptr.
	 @param[in]		str
					A pointer to the null-terminated byte string.
	 @param[in]		delimiters
					A pointer to the null-terminated byte string containing the delimiting characters.
	 @return		@c nullptr if the end of string character is reached.
	 @return		A pointer to the first non-delimiting character in the given string.
	 */
	const char *SkipDelimiters(const char *str, const char *delimiters = mage_default_delimiters) noexcept;

	/**
	 Advances to the first delimiting character in the given string.

	 @pre			@a str is not equal to @c nullptr.
	 @pre			@a delimiters is not equal to @c nullptr.
	 @param[in]		str
					A pointer to the null-terminated byte string.
	 @param[in]		delimiters
					A pointer to the null-terminated byte string containing the delimiting characters.
	 @return		@c nullptr if the end of string character is reached.
	 @return		A pointer to the first delimiting character in the given string.
	 */
	char *GotoDelimiters(char *str, const char *delimiters = mage_default_delimiters) noexcept;

	/**
	 Advances to the first delimiting character in the given string.

	 @pre			@a str is not equal to @c nullptr.
	 @pre			@a delimiters is not equal to @c nullptr.
	 @param[in]		str
					A pointer to the null-terminated byte string.
	 @param[in]		delimiters
					A pointer to the null-terminated byte string containing the delimiting characters.
	 @return		@c nullptr if the end of string character is reached.
	 @return		A pointer to the first delimiting character in the given string.
	 */
	const char *GotoDelimiters(const char *str, const char *delimiters = mage_default_delimiters) noexcept;

#pragma endregion
}