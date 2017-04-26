#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "collection\collection.hpp" 
#include "scripting\variable.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 Imports the variables from the given VS file.

	 @param[in]		fname
					A reference to the VS filename.
	 @param[in,out]	variable_buffer
					A reference to a vector containing the variables.
	 @throws		FormattedException
					Failed to import the variable script from file.
	 */
	void ImportVSFromFile(const wstring &fname, vector< Variable > &variable_buffer);

	/**
	 Exports the given variables to the given VS file.

	 @param[in]		fname
					A reference to the VS filename.
	 @param[in]		variable_buffer
					A reference to a vector containing the variables.
	 @throws		FormattedException
					Failed to export the variable script to file.
	 */
	void ExportVSToFile(const wstring &fname, const vector< Variable > &variable_buffer);
}