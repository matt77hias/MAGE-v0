//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "utils\io\binary_writer.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	BigEndianBinaryWriter::BigEndianBinaryWriter()
		: m_file_stream(nullptr), 
		m_fname() {}

	BigEndianBinaryWriter::BigEndianBinaryWriter(
		BigEndianBinaryWriter &&writer) = default;

	BigEndianBinaryWriter::~BigEndianBinaryWriter() = default;

	void BigEndianBinaryWriter::WriteToFile(wstring fname) {
		m_fname = std::move(fname);

		FILE *file;
		{
			const errno_t result = _wfopen_s(&file, m_fname.c_str(), L"wb");
			ThrowIfFailed((0 == result),
				"%ls: could not open file.", m_fname.c_str());
		}

		m_file_stream.reset(file);

		Write();
	}

	void BigEndianBinaryWriter::WriteCharacter(char c) {
		const int result = fputc(c, m_file_stream.get());
		ThrowIfFailed((EOF != result),
			"%ls: could not write to file.", GetFilename().c_str());
	}

	void BigEndianBinaryWriter::WriteString(const char *str) {
		Assert(str);

		const int result = fputs(str, m_file_stream.get());
		ThrowIfFailed((EOF != result),
			"%ls: could not write to file.", GetFilename().c_str());
	}
}