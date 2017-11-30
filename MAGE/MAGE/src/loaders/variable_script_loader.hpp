#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "scripting\variable.hpp"
#include "utils\collection\collection.hpp" 

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 Imports the variables from the given file.

	 @param[in]		fname
					A reference to the filename.
	 @param[in,out]	variable_buffer
					A reference to a map containing the variables.
	 @throws		FormattedException
					Failed to import the variable script from file.
	 */
	void ImportVariableScriptFromFile(const wstring &fname, 
		map< string, Value > &variable_buffer);

	/**
	 Exports the given variables to the given file.

	 @param[in]		fname
					A reference to the filename.
	 @param[in]		variable_buffer
					A reference to a map containing the variables.
	 @throws		FormattedException
					Failed to export the variable script to file.
	 */
	void ExportVariableScriptToFile(const wstring &fname, 
		const map< string, Value > &variable_buffer);
}