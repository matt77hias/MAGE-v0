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

	BigEndianBinaryWriter::BigEndianBinaryWriter()
		: m_file_stream(nullptr), m_fname() {}

	BigEndianBinaryWriter::BigEndianBinaryWriter(BigEndianBinaryWriter &&writer) = default;

	BigEndianBinaryWriter::~BigEndianBinaryWriter() = default;

	void BigEndianBinaryWriter::WriteToFile(const wstring &fname) {
		m_fname = fname;

		FILE *file;
		const errno_t result_fopen_s = _wfopen_s(&file, GetFilename().c_str(), L"wb");
		if (result_fopen_s) {
			throw FormattedException("%ls: could not open file.", GetFilename().c_str());
		}
		m_file_stream.reset(file);

		Write();
	}

	void BigEndianBinaryWriter::WriteCharacter(char c) {
		const int result = fputc(c, m_file_stream.get());
		if (result == EOF) {
			throw FormattedException("%ls: could not write to file.", GetFilename().c_str());
		}
	}

	void BigEndianBinaryWriter::WriteString(const char *str) {
		Assert(str);

		const int result = fputs(str, m_file_stream.get());
		if (result == EOF) {
			throw FormattedException("%ls: could not write to file.", GetFilename().c_str());
		}
	}
}