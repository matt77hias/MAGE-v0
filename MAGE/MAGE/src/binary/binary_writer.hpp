#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "platform\windows.hpp"
#include "string\string.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	class BigEndianBinaryWriter {

	public:

		//---------------------------------------------------------------------
		// Destructors
		//---------------------------------------------------------------------

		virtual ~BigEndianBinaryWriter() = default;

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		BigEndianBinaryWriter &operator=(const BigEndianBinaryWriter &reader) = delete;
		BigEndianBinaryWriter &operator=(BigEndianBinaryWriter &&reader) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		HRESULT WriteToFile(const wstring &fname);

		const wstring &GetFilename() const {
			return m_fname;
		}

	protected:

		//---------------------------------------------------------------------
		// Constructors
		//---------------------------------------------------------------------

		BigEndianBinaryWriter()
			: m_file(nullptr), m_fname() {}
		BigEndianBinaryWriter(const BigEndianBinaryWriter &reader) = delete;
		BigEndianBinaryWriter(BigEndianBinaryWriter &&reader) = default;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		template< typename DataT >
		void WriteValue(const DataT &data);
		template< typename DataT >
		void WriteValueArray(const DataT *data, size_t count);
		void WriteCharacter(char c);
		void WriteString(const char *str);
		void WriteString(const string &str) {
			WriteString(str.c_str());
		}

	private:

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		virtual HRESULT Write() = 0;

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		FILE *m_file;
		wstring m_fname;
	};
}

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "binary\binary_writer.tpp"

#pragma endregion