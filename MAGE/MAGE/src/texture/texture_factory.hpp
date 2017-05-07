#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "texture\texture.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 Creates a black texture.

	 @pre			The current engine must be loaded.
	 @pre			The standard assets must be present.
	 @return		A pointer to the texture.
	 @throws		FormattedException
					Failed to create the texture.
	 */
	inline SharedPtr< Texture > CreateBlackTexture() {
		return CreateTexture(L"assets/sprites/black.dds");
	}

	/**
	 Creates a white texture.

	 @pre			The current engine must be loaded.
	 @pre			The standard assets must be present.
	 @return		A pointer to the texture.
	 @throws		FormattedException
					Failed to create the texture.
	 */
	inline SharedPtr< Texture > CreateWhiteTexture() {
		return CreateTexture(L"assets/sprites/white.dds");
	}
}