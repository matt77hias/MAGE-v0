#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "memory\memory.hpp"
#include "string\string.hpp"
#include "binary\binary_utils.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	HRESULT ReadBinaryFile(const wchar_t *fname, UniquePtr< uint8_t[] > &data, size_t *size);

	//-------------------------------------------------------------------------
	// BinaryReader
	//-------------------------------------------------------------------------

	class BinaryReader {

	public:

		//---------------------------------------------------------------------
		// Destructors
		//---------------------------------------------------------------------

		virtual ~BinaryReader() = default;

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------	

		BinaryReader &operator=(const BinaryReader &reader) = delete;
		BinaryReader &operator=(BinaryReader &&reader) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		HRESULT ReadFromFile(const wstring &fname, bool big_endian);
		HRESULT ReadFromMemory(const uint8_t *input, size_t size, bool big_endian);

		const wstring &GetFilename() const {
			return m_fname;
		}
		
	protected:

		//---------------------------------------------------------------------
		// Constructors
		//---------------------------------------------------------------------

		BinaryReader()
			: m_fname(), m_big_endian(true), 
			m_pos(nullptr), m_end(nullptr), m_data() {}
		BinaryReader(const BinaryReader &reader) = delete;
		BinaryReader(BinaryReader &&reader) = default;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		bool HasCharsLeft() const {
			return m_pos < m_end;
		}

		const char *ReadChars(size_t size);
		int8_t ReadInt8();
		uint8_t ReadUInt8();
		int16_t ReadInt16();
		uint16_t ReadUInt16();
		int32_t ReadInt32();
		uint32_t ReadUInt32();
		int64_t ReadInt64();
		uint64_t ReadUInt64();
		float ReadFloat();
		double ReadDouble();

	private:

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		virtual HRESULT Read() = 0;

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		wstring m_fname;
		bool m_big_endian;
		const uint8_t *m_pos;
		const uint8_t *m_end;
		UniquePtr< uint8_t[] > m_data;
	};

	//-------------------------------------------------------------------------
	// BigEndianBinaryReader
	//-------------------------------------------------------------------------

	class BigEndianBinaryReader {

	public:

		//---------------------------------------------------------------------
		// Destructors
		//---------------------------------------------------------------------

		virtual ~BigEndianBinaryReader() = default;

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------	

		BigEndianBinaryReader &operator=(const BigEndianBinaryReader &reader) = delete;
		BigEndianBinaryReader &operator=(BigEndianBinaryReader &&reader) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		HRESULT ReadFromFile(const wstring &fname);
		HRESULT ReadFromMemory(const uint8_t *input, size_t size);

		const wstring &GetFilename() const {
			return m_fname;
		}

	protected:

		//---------------------------------------------------------------------
		// Constructors
		//---------------------------------------------------------------------

		BigEndianBinaryReader()
			: m_fname(), m_pos(nullptr), m_end(nullptr), m_data() {}
		BigEndianBinaryReader(const BigEndianBinaryReader &reader) = delete;
		BigEndianBinaryReader(BigEndianBinaryReader &&reader) = default;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		bool HasCharsLeft() const {
			return m_pos < m_end;
		}

		template< typename ValueT >
		const ValueT &ReadValue();
		template< typename ValueT >
		const ValueT *ReadValueArray(size_t size);
		
	private:

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		virtual HRESULT Read() = 0;

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		wstring m_fname;
		const uint8_t *m_pos;
		const uint8_t *m_end;
		UniquePtr< uint8_t[] > m_data;
	};
}

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "binary\binary_reader.tpp"

#pragma endregion