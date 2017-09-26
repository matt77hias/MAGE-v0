//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "scripting\variable_script_loader.hpp"
#include "scripting\vs\vs_loader.hpp"
#include "file\file_utils.hpp"
#include "logging\exception.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	void ImportVariableScriptFromFile(const wstring &fname, 
		vector< Variable > &variable_buffer) {
		
		const wstring extension = GetFileExtension(fname);

		if (extension == L"vs" || extension == L"VS") {
			ImportVSFromFile(fname, variable_buffer);
		}
		else {
			throw FormattedException(
				"Unknown variable script file extension: %ls", fname.c_str());
		}
	}

	void ExportVariableScriptToFile(const wstring &fname, 
		const vector< Variable > &variable_buffer) {
		
		const wstring extension = GetFileExtension(fname);

		if (extension == L"vs" || extension == L"VS") {
			ExportVSToFile(fname, variable_buffer);
		}
		else {
			throw FormattedException(
				"Unknown variable script file extension: %ls", fname.c_str());
		}
	}
}