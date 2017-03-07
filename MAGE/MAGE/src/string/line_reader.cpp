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
	
	const char *LineReader::ReadChars() {
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
		string result;
		const TokenResult token_result = mage::ReadQuotedString(nullptr, &m_context, result, GetDelimiters().c_str());

		switch (token_result) {
		case valid_token: {
			return result;
		}
		case no_token: {
			Error("%ls: line %u: no quoted string value found.", GetFilename().c_str(), GetCurrentLineNumber());
			return "";
		}
		default: {
			Error("%ls: line %u: invalid quoted string value found.", GetFilename().c_str(), GetCurrentLineNumber());
			return "";
		}
		}
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
	int8_t LineReader::ReadInt8() {
		int8_t result;
		const TokenResult token_result = mage::ReadInt8(nullptr, &m_context, result, GetDelimiters().c_str());

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
	uint8_t LineReader::ReadUInt8() {
		uint8_t result;
		const TokenResult token_result = mage::ReadUInt8(nullptr, &m_context, result, GetDelimiters().c_str());

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
	int16_t LineReader::ReadInt16() {
		int16_t result;
		const TokenResult token_result = mage::ReadInt16(nullptr, &m_context, result, GetDelimiters().c_str());

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
	uint16_t LineReader::ReadUInt16() {
		uint16_t result;
		const TokenResult token_result = mage::ReadUInt16(nullptr, &m_context, result, GetDelimiters().c_str());

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
	int32_t LineReader::ReadInt32() {
		int32_t result;
		const TokenResult token_result = mage::ReadInt32(nullptr, &m_context, result, GetDelimiters().c_str());

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
	uint32_t LineReader::ReadUInt32() {
		uint32_t result;
		const TokenResult token_result = mage::ReadUInt32(nullptr, &m_context, result, GetDelimiters().c_str());

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
	int64_t LineReader::ReadInt64() {
		int64_t result;
		const TokenResult token_result = mage::ReadInt64(nullptr, &m_context, result, GetDelimiters().c_str());

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
	uint64_t LineReader::ReadUInt64() {
		uint64_t result;
		const TokenResult token_result = mage::ReadUInt64(nullptr, &m_context, result, GetDelimiters().c_str());

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
		return mage::HasQuotedString(m_context, GetDelimiters().c_str()) == valid_token;
	}
	bool LineReader::HasBool() const {
		return mage::HasBool(m_context, GetDelimiters().c_str()) == valid_token;
	}
	bool LineReader::HasInt8() const {
		return mage::HasInt8(m_context, GetDelimiters().c_str()) == valid_token;
	}
	bool LineReader::HasUInt8() const {
		return mage::HasUInt8(m_context, GetDelimiters().c_str()) == valid_token;
	}
	bool LineReader::HasInt16() const {
		return mage::HasInt16(m_context, GetDelimiters().c_str()) == valid_token;
	}
	bool LineReader::HasUInt16() const {
		return mage::HasUInt16(m_context, GetDelimiters().c_str()) == valid_token;
	}
	bool LineReader::HasInt32() const {
		return mage::HasInt32(m_context, GetDelimiters().c_str()) == valid_token;
	}
	bool LineReader::HasUInt32() const {
		return mage::HasUInt32(m_context, GetDelimiters().c_str()) == valid_token;
	}
	bool LineReader::HasInt64() const {
		return mage::HasInt64(m_context, GetDelimiters().c_str()) == valid_token;
	}
	bool LineReader::HasUInt64() const {
		return mage::HasUInt64(m_context, GetDelimiters().c_str()) == valid_token;
	}
	bool LineReader::HasFloat() const {
		return mage::HasFloat(m_context, GetDelimiters().c_str()) == valid_token;
	}
	bool LineReader::HasDouble() const {
		return mage::HasDouble(m_context, GetDelimiters().c_str()) == valid_token;
	}
}