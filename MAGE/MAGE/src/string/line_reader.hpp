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
#include "string\parsing.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	class LineReader {

	public:

		LineReader() : m_context(nullptr) {}
		virtual ~LineReader() = default;

		HRESULT ReadFromFile(const wstring &fname, const string &delimiters = MAGE_DEFAULT_DELIMITERS);
		HRESULT ReadFromMemory(const char *input, const string &delimiters = MAGE_DEFAULT_DELIMITERS);

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
		string ParseQuotedString();
		bool ParseBool();
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
		string ParseOptionalQuotedString(const string &default_value = "", ParseResult *pr = nullptr);
		bool ParseOptionalBool(bool default_value = false, ParseResult *pr = nullptr);
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

		LineReader(const LineReader &parser) = delete;
		LineReader &operator=(const LineReader &parser) = delete;

		wstring m_fname;
		string m_delimiters;
		uint32_t m_line_number;
	};
}