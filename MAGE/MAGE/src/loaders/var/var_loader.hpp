#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "utils\collection\collection.hpp" 
#include "scripting\variable.hpp"

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
					A reference to a vector containing the variables.
	 @throws		FormattedException
					Failed to import the variable script from file.
	 */
	void ImportVARFromFile(const wstring &fname, 
		vector< Variable > &variable_buffer);

	/**
	 Exports the given variables to the given VAR file.

	 @param[in]		fname
					A reference to the VAR filename.
	 @param[in]		variable_buffer
					A reference to a vector containing the variables.
	 @throws		FormattedException
					Failed to export the variable script to file.
	 */
	void ExportVARToFile(const wstring &fname, 
		const vector< Variable > &variable_buffer);
}