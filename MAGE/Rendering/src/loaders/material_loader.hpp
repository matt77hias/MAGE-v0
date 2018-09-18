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
	 Imports the materials from the file associated with the given path.

	 @param[in]		path
					A reference to the path.
	 @param[in]		resource_manaer
					A reference to the resource manager.
	 @param[out]	materials
					A reference to a vector containing the materials.
	 @throws		Exception
					Failed to import the materials from file.
	 */
	void ImportMaterialFromFile(const std::filesystem::path& path, 
								ResourceManager &resource_manaer, 
		                        std::vector< Material >& materials);
}