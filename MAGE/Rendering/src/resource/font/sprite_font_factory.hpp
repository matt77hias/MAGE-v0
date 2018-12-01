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

	//-------------------------------------------------------------------------
	// Factory Methods: Miscellaneous
	//-------------------------------------------------------------------------
	#pragma region

	/**
	 Creates a consolas sprite font.

	 @param[in,out]	resource_manager
					A reference to the resource manager.
	 @return		A pointer to the sprite font.
	 @throws		Exception
					Failed to create the sprite font.
	 */
	SpriteFontPtr CreateConsolasFont(ResourceManager& resource_manager);

	#pragma endregion
}