#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "shader\compiled_shader.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations
//-----------------------------------------------------------------------------
namespace mage {

	//-------------------------------------------------------------------------
	// Factory Methods: GBufferPass
	//-------------------------------------------------------------------------
#pragma region

	/**
	 Returns the compiled depth vertex shader.

	 @return		A buffer compiled depth vertex shader.
	 */
	const BufferCompiledShader CreateCompiledDepthVS() noexcept;

#pragma endregion

	//-------------------------------------------------------------------------
	// Factory Methods: ConstantShadingPass and VariableShadingPass
	//-------------------------------------------------------------------------
#pragma region

	/**
	 Returns the compiled transform vertex shader.

	 @return		A buffer compiled transform vertex shader.
	 */
	const BufferCompiledShader CreateCompiledTransformVS() noexcept;

	/**
	 Returns the compiled emissive pixel shader.

	 @return		A buffer compiled emissive pixel shader.
	 */
	const BufferCompiledShader CreateCompiledEmissivePS() noexcept;

	/**
	 Returns the compiled Lambertian pixel shader.

	 @return		A buffer compiled Lambertian pixel shader.
	 */
	const BufferCompiledShader CreateCompiledLambertianPS() noexcept;

	/**
	 Returns the compiled Phong pixel shader.

	 @return		A buffer compiled Phong pixel shader.
	 */
	const BufferCompiledShader CreateCompiledPhongPS() noexcept;

	/**
	 Returns the compiled Modified Phong pixel shader.

	 @return		A buffer compiled Modified Phong pixel shader.
	 */
	const BufferCompiledShader CreateCompiledModifiedPhongPS() noexcept;

	/**
	 Returns the compiled Blinn-Phong pixel shader.

	 @return		A buffer compiled Blinn-Phong pixel shader.
	 */
	const BufferCompiledShader CreateCompiledBlinnPhongPS() noexcept;

	/**
	 Returns the compiled Modified Blinn-Phong pixel shader.

	 @return		A buffer compiled Modified Blinn-Phong pixel shader.
	 */
	const BufferCompiledShader CreateCompiledModifiedBlinnPhongPS() noexcept;

	/**
	 Returns the compiled Ward pixel shader.

	 @return		A buffer compiled Ward pixel shader.
	 */
	const BufferCompiledShader CreateCompiledWardPS() noexcept;

	/**
	 Returns the compiled Ward-Duer pixel shader.

	 @return		A buffer compiled Ward-Duer pixel shader.
	 */
	const BufferCompiledShader CreateCompiledWardDuerPS() noexcept;

	/**
	 Returns the compiled Cook-Torrance pixel shader.

	 @return		A buffer compiled Cook-Torrance pixel shader.
	 */
	const BufferCompiledShader CreateCompiledCookTorrancePS() noexcept;

	/**
	 Returns the compiled Lambertian tsnm pixel shader.

	 @return		A buffer compiled Lambertian tsnm pixel shader.
	 */
	const BufferCompiledShader CreateCompiledLambertianTSNMPS() noexcept;

	/**
	 Returns the compiled Phong tsnm pixel shader.

	 @return		A buffer compiled Phong tsnm pixel shader.
	 */
	const BufferCompiledShader CreateCompiledPhongTSNMPS() noexcept;

	/**
	 Returns the compiled Modified Phong tsnm pixel shader.

	 @return		A buffer compiled Modified Phong tsnm pixel shader.
	 */
	const BufferCompiledShader CreateCompiledModifiedPhongTSNMPS() noexcept;

	/**
	 Returns the compiled Blinn-Phong tsnm pixel shader.

	 @return		A buffer compiled Blinn-Phong tsnm pixel shader.
	 */
	const BufferCompiledShader CreateCompiledBlinnPhongTSNMPS() noexcept;

	/**
	 Returns the compiled Modified Blinn-Phong tsnm pixel shader.

	 @return		A buffer compiled Modified Blinn-Phong tsnm pixel shader.
	 */
	const BufferCompiledShader CreateCompiledModifiedBlinnPhongTSNMPS() noexcept;

	/**
	 Returns the compiled Ward tsnm pixel shader.

	 @return		A buffer compiled Ward tsnm pixel shader.
	 */
	const BufferCompiledShader CreateCompiledWardTSNMPS() noexcept;

	/**
	 Returns the compiled Ward-Duer tsnm pixel shader.

	 @return		A buffer compiled Ward-Duer tsnm pixel shader.
	 */
	const BufferCompiledShader CreateCompiledWardDuerTSNMPS() noexcept;

	/**
	 Returns the compiled Cook-Torrance tsnm pixel shader.

	 @return		A buffer compiled Cook-Torrance tsnm pixel shader.
	 */
	const BufferCompiledShader CreateCompiledCookTorranceTSNMPS() noexcept;

#pragma endregion

	//-------------------------------------------------------------------------
	// Factory Methods: GBufferPass
	//-------------------------------------------------------------------------
#pragma region

	/**
	 Returns the compiled GBuffer pixel shader.

	 @return		A buffer compiled GBuffer pixel shader.
	 */
	const BufferCompiledShader CreateCompiledGBufferPS() noexcept;

	/**
	 Returns the compiled GBuffer tsnm pixel shader.

	 @return		A buffer compiled GBuffer tsnm pixel shader.
	 */
	const BufferCompiledShader CreateCompiledGBufferTSNMPS() noexcept;

#pragma endregion

	//-------------------------------------------------------------------------
	// Factory Methods: DeferredShadingPass
	//-------------------------------------------------------------------------
#pragma region

	/**
	 Returns the compiled deferred emissive compute shader.

	 @return		A buffer compiled deferred emissive compute shader.
	 */
	const BufferCompiledShader CreateCompiledDeferredEmissiveCS() noexcept;

	/**
	 Returns the compiled deferred Lambertian compute shader.

	 @return		A buffer compiled deferred Lambertian compute shader.
	 */
	const BufferCompiledShader CreateCompiledDeferredLambertianCS() noexcept;

	/**
	 Returns the compiled deferred Phong compute shader.

	 @return		A buffer compiled deferred Phong compute shader.
	 */
	const BufferCompiledShader CreateCompiledDeferredPhongCS() noexcept;

	/**
	 Returns the compiled deferred Modified Phong compute shader.

	 @return		A buffer compiled deferred Modified Phong compute shader.
	 */
	const BufferCompiledShader CreateCompiledDeferredModifiedPhongCS() noexcept;

	/**
	 Returns the compiled deferred Blinn-Phong compute shader.

	 @return		A buffer compiled deferred Blinn-Phong compute shader.
	 */
	const BufferCompiledShader CreateCompiledDeferredBlinnPhongCS() noexcept;

	/**
	 Returns the compiled deferred Modified Blinn-Phong compute shader.

	 @return		A buffer compiled deferred Modified Blinn-Phong compute shader.
	 */
	const BufferCompiledShader CreateCompiledDeferredModifiedBlinnPhongCS() noexcept;

	/**
	 Returns the compiled deferred Ward compute shader.

	 @return		A buffer compiled deferred Ward compute shader.
	 */
	const BufferCompiledShader CreateCompiledDeferredWardCS() noexcept;

	/**
	 Returns the compiled deferred Ward-Duer compute shader.

	 @return		A buffer compiled deferred Ward-Duer compute shader.
	 */
	const BufferCompiledShader CreateCompiledDeferredWardDuerCS() noexcept;

	/**
	 Returns the compiled deferred Cook-Torrance compute shader.

	 @return		A buffer compiled deferred Cook-Torrance compute shader.
	 */
	const BufferCompiledShader CreateCompiledDeferredCookTorranceCS() noexcept;

#pragma endregion

	//-------------------------------------------------------------------------
	// Factory Methods: SpritePass
	//-------------------------------------------------------------------------
#pragma region

	/**
	 Returns the compiled sprite vertex shader.

	 @return		A buffer compiled sprite vertex shader.
	 */
	const BufferCompiledShader CreateCompiledSpriteVS() noexcept;

	/**
	 Returns the compiled sprite pixel shader.

	 @return		A buffer compiled sprite pixel shader.
	 */
	const BufferCompiledShader CreateCompiledSpritePS() noexcept;

#pragma endregion

	//-------------------------------------------------------------------------
	// Factory Methods: ConstantComponentPass and VariableComponentPass
	//-------------------------------------------------------------------------
#pragma region

	/**
	 Returns the compiled minimal transform vertex shader.

	 @return		A buffer compiled minimal transform vertex shader.
	 */
	const BufferCompiledShader CreateCompiledMinimalTransformVS() noexcept;

	/**
	 Returns the compiled constant color pixel shader.

	 @return		A buffer compiled constant color pixel shader.
	 */
	const BufferCompiledShader CreateCompiledConstantColorPS() noexcept;

	/**
	 Returns the compiled constant color texture pixel shader.

	 @return		A buffer compiled constant color texture pixel shader.
	 */
	const BufferCompiledShader CreateCompiledConstantColorTexturePS() noexcept;

	/**
	 Returns the compiled distance pixel shader.

	 @return		A buffer compiled distance pixel shader.
	 */
	const BufferCompiledShader CreateCompiledDistancePS() noexcept;

#pragma endregion

	//-------------------------------------------------------------------------
	// Factory Methods: ShadingNormalPass
	//-------------------------------------------------------------------------
#pragma region

	/**
	 Returns the compiled shading normal vertex shader.

	 @return		A buffer compiled shading normal vertex shader.
	 */
	const BufferCompiledShader CreateCompiledShadingNormalVS() noexcept;

	/**
	 Returns the compiled shading normal pixel shader.

	 @return		A buffer compiled shading normal pixel shader.
	 */
	const BufferCompiledShader CreateCompiledShadingNormalPS() noexcept;

	/**
	 Returns the compiled tsnm shading normal pixel shader.

	 @return		A buffer compiled tsnm shading normal pixel shader.
	 */
	const BufferCompiledShader CreateCompiledShadingNormalTSNMPS() noexcept;

#pragma endregion

	//-------------------------------------------------------------------------
	// Factory Methods: BoundingVolumePass
	//-------------------------------------------------------------------------
#pragma region

	/**
	 Returns the compiled bounding volume vertex shader.

	 @return		A buffer compiled bounding volume vertex shader.
	 */
	const BufferCompiledShader CreateCompiledBoundingVolumeVS() noexcept;

	/**
	 Returns the compiled bounding volume pixel shader.

	 @return		A buffer compiled bounding volume pixel shader.
	 */
	const BufferCompiledShader CreateCompiledBoundingVolumePS() noexcept;

#pragma endregion

	//-------------------------------------------------------------------------
	// Factory Methods
	//-------------------------------------------------------------------------
#pragma region

	/**
	 Returns the compiled image pixel shader.

	 @return		A buffer compiled image pixel shader.
	 */
	const BufferCompiledShader CreateCompiledImagePS() noexcept;

	/**
	 Returns the compiled multi-sample image pixel shader.

	 @return		A buffer compiled multi-sample image pixel shader.
	 */
	const BufferCompiledShader CreateCompiledMultiSampleImagePS() noexcept;

	/**
	 Returns the compiled fullscreen triangle vertex shader.

	 @return		A buffer compiled fullscreen triangle vertex shader.
	 */
	const BufferCompiledShader CreateCompiledFullscreenTriangleVS() noexcept;

#pragma endregion
}