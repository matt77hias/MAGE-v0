//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "utils\io\line_reader.hpp"
#include "utils\string\string_utils.hpp"
#include "utils\logging\error.hpp"
#include "utils\exception\exception.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	LineReader::LineReader()
		: m_context(nullptr), 
		m_file_stream(nullptr), 
		m_fname(),
		m_delimiters(g_default_delimiters), 
		m_line_number(0) {}

	LineReader::LineReader(LineReader &&reader) = default;

	LineReader::~LineReader() = default;

	void LineReader::ReadFromFile(wstring fname, string delimiters) {
		m_fname      = std::move(fname);
		m_delimiters = std::move(delimiters);
		
		// Open the file.
		FILE *file;
		{
			const errno_t result = _wfopen_s(&file, m_fname.c_str(), L"r");
			ThrowIfFailed((0 == result), 
				"%ls: could not open file.", m_fname.c_str());
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

	void LineReader::ReadFromMemory(const char *input, string delimiters) {
		Assert(input);
		
		m_fname      = L"input string";
		m_delimiters = std::move(delimiters);
		
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
		const TokenResult token_result 
			= mage::ReadChars(nullptr, &m_context, &result, GetDelimiters().c_str());

		switch (token_result) {
		
		case TokenResult::Valid: {
			return result;
		}
		
		default: {
			throw FormattedException(
				"%ls: line %u: no char string value found.",
				GetFilename().c_str(), GetCurrentLineNumber());
		}
		}
	}
	
	const string LineReader::ReadString() {
		string result;
		const TokenResult token_result 
			= mage::ReadString(nullptr, &m_context, result, GetDelimiters().c_str());

		switch (token_result) {
		
		case TokenResult::Valid: {
			return result;
		}
		
		default: {
			throw FormattedException(
				"%ls: line %u: no string value found.", 
				GetFilename().c_str(), GetCurrentLineNumber());
		}
		}
	}
	
	const string LineReader::ReadQuotedString() {
		string result;
		const TokenResult token_result 
			= mage::ReadQuotedString(nullptr, &m_context, result, GetDelimiters().c_str());

		switch (token_result) {
		
		case TokenResult::Valid: {
			return result;
		}
		
		case TokenResult::None: {
			throw FormattedException(
				"%ls: line %u: no quoted string value found.", 
				GetFilename().c_str(), GetCurrentLineNumber());
		}
		
		default: {
			throw FormattedException(
				"%ls: line %u: invalid quoted string value found.", 
				GetFilename().c_str(), GetCurrentLineNumber());
		}
		}
	}
	
	bool LineReader::ReadBool() {
		bool result;
		const TokenResult token_result 
			= mage::ReadBool(nullptr, &m_context, result, GetDelimiters().c_str());

		switch (token_result) {
		
		case TokenResult::Valid: {
			return result;
		}
		
		case TokenResult::None: {
			throw FormattedException(
				"%ls: line %u: no bool value found.", 
				GetFilename().c_str(), GetCurrentLineNumber());
		}
		
		default: {
			throw FormattedException(
				"%ls: line %u: invalid bool value found.", 
				GetFilename().c_str(), GetCurrentLineNumber());
		}
		}
	}
	
	S8 LineReader::ReadS8() {
		S8 result;
		const TokenResult token_result 
			= mage::ReadS8(nullptr, &m_context, result, GetDelimiters().c_str());

		switch (token_result) {
		
		case TokenResult::Valid: {
			return result;
		}
		
		case TokenResult::None: {
			throw FormattedException(
				"%ls: line %u: no 8 bit integer value found.", 
				GetFilename().c_str(), GetCurrentLineNumber());
		}
		
		default: {
			throw FormattedException(
				"%ls: line %u: invalid 8 bit integer value found.", 
				GetFilename().c_str(), GetCurrentLineNumber());
		}
		}
	}
	
	U8 LineReader::ReadU8() {
		U8 result;
		const TokenResult token_result 
			= mage::ReadU8(nullptr, &m_context, result, GetDelimiters().c_str());

		switch (token_result) {
		
		case TokenResult::Valid: {
			return result;
		}
		
		case TokenResult::None: {
			throw FormattedException(
				"%ls: line %u: no 8 bit unsigned integer value found.", 
				GetFilename().c_str(), GetCurrentLineNumber());
		}
		
		default: {
			throw FormattedException(
				"%ls: line %u: invalid 8 bit unsigned integer value found.", 
				GetFilename().c_str(), GetCurrentLineNumber());
		}
		}
	}
	
	S16 LineReader::ReadS16() {
		S16 result;
		const TokenResult token_result 
			= mage::ReadS16(nullptr, &m_context, result, GetDelimiters().c_str());

		switch (token_result) {
		
		case TokenResult::Valid: {
			return result;
		}
		
		case TokenResult::None: {
			throw FormattedException(
				"%ls: line %u: no 16 bit integer value found.", 
				GetFilename().c_str(), GetCurrentLineNumber());
		}
		
		default: {
			throw FormattedException(
				"%ls: line %u: invalid 16 bit integer value found.", 
				GetFilename().c_str(), GetCurrentLineNumber());
		}
		}
	}
	
	U16 LineReader::ReadU16() {
		U16 result;
		const TokenResult token_result 
			= mage::ReadU16(nullptr, &m_context, result, GetDelimiters().c_str());

		switch (token_result) {
		
		case TokenResult::Valid: {
			return result;
		}
		
		case TokenResult::None: {
			throw FormattedException(
				"%ls: line %u: no 16 bit unsigned integer value found.", 
				GetFilename().c_str(), GetCurrentLineNumber());
		}
		
		default: {
			throw FormattedException(
				"%ls: line %u: invalid 16 bit unsigned integer value found.", 
				GetFilename().c_str(), GetCurrentLineNumber());
		}
		}
	}
	
	S32 LineReader::ReadS32() {
		S32 result;
		const TokenResult token_result 
			= mage::ReadS32(nullptr, &m_context, result, GetDelimiters().c_str());

		switch (token_result) {
		
		case TokenResult::Valid: {
			return result;
		}
		
		case TokenResult::None: {
			throw FormattedException(
				"%ls: line %u: no 32 bit integer value found.", 
				GetFilename().c_str(), GetCurrentLineNumber());
		}
		
		default: {
			throw FormattedException(
				"%ls: line %u: invalid 32 bit integer value found.", 
				GetFilename().c_str(), GetCurrentLineNumber());
		}
		}
	}
	
	U32 LineReader::ReadU32() {
		U32 result;
		const TokenResult token_result 
			= mage::ReadU32(nullptr, &m_context, result, GetDelimiters().c_str());

		switch (token_result) {
		
		case TokenResult::Valid: {
			return result;
		}
		
		case TokenResult::None: {
			throw FormattedException(
				"%ls: line %u: no unsigned 32 bit integer value found.", 
				GetFilename().c_str(), GetCurrentLineNumber());
		}
		
		default: {
			throw FormattedException(
				"%ls: line %u: invalid unsigned 32 bit integer value found.", 
				GetFilename().c_str(), GetCurrentLineNumber());
		}
		}
	}
	
	S64 LineReader::ReadS64() {
		S64 result;
		const TokenResult token_result 
			= mage::ReadS64(nullptr, &m_context, result, GetDelimiters().c_str());

		switch (token_result) {
		
		case TokenResult::Valid: {
			return result;
		}
		
		case TokenResult::None: {
			throw FormattedException(
				"%ls: line %u: no 64 bit integer value found.", 
				GetFilename().c_str(), GetCurrentLineNumber());
		}
		
		default: {
			throw FormattedException(
				"%ls: line %u: invalid 64 bit integer value found.", 
				GetFilename().c_str(), GetCurrentLineNumber());
		}
		}
	}
	
	U64 LineReader::ReadU64() {
		U64 result;
		const TokenResult token_result 
			= mage::ReadU64(nullptr, &m_context, result, GetDelimiters().c_str());

		switch (token_result) {
		
		case TokenResult::Valid: {
			return result;
		}
		
		case TokenResult::None: {
			throw FormattedException(
				"%ls: line %u: no 64 bit unsigned integer value found.", 
				GetFilename().c_str(), GetCurrentLineNumber());
		}
		
		default: {
			throw FormattedException(
				"%ls: line %u: invalid 64 bit unsigned integer value found.", 
				GetFilename().c_str(), GetCurrentLineNumber());
		}
		}
	}
	
	F32 LineReader::ReadF32() {
		F32 result;
		const TokenResult token_result 
			= mage::ReadF32(nullptr, &m_context, result, GetDelimiters().c_str());

		switch (token_result) {
		
		case TokenResult::Valid: {
			return result;
		}
		
		case TokenResult::None: {
			throw FormattedException(
				"%ls: line %u: no F32 value found.", GetFilename().c_str(), GetCurrentLineNumber());
		}
		
		default: {
			throw FormattedException(
				"%ls: line %u: invalid F32 value found.", GetFilename().c_str(), GetCurrentLineNumber());
		}
		}
	}
	
	F64 LineReader::ReadF64() {
		F64 result;
		const TokenResult token_result 
			= mage::ReadF64(nullptr, &m_context, result, GetDelimiters().c_str());

		switch (token_result) {
		
		case TokenResult::Valid: {
			return result;
		}
		
		case TokenResult::None: {
			throw FormattedException(
				"%ls: line %u: no F64 value found.", 
				GetFilename().c_str(), GetCurrentLineNumber());
		}
		
		default: {
			throw FormattedException(
				"%ls: line %u: invalid F64 value found.", 
				GetFilename().c_str(), GetCurrentLineNumber());
		}
		}
	}
	
	const XMFLOAT2 LineReader::ReadF32x2() {
		XMFLOAT2 result;
		const TokenResult token_result 
			= mage::ReadF32x2(nullptr, &m_context, result, GetDelimiters().c_str());

		switch (token_result) {
		
		case TokenResult::Valid: {
			return result;
		}
		
		case TokenResult::None: {
			throw FormattedException(
				"%ls: line %u: no F322 value found.", 
				GetFilename().c_str(), GetCurrentLineNumber());
		}
		
		default: {
			throw FormattedException(
				"%ls: line %u: invalid F322 value found.", 
				GetFilename().c_str(), GetCurrentLineNumber());
		}
		}
	}
	
	const XMFLOAT3 LineReader::ReadF32x3() {
		XMFLOAT3 result;
		const TokenResult token_result 
			= mage::ReadF32x3(nullptr, &m_context, result, GetDelimiters().c_str());

		switch (token_result) {
		
		case TokenResult::Valid: {
			return result;
		}
		
		case TokenResult::None: {
			throw FormattedException(
				"%ls: line %u: no F323 value found.", 
				GetFilename().c_str(), GetCurrentLineNumber());
		}
		
		default: {
			throw FormattedException(
				"%ls: line %u: invalid F323 value found.", 
				GetFilename().c_str(), GetCurrentLineNumber());
		}
		}
	}
	
	const XMFLOAT4 LineReader::ReadF32x4() {
		XMFLOAT4 result;
		const TokenResult token_result 
			= mage::ReadF32x4(nullptr, &m_context, result, GetDelimiters().c_str());

		switch (token_result) {
		
		case TokenResult::Valid: {
			return result;
		}
		
		case TokenResult::None: {
			throw FormattedException(
				"%ls: line %u: no F324 value found.", 
				GetFilename().c_str(), GetCurrentLineNumber());
		}
		
		default: {
			throw FormattedException(
				"%ls: line %u: invalid F324 value found.", 
				GetFilename().c_str(), GetCurrentLineNumber());
		}
		}
	}

	bool LineReader::HasChars() const {
		return mage::HasChars(m_context, GetDelimiters().c_str()) 
			== TokenResult::Valid;
	}
	
	bool LineReader::HasString() const {
		return mage::HasString(m_context, GetDelimiters().c_str()) 
			== TokenResult::Valid;
	}
	
	bool LineReader::HasQuotedString() const {
		return mage::HasQuotedString(m_context, GetDelimiters().c_str()) 
			== TokenResult::Valid;
	}
	
	bool LineReader::HasBool() const {
		return mage::HasBool(m_context, GetDelimiters().c_str()) 
			== TokenResult::Valid;
	}
	
	bool LineReader::HasS8() const {
		return mage::HasS8(m_context, GetDelimiters().c_str()) 
			== TokenResult::Valid;
	}
	
	bool LineReader::HasU8() const {
		return mage::HasU8(m_context, GetDelimiters().c_str()) 
			== TokenResult::Valid;
	}
	
	bool LineReader::HasS16() const {
		return mage::HasS16(m_context, GetDelimiters().c_str()) 
			== TokenResult::Valid;
	}
	
	bool LineReader::HasU16() const {
		return mage::HasU16(m_context, GetDelimiters().c_str()) 
			== TokenResult::Valid;
	}
	
	bool LineReader::HasS32() const {
		return mage::HasS32(m_context, GetDelimiters().c_str()) 
			== TokenResult::Valid;
	}
	
	bool LineReader::HasU32() const {
		return mage::HasU32(m_context, GetDelimiters().c_str()) 
			== TokenResult::Valid;
	}
	
	bool LineReader::HasS64() const {
		return mage::HasS64(m_context, GetDelimiters().c_str()) 
			== TokenResult::Valid;
	}
	
	bool LineReader::HasU64() const {
		return mage::HasU64(m_context, GetDelimiters().c_str()) 
			== TokenResult::Valid;
	}
	
	bool LineReader::HasF32() const {
		return mage::HasF32(m_context, GetDelimiters().c_str()) 
			== TokenResult::Valid;
	}
	
	bool LineReader::HasF64() const {
		return mage::HasF64(m_context, GetDelimiters().c_str()) 
			== TokenResult::Valid;
	}
}