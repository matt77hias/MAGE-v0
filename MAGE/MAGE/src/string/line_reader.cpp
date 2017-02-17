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

			const HRESULT result_line = ReadLine(current_line);
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

			const HRESULT result_line = ReadLine(current_line);
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

	void LineReader::ReadLineRemaining() {
		char *next_token = strtok_s(nullptr, GetDelimiters().c_str(), &m_context);
		while (next_token) {
			Warning("%ls: line %u: unused token: %s.", GetFilename().c_str(), GetCurrentLineNumber(), next_token);
			next_token = strtok_s(nullptr, GetDelimiters().c_str(), &m_context);
		}
	}
	
	char *LineReader::ReadChars() {
		char *result;
		const TokenResult token_result = mage::ReadChars(nullptr, &m_context, &result, GetDelimiters().c_str());

		switch (token_result) {
		case valid_token: {
			return result;
		}
		default: {
			Error("%ls: line %u: no char string value found.", GetFilename().c_str(), GetCurrentLineNumber());
			return "";
		}
		}
	}
	string LineReader::ReadString() {
		string result;
		const TokenResult token_result = mage::ReadString(nullptr, &m_context, result, GetDelimiters().c_str());

		switch (token_result) {
		case valid_token: {
			return result;
		}
		default: {
			Error("%ls: line %u: no string value found.", GetFilename().c_str(), GetCurrentLineNumber());
			return "";
		}
		}
	}
	string LineReader::ReadQuotedString() {
		const char *first_quote = strchr(m_context, '"');
		char *last_quote = strrchr(m_context, '"');

		if (first_quote == last_quote || !str_contains(GetDelimiters().c_str(), *(last_quote + 1))) {
			Error("%ls: line %u: no quoted string value found.", GetFilename().c_str(), GetCurrentLineNumber());
			return "";
		}

		*last_quote = '\0';
		m_context = last_quote + 1;

		return first_quote + 1;
	}
	bool LineReader::ReadBool() {
		bool result;
		const TokenResult token_result = mage::ReadBool(nullptr, &m_context, result, GetDelimiters().c_str());

		switch (token_result) {
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
	int LineReader::ReadInt() {
		int result;
		const TokenResult token_result = mage::ReadInt(nullptr, &m_context, result, GetDelimiters().c_str());

		switch (token_result) {
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
	unsigned int LineReader::ReadUnsignedInt() {
		unsigned int result;
		const TokenResult token_result = mage::ReadUnsignedInt(nullptr, &m_context, result, GetDelimiters().c_str());

		switch (token_result) {
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
	long LineReader::ReadLong() {
		long result;
		const TokenResult token_result = mage::ReadLong(nullptr, &m_context, result, GetDelimiters().c_str());

		switch (token_result) {
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
	unsigned long LineReader::ReadUnsignedLong() {
		unsigned long result;
		const TokenResult token_result = mage::ReadUnsignedLong(nullptr, &m_context, result, GetDelimiters().c_str());

		switch (token_result) {
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
	long long LineReader::ReadLongLong() {
		long long result;
		const TokenResult token_result = mage::ReadLongLong(nullptr, &m_context, result, GetDelimiters().c_str());

		switch (token_result) {
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
	unsigned long long LineReader::ReadUnsignedLongLong() {
		unsigned long long result;
		const TokenResult token_result = mage::ReadUnsignedLongLong(nullptr, &m_context, result, GetDelimiters().c_str());

		switch (token_result) {
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
	float LineReader::ReadFloat() {
		float result;
		const TokenResult token_result = mage::ReadFloat(nullptr, &m_context, result, GetDelimiters().c_str());

		switch (token_result) {
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
	double LineReader::ReadDouble() {
		double result;
		const TokenResult token_result = mage::ReadDouble(nullptr, &m_context, result, GetDelimiters().c_str());

		switch (token_result) {
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
	XMFLOAT2 LineReader::ReadFloat2() {
		XMFLOAT2 result;
		const TokenResult token_result = mage::ReadFloat2(nullptr, &m_context, result, GetDelimiters().c_str());

		switch (token_result) {
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
	XMFLOAT3 LineReader::ReadFloat3() {
		XMFLOAT3 result;
		const TokenResult token_result = mage::ReadFloat3(nullptr, &m_context, result, GetDelimiters().c_str());

		switch (token_result) {
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
	XMFLOAT4 LineReader::ReadFloat4() {
		XMFLOAT4 result;
		const TokenResult token_result = mage::ReadFloat4(nullptr, &m_context, result, GetDelimiters().c_str());

		switch (token_result) {
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

	bool LineReader::HasChars() const {
		return mage::HasChars(m_context, GetDelimiters().c_str()) == valid_token;
	}
	bool LineReader::HasString() const {
		return mage::HasString(m_context, GetDelimiters().c_str()) == valid_token;
	}
	bool LineReader::HasQuotedString() const {
		return false;
	}
	bool LineReader::HasBool() const {
		return mage::HasBool(m_context, GetDelimiters().c_str()) == valid_token;
	}
	bool LineReader::HasInt() const {
		return mage::HasInt(m_context, GetDelimiters().c_str()) == valid_token;
	}
	bool LineReader::HasUnsignedInt() const {
		return mage::HasUnsignedInt(m_context, GetDelimiters().c_str()) == valid_token;
	}
	bool LineReader::HasLong() const {
		return mage::HasLong(m_context, GetDelimiters().c_str()) == valid_token;
	}
	bool LineReader::HasUnsignedLong() const {
		return mage::HasUnsignedLong(m_context, GetDelimiters().c_str()) == valid_token;
	}
	bool LineReader::HasLongLong() const {
		return mage::HasLongLong(m_context, GetDelimiters().c_str()) == valid_token;
	}
	bool LineReader::HasUnsignedLongLong() const {
		return mage::HasUnsignedLongLong(m_context, GetDelimiters().c_str()) == valid_token;
	}
	bool LineReader::HasFloat() const {
		return mage::HasFloat(m_context, GetDelimiters().c_str()) == valid_token;
	}
	bool LineReader::HasDouble() const {
		return mage::HasDouble(m_context, GetDelimiters().c_str()) == valid_token;
	}
}