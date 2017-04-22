#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "resource\resource.hpp"
#include "material\material.hpp"
#include "light\light_buffer.hpp"
#include "world\transform_buffer.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	//-------------------------------------------------------------------------
	// VertexShader
	//-------------------------------------------------------------------------

	class VertexShader : public Resource {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		explicit VertexShader(ID3D11Device2 *device, ID3D11DeviceContext2 *device_context,
			const wstring &guid, const D3D11_INPUT_ELEMENT_DESC *input_element_desc, uint32_t nb_input_elements);
		explicit VertexShader(ID3D11Device2 *device, ID3D11DeviceContext2 *device_context,
			const wstring &guid, const void *bytecode, SIZE_T bytecode_size,
			const D3D11_INPUT_ELEMENT_DESC *input_element_desc, uint32_t nb_input_elements);
		VertexShader(const VertexShader &vertex_shader) = delete;
		VertexShader(VertexShader &&vertex_shader) = default;
		virtual ~VertexShader() = default;

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		VertexShader &operator=(const VertexShader &vertex_shader) = delete;
		VertexShader &operator=(VertexShader &&vertex_shader) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		virtual void PrepareShading(const XMMATRIX &transform) const;
		virtual void PrepareShading(const TransformBuffer &transform) const;

	protected:

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		ID3D11Device2 * const m_device;
		ID3D11DeviceContext2 * const m_device_context;
		ComPtr< ID3D11VertexShader > m_vertex_shader;
		ComPtr< ID3D11InputLayout >  m_vertex_layout;

	private:

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		HRESULT SetupShader(const D3D11_INPUT_ELEMENT_DESC *input_element_desc, uint32_t nb_input_elements);
		HRESULT SetupShader(const void *bytecode, SIZE_T bytecode_size,
			const D3D11_INPUT_ELEMENT_DESC *input_element_desc, uint32_t nb_input_elements);
	};

	//-------------------------------------------------------------------------
	// PixelShader
	//-------------------------------------------------------------------------

	class PixelShader : public Resource {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		explicit PixelShader(ID3D11Device2 *device, ID3D11DeviceContext2 *device_context,
			const wstring &guid);
		explicit PixelShader(ID3D11Device2 *device, ID3D11DeviceContext2 *device_context,
			const wstring &guid, const void *bytecode, SIZE_T bytecode_size);
		PixelShader(const PixelShader &pixel_shader) = delete;
		PixelShader(PixelShader &&pixel_shader) = default;
		virtual ~PixelShader() = default;

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		PixelShader &operator=(const PixelShader &pixel_shader) = delete;
		PixelShader &operator=(PixelShader &&pixel_shader) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		void PrepareShading(const Texture &texture) const {
			PrepareShading(texture.GetTextureResourceViewAddress());
		}
		virtual void PrepareShading(ID3D11ShaderResourceView * const *texture) const;
		virtual void PrepareShading(const Material &material, const LightBuffer &lighting) const;

	protected:

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		ID3D11Device2 * const m_device;
		ID3D11DeviceContext2 * const m_device_context;
		ComPtr< ID3D11PixelShader > m_pixel_shader;

	private:

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		HRESULT SetupShader();
		HRESULT SetupShader(const void *bytecode, SIZE_T bytecode_size);
	};

	//-------------------------------------------------------------------------
	// CombinedShader
	//-------------------------------------------------------------------------

	struct CombinedShader final {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		explicit CombinedShader(SharedPtr< VertexShader > vertex_shader, SharedPtr< PixelShader > pixel_shader)
			: m_vertex_shader(vertex_shader), m_pixel_shader(pixel_shader) {}
		CombinedShader(const CombinedShader &shader) = default;
		CombinedShader(CombinedShader &&shader) = default;
		~CombinedShader() = default;

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		CombinedShader &operator=(const CombinedShader &shader) = default;
		CombinedShader &operator=(CombinedShader &&shader) = default;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		void PrepareShading(const Texture &texture, const XMMATRIX &transform) const {
			m_vertex_shader->PrepareShading(transform);
			m_pixel_shader->PrepareShading(texture);
		}
		void PrepareShading(ID3D11ShaderResourceView * const *texture, const XMMATRIX &matrix) const {
			m_vertex_shader->PrepareShading(matrix);
			m_pixel_shader->PrepareShading(texture);
		}
		void PrepareShading(const Material &material, const LightBuffer &lighting, const TransformBuffer &transform) const {
			m_vertex_shader->PrepareShading(transform);
			m_pixel_shader->PrepareShading(material, lighting);
		}

	private:

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		SharedPtr< VertexShader > m_vertex_shader;
		SharedPtr< PixelShader > m_pixel_shader;
	};
}