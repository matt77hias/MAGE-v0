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

		Writer() 
			: m_file(nullptr), m_fname() {}
		Writer(const Writer &reader) = delete;
		Writer(Writer &&reader) = default;
		virtual ~Writer() = default;

		Writer &operator=(const Writer &reader) = delete;
		Writer &operator=(Writer &&reader) = delete;

		HRESULT WriteToFile(const wstring &fname);

		const wstring &GetFilename() const {
			return m_fname;
		}

	protected:

		virtual HRESULT Write() const = 0;
		void Write(char c) const;
		void Write(const char *str) const;
		void WriteLine(const char *str) const;

	private:

		FILE *m_file;
		wstring m_fname;
	};
}