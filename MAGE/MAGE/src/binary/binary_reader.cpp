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

	void ReadBinaryFile(const wchar_t *fname, UniquePtr< u8[] > &data, size_t *size) {
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
		data = MakeUnique< u8[] >(nb_bytes);
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
	
	void BinaryReader::ReadFromMemory(const u8 *input, size_t size, bool big_endian) {
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
		const u8 *new_pos = m_pos + size;
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

	i8 BinaryReader::ReadI8() {
		const u8 *new_pos = m_pos + sizeof(i8);
		if (new_pos < m_pos) {
			throw FormattedException("%ls: overflow: no i8 value found.", GetFilename().c_str());
		}
		if (m_end < new_pos) {
			throw FormattedException("%ls: end of file: no i8 value found.", GetFilename().c_str());
		}

		const i8 result = BytesToI8(m_pos);
		m_pos = new_pos;
		return result;
	}

	u8 BinaryReader::ReadU8() {
		const u8 *new_pos = m_pos + sizeof(u8);
		if (new_pos < m_pos) {
			throw FormattedException("%ls: overflow: no u8 value found.", GetFilename().c_str());
		}
		if (m_end < new_pos) {
			throw FormattedException("%ls: end of file: no u8 value found.", GetFilename().c_str());
		}

		const u8 result = BytesToU8(m_pos);
		m_pos = new_pos;
		return result;
	}

	i16 BinaryReader::ReadI16() {
		const u8 *new_pos = m_pos + sizeof(i16);
		if (new_pos < m_pos) {
			throw FormattedException("%ls: overflow: no i16 value found.", GetFilename().c_str());
		}
		if (m_end < new_pos) {
			throw FormattedException("%ls: end of file: no i16 value found.", GetFilename().c_str());
		}

		const i16 result = BytesToI16(m_pos, m_big_endian);
		m_pos = new_pos;
		return result;
	}

	u16 BinaryReader::ReadU16() {
		const u8 *new_pos = m_pos + sizeof(u16);
		if (new_pos < m_pos) {
			throw FormattedException("%ls: overflow: no u16 value found.", GetFilename().c_str());
		}
		if (m_end < new_pos) {
			throw FormattedException("%ls: end of file: no u16 value found.", GetFilename().c_str());
		}

		const u16 result = BytesToU16(m_pos, m_big_endian);
		m_pos = new_pos;
		return result;
	}
	
	i32 BinaryReader::ReadI32() {
		const u8 *new_pos = m_pos + sizeof(i32);
		if (new_pos < m_pos) {
			throw FormattedException("%ls: overflow: no i32 value found.", GetFilename().c_str());
		}
		if (m_end < new_pos) {
			throw FormattedException("%ls: end of file: no i32 value found.", GetFilename().c_str());
		}

		const i32 result = BytesToI32(m_pos, m_big_endian);
		m_pos = new_pos;
		return result;
	}
	
	u32 BinaryReader::ReadU32() {
		const u8 *new_pos = m_pos + sizeof(u32);
		if (new_pos < m_pos) {
			throw FormattedException("%ls: overflow: no u32 value found.", GetFilename().c_str());
		}
		if (m_end < new_pos) {
			throw FormattedException("%ls: end of file: no u32 value found.", GetFilename().c_str());
		}

		const u32 result = BytesToU32(m_pos, m_big_endian);
		m_pos = new_pos;
		return result;
	}
	
	i64 BinaryReader::ReadI64() {
		const u8 *new_pos = m_pos + sizeof(i64);
		if (new_pos < m_pos) {
			throw FormattedException("%ls: overflow: no i64 value found.", GetFilename().c_str());
		}
		if (m_end < new_pos) {
			throw FormattedException("%ls: end of file: no i64 value found.", GetFilename().c_str());
		}

		const i64 result = BytesToI64(m_pos, m_big_endian);
		m_pos = new_pos;
		return result;
	}
	
	u64 BinaryReader::ReadU64() {
		const u8 *new_pos = m_pos + sizeof(u64);
		if (new_pos < m_pos) {
			throw FormattedException("%ls: overflow: no u64 value found.", GetFilename().c_str());
		}
		if (m_end < new_pos) {
			throw FormattedException("%ls: end of file: no u64 value found.", GetFilename().c_str());
		}

		const u64 result = BytesToU64(m_pos, m_big_endian);
		m_pos = new_pos;
		return result;
	}
	
	float BinaryReader::ReadFloat() {
		const u8 *new_pos = m_pos + sizeof(float);
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
		const u8 *new_pos = m_pos + sizeof(double);
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
	
	void BigEndianBinaryReader::ReadFromMemory(const u8 *input, size_t size) {
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