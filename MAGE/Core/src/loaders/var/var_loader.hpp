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

#include <filesystem>
#include <map>

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations
//-----------------------------------------------------------------------------
namespace mage::loader {

	/**
	 Imports the variables from the VAR file associated with the given path.

	 @param[in]		path
					A reference to the path.
	 @param[out]	variable_buffer
					A reference to a map containing the variables.
	 @throws		Exception
					Failed to import the variable script from file.
	 */
	void ImportVARFromFile(const std::filesystem::path& path, 
		                   std::map< string, Value >& variable_buffer);

	/**
	 Exports the given variables to the VAR file associated with the given 
	 path.

	 @param[in]		path
					A reference to the path.
	 @param[in]		variable_buffer
					A reference to a map containing the variables.
	 @throws		Exception
					Failed to export the variable script to file.
	 */
	void ExportVARToFile(const std::filesystem::path& path, 
		                 const std::map< string, Value >& variable_buffer);
}