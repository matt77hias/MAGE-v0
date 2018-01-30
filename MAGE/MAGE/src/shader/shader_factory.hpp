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
	 @throws		Exception
					Failed to create the compute shader.
	 */
	ComputeShaderPtr CreateAAPreprocessCS();

	/**
	 Creates a FXAA compute shader.

	 @pre			The resource manager associated with the current engine 
					must be loaded.
	 @pre			The rendering manager associated with the current engine 
					must be loaded.
	 @return		A pointer to the FXAA compute shader.
	 @throws		Exception
					Failed to create the compute shader.
	 */
	ComputeShaderPtr CreateFXAACS();

	/**
	 Creates a MSAA resolve compute shader.

	 @pre			The resource manager associated with the current engine 
					must be loaded.
	 @pre			The rendering manager associated with the current engine 
					must be loaded.
	 @return		A pointer to the MSAA resolve compute shader.
	 @throws		Exception
					Failed to create the compute shader.
	 */
	ComputeShaderPtr CreateMSAAResolveCS();

	/**
	 Creates a SSAA resolve compute shader.

	 @pre			The resource manager associated with the current engine 
					must be loaded.
	 @pre			The rendering manager associated with the current engine 
					must be loaded.
	 @return		A pointer to the SSAA resolve compute shader.
	 @throws		Exception
					Failed to create the compute shader.
	 */
	ComputeShaderPtr CreateSSAAResolveCS();

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
	 @throws		Exception
					Failed to create the compute shader.
	 */
	ComputeShaderPtr CreateDeferredBlinnPhongCS();

	/**
	 Creates a deferred Cook-Torrance compute shader.

	 @pre			The resource manager associated with the current engine 
					must be loaded.
	 @pre			The rendering manager associated with the current engine 
					must be loaded.
	 @return		A pointer to the deferred Cook-Torrance compute shader.
	 @throws		Exception
					Failed to create the compute shader.
	 */
	ComputeShaderPtr CreateDeferredCookTorranceCS();

	/**
	 Creates a deferred emissive compute shader.

	 @pre			The resource manager associated with the current engine 
					must be loaded.
	 @pre			The rendering manager associated with the current engine 
					must be loaded.
	 @return		A pointer to the deferred emissive compute shader.
	 @throws		Exception
					Failed to create the compute shader.
	 */
	ComputeShaderPtr CreateDeferredEmissiveCS();

	/**
	 Creates a deferred Frostbite compute shader.

	 @pre			The resource manager associated with the current engine 
					must be loaded.
	 @pre			The rendering manager associated with the current engine 
					must be loaded.
	 @return		A pointer to the deferred Frostbite compute shader.
	 @throws		Exception
					Failed to create the compute shader.
	 */
	ComputeShaderPtr CreateDeferredFrostbiteCS();

	/**
	 Creates a deferred Ward-Duer compute shader.

	 @pre			The resource manager associated with the current engine 
					must be loaded.
	 @pre			The rendering manager associated with the current engine 
					must be loaded.
	 @return		A pointer to the deferred Ward-Duer compute shader.
	 @throws		Exception
					Failed to create the compute shader.
	 */
	ComputeShaderPtr CreateDeferredWardDuerCS();

	/**
	 Creates a deferred Lambertian compute shader.

	 @pre			The resource manager associated with the current engine 
					must be loaded.
	 @pre			The rendering manager associated with the current engine 
					must be loaded.
	 @return		A pointer to the deferred Lambertian compute shader.
	 @throws		Exception
					Failed to create the compute shader.
	 */
	ComputeShaderPtr CreateDeferredLambertianCS();

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
	 @throws		Exception
					Failed to create the compute shader.
	 */
	ComputeShaderPtr CreateDeferredCS(BRDFType brdf);

	/**
	 Creates a deferred MSAA Blinn-Phong pixel shader.

	 @pre			The resource manager associated with the current engine 
					must be loaded.
	 @pre			The rendering manager associated with the current engine 
					must be loaded.
	 @return		A pointer to the deferred MSAA Blinn-Phong pixel shader.
	 @throws		Exception
					Failed to create the pixel shader.
	 */
	PixelShaderPtr CreateDeferredMSAABlinnPhongPS();

	/**
	 Creates a deferred MSAA Cook-Torrance pixel shader.

	 @pre			The resource manager associated with the current engine 
					must be loaded.
	 @pre			The rendering manager associated with the current engine 
					must be loaded.
	 @return		A pointer to the deferred MSAA Cook-Torrance pixel shader.
	 @throws		Exception
					Failed to create the pixel shader.
	 */
	PixelShaderPtr CreateDeferredMSAACookTorrancePS();

	/**
	 Creates a deferred MSAA emissive pixel shader.

	 @pre			The resource manager associated with the current engine 
					must be loaded.
	 @pre			The rendering manager associated with the current engine 
					must be loaded.
	 @return		A pointer to the deferred MSAA emissive pixel shader.
	 @throws		Exception
					Failed to create the pixel shader.
	 */
	PixelShaderPtr CreateDeferredMSAAEmissivePS();

	/**
	 Creates a deferred MSAA Frostbite pixel shader.

	 @pre			The resource manager associated with the current engine 
					must be loaded.
	 @pre			The rendering manager associated with the current engine 
					must be loaded.
	 @return		A pointer to the deferred MSAA Frostbite pixel shader.
	 @throws		Exception
					Failed to create the pixel shader.
	 */
	PixelShaderPtr CreateDeferredMSAAFrostbitePS();

	/**
	 Creates a deferred MSAA Ward-Duer pixel shader.

	 @pre			The resource manager associated with the current engine 
					must be loaded.
	 @pre			The rendering manager associated with the current engine 
					must be loaded.
	 @return		A pointer to the deferred MSAA Ward-Duer pixel shader.
	 @throws		Exception
					Failed to create the pixel shader.
	 */
	PixelShaderPtr CreateDeferredMSAAWardDuerPS();

	/**
	 Creates a deferred MSAA Lambertian pixel shader.

	 @pre			The resource manager associated with the current engine 
					must be loaded.
	 @pre			The rendering manager associated with the current engine 
					must be loaded.
	 @return		A pointer to the deferred MSAA Lambertian pixel shader.
	 @throws		Exception
					Failed to create the pixel shader.
	 */
	PixelShaderPtr CreateDeferredMSAALambertianPS();

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
	 @throws		Exception
					Failed to create the pixel shader.
	 */
	PixelShaderPtr CreateDeferredMSAAPS(BRDFType brdf);

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
	 @throws		Exception
					Failed to create the vertex shader.
	 */
	VertexShaderPtr CreateDepthVS();

	/**
	 Creates a depth transparent vertex shader.

	 @pre			The resource manager associated with the current engine 
					must be loaded.
	 @pre			The rendering manager associated with the current engine 
					must be loaded.
	 @return		A pointer to the depth transparent vertex shader.
	 @throws		Exception
					Failed to create the vertex shader.
	 */
	VertexShaderPtr CreateDepthTransparentVS();

	/**
	 Creates a depth transparent pixel shader.

	 @pre			The resource manager associated with the current engine 
					must be loaded.
	 @pre			The rendering manager associated with the current engine 
					must be loaded.
	 @return		A pointer to the depth transparent pixel shader.
	 @throws		Exception
					Failed to create the pixel shader.
	 */
	PixelShaderPtr CreateDepthTransparentPS();

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
	 @throws		Exception
					Failed to create the pixel shader.
	 */
	PixelShaderPtr CreateForwardBlinnPhongPS(bool tsnm = false, 
											 bool transparency = false);

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
	 @throws		Exception
					Failed to create the pixel shader.
	 */
	PixelShaderPtr CreateForwardCookTorrancePS(bool tsnm = false, 
											   bool transparency = false);

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
	 @throws		Exception
					Failed to create the pixel shader.
	 */
	PixelShaderPtr CreateForwardEmissivePS(bool transparency = false);

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
	 @throws		Exception
					Failed to create the pixel shader.
	 */
	PixelShaderPtr CreateForwardFrostbitePS(bool tsnm = false, 
											bool transparency = false);

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
	 @throws		Exception
					Failed to create the pixel shader.
	 */
	PixelShaderPtr CreateForwardLambertianPS(bool tsnm = false, 
											 bool transparency = false);

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
	 @throws		Exception
					Failed to create the pixel shader.
	 */
	PixelShaderPtr CreateForwardWardDuerPS(bool tsnm = false, 
										   bool transparency = false);

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
	 @throws		Exception
					Failed to create the pixel shader.
	 */
	PixelShaderPtr CreateForwardPS(BRDFType brdf, 
								   bool tsnm = false, 
								   bool transparency = false);

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
	 @throws		Exception
					Failed to create the pixel shader.
	 */
	PixelShaderPtr CreateGBufferPS(bool tsnm = false);

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
	 @throws		Exception
					Failed to create the pixel shader.
	 */
	PixelShaderPtr CreateBackBufferPS();

	/**
	 Creates a constant color pixel shader.

	 @pre			The resource manager associated with the current engine 
					must be loaded.
	 @pre			The rendering manager associated with the current engine 
					must be loaded.
	 @return		A pointer to the constant color pixel shader.
	 @throws		Exception
					Failed to create the pixel shader.
	 */
	PixelShaderPtr CreateConstantColorPS();

	/**
	 Creates a constant color texture pixel shader.

	 @pre			The resource manager associated with the current engine 
					must be loaded.
	 @pre			The rendering manager associated with the current engine 
					must be loaded.
	 @return		A pointer to the constant color texture pixel shader.
	 @throws		Exception
					Failed to create the pixel shader.
	 */
	PixelShaderPtr CreateConstantColorTexturePS();

	/**
	 Creates a distance pixel shader.

	 @pre			The resource manager associated with the current engine 
					must be loaded.
	 @pre			The rendering manager associated with the current engine 
					must be loaded.
	 @return		A pointer to the distance pixel shader.
	 @throws		Exception
					Failed to create the pixel shader.
	 */
	PixelShaderPtr CreateDistancePS();

	/**
	 Creates a shading normal vertex shader.

	 @pre			The resource manager associated with the current engine 
					must be loaded.
	 @pre			The rendering manager associated with the current engine 
					must be loaded.
	 @return		A pointer to the shading normal vertex shader.
	 @throws		Exception
					Failed to create the vertex shader.
	 */
	VertexShaderPtr CreateShadingNormalVS();

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
	 @throws		Exception
					Failed to create the pixel shader.
	 */
	PixelShaderPtr CreateShadingNormalPS(bool tsnm = false);

	#pragma endregion

	//-------------------------------------------------------------------------
	// Factory Methods: Post Processing
	//-------------------------------------------------------------------------
	#pragma region

	/**
	 Creates a depth-of-field compute shader.

	 @pre			The resource manager associated with the current engine 
					must be loaded.
	 @pre			The rendering manager associated with the current engine 
					must be loaded.
	 @return		A pointer to the depth-of-field compute shader.
	 @throws		Exception
					Failed to create the compute shader.
	 */
	ComputeShaderPtr CreateDepthOfFieldCS();

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
	 @throws		Exception
					Failed to create the vertex shader.
	 */
	VertexShaderPtr CreateLineCubeVS();

	/**
	 Creates a line cube pixel shader.

	 @pre			The resource manager associated with the current engine 
					must be loaded.
	 @pre			The rendering manager associated with the current engine 
					must be loaded.
	 @return		A pointer to the line cube pixel shader.
	 @throws		Exception
					Failed to create the pixel shader.
	 */
	PixelShaderPtr CreateLineCubePS();

	/**
	 Creates a far fullscreen triangle vertex shader.

	 @pre			The resource manager associated with the current engine 
					must be loaded.
	 @pre			The rendering manager associated with the current engine 
					must be loaded.
	 @return		A pointer to the far fullscreen triangle vertex shader.
	 @throws		Exception
					Failed to create the vertex shader.
	 */
	VertexShaderPtr CreateFarFullscreenTriangleVS();

	/**
	 Creates a near fullscreen triangle vertex shader.

	 @pre			The resource manager associated with the current engine 
					must be loaded.
	 @pre			The rendering manager associated with the current engine 
					must be loaded.
	 @return		A pointer to the near fullscreen triangle vertex shader.
	 @throws		Exception
					Failed to create the vertex shader.
	 */
	VertexShaderPtr CreateNearFullscreenTriangleVS();

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
	 @throws		Exception
					Failed to create the vertex shader.
	 */
	VertexShaderPtr CreateSkyVS();

	/**
	 Creates a sky pixel shader.

	 @pre			The resource manager associated with the current engine 
					must be loaded.
	 @pre			The rendering manager associated with the current engine 
					must be loaded.
	 @return		A pointer to the sky pixel shader.
	 @throws		Exception
					Failed to create the pixel shader.
	 */
	PixelShaderPtr CreateSkyPS();

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
	 @throws		Exception
					Failed to create the vertex shader.
	 */
	VertexShaderPtr CreateSpriteVS();

	/**
	 Creates a sprite pixel shader.

	 @pre			The resource manager associated with the current engine 
					must be loaded.
	 @pre			The rendering manager associated with the current engine 
					must be loaded.
	 @return		A pointer to the sprite pixel shader.
	 @throws		Exception
					Failed to create the pixel shader.
	 */
	PixelShaderPtr CreateSpritePS();

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
	 @throws		Exception
					Failed to create the vertex shader.
	 */
	VertexShaderPtr CreateTransformVS();

	/**
	 Creates a minimal transform vertex shader.

	 @pre			The resource manager associated with the current engine 
					must be loaded.
	 @pre			The rendering manager associated with the current engine 
					must be loaded.
	 @return		A pointer to the minimal transform vertex shader.
	 @throws		Exception
					Failed to create the vertex shader.
	 */
	VertexShaderPtr CreateMinimalTransformVS();

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
	 @throws		Exception
					Failed to create the geometry shader.
	 */
	GeometryShaderPtr CreateVoxelizationGS();

	/**
	 Creates a voxelization Blinn-Phong pixel shader.

	 @pre			The resource manager associated with the current engine 
					must be loaded.
	 @pre			The rendering manager associated with the current engine 
					must be loaded.
	 @param[in]		tsnm
					@c true if tangent space normal mapping should be 
					supported. @c false otherwise.
	 @return		A pointer to the voxelization Blinn-Phong pixel shader.
	 @throws		Exception
					Failed to create the pixel shader.
	 */
	PixelShaderPtr CreateVoxelizationBlinnPhongPS(bool tsnm = false);

	/**
	 Creates a voxelization Cook-Torrance pixel shader.

	 @pre			The resource manager associated with the current engine 
					must be loaded.
	 @pre			The rendering manager associated with the current engine 
					must be loaded.
	 @param[in]		tsnm
					@c true if tangent space normal mapping should be 
					supported. @c false otherwise.
	 @return		A pointer to the voxelization Cook-Torrance pixel shader.
	 @throws		Exception
					Failed to create the pixel shader.
	 */
	PixelShaderPtr CreateVoxelizationCookTorrancePS(bool tsnm = false);

	/**
	 Creates a voxelization Frostbite pixel shader.

	 @pre			The resource manager associated with the current engine 
					must be loaded.
	 @pre			The rendering manager associated with the current engine 
					must be loaded.
	 @param[in]		tsnm
					@c true if tangent space normal mapping should be 
					supported. @c false otherwise.
	 @return		A pointer to the voxelization Frostbite pixel shader.
	 @throws		Exception
					Failed to create the pixel shader.
	 */
	PixelShaderPtr CreateVoxelizationFrostbitePS(bool tsnm = false);

	/**
	 Creates a voxelization Lambertian pixel shader.

	 @pre			The resource manager associated with the current engine 
					must be loaded.
	 @pre			The rendering manager associated with the current engine 
					must be loaded.
	 @param[in]		tsnm
					@c true if tangent space normal mapping should be 
					supported. @c false otherwise.
	 @return		A pointer to the voxelization Lambertian pixel shader.
	 @throws		Exception
					Failed to create the pixel shader.
	 */
	PixelShaderPtr CreateVoxelizationLambertianPS(bool tsnm = false);

	/**
	 Creates a voxelization Ward-Duer pixel shader.

	 @pre			The resource manager associated with the current engine 
					must be loaded.
	 @pre			The rendering manager associated with the current engine 
					must be loaded.
	 @param[in]		tsnm
					@c true if tangent space normal mapping should be 
					supported. @c false otherwise.
	 @return		A pointer to the voxelization Ward-Duer pixel shader.
	 @throws		Exception
					Failed to create the pixel shader.
	 */
	PixelShaderPtr CreateVoxelizationWardDuerPS(bool tsnm = false);

	/**
	 Creates a voxelization pixel shader matching the given BRDF.

	 @pre			The resource manager associated with the current engine 
					must be loaded.
	 @pre			The rendering manager associated with the current engine 
					must be loaded.
	 @param[in]		brdf
					The BRDF type.
	 @param[in]		tsnm
					@c true if tangent space normal mapping should be 
					supported. @c false otherwise.
	 @return		A pointer to the voxelization pixel shader matching the given 
					BRDF.
	 @throws		Exception
					Failed to create the pixel shader.
	 */
	PixelShaderPtr CreateVoxelizationPS(BRDFType brdf, bool tsnm = false);

	#pragma endregion
}