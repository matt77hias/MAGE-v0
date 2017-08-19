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
	UniquePtr< const CompiledShader > CreateCompiledTransformVS() noexcept;

	/**
	 Returns the compiled emissive pixel shader.

	 @return		A pointer to the compiled emissive pixel shader.
	 */
	UniquePtr< const CompiledShader > CreateCompiledEmissivePS() noexcept;

	/**
	 Returns the compiled Lambertian pixel shader.

	 @return		A pointer to the compiled Lambertian pixel shader.
	 */
	UniquePtr< const CompiledShader > CreateCompiledLambertianPS() noexcept;

	/**
	 Returns the compiled Phong pixel shader.

	 @return		A pointer to the compiled Phong pixel shader.
	 */
	UniquePtr< const CompiledShader > CreateCompiledPhongPS() noexcept;

	/**
	 Returns the compiled Modified Phong pixel shader.

	 @return		A pointer to the compiled Modified Phong pixel shader.
	 */
	UniquePtr< const CompiledShader > CreateCompiledModifiedPhongPS() noexcept;

	/**
	 Returns the compiled Blinn-Phong pixel shader.

	 @return		A pointer to the compiled Blinn-Phong pixel shader.
	 */
	UniquePtr< const CompiledShader > CreateCompiledBlinnPhongPS() noexcept;

	/**
	 Returns the compiled Modified Blinn-Phong pixel shader.

	 @return		A pointer to the compiled Modified Blinn-Phong pixel shader.
	 */
	UniquePtr< const CompiledShader > CreateCompiledModifiedBlinnPhongPS() noexcept;

	/**
	 Returns the compiled Ward pixel shader.

	 @return		A pointer to the compiled Ward pixel shader.
	 */
	UniquePtr< const CompiledShader > CreateCompiledWardPS() noexcept;

	/**
	 Returns the compiled Ward-Duer pixel shader.

	 @return		A pointer to the compiled Ward-Duer pixel shader.
	 */
	UniquePtr< const CompiledShader > CreateCompiledWardDuerPS() noexcept;

	/**
	 Returns the compiled Cook-Torrance pixel shader.

	 @return		A pointer to the compiled Cook-Torrance pixel shader.
	 */
	UniquePtr< const CompiledShader > CreateCompiledCookTorrancePS() noexcept;

	/**
	 Returns the compiled Lambertian tsnm pixel shader.

	 @return		A pointer to the compiled Lambertian tsnm pixel shader.
	 */
	UniquePtr< const CompiledShader > CreateCompiledLambertianTSNMPS() noexcept;

	/**
	 Returns the compiled Phong tsnm pixel shader.

	 @return		A pointer to the compiled Phong tsnm pixel shader.
	 */
	UniquePtr< const CompiledShader > CreateCompiledPhongTSNMPS() noexcept;

	/**
	 Returns the compiled Modified Phong tsnm pixel shader.

	 @return		A pointer to the compiled Modified Phong tsnm pixel shader.
	 */
	UniquePtr< const CompiledShader > CreateCompiledModifiedPhongTSNMPS() noexcept;

	/**
	 Returns the compiled Blinn-Phong tsnm pixel shader.

	 @return		A pointer to the compiled Blinn-Phong tsnm pixel shader.
	 */
	UniquePtr< const CompiledShader > CreateCompiledBlinnPhongTSNMPS() noexcept;

	/**
	 Returns the compiled Modified Blinn-Phong tsnm pixel shader.

	 @return		A pointer to the compiled Modified Blinn-Phong tsnm pixel shader.
	 */
	UniquePtr< const CompiledShader > CreateCompiledModifiedBlinnPhongTSNMPS() noexcept;

	/**
	 Returns the compiled Ward tsnm pixel shader.

	 @return		A pointer to the compiled Ward tsnm pixel shader.
	 */
	UniquePtr< const CompiledShader > CreateCompiledWardTSNMPS() noexcept;

	/**
	 Returns the compiled Ward-Duer tsnm pixel shader.

	 @return		A pointer to the compiled Ward-Duer tsnm pixel shader.
	 */
	UniquePtr< const CompiledShader > CreateCompiledWardDuerTSNMPS() noexcept;

	/**
	 Returns the compiled Cook-Torrance tsnm pixel shader.

	 @return		A pointer to the compiled Cook-Torrance tsnm pixel shader.
	 */
	UniquePtr< const CompiledShader > CreateCompiledCookTorranceTSNMPS() noexcept;

	/**
	 Returns the compiled sprite vertex shader.

	 @return		A pointer to the compiled sprite vertex shader.
	 */
	UniquePtr< const CompiledShader > CreateCompiledSpriteVS() noexcept;

	/**
	 Returns the compiled sprite pixel shader.

	 @return		A pointer to the compiled sprite pixel shader.
	 */
	UniquePtr< const CompiledShader > CreateCompiledSpritePS() noexcept;
}