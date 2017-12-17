#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "scripting\variable.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// System Includes
//-----------------------------------------------------------------------------
#pragma region

#include <map>

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations
//-----------------------------------------------------------------------------
namespace mage::loader {

	/**
	 Imports the variables from the given VAR file.

	 @param[in]		fname
					A reference to the VAR filename.
	 @param[out]	variable_buffer
					A reference to a map containing the variables.
	 @throws		Exception
					Failed to import the variable script from file.
	 */
	void ImportVARFromFile(const wstring &fname, 
		std::map< string, Value > &variable_buffer);

	/**
	 Exports the given variables to the given VAR file.

	 @param[in]		fname
					A reference to the VAR filename.
	 @param[in]		variable_buffer
					A reference to a map containing the variables.
	 @throws		Exception
					Failed to export the variable script to file.
	 */
	void ExportVARToFile(const wstring &fname, 
		const std::map< string, Value > &variable_buffer);
}