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
	// Parsing Utilities
	//-------------------------------------------------------------------------

	ParseResult ParseChars(char **result, char **context, char *str, const char *delimiters) {
		*result = strtok_s(str, delimiters, context);
		if (!result) {
			return no_token;
		}

		return valid_token;
	}

	ParseResult ParseString(string &result, char **context, char *str, const char *delimiters) {
		const char *token = strtok_s(str, delimiters, context);
		if (!token) {
			return no_token;
		}
		
		result = token;

		return valid_token;
	}

	ParseResult ParseUnsignedInt(unsigned int &result, char **context, char *str, const char *delimiters) {
		const char *token = strtok_s(str, delimiters, context);
		if (!token) {
			return no_token;
		}

		char *inner_context = nullptr;
		result = (unsigned int)strtoul(token, &inner_context, 10);
		if (inner_context == token) {
			return invalid_token;
		}

		return valid_token;
	}

	ParseResult ParseInt(int &result, char **context, char *str, const char *delimiters) {
		const char *token = strtok_s(str, delimiters, context);
		if (!token) {
			return no_token;
		}

		char *inner_context = nullptr;
		result = (int)strtol(token, &inner_context, 10);
		if (inner_context == token) {
			return invalid_token;
		}

		return valid_token;
	}

	ParseResult ParseLong(long &result, char **context, char *str, const char *delimiters) {
		const char *token = strtok_s(str, delimiters, context);
		if (!token) {
			return no_token;
		}

		char *inner_context = nullptr;
		result = strtol(token, &inner_context, 10);
		if (inner_context == token) {
			return invalid_token;
		}

		return valid_token;
	}

	ParseResult ParseUnsignedLong(unsigned long &result, char **context, char *str, const char *delimiters) {
		const char *token = strtok_s(str, delimiters, context);
		if (!token) {
			return no_token;
		}

		char *inner_context = nullptr;
		result = strtoul(token, &inner_context, 10);
		if (inner_context == token) {
			return invalid_token;
		}

		return valid_token;
	}

	ParseResult ParseFloat(float &result, char **context, char *str, const char *delimiters) {
		const char *token = strtok_s(str, delimiters, context);
		if (!token) {
			return no_token;
		}

		char *inner_context = nullptr;
		result = strtof(token, &inner_context);
		if (inner_context == token) {
			return invalid_token;
		}

		return valid_token;
	}

	ParseResult ParseDouble(double &result, char **context, char *str, const char *delimiters) {
		const char *token = strtok_s(str, delimiters, context);
		if (!token) {
			return no_token;
		}

		char *inner_context = nullptr;
		result = strtod(token, &inner_context);
		if (inner_context == token) {
			return invalid_token;
		}

		return valid_token;
	}

	ParseResult ParseFloat2(XMFLOAT2 &result, char **context, char *str, const char *delimiters) {
		const ParseResult parse_result_x = ParseFloat(result.x, context, str, delimiters);
		const ParseResult parse_result_y = ParseFloat(result.y, context, str, delimiters);

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

	ParseResult ParseFloat3(XMFLOAT3 &result, char **context, char *str, const char *delimiters) {
		const ParseResult parse_result_x = ParseFloat(result.x, context, str, delimiters);
		const ParseResult parse_result_y = ParseFloat(result.y, context, str, delimiters);
		const ParseResult parse_result_z = ParseFloat(result.z, context, str, delimiters);

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

	ParseResult ParseFloat4(XMFLOAT4 &result, char **context, char *str, const char *delimiters) {
		const ParseResult parse_result_x = ParseFloat(result.x, context, str, delimiters);
		const ParseResult parse_result_y = ParseFloat(result.y, context, str, delimiters);
		const ParseResult parse_result_z = ParseFloat(result.z, context, str, delimiters);
		const ParseResult parse_result_w = ParseFloat(result.w, context, str, delimiters);

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

	void LineParser::ParseLineRemaining() {
		char *next_token = strtok_s(nullptr, m_delimiters.c_str(), &m_context);
		while (next_token) {
			Warning("%ls: line %u: unused token: %s.", GetFilename().c_str(), GetCurrentLineNumber(), next_token);
			next_token = strtok_s(nullptr, m_delimiters.c_str(), &m_context);
		}
	}

	char *LineParser::ParseChars(bool report_error) {
		char *result;
		const ParseResult parse_result = mage::ParseChars(&result, &m_context, nullptr, m_delimiters.c_str());

		switch (parse_result) {
		case valid_token: {
			return result;
		}
		case no_token: {
			if (report_error) {
				Error("%ls: line %u: no char string value found.", GetFilename().c_str(), GetCurrentLineNumber());
			}
			return "";
		}
		default: {
			if (report_error) {
				Error("%ls: line %u: invalid char string value found.", GetFilename().c_str(), GetCurrentLineNumber());
			}
			return "";
		}
		}
	}

	string LineParser::ParseString(const string &default_value, bool report_error) {
		string result;
		const ParseResult parse_result = mage::ParseString(result, &m_context, nullptr, m_delimiters.c_str());

		switch (parse_result) {
		case valid_token: {
			return result;
		}
		case no_token: {
			if (report_error) {
				Error("%ls: line %u: no string value found.", GetFilename().c_str(), GetCurrentLineNumber());
			}
			return default_value;
		}
		default: {
			if (report_error) {
				Error("%ls: line %u: invalid string value found.", GetFilename().c_str(), GetCurrentLineNumber());
			}
			return default_value;
		}
		}
	}

	unsigned int LineParser::ParseUnsignedInt(unsigned int default_value, bool report_error) {
		unsigned int result;
		const ParseResult parse_result = mage::ParseUnsignedInt(result, &m_context, nullptr, m_delimiters.c_str());

		switch (parse_result) {
		case valid_token: {
			return result;
		}
		case no_token: {
			if (report_error) {
				Error("%ls: line %u: no unsigned int value found.", GetFilename().c_str(), GetCurrentLineNumber());
			}
			return default_value;
		}
		default: {
			if (report_error) {
				Error("%ls: line %u: invalid unsigned int value found.", GetFilename().c_str(), GetCurrentLineNumber());
			}
			return default_value;
		}
		}
	}

	int LineParser::ParseInt(int default_value, bool report_error) {
		int result;
		const ParseResult parse_result = mage::ParseInt(result, &m_context, nullptr, m_delimiters.c_str());

		switch (parse_result) {
		case valid_token: {
			return result;
		}
		case no_token: {
			if (report_error) {
				Error("%ls: line %u: no int value found.", GetFilename().c_str(), GetCurrentLineNumber());
			}
			return default_value;
		}
		default: {
			if (report_error) {
				Error("%ls: line %u: invalid int value found.", GetFilename().c_str(), GetCurrentLineNumber());
			}
			return default_value;
		}
		}
	}

	unsigned long LineParser::ParseUnsignedLong(unsigned long default_value, bool report_error) {
		unsigned long result;
		const ParseResult parse_result = mage::ParseUnsignedLong(result, &m_context, nullptr, m_delimiters.c_str());

		switch (parse_result) {
		case valid_token: {
			return result;
		}
		case no_token: {
			if (report_error) {
				Error("%ls: line %u: no unsigned long value found.", GetFilename().c_str(), GetCurrentLineNumber());
			}
			return default_value;
		}
		default: {
			if (report_error) {
				Error("%ls: line %u: invalid unsigned long value found.", GetFilename().c_str(), GetCurrentLineNumber());
			}
			return default_value;
		}
		}
	}

	long LineParser::ParseLong(long default_value, bool report_error) {
		long result;
		const ParseResult parse_result = mage::ParseLong(result, &m_context, nullptr, m_delimiters.c_str());

		switch (parse_result) {
		case valid_token: {
			return result;
		}
		case no_token: {
			if (report_error) {
				Error("%ls: line %u: no long value found.", GetFilename().c_str(), GetCurrentLineNumber());
			}
			return default_value;
		}
		default: {
			if (report_error) {
				Error("%ls: line %u: invalid long value found.", GetFilename().c_str(), GetCurrentLineNumber());
			}
			return default_value;
		}
		}
	}

	float LineParser::ParseFloat(float default_value, bool report_error) {
		float result;
		const ParseResult parse_result = mage::ParseFloat(result, &m_context, nullptr, m_delimiters.c_str());

		switch (parse_result) {
		case valid_token: {
			return result;
		}
		case no_token: {
			if (report_error) {
				Error("%ls: line %u: no float value found.", GetFilename().c_str(), GetCurrentLineNumber());
			}
			return default_value;
		}
		default: {
			if (report_error) {
				Error("%ls: line %u: invalid float value found.", GetFilename().c_str(), GetCurrentLineNumber());
			}
			return default_value;
		}
		}
	}

	double LineParser::ParseDouble(double default_value, bool report_error) {
		double result;
		const ParseResult parse_result = mage::ParseDouble(result, &m_context, nullptr, m_delimiters.c_str());

		switch (parse_result) {
		case valid_token: {
			return result;
		}
		case no_token: {
			if (report_error) {
				Error("%ls: line %u: no double value found.", GetFilename().c_str(), GetCurrentLineNumber());
			}
			return default_value;
		}
		default: {
			if (report_error) {
				Error("%ls: line %u: invalid double value found.", GetFilename().c_str(), GetCurrentLineNumber());
			}
			return default_value;
		}
		}
	}

	XMFLOAT2 LineParser::ParseFloat2(XMFLOAT2 default_value, bool report_error) {
		XMFLOAT2 result;
		const ParseResult parse_result = mage::ParseFloat2(result, &m_context, nullptr, m_delimiters.c_str());

		switch (parse_result) {
		case valid_token: {
			return result;
		}
		case no_token: {
			if (report_error) {
				Error("%ls: line %u: no float2 value found.", GetFilename().c_str(), GetCurrentLineNumber());
			}
			return default_value;
		}
		default: {
			if (report_error) {
				Error("%ls: line %u: invalid float2 value found.", GetFilename().c_str(), GetCurrentLineNumber());
			}
			return default_value;
		}
		}
	}

	XMFLOAT3 LineParser::ParseFloat3(XMFLOAT3 default_value, bool report_error) {
		XMFLOAT3 result;
		const ParseResult parse_result = mage::ParseFloat3(result, &m_context, nullptr, m_delimiters.c_str());

		switch (parse_result) {
		case valid_token: {
			return result;
		}
		case no_token: {
			if (report_error) {
				Error("%ls: line %u: no float3 value found.", GetFilename().c_str(), GetCurrentLineNumber());
			}
			return default_value;
		}
		default: {
			if (report_error) {
				Error("%ls: line %u: invalid float3 value found.", GetFilename().c_str(), GetCurrentLineNumber());
			}
			return default_value;
		}
		}
	}

	XMFLOAT4 LineParser::ParseFloat4(XMFLOAT4 default_value, bool report_error) {
		XMFLOAT4 result;
		const ParseResult parse_result = mage::ParseFloat4(result, &m_context, nullptr, m_delimiters.c_str());

		switch (parse_result) {
		case valid_token: {
			return result;
		}
		case no_token: {
			if (report_error) {
				Error("%ls: line %u: no float4 value found.", GetFilename().c_str(), GetCurrentLineNumber());
			}
			return default_value;
		}
		default: {
			if (report_error) {
				Error("%ls: line %u: invalid float4 value found.", GetFilename().c_str(), GetCurrentLineNumber());
			}
			return default_value;
		}
		}
	}
}