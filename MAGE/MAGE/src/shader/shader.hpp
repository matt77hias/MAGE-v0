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

		explicit VertexShader(ID3D11Device2 *device, ID3D11DeviceContext2 *device_context,
			const wstring &guid, const D3D11_INPUT_ELEMENT_DESC *input_element_desc, uint32_t nb_input_elements);
		explicit VertexShader(ID3D11Device2 *device, ID3D11DeviceContext2 *device_context,
			const wstring &guid, const void *bytecode, SIZE_T bytecode_size,
			const D3D11_INPUT_ELEMENT_DESC *input_element_desc, uint32_t nb_input_elements);
		VertexShader(VertexShader &&vertex_shader) = default;
		virtual ~VertexShader() = default;

		virtual void Draw(const Material &material, const World &world, const TransformBuffer &transform_buffer) const = 0;

	protected:

		ID3D11Device2 * const m_device;
		ID3D11DeviceContext2 * const m_device_context;
		ComPtr< ID3D11VertexShader > m_vertex_shader;
		ComPtr< ID3D11InputLayout >  m_vertex_layout;

	private:

		VertexShader(const VertexShader &vertex_shader) = delete;
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

		explicit PixelShader(ID3D11Device2 *device, ID3D11DeviceContext2 *device_context,
			const wstring &guid);
		explicit PixelShader(ID3D11Device2 *device, ID3D11DeviceContext2 *device_context,
			const wstring &guid, const void *bytecode, SIZE_T bytecode_size);
		PixelShader(PixelShader &&pixel_shader) = default;
		virtual ~PixelShader() = default;

		virtual void Draw(const Material &material, const World &world) const = 0;

	protected:

		ID3D11Device2 * const m_device;
		ID3D11DeviceContext2 * const m_device_context;
		ComPtr< ID3D11PixelShader > m_pixel_shader;

	private:

		PixelShader(const PixelShader &pixel_shader) = delete;
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

		explicit CombinedShader(SharedPtr< VertexShader > vertex_shader, SharedPtr< PixelShader > pixel_shader)
			: m_vertex_shader(vertex_shader), m_pixel_shader(pixel_shader) {}
		CombinedShader(const CombinedShader &shader) = default;
		CombinedShader(CombinedShader &&shader) = default;
		~CombinedShader() = default;

		CombinedShader &operator=(const CombinedShader &shader) = default;
		CombinedShader &operator=(CombinedShader &&shader) = default;

		void Draw(const Material &material, const World &world, const TransformBuffer &transform_buffer) const {
			m_vertex_shader->Draw(material, world, transform_buffer);
			m_pixel_shader->Draw(material, world);
		}

	private:

		SharedPtr< VertexShader > m_vertex_shader;
		SharedPtr< PixelShader > m_pixel_shader;
	};
}