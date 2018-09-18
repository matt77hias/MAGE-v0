//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "io\writer.hpp"
#include "exception\exception.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	Writer::Writer()
		: m_file_stream(nullptr), 
		m_path() {}

	Writer::Writer(Writer&& writer) noexcept = default;

	Writer::~Writer() = default;

	Writer& Writer::operator=(Writer&& writer) noexcept = default;

	void Writer::WriteToFile(std::filesystem::path path) {
		m_path = std::move(path);

		std::FILE* file;
		{
			const errno_t result = _wfopen_s(&file, m_path.c_str(), L"w");
			ThrowIfFailed((0 == result), "{}: could not open file.", m_path);
		}

		m_file_stream.reset(file);

		Write();
	}

	void Writer::WriteCharacter(char c) {
		const int result = std::fputc(c, m_file_stream.get());
		ThrowIfFailed((EOF != result), 
					  "{}: could not write to file.", GetPath());
	}
	
	void Writer::WriteString(NotNull< const_zstring > str) {
		const int result = std::fputs(str, m_file_stream.get());
		ThrowIfFailed((EOF != result), 
					  "{}: could not write to file.", GetPath());
	}
	
	void Writer::WriteStringLine(NotNull< const_zstring > str) {
		WriteString(str);
		WriteCharacter('\n');
	}
}