//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "binary\binary_reader.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations
//-----------------------------------------------------------------------------
namespace mage {

	HRESULT ReadBinaryFile(const wchar_t *fname, UniquePtr< uint8_t[] > &data, size_t *size) {
		UniqueHandle file_handle(SafeHandle(CreateFile2(fname, GENERIC_READ, FILE_SHARE_READ, OPEN_EXISTING, nullptr)));
		FILE_STANDARD_INFO file_info;
		if (!GetFileInformationByHandleEx(file_handle.get(), FileStandardInfo, &file_info, sizeof(file_info))) {
			Error("%ls: could not retrieve file information.", fname);
			return HRESULT_FROM_WIN32(GetLastError());
		}
		if (file_info.EndOfFile.HighPart > 0) {
			Error("%ls: file too big for 32-bit allocation.", fname);
			return E_FAIL;
		}
		
		const DWORD nb_bytes = file_info.EndOfFile.LowPart;
		*size = nb_bytes;
		data.reset(new uint8_t[nb_bytes]);
		if (!data) {
			Error("%ls: file too big for allocation.", fname);
			return E_FAIL;
		}

		DWORD nb_bytes_read = 0;
		if (!ReadFile(file_handle.get(), data.get(), nb_bytes, &nb_bytes_read, nullptr)) {
			Error("%ls: could not load file data.", fname);
			return HRESULT_FROM_WIN32(GetLastError());
		}
		if (nb_bytes_read < nb_bytes) {
			Error("%ls: could not load all file data.", fname);
			return E_FAIL;
		}
	
		return S_OK;
	}

	//-------------------------------------------------------------------------
	// BinaryReader
	//-------------------------------------------------------------------------

	HRESULT BinaryReader::ReadFromFile(const wstring &fname, bool big_endian) {
		m_fname = fname;
		m_big_endian = big_endian;

		size_t nb_bytes;
		const HRESULT result_read = ReadBinaryFile(fname.c_str(), m_data, &nb_bytes);
		if (FAILED(result_read)) {
			Error("%ls: failed to read binary file.", fname.c_str());
			return E_FAIL;
		}

		m_pos = m_data.get();
		m_end = m_data.get() + nb_bytes;
		return Read();
	}
	HRESULT BinaryReader::ReadFromMemory(const uint8_t *input, size_t size, bool big_endian) {
		m_fname = L"input string";
		m_big_endian = big_endian;

		if (m_end < m_pos) {
			Error("%ls: overflow.", GetFilename().c_str());
			return E_FAIL;
		}

		m_pos = input;
		m_end = input + size;
		return Read();
	}

	const char *BinaryReader::ReadChars(size_t size) {
		const uint8_t *new_pos = m_pos + size;
		if (new_pos < m_pos) {
			Error("%ls: overflow: no chars value found.", GetFilename().c_str());
			return 0;
		}
		if (m_end < new_pos) {
			Error("%ls: end of file: no chars value found.", GetFilename().c_str());
			return 0;
		}

		const char *result = reinterpret_cast< const char * >(m_pos);
		m_pos = new_pos;
		return result;
	}
	int8_t BinaryReader::ReadInt8() {
		const uint8_t *new_pos = m_pos + sizeof(int8_t);
		if (new_pos < m_pos) {
			Error("%ls: overflow: no int8_t value found.", GetFilename().c_str());
			return 0;
		}
		if (m_end < new_pos) {
			Error("%ls: end of file: no int8_t value found.", GetFilename().c_str());
			return 0;
		}

		const int8_t result = BytesToInt8(m_pos);
		m_pos = new_pos;
		return result;
	}
	uint8_t BinaryReader::ReadUInt8() {
		const uint8_t *new_pos = m_pos + sizeof(uint8_t);
		if (new_pos < m_pos) {
			Error("%ls: overflow: no uint8_t value found.", GetFilename().c_str());
			return 0;
		}
		if (m_end < new_pos) {
			Error("%ls: end of file: no uint8_t value found.", GetFilename().c_str());
			return 0;
		}

		const uint8_t result = BytesToUInt8(m_pos);
		m_pos = new_pos;
		return result;
	}
	int16_t BinaryReader::ReadInt16() {
		const uint8_t *new_pos = m_pos + sizeof(int16_t);
		if (new_pos < m_pos) {
			Error("%ls: overflow: no int16_t value found.", GetFilename().c_str());
			return 0;
		}
		if (m_end < new_pos) {
			Error("%ls: end of file: no int16_t value found.", GetFilename().c_str());
			return 0;
		}

		const int16_t result = BytesToInt16(m_pos, m_big_endian);
		m_pos = new_pos;
		return result;
	}
	uint16_t BinaryReader::ReadUInt16() {
		const uint8_t *new_pos = m_pos + sizeof(uint16_t);
		if (new_pos < m_pos) {
			Error("%ls: overflow: no uint16_t value found.", GetFilename().c_str());
			return 0;
		}
		if (m_end < new_pos) {
			Error("%ls: end of file: no uint16_t value found.", GetFilename().c_str());
			return 0;
		}

		const uint16_t result = BytesToUInt16(m_pos, m_big_endian);
		m_pos = new_pos;
		return result;
	}
	int32_t BinaryReader::ReadInt32() {
		const uint8_t *new_pos = m_pos + sizeof(int32_t);
		if (new_pos < m_pos) {
			Error("%ls: overflow: no int32_t value found.", GetFilename().c_str());
			return 0;
		}
		if (m_end < new_pos) {
			Error("%ls: end of file: no int32_t value found.", GetFilename().c_str());
			return 0;
		}

		const int32_t result = BytesToInt32(m_pos, m_big_endian);
		m_pos = new_pos;
		return result;
	}
	uint32_t BinaryReader::ReadUInt32() {
		const uint8_t *new_pos = m_pos + sizeof(uint32_t);
		if (new_pos < m_pos) {
			Error("%ls: overflow: no uint32_t value found.", GetFilename().c_str());
			return 0;
		}
		if (m_end < new_pos) {
			Error("%ls: end of file: no uint32_t value found.", GetFilename().c_str());
			return 0;
		}

		const uint32_t result = BytesToUInt32(m_pos, m_big_endian);
		m_pos = new_pos;
		return result;
	}
	int64_t BinaryReader::ReadInt64() {
		const uint8_t *new_pos = m_pos + sizeof(int64_t);
		if (new_pos < m_pos) {
			Error("%ls: overflow: no int64_t value found.", GetFilename().c_str());
			return 0;
		}
		if (m_end < new_pos) {
			Error("%ls: end of file: no int64_t value found.", GetFilename().c_str());
			return 0;
		}

		const int64_t result = BytesToInt64(m_pos, m_big_endian);
		m_pos = new_pos;
		return result;
	}
	uint64_t BinaryReader::ReadUInt64() {
		const uint8_t *new_pos = m_pos + sizeof(uint64_t);
		if (new_pos < m_pos) {
			Error("%ls: overflow: no uint64_t value found.", GetFilename().c_str());
			return 0;
		}
		if (m_end < new_pos) {
			Error("%ls: end of file: no uint64_t value found.", GetFilename().c_str());
			return 0;
		}

		const uint64_t result = BytesToUInt64(m_pos, m_big_endian);
		m_pos = new_pos;
		return result;
	}
	float BinaryReader::ReadFloat() {
		const uint8_t *new_pos = m_pos + sizeof(float);
		if (new_pos < m_pos) {
			Error("%ls: overflow: no float value found.", GetFilename().c_str());
			return 0.0f;
		}
		if (m_end < new_pos) {
			Error("%ls: end of file: no float value found.", GetFilename().c_str());
			return 0.0f;
		}

		const float result = BytesToFloat(m_pos, m_big_endian);
		m_pos = new_pos;
		return result;
	}
	double BinaryReader::ReadDouble() {
		const uint8_t *new_pos = m_pos + sizeof(double);
		if (new_pos < m_pos) {
			Error("%ls: overflow: no double value found.", GetFilename().c_str());
			return 0.0;
		}
		if (m_end < new_pos) {
			Error("%ls: end of file: no double value found.", GetFilename().c_str());
			return 0.0;
		}

		const double result = BytesToDouble(m_pos, m_big_endian);
		m_pos = new_pos;
		return result;
	}

	//-------------------------------------------------------------------------
	// BigEndianBinaryReader
	//-------------------------------------------------------------------------

	HRESULT BigEndianBinaryReader::ReadFromFile(const wstring &fname) {
		m_fname = fname;

		size_t nb_bytes;
		const HRESULT result_read = ReadBinaryFile(fname.c_str(), m_data, &nb_bytes);
		if (FAILED(result_read)) {
			Error("%ls: failed to read binary file.", fname.c_str());
			return E_FAIL;
		}

		m_pos = m_data.get();
		m_end = m_data.get() + nb_bytes;
		return Read();
	}
	HRESULT BigEndianBinaryReader::ReadFromMemory(const uint8_t *input, size_t size) {
		m_fname = L"input string";

		if (m_end < m_pos) {
			Error("%ls: overflow.", GetFilename().c_str());
			return E_FAIL;
		}

		m_pos = input;
		m_end = input + size;
		return Read();
	}
}