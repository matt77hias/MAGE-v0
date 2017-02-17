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

	enum TokenResult {
		valid_token,
		no_token,
		invalid_token
	};

	//-------------------------------------------------------------------------
	// Conversion Utilities
	//-------------------------------------------------------------------------

	TokenResult StringToBool(const char *str, bool &result);
	TokenResult StringToInt(const char *str, int &result);
	TokenResult StringToUnsignedInt(const char *str, unsigned int &result);
	TokenResult StringToLong(const char *str, long &result);
	TokenResult StringToUnsignedLong(const char *str, unsigned long &result);
	TokenResult StringToLongLong(const char *str, long long &result);
	TokenResult StringToUnsignedLongLong(const char *str, unsigned long long &result);
	TokenResult StringToFloat(const char *str, float &result);
	TokenResult StringToDouble(const char *str, double &result);

	TokenResult StringToBool(const char *begin, const char *end, bool &result);
	TokenResult StringToInt(const char *begin, const char *end, int &result);
	TokenResult StringToUnsignedInt(const char *begin, const char *end, unsigned int &result);
	TokenResult StringToLong(const char *begin, const char *end, long &result);
	TokenResult StringToUnsignedLong(const char *begin, const char *end, unsigned long &result);
	TokenResult StringToLongLong(const char *begin, const char *end, long long &result);
	TokenResult StringToUnsignedLongLong(const char *begin, const char *end, unsigned long long &result);
	TokenResult StringToFloat(const char *begin, const char *end, float &result);
	TokenResult StringToDouble(const char *begin, const char *end, double &result);

	TokenResult StringPrefixToInt(const char *str, int &result);
	TokenResult StringPrefixToUnsignedInt(const char *str, unsigned int &result);
	TokenResult StringPrefixToLong(const char *str, long &result);
	TokenResult StringPrefixToUnsignedLong(const char *str, unsigned long &result);
	TokenResult StringPrefixToLongLong(const char *str, long long &result);
	TokenResult StringPrefixToUnsignedLongLong(const char *str, unsigned long long &result);
	TokenResult StringPrefixToFloat(const char *str, float &result);
	TokenResult StringPrefixToDouble(const char *str, double &result);

	//-------------------------------------------------------------------------
	// Parsing Utilities
	//-------------------------------------------------------------------------

	TokenResult ReadChars(char *str, char **context, char **result, const char *delimiters = MAGE_DEFAULT_DELIMITERS);
	TokenResult ReadString(char *str, char **context, string &result, const char *delimiters = MAGE_DEFAULT_DELIMITERS);
	TokenResult ReadQuotedString(char *str, char **context, string &result, const char *delimiters = MAGE_DEFAULT_DELIMITERS);
	TokenResult ReadBool(char *str, char **context, bool &result, const char *delimiters = MAGE_DEFAULT_DELIMITERS);
	TokenResult ReadInt(char *str, char **context, int &result, const char *delimiters = MAGE_DEFAULT_DELIMITERS);
	TokenResult ReadUnsignedInt(char *str, char **context, unsigned int &result, const char *delimiters = MAGE_DEFAULT_DELIMITERS);
	TokenResult ReadLong(char *str, char **context, long &result, const char *delimiters = MAGE_DEFAULT_DELIMITERS);
	TokenResult ReadUnsignedLong(char *str, char **context, unsigned long &result, const char *delimiters = MAGE_DEFAULT_DELIMITERS);
	TokenResult ReadLongLong(char *str, char **context, long long &result, const char *delimiters = MAGE_DEFAULT_DELIMITERS);
	TokenResult ReadUnsignedLongLong(char *str, char **context, unsigned long long &result, const char *delimiters = MAGE_DEFAULT_DELIMITERS);
	TokenResult ReadFloat(char *str, char **context, float &result, const char *delimiters = MAGE_DEFAULT_DELIMITERS);
	TokenResult ReadDouble(char *str, char **context, double &result, const char *delimiters = MAGE_DEFAULT_DELIMITERS);
	TokenResult ReadFloat2(char *str, char **context, XMFLOAT2 &result, const char *delimiters = MAGE_DEFAULT_DELIMITERS);
	TokenResult ReadFloat3(char *str, char **context, XMFLOAT3 &result, const char *delimiters = MAGE_DEFAULT_DELIMITERS);
	TokenResult ReadFloat4(char *str, char **context, XMFLOAT4 &result, const char *delimiters = MAGE_DEFAULT_DELIMITERS);

	TokenResult HasChars(const char *str, const char *delimiters = MAGE_DEFAULT_DELIMITERS);
	TokenResult HasString(const char *str, const char *delimiters = MAGE_DEFAULT_DELIMITERS);
	TokenResult HasQuotedString(const char *str, const char *delimiters = MAGE_DEFAULT_DELIMITERS);
	TokenResult HasBool(const char *str, const char *delimiters = MAGE_DEFAULT_DELIMITERS);
	TokenResult HasInt(const char *str, const char *delimiters = MAGE_DEFAULT_DELIMITERS);
	TokenResult HasUnsignedInt(const char *str, const char *delimiters = MAGE_DEFAULT_DELIMITERS);
	TokenResult HasLong(const char *str, const char *delimiters = MAGE_DEFAULT_DELIMITERS);
	TokenResult HasUnsignedLong(const char *str, const char *delimiters = MAGE_DEFAULT_DELIMITERS);
	TokenResult HasLongLong(const char *str, const char *delimiters = MAGE_DEFAULT_DELIMITERS);
	TokenResult HasUnsignedLongLong(const char *str, const char *delimiters = MAGE_DEFAULT_DELIMITERS);
	TokenResult HasFloat(const char *str, const char *delimiters = MAGE_DEFAULT_DELIMITERS);
	TokenResult HasDouble(const char *str, const char *delimiters = MAGE_DEFAULT_DELIMITERS);

	char *SkipDelimiters(char *str, const char *delimiters = MAGE_DEFAULT_DELIMITERS);
	const char *SkipDelimiters(const char *str, const char *delimiters = MAGE_DEFAULT_DELIMITERS);
	char *GotoDelimiters(char *str, const char *delimiters = MAGE_DEFAULT_DELIMITERS);
	const char *GotoDelimiters(const char *str, const char *delimiters = MAGE_DEFAULT_DELIMITERS);
}