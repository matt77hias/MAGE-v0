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

	const std::regex LineReader::g_default_regex 
		= std::regex(R"((\".*?\")|[^\n\r\s\t]+)");

	LineReader::LineReader()
		: m_regex(), 
		m_path(), 
		m_token_iterator(), 
		m_line_number(0) {}

	LineReader::LineReader(LineReader&& reader) noexcept 
		: m_regex(std::move(reader.m_regex)), 
		m_path(std::move(reader.m_path)), 
		m_token_iterator(reader.m_token_iterator),
		m_line_number(reader.m_line_number) {}

	LineReader::~LineReader() = default;

	LineReader& LineReader::operator=(LineReader&& reader) noexcept {
		m_regex          = std::move(reader.m_regex);
		m_path           = std::move(reader.m_path);
		m_token_iterator = reader.m_token_iterator;
		m_line_number    = reader.m_line_number;
		return *this;
	}

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

	void LineReader::ReadFromMemory(const std::string &input,
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
		m_line_number = 0;
		
		std::string line;
		while (std::getline(stream, line)) {
			m_token_iterator = std::sregex_token_iterator(line.cbegin(), 
														  line.cend(), 
														  m_regex, 0);
			if (ContainsTokens()) {
				ReadLine();
			}
			
			++m_line_number;
		}

		m_token_iterator = {};
	}

	void LineReader::Postprocess() {}

	void LineReader::ReadRemainingTokens() {
		for (; ContainsTokens(); ++m_token_iterator) {
			const auto token = m_token_iterator->str();
			Warning("%ls: line %u: unused token: %s.",
					GetPath().c_str(), GetCurrentLineNumber(), token.c_str());
		}
	}

	[[nodiscard]]
	bool LineReader::ContainsTokens() const noexcept {
		static const std::sregex_token_iterator token_end_iterator;
		return token_end_iterator != m_token_iterator;
	}

	[[nodiscard]]
	const std::string_view LineReader::GetCurrentToken() const noexcept {
		if (m_token_iterator->matched) {
			return { &*m_token_iterator->first, static_cast< size_t >(
				m_token_iterator->second - m_token_iterator->first) };
		}
		else {
			return {};
		}
	}
}