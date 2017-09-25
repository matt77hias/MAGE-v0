#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "memory\types.hpp"
#include "math\math.hpp"

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
	 @c Valid, 
	 @c None and 
	 @c Invalid.
	 */
	enum struct TokenResult {
		Valid,	// The parsed token is valid (matches the expected token type).
		None,	// No token can be parsed (independent of the token type).
		Invalid	// The parsed token is invalid (matches the expected token type).
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
	 Converts the given string to a @c i8.

	 @param[in]		str
					A pointer to the null-terminated byte string to convert.
	 @param[out]	result
					A reference to the @c i8 represented by the string @a str.
	 @return		A token result indicating whether the conversion
					of the given string @a str to a @c i8 succeeded or not.
	 */
	TokenResult StringToI8(const char *str, i8 &result) noexcept;

	/**
	 Converts the given string to a @c u8.

	 @param[in]		str
					A pointer to the null-terminated byte string to convert.
	 @param[out]	result
					A reference to the @c u8 represented by the string @a str.
	 @return		A token result indicating whether the conversion
					of the given string @a str to a @c u8 succeeded or not.
	 */
	TokenResult StringToU8(const char *str, u8 &result) noexcept;

	/**
	 Converts the given string to a @c i16.

	 @param[in]		str
					A pointer to the null-terminated byte string to convert.
	 @param[out]	result
					A reference to the @c i16 represented by the string @a str.
	 @return		A token result indicating whether the conversion
					of the given string @a str to a @c i16 succeeded or not.
	 */
	TokenResult StringToI16(const char *str, i16 &result) noexcept;

	/**
	 Converts the given string to a @c u16.

	 @param[in]		str
					A pointer to the null-terminated byte string to convert.
	 @param[out]	result
					A reference to the @c u16 represented by the string @a str.
	 @return		A token result indicating whether the conversion
					of the given string @a str to a @c u16 succeeded or not.
	 */
	TokenResult StringToU16(const char *str, u16 &result) noexcept;

	/**
	 Converts the given string to a @c i32.

	 @param[in]		str
					A pointer to the null-terminated byte string to convert.
	 @param[out]	result
					A reference to the @c i32 represented by the string @a str.
	 @return		A token result indicating whether the conversion
					of the given string @a str to a @c i32 succeeded or not.
	 */
	TokenResult StringToI32(const char *str, i32 &result) noexcept;

	/**
	 Converts the given string to a @c u32.

	 @param[in]		str
					A pointer to the null-terminated byte string to convert.
	 @param[out]	result
					A reference to the @c u32 represented by the string @a str.
	 @return		A token result indicating whether the conversion
					of the given string @a str to a @c u32 succeeded or not.
	 */
	TokenResult StringToU32(const char *str, u32 &result) noexcept;

	/**
	 Converts the given string to a @c i64.

	 @param[in]		str
					A pointer to the null-terminated byte string to convert.
	 @param[out]	result
					A reference to the @c i64 represented by the string @a str.
	 @return		A token result indicating whether the conversion
					of the given string @a str to a @c i64 succeeded or not.
	 */
	TokenResult StringToI64(const char *str, i64 &result) noexcept;

	/**
	 Converts the given string to a @c u64.

	 @param[in]		str
					A pointer to the null-terminated byte string to convert.
	 @param[out]	result
					A reference to the @c u64 represented by the string @a str.
	 @return		A token result indicating whether the conversion
					of the given string @a str to a @c u64 succeeded or not.
	 */
	TokenResult StringToU64(const char *str, u64 &result) noexcept;

	/**
	 Converts the given string to a @c float.

	 @param[in]		str
					A pointer to the null-terminated byte string to convert.
	 @param[out]	result
					A reference to the @c float represented by the string @a str.
	 @return		A token result indicating whether the conversion
					of the given string @a str to a @c float succeeded or not.
	 */
	TokenResult StringToF32(const char *str, float &result) noexcept;

	/**
	 Converts the given string to a @c f64.

	 @param[in]		str
					A pointer to the null-terminated byte string to convert.
	 @param[out]	result
					A reference to the @c f64 represented by the string @a str.
	 @return		A token result indicating whether the conversion
					of the given string @a str to a @c f64 succeeded or not.
	 */
	TokenResult StringToF64(const char *str, f64 &result) noexcept;

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
	 Converts the given string to a @c i8.

	 @pre			@a end is not equal to @c nullptr 
					if @a begin is not equal to @c nullptr.
	 @param[in]		begin
					A pointer to the begin (inclusive) of the string to convert.
	 @param[in]		end
					A pointer to the end (exclusive) of the string to convert.
	 @param[out]	result
					A reference to the @c i8 represented by the string @a str.
	 @return		A token result indicating whether the conversion
					of the given string @a str to a @c i8 succeeded or not.
	 */
	TokenResult StringToI8(const char *begin, const char *end, i8 &result) noexcept;
	
	/**
	 Converts the given string to a @c u8.

	 @pre			@a end is not equal to @c nullptr 
					if @a begin is not equal to @c nullptr.
	 @param[in]		begin
					A pointer to the begin (inclusive) of the string to convert.
	 @param[in]		end
					A pointer to the end (exclusive) of the string to convert.
	 @param[out]	result
					A reference to the @c u8 represented by the string @a str.
	 @return		A token result indicating whether the conversion
					of the given string @a str to a @c u8 succeeded or not.
	 */
	TokenResult StringToU8(const char *begin, const char *end, u8 &result) noexcept;
	
	/**
	 Converts the given string to a @c i16.

	 @pre			@a end is not equal to @c nullptr 
					if @a begin is not equal to @c nullptr.
	 @param[in]		begin
					A pointer to the begin (inclusive) of the string to convert.
	 @param[in]		end
					A pointer to the end (exclusive) of the string to convert.
	 @param[out]	result
					A reference to the @c i16 represented by the string @a str.
	 @return		A token result indicating whether the conversion
					of the given string @a str to a @c i16 succeeded or not.
	 */
	TokenResult StringToI16(const char *begin, const char *end, i16 &result) noexcept;
	
	/**
	 Converts the given string to a @c u16.

	 @pre			@a end is not equal to @c nullptr 
					if @a begin is not equal to @c nullptr.
	 @param[in]		begin
					A pointer to the begin (inclusive) of the string to convert.
	 @param[in]		end
					A pointer to the end (exclusive) of the string to convert.
	 @param[out]	result
					A reference to the @c u16 represented by the string @a str.
	 @return		A token result indicating whether the conversion
					of the given string @a str to a @c u16 succeeded or not.
	 */
	TokenResult StringToU16(const char *begin, const char *end, u16 &result) noexcept;
	
	/**
	 Converts the given string to a @c i32.

	 @pre			@a end is not equal to @c nullptr 
					if @a begin is not equal to @c nullptr.
	 @param[in]		begin
					A pointer to the begin (inclusive) of the string to convert.
	 @param[in]		end
					A pointer to the end (exclusive) of the string to convert.
	 @param[out]	result
					A reference to the @c i32 represented by the string @a str.
	 @return		A token result indicating whether the conversion
					of the given string @a str to a @c i32 succeeded or not.
	 */
	TokenResult StringToI32(const char *begin, const char *end, i32 &result) noexcept;
	
	/**
	 Converts the given string to a @c u32.

	 @pre			@a end is not equal to @c nullptr 
					if @a begin is not equal to @c nullptr.
	 @param[in]		begin
					A pointer to the begin (inclusive) of the string to convert.
	 @param[in]		end
					A pointer to the end (exclusive) of the string to convert.
	 @param[out]	result
					A reference to the @c u32 represented by the string @a str.
	 @return		A token result indicating whether the conversion
					of the given string @a str to a @c u32 succeeded or not.
	 */
	TokenResult StringToU32(const char *begin, const char *end, u32 &result) noexcept;
	
	/**
	 Converts the given string to a @c i64.

	 @pre			@a end is not equal to @c nullptr 
					if @a begin is not equal to @c nullptr.
	 @param[in]		begin
					A pointer to the begin (inclusive) of the string to convert.
	 @param[in]		end
					A pointer to the end (exclusive) of the string to convert.
	 @param[out]	result
					A reference to the @c i64 represented by the string @a str.
	 @return		A token result indicating whether the conversion
					of the given string @a str to a @c i64 succeeded or not.
	 */
	TokenResult StringToI64(const char *begin, const char *end, i64 &result) noexcept;
	
	/**
	 Converts the given string to a @c u64.

	 @pre			@a end is not equal to @c nullptr 
					if @a begin is not equal to @c nullptr.
	 @param[in]		begin
					A pointer to the begin (inclusive) of the string to convert.
	 @param[in]		end
					A pointer to the end (exclusive) of the string to convert.
	 @param[out]	result
					A reference to the @c u64 represented by the string @a str.
	 @return		A token result indicating whether the conversion
					of the given string @a str to a @c u64 succeeded or not.
	 */
	TokenResult StringToU64(const char *begin, const char *end, u64 &result) noexcept;
	
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
	TokenResult StringToF32(const char *begin, const char *end, float &result) noexcept;
	
	/**
	 Converts the given string to a @c f64.

	 @pre			@a end is not equal to @c nullptr 
					if @a begin is not equal to @c nullptr.
	 @param[in]		begin
					A pointer to the begin (inclusive) of the string to convert.
	 @param[in]		end
					A pointer to the end (exclusive) of the string to convert.
	 @param[out]	result
					A reference to the @c f64 represented by the string @a str.
	 @return		A token result indicating whether the conversion
					of the given string @a str to a @c f64 succeeded or not.
	 */
	TokenResult StringToF64(const char *begin, const char *end, f64 &result) noexcept;

#pragma endregion

	//-------------------------------------------------------------------------
	// String Conversion Utilities: String Prefix
	//-------------------------------------------------------------------------
#pragma region

	/**
	 Converts the prefix of the given string @a str to a @c i8.

	 @param[in]		str
					A pointer to the null-terminated byte string to convert.
	 @param[out]	result
					A reference to the @c i8 represented by the prefix of the given string @a str.
	 @return		A token result indicating whether the conversion of the prefix 
					of the given string @a str to a @c i8 succeeded or not.
	 */
	TokenResult StringPrefixToI8(const char *str, i8 &result) noexcept;

	/**
	 Converts the prefix of the given string @a str to a @c u8.

	 @param[in]		str
					A pointer to the null-terminated byte string to convert.
	 @param[out]	result
					A reference to the @c u8 represented by the prefix of the given string @a str.
	 @return		A token result indicating whether the conversion of the prefix 
					of the given string @a str to a @c u8 succeeded or not.
	 */
	TokenResult StringPrefixToU8(const char *str, u8 &result) noexcept;

	/**
	 Converts the prefix of the given string @a str to a @c i16.

	 @param[in]		str
					A pointer to the null-terminated byte string to convert.
	 @param[out]	result
					A reference to the @c i16 represented by the prefix of the given string @a str.
	 @return		A token result indicating whether the conversion of the prefix 
					of the given string @a str to a @c i16 succeeded or not.
	 */
	TokenResult StringPrefixToI16(const char *str, i16 &result) noexcept;

	/**
	 Converts the prefix of the given string @a str to a @c u16.

	 @param[in]		str
					A pointer to the null-terminated byte string to convert.
	 @param[out]	result
					A reference to the @c u16 represented by the prefix of the given string @a str.
	 @return		A token result indicating whether the conversion of the prefix 
					of the given string @a str to a @c u16 succeeded or not.
	 */
	TokenResult StringPrefixToU16(const char *str, u16 &result) noexcept;

	/**
	 Converts the prefix of the given string @a str to a @c i32.

	 @param[in]		str
					A pointer to the null-terminated byte string to convert.
	 @param[out]	result
					A reference to the @c i32 represented by the prefix of the given string @a str.
	 @return		A token result indicating whether the conversion of the prefix 
					of the given string @a str to a @c i32 succeeded or not.
	 */
	TokenResult StringPrefixToI32(const char *str, i32 &result) noexcept;

	/**
	 Converts the prefix of the given string @a str to a @c u32.

	 @param[in]		str
					A pointer to the null-terminated byte string to convert.
	 @param[out]	result
					A reference to the @c u32 represented by the prefix of the given string @a str.
	 @return		A token result indicating whether the conversion of the prefix 
					of the given string @a str to a @c u32 succeeded or not.
	 */
	TokenResult StringPrefixToU32(const char *str, u32 &result) noexcept;

	/**
	 Converts the prefix of the given string @a str to a @c i64.

	 @param[in]		str
					A pointer to the null-terminated byte string to convert.
	 @param[out]	result
					A reference to the @c i64 represented by the prefix of the given string @a str.
	 @return		A token result indicating whether the conversion of the prefix 
					of the given string @a str to a @c i64 succeeded or not.
	 */
	TokenResult StringPrefixToI64(const char *str, i64 &result) noexcept;

	/**
	 Converts the prefix of the given string @a str to a @c u64.

	 @param[in]		str
					A pointer to the null-terminated byte string to convert.
	 @param[out]	result
					A reference to the @c u64 represented by the prefix of the given string @a str.
	 @return		A token result indicating whether the conversion of the prefix 
					of the given string @a str to a @c u64 succeeded or not.
	 */
	TokenResult StringPrefixToU64(const char *str, u64 &result) noexcept;

	/**
	 Converts the prefix of the given string @a str to a @c float.

	 @param[in]		str
					A pointer to the null-terminated byte string to convert.
	 @param[out]	result
					A reference to the @c float represented by the prefix of the given string @a str.
	 @return		A token result indicating whether the conversion of the prefix 
					of the given string @a str to a @c float succeeded or not.
	 */
	TokenResult StringPrefixToF32(const char *str, float &result) noexcept;

	/**
	 Converts the prefix of the given string @a str to a @c f64.

	 @param[in]		str
					A pointer to the null-terminated byte string to convert.
	 @param[out]	result
					A reference to the @c f64 represented by the prefix of the given string @a str.
	 @return		A token result indicating whether the conversion of the prefix 
					of the given string @a str to a @c f64 succeeded or not.
	 */
	TokenResult StringPrefixToF64(const char *str, f64 &result) noexcept;

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
	 Reads and converts the next token in the given string to a @c i8.

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
					A reference to the @c i8 represented by the next token in the given string @a str.
	 @param[in]		delimiters
					A pointer to the null-terminated byte string containing the delimiting characters.
	 @return		A token result indicating whether the conversion
					of the next token in the given string to a @c i8 succeeded or not.
	 */
	TokenResult ReadI8(char *str, char **context, i8 &result, const char *delimiters = mage_default_delimiters) noexcept;
	
	/**
	 Reads and converts the next token in the given string to a @c u8.

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
					A reference to the @c u8 represented by the next token in the given string @a str.
	 @param[in]		delimiters
					A pointer to the null-terminated byte string containing the delimiting characters.
	 @return		A token result indicating whether the conversion
					of the next token in the given string to a @c u8 succeeded or not.
	 */
	TokenResult ReadU8(char *str, char **context, u8 &result, const char *delimiters = mage_default_delimiters) noexcept;
	
	/**
	 Reads and converts the next token in the given string to a @c i16.

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
					A reference to the @c i16 represented by the next token in the given string @a str.
	 @param[in]		delimiters
					A pointer to the null-terminated byte string containing the delimiting characters.
	 @return		A token result indicating whether the conversion
					of the next token in the given string to a @c i16 succeeded or not.
	 */
	TokenResult ReadI16(char *str, char **context, i16 &result, const char *delimiters = mage_default_delimiters) noexcept;
	
	/**
	 Reads and converts the next token in the given string to a @c u16.

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
					A reference to the @c u16 represented by the next token in the given string @a str.
	 @param[in]		delimiters
					A pointer to the null-terminated byte string containing the delimiting characters.
	 @return		A token result indicating whether the conversion
					of the next token in the given string to a @c u16 succeeded or not.
	 */
	TokenResult ReadU16(char *str, char **context, u16 &result, const char *delimiters = mage_default_delimiters) noexcept;
	
	/**
	 Reads and converts the next token in the given string to a @c i32.

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
					A reference to the @c i32 represented by the next token in the given string @a str.
	 @param[in]		delimiters
					A pointer to the null-terminated byte string containing the delimiting characters.
	 @return		A token result indicating whether the conversion
					of the next token in the given string to a @c i32 succeeded or not.
	 */
	TokenResult ReadI32(char *str, char **context, i32 &result, const char *delimiters = mage_default_delimiters) noexcept;
	
	/**
	 Reads and converts the next token in the given string to a @c u32.

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
					A reference to the @c u32 represented by the next token in the given string @a str.
	 @param[in]		delimiters
					A pointer to the null-terminated byte string containing the delimiting characters.
	 @return		A token result indicating whether the conversion
					of the next token in the given string to a @c u32 succeeded or not.
	 */
	TokenResult ReadU32(char *str, char **context, u32 &result, const char *delimiters = mage_default_delimiters) noexcept;
	
	/**
	 Reads and converts the next token in the given string to a @c i64.

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
					A reference to the @c i64 represented by the next token in the given string @a str.
	 @param[in]		delimiters
					A pointer to the null-terminated byte string containing the delimiting characters.
	 @return		A token result indicating whether the conversion
					of the next token in the given string to a @c i64 succeeded or not.
	 */
	TokenResult ReadI64(char *str, char **context, i64 &result, const char *delimiters = mage_default_delimiters) noexcept;
	
	/**
	 Reads and converts the next token in the given string to a @c u64.

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
					A reference to the @c u64 represented by the next token in the given string @a str.
	 @param[in]		delimiters
					A pointer to the null-terminated byte string containing the delimiting characters.
	 @return		A token result indicating whether the conversion
					of the next token in the given string to a @c u64 succeeded or not.
	 */
	TokenResult ReadU64(char *str, char **context, u64 &result, const char *delimiters = mage_default_delimiters) noexcept;
	
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
	 Reads and converts the next token in the given string to a @c f64.

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
					A reference to the @c f64 represented by the next token in the given string @a str.
	 @param[in]		delimiters
					A pointer to the null-terminated byte string containing the delimiting characters.
	 @return		A token result indicating whether the conversion
					of the next token in the given string to a @c f64 succeeded or not.
	 */
	TokenResult ReadDouble(char *str, char **context, f64 &result, const char *delimiters = mage_default_delimiters) noexcept;
	
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
					of the next token in the given string to a @c u32 succeeds or not.
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
	 Checks whether the next token in the given string represents a @c u8.

	 @pre			@a str is not equal to @c nullptr.
	 @pre			@a delimiters is not equal to @c nullptr.
	 @param[in]		str
					A pointer to the null-terminated byte string.
	 @param[in]		delimiters
					A pointer to the null-terminated byte string containing the delimiting characters.
	 @return		A token result indicating whether the conversion
					of the next token in the given string to a @c i8 succeeds or not.
	 */
	TokenResult HasI8(const char *str, const char *delimiters = mage_default_delimiters) noexcept;

	/**
	 Checks whether the next token in the given string represents a @c u8.

	 @pre			@a str is not equal to @c nullptr.
	 @pre			@a delimiters is not equal to @c nullptr.
	 @param[in]		str
					A pointer to the null-terminated byte string.
	 @param[in]		delimiters
					A pointer to the null-terminated byte string containing the delimiting characters.
	 @return		A token result indicating whether the conversion
					of the next token in the given string to a @c u8 succeeds or not.
	 */
	TokenResult HasU8(const char *str, const char *delimiters = mage_default_delimiters) noexcept;

	/**
	 Checks whether the next token in the given string represents a @c i16.

	 @pre			@a str is not equal to @c nullptr.
	 @pre			@a delimiters is not equal to @c nullptr.
	 @param[in]		str
					A pointer to the null-terminated byte string.
	 @param[in]		delimiters
					A pointer to the null-terminated byte string containing the delimiting characters.
	 @return		A token result indicating whether the conversion
					of the next token in the given string to a @c i16 succeeds or not.
	 */
	TokenResult HasI16(const char *str, const char *delimiters = mage_default_delimiters) noexcept;

	/**
	 Checks whether the next token in the given string represents a @c u16.

	 @pre			@a str is not equal to @c nullptr.
	 @pre			@a delimiters is not equal to @c nullptr.
	 @param[in]		str
					A pointer to the null-terminated byte string.
	 @param[in]		delimiters
					A pointer to the null-terminated byte string containing the delimiting characters.
	 @return		A token result indicating whether the conversion
					of the next token in the given string to a @c u16 succeeds or not.
	 */
	TokenResult HasU16(const char *str, const char *delimiters = mage_default_delimiters) noexcept;

	/**
	 Checks whether the next token in the given string represents a @c i32.

	 @pre			@a str is not equal to @c nullptr.
	 @pre			@a delimiters is not equal to @c nullptr.
	 @param[in]		str
					A pointer to the null-terminated byte string.
	 @param[in]		delimiters
					A pointer to the null-terminated byte string containing the delimiting characters.
	 @return		A token result indicating whether the conversion
					of the next token in the given string to a @c i32 succeeds or not.
	 */
	TokenResult HasI32(const char *str, const char *delimiters = mage_default_delimiters) noexcept;

	/**
	 Checks whether the next token in the given string represents a @c u32 .

	 @pre			@a str is not equal to @c nullptr.
	 @pre			@a delimiters is not equal to @c nullptr.
	 @param[in]		str
					A pointer to the null-terminated byte string.
	 @param[in]		delimiters
					A pointer to the null-terminated byte string containing the delimiting characters.
	 @return		A token result indicating whether the conversion
					of the next token in the given string to a @c u32 succeeds or not.
	 */
	TokenResult HasU32(const char *str, const char *delimiters = mage_default_delimiters) noexcept;

	/**
	 Checks whether the next token in the given string represents a @c i64.

	 @pre			@a str is not equal to @c nullptr.
	 @pre			@a delimiters is not equal to @c nullptr.
	 @param[in]		str
					A pointer to the null-terminated byte string.
	 @param[in]		delimiters
					A pointer to the null-terminated byte string containing the delimiting characters.
	 @return		A token result indicating whether the conversion
					of the next token in the given string to a @c i64 succeeds or not.
	 */
	TokenResult HasI64(const char *str, const char *delimiters = mage_default_delimiters) noexcept;

	/**
	 Checks whether the next token in the given string represents a @c u64.

	 @pre			@a str is not equal to @c nullptr.
	 @pre			@a delimiters is not equal to @c nullptr.
	 @param[in]		str
					A pointer to the null-terminated byte string.
	 @param[in]		delimiters
					A pointer to the null-terminated byte string containing the delimiting characters.
	 @return		A token result indicating whether the conversion
					of the next token in the given string to a @c u64 succeeds or not.
	 */
	TokenResult HasU64(const char *str, const char *delimiters = mage_default_delimiters) noexcept;

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
	TokenResult HasF32(const char *str, const char *delimiters = mage_default_delimiters) noexcept;

	/**
	 Checks whether the next token in the given string represents a @c f64.

	 @pre			@a str is not equal to @c nullptr.
	 @pre			@a delimiters is not equal to @c nullptr.
	 @param[in]		str
					A pointer to the null-terminated byte string.
	 @param[in]		delimiters
					A pointer to the null-terminated byte string containing the delimiting characters.
	 @return		A token result indicating whether the conversion
					of the next token in the given string to a @c f64 succeeds or not.
	 */
	TokenResult HasF64(const char *str, const char *delimiters = mage_default_delimiters) noexcept;

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