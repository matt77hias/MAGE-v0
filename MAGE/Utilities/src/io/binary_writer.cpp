//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "io\binary_writer.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	BigEndianBinaryWriter::BigEndianBinaryWriter()
		: m_file_stream(nullptr), 
		m_path() {}

	BigEndianBinaryWriter::BigEndianBinaryWriter(
		BigEndianBinaryWriter&& writer) noexcept = default;

	BigEndianBinaryWriter::~BigEndianBinaryWriter() = default;

	BigEndianBinaryWriter& BigEndianBinaryWriter
		::operator=(BigEndianBinaryWriter&& writer) noexcept = default;

	void BigEndianBinaryWriter::WriteToFile(std::filesystem::path path) {
		m_path = std::move(path);

		FILE* file;
		{
			const errno_t result = _wfopen_s(&file, m_path.c_str(), L"wb");
			ThrowIfFailed((0 == result), 
						  "%ls: could not open file.", m_path.c_str());
		}

		m_file_stream.reset(file);

		WriteData();
	}

	void BigEndianBinaryWriter::WriteCharacter(char c) {
		const int result = fputc(c, m_file_stream.get());
		ThrowIfFailed((EOF != result), 
					  "%ls: could not write to file.", GetPath().c_str());
	}

	void BigEndianBinaryWriter::WriteString(NotNull< const_zstring > str) {
		const int result = fputs(str, m_file_stream.get());
		ThrowIfFailed((EOF != result), 
					  "%ls: could not write to file.", GetPath().c_str());
	}
}