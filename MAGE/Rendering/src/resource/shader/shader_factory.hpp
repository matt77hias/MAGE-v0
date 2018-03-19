#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "renderer\configuration.hpp"
#include "resource\rendering_resource_manager.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations
//-----------------------------------------------------------------------------
namespace mage::rendering {

	//-------------------------------------------------------------------------
	// Factory Methods: Anti-aliasing
	//-------------------------------------------------------------------------
	#pragma region

	/**
	 Creates a AA preprocess compute shader.

	 @param[in]		resource_manager
					A reference to the resource manager.
	 @return		A pointer to the AA preprocess compute shader.
	 @throws		Exception
					Failed to create the compute shader.
	 */
	ComputeShaderPtr CreateAAPreprocessCS(ResourceManager& resource_manager);

	/**
	 Creates a FXAA compute shader.

	 @param[in]		resource_manager
					A reference to the resource manager.
	 @return		A pointer to the FXAA compute shader.
	 @throws		Exception
					Failed to create the compute shader.
	 */
	ComputeShaderPtr CreateFXAACS(ResourceManager& resource_manager);

	/**
	 Creates a MSAA resolve compute shader.

	 @param[in]		resource_manager
					A reference to the resource manager.
	 @return		A pointer to the MSAA resolve compute shader.
	 @throws		Exception
					Failed to create the compute shader.
	 */
	ComputeShaderPtr CreateMSAAResolveCS(ResourceManager& resource_manager);

	/**
	 Creates a SSAA resolve compute shader.

	 @param[in]		resource_manager
					A reference to the resource manager.
	 @return		A pointer to the SSAA resolve compute shader.
	 @throws		Exception
					Failed to create the compute shader.
	 */
	ComputeShaderPtr CreateSSAAResolveCS(ResourceManager& resource_manager);

	#pragma endregion

	//-------------------------------------------------------------------------
	// Factory Methods: Back Buffer
	//-------------------------------------------------------------------------
	#pragma region

	/**
	 Creates a back buffer pixel shader.

	 @param[in]		resource_manager
					A reference to the resource manager.
	 @param[in]		tone_mapping
					The tone mapping function.
	 @return		A pointer to the back buffer pixel shader.
	 @throws		Exception
					Failed to create the pixel shader.
	 */
	PixelShaderPtr CreateBackBufferPS(ResourceManager& resource_manager, 
									  ToneMapping tone_mapping);

	#pragma endregion
	
	//-------------------------------------------------------------------------
	// Factory Methods: Deferred
	//-------------------------------------------------------------------------
	#pragma region

	/**
	 Creates a deferred emissive compute shader.

	 @param[in]		resource_manager
					A reference to the resource manager.
	 @return		A pointer to the deferred emissive compute shader.
	 @throws		Exception
					Failed to create the compute shader.
	 */
	ComputeShaderPtr CreateDeferredEmissiveCS(ResourceManager& resource_manager);

	/**
	 Creates a deferred compute shader matching the given BRDF.

	 @param[in]		resource_manager
					A reference to the resource manager.
	 @param[in]		brdf
					The BRDF function.
	 @param[in]		vct
					@c true if voxel cone tracing should be enabled. @c false 
					otherwise.
	 @return		A pointer to the deferred compute shader matching the given 
					BRDF.
	 @throws		Exception
					Failed to create the compute shader.
	 */
	ComputeShaderPtr CreateDeferredCS(ResourceManager& resource_manager, 
									  BRDF brdf, bool vct);

	/**
	 Creates a deferred MSAA emissive pixel shader.

	 @param[in]		resource_manager
					A reference to the resource manager.
	 @return		A pointer to the deferred MSAA emissive pixel shader.
	 @throws		Exception
					Failed to create the pixel shader.
	 */
	PixelShaderPtr CreateDeferredMSAAEmissivePS(ResourceManager& resource_manager);

	/**
	 Creates a deferred MSAA pixel shader matching the given BRDF.

	 @param[in]		resource_manager
					A reference to the resource manager.
	 @param[in]		brdf
					The BRDF function.
	 @param[in]		vct
					@c true if voxel cone tracing should be enabled. @c false 
					otherwise.
	 @return		A pointer to the deferred MSAA pixel shader matching the 
					given BRDF.
	 @throws		Exception
					Failed to create the pixel shader.
	 */
	PixelShaderPtr CreateDeferredMSAAPS(ResourceManager& resource_manager, 
										BRDF brdf, bool vct);

	#pragma endregion

	//-------------------------------------------------------------------------
	// Factory Methods: Depth
	//-------------------------------------------------------------------------
	#pragma region

	/**
	 Creates a depth vertex shader.

	 @param[in]		resource_manager
					A reference to the resource manager.
	 @return		A pointer to the depth vertex shader.
	 @throws		Exception
					Failed to create the vertex shader.
	 */
	VertexShaderPtr CreateDepthVS(ResourceManager& resource_manager);

	/**
	 Creates a depth transparent vertex shader.

	 @param[in]		resource_manager
					A reference to the resource manager.
	 @return		A pointer to the depth transparent vertex shader.
	 @throws		Exception
					Failed to create the vertex shader.
	 */
	VertexShaderPtr CreateDepthTransparentVS(ResourceManager& resource_manager);

	/**
	 Creates a depth transparent pixel shader.

	 @param[in]		resource_manager
					A reference to the resource manager.
	 @return		A pointer to the depth transparent pixel shader.
	 @throws		Exception
					Failed to create the pixel shader.
	 */
	PixelShaderPtr CreateDepthTransparentPS(ResourceManager& resource_manager);

	#pragma endregion

	//-------------------------------------------------------------------------
	// Factory Methods: False Color
	//-------------------------------------------------------------------------
	#pragma region

	/**
	 Creates a false color pixel shader.

	 @param[in]		resource_manager
					A reference to the resource manager.
	 @param[in]		false_color
					The false color.
	 @return		A pointer to the distance pixel shader.
	 @throws		Exception
					Failed to create the pixel shader.
	 */
	PixelShaderPtr CreateFalseColorPS(ResourceManager& resource_manager, 
									  FalseColor false_color);
	
	#pragma endregion
	
	//-------------------------------------------------------------------------
	// Factory Methods: Forward
	//-------------------------------------------------------------------------
	#pragma region

	/**
	 Creates an forward emissive pixel shader.

	 @param[in]		resource_manager
					A reference to the resource manager.
	 @param[in]		transparency
					@c true if transparency should be enabled. @c false 
					otherwise.
	 @return		A pointer to the forward emissive pixel shader.
	 @throws		Exception
					Failed to create the pixel shader.
	 */
	PixelShaderPtr CreateForwardEmissivePS(ResourceManager& resource_manager, 
										   bool transparency);

	/**
	 Creates a forward pixel shader matching the given BRDF.

	 @param[in]		resource_manager
					A reference to the resource manager.
	 @param[in]		brdf
					The BRDF function.
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
	PixelShaderPtr CreateForwardPS(ResourceManager& resource_manager, 
								   BRDF brdf,
								   bool transparency, 
								   bool vct, 
								   bool tsnm);

	/**
	 Creates a forward solid pixel shader.

	 @param[in]		resource_manager
					A reference to the resource manager.
	 @return		A pointer to the forward Lambertian pixel shader.
	 @throws		Exception
					Failed to create the pixel shader.
	 */
	PixelShaderPtr CreateForwardSolidPS(ResourceManager& resource_manager);

	#pragma endregion

	//-------------------------------------------------------------------------
	// Factory Methods: GBuffer
	//-------------------------------------------------------------------------
	#pragma region

	/**
	 Creates a GBuffer pixel shader.

	 @param[in]		resource_manager
					A reference to the resource manager.
	 @param[in]		tsnm
					@c true if tangent space normal mapping should be enabled. 
					@c false otherwise.
	 @return		A pointer to the GBuffer pixel shader.
	 @throws		Exception
					Failed to create the pixel shader.
	 */
	PixelShaderPtr CreateGBufferPS(ResourceManager& resource_manager, 
								   bool tsnm);

	#pragma endregion

	//-------------------------------------------------------------------------
	// Factory Methods: Post-processing
	//-------------------------------------------------------------------------
	#pragma region

	/**
	 Creates a depth-of-field compute shader.

	 @param[in]		resource_manager
					A reference to the resource manager.
	 @return		A pointer to the depth-of-field compute shader.
	 @throws		Exception
					Failed to create the compute shader.
	 */
	ComputeShaderPtr CreateDepthOfFieldCS(ResourceManager& resource_manager);

	#pragma endregion

	//-------------------------------------------------------------------------
	// Factory Methods: Primitive
	//-------------------------------------------------------------------------
	#pragma region

	/**
	 Creates a line cube vertex shader.

	 @param[in]		resource_manager
					A reference to the resource manager.
	 @return		A pointer to the line cube vertex shader.
	 @throws		Exception
					Failed to create the vertex shader.
	 */
	VertexShaderPtr CreateLineCubeVS(ResourceManager& resource_manager);

	/**
	 Creates a line cube pixel shader.

	 @param[in]		resource_manager
					A reference to the resource manager.
	 @return		A pointer to the line cube pixel shader.
	 @throws		Exception
					Failed to create the pixel shader.
	 */
	PixelShaderPtr CreateLineCubePS(ResourceManager& resource_manager);

	/**
	 Creates a far fullscreen triangle vertex shader.

	 @param[in]		resource_manager
					A reference to the resource manager.
	 @return		A pointer to the far fullscreen triangle vertex shader.
	 @throws		Exception
					Failed to create the vertex shader.
	 */
	VertexShaderPtr CreateFarFullscreenTriangleVS(ResourceManager& resource_manager);

	/**
	 Creates a near fullscreen triangle vertex shader.

	 @param[in]		resource_manager
					A reference to the resource manager.
	 @return		A pointer to the near fullscreen triangle vertex shader.
	 @throws		Exception
					Failed to create the vertex shader.
	 */
	VertexShaderPtr CreateNearFullscreenTriangleVS(ResourceManager& resource_manager);

	#pragma endregion

	//-------------------------------------------------------------------------
	// Factory Methods: Sky
	//-------------------------------------------------------------------------
	#pragma region

	/**
	 Creates a sky vertex shader.

	 @param[in]		resource_manager
					A reference to the resource manager.
	 @return		A pointer to the sky vertex shader.
	 @throws		Exception
					Failed to create the vertex shader.
	 */
	VertexShaderPtr CreateSkyVS(ResourceManager& resource_manager);

	/**
	 Creates a sky pixel shader.

	 @param[in]		resource_manager
					A reference to the resource manager.
	 @return		A pointer to the sky pixel shader.
	 @throws		Exception
					Failed to create the pixel shader.
	 */
	PixelShaderPtr CreateSkyPS(ResourceManager& resource_manager);

	#pragma endregion

	//-------------------------------------------------------------------------
	// Factory Methods: Sprite
	//-------------------------------------------------------------------------
	#pragma region

	/**
	 Creates a sprite vertex shader.

	 @param[in]		resource_manager
					A reference to the resource manager.
	 @return		A pointer to the sprite vertex shader.
	 @throws		Exception
					Failed to create the vertex shader.
	 */
	VertexShaderPtr CreateSpriteVS(ResourceManager& resource_manager);

	/**
	 Creates a sprite pixel shader.

	 @param[in]		resource_manager
					A reference to the resource manager.
	 @return		A pointer to the sprite pixel shader.
	 @throws		Exception
					Failed to create the pixel shader.
	 */
	PixelShaderPtr CreateSpritePS(ResourceManager& resource_manager);

	#pragma endregion

	//-------------------------------------------------------------------------
	// Factory Methods: Transform
	//-------------------------------------------------------------------------
	#pragma region

	/**
	 Creates a transform vertex shader.

	 @param[in]		resource_manager
					A reference to the resource manager.
	 @return		A pointer to the transform vertex shader.
	 @throws		Exception
					Failed to create the vertex shader.
	 */
	VertexShaderPtr CreateTransformVS(ResourceManager& resource_manager);

	#pragma endregion

	//-------------------------------------------------------------------------
	// Factory Methods: Voxelization
	//-------------------------------------------------------------------------
	#pragma region

	/**
	 Creates a voxelization vertex shader.

	 @param[in]		resource_manager
					A reference to the resource manager.
	 @return		A pointer to the voxelization geometry shader.
	 @throws		Exception
					Failed to create the vertex shader.
	 */
	VertexShaderPtr CreateVoxelizationVS(ResourceManager& resource_manager);

	/**
	 Creates a voxelization geometry shader.

	 @param[in]		resource_manager
					A reference to the resource manager.
	 @return		A pointer to the voxelization geometry shader.
	 @throws		Exception
					Failed to create the geometry shader.
	 */
	GeometryShaderPtr CreateVoxelizationGS(ResourceManager& resource_manager);

	/**
	 Creates a voxelization pixel shader matching the given BRDF.

	 @param[in]		resource_manager
					A reference to the resource manager.
	 @param[in]		brdf
					The BRDF function.
	 @param[in]		tsnm
					@c true if tangent space normal mapping should be enabled. 
					@c false otherwise.
	 @return		A pointer to the voxelization pixel shader matching the given 
					BRDF.
	 @throws		Exception
					Failed to create the pixel shader.
	 */
	PixelShaderPtr CreateVoxelizationPS(ResourceManager& resource_manager, 
										BRDF brdf, bool tsnm);

	/**
	 Creates a voxelization compute shader.

	 @param[in]		resource_manager
					A reference to the resource manager.
	 @return		A pointer to the voxelization geometry shader.
	 @throws		Exception
					Failed to create the compute shader.
	 */
	ComputeShaderPtr CreateVoxelizationCS(ResourceManager& resource_manager);

	/**
	 Creates a voxel grid vertex shader.

	 @param[in]		resource_manager
					A reference to the resource manager.
	 @return		A pointer to the voxelization geometry shader.
	 @throws		Exception
					Failed to create the vertex shader.
	 */
	VertexShaderPtr CreateVoxelGridVS(ResourceManager& resource_manager);

	/**
	 Creates a voxel grid geometry shader.

	 @param[in]		resource_manager
					A reference to the resource manager.
	 @return		A pointer to the voxelization geometry shader.
	 @throws		Exception
					Failed to create the geometry shader.
	 */
	GeometryShaderPtr CreateVoxelGridGS(ResourceManager& resource_manager);

	/**
	 Creates a voxel grid pixel shader.

	 @param[in]		resource_manager
					A reference to the resource manager.
	 @return		A pointer to the voxelization geometry shader.
	 @throws		Exception
					Failed to create the pixel shader.
	 */
	PixelShaderPtr CreateVoxelGridPS(ResourceManager& resource_manager);

	#pragma endregion
}