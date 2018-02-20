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
	 @param[in]		vct
					@c true if voxel cone tracing should be enabled. @c false 
					otherwise.
	 @return		A pointer to the deferred Blinn-Phong compute shader.
	 @throws		Exception
					Failed to create the compute shader.
	 */
	ComputeShaderPtr CreateDeferredBlinnPhongCS(bool vct);

	/**
	 Creates a deferred Cook-Torrance compute shader.

	 @pre			The resource manager associated with the current engine 
					must be loaded.
	 @pre			The rendering manager associated with the current engine 
					must be loaded.
	 @param[in]		vct
					@c true if voxel cone tracing should be enabled. @c false 
					otherwise.
	 @return		A pointer to the deferred Cook-Torrance compute shader.
	 @throws		Exception
					Failed to create the compute shader.
	 */
	ComputeShaderPtr CreateDeferredCookTorranceCS(bool vct);

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
	 @param[in]		vct
					@c true if voxel cone tracing should be enabled. @c false 
					otherwise.
	 @return		A pointer to the deferred Frostbite compute shader.
	 @throws		Exception
					Failed to create the compute shader.
	 */
	ComputeShaderPtr CreateDeferredFrostbiteCS(bool vct);

	/**
	 Creates a deferred Ward-Duer compute shader.

	 @pre			The resource manager associated with the current engine 
					must be loaded.
	 @pre			The rendering manager associated with the current engine 
					must be loaded.
	 @param[in]		vct
					@c true if voxel cone tracing should be enabled. @c false
					otherwise.
	 @return		A pointer to the deferred Ward-Duer compute shader.
	 @throws		Exception
					Failed to create the compute shader.
	 */
	ComputeShaderPtr CreateDeferredWardDuerCS(bool vct);

	/**
	 Creates a deferred Lambertian compute shader.

	 @pre			The resource manager associated with the current engine 
					must be loaded.
	 @pre			The rendering manager associated with the current engine 
					must be loaded.
	 @param[in]		vct
					@c true if voxel cone tracing should be enabled. @c false 
					otherwise.
	 @return		A pointer to the deferred Lambertian compute shader.
	 @throws		Exception
					Failed to create the compute shader.
	 */
	ComputeShaderPtr CreateDeferredLambertianCS(bool vct);

	/**
	 Creates a deferred compute shader matching the given BRDF.

	 @pre			The resource manager associated with the current engine 
					must be loaded.
	 @pre			The rendering manager associated with the current engine 
					must be loaded.
	 @param[in]		brdf
					The BRDF type.
	 @param[in]		vct
					@c true if voxel cone tracing should be enabled. @c false 
					otherwise.
	 @return		A pointer to the deferred compute shader matching the given 
					BRDF.
	 @throws		Exception
					Failed to create the compute shader.
	 */
	ComputeShaderPtr CreateDeferredCS(BRDFType brdf, bool vct);

	/**
	 Creates a deferred MSAA Blinn-Phong pixel shader.

	 @pre			The resource manager associated with the current engine 
					must be loaded.
	 @pre			The rendering manager associated with the current engine 
					must be loaded.
	 @param[in]		vct
					@c true if voxel cone tracing should be enabled. @c false 
					otherwise.
	 @return		A pointer to the deferred MSAA Blinn-Phong pixel shader.
	 @throws		Exception
					Failed to create the pixel shader.
	 */
	PixelShaderPtr CreateDeferredMSAABlinnPhongPS(bool vct);

	/**
	 Creates a deferred MSAA Cook-Torrance pixel shader.

	 @pre			The resource manager associated with the current engine 
					must be loaded.
	 @pre			The rendering manager associated with the current engine 
					must be loaded.
	 @param[in]		vct
					@c true if voxel cone tracing should be enabled. @c false 
					otherwise.
	 @return		A pointer to the deferred MSAA Cook-Torrance pixel shader.
	 @throws		Exception
					Failed to create the pixel shader.
	 */
	PixelShaderPtr CreateDeferredMSAACookTorrancePS(bool vct);

	/**
	 Creates a deferred MSAA emissive pixel shader.

	 @pre			The resource manager associated with the current engine 
					must be loaded.
	 @pre			The rendering manager associated with the current engine 
					must be loaded.
	 @param[in]		vct
					@c true if voxel cone tracing should be enabled. @c false 
					otherwise.
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
	 @param[in]		vct
					@c true if voxel cone tracing should be enabled. @c false 
					otherwise.
	 @return		A pointer to the deferred MSAA Frostbite pixel shader.
	 @throws		Exception
					Failed to create the pixel shader.
	 */
	PixelShaderPtr CreateDeferredMSAAFrostbitePS(bool vct);

	/**
	 Creates a deferred MSAA Ward-Duer pixel shader.

	 @pre			The resource manager associated with the current engine 
					must be loaded.
	 @pre			The rendering manager associated with the current engine 
					must be loaded.
	 @param[in]		vct
					@c true if voxel cone tracing should be enabled. @c false 
					otherwise.
	 @return		A pointer to the deferred MSAA Ward-Duer pixel shader.
	 @throws		Exception
					Failed to create the pixel shader.
	 */
	PixelShaderPtr CreateDeferredMSAAWardDuerPS(bool vct);

	/**
	 Creates a deferred MSAA Lambertian pixel shader.

	 @pre			The resource manager associated with the current engine 
					must be loaded.
	 @pre			The rendering manager associated with the current engine 
					must be loaded.
	 @param[in]		vct
					@c true if voxel cone tracing should be enabled. @c false 
					otherwise.
	 @return		A pointer to the deferred MSAA Lambertian pixel shader.
	 @throws		Exception
					Failed to create the pixel shader.
	 */
	PixelShaderPtr CreateDeferredMSAALambertianPS(bool vct);

	/**
	 Creates a deferred MSAA pixel shader matching the given BRDF.

	 @pre			The resource manager associated with the current engine 
					must be loaded.
	 @pre			The rendering manager associated with the current engine 
					must be loaded.
	 @param[in]		brdf
					The BRDF type.
	 @param[in]		vct
					@c true if voxel cone tracing should be enabled. @c false 
					otherwise.
	 @return		A pointer to the deferred MSAA pixel shader matching the 
					given BRDF.
	 @throws		Exception
					Failed to create the pixel shader.
	 */
	PixelShaderPtr CreateDeferredMSAAPS(BRDFType brdf, bool vct);

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
	 @param[in]		transparency
					@c true if transparency should be enabled. @c false 
					otherwise.
	 @param[in]		vct
					@c true if voxel cone tracing should be enabled. @c false 
					otherwise.
	 @param[in]		tsnm
					@c true if tangent space normal mapping should be enabled. 
					@c false otherwise.
	 @return		A pointer to the forward Blinn-Phong pixel shader.
	 @throws		Exception
					Failed to create the pixel shader.
	 */
	PixelShaderPtr CreateForwardBlinnPhongPS(bool transparency, 
											 bool vct, 
											 bool tsnm);

	/**
	 Creates a forward Cook-Torrance pixel shader.

	 @pre			The resource manager associated with the current engine 
					must be loaded.
	 @pre			The rendering manager associated with the current engine 
					must be loaded.
	 @param[in]		transparency
					@c true if transparency should be enabled. @c false 
					otherwise.
	 @param[in]		vct
					@c true if voxel cone tracing should be enabled. @c false 
					otherwise.
	 @param[in]		tsnm
					@c true if tangent space normal mapping should be enabled. 
					@c false otherwise.
	 @return		A pointer to the forward Cook-Torrance pixel shader.
	 @throws		Exception
					Failed to create the pixel shader.
	 */
	PixelShaderPtr CreateForwardCookTorrancePS(bool transparency,
											   bool vct,
											   bool tsnm);

	/**
	 Creates an forward emissive pixel shader.

	 @pre			The resource manager associated with the current engine 
					must be loaded.
	 @pre			The rendering manager associated with the current engine 
					must be loaded.
	 @param[in]		transparency
					@c true if transparency should be enabled. @c false 
					otherwise.
	 @param[in]		vct
					@c true if voxel cone tracing should be enabled. @c false 
					otherwise.
	 @param[in]		tsnm
					@c true if tangent space normal mapping should be enabled. 
					@c false otherwise.
	 @return		A pointer to the forward emissive pixel shader.
	 @throws		Exception
					Failed to create the pixel shader.
	 */
	PixelShaderPtr CreateForwardEmissivePS(bool transparency);

	/**
	 Creates a forward Frostbite pixel shader.

	 @pre			The resource manager associated with the current engine 
					must be loaded.
	 @pre			The rendering manager associated with the current engine 
					must be loaded.
	 @param[in]		transparency
					@c true if transparency should be enabled. @c false 
					otherwise.
	 @param[in]		vct
					@c true if voxel cone tracing should be enabled. @c false 
					otherwise.
	 @param[in]		tsnm
					@c true if tangent space normal mapping should be enabled. 
					@c false otherwise.
	 @return		A pointer to the forward Frostbite pixel shader.
	 @throws		Exception
					Failed to create the pixel shader.
	 */
	PixelShaderPtr CreateForwardFrostbitePS(bool transparency,
											bool vct,
											bool tsnm);

	/**
	 Creates a forward Lambertian pixel shader.

	 @pre			The resource manager associated with the current engine 
					must be loaded.
	 @pre			The rendering manager associated with the current engine 
					must be loaded.
	 @param[in]		transparency
					@c true if transparency should be enabled. @c false 
					otherwise.
	 @param[in]		vct
					@c true if voxel cone tracing should be enabled. @c false 
					otherwise.
	 @param[in]		tsnm
					@c true if tangent space normal mapping should be enabled. 
					@c false otherwise.
	 @return		A pointer to the forward Lambertian pixel shader.
	 @throws		Exception
					Failed to create the pixel shader.
	 */
	PixelShaderPtr CreateForwardLambertianPS(bool transparency,
											 bool vct,
											 bool tsnm);

	/**
	 Creates a forward Ward-Duer pixel shader.

	 @pre			The resource manager associated with the current engine 
					must be loaded.
	 @pre			The rendering manager associated with the current engine 
					must be loaded.
	 @param[in]		transparency
					@c true if transparency should be enabled. @c false 
					otherwise.
	 @param[in]		vct
					@c true if voxel cone tracing should be enabled. @c false 
					otherwise.
	 @param[in]		tsnm
					@c true if tangent space normal mapping should be enabled. 
					@c false otherwise.
	 @return		A pointer to the forward Ward-Duer pixel shader.
	 @throws		Exception
					Failed to create the pixel shader.
	 */
	PixelShaderPtr CreateForwardWardDuerPS(bool transparency,
										   bool vct,
										   bool tsnm);

	/**
	 Creates a forward pixel shader matching the given BRDF.

	 @pre			The resource manager associated with the current engine 
					must be loaded.
	 @pre			The rendering manager associated with the current engine 
					must be loaded.
	 @param[in]		brdf
					The BRDF type.
	 @param[in]		transparency
					@c true if transparency should be enabled. @c false 
					otherwise.
	 @param[in]		vct
					@c true if voxel cone tracing should be enabled. @c false 
					otherwise.
	 @param[in]		tsnm
					@c true if tangent space normal mapping should be enabled. 
					@c false otherwise.
	 @return		A pointer to the forward pixel shader matching the given 
					BRDF.
	 @throws		Exception
					Failed to create the pixel shader.
	 */
	PixelShaderPtr CreateForwardPS(BRDFType brdf, 
								   bool transparency, 
								   bool vct, 
								   bool tsnm);

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
					@c true if tangent space normal mapping should be enabled. 
					@c false otherwise.
	 @return		A pointer to the GBuffer pixel shader.
	 @throws		Exception
					Failed to create the pixel shader.
	 */
	PixelShaderPtr CreateGBufferPS(bool tsnm);

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
	 An enumeration of the different false colors.
	 
	 This contains:
	 
	 @c ConstantColor,
	 @c ConstantColorTexture,
	 @c BaseColor,
	 @c BaseColorCoefficient,
	 @c BaseColorTexture,
	 @c Material,
	 @c MaterialCoefficient,
	 @c MaterialTexture,
	 @c Roughness,
	 @c RoughnessCoefficient,
	 @c RoughnessTexture,
	 @c Metalness,
	 @c MetalnessCoefficient,
	 @c MetalnessTexture,
	 @c ShadingNormal,
	 @c TSNMShadingNormal, and
	 @c Distance.
	 */
	enum class FalseColor : U8 {
		ConstantColor = 0,
		ConstantColorTexture,
		BaseColor,
		BaseColorCoefficient,
		BaseColorTexture,
		Material,
		MaterialCoefficient,
		MaterialTexture,
		Roughness,
		RoughnessCoefficient,
		RoughnessTexture,
		Metalness,
		MetalnessCoefficient,
		MetalnessTexture,
		ShadingNormal,
		TSNMShadingNormal,
		Distance
	};
	
	/**
	 Creates a false color pixel shader.

	 @pre			The resource manager associated with the current engine 
					must be loaded.
	 @pre			The rendering manager associated with the current engine 
					must be loaded.
	 @param[in]		false_color
					The false color.
	 @return		A pointer to the distance pixel shader.
	 @throws		Exception
					Failed to create the pixel shader.
	 */
	PixelShaderPtr CreateFalseColorPS(FalseColor false_color);
	
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

	#pragma endregion

	//-------------------------------------------------------------------------
	// Factory Methods: Voxelization
	//-------------------------------------------------------------------------
	#pragma region

	/**
	 Creates a voxelization vertex shader.

	 @pre			The resource manager associated with the current engine 
					must be loaded.
	 @pre			The rendering manager associated with the current engine 
					must be loaded.
	 @return		A pointer to the voxelization geometry shader.
	 @throws		Exception
					Failed to create the vertex shader.
	 */
	VertexShaderPtr CreateVoxelizationVS();

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
					@c true if tangent space normal mapping should be enabled. 
					@c false otherwise.
	 @return		A pointer to the voxelization Blinn-Phong pixel shader.
	 @throws		Exception
					Failed to create the pixel shader.
	 */
	PixelShaderPtr CreateVoxelizationBlinnPhongPS(bool tsnm);

	/**
	 Creates a voxelization Cook-Torrance pixel shader.

	 @pre			The resource manager associated with the current engine 
					must be loaded.
	 @pre			The rendering manager associated with the current engine 
					must be loaded.
	 @param[in]		tsnm
					@c true if tangent space normal mapping should be enabled. 
					@c false otherwise.
	 @return		A pointer to the voxelization Cook-Torrance pixel shader.
	 @throws		Exception
					Failed to create the pixel shader.
	 */
	PixelShaderPtr CreateVoxelizationCookTorrancePS(bool tsnm);

	/**
	 Creates a voxelization Frostbite pixel shader.

	 @pre			The resource manager associated with the current engine 
					must be loaded.
	 @pre			The rendering manager associated with the current engine 
					must be loaded.
	 @param[in]		tsnm
					@c true if tangent space normal mapping should be enabled. 
					@c false otherwise.
	 @return		A pointer to the voxelization Frostbite pixel shader.
	 @throws		Exception
					Failed to create the pixel shader.
	 */
	PixelShaderPtr CreateVoxelizationFrostbitePS(bool tsnm);

	/**
	 Creates a voxelization Lambertian pixel shader.

	 @pre			The resource manager associated with the current engine 
					must be loaded.
	 @pre			The rendering manager associated with the current engine 
					must be loaded.
	 @param[in]		tsnm
					@c true if tangent space normal mapping should be enabled. 
					@c false otherwise.
	 @return		A pointer to the voxelization Lambertian pixel shader.
	 @throws		Exception
					Failed to create the pixel shader.
	 */
	PixelShaderPtr CreateVoxelizationLambertianPS(bool tsnm);

	/**
	 Creates a voxelization Ward-Duer pixel shader.

	 @pre			The resource manager associated with the current engine 
					must be loaded.
	 @pre			The rendering manager associated with the current engine 
					must be loaded.
	 @param[in]		tsnm
					@c true if tangent space normal mapping should be enabled. 
					@c false otherwise.
	 @return		A pointer to the voxelization Ward-Duer pixel shader.
	 @throws		Exception
					Failed to create the pixel shader.
	 */
	PixelShaderPtr CreateVoxelizationWardDuerPS(bool tsnm);

	/**
	 Creates a voxelization pixel shader matching the given BRDF.

	 @pre			The resource manager associated with the current engine 
					must be loaded.
	 @pre			The rendering manager associated with the current engine 
					must be loaded.
	 @param[in]		brdf
					The BRDF type.
	 @param[in]		tsnm
					@c true if tangent space normal mapping should be enabled. 
					@c false otherwise.
	 @return		A pointer to the voxelization pixel shader matching the given 
					BRDF.
	 @throws		Exception
					Failed to create the pixel shader.
	 */
	PixelShaderPtr CreateVoxelizationPS(BRDFType brdf, bool tsnm);

	/**
	 Creates a voxelization compute shader.

	 @pre			The resource manager associated with the current engine 
					must be loaded.
	 @pre			The rendering manager associated with the current engine 
					must be loaded.
	 @return		A pointer to the voxelization geometry shader.
	 @throws		Exception
					Failed to create the compute shader.
	 */
	ComputeShaderPtr CreateVoxelizationCS();

	#pragma endregion
}