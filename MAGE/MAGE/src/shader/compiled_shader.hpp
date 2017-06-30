#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "memory\memory.hpp"
#include "rendering\rendering.hpp"
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
	 A struct of compiled shaders.
	 */
	struct CompiledShader {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a compiled shader.

		 @param[in]		fname
						A reference to the filename.
		 @throws		FormattedException
						Failed to load the compiled
						shader from the given file.
		 */
		explicit CompiledShader(const wstring &fname);

		/**
		 Constructs a compiled shader.

		 @pre			@a bytecode is not equal to @c nullptr.
		 @pre			The size of the data pointed to by @a bytecode
						is equal to @a bytecode_size (bytes).
		 @param[in]		bytecode
						A pointer to the shader bytecode.
		 @param[in]		bytecode_size
						The size of the given shader bytecode.
		 */
		explicit CompiledShader(const BYTE *bytecode, SIZE_T bytecode_size);

		/**
		 Constructs a compiled shader from the given compiled shader.

		 @param[in]		compiled_shader
						A reference to the compiled shader to copy.
		 */
		CompiledShader(const CompiledShader &compiled_shader);

		/**
		 Constructs a compiled shader by moving the given compiled shader.

		 @param[in]		compiled_shader
						A reference to the compiled shader to move.
		 */
		CompiledShader(CompiledShader &&compiled_shader);

		/**
		 Destructs this compiled shader.
		 */
		~CompiledShader();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given compiled shader to this compiled shader.

		 @param[in]		compiled_shader
						A reference to the compiled shader to copy.
		 @return		A reference to the copy of the given compiled shader
						(i.e. this compiled shader).
		 */
		CompiledShader &operator=(const CompiledShader &compiled_shader) = delete;

		/**
		 Moves the given compiled shader to this compiled shader.

		 @param[in]		compiled_shader
						A reference to the compiled shader to copy.
		 @return		A reference to the moved compiled shader
						(i.e. this compiled shader).
		 */
		CompiledShader &operator=(CompiledShader &&compiled_shader) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Returns the shader bytecode of this compiled shader.

		 @return		A pointer to the shader bytecode 
						of this compiled shader.
		 */
		const BYTE *GetBytecode() const noexcept {
			return m_bytecode;
		}

		/**
		 Returns the size of the shader bytecode (in bytes) 
		 of this compiled shader.

		 @return		The size of the shader bytecode (in bytes)
						of this compiled shader.
		 */
		SIZE_T GetBytecodeSize() const noexcept {
			return m_bytecode_size;
		}

	private:

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 A pointer to the shader bytecode of this compiled shader.
		 */
		const BYTE *m_bytecode;

		/**
		 The size of the shader bytecode of this compiled shader.
		 */
		SIZE_T m_bytecode_size;

		/**
		 A (optional) pointer to the shader blob of this compiled shader.
		 */
		ComPtr< ID3DBlob > m_shader_blob;
	};

	//-------------------------------------------------------------------------
	// CompiledVertexShader
	//-------------------------------------------------------------------------

	/**
	 A struct of compiled vertex shaders.
	 */
	struct CompiledVertexShader final : public CompiledShader {

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
		 @param[in]		bytecode
						A pointer to the shader bytecode.
		 @param[in]		bytecode_size
						The size of the given shader bytecode.
		 */
		explicit CompiledVertexShader(const BYTE *bytecode, SIZE_T bytecode_size);
		
		/**
		 Constructs a compiled vertex shader from the given compiled vertex shader.

		 @param[in]		compiled_vertex_shader
						A reference to the compiled vertex shader to copy.
		 */
		CompiledVertexShader(const CompiledVertexShader &compiled_vertex_shader);

		/**
		 Constructs a compiled vertex shader by moving the given compiled vertex shader.

		 @param[in]		compiled_vertex_shader
						A reference to the compiled vertex shader to move.
		 */
		CompiledVertexShader(CompiledVertexShader &&compiled_vertex_shader);

		/**
		 Destructs this compiled vertex shader.
		 */
		~CompiledVertexShader();
		
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
	};

	//-------------------------------------------------------------------------
	// CompiledPixelShader
	//-------------------------------------------------------------------------

	/**
	 A struct of compiled pixel shaders.
	 */
	struct CompiledPixelShader final : public CompiledShader {

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
		 @param[in]		bytecode
						A pointer to the shader bytecode.
		 @param[in]		bytecode_size
						The size of the given shader bytecode.
		 */
		explicit CompiledPixelShader(const BYTE *bytecode, SIZE_T bytecode_size);

		/**
		 Constructs a compiled pixel shader from the given compiled pixel shader.

		 @param[in]		compiled_pixel_shader
						A reference to the compiled pixel shader to copy.
		 */
		CompiledPixelShader(const CompiledPixelShader &compiled_pixel_shader);

		/**
		 Constructs a compiled pixel shader by moving the given compiled pixel shader.

		 @param[in]		compiled_pixel_shader
						A reference to the compiled pixel shader to move.
		 */
		CompiledPixelShader(CompiledPixelShader &&compiled_pixel_shader);

		/**
		 Destructs this compiled pixel shader.
		 */
		~CompiledPixelShader();

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
	};
}