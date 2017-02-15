//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "string\parsing.hpp"
#include "string\string_utils.hpp"
#include "logging\error.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	//-------------------------------------------------------------------------
	// Conversion Utilities
	//-------------------------------------------------------------------------

	ParseResult StringToInt(const char *str, int &result) {
		if (!str) {
			return no_token;
		}

		char *inner_context = nullptr;
		result = (unsigned int)strtoul(str, &inner_context, 10);
		return (inner_context != str) ? valid_token : invalid_token;
	}

	ParseResult StringToUnsignedInt(const char *str, unsigned int &result) {
		if (!str) {
			return no_token;
		}

		char *inner_context = nullptr;
		result = (int)strtol(str, &inner_context, 10);
		return (inner_context != str) ? valid_token : invalid_token;
	}

	ParseResult StringToLong(const char *str, long &result) {
		if (!str) {
			return no_token;
		}

		char *inner_context = nullptr;
		result = strtol(str, &inner_context, 10);
		return (inner_context != str) ? valid_token : invalid_token;
	}

	ParseResult StringToUnsignedLong(const char *str, unsigned long &result) {
		if (!str) {
			return no_token;
		}

		char *inner_context = nullptr;
		result = strtoul(str, &inner_context, 10);
		return (inner_context != str) ? valid_token : invalid_token;
	}

	ParseResult StringToFloat(const char *str, float &result) {
		if (!str) {
			return no_token;
		}

		char *inner_context = nullptr;
		result = (float)strtof(str, &inner_context);
		return (inner_context != str) ? valid_token : invalid_token;
	}

	ParseResult StringToDouble(const char *str, double &result) {
		if (!str) {
			return no_token;
		}

		char *inner_context = nullptr;
		result = strtof(str, &inner_context);
		return (inner_context != str) ? valid_token : invalid_token;
	}

	//-------------------------------------------------------------------------
	// Parsing Utilities
	//-------------------------------------------------------------------------

	ParseResult ParseChars(char *str, char **context, char **result, const char *delimiters) {
		*result = strtok_s(str, delimiters, context);
		if (!result) {
			return no_token;
		}

		return valid_token;
	}

	ParseResult ParseString(char *str, char **context, string &result, const char *delimiters) {
		const char *token = strtok_s(str, delimiters, context);
		if (!token) {
			return no_token;
		}
		
		result = token;

		return valid_token;
	}

	ParseResult ParseInt(char *str, char **context, int &result, const char *delimiters) {
		const char *token = strtok_s(str, delimiters, context);
		return StringToInt(token, result);
	}

	ParseResult ParseUnsignedInt(char *str, char **context, unsigned int &result, const char *delimiters) {
		const char *token = strtok_s(str, delimiters, context);
		return StringToUnsignedInt(token, result);
	}

	ParseResult ParseLong(char *str, char **context, long &result, const char *delimiters) {
		const char *token = strtok_s(str, delimiters, context);
		return StringToLong(token, result);
	}

	ParseResult ParseUnsignedLong(char *str, char **context, unsigned long &result, const char *delimiters) {
		const char *token = strtok_s(str, delimiters, context);
		return StringToUnsignedLong(token, result);
	}

	ParseResult ParseFloat(char *str, char **context, float &result, const char *delimiters) {
		const char *token = strtok_s(str, delimiters, context);
		return StringToFloat(token, result);
	}

	ParseResult ParseDouble(char *str, char **context, double &result, const char *delimiters) {
		const char *token = strtok_s(str, delimiters, context);
		return StringToDouble(token, result);
	}

	ParseResult ParseFloat2(char *str, char **context, XMFLOAT2 &result, const char *delimiters) {
		const ParseResult parse_result_x = ParseFloat(str, context, result.x, delimiters);
		const ParseResult parse_result_y = ParseFloat(str, context, result.y, delimiters);

		if (parse_result_x == invalid_token 
			|| parse_result_y == invalid_token) {
			return invalid_token;
		}
		if (parse_result_x == no_token 
			|| parse_result_y == no_token) {
			return no_token;
		}
		return valid_token;
	}

	ParseResult ParseFloat3(char *str, char **context, XMFLOAT3 &result, const char *delimiters) {
		const ParseResult parse_result_x = ParseFloat(str, context, result.x, delimiters);
		const ParseResult parse_result_y = ParseFloat(str, context, result.y, delimiters);
		const ParseResult parse_result_z = ParseFloat(str, context, result.z, delimiters);

		if (parse_result_x == invalid_token 
			|| parse_result_y == invalid_token 
			|| parse_result_z == invalid_token) {
			return invalid_token;
		}
		if (parse_result_x == no_token 
			|| parse_result_y == no_token 
			|| parse_result_z == no_token) {
			return no_token;
		}
		return valid_token;
	}

	ParseResult ParseFloat4(char *str, char **context, XMFLOAT4 &result, const char *delimiters) {
		const ParseResult parse_result_x = ParseFloat(str, context, result.x, delimiters);
		const ParseResult parse_result_y = ParseFloat(str, context, result.y, delimiters);
		const ParseResult parse_result_z = ParseFloat(str, context, result.z, delimiters);
		const ParseResult parse_result_w = ParseFloat(str, context, result.w, delimiters);

		if (parse_result_x == invalid_token 
			|| parse_result_y == invalid_token 
			|| parse_result_z == invalid_token 
			|| parse_result_w == invalid_token) {
			return invalid_token;
		}
		if (parse_result_x == no_token 
			|| parse_result_y == no_token 
			|| parse_result_z == no_token 
			|| parse_result_w == no_token) {
			return no_token;
		}
		return valid_token;
	}

	//-------------------------------------------------------------------------
	// LineParser
	//-------------------------------------------------------------------------

	HRESULT LineParser::ParseFromFile(const wstring &fname, const string &delimiters) {
		m_fname = fname;
		m_delimiters = delimiters;
		
		// Open the file.
		FILE *file = nullptr;
		const errno_t result_fopen_s = _wfopen_s(&file, GetFilename().c_str(), L"r");
		if (result_fopen_s) {
			Error("%ls: could not open file.", m_fname.c_str());
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

		return S_OK;
	}

	HRESULT LineParser::ParseFromMemory(const char *input, const string &delimiters) {
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

		return S_OK;
	}

	HRESULT LineParser::Preprocess() {
		return S_OK;
	}

	HRESULT LineParser::Postprocess() {
		return S_OK;
	}

	void LineParser::ParseLineRemaining() {
		char *next_token = strtok_s(nullptr, GetDelimiters().c_str(), &m_context);
		while (next_token) {
			Warning("%ls: line %u: unused token: %s.", GetFilename().c_str(), GetCurrentLineNumber(), next_token);
			next_token = strtok_s(nullptr, GetDelimiters().c_str(), &m_context);
		}
	}

	char *LineParser::ParseChars() {
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

	string LineParser::ParseString() {
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

	int LineParser::ParseInt() {
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

	unsigned int LineParser::ParseUnsignedInt() {
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

	long LineParser::ParseLong() {
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

	unsigned long LineParser::ParseUnsignedLong() {
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

	float LineParser::ParseFloat() {
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

	double LineParser::ParseDouble() {
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

	XMFLOAT2 LineParser::ParseFloat2() {
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

	XMFLOAT3 LineParser::ParseFloat3() {
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

	XMFLOAT4 LineParser::ParseFloat4() {
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

	char *LineParser::ParseOptionalChars(ParseResult *pr) {
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

	string LineParser::ParseOptionalString(const string &default_value, ParseResult *pr) {
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

	int LineParser::ParseOptionalInt(int default_value, ParseResult *pr) {
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

	unsigned int LineParser::ParseOptionalUnsignedInt(unsigned int default_value, ParseResult *pr) {
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

	long LineParser::ParseOptionalLong(long default_value, ParseResult *pr) {
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

	unsigned long LineParser::ParseOptionalUnsignedLong(unsigned long default_value, ParseResult *pr) {
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

	float LineParser::ParseOptionalFloat(float default_value, ParseResult *pr) {
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

	double LineParser::ParseOptionalDouble(double default_value, ParseResult *pr) {
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

	XMFLOAT2 LineParser::ParseOptionalFloat2(XMFLOAT2 default_value, ParseResult *pr) {
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

	XMFLOAT3 LineParser::ParseOptionalFloat3(XMFLOAT3 default_value, ParseResult *pr) {
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

	XMFLOAT4 LineParser::ParseOptionalFloat4(XMFLOAT4 default_value, ParseResult *pr) {
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