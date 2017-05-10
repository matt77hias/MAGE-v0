#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "shader\basic_shader.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations
//-----------------------------------------------------------------------------
namespace mage {

	//-------------------------------------------------------------------------
	// Factory Methods
	//-------------------------------------------------------------------------

	/**
	 Creates a diffuse shader.

	 @pre			The current engine must be loaded.
	 @return		The diffuse shader.
	 @throws		FormattedException
					Failed to create the shader.
	 */
	const CombinedShader CreateDiffuseShader();

	/**
	 Creates a Lambertian shader.

	 @pre			The current engine must be loaded.
	 @return		The Lambertian shader.
	 @throws		FormattedException
					Failed to create the shader.
	 */
	const CombinedShader CreateLambertianShader();

	/**
	 Creates a Phong shader.

	 @pre			The current engine must be loaded.
	 @return		The Phong shader.
	 @throws		FormattedException
					Failed to create the shader.
	 */
	const CombinedShader CreatePhongShader();

	/**
	 Creates a Modified Phong shader.

	 @pre			The current engine must be loaded.
	 @return		The Modified Phong shader.
	 @throws		FormattedException
					Failed to create the shader.
	 */
	const CombinedShader CreateModifiedPhongShader();

	/**
	 Creates a Blinn-Phong shader.

	 @pre			The current engine must be loaded.
	 @return		The Blinn-Phong shader.
	 @throws		FormattedException
					Failed to create the shader.
	 */
	const CombinedShader CreateBlinnPhongShader();

	/**
	 Creates a Modified Blinn-Phong shader.

	 @pre			The current engine must be loaded.
	 @return		The Modified Blinn-Phong shader.
	 @throws		FormattedException
					Failed to create the shader.
	 */
	const CombinedShader CreateModifiedBlinnPhongShader();
}