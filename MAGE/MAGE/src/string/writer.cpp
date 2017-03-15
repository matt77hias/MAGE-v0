//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "string\writer.hpp"
#include "logging\error.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	HRESULT Writer::WriteToFile(const wstring &fname) {
		m_fname = fname;

		const errno_t result_fopen_s = _wfopen_s(&m_file, GetFilename().c_str(), L"w");
		if (result_fopen_s) {
			Error("%ls: could not open file.", GetFilename().c_str());
			return E_FAIL;
		}

		const HRESULT result_write = Write();
		
		// Close the script file.
		fclose(m_file);
		m_file = nullptr;

		return result_write;
	}

	void Writer::Write(char c) const {
		fputc(c, m_file);
	}
	
	void Writer::Write(const char *str) const {
		fputs(str, m_file);
	}
	
	void Writer::WriteLine(const char *str) const {
		Write(str);
		Write('\n');
	}
}