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

	// Forward declaration.
	class ResourceManager;

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
	ComputeShaderPtr CreateAAPreprocessCS(ResourceManager &resource_manager);

	/**
	 Creates a FXAA compute shader.

	 @param[in]		resource_manager
					A reference to the resource manager.
	 @return		A pointer to the FXAA compute shader.
	 @throws		Exception
					Failed to create the compute shader.
	 */
	ComputeShaderPtr CreateFXAACS(ResourceManager &resource_manager);

	/**
	 Creates a MSAA resolve compute shader.

	 @param[in]		resource_manager
					A reference to the resource manager.
	 @return		A pointer to the MSAA resolve compute shader.
	 @throws		Exception
					Failed to create the compute shader.
	 */
	ComputeShaderPtr CreateMSAAResolveCS(ResourceManager &resource_manager);

	/**
	 Creates a SSAA resolve compute shader.

	 @param[in]		resource_manager
					A reference to the resource manager.
	 @return		A pointer to the SSAA resolve compute shader.
	 @throws		Exception
					Failed to create the compute shader.
	 */
	ComputeShaderPtr CreateSSAAResolveCS(ResourceManager &resource_manager);

	#pragma endregion

	//-------------------------------------------------------------------------
	// Factory Methods: Back Buffer
	//-------------------------------------------------------------------------
	#pragma region

	/**
	 Creates a back buffer pixel shader.

	 @param[in]		resource_manager
					A reference to the resource manager.
	 @return		A pointer to the back buffer pixel shader.
	 @throws		Exception
					Failed to create the pixel shader.
	 */
	PixelShaderPtr CreateBackBufferPS(ResourceManager &resource_manager);

	#pragma endregion
	
	//-------------------------------------------------------------------------
	// Factory Methods: Deferred
	//-------------------------------------------------------------------------
	#pragma region

	/**
	 Creates a deferred Blinn-Phong compute shader.

	 @param[in]		resource_manager
					A reference to the resource manager.
	 @param[in]		vct
					@c true if voxel cone tracing should be enabled. @c false 
					otherwise.
	 @return		A pointer to the deferred Blinn-Phong compute shader.
	 @throws		Exception
					Failed to create the compute shader.
	 */
	ComputeShaderPtr CreateDeferredBlinnPhongCS(ResourceManager &resource_manager, 
												bool vct);

	/**
	 Creates a deferred Cook-Torrance compute shader.

	 @param[in]		resource_manager
					A reference to the resource manager.
	 @param[in]		vct
					@c true if voxel cone tracing should be enabled. @c false 
					otherwise.
	 @return		A pointer to the deferred Cook-Torrance compute shader.
	 @throws		Exception
					Failed to create the compute shader.
	 */
	ComputeShaderPtr CreateDeferredCookTorranceCS(ResourceManager &resource_manager, 
												  bool vct);

	/**
	 Creates a deferred emissive compute shader.

	 @param[in]		resource_manager
					A reference to the resource manager.
	 @return		A pointer to the deferred emissive compute shader.
	 @throws		Exception
					Failed to create the compute shader.
	 */
	ComputeShaderPtr CreateDeferredEmissiveCS(ResourceManager &resource_manager);

	/**
	 Creates a deferred Frostbite compute shader.

	 @param[in]		resource_manager
					A reference to the resource manager.
	 @param[in]		vct
					@c true if voxel cone tracing should be enabled. @c false 
					otherwise.
	 @return		A pointer to the deferred Frostbite compute shader.
	 @throws		Exception
					Failed to create the compute shader.
	 */
	ComputeShaderPtr CreateDeferredFrostbiteCS(ResourceManager &resource_manager, 
											   bool vct);

	/**
	 Creates a deferred Ward-Duer compute shader.

	 @param[in]		resource_manager
					A reference to the resource manager.
	 @param[in]		vct
					@c true if voxel cone tracing should be enabled. @c false
					otherwise.
	 @return		A pointer to the deferred Ward-Duer compute shader.
	 @throws		Exception
					Failed to create the compute shader.
	 */
	ComputeShaderPtr CreateDeferredWardDuerCS(ResourceManager &resource_manager, 
											  bool vct);

	/**
	 Creates a deferred Lambertian compute shader.

	 @param[in]		resource_manager
					A reference to the resource manager.
	 @param[in]		vct
					@c true if voxel cone tracing should be enabled. @c false 
					otherwise.
	 @return		A pointer to the deferred Lambertian compute shader.
	 @throws		Exception
					Failed to create the compute shader.
	 */
	ComputeShaderPtr CreateDeferredLambertianCS(ResourceManager &resource_manager, 
												bool vct);

	/**
	 Creates a deferred compute shader matching the given BRDF.

	 @param[in]		resource_manager
					A reference to the resource manager.
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
	ComputeShaderPtr CreateDeferredCS(ResourceManager &resource_manager, 
									  BRDFType brdf, bool vct);

	/**
	 Creates a deferred MSAA Blinn-Phong pixel shader.

	 @param[in]		resource_manager
					A reference to the resource manager.
	 @param[in]		vct
					@c true if voxel cone tracing should be enabled. @c false 
					otherwise.
	 @return		A pointer to the deferred MSAA Blinn-Phong pixel shader.
	 @throws		Exception
					Failed to create the pixel shader.
	 */
	PixelShaderPtr CreateDeferredMSAABlinnPhongPS(ResourceManager &resource_manager, 
												  bool vct);

	/**
	 Creates a deferred MSAA Cook-Torrance pixel shader.

	 @param[in]		resource_manager
					A reference to the resource manager.
	 @param[in]		vct
					@c true if voxel cone tracing should be enabled. @c false 
					otherwise.
	 @return		A pointer to the deferred MSAA Cook-Torrance pixel shader.
	 @throws		Exception
					Failed to create the pixel shader.
	 */
	PixelShaderPtr CreateDeferredMSAACookTorrancePS(ResourceManager &resource_manager, 
													bool vct);

	/**
	 Creates a deferred MSAA emissive pixel shader.

	 @param[in]		resource_manager
					A reference to the resource manager.
	 @param[in]		vct
					@c true if voxel cone tracing should be enabled. @c false 
					otherwise.
	 @return		A pointer to the deferred MSAA emissive pixel shader.
	 @throws		Exception
					Failed to create the pixel shader.
	 */
	PixelShaderPtr CreateDeferredMSAAEmissivePS(ResourceManager &resource_manager);

	/**
	 Creates a deferred MSAA Frostbite pixel shader.

	 @param[in]		resource_manager
					A reference to the resource manager.
	 @param[in]		vct
					@c true if voxel cone tracing should be enabled. @c false 
					otherwise.
	 @return		A pointer to the deferred MSAA Frostbite pixel shader.
	 @throws		Exception
					Failed to create the pixel shader.
	 */
	PixelShaderPtr CreateDeferredMSAAFrostbitePS(ResourceManager &resource_manager, 
												 bool vct);

	/**
	 Creates a deferred MSAA Ward-Duer pixel shader.

	 @param[in]		resource_manager
					A reference to the resource manager.
	 @param[in]		vct
					@c true if voxel cone tracing should be enabled. @c false 
					otherwise.
	 @return		A pointer to the deferred MSAA Ward-Duer pixel shader.
	 @throws		Exception
					Failed to create the pixel shader.
	 */
	PixelShaderPtr CreateDeferredMSAAWardDuerPS(ResourceManager &resource_manager, 
												bool vct);

	/**
	 Creates a deferred MSAA Lambertian pixel shader.

	 @param[in]		resource_manager
					A reference to the resource manager.
	 @param[in]		vct
					@c true if voxel cone tracing should be enabled. @c false 
					otherwise.
	 @return		A pointer to the deferred MSAA Lambertian pixel shader.
	 @throws		Exception
					Failed to create the pixel shader.
	 */
	PixelShaderPtr CreateDeferredMSAALambertianPS(ResourceManager &resource_manager, 
												  bool vct);

	/**
	 Creates a deferred MSAA pixel shader matching the given BRDF.

	 @param[in]		resource_manager
					A reference to the resource manager.
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
	PixelShaderPtr CreateDeferredMSAAPS(ResourceManager &resource_manager, 
										BRDFType brdf, bool vct);

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
	VertexShaderPtr CreateDepthVS(ResourceManager &resource_manager);

	/**
	 Creates a depth transparent vertex shader.

	 @param[in]		resource_manager
					A reference to the resource manager.
	 @return		A pointer to the depth transparent vertex shader.
	 @throws		Exception
					Failed to create the vertex shader.
	 */
	VertexShaderPtr CreateDepthTransparentVS(ResourceManager &resource_manager);

	/**
	 Creates a depth transparent pixel shader.

	 @param[in]		resource_manager
					A reference to the resource manager.
	 @return		A pointer to the depth transparent pixel shader.
	 @throws		Exception
					Failed to create the pixel shader.
	 */
	PixelShaderPtr CreateDepthTransparentPS(ResourceManager &resource_manager);

	#pragma endregion

	//-------------------------------------------------------------------------
	// Factory Methods: False Color
	//-------------------------------------------------------------------------
	#pragma region

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
	 @c TSNMShadingNormal,
	 @c Depth,
	 @c Distance, and
	 @c UV.
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
		Depth,
		Distance,
		UV
	};
	
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
	PixelShaderPtr CreateFalseColorPS(ResourceManager &resource_manager, 
									  FalseColor false_color);
	
	#pragma endregion
	
	//-------------------------------------------------------------------------
	// Factory Methods: Forward
	//-------------------------------------------------------------------------
	#pragma region

	/**
	 Creates a forward Blinn-Phong pixel shader.

	 @param[in]		resource_manager
					A reference to the resource manager.
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
	PixelShaderPtr CreateForwardBlinnPhongPS(ResourceManager &resource_manager, 
											 bool transparency,
											 bool vct, 
											 bool tsnm);

	/**
	 Creates a forward Cook-Torrance pixel shader.

	 @param[in]		resource_manager
					A reference to the resource manager.
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
	PixelShaderPtr CreateForwardCookTorrancePS(ResourceManager &resource_manager, 
											   bool transparency,
											   bool vct,
											   bool tsnm);

	/**
	 Creates an forward emissive pixel shader.

	 @param[in]		resource_manager
					A reference to the resource manager.
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
	PixelShaderPtr CreateForwardEmissivePS(ResourceManager &resource_manager, 
										   bool transparency);

	/**
	 Creates a forward Frostbite pixel shader.

	 @param[in]		resource_manager
					A reference to the resource manager.
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
	PixelShaderPtr CreateForwardFrostbitePS(ResourceManager &resource_manager, 
											bool transparency,
											bool vct,
											bool tsnm);

	/**
	 Creates a forward Lambertian pixel shader.

	 @param[in]		resource_manager
					A reference to the resource manager.
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
	PixelShaderPtr CreateForwardLambertianPS(ResourceManager &resource_manager, 
											 bool transparency,
											 bool vct,
											 bool tsnm);

	/**
	 Creates a forward Ward-Duer pixel shader.

	 @param[in]		resource_manager
					A reference to the resource manager.
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
	PixelShaderPtr CreateForwardWardDuerPS(ResourceManager &resource_manager, 
										   bool transparency,
										   bool vct,
										   bool tsnm);

	/**
	 Creates a forward pixel shader matching the given BRDF.

	 @param[in]		resource_manager
					A reference to the resource manager.
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
	PixelShaderPtr CreateForwardPS(ResourceManager &resource_manager, 
								   BRDFType brdf,
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
	PixelShaderPtr CreateForwardSolidPS(ResourceManager &resource_manager);

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
	PixelShaderPtr CreateGBufferPS(ResourceManager &resource_manager, 
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
	ComputeShaderPtr CreateDepthOfFieldCS(ResourceManager &resource_manager);

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
	VertexShaderPtr CreateLineCubeVS(ResourceManager &resource_manager);

	/**
	 Creates a line cube pixel shader.

	 @param[in]		resource_manager
					A reference to the resource manager.
	 @return		A pointer to the line cube pixel shader.
	 @throws		Exception
					Failed to create the pixel shader.
	 */
	PixelShaderPtr CreateLineCubePS(ResourceManager &resource_manager);

	/**
	 Creates a far fullscreen triangle vertex shader.

	 @param[in]		resource_manager
					A reference to the resource manager.
	 @return		A pointer to the far fullscreen triangle vertex shader.
	 @throws		Exception
					Failed to create the vertex shader.
	 */
	VertexShaderPtr CreateFarFullscreenTriangleVS(ResourceManager &resource_manager);

	/**
	 Creates a near fullscreen triangle vertex shader.

	 @param[in]		resource_manager
					A reference to the resource manager.
	 @return		A pointer to the near fullscreen triangle vertex shader.
	 @throws		Exception
					Failed to create the vertex shader.
	 */
	VertexShaderPtr CreateNearFullscreenTriangleVS(ResourceManager &resource_manager);

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
	VertexShaderPtr CreateSkyVS(ResourceManager &resource_manager);

	/**
	 Creates a sky pixel shader.

	 @param[in]		resource_manager
					A reference to the resource manager.
	 @return		A pointer to the sky pixel shader.
	 @throws		Exception
					Failed to create the pixel shader.
	 */
	PixelShaderPtr CreateSkyPS(ResourceManager &resource_manager);

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
	VertexShaderPtr CreateSpriteVS(ResourceManager &resource_manager);

	/**
	 Creates a sprite pixel shader.

	 @param[in]		resource_manager
					A reference to the resource manager.
	 @return		A pointer to the sprite pixel shader.
	 @throws		Exception
					Failed to create the pixel shader.
	 */
	PixelShaderPtr CreateSpritePS(ResourceManager &resource_manager);

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
	VertexShaderPtr CreateTransformVS(ResourceManager &resource_manager);

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
	VertexShaderPtr CreateVoxelizationVS(ResourceManager &resource_manager);

	/**
	 Creates a voxelization geometry shader.

	 @param[in]		resource_manager
					A reference to the resource manager.
	 @return		A pointer to the voxelization geometry shader.
	 @throws		Exception
					Failed to create the geometry shader.
	 */
	GeometryShaderPtr CreateVoxelizationGS(ResourceManager &resource_manager);

	/**
	 Creates a voxelization Blinn-Phong pixel shader.

	 @param[in]		resource_manager
					A reference to the resource manager.
	 @param[in]		tsnm
					@c true if tangent space normal mapping should be enabled. 
					@c false otherwise.
	 @return		A pointer to the voxelization Blinn-Phong pixel shader.
	 @throws		Exception
					Failed to create the pixel shader.
	 */
	PixelShaderPtr CreateVoxelizationBlinnPhongPS(ResourceManager &resource_manager, 
												  bool tsnm);

	/**
	 Creates a voxelization Cook-Torrance pixel shader.

	 @param[in]		resource_manager
					A reference to the resource manager.
	 @param[in]		tsnm
					@c true if tangent space normal mapping should be enabled. 
					@c false otherwise.
	 @return		A pointer to the voxelization Cook-Torrance pixel shader.
	 @throws		Exception
					Failed to create the pixel shader.
	 */
	PixelShaderPtr CreateVoxelizationCookTorrancePS(ResourceManager &resource_manager, 
													bool tsnm);

	/**
	 Creates a voxelization Frostbite pixel shader.

	 @param[in]		resource_manager
					A reference to the resource manager.
	 @param[in]		tsnm
					@c true if tangent space normal mapping should be enabled. 
					@c false otherwise.
	 @return		A pointer to the voxelization Frostbite pixel shader.
	 @throws		Exception
					Failed to create the pixel shader.
	 */
	PixelShaderPtr CreateVoxelizationFrostbitePS(ResourceManager &resource_manager, 
												 bool tsnm);

	/**
	 Creates a voxelization Lambertian pixel shader.

	 @param[in]		resource_manager
					A reference to the resource manager.
	 @param[in]		tsnm
					@c true if tangent space normal mapping should be enabled. 
					@c false otherwise.
	 @return		A pointer to the voxelization Lambertian pixel shader.
	 @throws		Exception
					Failed to create the pixel shader.
	 */
	PixelShaderPtr CreateVoxelizationLambertianPS(ResourceManager &resource_manager, 
												  bool tsnm);

	/**
	 Creates a voxelization Ward-Duer pixel shader.

	 @param[in]		resource_manager
					A reference to the resource manager.
	 @param[in]		tsnm
					@c true if tangent space normal mapping should be enabled. 
					@c false otherwise.
	 @return		A pointer to the voxelization Ward-Duer pixel shader.
	 @throws		Exception
					Failed to create the pixel shader.
	 */
	PixelShaderPtr CreateVoxelizationWardDuerPS(ResourceManager &resource_manager, 
												bool tsnm);

	/**
	 Creates a voxelization pixel shader matching the given BRDF.

	 @param[in]		resource_manager
					A reference to the resource manager.
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
	PixelShaderPtr CreateVoxelizationPS(ResourceManager &resource_manager, 
										BRDFType brdf, bool tsnm);

	/**
	 Creates a voxelization compute shader.

	 @param[in]		resource_manager
					A reference to the resource manager.
	 @return		A pointer to the voxelization geometry shader.
	 @throws		Exception
					Failed to create the compute shader.
	 */
	ComputeShaderPtr CreateVoxelizationCS(ResourceManager &resource_manager);

	/**
	 Creates a voxel grid vertex shader.

	 @param[in]		resource_manager
					A reference to the resource manager.
	 @return		A pointer to the voxelization geometry shader.
	 @throws		Exception
					Failed to create the vertex shader.
	 */
	VertexShaderPtr CreateVoxelGridVS(ResourceManager &resource_manager);

	/**
	 Creates a voxel grid geometry shader.

	 @param[in]		resource_manager
					A reference to the resource manager.
	 @return		A pointer to the voxelization geometry shader.
	 @throws		Exception
					Failed to create the geometry shader.
	 */
	GeometryShaderPtr CreateVoxelGridGS(ResourceManager &resource_manager);

	/**
	 Creates a voxel grid pixel shader.

	 @param[in]		resource_manager
					A reference to the resource manager.
	 @return		A pointer to the voxelization geometry shader.
	 @throws		Exception
					Failed to create the pixel shader.
	 */
	PixelShaderPtr CreateVoxelGridPS(ResourceManager &resource_manager);

	#pragma endregion
}