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
	// Factory Methods: ConstantShadingPass and VariableShadingPass
	//-------------------------------------------------------------------------

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

	//-------------------------------------------------------------------------
	// Factory Methods: GBufferPass
	//-------------------------------------------------------------------------

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

	//-------------------------------------------------------------------------
	// Factory Methods: DeferredShadingPass
	//-------------------------------------------------------------------------

	/**
	 Returns the compiled deferred transform vertex shader.

	 @return		A buffer compiled deferred transform vertex shader.
	 */
	const BufferCompiledShader CreateCompiledDeferredTransformVS() noexcept;

	/**
	 Returns the compiled deferred emissive pixel shader.

	 @return		A buffer compiled deferred emissive pixel shader.
	 */
	const BufferCompiledShader CreateCompiledDeferredEmissivePS() noexcept;

	/**
	 Returns the compiled deferred Lambertian pixel shader.

	 @return		A buffer compiled deferred Lambertian pixel shader.
	 */
	const BufferCompiledShader CreateCompiledDeferredLambertianPS() noexcept;

	/**
	 Returns the compiled deferred Phong pixel shader.

	 @return		A buffer compiled deferred Phong pixel shader.
	 */
	const BufferCompiledShader CreateCompiledDeferredPhongPS() noexcept;

	/**
	 Returns the compiled deferred Modified Phong pixel shader.

	 @return		A buffer compiled deferred Modified Phong pixel shader.
	 */
	const BufferCompiledShader CreateCompiledDeferredModifiedPhongPS() noexcept;

	/**
	 Returns the compiled deferred Blinn-Phong pixel shader.

	 @return		A buffer compiled deferred Blinn-Phong pixel shader.
	 */
	const BufferCompiledShader CreateCompiledDeferredBlinnPhongPS() noexcept;

	/**
	 Returns the compiled deferred Modified Blinn-Phong pixel shader.

	 @return		A buffer compiled deferred Modified Blinn-Phong pixel shader.
	 */
	const BufferCompiledShader CreateCompiledDeferredModifiedBlinnPhongPS() noexcept;

	/**
	 Returns the compiled deferred Ward pixel shader.

	 @return		A buffer compiled deferred Ward pixel shader.
	 */
	const BufferCompiledShader CreateCompiledDeferredWardPS() noexcept;

	/**
	 Returns the compiled deferred Ward-Duer pixel shader.

	 @return		A buffer compiled deferred Ward-Duer pixel shader.
	 */
	const BufferCompiledShader CreateCompiledDeferredWardDuerPS() noexcept;

	/**
	 Returns the compiled deferred Cook-Torrance pixel shader.

	 @return		A buffer compiled deferred Cook-Torrance pixel shader.
	 */
	const BufferCompiledShader CreateCompiledDeferredCookTorrancePS() noexcept;

	//-------------------------------------------------------------------------
	// Factory Methods: SpritePass
	//-------------------------------------------------------------------------

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

	//-------------------------------------------------------------------------
	// Factory Methods: ConstantComponentPass and VariableComponentPass
	//-------------------------------------------------------------------------

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

	//-------------------------------------------------------------------------
	// Factory Methods: ShadingNormalPass
	//-------------------------------------------------------------------------

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

	//-------------------------------------------------------------------------
	// Factory Methods: WireframePass
	//-------------------------------------------------------------------------

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
}