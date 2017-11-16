#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "utils\type\types.hpp"
#include "rendering\pipeline.hpp"

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
		// Destructors
		//---------------------------------------------------------------------

		/**
		 Destructs this compiled shader.
		 */
		virtual ~CompiledShader();

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
		CompiledShader &operator=(
			const CompiledShader &compiled_shader) = delete;

		/**
		 Moves the given compiled shader to this compiled shader.
		 
		 @param[in]		compiled_shader
						A reference to the compiled shader to copy.
		 @return		A reference to the moved compiled shader (i.e. this 
						compiled shader).
		 */
		CompiledShader &operator=(
			CompiledShader &&compiled_shader) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Returns the shader bytecode of this compiled shader.
		 
		 @return		A pointer to the shader bytecode of this compiled 
						shader.
		 */
		virtual const BYTE *GetBytecode() const noexcept = 0;

		/**
		 Returns the size of the shader bytecode (in bytes) of this compiled 
		 shader.
		 
		 @return		The size of the shader bytecode (in bytes) of this 
						compiled shader.
		 */
		virtual SIZE_T GetBytecodeSize() const noexcept = 0;
		
	protected:
	
		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a compiled shader.
		 */
		CompiledShader();

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
	};

	//-------------------------------------------------------------------------
	// BufferCompiledShader
	//-------------------------------------------------------------------------

	/**
	 A struct of buffer compiled shaders.
	 */
	struct BufferCompiledShader : public CompiledShader {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a buffer compiled shader.
		 
		 @pre			@a bytecode is not equal to @c nullptr.
		 @pre			The size of the data pointed to by @a bytecode is equal 
						to @a bytecode_size (bytes).
		 @param[in]		bytecode
						A pointer to the shader bytecode.
		 @param[in]		bytecode_size
						The size of the given shader bytecode.
		 */
		explicit BufferCompiledShader(
			const BYTE *bytecode, SIZE_T bytecode_size);

		/**
		 Constructs a buffer compiled shader from the given buffer compiled 
		 shader.
		 
		 @param[in]		compiled_shader
						A reference to the buffer compiled shader to copy.
		 */
		BufferCompiledShader(const BufferCompiledShader &compiled_shader);

		/**
		 Constructs a buffer compiled shader by moving the given buffer 
		 compiled shader.
		 
		 @param[in]		compiled_shader
						A reference to the buffer compiled shader to move.
		 */
		BufferCompiledShader(BufferCompiledShader &&compiled_shader);

		/**
		 Destructs this buffer compiled shader.
		 */
		virtual ~BufferCompiledShader();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given buffer compiled shader to this buffer compiled 
		 shader.
		 
		 @param[in]		compiled_shader
						A reference to the buffer compiled shader to copy.
		 @return		A reference to the copy of the given buffer compiled 
						shader (i.e. this buffer compiled shader).
		 */
		BufferCompiledShader &operator=(
			const BufferCompiledShader &compiled_shader) = delete;

		/**
		 Moves the given buffer compiled shader to this buffer compiled shader.
		 
		 @param[in]		compiled_shader
						A reference to the buffer compiled shader to copy.
		 @return		A reference to the moved buffer compiled shader (i.e. 
						this buffer compiled shader).
		 */
		BufferCompiledShader &operator=(
			BufferCompiledShader &&compiled_shader) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Returns the shader bytecode of this buffer compiled shader.
		 
		 @return		A pointer to the shader bytecode of this buffer 
						compiled shader.
		 */
		virtual const BYTE *GetBytecode() const noexcept override {
			return m_bytecode;
		}

		/**
		 Returns the size of the shader bytecode (in bytes) of this buffer 
		 compiled shader.
		 
		 @return		The size of the shader bytecode (in bytes) of this 
						buffer compiled shader.
		 */
		virtual SIZE_T GetBytecodeSize() const noexcept override {
			return m_bytecode_size;
		}

	private:

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 A pointer to the shader bytecode of this buffer compiled shader.
		 */
		const BYTE * const m_bytecode;

		/**
		 The size of the shader bytecode of this buffer compiled shader.
		 */
		const SIZE_T m_bytecode_size;
	};

	//-------------------------------------------------------------------------
	// BlobCompiledShader
	//-------------------------------------------------------------------------

	/**
	 A struct of blob compiled shaders.
	 */
	struct BlobCompiledShader : public CompiledShader {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a blob compiled shader.
		 
		 @param[in]		fname
						A reference to the filename.
		 @throws		FormattedException
						Failed to load the compiled shader from the given file.
		 */
		explicit BlobCompiledShader(const wstring &fname);
		
		/**
		 Constructs a blob compiled shader from the given blob compiled shader.
		 
		 @param[in]		compiled_shader
						A reference to the blob compiled shader to copy.
		 */
		BlobCompiledShader(const BlobCompiledShader &compiled_shader);

		/**
		 Constructs a blob compiled shader by moving the given blob compiled 
		 shader.
		 
		 @param[in]		compiled_shader
						A reference to the blob compiled shader to move.
		 */
		BlobCompiledShader(BlobCompiledShader &&compiled_shader);

		/**
		 Destructs this blob compiled shader.
		 */
		virtual ~BlobCompiledShader();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given blob compiled shader to this blob compiled shader.
		 
		 @param[in]		compiled_shader
						A reference to the blob compiled shader to copy.
		 @return		A reference to the copy of the given blob compiled 
						shader (i.e. this blob compiled shader).
		 */
		BlobCompiledShader &operator=(
			const BlobCompiledShader &compiled_shader) = delete;

		/**
		 Moves the given blob compiled shader to this blob compiled shader.
		 
		 @param[in]		compiled_shader
						A reference to the blob compiled shader to copy.
		 @return		A reference to the moved blob compiled shader (i.e. 
						this blob compiled shader).
		 */
		BlobCompiledShader &operator=(
			BlobCompiledShader &&compiled_shader) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Returns the shader bytecode of this blob compiled shader.
		 
		 @return		A pointer to the shader bytecode of this blob compiled 
						shader.
		 */
		virtual const BYTE *GetBytecode() const noexcept override {
			return static_cast< BYTE * >(m_shader_blob->GetBufferPointer());
		}

		/**
		 Returns the size of the shader bytecode (in bytes) of this blob 
		 compiled shader.
		 
		 @return		The size of the shader bytecode (in bytes) of this blob 
						compiled shader.
		 */
		virtual SIZE_T GetBytecodeSize() const noexcept override {
			return m_shader_blob->GetBufferSize();
		}

	private:

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 A pointer to the shader blob of this blob compiled shader.
		 */
		ComPtr< ID3DBlob > m_shader_blob;
	};
}