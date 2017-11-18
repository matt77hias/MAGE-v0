//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "loaders\variable_script_loader.hpp"
#include "loaders\var\var_loader.hpp"
#include "utils\file\file_utils.hpp"
#include "utils\exception\exception.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	void ImportVariableScriptFromFile(const wstring &fname, 
		vector< Variable > &variable_buffer) {
		
		const wstring extension = GetFileExtension(fname);

		if (extension == L"var" || extension == L"VAR") {
			ImportVARFromFile(fname, variable_buffer);
		}
		else {
			throw FormattedException(
				"Unknown variable script file extension: %ls", fname.c_str());
		}
	}

	void ExportVariableScriptToFile(const wstring &fname, 
		const vector< Variable > &variable_buffer) {
		
		const wstring extension = GetFileExtension(fname);

		if (extension == L"var" || extension == L"VAR") {
			ExportVARToFile(fname, variable_buffer);
		}
		else {
			throw FormattedException(
				"Unknown variable script file extension: %ls", fname.c_str());
		}
	}
}