//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "binary\binary_writer.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	BigEndianBinaryWriter::~BigEndianBinaryWriter() {
		CloseFile();
	}

	void BigEndianBinaryWriter::CloseFile() {
		if (m_file) {
			fclose(m_file);
			m_file = nullptr;
		}
	}

	void BigEndianBinaryWriter::WriteToFile(const wstring &fname) {
		m_fname = fname;

		CloseFile();

		const errno_t result_fopen_s = _wfopen_s(&m_file, GetFilename().c_str(), L"wb");
		if (result_fopen_s) {
			throw FormattedException("%ls: could not open file.", GetFilename().c_str());
		}

		Write();

		CloseFile();
	}

	void BigEndianBinaryWriter::WriteCharacter(char c) {
		const int result = fputc(c, m_file);
		if (result == EOF) {
			throw FormattedException("%ls: could not write to file.", GetFilename().c_str());
		}
	}

	void BigEndianBinaryWriter::WriteString(const char *str) {
		const int result = fputs(str, m_file);
		if (result == EOF) {
			throw FormattedException("%ls: could not write to file.", GetFilename().c_str());
		}
	}
}