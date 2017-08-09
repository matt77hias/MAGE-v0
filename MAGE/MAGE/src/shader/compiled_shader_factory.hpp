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
	// Factory Methods
	//-------------------------------------------------------------------------

	/**
	 Returns the compiled transform vertex shader.

	 @return		A pointer to the compiled transform vertex shader.
	 */
	UniquePtr< CompiledShader > CreateCompiledTransformVertexShader() noexcept;

	/**
	 Returns the compiled emissive pixel shader.

	 @return		A pointer to the compiled emissive pixel shader.
	 */
	UniquePtr< CompiledShader > CreateCompiledEmissivePixelShader() noexcept;

	/**
	 Returns the compiled Lambertian pixel shader.

	 @return		A pointer to the compiled Lambertian pixel shader.
	 */
	UniquePtr< CompiledShader > CreateCompiledLambertianPixelShader() noexcept;

	/**
	 Returns the compiled Phong pixel shader.

	 @return		A pointer to the compiled Phong pixel shader.
	 */
	UniquePtr< CompiledShader > CreateCompiledPhongPixelShader() noexcept;

	/**
	 Returns the compiled Modified Phong pixel shader.

	 @return		A pointer to the compiled Modified Phong pixel shader.
	 */
	UniquePtr< CompiledShader > CreateCompiledModifiedPhongPixelShader() noexcept;

	/**
	 Returns the compiled Blinn-Phong pixel shader.

	 @return		A pointer to the compiled Blinn-Phong pixel shader.
	 */
	UniquePtr< CompiledShader > CreateCompiledBlinnPhongPixelShader() noexcept;

	/**
	 Returns the compiled Modified Blinn-Phong pixel shader.

	 @return		A pointer to the compiled Modified Blinn-Phong pixel shader.
	 */
	UniquePtr< CompiledShader > CreateCompiledModifiedBlinnPhongPixelShader() noexcept;

	/**
	 Returns the compiled Ward pixel shader.

	 @return		A pointer to the compiled Ward pixel shader.
	 */
	UniquePtr< CompiledShader > CreateCompiledWardPixelShader() noexcept;

	/**
	 Returns the compiled Ward-Duer pixel shader.

	 @return		A pointer to the compiled Ward-Duer pixel shader.
	 */
	UniquePtr< CompiledShader > CreateCompiledWardDuerPixelShader() noexcept;

	/**
	 Returns the compiled Cook-Torrance pixel shader.

	 @return		A pointer to the compiled Cook-Torrance pixel shader.
	 */
	UniquePtr< CompiledShader > CreateCompiledCookTorrancePixelShader() noexcept;

	/**
	 Returns the compiled Lambertian tsnm pixel shader.

	 @return		A pointer to the compiled Lambertian tsnm pixel shader.
	 */
	UniquePtr< CompiledShader > CreateCompiledLambertianTSNMPixelShader() noexcept;

	/**
	 Returns the compiled Phong tsnm pixel shader.

	 @return		A pointer to the compiled Phong tsnm pixel shader.
	 */
	UniquePtr< CompiledShader > CreateCompiledPhongTSNMPixelShader() noexcept;

	/**
	 Returns the compiled Modified Phong tsnm pixel shader.

	 @return		A pointer to the compiled Modified Phong tsnm pixel shader.
	 */
	UniquePtr< CompiledShader > CreateCompiledModifiedPhongTSNMPixelShader() noexcept;

	/**
	 Returns the compiled Blinn-Phong tsnm pixel shader.

	 @return		A pointer to the compiled Blinn-Phong tsnm pixel shader.
	 */
	UniquePtr< CompiledShader > CreateCompiledBlinnPhongTSNMPixelShader() noexcept;

	/**
	 Returns the compiled Modified Blinn-Phong tsnm pixel shader.

	 @return		A pointer to the compiled Modified Blinn-Phong tsnm pixel shader.
	 */
	UniquePtr< CompiledShader > CreateCompiledModifiedBlinnPhongTSNMPixelShader() noexcept;

	/**
	 Returns the compiled Ward tsnm pixel shader.

	 @return		A pointer to the compiled Ward tsnm pixel shader.
	 */
	UniquePtr< CompiledShader > CreateCompiledWardTSNMPixelShader() noexcept;

	/**
	 Returns the compiled Ward-Duer tsnm pixel shader.

	 @return		A pointer to the compiled Ward-Duer tsnm pixel shader.
	 */
	UniquePtr< CompiledShader > CreateCompiledWardDuerTSNMPixelShader() noexcept;

	/**
	 Returns the compiled Cook-Torrance tsnm pixel shader.

	 @return		A pointer to the compiled Cook-Torrance tsnm pixel shader.
	 */
	UniquePtr< CompiledShader > CreateCompiledCookTorranceTSNMPixelShader() noexcept;

	/**
	 Returns the compiled sprite vertex shader.

	 @return		A pointer to the compiled sprite vertex shader.
	 */
	UniquePtr< CompiledShader > CreateCompiledSpriteVertexShader() noexcept;

	/**
	 Returns the compiled sprite pixel shader.

	 @return		A pointer to the compiled sprite pixel shader.
	 */
	UniquePtr< CompiledShader > CreateCompiledSpritePixelShader() noexcept;
}