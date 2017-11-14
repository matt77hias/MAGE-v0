#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "resource\resource.hpp"
#include "shader\compiled_shader.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	//-------------------------------------------------------------------------
	// VertexShader
	//-------------------------------------------------------------------------

	/**
	 A class of vertex shaders.
	 */
	class VertexShader : public Resource< VertexShader > {

	public:
	
		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a vertex shader.

		 @pre			The device associated of the rendering manager 
						associated with the current engine must be loaded.
		 @pre			The array pointed to by @a input_element_desc contains 
						@a nb_input_elements elements, if @a input_element_desc 
						is not equal to @c nullptr.
		 @param[in]		guid
						The globally unique identifier.
		 @param[in]		compiled_shader
						A reference to the compiled vertex shader.
		 @param[in]		input_element_desc
						A pointer the input element descriptors.
		 @param[in]		nb_input_elements
						The number of elements contained in the
						given input element descriptor.
		 @throws		FormattedException
						Failed to initialize this vertex shader.
		 */
		explicit VertexShader(wstring guid,
			const CompiledShader &compiled_shader,
			const D3D11_INPUT_ELEMENT_DESC *input_element_desc, 
			size_t nb_input_elements);
		
		/**
		 Constructs a vertex shader.

		 @pre			@a device is not equal to @c nullptr.
		 @pre			The array pointed to by @a input_element_desc contains 
						@a nb_input_elements elements, if @a input_element_desc 
						is not equal to @c nullptr.
		 @param[in]		guid
						The globally unique identifier.
		 @param[in]		device
						A pointer to the device.
		 @param[in]		compiled_shader
						A reference to the compiled vertex shader.
		 @param[in]		input_element_desc
						A pointer the input element descriptors.
		 @param[in]		nb_input_elements
						The number of elements contained in the
						given input element descriptor.
		 @throws		FormattedException
						Failed to initialize this vertex shader.
		*/
		explicit VertexShader(wstring guid, ID3D11Device5 *device, 
			const CompiledShader &compiled_shader, 
			const D3D11_INPUT_ELEMENT_DESC *input_element_desc, 
			size_t nb_input_elements);
		
		/**
		 Constructs a vertex shader from the given vertex shader.

		 @param[in]		vertex_shader
						A reference to the vertex shader to copy.
		 */
		VertexShader(const VertexShader &vertex_shader) = delete;
		
		/**
		 Constructs a vertex shader by moving the given vertex shader.

		 @param[in]		vertex_shader
						A reference to the vertex shader to move.
		 */
		VertexShader(VertexShader &&vertex_shader);
		
		/**
		 Destructs this vertex shader.
		 */
		virtual ~VertexShader();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given vertex shader to this vertex shader.

		 @param[in]		vertex_shader
						A reference to the vertex shader to copy.
		 @return		A reference to the copy of the given vertex shader 
						(i.e. this vertex shader).
		 */
		VertexShader &operator=(const VertexShader &vertex_shader) = delete;

		/**
		 Moves the given vertex shader to this vertex shader.

		 @param[in]		vertex_shader
						A reference to the vertex shader to copy.
		 @return		A reference to the moved vertex shader (i.e. this 
						vertex shader).
		 */
		VertexShader &operator=(VertexShader &&vertex_shader) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Binds this vertex shader.

		 @pre			@a device_context is not equal to @c nullptr.
		 @param[in]		device_context
						A pointer to the device context.
		 */
		void BindShader(ID3D11DeviceContext4 *device_context) const noexcept {
			Pipeline::IA::BindInputLayout(device_context, m_vertex_layout.Get());
			Pipeline::VS::BindShader(device_context, m_vertex_shader.Get());
		}

	private:

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Sets up this vertex shader.

		 @pre			@a device is not equal to @c nullptr.
		 @pre			@a input_element_desc is not equal to @c nullptr.
		 @pre			The array pointed to by @a input_element_desc contains 
						@a nb_input_elements elements.
		 @param[in]		device
						A pointer to the device.
		 @param[in]		compiled_shader
						A reference to the compiled vertex shader.
		 @param[in]		input_element_desc
						A pointer the input element descriptors.
		 @param[in]		nb_input_elements
						The number of elements contained in the
						given input element descriptor.
		 @throws		FormattedException
						Failed to setup this vertex shader.
		 */
		void SetupShader(ID3D11Device5 *device,
			const CompiledShader &compiled_shader,
			const D3D11_INPUT_ELEMENT_DESC *input_element_desc, 
			size_t nb_input_elements);
			
		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 A pointer to the vertex shader of this vertex shader.
		 */
		ComPtr< ID3D11VertexShader > m_vertex_shader;

		/**
		 A pointer to the input layout of this vertex shader.
		 */
		ComPtr< ID3D11InputLayout >  m_vertex_layout;
	};
	
	//-------------------------------------------------------------------------
	// Shader
	//-------------------------------------------------------------------------

	/**
	 A class of shaders.

	 @tparam		ShaderT
					The shader type.
	 @tparam		PipelineStageT
					The pipeline stage type.
	 */
	template< typename ShaderT, typename PipelineStageT >
	class Shader : public Resource< Shader< ShaderT, PipelineStageT > > {

	public:
	
		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a shader.

		 @pre			The device associated of the rendering manager 
						associated with the current engine must be loaded.
		 @param[in]		guid
						The globally unique identifier.
		 @param[in]		compiled_shader
						A reference to the compiled shader.
		 @throws		FormattedException
						Failed to initialize this shader.
		 */
		explicit Shader(wstring guid, 
			const CompiledShader &compiled_shader);

		/**
		 Constructs a shader.

		 @pre			@a device is not equal to @c nullptr.
		 @param[in]		guid
						The globally unique identifier.
		 @param[in]		device
						A pointer to the device.
		 @param[in]		compiled_shader
						A reference to the compiled shader.
		 @throws		FormattedException
						Failed to initialize this shader.
		 */
		explicit Shader(wstring guid, ID3D11Device5 *device,
			const CompiledShader &compiled_shader);
		
		/**
		 Constructs a shader from the given shader.

		 @param[in]		shader
						A reference to the shader to copy.
		 */
		Shader(const Shader< ShaderT, PipelineStageT > &shader) = delete;

		/**
		 Constructs a shader by moving the given shader.

		 @param[in]		shader
						A reference to the shader to move.
		 */
		Shader(Shader< ShaderT, PipelineStageT > &&shader);

		/**
		 Destructs this shader.
		 */
		virtual ~Shader();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given shader to this shader.

		 @param[in]		shader
						A reference to the shader to copy.
		 @return		A reference to the copy of the given shader (i.e. this 
						shader).
		 */
		Shader< ShaderT, PipelineStageT > &operator=(
			const Shader< ShaderT, PipelineStageT > &shader) = delete;

		/**
		 Moves the given shader to this shader.

		 @param[in]		shader
						A reference to the shader to move.
		 @return		A reference to the moved shader (i.e. this shader).
		 */
		Shader< ShaderT, PipelineStageT > &operator=(
			Shader< ShaderT, PipelineStageT > &&shader) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Binds this shader.

		 @pre			@a device_context is not equal to @c nullptr.
		 @param[in]		device_context
						A pointer to the device context.
		 */
		void BindShader(ID3D11DeviceContext4 *device_context) const noexcept;

	private:

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Sets up this shader.

		 @pre			@a device is not equal to @c nullptr.
		 @param[in]		device
						A pointer to the device.
		 @param[in]		compiled_shader
						A reference to the compiled shader.
		 @throws		FormattedException
						Failed to setup this shader.
		 */
		void SetupShader(ID3D11Device5 *device, 
			const CompiledShader &compiled_shader);
		
		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 A pointer to the shader of this shader.
		 */
		ComPtr< ShaderT > m_shader;
	};

	//-------------------------------------------------------------------------
	// Type Declarations and Definitions
	//-------------------------------------------------------------------------

	/**
	 A class of hull shaders.
	 */
	using HullShader = Shader< ID3D11HullShader, Pipeline::HS >;

	/**
	 A class of domain shaders.
	 */
	using DomainShader = Shader< ID3D11DomainShader, Pipeline::DS >;

	/**
	 A class of geometry shaders.
	 */
	using GeometryShader = Shader< ID3D11GeometryShader, Pipeline::GS >;

	/**
	 A class of pixel shaders.
	 */
	using PixelShader = Shader< ID3D11PixelShader, Pipeline::PS >;

	/**
	 A class of compute shaders.
	 */
	using ComputeShader = Shader< ID3D11ComputeShader, Pipeline::CS >;
}

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "shader\shader.tpp"

#pragma endregion