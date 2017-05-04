#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "platform\windows.hpp"
#include "string\string.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Defines
//-----------------------------------------------------------------------------
#pragma region

#define MAGE_GUID_TRANSFORM_VS L"transform_vs"
#define MAGE_GUID_DIFFUSE_PS L"diffuse_ps"
#define MAGE_GUID_LAMBERTIAN_PS L"lambertian_ps"
#define MAGE_GUID_PHONG_PS L"phong_ps"
#define MAGE_GUID_BLINN_PHONG_PS L"blinn_phong_ps"
#define MAGE_GUID_MODIFIED_BLINN_PHONG_PS L"modified_blinn_phong_ps"
#define MAGE_GUID_SPRITE_VS L"sprite_vs"
#define MAGE_GUID_SPRITE_PS L"sprite_ps"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	//-------------------------------------------------------------------------
	// CompiledVertexShader
	//-------------------------------------------------------------------------

	/**
	 A struct of compiled vertex shaders.
	 */
	struct CompiledVertexShader final {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a compiled vertex shader.

		 @pre			@a bytecode is not equal to @c nullptr.
		 @pre			The size of the data pointed to by @a bytecode
						is equal to @a bytecode_size (bytes).
		 @param[in]		name
						A reference to the name of the shader.
		 @param[in]		bytecode
						A pointer to the shader bytecode.
		 @param[in]		bytecode_size
						The size of the given shader bytecode.
		 */
		explicit CompiledVertexShader(const wstring &name, const BYTE *bytecode, SIZE_T bytecode_size)
			: m_name(name), m_bytecode(bytecode), m_bytecode_size(bytecode_size) {}
		
		/**
		 Constructs a compiled vertex shader from the given compiled vertex shader.

		 @param[in]		compiled_vertex_shader
						A reference to the compiled vertex shader to copy.
		 */
		CompiledVertexShader(const CompiledVertexShader &compiled_vertex_shader) = default;

		/**
		 Constructs a compiled vertex shader by moving the given compiled vertex shader.

		 @param[in]		compiled_vertex_shader
						A reference to the compiled vertex shader to move.
		 */
		CompiledVertexShader(CompiledVertexShader &&compiled_vertex_shader) = default;

		/**
		 Destructs this compiled vertex shader.
		 */
		~CompiledVertexShader() = default;
		
		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------
		
		/**
		 Copies the given compiled vertex shader to this compiled vertex shader.

		 @param[in]		compiled_vertex_shader
						A reference to the compiled vertex shader to copy.
		 @return		A reference to the copy of the given compiled vertex shader
						(i.e. this compiled vertex shader).
		 */
		CompiledVertexShader &operator=(const CompiledVertexShader &compiled_vertex_shader) = delete;

		/**
		 Moves the given compiled vertex shader to this compiled vertex shader.

		 @param[in]		compiled_vertex_shader
						A reference to the compiled vertex shader to copy.
		 @return		A reference to the moved compiled vertex shader
						(i.e. this compiled vertex shader).
		 */
		CompiledVertexShader &operator=(CompiledVertexShader &&compiled_vertex_shader) = delete;

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 The name of this compiled vertex shader.
		 */
		const wstring m_name;

		/**
		 A pointer to the bytecode of this compiled vertex shader.
		 */
		const BYTE * const m_bytecode;

		/**
		 The size of the bytecode of this compiled vertex shader.
		 */
		const SIZE_T m_bytecode_size;
	};

	//-------------------------------------------------------------------------
	// CompiledPixelShader
	//-------------------------------------------------------------------------

	/**
	 A struct of compiled pixel shaders.
	 */
	struct CompiledPixelShader final {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a compiled shader.

		 @pre			@a bytecode is not equal to @c nullptr.
		 @pre			The size of the data pointed to by @a bytecode
						is equal to @a bytecode_size (bytes).
		 @param[in]		name
						A reference to the name of the shader.
		 @param[in]		bytecode
						A pointer to the shader bytecode.
		 @param[in]		bytecode_size
						The size of the given shader bytecode.
		 */
		explicit CompiledPixelShader(const wstring &name, const BYTE *bytecode, SIZE_T bytecode_size)
			: m_name(name), m_bytecode(bytecode), m_bytecode_size(bytecode_size) {}

		/**
		 Constructs a compiled pixel shader from the given compiled pixel shader.

		 @param[in]		compiled_pixel_shader
						A reference to the compiled pixel shader to copy.
		 */
		CompiledPixelShader(const CompiledPixelShader &compiled_pixel_shader) = default;

		/**
		 Constructs a compiled pixel shader by moving the given compiled pixel shader.

		 @param[in]		compiled_pixel_shader
						A reference to the compiled pixel shader to move.
		 */
		CompiledPixelShader(CompiledPixelShader &&compiled_pixel_shader) = default;

		/**
		 Destructs this compiled pixel shader.
		 */
		~CompiledPixelShader() = default;

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given compiled pixel shader to this compiled pixel shader.

		 @param[in]		compiled_pixel_shader
						A reference to the compiled pixel shader to copy.
		 @return		A reference to the copy of the given compiled pixel shader
						(i.e. this compiled pixel shader).
		 */
		CompiledPixelShader &operator=(const CompiledPixelShader &compiled_pixel_shader) = delete;

		/**
		 Moves the given compiled pixel shader to this compiled pixel shader.

		 @param[in]		compiled_pixel_shader
						A reference to the compiled pixel shader to copy.
		 @return		A reference to the moved compiled pixel shader
						(i.e. this compiled pixel shader).
		 */
		CompiledPixelShader &operator=(CompiledPixelShader &&compiled_pixel_shader) = delete;

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 The name of this compiled pixel shader.
		 */
		const wstring m_name;

		/**
		 A pointer to the bytecode of this compiled pixel shader.
		 */
		const BYTE * const m_bytecode;

		/**
		 The size of the bytecode of this compiled pixel shader.
		 */
		const SIZE_T m_bytecode_size;
	};

	//-------------------------------------------------------------------------
	// Factory Methods
	//-------------------------------------------------------------------------

	/**
	 Returns the compiled transform vertex shader.

	 @return		The compiled transform vertex shader.
	 */
	const CompiledVertexShader CreateCompiledTransformVertexShader();

	/**
	 Returns the compiled diffuse pixel shader.

	 @return		The compiled diffuse pixel shader.
	 */
	const CompiledPixelShader CreateCompiledDiffusePixelShader();

	/**
	 Returns the compiled Lambertian pixel shader.

	 @return		The compiled Lambertian pixel shader.
	 */
	const CompiledPixelShader CreateCompiledLambertianPixelShader();

	/**
	 Returns the compiled Phong pixel shader.

	 @return		The compiled Phong pixel shader.
	 */
	const CompiledPixelShader CreateCompiledPhongPixelShader();

	/**
	 Returns the compiled Blinn-Phong pixel shader.

	 @return		The compiled Blinn-Phong pixel shader.
	 */
	const CompiledPixelShader CreateCompiledBlinnPhongPixelShader();

	/**
	 Returns the compiled Modified Blinn-Phong pixel shader.

	 @return		The compiled Modified Blinn-Phong pixel shader.
	 */
	const CompiledPixelShader CreateCompiledModifiedBlinnPhongPixelShader();

	/**
	 Returns the compiled sprite vertex shader.

	 @return		The compiled sprite vertex shader.
	 */
	const CompiledVertexShader CreateCompiledSpriteVertexShader();

	/**
	 Returns the compiled sprite pixel shader.

	 @return		The compiled sprite pixel shader.
	 */
	const CompiledPixelShader CreateCompiledSpritePixelShader();
}