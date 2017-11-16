#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "material\material.hpp"
#include "utils\collection\collection.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 Imports the materials from the given file.

	 @param[in]		fname
					A reference to the filename.
	 @param[out]	materials
					A reference to a vector containing the materials.
	 @throws		FormattedException
					Failed to import the materials from file.
	 */
	void ImportMaterialFromFile(const wstring &fname, 
		vector< Material > &materials);
}