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

	Writer::Writer()
		: m_file(nullptr), m_fname() {}

	Writer::~Writer() {
		CloseFile();
	}

	void Writer::CloseFile() {
		if (m_file) {
			fclose(m_file);
			m_file = nullptr;
		}
	}

	void Writer::WriteToFile(const wstring &fname) {
		m_fname = fname;

		CloseFile();

		const errno_t result_fopen_s = _wfopen_s(&m_file, GetFilename().c_str(), L"w");
		if (result_fopen_s) {
			throw FormattedException("%ls: could not open file.", GetFilename().c_str());
		}

		Write();
		
		CloseFile();
	}

	void Writer::WriteCharacter(char c) {
		const int result = fputc(c, m_file);
		if (result == EOF) {
			throw FormattedException("%ls: could not write to file.", GetFilename().c_str());
		}
	}
	
	void Writer::WriteString(const char *str) {
		Assert(str);
		
		const int result = fputs(str, m_file);
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