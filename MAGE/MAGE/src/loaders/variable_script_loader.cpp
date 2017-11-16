//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "loaders\variable_script_loader.hpp"
#include "loaders\vs\vs_loader.hpp"
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