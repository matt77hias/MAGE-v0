//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "io\line_reader.hpp"
#include "string\string_utils.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// System Includes
//-----------------------------------------------------------------------------
#pragma region

#include <iterator>

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

	LineReader::LineReader(LineReader &&reader) noexcept = default;

	LineReader::~LineReader() = default;

	LineReader &LineReader::operator=(LineReader &&reader) noexcept = default;

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
		while (fgets(current_line, 
			         static_cast< int >(std::size(current_line)), 
			         m_file_stream.get())) {

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
		while (str_gets(current_line, 
			            std::size(current_line), 
			            &input)) {

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
			throw Exception(
				"%ls: line %u: no char string value found.",
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
			throw Exception(
				"%ls: line %u: no quoted string value found.", 
				GetFilename().c_str(), GetCurrentLineNumber());
		}
		
		default: {
			throw Exception(
				"%ls: line %u: invalid quoted string value found.", 
				GetFilename().c_str(), GetCurrentLineNumber());
		}
		}
	}
	
	bool LineReader::HasChars() const {
		return mage::HasChars(m_context, GetDelimiters().c_str()) 
			== TokenResult::Valid;
	}
	
	bool LineReader::HasQuotedString() const {
		return mage::HasQuotedString(m_context, GetDelimiters().c_str()) 
			== TokenResult::Valid;
	}
}