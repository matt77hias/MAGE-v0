//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "binary\binary_reader.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	void ReadBinaryFile(const wchar_t *fname, UniquePtr< uint8_t[] > &data, size_t *size) {
		Assert(fname);
		Assert(size);
		
		UniqueHandle file_handle(SafeHandle(CreateFile2(fname, GENERIC_READ, FILE_SHARE_READ, OPEN_EXISTING, nullptr)));
		FILE_STANDARD_INFO file_info;
		if (!GetFileInformationByHandleEx(file_handle.get(), FileStandardInfo, &file_info, sizeof(file_info))) {
			throw FormattedException("%ls: could not retrieve file information.", fname);
		}
		if (file_info.EndOfFile.HighPart > 0) {
			throw FormattedException("%ls: file too big for 32-bit allocation.", fname);
		}
		
		const DWORD nb_bytes = file_info.EndOfFile.LowPart;
		*size = nb_bytes;
		data = MakeUnique< uint8_t[] >(nb_bytes);
		if (!data) {
			throw FormattedException("%ls: file too big for allocation.", fname);
		}

		DWORD nb_bytes_read = 0;
		if (!ReadFile(file_handle.get(), data.get(), nb_bytes, &nb_bytes_read, nullptr)) {
			throw FormattedException("%ls: could not load file data.", fname);
		}
		if (nb_bytes_read < nb_bytes) {
			throw FormattedException("%ls: could not load all file data.", fname);
		}
	}

	//-------------------------------------------------------------------------
	// BinaryReader
	//-------------------------------------------------------------------------

	BinaryReader::BinaryReader()
		: m_fname(), m_big_endian(true),
		m_pos(nullptr), m_end(nullptr), m_data() {}

	BinaryReader::BinaryReader(BinaryReader &&reader) = default;

	BinaryReader::~BinaryReader() = default;

	void BinaryReader::ReadFromFile(const wstring &fname, bool big_endian) {
		m_fname = fname;
		m_big_endian = big_endian;

		size_t nb_bytes;
		ReadBinaryFile(fname.c_str(), m_data, &nb_bytes);
		
		m_pos = m_data.get();
		m_end = m_data.get() + nb_bytes;
		
		Read();
	}
	
	void BinaryReader::ReadFromMemory(const uint8_t *input, size_t size, bool big_endian) {
		Assert(input);
		
		m_fname = L"input string";
		m_big_endian = big_endian;

		m_pos = input;
		m_end = input + size;

		if (m_end < m_pos) {
			throw FormattedException("%ls: overflow.", GetFilename().c_str());
		}
		
		Read();
	}

	const char *BinaryReader::ReadChars(size_t size) {
		const uint8_t *new_pos = m_pos + size;
		if (new_pos < m_pos) {
			throw FormattedException("%ls: overflow: no chars value found.", GetFilename().c_str());
		}
		if (m_end < new_pos) {
			throw FormattedException("%ls: end of file: no chars value found.", GetFilename().c_str());
		}

		const char *result = reinterpret_cast< const char * >(m_pos);
		m_pos = new_pos;
		return result;
	}

	int8_t BinaryReader::ReadInt8() {
		const uint8_t *new_pos = m_pos + sizeof(int8_t);
		if (new_pos < m_pos) {
			throw FormattedException("%ls: overflow: no int8_t value found.", GetFilename().c_str());
		}
		if (m_end < new_pos) {
			throw FormattedException("%ls: end of file: no int8_t value found.", GetFilename().c_str());
		}

		const int8_t result = BytesToInt8(m_pos);
		m_pos = new_pos;
		return result;
	}

	uint8_t BinaryReader::ReadUInt8() {
		const uint8_t *new_pos = m_pos + sizeof(uint8_t);
		if (new_pos < m_pos) {
			throw FormattedException("%ls: overflow: no uint8_t value found.", GetFilename().c_str());
		}
		if (m_end < new_pos) {
			throw FormattedException("%ls: end of file: no uint8_t value found.", GetFilename().c_str());
		}

		const uint8_t result = BytesToUInt8(m_pos);
		m_pos = new_pos;
		return result;
	}

	int16_t BinaryReader::ReadInt16() {
		const uint8_t *new_pos = m_pos + sizeof(int16_t);
		if (new_pos < m_pos) {
			throw FormattedException("%ls: overflow: no int16_t value found.", GetFilename().c_str());
		}
		if (m_end < new_pos) {
			throw FormattedException("%ls: end of file: no int16_t value found.", GetFilename().c_str());
		}

		const int16_t result = BytesToInt16(m_pos, m_big_endian);
		m_pos = new_pos;
		return result;
	}

	uint16_t BinaryReader::ReadUInt16() {
		const uint8_t *new_pos = m_pos + sizeof(uint16_t);
		if (new_pos < m_pos) {
			throw FormattedException("%ls: overflow: no uint16_t value found.", GetFilename().c_str());
		}
		if (m_end < new_pos) {
			throw FormattedException("%ls: end of file: no uint16_t value found.", GetFilename().c_str());
		}

		const uint16_t result = BytesToUInt16(m_pos, m_big_endian);
		m_pos = new_pos;
		return result;
	}
	
	int32_t BinaryReader::ReadInt32() {
		const uint8_t *new_pos = m_pos + sizeof(int32_t);
		if (new_pos < m_pos) {
			throw FormattedException("%ls: overflow: no int32_t value found.", GetFilename().c_str());
		}
		if (m_end < new_pos) {
			throw FormattedException("%ls: end of file: no int32_t value found.", GetFilename().c_str());
		}

		const int32_t result = BytesToInt32(m_pos, m_big_endian);
		m_pos = new_pos;
		return result;
	}
	
	uint32_t BinaryReader::ReadUInt32() {
		const uint8_t *new_pos = m_pos + sizeof(uint32_t);
		if (new_pos < m_pos) {
			throw FormattedException("%ls: overflow: no uint32_t value found.", GetFilename().c_str());
		}
		if (m_end < new_pos) {
			throw FormattedException("%ls: end of file: no uint32_t value found.", GetFilename().c_str());
		}

		const uint32_t result = BytesToUInt32(m_pos, m_big_endian);
		m_pos = new_pos;
		return result;
	}
	
	int64_t BinaryReader::ReadInt64() {
		const uint8_t *new_pos = m_pos + sizeof(int64_t);
		if (new_pos < m_pos) {
			throw FormattedException("%ls: overflow: no int64_t value found.", GetFilename().c_str());
		}
		if (m_end < new_pos) {
			throw FormattedException("%ls: end of file: no int64_t value found.", GetFilename().c_str());
		}

		const int64_t result = BytesToInt64(m_pos, m_big_endian);
		m_pos = new_pos;
		return result;
	}
	
	uint64_t BinaryReader::ReadUInt64() {
		const uint8_t *new_pos = m_pos + sizeof(uint64_t);
		if (new_pos < m_pos) {
			throw FormattedException("%ls: overflow: no uint64_t value found.", GetFilename().c_str());
		}
		if (m_end < new_pos) {
			throw FormattedException("%ls: end of file: no uint64_t value found.", GetFilename().c_str());
		}

		const uint64_t result = BytesToUInt64(m_pos, m_big_endian);
		m_pos = new_pos;
		return result;
	}
	
	float BinaryReader::ReadFloat() {
		const uint8_t *new_pos = m_pos + sizeof(float);
		if (new_pos < m_pos) {
			throw FormattedException("%ls: overflow: no float value found.", GetFilename().c_str());
		}
		if (m_end < new_pos) {
			throw FormattedException("%ls: end of file: no float value found.", GetFilename().c_str());
		}

		const float result = BytesToFloat(m_pos, m_big_endian);
		m_pos = new_pos;
		return result;
	}
	
	double BinaryReader::ReadDouble() {
		const uint8_t *new_pos = m_pos + sizeof(double);
		if (new_pos < m_pos) {
			throw FormattedException("%ls: overflow: no double value found.", GetFilename().c_str());
		}
		if (m_end < new_pos) {
			throw FormattedException("%ls: end of file: no double value found.", GetFilename().c_str());
		}

		const double result = BytesToDouble(m_pos, m_big_endian);
		m_pos = new_pos;
		return result;
	}

	//-------------------------------------------------------------------------
	// BigEndianBinaryReader
	//-------------------------------------------------------------------------

	BigEndianBinaryReader::BigEndianBinaryReader()
		: m_fname(), m_pos(nullptr), m_end(nullptr), m_data() {}

	BigEndianBinaryReader::BigEndianBinaryReader(BigEndianBinaryReader &&reader) = default;

	BigEndianBinaryReader::~BigEndianBinaryReader() = default;

	void BigEndianBinaryReader::ReadFromFile(const wstring &fname) {
		m_fname = fname;

		size_t nb_bytes;
		ReadBinaryFile(fname.c_str(), m_data, &nb_bytes);

		m_pos = m_data.get();
		m_end = m_data.get() + nb_bytes;
		
		Read();
	}
	
	void BigEndianBinaryReader::ReadFromMemory(const uint8_t *input, size_t size) {
		Assert(input);

		m_fname = L"input string";

		m_pos = input;
		m_end = input + size;

		if (m_end < m_pos) {
			throw FormattedException("%ls: overflow.", GetFilename().c_str());
		}

		Read();
	}
}