//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "string\writer.hpp"
#include "logging\error.hpp"
#include "logging\exception.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	Writer::Writer()
		: m_file_stream(nullptr), m_fname() {}

	Writer::Writer(Writer &&writer) = default;

	Writer::~Writer() = default;

	void Writer::WriteToFile(const wstring &fname) {
		m_fname = fname;

		FILE *file;
		{
			const errno_t result = _wfopen_s(&file, GetFilename().c_str(), L"w");
			ThrowIfFailed((0 != result),
				"%ls: could not open file.", GetFilename().c_str());
		}

		m_file_stream.reset(file);

		Write();
	}

	void Writer::WriteCharacter(char c) {
		const int result = fputc(c, m_file_stream.get());
		ThrowIfFailed((EOF == result), 
			"%ls: could not write to file.", GetFilename().c_str());
	}
	
	void Writer::WriteString(const char *str) {
		Assert(str);
		
		const int result = fputs(str, m_file_stream.get());
		ThrowIfFailed((EOF == result),
			"%ls: could not write to file.", GetFilename().c_str());
	}
	
	void Writer::WriteStringLine(const char *str) {
		Assert(str);

		WriteString(str);
		WriteCharacter('\n');
	}
}