//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "resource\resource_factory.hpp"
#include "logging\error.hpp"
#include "logging\exception.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	//-------------------------------------------------------------------------
	// VertexShader
	//-------------------------------------------------------------------------

	VertexShader::VertexShader(const wstring &guid,
		const CompiledShader *compiled_shader,
		const D3D11_INPUT_ELEMENT_DESC *input_element_desc, uint32_t nb_input_elements)
		: VertexShader(guid, GetRenderingDevice(), GetRenderingDeviceContext(),
			compiled_shader, input_element_desc, nb_input_elements) {}

	VertexShader::VertexShader(const wstring &guid, 
		ID3D11Device2 *device, ID3D11DeviceContext2 *device_context,
		const CompiledShader *compiled_shader, 
		const D3D11_INPUT_ELEMENT_DESC *input_element_desc, uint32_t nb_input_elements)
		: Resource< VertexShader >(guid),
		m_device(device), m_device_context(device_context), 
		m_vertex_shader(), m_vertex_layout() {

		Assert(device);
		Assert(device_context);
		Assert(compiled_shader);
		Assert(input_element_desc);

		SetupShader(compiled_shader, input_element_desc, nb_input_elements);
	}

	VertexShader::VertexShader(VertexShader &&vertex_shader) = default;

	VertexShader::~VertexShader() = default;

	void VertexShader::SetupShader(const CompiledShader *compiled_shader,
		const D3D11_INPUT_ELEMENT_DESC *input_element_desc, uint32_t nb_input_elements) {

		// Create the vertex shader.
		const HRESULT result_vertex_shader = m_device->CreateVertexShader(
																			compiled_shader->GetBytecode(),
																			compiled_shader->GetBytecodeSize(),
																			nullptr,
																			m_vertex_shader.ReleaseAndGetAddressOf());
		if (FAILED(result_vertex_shader)) {
			throw FormattedException("Vertex shader creation failed: %08X.", result_vertex_shader);
		}

		// Create the vertex input layout.
		const HRESULT result_vertex_input_layout = m_device->CreateInputLayout(
																			input_element_desc,
																			static_cast< UINT >(nb_input_elements),
																			compiled_shader->GetBytecode(),
																			compiled_shader->GetBytecodeSize(),
																			m_vertex_layout.ReleaseAndGetAddressOf());
		if (FAILED(result_vertex_input_layout)) {
			throw FormattedException("Vertex input layout creation failed: %08X.", result_vertex_input_layout);
		}
	}

	void VertexShader::PrepareShading(ID3D11Buffer *transform) const {
		UNUSED(transform);
		m_device_context->IASetInputLayout(m_vertex_layout.Get());
		m_device_context->VSSetShader(m_vertex_shader.Get(), nullptr, 0);
	}

	//-------------------------------------------------------------------------
	// PixelShader
	//-------------------------------------------------------------------------

	PixelShader::PixelShader(const wstring &guid,
		const CompiledShader *compiled_shader)
		: PixelShader(guid, GetRenderingDevice(), GetRenderingDeviceContext(),
			compiled_shader) {}

	PixelShader::PixelShader(const wstring &guid,
		ID3D11Device2 *device, ID3D11DeviceContext2 *device_context,
		const CompiledShader *compiled_shader)
		: Resource< PixelShader >(guid), 
		m_device(device), m_device_context(device_context), 
		m_pixel_shader() {

		Assert(device);
		Assert(device_context);
		Assert(compiled_shader);

		SetupShader(compiled_shader);
	}

	PixelShader::PixelShader(PixelShader &&pixel_shader) = default;

	PixelShader::~PixelShader() = default;

	void PixelShader::SetupShader(const CompiledShader *compiled_shader) {

		// Create the pixel shader.
		const HRESULT result_pixel_shader = m_device->CreatePixelShader(compiled_shader->GetBytecode(),
																		compiled_shader->GetBytecodeSize(),
																		nullptr,
																		m_pixel_shader.ReleaseAndGetAddressOf());
		if (FAILED(result_pixel_shader)) {
			throw FormattedException("Pixel shader creation failed: %08X.", result_pixel_shader);
		}
	}

	void PixelShader::PrepareShading(ID3D11ShaderResourceView *texture) const {
		UNUSED(texture);
		m_device_context->PSSetShader(m_pixel_shader.Get(), nullptr, 0);
	}

	void PixelShader::PrepareShading(const Material &material, const SceneInfo &scene) const {
		UNUSED(material);
		UNUSED(scene);
		m_device_context->PSSetShader(m_pixel_shader.Get(), nullptr, 0);
	}

	//-------------------------------------------------------------------------
	// CombinedShader
	//-------------------------------------------------------------------------

	CombinedShader::CombinedShader(
		SharedPtr< VertexShader > vertex_shader,
		SharedPtr< PixelShader > pixel_shader)
		: m_vertex_shader(vertex_shader),
		m_pixel_shader(pixel_shader) {

		Assert(m_vertex_shader);
		Assert(m_pixel_shader);
	}
}