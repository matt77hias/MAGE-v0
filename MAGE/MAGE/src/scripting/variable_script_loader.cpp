//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "scripting\variable_script_loader.hpp"
#include "scripting\vs\vs_loader.hpp"
#include "logging\error.hpp"
#include "file\file_utils.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	HRESULT ImportVariableScriptFromFile(const wstring &fname, vector< Variable * > &variable_buffer) {
		const wstring extension = GetFileExtension(fname);

		if (extension == L"vs" || extension == L"VS") {
			return ImportVSFromFile(fname, variable_buffer);
		}

		Warning("Unknown variable script file extension: %ls", fname.c_str());
		return E_FAIL;
	}

	HRESULT ExportVariableScriptToFile(const wstring &fname, const vector< Variable * > &variable_buffer) {
		const wstring extension = GetFileExtension(fname);

		if (extension == L"vs" || extension == L"VS") {
			return ExportVSToFile(fname, variable_buffer);
		}

		Warning("Unknown variable script file extension: %ls", fname.c_str());
		return E_FAIL;
	}
}