#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "scripting\variable.hpp"
#include "utils\collection\collection.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 Imports the variables from the given VAR file.

	 @param[in]		fname
					A reference to the VAR filename.
	 @param[out]	variable_buffer
					A reference to a map containing the variables.
	 @throws		FormattedException
					Failed to import the variable script from file.
	 */
	void ImportVARFromFile(const wstring &fname, 
		map< string, Value > &variable_buffer);

	/**
	 Exports the given variables to the given VAR file.

	 @param[in]		fname
					A reference to the VAR filename.
	 @param[in]		variable_buffer
					A reference to a map containing the variables.
	 @throws		FormattedException
					Failed to export the variable script to file.
	 */
	void ExportVARToFile(const wstring &fname, 
		const map< string, Value > &variable_buffer);
}