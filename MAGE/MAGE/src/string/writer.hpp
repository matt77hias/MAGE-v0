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

	class Writer {

	public:

		//---------------------------------------------------------------------
		// Destructors
		//---------------------------------------------------------------------

		virtual ~Writer() = default;

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		Writer &operator=(const Writer &reader) = delete;
		Writer &operator=(Writer &&reader) = delete;

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

		Writer()
			: m_file(nullptr), m_fname() {}
		Writer(const Writer &reader) = delete;
		Writer(Writer &&reader) = default;

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
		void WriteStringLine(const char *str);
		void WriteStringLine(const string &str) {
			WriteStringLine(str.c_str());
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

#include "string\writer.tpp"

#pragma endregion