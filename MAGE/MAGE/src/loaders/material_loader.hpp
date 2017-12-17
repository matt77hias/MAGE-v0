#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "material\material.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// System Includes
//-----------------------------------------------------------------------------
#pragma region

#include <vector>

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations
//-----------------------------------------------------------------------------
namespace mage::loader {

	/**
	 Imports the materials from the given file.

	 @param[in]		fname
					A reference to the filename.
	 @param[out]	materials
					A reference to a vector containing the materials.
	 @throws		Exception
					Failed to import the materials from file.
	 */
	void ImportMaterialFromFile(const wstring &fname, 
		std::vector< Material > &materials);
}