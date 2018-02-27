#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "type\types.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations
//-----------------------------------------------------------------------------
namespace mage {

	// Forward declarations.
	class Texture;
	class ResourceManager;

	/**
	 Creates a MAGE texture.

	 @pre			@a resource_manager is not equal to @c nullptr.
	 @param[in]		resource_manager
					A pointer to the resource manager.
	 @return		A pointer to the texture.
	 @throws		Exception
					Failed to create the texture.
	 */
	SharedPtr< const Texture > CreateMAGETexture(ResourceManager *resource_manager);

	/**
	 Creates a reference texture.

	 @pre			@a resource_manager is not equal to @c nullptr.
	 @param[in]		resource_manager
					A pointer to the resource manager.
	 @return		A pointer to the texture.
	 @throws		Exception
					Failed to create the texture.
	 */
	SharedPtr< const Texture > CreateReferenceTexture(ResourceManager *resource_manager);

	/**
	 Creates a black texture.

	 @pre			@a resource_manager is not equal to @c nullptr.
	 @param[in]		resource_manager
					A pointer to the resource manager.
	 @return		A pointer to the texture.
	 @throws		Exception
					Failed to create the texture.
	 */
	SharedPtr< const Texture > CreateBlackTexture(ResourceManager *resource_manager);

	/**
	 Creates a white texture.

	 @pre			@a resource_manager is not equal to @c nullptr.
	 @param[in]		resource_manager
					A pointer to the resource manager.
	 @return		A pointer to the texture.
	 @throws		Exception
					Failed to create the texture.
	 */
	SharedPtr< const Texture > CreateWhiteTexture(ResourceManager *resource_manager);

	/**
	 Creates a red texture.

	 @pre			@a resource_manager is not equal to @c nullptr.
	 @param[in]		resource_manager
					A pointer to the resource manager.
	 @return		A pointer to the texture.
	 @throws		Exception
					Failed to create the texture.
	 */
	SharedPtr< const Texture > CreateRedTexture(ResourceManager *resource_manager);

	/**
	 Creates a green texture.

	 @pre			@a resource_manager is not equal to @c nullptr.
	 @param[in]		resource_manager
					A pointer to the resource manager.
	 @return		A pointer to the texture.
	 @throws		Exception
					Failed to create the texture.
	 */
	SharedPtr< const Texture > CreateGreenTexture(ResourceManager *resource_manager);

	/**
	 Creates a blue texture.

	 @pre			@a resource_manager is not equal to @c nullptr.
	 @param[in]		resource_manager
					A pointer to the resource manager.
	 @return		A pointer to the texture.
	 @throws		Exception
					Failed to create the texture.
	 */
	SharedPtr< const Texture > CreateBlueTexture(ResourceManager *resource_manager);
}