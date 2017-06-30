#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "shader\sprite_shader.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations
//-----------------------------------------------------------------------------
namespace mage {

	//-------------------------------------------------------------------------
	// Factory Methods
	//-------------------------------------------------------------------------

	/**
	 Creates a sprite shader.

	 @pre			The current engine must be loaded.
	 @return		The sprite shader.
	 @throws		FormattedException
					Failed to create the shader.
	 */
	const CombinedShader CreateSpriteShader();
}