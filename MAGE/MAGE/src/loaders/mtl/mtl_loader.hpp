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
	 Imports the materials from the given MTL file.

	 @param[in]		fname
					A reference to the MTL filename.
	 @param[out]	materials
					A reference to a vector containing the materials.
	 @throws		Exception
					Failed to import the mesh from file.
	 */
	void ImportMTLMaterialFromFile(const wstring &fname, 
		                           std::vector< Material > &materials);
}