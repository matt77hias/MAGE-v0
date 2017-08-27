#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "shader\guids.hpp"
#include "shader\shader.hpp"
#include "material\brdf.hpp"

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
	 Creates a pixel shader matching the given BRDF.

	 @pre			The resource manager associated with the
					current engine must be loaded.
	 @param[in]		brdf
					The BRDF type.
	 @return		A pointer to the pixel shader matching
					the given BRDF.
	 @throws		FormattedException
					Failed to create the pixel shader.
	 */
	SharedPtr< const PixelShader > CreatePS(BRDFType brdf);

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
	 Creates a tsnm pixel shader matching the given BRDF.

	 @pre			The resource manager associated with the
					current engine must be loaded.
	 @param[in]		brdf
					The BRDF type.
	 @return		A pointer to the tsnm pixel shader matching
					the given BRDF.
	 @throws		FormattedException
					Failed to create the pixel shader.
	 */
	SharedPtr< const PixelShader > CreateTSNMPS(BRDFType brdf);

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

	/**
	 Creates a minimal transform vertex shader.

	 @pre			The resource manager associated with the
					current engine must be loaded.
	 @return		A pointer to the minimal transform vertex shader.
	 @throws		FormattedException
					Failed to create the vertex shader.
	 */
	SharedPtr< const VertexShader > CreateMinimalTransformVS() noexcept;

	/**
	 Creates a constant color pixel shader.

	 @pre			The resource manager associated with the
					current engine must be loaded.
	 @return		A pointer to the constant color pixel shader.
	 @throws		FormattedException
					Failed to create the pixel shader.
	 */
	SharedPtr< const PixelShader > CreateConstantColorPS() noexcept;

	/**
	 Creates a constant color texture pixel shader.

	 @pre			The resource manager associated with the
					current engine must be loaded.
	 @return		A pointer to the constant color texture pixel shader.
	 @throws		FormattedException
					Failed to create the pixel shader.
	 */
	SharedPtr< const PixelShader > CreateConstantColorTexturePS() noexcept;

	/**
	 Creates a distance pixel shader.

	 @pre			The resource manager associated with the
					current engine must be loaded.
	 @return		A pointer to the distance pixel shader.
	 @throws		FormattedException
					Failed to create the pixel shader.
	 */
	SharedPtr< const PixelShader > CreateDistancePS() noexcept;

	/**
	 Creates a shading normal vertex shader.

	 @pre			The resource manager associated with the
					current engine must be loaded.
	 @return		A pointer to the shading normal vertex shader.
	 @throws		FormattedException
					Failed to create the vertex shader.
	 */
	SharedPtr< const VertexShader > CreateShadingNormalVS() noexcept;

	/**
	 Creates a shading normal pixel shader.

	 @pre			The resource manager associated with the
					current engine must be loaded.
	 @return		A pointer to the shading normal pixel shader.
	 @throws		FormattedException
					Failed to create the pixel shader.
	 */
	SharedPtr< const PixelShader > CreateShadingNormalPS() noexcept;

	/**
	 Creates a tsnm shading normal pixel shader.

	 @pre			The resource manager associated with the
					current engine must be loaded.
	 @return		A pointer to the tsnm shading normal 
					pixel shader.
	 @throws		FormattedException
					Failed to create the pixel shader.
	 */
	SharedPtr< const PixelShader > CreateShadingNormalTSNMPS() noexcept;
}