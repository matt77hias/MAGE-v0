#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "resource\resource.hpp"
#include "material\material.hpp"
#include "world\world.hpp"

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

		VertexShader(ComPtr< ID3D11Device2 > device, ComPtr< ID3D11DeviceContext2 > device_context, 
			const wstring &guid, const D3D11_INPUT_ELEMENT_DESC *input_element_desc, uint32_t nb_input_elements);
		VertexShader(ComPtr< ID3D11Device2 > device, ComPtr< ID3D11DeviceContext2 > device_context,
			const wstring &guid, const void *bytecode, SIZE_T bytecode_size,
			const D3D11_INPUT_ELEMENT_DESC *input_element_desc, uint32_t nb_input_elements);
		virtual ~VertexShader() = default;

		virtual void Draw(const Material &material, const World &world, const TransformBuffer &transform_buffer) const = 0;

	protected:

		ComPtr< ID3D11Device2 >        m_device;
		ComPtr< ID3D11DeviceContext2 > m_device_context;
		ComPtr< ID3D11VertexShader >   m_vertex_shader;
		ComPtr< ID3D11InputLayout >    m_vertex_layout;

	private:

		VertexShader(const VertexShader &vertex_shader) = delete;
		VertexShader(VertexShader &&vertex_shader) = delete;
		VertexShader &operator=(const VertexShader &vertex_shader) = delete;
		VertexShader &operator=(VertexShader &&vertex_shader) = delete;

		HRESULT SetupShader(const D3D11_INPUT_ELEMENT_DESC *input_element_desc, uint32_t nb_input_elements);
		HRESULT SetupShader(const void *bytecode, SIZE_T bytecode_size,
			const D3D11_INPUT_ELEMENT_DESC *input_element_desc, uint32_t nb_input_elements);
	};

	//-------------------------------------------------------------------------
	// PixelShader
	//-------------------------------------------------------------------------

	class PixelShader : public Resource {

	public:

		PixelShader(ComPtr< ID3D11Device2 > device, ComPtr< ID3D11DeviceContext2 > device_context, 
			const wstring &guid);
		PixelShader(ComPtr< ID3D11Device2 > device, ComPtr< ID3D11DeviceContext2 > device_context, 
			const wstring &guid, const void *bytecode, SIZE_T bytecode_size);
		virtual ~PixelShader() = default;

		virtual void Draw(const Material &material, const World &world) const = 0;

	protected:

		ComPtr< ID3D11Device2 >        m_device;
		ComPtr< ID3D11DeviceContext2 > m_device_context;
		ComPtr< ID3D11PixelShader >    m_pixel_shader;

	private:

		PixelShader(const PixelShader &pixel_shader) = delete;
		PixelShader(PixelShader &&pixel_shader) = delete;
		PixelShader &operator=(const PixelShader &pixel_shader) = delete;
		PixelShader &operator=(PixelShader &&pixel_shader) = delete;

		HRESULT SetupShader();
		HRESULT SetupShader(const void *bytecode, SIZE_T bytecode_size);
	};

	//-------------------------------------------------------------------------
	// CombinedShader
	//-------------------------------------------------------------------------

	struct CombinedShader final {

	public:

		CombinedShader(SharedPtr< VertexShader > vertex_shader, SharedPtr< PixelShader > pixel_shader)
			: m_vertex_shader(vertex_shader), m_pixel_shader(pixel_shader) {}
		CombinedShader(const CombinedShader &shader) = default;
		CombinedShader(CombinedShader &&shader) = default;
		~CombinedShader() = default;

		CombinedShader &operator=(const CombinedShader &shader) = default;
		CombinedShader &operator=(CombinedShader &&shader) = default;

		SharedPtr< VertexShader > GetVertexShader() const {
			return m_vertex_shader;
		}
		void SetVertexShader(SharedPtr< VertexShader > vertex_shader) {
			m_vertex_shader = vertex_shader;
		}

		SharedPtr< PixelShader > GetPixelShader() const {
			return m_pixel_shader;
		}
		void SetPixelShader(SharedPtr< PixelShader > pixel_shader) {
			m_pixel_shader = pixel_shader;
		}

		void Draw(const Material &material, const World &world, const TransformBuffer &transform_buffer) {
			m_vertex_shader->Draw(material, world, transform_buffer);
			m_pixel_shader->Draw(material, world);
		}

	private:

		SharedPtr< VertexShader > m_vertex_shader;
		SharedPtr< PixelShader > m_pixel_shader;
	};
}