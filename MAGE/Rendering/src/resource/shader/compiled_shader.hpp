#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "direct3d11.hpp"
#include "type\types.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage::rendering {

	//-------------------------------------------------------------------------
	// Utilities
	//-------------------------------------------------------------------------
	#pragma region

	/**
	 Compiles Microsoft High Level Shader Language (HLSL) code into bytecode 
	 for a given shader target.

	 @param[in]		fname
					A pointer to a constant null-terminated string that 
					contains the name of the file that contains the shader 
					code.
	 @param[in]		entry_point
					A pointer to a constant null-terminated string that 
					contains the name of the shader entry point function where 
					shader execution begins.
	 @param[in]		shader_target
					A pointer to a constant null-terminated string that 
					specifies the shader target or set of shader features to 
					compile against.
	 @param[out]	output_blob
					A pointer to a variable that receives a pointer to the 
					@c ID3DBlob interface that you can use to access the 
					compiled code.
	 */
	[[nodiscard]]
	HRESULT CompileShaderFromFile(const std::wstring& fname,
								  const std::string& entry_point,
								  const std::string& shader_target,
								  NotNull< ID3DBlob** > output_blob);

	#pragma endregion

	//-------------------------------------------------------------------------
	// CompiledShader
	//-------------------------------------------------------------------------
	#pragma region

	/**
	 A class of compiled shaders.
	 */
	class CompiledShader {

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
		CompiledShader& operator=(const CompiledShader& compiled_shader) noexcept;

		/**
		 Moves the given compiled shader to this compiled shader.
		 
		 @param[in]		compiled_shader
						A reference to the compiled shader to copy.
		 @return		A reference to the moved compiled shader (i.e. this 
						compiled shader).
		 */
		CompiledShader& operator=(CompiledShader&& compiled_shader) noexcept;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Returns the shader bytecode of this compiled shader.
		 
		 @return		A pointer to the shader bytecode of this compiled 
						shader.
		 */
		[[nodiscard]]
		virtual const BYTE* GetBytecode() const noexcept = 0;

		/**
		 Returns the size of the shader bytecode (in bytes) of this compiled 
		 shader.
		 
		 @return		The size of the shader bytecode (in bytes) of this 
						compiled shader.
		 */
		[[nodiscard]]
		virtual SIZE_T GetBytecodeSize() const noexcept = 0;
		
	protected:
	
		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a compiled shader.
		 */
		CompiledShader() noexcept;

		/**
		 Constructs a compiled shader from the given compiled shader.
		 
		 @param[in]		compiled_shader
						A reference to the compiled shader to copy.
		 */
		CompiledShader(const CompiledShader& compiled_shader) noexcept;

		/**
		 Constructs a compiled shader by moving the given compiled shader.
		 
		 @param[in]		compiled_shader
						A reference to the compiled shader to move.
		 */
		CompiledShader(CompiledShader&& compiled_shader) noexcept;
	};

	#pragma endregion

	//-------------------------------------------------------------------------
	// BufferCompiledShader
	//-------------------------------------------------------------------------
	#pragma region

	/**
	 A class of buffer compiled shaders.
	 */
	class BufferCompiledShader : public CompiledShader {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a buffer compiled shader.
		 
		 @param[in]		bytecode
						The shader bytecode.
		 */
		explicit BufferCompiledShader(gsl::span< const BYTE > bytecode) noexcept;

		/**
		 Constructs a buffer compiled shader from the given buffer compiled 
		 shader.
		 
		 @param[in]		compiled_shader
						A reference to the buffer compiled shader to copy.
		 */
		BufferCompiledShader(const BufferCompiledShader& compiled_shader) noexcept;

		/**
		 Constructs a buffer compiled shader by moving the given buffer 
		 compiled shader.
		 
		 @param[in]		compiled_shader
						A reference to the buffer compiled shader to move.
		 */
		BufferCompiledShader(BufferCompiledShader&& compiled_shader) noexcept;

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
		BufferCompiledShader& operator=(
			const BufferCompiledShader& compiled_shader) noexcept;

		/**
		 Moves the given buffer compiled shader to this buffer compiled shader.
		 
		 @param[in]		compiled_shader
						A reference to the buffer compiled shader to copy.
		 @return		A reference to the moved buffer compiled shader (i.e. 
						this buffer compiled shader).
		 */
		BufferCompiledShader& operator=(
			BufferCompiledShader&& compiled_shader) noexcept;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Returns the shader bytecode of this buffer compiled shader.
		 
		 @return		A pointer to the shader bytecode of this buffer 
						compiled shader.
		 */
		[[nodiscard]]
		virtual const BYTE* GetBytecode() const noexcept override {
			return m_bytecode;
		}

		/**
		 Returns the size of the shader bytecode (in bytes) of this buffer 
		 compiled shader.
		 
		 @return		The size of the shader bytecode (in bytes) of this 
						buffer compiled shader.
		 */
		[[nodiscard]]
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
		const BYTE* m_bytecode;

		/**
		 The size of the shader bytecode of this buffer compiled shader.
		 */
		SIZE_T m_bytecode_size;
	};

	#pragma endregion

	//-------------------------------------------------------------------------
	// BlobCompiledShader
	//-------------------------------------------------------------------------
	#pragma region

	/**
	 A class of blob compiled shaders.
	 */
	class BlobCompiledShader : public CompiledShader {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a blob compiled shader.
		 
		 @param[in]		fname
						A reference to the filename.
		 @throws		Exception
						Failed to load the compiled shader from the given file.
		 */
		explicit BlobCompiledShader(const std::wstring& fname) noexcept;
		
		/**
		 Constructs a blob compiled shader from the given blob compiled shader.
		 
		 @param[in]		compiled_shader
						A reference to the blob compiled shader to copy.
		 */
		BlobCompiledShader(const BlobCompiledShader& compiled_shader) noexcept;

		/**
		 Constructs a blob compiled shader by moving the given blob compiled 
		 shader.
		 
		 @param[in]		compiled_shader
						A reference to the blob compiled shader to move.
		 */
		BlobCompiledShader(BlobCompiledShader&& compiled_shader) noexcept;

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
		BlobCompiledShader& operator=(
			const BlobCompiledShader& compiled_shader) noexcept;

		/**
		 Moves the given blob compiled shader to this blob compiled shader.
		 
		 @param[in]		compiled_shader
						A reference to the blob compiled shader to copy.
		 @return		A reference to the moved blob compiled shader (i.e. 
						this blob compiled shader).
		 */
		BlobCompiledShader& operator=(
			BlobCompiledShader&& compiled_shader) noexcept;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Returns the shader bytecode of this blob compiled shader.
		 
		 @return		A pointer to the shader bytecode of this blob compiled 
						shader.
		 */
		[[nodiscard]]
		virtual const BYTE* GetBytecode() const noexcept override {
			return static_cast< BYTE* >(m_shader_blob->GetBufferPointer());
		}

		/**
		 Returns the size of the shader bytecode (in bytes) of this blob 
		 compiled shader.
		 
		 @return		The size of the shader bytecode (in bytes) of this blob 
						compiled shader.
		 */
		[[nodiscard]]
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

	#pragma endregion
}

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "resource\shader\compiled_shader.hpp"

#pragma endregion