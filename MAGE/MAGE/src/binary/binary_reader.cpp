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

	void ReadBinaryFile(const wchar_t *fname, 
		UniquePtr< U8[] > &data, size_t *size) {

		Assert(fname);
		Assert(size);
		
		UniqueHandle file_handle(SafeHandle(CreateFile2(
			fname, GENERIC_READ, FILE_SHARE_READ, OPEN_EXISTING, nullptr)));
		
		FILE_STANDARD_INFO file_info;
		{
			const BOOL result = GetFileInformationByHandleEx(
				file_handle.get(), FileStandardInfo, &file_info, sizeof(file_info));
			ThrowIfFailed(result, 
				"%ls: could not retrieve file information.", fname);
			ThrowIfFailed((file_info.EndOfFile.HighPart <= 0),
				"%ls: file too big for 32-bit allocation.", fname);
		}
		
		// Allocate buffer.
		const DWORD nb_bytes = file_info.EndOfFile.LowPart;
		*size = nb_bytes;
		data = MakeUnique< U8[] >(nb_bytes);
		ThrowIfFailed((nullptr == data), 
			"%ls: file too big for allocation.", fname);

		// Populate buffer.
		{
			DWORD nb_bytes_read = 0;
			const BOOL result = ReadFile(
				file_handle.get(), data.get(), nb_bytes, &nb_bytes_read, nullptr);
			ThrowIfFailed(result, 
				"%ls: could not load file data.", fname);
			ThrowIfFailed((nb_bytes <= nb_bytes_read), 
				"%ls: could not load all file data.", fname);
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
	
	void BinaryReader::ReadFromMemory(const U8 *input, size_t size, bool big_endian) {
		Assert(input);
		
		m_fname = L"input string";
		m_big_endian = big_endian;

		m_pos = input;
		m_end = input + size;

		ThrowIfFailed((m_pos <= m_end), 
			"%ls: overflow.", GetFilename().c_str());

		Read();
	}

	const char *BinaryReader::ReadChars(size_t size) {
		const U8 *new_pos = m_pos + size;
		ThrowIfFailed((m_pos <= new_pos),
			"%ls: overflow: no chars value found.", GetFilename().c_str());
		ThrowIfFailed((new_pos <= m_end),
			"%ls: end of file: no chars value found.", GetFilename().c_str());

		const char *result = reinterpret_cast< const char * >(m_pos);
		m_pos = new_pos;
		return result;
	}

	S8 BinaryReader::ReadS8() {
		const U8 *new_pos = m_pos + sizeof(S8);
		ThrowIfFailed((m_pos <= new_pos),
			"%ls: overflow: no S8 value found.", GetFilename().c_str());
		ThrowIfFailed((new_pos <= m_end),
			"%ls: end of file: no S8 value found.", GetFilename().c_str());

		const S8 result = BytesToS8(m_pos);
		m_pos = new_pos;
		return result;
	}

	U8 BinaryReader::ReadU8() {
		const U8 *new_pos = m_pos + sizeof(U8);
		ThrowIfFailed((m_pos <= new_pos),
			"%ls: overflow: no U8 value found.", GetFilename().c_str());
		ThrowIfFailed((new_pos <= m_end),
			"%ls: end of file: no U8 value found.", GetFilename().c_str());

		const U8 result = BytesToU8(m_pos);
		m_pos = new_pos;
		return result;
	}

	S16 BinaryReader::ReadS16() {
		const U8 *new_pos = m_pos + sizeof(S16);
		ThrowIfFailed((m_pos <= new_pos),
			"%ls: overflow: no S16 value found.", GetFilename().c_str());
		ThrowIfFailed((new_pos <= m_end),
			"%ls: end of file: no S16 value found.", GetFilename().c_str());

		const S16 result = BytesToS16(m_pos, m_big_endian);
		m_pos = new_pos;
		return result;
	}

	U16 BinaryReader::ReadU16() {
		const U8 *new_pos = m_pos + sizeof(U16);
		ThrowIfFailed((m_pos <= new_pos),
			"%ls: overflow: no U16 value found.", GetFilename().c_str());
		ThrowIfFailed((new_pos <= m_end),
			"%ls: end of file: no U16 value found.", GetFilename().c_str());

		const U16 result = BytesToU16(m_pos, m_big_endian);
		m_pos = new_pos;
		return result;
	}
	
	S32 BinaryReader::ReadS32() {
		const U8 *new_pos = m_pos + sizeof(S32);
		ThrowIfFailed((m_pos <= new_pos),
			"%ls: overflow: no S32 value found.", GetFilename().c_str());
		ThrowIfFailed((new_pos <= m_end),
			"%ls: end of file: no S32 value found.", GetFilename().c_str());

		const S32 result = BytesToS32(m_pos, m_big_endian);
		m_pos = new_pos;
		return result;
	}
	
	U32 BinaryReader::ReadU32() {
		const U8 *new_pos = m_pos + sizeof(U32);
		ThrowIfFailed((m_pos <= new_pos),
			"%ls: overflow: no U32 value found.", GetFilename().c_str());
		ThrowIfFailed((new_pos <= m_end),
			"%ls: end of file: no U32 value found.", GetFilename().c_str());

		const U32 result = BytesToU32(m_pos, m_big_endian);
		m_pos = new_pos;
		return result;
	}
	
	S64 BinaryReader::ReadS64() {
		const U8 *new_pos = m_pos + sizeof(S64);
		ThrowIfFailed((m_pos <= new_pos),
			"%ls: overflow: no S64 value found.", GetFilename().c_str());
		ThrowIfFailed((new_pos <= m_end),
			"%ls: end of file: no S64 value found.", GetFilename().c_str());

		const S64 result = BytesToS64(m_pos, m_big_endian);
		m_pos = new_pos;
		return result;
	}
	
	U64 BinaryReader::ReadU64() {
		const U8 *new_pos = m_pos + sizeof(U64);
		ThrowIfFailed((m_pos <= new_pos),
			"%ls: overflow: no U64 value found.", GetFilename().c_str());
		ThrowIfFailed((new_pos <= m_end),
			"%ls: end of file: no U64 value found.", GetFilename().c_str());

		const U64 result = BytesToU64(m_pos, m_big_endian);
		m_pos = new_pos;
		return result;
	}
	
	F32 BinaryReader::ReadF32() {
		const U8 *new_pos = m_pos + sizeof(F32);
		ThrowIfFailed((m_pos <= new_pos),
			"%ls: overflow: no F32 value found.", GetFilename().c_str());
		ThrowIfFailed((new_pos <= m_end),
			"%ls: end of file: no F32 value found.", GetFilename().c_str());

		const F32 result = BytesToF32(m_pos, m_big_endian);
		m_pos = new_pos;
		return result;
	}
	
	F64 BinaryReader::ReadF64() {
		const U8 *new_pos = m_pos + sizeof(F64);
		ThrowIfFailed((m_pos <= new_pos),
			"%ls: overflow: no F64 value found.", GetFilename().c_str());
		ThrowIfFailed((new_pos <= m_end),
			"%ls: end of file: no F64 value found.", GetFilename().c_str());

		const F64 result = BytesToF64(m_pos, m_big_endian);
		m_pos = new_pos;
		return result;
	}

	//-------------------------------------------------------------------------
	// BigEndianBinaryReader
	//-------------------------------------------------------------------------

	BigEndianBinaryReader::BigEndianBinaryReader()
		: m_fname(), m_pos(nullptr), m_end(nullptr), m_data() {}

	BigEndianBinaryReader::BigEndianBinaryReader(
		BigEndianBinaryReader &&reader) = default;

	BigEndianBinaryReader::~BigEndianBinaryReader() = default;

	void BigEndianBinaryReader::ReadFromFile(const wstring &fname) {
		m_fname = fname;

		size_t nb_bytes;
		ReadBinaryFile(fname.c_str(), m_data, &nb_bytes);

		m_pos = m_data.get();
		m_end = m_data.get() + nb_bytes;
		
		Read();
	}
	
	void BigEndianBinaryReader::ReadFromMemory(const U8 *input, size_t size) {
		Assert(input);

		m_fname = L"input string";

		m_pos = input;
		m_end = input + size;

		ThrowIfFailed((m_pos <= m_end),
			"%ls: overflow.", GetFilename().c_str());

		Read();
	}
}