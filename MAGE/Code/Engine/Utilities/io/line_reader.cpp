//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "io\line_reader.hpp"
#include "logging\logging.hpp"

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

	const std::regex LineReader::s_default_regex
		= std::regex(R"((\"([^\"]*)\")|(\S+))");

	const LineReader::SelectionFunction LineReader::s_default_selection_function
		= [](const std::smatch& match) {
		return match[2].length() ? match[2] : match[3];
	};

	LineReader::LineReader()
		: m_regex(),
		m_selection_function(),
		m_path(),
		m_iterator(),
		m_line_number(0) {}

	LineReader::LineReader(LineReader&& reader) noexcept
		: m_regex(std::move(reader.m_regex)),
		m_selection_function(std::move(reader.m_selection_function)),
		m_path(std::move(reader.m_path)),
		m_iterator(reader.m_iterator),
		m_line_number(reader.m_line_number) {}

	LineReader::~LineReader() = default;

	LineReader& LineReader::operator=(LineReader&& reader) noexcept {
		m_regex              = std::move(reader.m_regex);
		m_selection_function = std::move(reader.m_selection_function);
		m_path               = reader.m_path;
		m_iterator           = reader.m_iterator;
		m_line_number        = reader.m_line_number;
		return *this;
	}

	void LineReader::ReadFromFile(const std::filesystem::path& path,
								  const std::regex& regex,
								  const SelectionFunction& selection_function) {

		m_path               = path;
		m_regex              = regex;
		m_selection_function = selection_function;

		// Preprocessing
		Preprocess();

		// Processing
		std::ifstream stream(m_path.c_str());
		ThrowIfFailed(stream.is_open(), "{}: could not open file.", m_path);
		Process(stream);

		// Postprocessing
		Postprocess();
	}

	void LineReader::ReadFromMemory(const std::string& input,
									const std::regex& regex,
									const SelectionFunction& selection_function) {

		m_path               = L"input string";
		m_regex              = regex;
		m_selection_function = selection_function;

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
		m_line_number = 0u;

		std::string line;
		while (std::getline(stream, line)) {
			m_iterator = std::sregex_iterator(line.cbegin(), line.cend(), m_regex);
			if (ContainsTokens()) {
				ReadLine();
			}

			++m_line_number;
		}

		m_iterator = {};
	}

	void LineReader::Postprocess() {}

	void LineReader::ReadRemainingTokens() {
		while (ContainsTokens()) {
			const auto token = Read< std::string_view >();
			Warning("{}: line {}: unused token: {}.",
					GetPath(), GetCurrentLineNumber(), token);
		}
	}

	[[nodiscard]]
	bool LineReader::ContainsTokens() const noexcept {
		static const std::sregex_iterator end_iterator;
		return end_iterator != m_iterator;
	}

	[[nodiscard]]
	const std::string_view LineReader::GetCurrentToken() const noexcept {
		const auto token = m_selection_function(*m_iterator);
		if (token.matched) {
			return { &*token.first,
				     static_cast< std::size_t >(token.second - token.first) };
		}
		else {
			return {};
		}
	}
}
