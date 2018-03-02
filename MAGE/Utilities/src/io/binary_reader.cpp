//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "io\binary_reader.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	void ReadBinaryFile(const wstring& fname,
						UniquePtr< U8[] >& data,
						size_t& size) {

		auto file_handle = CreateUniqueHandle(CreateFile2(fname.c_str(), 
														  GENERIC_READ, 
														  FILE_SHARE_READ, 
														  OPEN_EXISTING, 
														  nullptr));
		
		FILE_STANDARD_INFO file_info;
		{
			const BOOL result = GetFileInformationByHandleEx(file_handle.get(), 
															 FileStandardInfo, 
															 &file_info, 
															 sizeof(file_info));
			ThrowIfFailed(result, 
						  "%ls: could not retrieve file information.", 
						  fname.c_str());
			ThrowIfFailed((0 == file_info.EndOfFile.HighPart), 
						  "%ls: file too big for 32-bit allocation.", 
						  fname.c_str());
		}
		
		// Allocate buffer.
		const auto nb_bytes = file_info.EndOfFile.LowPart;
		size = nb_bytes;
		data = MakeUnique< U8[] >(nb_bytes);
		ThrowIfFailed((nullptr != data), 
					  "%ls: file too big for allocation.", fname.c_str());

		// Populate buffer.
		{
			DWORD nb_bytes_read = 0;
			const BOOL result = ReadFile(file_handle.get(), data.get(), 
										 nb_bytes, &nb_bytes_read, nullptr);
			ThrowIfFailed(result, 
						  "%ls: could not load file data.", fname.c_str());
			ThrowIfFailed((nb_bytes <= nb_bytes_read), 
						  "%ls: could not load all file data.", fname.c_str());
		}
	}

	//-------------------------------------------------------------------------
	// BinaryReader
	//-------------------------------------------------------------------------
	#pragma region

	BinaryReader::BinaryReader()
		: m_fname(), 
		m_big_endian(true),
		m_pos(nullptr), 
		m_end(nullptr), 
		m_data() {}

	BinaryReader::BinaryReader(BinaryReader&& reader) noexcept = default;

	BinaryReader::~BinaryReader() = default;

	BinaryReader& BinaryReader::operator=(BinaryReader&& reader) noexcept = default;

	void BinaryReader::ReadFromFile(wstring fname, bool big_endian) {
		m_fname = std::move(fname);
		m_big_endian = big_endian;

		size_t nb_bytes = 0u;
		ReadBinaryFile(m_fname, m_data, nb_bytes);
		
		m_pos = m_data.get();
		m_end = m_data.get() + nb_bytes;
		
		ReadData();
	}
	
	void BinaryReader::ReadFromMemory(gsl::span< const U8 > input, bool big_endian) {
		m_fname = L"input string";
		m_big_endian = big_endian;
		
		m_pos = input.data();
		m_end = input.data() + input.size();

		ThrowIfFailed((m_pos <= m_end), 
					  "%ls: overflow.", GetFilename().c_str());

		ReadData();
	}

	NotNull< const_zstring > BinaryReader::ReadChars(size_t size) {
		const auto old_pos = m_pos;
		const auto new_pos = m_pos + size;
		ThrowIfFailed((m_pos <= new_pos), 
					  "%ls: overflow: no chars value found.", 
					  GetFilename().c_str());
		ThrowIfFailed((new_pos <= m_end), 
					  "%ls: end of file: no chars value found.", 
					  GetFilename().c_str());

		m_pos = new_pos;
		return reinterpret_cast< const char* >(old_pos);
	}

	#pragma endregion

	//-------------------------------------------------------------------------
	// BigEndianBinaryReader
	//-------------------------------------------------------------------------
	#pragma region

	BigEndianBinaryReader::BigEndianBinaryReader()
		: m_fname(), 
		m_pos(nullptr), 
		m_end(nullptr), 
		m_data() {}

	BigEndianBinaryReader::BigEndianBinaryReader(BigEndianBinaryReader&& 
												 reader) noexcept = default;

	BigEndianBinaryReader::~BigEndianBinaryReader() = default;

	BigEndianBinaryReader& BigEndianBinaryReader
		::operator=(BigEndianBinaryReader&& reader) noexcept = default;

	void BigEndianBinaryReader::ReadFromFile(wstring fname) {
		m_fname = std::move(fname);

		size_t nb_bytes = 0u;
		ReadBinaryFile(m_fname, m_data, nb_bytes);

		m_pos = m_data.get();
		m_end = m_data.get() + nb_bytes;
		
		ReadData();
	}
	
	void BigEndianBinaryReader::ReadFromMemory(gsl::span< const U8 > input) {
		m_fname = L"input string";

		m_pos = input.data();
		m_end = input.data() + input.size();

		ThrowIfFailed((m_pos <= m_end), 
					  "%ls: overflow.", GetFilename().c_str());

		ReadData();
	}

	#pragma endregion
}