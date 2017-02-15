#pragma once

//-----------------------------------------------------------------------------
// System Includes
//-----------------------------------------------------------------------------
#pragma region

#include <stdint.h>

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "platform\windows.hpp"
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

	ParseResult StringToInt(const char *str, int &result);
	ParseResult StringToUnsignedInt(const char *str, unsigned int &result);
	ParseResult StringToLong(const char *str, long &result);
	ParseResult StringToUnsignedLong(const char *str, unsigned long &result);
	ParseResult StringToFloat(const char *str, float &result);
	ParseResult StringToDouble(const char *str, double &result);

	//-------------------------------------------------------------------------
	// Parsing Utilities
	//-------------------------------------------------------------------------

	ParseResult ParseChars(char *str, char **context, char **result, const char *delimiters = MAGE_DEFAULT_DELIMITERS);
	ParseResult ParseString(char *str, char **context, string &result, const char *delimiters = MAGE_DEFAULT_DELIMITERS);
	ParseResult ParseInt(char *str, char **context, int &result, const char *delimiters = MAGE_DEFAULT_DELIMITERS);
	ParseResult ParseUnsignedInt(char *str, char **context, unsigned int &result, const char *delimiters = MAGE_DEFAULT_DELIMITERS);
	ParseResult ParseLong(char *str, char **context, long &result, const char *delimiters = MAGE_DEFAULT_DELIMITERS);
	ParseResult ParseUnsignedLong(char *str, char **context, unsigned long &result, const char *delimiters = MAGE_DEFAULT_DELIMITERS);
	ParseResult ParseFloat(char *str, char **context, float &result, const char *delimiters = MAGE_DEFAULT_DELIMITERS);
	ParseResult ParseDouble(char *str, char **context, double &result, const char *delimiters = MAGE_DEFAULT_DELIMITERS);
	ParseResult ParseFloat2(char *str, char **context, XMFLOAT2 &result, const char *delimiters = MAGE_DEFAULT_DELIMITERS);
	ParseResult ParseFloat3(char *str, char **context, XMFLOAT3 &result, const char *delimiters = MAGE_DEFAULT_DELIMITERS);
	ParseResult ParseFloat4(char *str, char **context, XMFLOAT4 &result, const char *delimiters = MAGE_DEFAULT_DELIMITERS);

	//-------------------------------------------------------------------------
	// LineParser
	//-------------------------------------------------------------------------

	class LineParser {

	public:

		LineParser() = default;
		virtual ~LineParser() = default;

		HRESULT ParseFromFile(const wstring &fname, const string &delimiters = MAGE_DEFAULT_DELIMITERS);
		HRESULT ParseFromMemory(const char *input, const string &delimiters = MAGE_DEFAULT_DELIMITERS);

		const wstring &GetFilename() const {
			return m_fname;
		}
		const string &GetDelimiters() const {
			return m_delimiters;
		}

	protected:

		const uint32_t GetCurrentLineNumber() const {
			return m_line_number;
		}

		virtual HRESULT Preprocess();
		virtual HRESULT ParseLine(char *line) = 0;
		virtual HRESULT Postprocess();
		void ParseLineRemaining();

		char *ParseChars();
		string ParseString();
		int ParseInt();
		unsigned int ParseUnsignedInt();
		long ParseLong();
		unsigned long ParseUnsignedLong();
		float ParseFloat();
		double ParseDouble();
		XMFLOAT2 ParseFloat2();
		XMFLOAT3 ParseFloat3();
		XMFLOAT4 ParseFloat4();

		char *ParseOptionalChars(ParseResult *pr = nullptr);
		string ParseOptionalString(const string &default_value = "", ParseResult *pr = nullptr);
		int ParseOptionalInt(int default_value = 0, ParseResult *pr = nullptr);
		unsigned int ParseOptionalUnsignedInt(unsigned int default_value = 0, ParseResult *pr = nullptr);
		long ParseOptionalLong(long default_value = 0, ParseResult *pr = nullptr);
		unsigned long ParseOptionalUnsignedLong(unsigned long default_value = 0, ParseResult *pr = nullptr);
		float ParseOptionalFloat(float default_value = 0.0f, ParseResult *pr = nullptr);
		double ParseOptionalDouble(double default_value = 0.0, ParseResult *pr = nullptr);
		XMFLOAT2 ParseOptionalFloat2(XMFLOAT2 default_value = XMFLOAT2(), ParseResult *pr = nullptr);
		XMFLOAT3 ParseOptionalFloat3(XMFLOAT3 default_value = XMFLOAT3(), ParseResult *pr = nullptr);
		XMFLOAT4 ParseOptionalFloat4(XMFLOAT4 default_value = XMFLOAT4(), ParseResult *pr = nullptr);

		char *m_context;

	private:

		LineParser(const LineParser &parser) = delete;
		LineParser &operator=(const LineParser &parser) = delete;

		wstring m_fname;
		string m_delimiters;
		uint32_t m_line_number;
	};
}