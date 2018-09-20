#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "resource\rendering_resource_manager.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations
//-----------------------------------------------------------------------------
namespace mage::rendering::loader {

	/**
	 Imports the materials from the MTL file associated with the given path.

	 @param[in]		path
					A reference to the path.
	 @param[in]		resource_manager
					A reference to the resource manager.
	 @param[out]	materials
					A reference to a vector containing the materials.
	 @throws		Exception
					Failed to import the mesh from file.
	 */
	void ImportMTLMaterialFromFile(const std::filesystem::path& path,
								   ResourceManager& resource_manager,
		                           std::vector< Material >& materials);
}