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
namespace mage::rendering {

	/**
	 Creates a default material.

	 @param[in,out]	resource_manager
					A reference to the resource manager.
	 @return		The material.
	 @throws		Exception
					Failed to create the material.
	 */
	const Material CreateDefaultMaterial(ResourceManager& resource_manager);
}