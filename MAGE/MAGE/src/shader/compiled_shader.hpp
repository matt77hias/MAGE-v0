#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "platform\windows.hpp"
#include "string\string.hpp"

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

		 @param[in]		fname
						A reference to the filename.
		 @throws		FormattedException
						Failed to load the compiled vertex 
						shader from the given file.
		 */
		explicit CompiledVertexShader(const wstring &fname);

		/**
		 Constructs a compiled vertex shader.

		 @pre			@a bytecode is not equal to @c nullptr.
		 @pre			The size of the data pointed to by @a bytecode
						is equal to @a bytecode_size (bytes).
		 @param[in]		name
						A reference to the name of the vertex shader.
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
		const BYTE *m_bytecode;

		/**
		 The size of the bytecode of this compiled vertex shader.
		 */
		SIZE_T m_bytecode_size;
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
		 Constructs a compiled pixel shader.

		 @param[in]		fname
						A reference to the filename.
		 @throws		FormattedException
						Failed to load the compiled pixel 
						shader from the given file.
		 */
		explicit CompiledPixelShader(const wstring &fname);

		/**
		 Constructs a compiled pixel shader.

		 @pre			@a bytecode is not equal to @c nullptr.
		 @pre			The size of the data pointed to by @a bytecode
						is equal to @a bytecode_size (bytes).
		 @param[in]		name
						A reference to the name of the pixel shader.
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
		const BYTE *m_bytecode;

		/**
		 The size of the bytecode of this compiled pixel shader.
		 */
		SIZE_T m_bytecode_size;
	};
}