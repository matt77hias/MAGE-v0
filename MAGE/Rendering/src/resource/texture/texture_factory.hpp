#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "resource\texture\texture.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations
//-----------------------------------------------------------------------------
namespace mage::rendering {

	// Forward declaration.
	class ResourceManager;

	//-------------------------------------------------------------------------
	// Factory Methods: Flat
	//-------------------------------------------------------------------------
	#pragma region

	/**
	 Creates a black texture.

	 @param[in]		resource_manager
					A reference to the resource manager.
	 @return		A pointer to the texture.
	 @throws		Exception
					Failed to create the texture.
	 */
	TexturePtr CreateBlackTexture(ResourceManager& resource_manager);

	/**
	 Creates a white texture.

	 @param[in]		resource_manager
					A reference to the resource manager.
	 @return		A pointer to the texture.
	 @throws		Exception
					Failed to create the texture.
	 */
	TexturePtr CreateWhiteTexture(ResourceManager& resource_manager);

	/**
	 Creates a red texture.

	 @param[in]		resource_manager
					A reference to the resource manager.
	 @return		A pointer to the texture.
	 @throws		Exception
					Failed to create the texture.
	 */
	TexturePtr CreateRedTexture(ResourceManager& resource_manager);

	/**
	 Creates a green texture.

	 @param[in]		resource_manager
					A reference to the resource manager.
	 @return		A pointer to the texture.
	 @throws		Exception
					Failed to create the texture.
	 */
	TexturePtr CreateGreenTexture(ResourceManager& resource_manager);

	/**
	 Creates a blue texture.

	 @param[in]		resource_manager
					A reference to the resource manager.
	 @return		A pointer to the texture.
	 @throws		Exception
					Failed to create the texture.
	 */
	TexturePtr CreateBlueTexture(ResourceManager& resource_manager);

	#pragma endregion

	//-------------------------------------------------------------------------
	// Factory Methods: Miscellaneous
	//-------------------------------------------------------------------------
	#pragma region

	/**
	 Creates a MAGE texture.

	 @param[in]		resource_manager
					A reference to the resource manager.
	 @return		A pointer to the texture.
	 @throws		Exception
					Failed to create the texture.
	 */
	TexturePtr CreateMAGETexture(ResourceManager& resource_manager);

	/**
	 Creates a reference texture.

	 @param[in]		resource_manager
					A reference to the resource manager.
	 @return		A pointer to the texture.
	 @throws		Exception
					Failed to create the texture.
	 */
	TexturePtr CreateReferenceTexture(ResourceManager& resource_manager);

	#pragma endregion
}