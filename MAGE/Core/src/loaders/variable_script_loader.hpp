#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "resource\script\variable_value.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// System Includes
//-----------------------------------------------------------------------------
#pragma region

#include <map>

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage::loader {

	/**
	 Imports the variables from the given file.

	 @param[in]		fname
					A reference to the filename.
	 @param[out]	variable_buffer
					A reference to a map containing the variables.
	 @throws		Exception
					Failed to import the variable script from file.
	 */
	void ImportVariableScriptFromFile(const wstring& fname, 
									  std::map< string, Value >& 
									  variable_buffer);

	/**
	 Exports the given variables to the given file.

	 @param[in]		fname
					A reference to the filename.
	 @param[in]		variable_buffer
					A reference to a map containing the variables.
	 @throws		Exception
					Failed to export the variable script to file.
	 */
	void ExportVariableScriptToFile(const wstring& fname, 
									const std::map< string, Value >& 
									variable_buffer);
}