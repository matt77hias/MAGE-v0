#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "resource\resource.hpp"
#include "resource\shader\compiled_shader.hpp"
#include "renderer\pipeline.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage::rendering {

	//-------------------------------------------------------------------------
	// VertexShader
	//-------------------------------------------------------------------------
	#pragma region

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

		 @param[in,out]	device
						A reference to the device.
		 @param[in]		guid
						The globally unique identifier.
		 @param[in]		compiled_shader
						A reference to the compiled vertex shader.
		 @param[in]		input_element_descs
						The input element descriptors.
		 @throws		Exception
						Failed to initialize this vertex shader.
		 */
		explicit VertexShader(ID3D11Device& device,
							  std::wstring guid,
			                  const CompiledShader& compiled_shader,
			                  gsl::span< const D3D11_INPUT_ELEMENT_DESC >
							  input_element_descs);

		/**
		 Constructs a vertex shader from the given vertex shader.

		 @param[in]		vertex_shader
						A reference to the vertex shader to copy.
		 */
		VertexShader(const VertexShader& vertex_shader) = delete;

		/**
		 Constructs a vertex shader by moving the given vertex shader.

		 @param[in]		vertex_shader
						A reference to the vertex shader to move.
		 */
		VertexShader(VertexShader&& vertex_shader) noexcept;

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
		VertexShader& operator=(const VertexShader& vertex_shader) = delete;

		/**
		 Moves the given vertex shader to this vertex shader.

		 @param[in]		vertex_shader
						A reference to the vertex shader to copy.
		 @return		A reference to the moved vertex shader (i.e. this
						vertex shader).
		 */
		VertexShader& operator=(VertexShader&& vertex_shader) noexcept;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Binds this vertex shader.

		 @param[in,out]	device_context
						A reference to the device context.
		 */
		void BindShader(ID3D11DeviceContext& device_context) const noexcept {
			Pipeline::IA::BindInputLayout(device_context, *m_vertex_layout.Get());
			Pipeline::VS::BindShader(device_context, m_vertex_shader.Get());
		}

	private:

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Sets up this vertex shader.

		 @param[in]		device
						A reference to the device.
		 @param[in]		compiled_shader
						A reference to the compiled vertex shader.
		 @param[in]		input_element_descs
						The input element descriptors.
		 @throws		Exception
						Failed to setup this vertex shader.
		 */
		void SetupShader(ID3D11Device& device,
			             const CompiledShader& compiled_shader,
						 gsl::span< const D3D11_INPUT_ELEMENT_DESC >
						 input_element_descs);

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

	#pragma endregion

	//-------------------------------------------------------------------------
	// Shader
	//-------------------------------------------------------------------------
	#pragma region

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

		 @param[in,out]	device
						A reference to the device.
		 @param[in]		guid
						The globally unique identifier.
		 @param[in]		compiled_shader
						A reference to the compiled shader.
		 @throws		Exception
						Failed to initialize this shader.
		 */
		explicit Shader(ID3D11Device& device,
						std::wstring guid,
			            const CompiledShader& compiled_shader);

		/**
		 Constructs a shader from the given shader.

		 @param[in]		shader
						A reference to the shader to copy.
		 */
		Shader(const Shader& shader) = delete;

		/**
		 Constructs a shader by moving the given shader.

		 @param[in]		shader
						A reference to the shader to move.
		 */
		Shader(Shader&& shader) noexcept;

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
		Shader& operator=(const Shader& shader) = delete;

		/**
		 Moves the given shader to this shader.

		 @param[in]		shader
						A reference to the shader to move.
		 @return		A reference to the moved shader (i.e. this shader).
		 */
		Shader& operator=(Shader&& shader) noexcept;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Binds this shader.

		 @param[in,out]	device_context
						A reference to the device context.
		 */
		void BindShader(ID3D11DeviceContext& device_context) const noexcept;

	private:

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Sets up this shader.

		 @param[in,out]	device
						A reference to the device.
		 @param[in]		compiled_shader
						A reference to the compiled shader.
		 @throws		Exception
						Failed to setup this shader.
		 */
		void SetupShader(ID3D11Device& device,
			             const CompiledShader& compiled_shader);

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 A pointer to the shader of this shader.
		 */
		ComPtr< ShaderT > m_shader;
	};

	#pragma endregion

	//-------------------------------------------------------------------------
	// Type Declarations and Definitions: Shaders
	//-------------------------------------------------------------------------
	#pragma region

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

	#pragma endregion

	//-------------------------------------------------------------------------
	// Type Declarations and Definitions: Shader Pointers
	//-------------------------------------------------------------------------
	#pragma region

	/**
	 A pointer to a vertex shader resource.
	 */
	using VertexShaderPtr = SharedPtr< const VertexShader >;

	/**
	 A pointer to a hull shader resource.
	 */
	using HullShaderPtr = SharedPtr< const HullShader >;

	/**
	 A pointer to a domain shader resource.
	 */
	using DomainShaderPtr = SharedPtr< const DomainShader >;

	/**
	 A pointer to a geometry shader resource.
	 */
	using GeometryShaderPtr = SharedPtr< const GeometryShader >;

	/**
	 A pointer to a pixel shader resource.
	 */
	using PixelShaderPtr = SharedPtr< const PixelShader >;

	/**
	 A pointer to a compute shader resource.
	 */
	using ComputeShaderPtr = SharedPtr< const ComputeShader >;

	#pragma endregion

	//-------------------------------------------------------------------------
	// Type Traits
	//-------------------------------------------------------------------------
	#pragma region

	template< typename T >
	struct is_shader : public std::false_type {};
	template<>
	struct is_shader< VertexShader >   : public std::true_type {};
	template<>
	struct is_shader< HullShader >     : public std::true_type {};
	template<>
	struct is_shader< DomainShader >   : public std::true_type {};
	template<>
	struct is_shader< GeometryShader > : public std::true_type {};
	template<>
	struct is_shader< PixelShader >    : public std::true_type {};
	template<>
	struct is_shader< ComputeShader >  : public std::true_type {};

	template< typename T >
	constexpr bool is_shader_v = is_shader< T >::value;

	#pragma endregion
}

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "resource\shader\shader.tpp"

#pragma endregion