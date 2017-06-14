#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "shader\tsnm_shader.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations
//-----------------------------------------------------------------------------
namespace mage {

	//-------------------------------------------------------------------------
	// Factory Methods
	//-------------------------------------------------------------------------

	/**
	 Creates a Lambertian tsnm shader.

	 @pre			The current engine must be loaded.
	 @return		The Lambertian tsnm shader.
	 @throws		FormattedException
					Failed to create the shader.
	 */
	const CombinedShader CreateLambertianTSNMShader();

	/**
	 Creates a Phong tsnm shader.

	 @pre			The current engine must be loaded.
	 @return		The Phong tsnm shader.
	 @throws		FormattedException
					Failed to create the shader.
	 */
	const CombinedShader CreatePhongTSNMShader();

	/**
	 Creates a Modified Phong tsnm shader.

	 @pre			The current engine must be loaded.
	 @return		The Modified Phong tsnm shader.
	 @throws		FormattedException
					Failed to create the shader.
	 */
	const CombinedShader CreateModifiedPhongTSNMShader();

	/**
	 Creates a Blinn-Phong tsnm shader.

	 @pre			The current engine must be loaded.
	 @return		The Blinn-Phong tsnm shader.
	 @throws		FormattedException
					Failed to create the shader.
	 */
	const CombinedShader CreateBlinnPhongTSNMShader();

	/**
	 Creates a Modified Blinn-Phong tsnm shader.

	 @pre			The current engine must be loaded.
	 @return		The Modified Blinn-Phong tsnm shader.
	 @throws		FormattedException
					Failed to create the shader.
	 */
	const CombinedShader CreateModifiedBlinnPhongTSNMShader();

	/**
	 Creates a Ward tsnm shader.

	 @pre			The current engine must be loaded.
	 @return		The Ward tsnm shader.
	 @throws		FormattedException
					Failed to create the shader.
	 */
	const CombinedShader CreateWardTSNMShader();

	/**
	 Creates a Ward-Duer tsnm shader.

	 @pre			The current engine must be loaded.
	 @return		The Ward-Duer tsnm shader.
	 @throws		FormattedException
					Failed to create the shader.
	 */
	const CombinedShader CreateWardDuerTSNMShader();

	/**
	 Creates a Cook-Torrance tsnm shader.

	 @pre			The current engine must be loaded.
	 @return		The Cook-Torrance tsnm shader.
	 @throws		FormattedException
					Failed to create the shader.
	 */
	const CombinedShader CreateCookTorranceTSNMShader();
}