#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "shader\guids.hpp"
#include "shader\shader.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations
//-----------------------------------------------------------------------------
namespace mage {

	//-------------------------------------------------------------------------
	// Factory Methods
	//-------------------------------------------------------------------------

	/**
	 Creates a transform vertex shader.

	 @pre			The resource manager associated with the
					current engine must be loaded.
	 @return		A pointer to the transform vertex shader.
	 @throws		FormattedException
					Failed to create the vertex shader.
	 */
	SharedPtr< const VertexShader > CreateTransformVS();

	/**
	 Creates an emissive pixel shader.

	 @pre			The resource manager associated with the
					current engine must be loaded.
	 @return		A pointer to the emissive pixel shader.
	 @throws		FormattedException
					Failed to create the pixel shader.
	 */
	SharedPtr< const PixelShader > CreateEmissivePS();

	/**
	 Creates a Lambertian pixel shader.

	 @pre			The resource manager associated with the
					current engine must be loaded.
	 @return		A pointer to the Lambertian pixel shader.
	 @throws		FormattedException
					Failed to create the pixel shader.
	 */
	SharedPtr< const PixelShader > CreateLambertianPS();

	/**
	 Creates a Phong pixel shader.

	 @pre			The resource manager associated with the
					current engine must be loaded.
	 @return		A pointer to the Phong pixel shader.
	 @throws		FormattedException
					Failed to create the pixel shader.
	 */
	SharedPtr< const PixelShader > CreatePhongPS();

	/**
	 Creates a Modified Phong pixel shader.

	 @pre			The resource manager associated with the
					current engine must be loaded.
	 @return		A pointer to the Modified Phong pixel shader.
	 @throws		FormattedException
					Failed to create the pixel shader.
	 */
	SharedPtr< const PixelShader > CreateModifiedPhongPS();

	/**
	 Creates a Blinn-Phong pixel shader.

	 @pre			The resource manager associated with the
					current engine must be loaded.
	 @return		A pointer to the Blinn-Phong pixel shader.
	 @throws		FormattedException
					Failed to create the pixel shader.
	 */
	SharedPtr< const PixelShader > CreateBlinnPhongPS();

	/**
	 Creates a Modified Blinn-Phong pixel shader.

	 @pre			The resource manager associated with the
					current engine must be loaded.
	 @return		A pointer to the Modified Blinn-Phong pixel shader.
	 @throws		FormattedException
					Failed to create the pixel shader.
	 */
	SharedPtr< const PixelShader > CreateModifiedBlinnPhongPS();

	/**
	 Creates a Ward pixel shader.

	 @pre			The resource manager associated with the
					current engine must be loaded.
	 @return		A pointer to the Ward pixel shader.
	 @throws		FormattedException
					Failed to create the pixel shader.
	 */
	SharedPtr< const PixelShader > CreateWardPS();

	/**
	 Creates a Ward-Duer pixel shader.

	 @pre			The resource manager associated with the
					current engine must be loaded.
	 @return		A pointer to the Ward-Duer pixel shader.
	 @throws		FormattedException
					Failed to create the pixel shader.
	 */
	SharedPtr< const PixelShader > CreateWardDuerPS();

	/**
	 Creates a Cook-Torrance pixel shader.

	 @pre			The resource manager associated with the
					current engine must be loaded.
	 @return		A pointer to the Cook-Torrance pixel shader.
	 @throws		FormattedException
					Failed to create the pixel shader.
	 */
	SharedPtr< const PixelShader > CreateCookTorrancePS();

	/**
	 Creates a Lambertian tsnm pixel shader.

	 @pre			The resource manager associated with the
					current engine must be loaded.
	 @return		A pointer to the Lambertian tsnm pixel shader.
	 @throws		FormattedException
					Failed to create the pixel shader.
	 */
	SharedPtr< const PixelShader > CreateLambertianTSNMPS();

	/**
	 Creates a Phong tsnm pixel shader.

	 @pre			The resource manager associated with the
					current engine must be loaded.
	 @return		A pointer to the Phong tsnm pixel shader.
	 @throws		FormattedException
					Failed to create the pixel shader.
	 */
	SharedPtr< const PixelShader > CreatePhongTSNMPS();

	/**
	 Creates a Modified Phong tsnm pixel shader.

	 @pre			The resource manager associated with the
					current engine must be loaded.
	 @return		A pointer to the Modified Phong tsnm pixel shader.
	 @throws		FormattedException
					Failed to create the pixel shader.
	 */
	SharedPtr< const PixelShader > CreateModifiedPhongTSNMPS();

	/**
	 Creates a Blinn-Phong tsnm pixel shader.

	 @pre			The resource manager associated with the
					current engine must be loaded.
	 @return		A pointer to the Blinn-Phong tsnm pixel shader.
	 @throws		FormattedException
					Failed to create the pixel shader.
	 */
	SharedPtr< const PixelShader > CreateBlinnPhongTSNMPS();

	/**
	 Creates a Modified Blinn-Phong tsnm pixel shader.

	 @pre			The resource manager associated with the
					current engine must be loaded.
	 @return		A pointer to the Modified Blinn-Phong tsnm pixel shader.
	 @throws		FormattedException
					Failed to create the pixel shader.
	 */
	SharedPtr< const PixelShader > CreateModifiedBlinnPhongTSNMPS();

	/**
	 Creates a Ward tsnm pixel shader.

	 @pre			The resource manager associated with the
					current engine must be loaded.
	 @return		A pointer to the Ward tsnm pixel shader.
	 @throws		FormattedException
					Failed to create the pixel shader.
	 */
	SharedPtr< const PixelShader > CreateWardTSNMPS();

	/**
	 Creates a Ward-Duer tsnm pixel shader.

	 @pre			The resource manager associated with the
					current engine must be loaded.
	 @return		A pointer to the Ward-Duer tsnm pixel shader.
	 @throws		FormattedException
					Failed to create the pixel shader.
	 */
	SharedPtr< const PixelShader > CreateWardDuerTSNMPS();

	/**
	 Creates a Cook-Torrance tsnm pixel shader.

	 @pre			The resource manager associated with the
					current engine must be loaded.
	 @return		A pointer to the Cook-Torrance tsnm pixel shader.
	 @throws		FormattedException
					Failed to create the pixel shader.
	 */
	SharedPtr< const PixelShader > CreateCookTorranceTSNMPS();

	/**
	 Creates a sprite vertex shader.

	 @pre			The resource manager associated with the
					current engine must be loaded.
	 @return		A pointer to the sprite vertex shader.
	 @throws		FormattedException
					Failed to create the vertex shader.
	 */
	SharedPtr< const VertexShader > CreateSpriteVS();

	/**
	 Creates a sprite pixel shader.

	 @pre			The resource manager associated with the
					current engine must be loaded.
	 @return		A pointer to the sprite pixel shader.
	 @throws		FormattedException
					Failed to create the pixel shader.
	 */
	SharedPtr< const PixelShader > CreateSpritePS();
}