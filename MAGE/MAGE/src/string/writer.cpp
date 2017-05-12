//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "string\writer.hpp"
#include "logging\error.hpp"
#include "logging\exception.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	Writer::Writer() noexcept
		: m_file_stream(nullptr), m_fname() {}

	Writer::Writer(Writer &&writer) noexcept = default;

	Writer::~Writer() noexcept = default;

	void Writer::WriteToFile(const wstring &fname) {
		m_fname = fname;

		FILE *file;
		const errno_t result_fopen_s = _wfopen_s(&file, GetFilename().c_str(), L"w");
		if (result_fopen_s) {
			throw FormattedException("%ls: could not open file.", GetFilename().c_str());
		}
		m_file_stream.reset(file);

		Write();
	}

	void Writer::WriteCharacter(char c) {
		const int result = fputc(c, m_file_stream.get());
		if (result == EOF) {
			throw FormattedException("%ls: could not write to file.", GetFilename().c_str());
		}
	}
	
	void Writer::WriteString(const char *str) {
		Assert(str);
		
		const int result = fputs(str, m_file_stream.get());
		if (result == EOF) {
			throw FormattedException("%ls: could not write to file.", GetFilename().c_str());
		}
	}
	
	void Writer::WriteStringLine(const char *str) {
		Assert(str);

		WriteString(str);
		WriteCharacter('\n');
	}
}