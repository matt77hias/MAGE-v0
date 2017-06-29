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
	SharedPtr< Texture > CreateBlackTexture();

	/**
	 Creates a white texture.

	 @pre			The current engine must be loaded.
	 @pre			The standard assets must be present.
	 @return		A pointer to the texture.
	 @throws		FormattedException
					Failed to create the texture.
	 */
	SharedPtr< Texture > CreateWhiteTexture();

	/**
	 Creates a red texture.

	 @pre			The current engine must be loaded.
	 @pre			The standard assets must be present.
	 @return		A pointer to the texture.
	 @throws		FormattedException
					Failed to create the texture.
	 */
	SharedPtr< Texture > CreateRedTexture();

	/**
	 Creates a green texture.

	 @pre			The current engine must be loaded.
	 @pre			The standard assets must be present.
	 @return		A pointer to the texture.
	 @throws		FormattedException
					Failed to create the texture.
	 */
	SharedPtr< Texture > CreateGreenTexture();

	/**
	 Creates a blue texture.

	 @pre			The current engine must be loaded.
	 @pre			The standard assets must be present.
	 @return		A pointer to the texture.
	 @throws		FormattedException
					Failed to create the texture.
	 */
	SharedPtr< Texture > CreateBlueTexture();
}