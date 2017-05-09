#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "shader\bump_shader.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	//-------------------------------------------------------------------------
	// Factory Methods
	//-------------------------------------------------------------------------

	/**
	 Creates a diffuse bump shader.

	 @pre			The current engine must be loaded.
	 @return		The diffuse bump shader.
	 @throws		FormattedException
					Failed to create the shader.
	 */
	const CombinedShader CreateDiffuseBumpShader();

	/**
	 Creates a Lambertian bump shader.

	 @pre			The current engine must be loaded.
	 @return		The Lambertian bump shader.
	 @throws		FormattedException
					Failed to create the shader.
	 */
	const CombinedShader CreateLambertianBumpShader();

	/**
	 Creates a Phong bump shader.

	 @pre			The current engine must be loaded.
	 @return		The Phong bump shader.
	 @throws		FormattedException
					Failed to create the shader.
	 */
	const CombinedShader CreatePhongBumpShader();

	/**
	 Creates a Blinn-Phong bump shader.

	 @pre			The current engine must be loaded.
	 @return		The Blinn-Phong bump shader.
	 @throws		FormattedException
					Failed to create the shader.
	 */
	const CombinedShader CreateBlinnPhongBumpShader();

	/**
	 Creates a Modified Blinn-Phong bump shader.

	 @pre			The current engine must be loaded.
	 @return		The Modified Blinn-Phong bump shader.
	 @throws		FormattedException
					Failed to create the shader.
	 */
	const CombinedShader CreateModifiedBlinnPhongBumpShader();
}