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
	 Imports the materials from the given MTL file.

	 @param[in]		fname
					A reference to the MTL filename.
	 @param[out]	materials
					A reference to a vector containing the materials.
	 @throws		FormattedException
					Failed to import the mesh from file.
	 */
	void ImportMTLMaterialFromFile(const wstring &fname, 
		vector< Material > &materials);
}