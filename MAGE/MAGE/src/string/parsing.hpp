#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "string\string.hpp"
#include "math\math.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Defines
//-----------------------------------------------------------------------------
#pragma region

#define MAGE_DEFAULT_DELIMITERS " \t\n\r"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	enum ParseResult {
		valid_token,
		no_token,
		invalid_token
	};

	//-------------------------------------------------------------------------
	// Conversion Utilities
	//-------------------------------------------------------------------------

	ParseResult StringToBool(const char *str, bool &result);
	ParseResult StringToInt(const char *str, int &result);
	ParseResult StringToUnsignedInt(const char *str, unsigned int &result);
	ParseResult StringToLong(const char *str, long &result);
	ParseResult StringToUnsignedLong(const char *str, unsigned long &result);
	ParseResult StringToFloat(const char *str, float &result);
	ParseResult StringToDouble(const char *str, double &result);

	ParseResult StringPrefixToInt(const char *str, int &result);
	ParseResult StringPrefixToUnsignedInt(const char *str, unsigned int &result);
	ParseResult StringPrefixToLong(const char *str, long &result);
	ParseResult StringPrefixToUnsignedLong(const char *str, unsigned long &result);
	ParseResult StringPrefixToFloat(const char *str, float &result);
	ParseResult StringPrefixToDouble(const char *str, double &result);

	//-------------------------------------------------------------------------
	// Parsing Utilities
	//-------------------------------------------------------------------------

	ParseResult ParseChars(char *str, char **context, char **result, const char *delimiters = MAGE_DEFAULT_DELIMITERS);
	ParseResult ParseString(char *str, char **context, string &result, const char *delimiters = MAGE_DEFAULT_DELIMITERS);
	ParseResult ParseBool(char *str, char **context, bool &result, const char *delimiters = MAGE_DEFAULT_DELIMITERS);
	ParseResult ParseInt(char *str, char **context, int &result, const char *delimiters = MAGE_DEFAULT_DELIMITERS);
	ParseResult ParseUnsignedInt(char *str, char **context, unsigned int &result, const char *delimiters = MAGE_DEFAULT_DELIMITERS);
	ParseResult ParseLong(char *str, char **context, long &result, const char *delimiters = MAGE_DEFAULT_DELIMITERS);
	ParseResult ParseUnsignedLong(char *str, char **context, unsigned long &result, const char *delimiters = MAGE_DEFAULT_DELIMITERS);
	ParseResult ParseFloat(char *str, char **context, float &result, const char *delimiters = MAGE_DEFAULT_DELIMITERS);
	ParseResult ParseDouble(char *str, char **context, double &result, const char *delimiters = MAGE_DEFAULT_DELIMITERS);
	ParseResult ParseFloat2(char *str, char **context, XMFLOAT2 &result, const char *delimiters = MAGE_DEFAULT_DELIMITERS);
	ParseResult ParseFloat3(char *str, char **context, XMFLOAT3 &result, const char *delimiters = MAGE_DEFAULT_DELIMITERS);
	ParseResult ParseFloat4(char *str, char **context, XMFLOAT4 &result, const char *delimiters = MAGE_DEFAULT_DELIMITERS);
}