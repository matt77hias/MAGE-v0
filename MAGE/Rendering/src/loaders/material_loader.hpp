#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "resource\model\material.hpp"

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
namespace mage::rendering {
	// Forward declaration.
	class ResourceManager;
}

namespace mage::rendering::loader {

	/**
	 Imports the materials from the given file.

	 @param[in]		fname
					A reference to the filename.
	 @param[in]		resource_manaer
					A reference to the resource manager.
	 @param[out]	materials
					A reference to a vector containing the materials.
	 @throws		Exception
					Failed to import the materials from file.
	 */
	void ImportMaterialFromFile(const wstring& fname, 
								ResourceManager &resource_manaer, 
		                        std::vector< Material >& materials);
}