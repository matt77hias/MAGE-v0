//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "string\line_reader.hpp"
#include "string\string_utils.hpp"
#include "logging\exception.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	LineReader::LineReader()
		: m_context(nullptr), m_file_stream(nullptr), m_fname(),
		m_delimiters(mage_default_delimiters), m_line_number(0) {}

	void LineReader::ReadFromFile(const wstring &fname, const string &delimiters) {
		m_fname = fname;
		m_delimiters = delimiters;
		
		// Open the file.
		FILE *file;
		const errno_t result_fopen_s = _wfopen_s(&file, GetFilename().c_str(), L"r");
		if (result_fopen_s) {
			throw FormattedException("%ls: could not open file.", GetFilename().c_str());
		}
		m_file_stream.reset(file);

		Preprocess();

		char current_line[MAX_PATH];
		m_line_number = 1;
		// Continue reading from the file until the eof is reached.
		while (fgets(current_line, _countof(current_line), m_file_stream.get())) {
			ReadLine(current_line);
			++m_line_number;
		}

		Postprocess();

		m_context = nullptr;
	}

	void LineReader::ReadFromMemory(const char *input, const string &delimiters) {
		Assert(input);
		
		m_fname = L"input string";
		m_delimiters = delimiters;
		m_file_stream.reset(nullptr);

		Preprocess();

		char current_line[MAX_PATH];
		m_line_number = 1;
		// Continue reading from the file until the eof is reached.
		while (str_gets(current_line, _countof(current_line), &input)) {
			ReadLine(current_line);
			++m_line_number;
		}

		Postprocess();

		m_context = nullptr;
	}

	void LineReader::ReadLineRemaining() {
		char *next_token = strtok_s(nullptr, GetDelimiters().c_str(), &m_context);
		while (next_token) {
			Warning("%ls: line %u: unused token: %s.", 
				GetFilename().c_str(), GetCurrentLineNumber(), next_token);
			next_token = strtok_s(nullptr, GetDelimiters().c_str(), &m_context);
		}
	}
	
	const char *LineReader::ReadChars() {
		char *result;
		const TokenResult token_result = mage::ReadChars(nullptr, &m_context, &result, GetDelimiters().c_str());

		switch (token_result) {
		case TokenResult_Valid: {
			return result;
		}
		default: {
			throw FormattedException("%ls: line %u: no char string value found.",
				GetFilename().c_str(), GetCurrentLineNumber());
		}
		}
	}
	
	const string LineReader::ReadString() {
		string result;
		const TokenResult token_result = mage::ReadString(nullptr, &m_context, result, GetDelimiters().c_str());

		switch (token_result) {
		case TokenResult_Valid: {
			return result;
		}
		default: {
			throw FormattedException("%ls: line %u: no string value found.", 
				GetFilename().c_str(), GetCurrentLineNumber());
		}
		}
	}
	
	const string LineReader::ReadQuotedString() {
		string result;
		const TokenResult token_result = mage::ReadQuotedString(nullptr, &m_context, result, GetDelimiters().c_str());

		switch (token_result) {
		case TokenResult_Valid: {
			return result;
		}
		case TokenResult_None: {
			throw FormattedException("%ls: line %u: no quoted string value found.", 
				GetFilename().c_str(), GetCurrentLineNumber());
		}
		default: {
			throw FormattedException("%ls: line %u: invalid quoted string value found.", 
				GetFilename().c_str(), GetCurrentLineNumber());
		}
		}
	}
	
	bool LineReader::ReadBool() {
		bool result;
		const TokenResult token_result = mage::ReadBool(nullptr, &m_context, result, GetDelimiters().c_str());

		switch (token_result) {
		case TokenResult_Valid: {
			return result;
		}
		case TokenResult_None: {
			throw FormattedException("%ls: line %u: no bool value found.", 
				GetFilename().c_str(), GetCurrentLineNumber());
		}
		default: {
			throw FormattedException("%ls: line %u: invalid bool value found.", 
				GetFilename().c_str(), GetCurrentLineNumber());
		}
		}
	}
	
	int8_t LineReader::ReadInt8() {
		int8_t result;
		const TokenResult token_result = mage::ReadInt8(nullptr, &m_context, result, GetDelimiters().c_str());

		switch (token_result) {
		case TokenResult_Valid: {
			return result;
		}
		case TokenResult_None: {
			throw FormattedException("%ls: line %u: no 8 bit integer value found.", 
				GetFilename().c_str(), GetCurrentLineNumber());
		}
		default: {
			throw FormattedException("%ls: line %u: invalid 8 bit integer value found.", 
				GetFilename().c_str(), GetCurrentLineNumber());
		}
		}
	}
	
	uint8_t LineReader::ReadUInt8() {
		uint8_t result;
		const TokenResult token_result = mage::ReadUInt8(nullptr, &m_context, result, GetDelimiters().c_str());

		switch (token_result) {
		case TokenResult_Valid: {
			return result;
		}
		case TokenResult_None: {
			throw FormattedException("%ls: line %u: no 8 bit unsigned integer value found.", 
				GetFilename().c_str(), GetCurrentLineNumber());
		}
		default: {
			throw FormattedException("%ls: line %u: invalid 8 bit unsigned integer value found.", 
				GetFilename().c_str(), GetCurrentLineNumber());
		}
		}
	}
	
	int16_t LineReader::ReadInt16() {
		int16_t result;
		const TokenResult token_result = mage::ReadInt16(nullptr, &m_context, result, GetDelimiters().c_str());

		switch (token_result) {
		case TokenResult_Valid: {
			return result;
		}
		case TokenResult_None: {
			throw FormattedException("%ls: line %u: no 16 bit integer value found.", 
				GetFilename().c_str(), GetCurrentLineNumber());
		}
		default: {
			throw FormattedException("%ls: line %u: invalid 16 bit integer value found.", 
				GetFilename().c_str(), GetCurrentLineNumber());
		}
		}
	}
	
	uint16_t LineReader::ReadUInt16() {
		uint16_t result;
		const TokenResult token_result = mage::ReadUInt16(nullptr, &m_context, result, GetDelimiters().c_str());

		switch (token_result) {
		case TokenResult_Valid: {
			return result;
		}
		case TokenResult_None: {
			throw FormattedException("%ls: line %u: no 16 bit unsigned integer value found.", 
				GetFilename().c_str(), GetCurrentLineNumber());
		}
		default: {
			throw FormattedException("%ls: line %u: invalid 16 bit unsigned integer value found.", 
				GetFilename().c_str(), GetCurrentLineNumber());
		}
		}
	}
	
	int32_t LineReader::ReadInt32() {
		int32_t result;
		const TokenResult token_result = mage::ReadInt32(nullptr, &m_context, result, GetDelimiters().c_str());

		switch (token_result) {
		case TokenResult_Valid: {
			return result;
		}
		case TokenResult_None: {
			throw FormattedException("%ls: line %u: no 32 bit integer value found.", 
				GetFilename().c_str(), GetCurrentLineNumber());
		}
		default: {
			throw FormattedException("%ls: line %u: invalid 32 bit integer value found.", 
				GetFilename().c_str(), GetCurrentLineNumber());
		}
		}
	}
	
	uint32_t LineReader::ReadUInt32() {
		uint32_t result;
		const TokenResult token_result = mage::ReadUInt32(nullptr, &m_context, result, GetDelimiters().c_str());

		switch (token_result) {
		case TokenResult_Valid: {
			return result;
		}
		case TokenResult_None: {
			throw FormattedException("%ls: line %u: no unsigned 32 bit integer value found.", 
				GetFilename().c_str(), GetCurrentLineNumber());
		}
		default: {
			throw FormattedException("%ls: line %u: invalid unsigned 32 bit integer value found.", 
				GetFilename().c_str(), GetCurrentLineNumber());
		}
		}
	}
	
	int64_t LineReader::ReadInt64() {
		int64_t result;
		const TokenResult token_result = mage::ReadInt64(nullptr, &m_context, result, GetDelimiters().c_str());

		switch (token_result) {
		case TokenResult_Valid: {
			return result;
		}
		case TokenResult_None: {
			throw FormattedException("%ls: line %u: no 64 bit integer value found.", GetFilename().c_str(), GetCurrentLineNumber());
		}
		default: {
			throw FormattedException("%ls: line %u: invalid 64 bit integer value found.", GetFilename().c_str(), GetCurrentLineNumber());
		}
		}
	}
	
	uint64_t LineReader::ReadUInt64() {
		uint64_t result;
		const TokenResult token_result = mage::ReadUInt64(nullptr, &m_context, result, GetDelimiters().c_str());

		switch (token_result) {
		case TokenResult_Valid: {
			return result;
		}
		case TokenResult_None: {
			throw FormattedException("%ls: line %u: no 64 bit unsigned integer value found.", 
				GetFilename().c_str(), GetCurrentLineNumber());
		}
		default: {
			throw FormattedException("%ls: line %u: invalid 64 bit unsigned integer value found.", 
				GetFilename().c_str(), GetCurrentLineNumber());
		}
		}
	}
	
	float LineReader::ReadFloat() {
		float result;
		const TokenResult token_result = mage::ReadFloat(nullptr, &m_context, result, GetDelimiters().c_str());

		switch (token_result) {
		case TokenResult_Valid: {
			return result;
		}
		case TokenResult_None: {
			throw FormattedException("%ls: line %u: no float value found.", GetFilename().c_str(), GetCurrentLineNumber());
		}
		default: {
			throw FormattedException("%ls: line %u: invalid float value found.", GetFilename().c_str(), GetCurrentLineNumber());
		}
		}
	}
	
	double LineReader::ReadDouble() {
		double result;
		const TokenResult token_result = mage::ReadDouble(nullptr, &m_context, result, GetDelimiters().c_str());

		switch (token_result) {
		case TokenResult_Valid: {
			return result;
		}
		case TokenResult_None: {
			throw FormattedException("%ls: line %u: no double value found.", 
				GetFilename().c_str(), GetCurrentLineNumber());
		}
		default: {
			throw FormattedException("%ls: line %u: invalid double value found.", 
				GetFilename().c_str(), GetCurrentLineNumber());
		}
		}
	}
	
	const XMFLOAT2 LineReader::ReadFloat2() {
		XMFLOAT2 result;
		const TokenResult token_result = mage::ReadFloat2(nullptr, &m_context, result, GetDelimiters().c_str());

		switch (token_result) {
		case TokenResult_Valid: {
			return result;
		}
		case TokenResult_None: {
			throw FormattedException("%ls: line %u: no float2 value found.", 
				GetFilename().c_str(), GetCurrentLineNumber());
		}
		default: {
			throw FormattedException("%ls: line %u: invalid float2 value found.", 
				GetFilename().c_str(), GetCurrentLineNumber());
		}
		}
	}
	
	const XMFLOAT3 LineReader::ReadFloat3() {
		XMFLOAT3 result;
		const TokenResult token_result = mage::ReadFloat3(nullptr, &m_context, result, GetDelimiters().c_str());

		switch (token_result) {
		case TokenResult_Valid: {
			return result;
		}
		case TokenResult_None: {
			throw FormattedException("%ls: line %u: no float3 value found.", 
				GetFilename().c_str(), GetCurrentLineNumber());
		}
		default: {
			throw FormattedException("%ls: line %u: invalid float3 value found.", 
				GetFilename().c_str(), GetCurrentLineNumber());
		}
		}
	}
	
	const XMFLOAT4 LineReader::ReadFloat4() {
		XMFLOAT4 result;
		const TokenResult token_result = mage::ReadFloat4(nullptr, &m_context, result, GetDelimiters().c_str());

		switch (token_result) {
		case TokenResult_Valid: {
			return result;
		}
		case TokenResult_None: {
			throw FormattedException("%ls: line %u: no float4 value found.", 
				GetFilename().c_str(), GetCurrentLineNumber());
		}
		default: {
			throw FormattedException("%ls: line %u: invalid float4 value found.", 
				GetFilename().c_str(), GetCurrentLineNumber());
		}
		}
	}

	bool LineReader::HasChars() const {
		return mage::HasChars(m_context, GetDelimiters().c_str()) == TokenResult_Valid;
	}
	
	bool LineReader::HasString() const {
		return mage::HasString(m_context, GetDelimiters().c_str()) == TokenResult_Valid;
	}
	
	bool LineReader::HasQuotedString() const {
		return mage::HasQuotedString(m_context, GetDelimiters().c_str()) == TokenResult_Valid;
	}
	
	bool LineReader::HasBool() const {
		return mage::HasBool(m_context, GetDelimiters().c_str()) == TokenResult_Valid;
	}
	
	bool LineReader::HasInt8() const {
		return mage::HasInt8(m_context, GetDelimiters().c_str()) == TokenResult_Valid;
	}
	
	bool LineReader::HasUInt8() const {
		return mage::HasUInt8(m_context, GetDelimiters().c_str()) == TokenResult_Valid;
	}
	
	bool LineReader::HasInt16() const {
		return mage::HasInt16(m_context, GetDelimiters().c_str()) == TokenResult_Valid;
	}
	
	bool LineReader::HasUInt16() const {
		return mage::HasUInt16(m_context, GetDelimiters().c_str()) == TokenResult_Valid;
	}
	
	bool LineReader::HasInt32() const {
		return mage::HasInt32(m_context, GetDelimiters().c_str()) == TokenResult_Valid;
	}
	
	bool LineReader::HasUInt32() const {
		return mage::HasUInt32(m_context, GetDelimiters().c_str()) == TokenResult_Valid;
	}
	
	bool LineReader::HasInt64() const {
		return mage::HasInt64(m_context, GetDelimiters().c_str()) == TokenResult_Valid;
	}
	
	bool LineReader::HasUInt64() const {
		return mage::HasUInt64(m_context, GetDelimiters().c_str()) == TokenResult_Valid;
	}
	
	bool LineReader::HasFloat() const {
		return mage::HasFloat(m_context, GetDelimiters().c_str()) == TokenResult_Valid;
	}
	
	bool LineReader::HasDouble() const {
		return mage::HasDouble(m_context, GetDelimiters().c_str()) == TokenResult_Valid;
	}
}