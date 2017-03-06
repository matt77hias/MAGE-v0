#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "platform\windows.hpp"
#include "collection\collection.hpp" 
#include "scripting\variable.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 Imports the variables from the given VS file.

	 @param[in]		fname
					A reference to the VS filename.
	 @param[in,out]	variable_buffer
					A reference to a vector containing the variables.
	 @return		A success/error value.
	 */
	HRESULT ImportVSFromFile(const wstring &fname, vector< Variable * > &variable_buffer);

	/**
	 Exports the given variables to the given VS file.

	 @param[in]		fname
					A reference to the VS filename.
	 @param[in]		variable_buffer
					A reference to a vector containing the variables.
	 @return		A success/error value.
	 */
	HRESULT ExportVSToFile(const wstring &fname, const vector< Variable * > &variable_buffer);
}