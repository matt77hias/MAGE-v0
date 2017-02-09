#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "scripting\variable_script.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 Imports the given variable script from its associated file.

	 @param[in]		fname
					A reference to the filename.
	 @param[in,out]	variable_script
					A reference to the variable script to import to.
	 @return		A success/error value.
	 */
	HRESULT ImportVariableScriptFromFile(const wstring &fname, VariableScript &variable_script);

	/**
	 Exports the given variable script to the file with the given filename.

	 @param[in]		fname
					A reference to the filename.
	 @param[in,out]	variable_script
					A reference to the variable script to export from.
	 @return		A success/error value.
	 */
	HRESULT ExportVariableScriptToFile(const wstring &fname, const VariableScript &variable_script);
}