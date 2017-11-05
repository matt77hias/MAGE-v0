#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "shader\shader.hpp"
#include "material\brdf.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations
//-----------------------------------------------------------------------------
namespace mage {

	//-------------------------------------------------------------------------
	// Factory Methods: AA
	//-------------------------------------------------------------------------
#pragma region

	/**
	 Creates a AA preprocess compute shader.

	 @pre			The resource manager associated with the current engine 
					must be loaded.
	 @pre			The rendering manager associated with the current engine 
					must be loaded.
	 @return		A pointer to the AA preprocess compute shader.
	 @throws		FormattedException
					Failed to create the compute shader.
	 */
	SharedPtr< const ComputeShader > CreateAAPreprocessCS();

	/**
	 Creates a FXAA compute shader.

	 @pre			The resource manager associated with the current engine 
					must be loaded.
	 @pre			The rendering manager associated with the current engine 
					must be loaded.
	 @return		A pointer to the FXAA compute shader.
	 @throws		FormattedException
					Failed to create the compute shader.
	 */
	SharedPtr< const ComputeShader > CreateFXAACS();

	/**
	 Creates a MSAA resolve compute shader.

	 @pre			The resource manager associated with the current engine 
					must be loaded.
	 @pre			The rendering manager associated with the current engine 
					must be loaded.
	 @param[in]		nb_samples
					The number of MSAA samples (i.e. subpixels).
	 @return		A pointer to the MSAA resolve compute shader.
	 @throws		FormattedException
					Failed to create the compute shader.
	 */
	SharedPtr< const ComputeShader > CreateMSAAResolveCS(U32 nb_samples);

	/**
	 Creates a SSAA resolve compute shader.

	 @pre			The resource manager associated with the current engine 
					must be loaded.
	 @pre			The rendering manager associated with the current engine 
					must be loaded.
	 @param[in]		nb_samples
					The number of SSAA samples (both dimensions).
	 @return		A pointer to the SSAA resolve compute shader.
	 @throws		FormattedException
					Failed to create the compute shader.
	 */
	SharedPtr< const ComputeShader > CreateSSAAResolveCS(U32 nb_samples);

#pragma endregion

	//-------------------------------------------------------------------------
	// Factory Methods: Deferred
	//-------------------------------------------------------------------------
#pragma region

	/**
	 Creates a deferred Blinn-Phong compute shader.

	 @pre			The resource manager associated with the current engine 
					must be loaded.
	 @pre			The rendering manager associated with the current engine 
					must be loaded.
	 @return		A pointer to the deferred Blinn-Phong compute shader.
	 @throws		FormattedException
					Failed to create the compute shader.
	 */
	SharedPtr< const ComputeShader > CreateDeferredBlinnPhongCS();

	/**
	 Creates a deferred Cook-Torrance compute shader.

	 @pre			The resource manager associated with the current engine 
					must be loaded.
	 @pre			The rendering manager associated with the current engine 
					must be loaded.
	 @return		A pointer to the deferred Cook-Torrance compute shader.
	 @throws		FormattedException
					Failed to create the compute shader.
	 */
	SharedPtr< const ComputeShader > CreateDeferredCookTorranceCS();

	/**
	 Creates a deferred emissive compute shader.

	 @pre			The resource manager associated with the current engine 
					must be loaded.
	 @pre			The rendering manager associated with the current engine 
					must be loaded.
	 @return		A pointer to the deferred emissive compute shader.
	 @throws		FormattedException
					Failed to create the compute shader.
	 */
	SharedPtr< const ComputeShader > CreateDeferredEmissiveCS();

	/**
	 Creates a deferred Frostbite compute shader.

	 @pre			The resource manager associated with the current engine 
					must be loaded.
	 @pre			The rendering manager associated with the current engine 
					must be loaded.
	 @return		A pointer to the deferred Frostbite compute shader.
	 @throws		FormattedException
					Failed to create the compute shader.
	 */
	SharedPtr< const ComputeShader > CreateDeferredFrostbiteCS();

	/**
	 Creates a deferred Ward-Duer compute shader.

	 @pre			The resource manager associated with the current engine 
					must be loaded.
	 @pre			The rendering manager associated with the current engine 
					must be loaded.
	 @return		A pointer to the deferred Ward-Duer compute shader.
	 @throws		FormattedException
					Failed to create the compute shader.
	 */
	SharedPtr< const ComputeShader > CreateDeferredWardDuerCS();

	/**
	 Creates a deferred Lambertian compute shader.

	 @pre			The resource manager associated with the current engine 
					must be loaded.
	 @pre			The rendering manager associated with the current engine 
					must be loaded.
	 @return		A pointer to the deferred Lambertian compute shader.
	 @throws		FormattedException
					Failed to create the compute shader.
	 */
	SharedPtr< const ComputeShader > CreateDeferredLambertianCS();

	/**
	 Creates a deferred compute shader matching the given BRDF.

	 @pre			The resource manager associated with the current engine 
					must be loaded.
	 @pre			The rendering manager associated with the current engine 
					must be loaded.
	 @param[in]		brdf
					The BRDF type.
	 @return		A pointer to the deferred compute shader matching the given 
					BRDF.
	 @throws		FormattedException
					Failed to create the compute shader.
	 */
	SharedPtr< const ComputeShader > CreateDeferredCS(BRDFType brdf);

	/**
	 Creates a deferred MSAA Blinn-Phong pixel shader.

	 @pre			The resource manager associated with the current engine 
					must be loaded.
	 @pre			The rendering manager associated with the current engine 
					must be loaded.
	 @return		A pointer to the deferred MSAA Blinn-Phong pixel shader.
	 @throws		FormattedException
					Failed to create the pixel shader.
	 */
	SharedPtr< const PixelShader > CreateDeferredMSAABlinnPhongPS();

	/**
	 Creates a deferred MSAA Cook-Torrance pixel shader.

	 @pre			The resource manager associated with the current engine 
					must be loaded.
	 @pre			The rendering manager associated with the current engine 
					must be loaded.
	 @return		A pointer to the deferred MSAA Cook-Torrance pixel shader.
	 @throws		FormattedException
					Failed to create the pixel shader.
	 */
	SharedPtr< const PixelShader > CreateDeferredMSAACookTorrancePS();

	/**
	 Creates a deferred MSAA emissive pixel shader.

	 @pre			The resource manager associated with the current engine 
					must be loaded.
	 @pre			The rendering manager associated with the current engine 
					must be loaded.
	 @return		A pointer to the deferred MSAA emissive pixel shader.
	 @throws		FormattedException
					Failed to create the pixel shader.
	 */
	SharedPtr< const PixelShader > CreateDeferredMSAAEmissivePS();

	/**
	 Creates a deferred MSAA Frostbite pixel shader.

	 @pre			The resource manager associated with the current engine 
					must be loaded.
	 @pre			The rendering manager associated with the current engine 
					must be loaded.
	 @return		A pointer to the deferred MSAA Frostbite pixel shader.
	 @throws		FormattedException
					Failed to create the pixel shader.
	 */
	SharedPtr< const PixelShader > CreateDeferredMSAAFrostbitePS();

	/**
	 Creates a deferred MSAA Ward-Duer pixel shader.

	 @pre			The resource manager associated with the current engine 
					must be loaded.
	 @pre			The rendering manager associated with the current engine 
					must be loaded.
	 @return		A pointer to the deferred MSAA Ward-Duer pixel shader.
	 @throws		FormattedException
					Failed to create the pixel shader.
	 */
	SharedPtr< const PixelShader > CreateDeferredMSAAWardDuerPS();

	/**
	 Creates a deferred MSAA Lambertian pixel shader.

	 @pre			The resource manager associated with the current engine 
					must be loaded.
	 @pre			The rendering manager associated with the current engine 
					must be loaded.
	 @return		A pointer to the deferred MSAA Lambertian pixel shader.
	 @throws		FormattedException
					Failed to create the pixel shader.
	 */
	SharedPtr< const PixelShader > CreateDeferredMSAALambertianPS();

	/**
	 Creates a deferred MSAA pixel shader matching the given BRDF.

	 @pre			The resource manager associated with the current engine 
					must be loaded.
	 @pre			The rendering manager associated with the current engine 
					must be loaded.
	 @param[in]		brdf
					The BRDF type.
	 @return		A pointer to the deferred MSAA pixel shader matching the 
					given BRDF.
	 @throws		FormattedException
					Failed to create the pixel shader.
	 */
	SharedPtr< const PixelShader > CreateDeferredMSAAPS(BRDFType brdf);

#pragma endregion

	//-------------------------------------------------------------------------
	// Factory Methods: Depth
	//-------------------------------------------------------------------------
#pragma region

	/**
	 Creates a depth vertex shader.

	 @pre			The resource manager associated with the current engine 
					must be loaded.
	 @pre			The rendering manager associated with the current engine 
					must be loaded.
	 @return		A pointer to the depth vertex shader.
	 @throws		FormattedException
					Failed to create the vertex shader.
	 */
	SharedPtr< const VertexShader > CreateDepthVS();

	/**
	 Creates a depth transparent vertex shader.

	 @pre			The resource manager associated with the current engine 
					must be loaded.
	 @pre			The rendering manager associated with the current engine 
					must be loaded.
	 @return		A pointer to the depth transparent vertex shader.
	 @throws		FormattedException
					Failed to create the vertex shader.
	 */
	SharedPtr< const VertexShader > CreateDepthTransparentVS();

	/**
	 Creates a depth transparent pixel shader.

	 @pre			The resource manager associated with the current engine 
					must be loaded.
	 @pre			The rendering manager associated with the current engine 
					must be loaded.
	 @return		A pointer to the depth transparent pixel shader.
	 @throws		FormattedException
					Failed to create the pixel shader.
	 */
	SharedPtr< const PixelShader > CreateDepthTransparentPS();

#pragma endregion

	//-------------------------------------------------------------------------
	// Factory Methods: Forward
	//-------------------------------------------------------------------------
#pragma region

	/**
	 Creates a forward Blinn-Phong pixel shader.

	 @pre			The resource manager associated with the current engine 
					must be loaded.
	 @pre			The rendering manager associated with the current engine 
					must be loaded.
	 @param[in]		tsnm
					@c true if tangent space normal mapping should be 
					supported. @c false otherwise.
	 @param[in]		transparency
					@c true if transparency should be supported. @c false 
					otherwise.
	 @return		A pointer to the forward Blinn-Phong pixel shader.
	 @throws		FormattedException
					Failed to create the pixel shader.
	 */
	SharedPtr< const PixelShader > CreateForwardBlinnPhongPS(
		bool tsnm = false, bool transparency = false);

	/**
	 Creates a forward Cook-Torrance pixel shader.

	 @pre			The resource manager associated with the current engine 
					must be loaded.
	 @pre			The rendering manager associated with the current engine 
					must be loaded.
	 @param[in]		tsnm
					@c true if tangent space normal mapping should be 
					supported. @c false otherwise.
	 @param[in]		transparency
					@c true if transparency should be supported. @c false 
					otherwise.
	 @return		A pointer to the forward Cook-Torrance pixel shader.
	 @throws		FormattedException
					Failed to create the pixel shader.
	 */
	SharedPtr< const PixelShader > CreateForwardCookTorrancePS(
		bool tsnm = false, bool transparency = false);

	/**
	 Creates an forward emissive pixel shader.

	 @pre			The resource manager associated with the current engine 
					must be loaded.
	 @pre			The rendering manager associated with the current engine 
					must be loaded.
	 @param[in]		transparency
					@c true if transparency should be supported. @c false 
					otherwise.
	 @return		A pointer to the forward emissive pixel shader.
	 @throws		FormattedException
					Failed to create the pixel shader.
	 */
	SharedPtr< const PixelShader > CreateForwardEmissivePS(
		bool transparency = false);

	/**
	 Creates a forward Frostbite pixel shader.

	 @pre			The resource manager associated with the current engine 
					must be loaded.
	 @pre			The rendering manager associated with the current engine 
					must be loaded.
	 @param[in]		tsnm
					@c true if tangent space normal mapping should be 
					supported. @c false otherwise.
	 @param[in]		transparency
					@c true if transparency should be supported. @c false 
					otherwise.
	 @return		A pointer to the forward Frostbite pixel shader.
	 @throws		FormattedException
					Failed to create the pixel shader.
	 */
	SharedPtr< const PixelShader > CreateForwardFrostbitePS(
		bool tsnm = false, bool transparency = false);

	/**
	 Creates a forward Lambertian pixel shader.

	 @pre			The resource manager associated with the current engine 
					must be loaded.
	 @pre			The rendering manager associated with the current engine 
					must be loaded.
	 @param[in]		tsnm
					@c true if tangent space normal mapping should be 
					supported. @c false otherwise.
	 @param[in]		transparency
					@c true if transparency should be supported. @c false 
					otherwise.
	 @return		A pointer to the forward Lambertian pixel shader.
	 @throws		FormattedException
					Failed to create the pixel shader.
	 */
	SharedPtr< const PixelShader > CreateForwardLambertianPS(
		bool tsnm = false, bool transparency = false);

	/**
	 Creates a forward Ward-Duer pixel shader.

	 @pre			The resource manager associated with the current engine 
					must be loaded.
	 @pre			The rendering manager associated with the current engine 
					must be loaded.
	 @param[in]		tsnm
					@c true if tangent space normal mapping should be 
					supported. @c false otherwise.
	 @param[in]		transparency
					@c true if transparency should be supported. @c false 
					otherwise.
	 @return		A pointer to the forward Ward-Duer pixel shader.
	 @throws		FormattedException
					Failed to create the pixel shader.
	 */
	SharedPtr< const PixelShader > CreateForwardWardDuerPS(
		bool tsnm = false, bool transparency = false);

	/**
	 Creates a forward pixel shader matching the given BRDF.

	 @pre			The resource manager associated with the current engine 
					must be loaded.
	 @pre			The rendering manager associated with the current engine 
					must be loaded.
	 @param[in]		brdf
					The BRDF type.
	 @param[in]		tsnm
					@c true if tangent space normal mapping should be 
					supported. @c false otherwise.
	 @param[in]		transparency
					@c true if transparency should be supported. @c false 
					otherwise.
	 @return		A pointer to the forward pixel shader matching the given 
					BRDF.
	 @throws		FormattedException
					Failed to create the pixel shader.
	 */
	SharedPtr< const PixelShader > CreateForwardPS(BRDFType brdf,
		bool tsnm = false, bool transparency = false);

#pragma endregion

	//-------------------------------------------------------------------------
	// Factory Methods: GBuffer
	//-------------------------------------------------------------------------
#pragma region

	/**
	 Creates a GBuffer pixel shader.

	 @pre			The resource manager associated with the current engine 
					must be loaded.
	 @pre			The rendering manager associated with the current engine 
					must be loaded.
	 @param[in]		tsnm
					@c true if tangent space normal mapping should be 
					supported. @c false otherwise.
	 @return		A pointer to the GBuffer pixel shader.
	 @throws		FormattedException
					Failed to create the pixel shader.
	 */
	SharedPtr< const PixelShader > CreateGBufferPS(bool tsnm = false);

#pragma endregion

	//-------------------------------------------------------------------------
	// Factory Methods: Miscellaneous
	//-------------------------------------------------------------------------
#pragma region

	/**
	 Creates a back buffer pixel shader.

	 @pre			The resource manager associated with the current engine 
					must be loaded.
	 @pre			The rendering manager associated with the current engine 
					must be loaded.
	 @return		A pointer to the back buffer pixel shader.
	 @throws		FormattedException
					Failed to create the pixel shader.
	 */
	SharedPtr< const PixelShader > CreateBackBufferPS();

	/**
	 Creates a constant color pixel shader.

	 @pre			The resource manager associated with the current engine 
					must be loaded.
	 @pre			The rendering manager associated with the current engine 
					must be loaded.
	 @return		A pointer to the constant color pixel shader.
	 @throws		FormattedException
					Failed to create the pixel shader.
	 */
	SharedPtr< const PixelShader > CreateConstantColorPS();

	/**
	 Creates a constant color texture pixel shader.

	 @pre			The resource manager associated with the current engine 
					must be loaded.
	 @pre			The rendering manager associated with the current engine 
					must be loaded.
	 @return		A pointer to the constant color texture pixel shader.
	 @throws		FormattedException
					Failed to create the pixel shader.
	 */
	SharedPtr< const PixelShader > CreateConstantColorTexturePS();

	/**
	 Creates a distance pixel shader.

	 @pre			The resource manager associated with the current engine 
					must be loaded.
	 @pre			The rendering manager associated with the current engine 
					must be loaded.
	 @return		A pointer to the distance pixel shader.
	 @throws		FormattedException
					Failed to create the pixel shader.
	 */
	SharedPtr< const PixelShader > CreateDistancePS();

	/**
	 Creates a shading normal vertex shader.

	 @pre			The resource manager associated with the current engine 
					must be loaded.
	 @pre			The rendering manager associated with the current engine 
					must be loaded.
	 @return		A pointer to the shading normal vertex shader.
	 @throws		FormattedException
					Failed to create the vertex shader.
	 */
	SharedPtr< const VertexShader > CreateShadingNormalVS();

	/**
	 Creates a shading normal pixel shader.

	 @pre			The resource manager associated with the current engine 
					must be loaded.
	 @pre			The rendering manager associated with the current engine 
					must be loaded.
	 @param[in]		tsnm
					@c true if tangent space normal mapping should be 
					supported. @c false otherwise.
	 @return		A pointer to the shading normal pixel shader.
	 @throws		FormattedException
					Failed to create the pixel shader.
	 */
	SharedPtr< const PixelShader > CreateShadingNormalPS(
		bool tsnm = false);

#pragma endregion

	//-------------------------------------------------------------------------
	// Factory Methods: Primitive
	//-------------------------------------------------------------------------
#pragma region

	/**
	 Creates a line cube vertex shader.

	 @pre			The resource manager associated with the current engine 
					must be loaded.
	 @pre			The rendering manager associated with the current engine 
					must be loaded.
	 @return		A pointer to the line cube vertex shader.
	 @throws		FormattedException
					Failed to create the vertex shader.
	 */
	SharedPtr< const VertexShader > CreateLineCubeVS();

	/**
	 Creates a line cube pixel shader.

	 @pre			The resource manager associated with the current engine 
					must be loaded.
	 @pre			The rendering manager associated with the current engine 
					must be loaded.
	 @return		A pointer to the line cube pixel shader.
	 @throws		FormattedException
					Failed to create the pixel shader.
	 */
	SharedPtr< const PixelShader > CreateLineCubePS();

	/**
	 Creates a far fullscreen triangle vertex shader.

	 @pre			The resource manager associated with the current engine 
					must be loaded.
	 @pre			The rendering manager associated with the current engine 
					must be loaded.
	 @return		A pointer to the far fullscreen triangle vertex shader.
	 @throws		FormattedException
					Failed to create the vertex shader.
	 */
	SharedPtr< const VertexShader > CreateFarFullscreenTriangleVS();

	/**
	 Creates a near fullscreen triangle vertex shader.

	 @pre			The resource manager associated with the current engine 
					must be loaded.
	 @pre			The rendering manager associated with the current engine 
					must be loaded.
	 @return		A pointer to the near fullscreen triangle vertex shader.
	 @throws		FormattedException
					Failed to create the vertex shader.
	 */
	SharedPtr< const VertexShader > CreateNearFullscreenTriangleVS();

#pragma endregion

	//-------------------------------------------------------------------------
	// Factory Methods: Sky
	//-------------------------------------------------------------------------
#pragma region

	/**
	 Creates a sky vertex shader.

	 @pre			The resource manager associated with the current engine 
					must be loaded.
	 @pre			The rendering manager associated with the current engine 
					must be loaded.
	 @return		A pointer to the sky vertex shader.
	 @throws		FormattedException
					Failed to create the vertex shader.
	 */
	SharedPtr< const VertexShader > CreateSkyVS();

	/**
	 Creates a sky pixel shader.

	 @pre			The resource manager associated with the current engine 
					must be loaded.
	 @pre			The rendering manager associated with the current engine 
					must be loaded.
	 @return		A pointer to the sky pixel shader.
	 @throws		FormattedException
					Failed to create the pixel shader.
	 */
	SharedPtr< const PixelShader > CreateSkyPS();

#pragma endregion

	//-------------------------------------------------------------------------
	// Factory Methods: Sprite
	//-------------------------------------------------------------------------
#pragma region

	/**
	 Creates a sprite vertex shader.

	 @pre			The resource manager associated with the current engine 
					must be loaded.
	 @pre			The rendering manager associated with the current engine 
					must be loaded.
	 @return		A pointer to the sprite vertex shader.
	 @throws		FormattedException
					Failed to create the vertex shader.
	 */
	SharedPtr< const VertexShader > CreateSpriteVS();

	/**
	 Creates a sprite pixel shader.

	 @pre			The resource manager associated with the current engine 
					must be loaded.
	 @pre			The rendering manager associated with the current engine 
					must be loaded.
	 @return		A pointer to the sprite pixel shader.
	 @throws		FormattedException
					Failed to create the pixel shader.
	 */
	SharedPtr< const PixelShader > CreateSpritePS();

#pragma endregion

	//-------------------------------------------------------------------------
	// Factory Methods: Transform
	//-------------------------------------------------------------------------
#pragma region

	/**
	 Creates a transform vertex shader.

	 @pre			The resource manager associated with the current engine 
					must be loaded.
	 @pre			The rendering manager associated with the current engine 
					must be loaded.
	 @return		A pointer to the transform vertex shader.
	 @throws		FormattedException
					Failed to create the vertex shader.
	 */
	SharedPtr< const VertexShader > CreateTransformVS();

	/**
	 Creates a minimal transform vertex shader.

	 @pre			The resource manager associated with the current engine 
					must be loaded.
	 @pre			The rendering manager associated with the current engine 
					must be loaded.
	 @return		A pointer to the minimal transform vertex shader.
	 @throws		FormattedException
					Failed to create the vertex shader.
	 */
	SharedPtr< const VertexShader > CreateMinimalTransformVS();

#pragma endregion

	//-------------------------------------------------------------------------
	// Factory Methods: Voxelization
	//-------------------------------------------------------------------------
#pragma region

	/**
	 Creates a voxelization geometry shader.

	 @pre			The resource manager associated with the current engine 
					must be loaded.
	 @pre			The rendering manager associated with the current engine 
					must be loaded.
	 @return		A pointer to the voxelization geometry shader.
	 @throws		FormattedException
					Failed to create the geometry shader.
	 */
	SharedPtr< const GeometryShader > CreateVoxelizationGS();

	/**
	 Creates a voxelization pixel shader.

	 @pre			The resource manager associated with the current engine 
					must be loaded.
	 @pre			The rendering manager associated with the current engine 
					must be loaded.
	 @return		A pointer to the voxelization pixel shader.
	 @throws		FormattedException
					Failed to create the pixel shader.
	 */
	SharedPtr< const PixelShader > CreateVoxelizationPS();

#pragma endregion
}