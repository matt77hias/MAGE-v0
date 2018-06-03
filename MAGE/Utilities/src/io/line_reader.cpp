//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "io\line_reader.hpp"
#include "logging\error.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// System Includes
//-----------------------------------------------------------------------------
#pragma region

#include <fstream>
#include <sstream>

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	namespace {

		[[nodiscard]]
		inline bool IsValidID(const string& str) noexcept {
			const auto f = [](char c) { 
				return false; 
			};
			return str.cend() == std::find_if(str.cbegin(), str.cend(), f);
		}
	}

	const std::regex LineReader::g_default_regex 
		= std::regex(R"((\".*?\")|[^\n\r\s\t]+)");

	LineReader::LineReader()
		: m_regex(), 
		m_path(), 
		m_tokens(), 
		m_token_iterator(), 
		m_line_number(0) {}

	LineReader::LineReader(LineReader&& reader) noexcept = default;

	LineReader::~LineReader() = default;

	LineReader& LineReader::operator=(LineReader&& reader) noexcept = default;

	void LineReader::ReadFromFile(std::filesystem::path path, 
								  std::regex regex) {

		m_path  = std::move(path);
		m_regex = std::move(regex);

		// Preprocessing
		Preprocess();

		// Processing
		std::ifstream stream(m_path.c_str());
		ThrowIfFailed(stream.is_open(),
					  "%ls: could not open file.", m_path.c_str());
		Process(stream);

		// Postprocessing
		Postprocess();
	}

	void LineReader::ReadFromMemory(const string &input,
									std::regex regex) {

		m_path    = L"input string";
		m_regex   = std::move(regex);
		
		// Preprocessing
		Preprocess();

		// Processing
		std::istringstream stream(input);
		Process(stream);

		// Postprocessing
		Postprocess();
	}

	void LineReader::Preprocess() {}

	void LineReader::Process(std::istream& stream) {
		m_tokens.clear();
		m_token_iterator = m_tokens.cbegin();
		m_line_number = 0;
		
		string line;
		while (std::getline(stream, line)) {
			m_tokens.clear();
			std::copy(std::sregex_token_iterator(line.begin(), line.end(), m_regex, 0), 
					  std::sregex_token_iterator(), std::back_inserter(m_tokens));
			m_token_iterator = m_tokens.cbegin();
			
			if (ContainsTokens()) {
				ReadLine();
			}
			
			++m_line_number;
		}

		m_tokens.clear();
		m_token_iterator = m_tokens.cbegin();
	}

	void LineReader::Postprocess() {}

	const string LineReader::ReadIDString() {
		if (m_tokens.cend() == m_token_iterator) {
			throw Exception("%ls: line %u: no alpha-numeric string value found.",
							GetPath().c_str(), GetCurrentLineNumber());
		}

		const auto result = m_token_iterator->str();
		
		if (IsValidID(result)) {
			++m_token_iterator;
			return result;
		}
		else {
			throw Exception("%ls: line %u: invalid alpha-numeric string value found: %s.",
							GetPath().c_str(), GetCurrentLineNumber(),
							result.c_str());
		}
	}

	void LineReader::ReadRemainingTokens() {
		for (; m_token_iterator != m_tokens.cend(); ++m_token_iterator) {
			const auto token = m_token_iterator->str();
			Warning("%ls: line %u: unused token: %s.",
					GetPath().c_str(), GetCurrentLineNumber(), token.c_str());
		}
	}

	[[nodiscard]]
	bool LineReader::ContainsIDString() const noexcept {
		if (m_tokens.cend() == m_token_iterator) {
			return false;
		}

		const auto result = m_token_iterator->str();
		return IsValidID(result);
	}

	[[nodiscard]]
	bool LineReader::ContainsTokens() const noexcept {
		return Contains< string >();
	}
}