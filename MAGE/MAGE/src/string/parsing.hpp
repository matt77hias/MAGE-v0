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

	//-------------------------------------------------------------------------
	// Parsing Utilities
	//-------------------------------------------------------------------------

	enum ParseResult {
		valid_token,
		no_token,
		invalid_token
	};

	ParseResult ParseChars(char **result, char **context, char *str = nullptr, const char *delimiters = MAGE_DEFAULT_DELIMITERS);
	ParseResult ParseString(string &result, char **context, char *str = nullptr, const char *delimiters = MAGE_DEFAULT_DELIMITERS);
	ParseResult ParseUnsignedInt(unsigned int &result, char **context, char *str = nullptr, const char *delimiters = MAGE_DEFAULT_DELIMITERS);
	ParseResult ParseInt(int &result, char **context, char *str = nullptr, const char *delimiters = MAGE_DEFAULT_DELIMITERS);
	ParseResult ParseLong(long &result, char **context, char *str = nullptr, const char *delimiters = MAGE_DEFAULT_DELIMITERS);
	ParseResult ParseUnsignedLong(unsigned long &result, char **context, char *str = nullptr, const char *delimiters = MAGE_DEFAULT_DELIMITERS);
	ParseResult ParseFloat(float &result, char **context, char *str = nullptr, const char *delimiters = MAGE_DEFAULT_DELIMITERS);
	ParseResult ParseDouble(double &result, char **context, char *str = nullptr, const char *delimiters = MAGE_DEFAULT_DELIMITERS);
	ParseResult ParseFloat2(XMFLOAT2 &result, char **context, char *str = nullptr, const char *delimiters = MAGE_DEFAULT_DELIMITERS);
	ParseResult ParseFloat3(XMFLOAT3 &result, char **context, char *str = nullptr, const char *delimiters = MAGE_DEFAULT_DELIMITERS);
	ParseResult ParseFloat4(XMFLOAT4 &result, char **context, char *str = nullptr, const char *delimiters = MAGE_DEFAULT_DELIMITERS);

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

	protected:

		const uint32_t GetCurrentLineNumber() const {
			return m_line_number;
		}

		virtual HRESULT Preprocess() = 0;
		virtual HRESULT ParseLine(char *line) = 0;
		virtual HRESULT Postprocess() = 0;
		void ParseLineRemaining();

		char *ParseChars(bool report_error = true);
		string ParseString(const string &default_value = "", bool report_error = true);
		unsigned int ParseUnsignedInt(unsigned int default_value = 0, bool report_error = true);
		int ParseInt(int default_value = 0, bool report_error = true);
		unsigned long ParseUnsignedLong(unsigned long default_value = 0, bool report_error = true);
		long ParseLong(long default_value = 0, bool report_error = true);
		float ParseFloat(float default_value = 0.0f, bool report_error = true);
		double ParseDouble(double default_value = 0.0, bool report_error = true);
		XMFLOAT2 ParseFloat2(XMFLOAT2 default_value = XMFLOAT2(), bool report_error = true);
		XMFLOAT3 ParseFloat3(XMFLOAT3 default_value = XMFLOAT3(), bool report_error = true);
		XMFLOAT4 ParseFloat4(XMFLOAT4 default_value = XMFLOAT4(), bool report_error = true);

		char *m_context;

	private:

		LineParser(const LineParser &parser) = delete;
		LineParser &operator=(const LineParser &parser) = delete;

		wstring m_fname;
		string m_delimiters;
		uint32_t m_line_number;
	};
}