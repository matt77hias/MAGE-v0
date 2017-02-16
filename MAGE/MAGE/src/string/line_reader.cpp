//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "string\line_reader.hpp"
#include "string\string_utils.hpp"
#include "logging\error.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	HRESULT LineReader::ReadFromFile(const wstring &fname, const string &delimiters) {
		m_fname = fname;
		m_delimiters = delimiters;

		// Open the file.
		FILE *file = nullptr;
		const errno_t result_fopen_s = _wfopen_s(&file, GetFilename().c_str(), L"r");
		if (result_fopen_s) {
			Error("%ls: could not open file.", GetFilename().c_str());
			return E_FAIL;
		}

		const HRESULT result_preprocess = Preprocess();
		if (FAILED(result_preprocess)) {
			Error("%ls: preprocessing failed.", GetFilename().c_str());

			// Close the file.
			fclose(file);

			return result_preprocess;
		}

		char current_line[MAX_PATH];
		m_line_number = 1;
		// Continue reading from the file until the eof is reached.
		while (fgets(current_line, _countof(current_line), file)) {

			const HRESULT result_line = ParseLine(current_line);
			if (FAILED(result_line)) {
				Error("%ls: line %u: parsing failed.", GetFilename().c_str(), GetCurrentLineNumber());

				// Close the file.
				fclose(file);

				return result_line;
			}

			++m_line_number;
		}

		const HRESULT result_postprocess = Postprocess();
		if (FAILED(result_postprocess)) {
			Error("%ls: postprocessing failed.", GetFilename().c_str());

			// Close the file.
			fclose(file);

			return result_postprocess;
		}

		// Close the file.
		fclose(file);

		m_context = nullptr;

		return S_OK;
	}

	HRESULT LineReader::ReadFromMemory(const char *input, const string &delimiters) {
		m_fname = L"input string";
		m_delimiters = delimiters;

		const HRESULT result_preprocess = Preprocess();
		if (FAILED(result_preprocess)) {
			Error("%ls: preprocessing failed.", GetFilename().c_str());
			return result_preprocess;
		}

		char current_line[MAX_PATH];
		m_line_number = 1;
		// Continue reading from the file until the eof is reached.
		while (str_gets(current_line, _countof(current_line), &input)) {

			const HRESULT result_line = ParseLine(current_line);
			if (FAILED(result_line)) {
				Error("%ls: line %u: parsing failed.", GetFilename().c_str(), GetCurrentLineNumber());
				return result_line;
			}

			++m_line_number;
		}

		const HRESULT result_postprocess = Postprocess();
		if (FAILED(result_postprocess)) {
			Error("%ls: postprocessing failed.", GetFilename().c_str());
			return result_postprocess;
		}

		m_context = nullptr;

		return S_OK;
	}

	HRESULT LineReader::Preprocess() {
		return S_OK;
	}

	HRESULT LineReader::Postprocess() {
		return S_OK;
	}

	void LineReader::ParseLineRemaining() {
		char *next_token = strtok_s(nullptr, GetDelimiters().c_str(), &m_context);
		while (next_token) {
			Warning("%ls: line %u: unused token: %s.", GetFilename().c_str(), GetCurrentLineNumber(), next_token);
			next_token = strtok_s(nullptr, GetDelimiters().c_str(), &m_context);
		}
	}

	char *LineReader::ParseChars() {
		char *result;
		const ParseResult parse_result = mage::ParseChars(nullptr, &m_context, &result, GetDelimiters().c_str());

		switch (parse_result) {
		case valid_token: {
			return result;
		}
		default: {
			Error("%ls: line %u: no char string value found.", GetFilename().c_str(), GetCurrentLineNumber());
			return "";
		}
		}
	}

	string LineReader::ParseString() {
		string result;
		const ParseResult parse_result = mage::ParseString(nullptr, &m_context, result, GetDelimiters().c_str());

		switch (parse_result) {
		case valid_token: {
			return result;
		}
		default: {
			Error("%ls: line %u: no string value found.", GetFilename().c_str(), GetCurrentLineNumber());
			return "";
		}
		}
	}

	string LineReader::ParseQuotedString() {
		const char *first_quote = strchr(m_context, '"');
		char *last_quote = strrchr(m_context + 1, '"');

		if (!first_quote || !last_quote) {
			Error("%ls: line %u: no quoted string value found.", GetFilename().c_str(), GetCurrentLineNumber());
			return "";
		}

		m_context = last_quote + 1;
		*m_context = '\0';
		++m_context;

		return first_quote;
	}

	bool LineReader::ParseBool() {
		bool result;
		const ParseResult parse_result = mage::ParseBool(nullptr, &m_context, result, GetDelimiters().c_str());

		switch (parse_result) {
		case valid_token: {
			return result;
		}
		case no_token: {
			Error("%ls: line %u: no bool value found.", GetFilename().c_str(), GetCurrentLineNumber());
			return false;
		}
		default: {
			Error("%ls: line %u: invalid bool value found.", GetFilename().c_str(), GetCurrentLineNumber());
			return false;
		}
		}
	}

	int LineReader::ParseInt() {
		int result;
		const ParseResult parse_result = mage::ParseInt(nullptr, &m_context, result, GetDelimiters().c_str());

		switch (parse_result) {
		case valid_token: {
			return result;
		}
		case no_token: {
			Error("%ls: line %u: no int value found.", GetFilename().c_str(), GetCurrentLineNumber());
			return 0;
		}
		default: {
			Error("%ls: line %u: invalid int value found.", GetFilename().c_str(), GetCurrentLineNumber());
			return 0;
		}
		}
	}

	unsigned int LineReader::ParseUnsignedInt() {
		unsigned int result;
		const ParseResult parse_result = mage::ParseUnsignedInt(nullptr, &m_context, result, GetDelimiters().c_str());

		switch (parse_result) {
		case valid_token: {
			return result;
		}
		case no_token: {
			Error("%ls: line %u: no unsigned int value found.", GetFilename().c_str(), GetCurrentLineNumber());
			return 0;
		}
		default: {
			Error("%ls: line %u: invalid unsigned int value found.", GetFilename().c_str(), GetCurrentLineNumber());
			return 0;
		}
		}
	}

	long LineReader::ParseLong() {
		long result;
		const ParseResult parse_result = mage::ParseLong(nullptr, &m_context, result, GetDelimiters().c_str());

		switch (parse_result) {
		case valid_token: {
			return result;
		}
		case no_token: {
			Error("%ls: line %u: no long value found.", GetFilename().c_str(), GetCurrentLineNumber());
			return 0;
		}
		default: {
			Error("%ls: line %u: invalid long value found.", GetFilename().c_str(), GetCurrentLineNumber());
			return 0;
		}
		}
	}

	unsigned long LineReader::ParseUnsignedLong() {
		unsigned long result;
		const ParseResult parse_result = mage::ParseUnsignedLong(nullptr, &m_context, result, GetDelimiters().c_str());

		switch (parse_result) {
		case valid_token: {
			return result;
		}
		case no_token: {
			Error("%ls: line %u: no unsigned long value found.", GetFilename().c_str(), GetCurrentLineNumber());
			return 0;
		}
		default: {
			Error("%ls: line %u: invalid unsigned long value found.", GetFilename().c_str(), GetCurrentLineNumber());
			return 0;
		}
		}
	}

	float LineReader::ParseFloat() {
		float result;
		const ParseResult parse_result = mage::ParseFloat(nullptr, &m_context, result, GetDelimiters().c_str());

		switch (parse_result) {
		case valid_token: {
			return result;
		}
		case no_token: {
			Error("%ls: line %u: no float value found.", GetFilename().c_str(), GetCurrentLineNumber());
			return 0.0f;
		}
		default: {
			Error("%ls: line %u: invalid float value found.", GetFilename().c_str(), GetCurrentLineNumber());
			return 0.0f;
		}
		}
	}

	double LineReader::ParseDouble() {
		double result;
		const ParseResult parse_result = mage::ParseDouble(nullptr, &m_context, result, GetDelimiters().c_str());

		switch (parse_result) {
		case valid_token: {
			return result;
		}
		case no_token: {
			Error("%ls: line %u: no double value found.", GetFilename().c_str(), GetCurrentLineNumber());
			return 0.0;
		}
		default: {
			Error("%ls: line %u: invalid double value found.", GetFilename().c_str(), GetCurrentLineNumber());
			return 0.0;
		}
		}
	}

	XMFLOAT2 LineReader::ParseFloat2() {
		XMFLOAT2 result;
		const ParseResult parse_result = mage::ParseFloat2(nullptr, &m_context, result, GetDelimiters().c_str());

		switch (parse_result) {
		case valid_token: {
			return result;
		}
		case no_token: {
			Error("%ls: line %u: no float2 value found.", GetFilename().c_str(), GetCurrentLineNumber());
			return XMFLOAT2();
		}
		default: {
			Error("%ls: line %u: invalid float2 value found.", GetFilename().c_str(), GetCurrentLineNumber());
			return XMFLOAT2();
		}
		}
	}

	XMFLOAT3 LineReader::ParseFloat3() {
		XMFLOAT3 result;
		const ParseResult parse_result = mage::ParseFloat3(nullptr, &m_context, result, GetDelimiters().c_str());

		switch (parse_result) {
		case valid_token: {
			return result;
		}
		case no_token: {
			Error("%ls: line %u: no float3 value found.", GetFilename().c_str(), GetCurrentLineNumber());
			return XMFLOAT3();
		}
		default: {
			Error("%ls: line %u: invalid float3 value found.", GetFilename().c_str(), GetCurrentLineNumber());
			return XMFLOAT3();
		}
		}
	}

	XMFLOAT4 LineReader::ParseFloat4() {
		XMFLOAT4 result;
		const ParseResult parse_result = mage::ParseFloat4(nullptr, &m_context, result, GetDelimiters().c_str());

		switch (parse_result) {
		case valid_token: {
			return result;
		}
		case no_token: {
			Error("%ls: line %u: no float4 value found.", GetFilename().c_str(), GetCurrentLineNumber());
			return XMFLOAT4();
		}
		default: {
			Error("%ls: line %u: invalid float4 value found.", GetFilename().c_str(), GetCurrentLineNumber());
			return XMFLOAT4();
		}
		}
	}

	char *LineReader::ParseOptionalChars(ParseResult *pr) {
		char *result;
		const ParseResult parse_result = mage::ParseChars(nullptr, &m_context, &result, GetDelimiters().c_str());

		if (pr) {
			*pr = parse_result;
		}

		switch (parse_result) {
		case valid_token: {
			return result;
		}
		default: {
			return "";
		}
		}
	}

	string LineReader::ParseOptionalString(const string &default_value, ParseResult *pr) {
		string result;
		const ParseResult parse_result = mage::ParseString(nullptr, &m_context, result, GetDelimiters().c_str());

		if (pr) {
			*pr = parse_result;
		}

		switch (parse_result) {
		case valid_token: {
			return result;
		}
		default: {
			return default_value;
		}
		}
	}

	string LineReader::ParseOptionalQuotedString(const string &default_value, ParseResult *pr) {
		const char *first_quote = strchr(m_context, '"');
		char *last_quote = strrchr(m_context + 1, '"');

		if (!first_quote || !last_quote) {

			if (pr) {
				*pr = invalid_token;
			}

			Error("%ls: line %u: no quoted string value found.", GetFilename().c_str(), GetCurrentLineNumber());
			return default_value;
		}

		if (pr) {
			*pr = valid_token;
		}

		m_context = last_quote + 1;
		*m_context = '\0';
		++m_context;

		return first_quote;
	}

	bool LineReader::ParseOptionalBool(bool default_value, ParseResult *pr) {
		bool result;
		const ParseResult parse_result = mage::ParseBool(nullptr, &m_context, result, GetDelimiters().c_str());

		if (pr) {
			*pr = parse_result;
		}

		switch (parse_result) {
		case valid_token: {
			return result;
		}
		case no_token: {
			return default_value;
		}
		default: {
			Error("%ls: line %u: invalid bool value found.", GetFilename().c_str(), GetCurrentLineNumber());
			return default_value;
		}
		}
	}

	int LineReader::ParseOptionalInt(int default_value, ParseResult *pr) {
		int result;
		const ParseResult parse_result = mage::ParseInt(nullptr, &m_context, result, GetDelimiters().c_str());

		if (pr) {
			*pr = parse_result;
		}

		switch (parse_result) {
		case valid_token: {
			return result;
		}
		case no_token: {
			return default_value;
		}
		default: {
			Error("%ls: line %u: invalid int value found.", GetFilename().c_str(), GetCurrentLineNumber());
			return default_value;
		}
		}
	}

	unsigned int LineReader::ParseOptionalUnsignedInt(unsigned int default_value, ParseResult *pr) {
		unsigned int result;
		const ParseResult parse_result = mage::ParseUnsignedInt(nullptr, &m_context, result, GetDelimiters().c_str());

		if (pr) {
			*pr = parse_result;
		}

		switch (parse_result) {
		case valid_token: {
			return result;
		}
		case no_token: {
			return default_value;
		}
		default: {
			Error("%ls: line %u: invalid unsigned int value found.", GetFilename().c_str(), GetCurrentLineNumber());
			return default_value;
		}
		}
	}

	long LineReader::ParseOptionalLong(long default_value, ParseResult *pr) {
		long result;
		const ParseResult parse_result = mage::ParseLong(nullptr, &m_context, result, GetDelimiters().c_str());

		if (pr) {
			*pr = parse_result;
		}

		switch (parse_result) {
		case valid_token: {
			return result;
		}
		case no_token: {
			return default_value;
		}
		default: {
			Error("%ls: line %u: invalid long value found.", GetFilename().c_str(), GetCurrentLineNumber());
			return default_value;
		}
		}
	}

	unsigned long LineReader::ParseOptionalUnsignedLong(unsigned long default_value, ParseResult *pr) {
		unsigned long result;
		const ParseResult parse_result = mage::ParseUnsignedLong(nullptr, &m_context, result, GetDelimiters().c_str());

		if (pr) {
			*pr = parse_result;
		}

		switch (parse_result) {
		case valid_token: {
			return result;
		}
		case no_token: {
			return default_value;
		}
		default: {
			Error("%ls: line %u: invalid unsigned long value found.", GetFilename().c_str(), GetCurrentLineNumber());
			return default_value;
		}
		}
	}

	float LineReader::ParseOptionalFloat(float default_value, ParseResult *pr) {
		float result;
		const ParseResult parse_result = mage::ParseFloat(nullptr, &m_context, result, GetDelimiters().c_str());

		if (pr) {
			*pr = parse_result;
		}

		switch (parse_result) {
		case valid_token: {
			return result;
		}
		case no_token: {
			return default_value;
		}
		default: {
			Error("%ls: line %u: invalid float value found.", GetFilename().c_str(), GetCurrentLineNumber());
			return default_value;
		}
		}
	}

	double LineReader::ParseOptionalDouble(double default_value, ParseResult *pr) {
		double result;
		const ParseResult parse_result = mage::ParseDouble(nullptr, &m_context, result, GetDelimiters().c_str());

		if (pr) {
			*pr = parse_result;
		}

		switch (parse_result) {
		case valid_token: {
			return result;
		}
		case no_token: {
			return default_value;
		}
		default: {
			Error("%ls: line %u: invalid double value found.", GetFilename().c_str(), GetCurrentLineNumber());
			return default_value;
		}
		}
	}

	XMFLOAT2 LineReader::ParseOptionalFloat2(XMFLOAT2 default_value, ParseResult *pr) {
		XMFLOAT2 result;
		const ParseResult parse_result = mage::ParseFloat2(nullptr, &m_context, result, GetDelimiters().c_str());

		if (pr) {
			*pr = parse_result;
		}

		switch (parse_result) {
		case valid_token: {
			return result;
		}
		case no_token: {
			return default_value;
		}
		default: {
			Error("%ls: line %u: invalid float2 value found.", GetFilename().c_str(), GetCurrentLineNumber());
			return default_value;
		}
		}
	}

	XMFLOAT3 LineReader::ParseOptionalFloat3(XMFLOAT3 default_value, ParseResult *pr) {
		XMFLOAT3 result;
		const ParseResult parse_result = mage::ParseFloat3(nullptr, &m_context, result, GetDelimiters().c_str());

		if (pr) {
			*pr = parse_result;
		}

		switch (parse_result) {
		case valid_token: {
			return result;
		}
		case no_token: {
			return default_value;
		}
		default: {
			Error("%ls: line %u: invalid float3 value found.", GetFilename().c_str(), GetCurrentLineNumber());
			return default_value;
		}
		}
	}

	XMFLOAT4 LineReader::ParseOptionalFloat4(XMFLOAT4 default_value, ParseResult *pr) {
		XMFLOAT4 result;
		const ParseResult parse_result = mage::ParseFloat4(nullptr, &m_context, result, GetDelimiters().c_str());

		if (pr) {
			*pr = parse_result;
		}

		switch (parse_result) {
		case valid_token: {
			return result;
		}
		case no_token: {
			return default_value;
		}
		default: {
			Error("%ls: line %u: invalid float4 value found.", GetFilename().c_str(), GetCurrentLineNumber());
			return default_value;
		}
		}
	}
}