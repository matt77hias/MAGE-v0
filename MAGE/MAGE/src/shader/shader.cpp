//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "resource\resource_factory.hpp"
#include "shader\shading.hpp"
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

	VertexShader::VertexShader(ID3D11Device2 *device, ID3D11DeviceContext2 *device_context,
		const wstring &guid,
		const D3D11_INPUT_ELEMENT_DESC *input_element_desc, uint32_t nb_input_elements)
		: Resource(guid), m_device(device), m_device_context(device_context),
		m_vertex_shader(), m_vertex_layout() {

		Assert(device);
		Assert(device_context);
		Assert(input_element_desc);

		SetupShader(input_element_desc, nb_input_elements);
	}

	VertexShader::VertexShader(ID3D11Device2 *device, ID3D11DeviceContext2 *device_context,
		const wstring &guid, const void *bytecode, SIZE_T bytecode_size,
		const D3D11_INPUT_ELEMENT_DESC *input_element_desc, uint32_t nb_input_elements)
		: Resource(guid), m_device(device), m_device_context(device_context),
		m_vertex_shader(), m_vertex_layout() {

		Assert(device);
		Assert(device_context);
		Assert(bytecode);
		Assert(input_element_desc);

		SetupShader(bytecode, bytecode_size, input_element_desc, nb_input_elements);
	}

	VertexShader::VertexShader(VertexShader &&vertex_shader) = default;

	VertexShader::~VertexShader() = default;

	void VertexShader::SetupShader(const D3D11_INPUT_ELEMENT_DESC *input_element_desc, uint32_t nb_input_elements) {

		// Compile/Read the vertex shader.
		ComPtr< ID3DBlob > vertex_shader_blob;
		const HRESULT result_vertex_shader_blob = D3DReadFileToBlob(GetGuid().c_str(), vertex_shader_blob.GetAddressOf());
		if (FAILED(result_vertex_shader_blob)) {
			throw FormattedException("D3DReadFileToBlob failed: %08X.", result_vertex_shader_blob);
		}

		SetupShader(
			vertex_shader_blob->GetBufferPointer(), 
			vertex_shader_blob->GetBufferSize(), 
			input_element_desc, 
			nb_input_elements);
	}

	void VertexShader::SetupShader(const void *bytecode, SIZE_T bytecode_size,
		const D3D11_INPUT_ELEMENT_DESC *input_element_desc, uint32_t nb_input_elements) {

		// Create the vertex shader.
		const HRESULT result_vertex_shader = m_device->CreateVertexShader(
																			bytecode,
																			bytecode_size,
																			nullptr,
																			m_vertex_shader.ReleaseAndGetAddressOf());
		if (FAILED(result_vertex_shader)) {
			throw FormattedException("Vertex shader creation failed: %08X.", result_vertex_shader);
		}

		// Create the vertex input layout.
		const HRESULT result_vertex_input_layout = m_device->CreateInputLayout(input_element_desc,
																			   static_cast< UINT >(nb_input_elements),
																			   bytecode,
																			   bytecode_size,
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

	PixelShader::PixelShader(ID3D11Device2 *device, ID3D11DeviceContext2 *device_context,
		const wstring &guid)
		: Resource(guid), m_device(device), m_device_context(device_context), 
		m_pixel_shader() {

		Assert(device);
		Assert(device_context);

		SetupShader();
	}

	PixelShader::PixelShader(ID3D11Device2 *device, ID3D11DeviceContext2 *device_context,
		const wstring &guid, const void *bytecode, SIZE_T bytecode_size)
		: Resource(guid), m_device(device), m_device_context(device_context), 
		m_pixel_shader() {

		Assert(device);
		Assert(device_context);
		Assert(bytecode);

		SetupShader(bytecode, bytecode_size);
	}

	PixelShader::PixelShader(PixelShader &&pixel_shader) = default;

	PixelShader::~PixelShader() = default;

	void PixelShader::SetupShader() {

		// Compile/Read the pixel shader.
		ComPtr< ID3DBlob > pixel_shader_blob;
		const HRESULT result_pixel_shader_blob = D3DReadFileToBlob(GetGuid().c_str(), pixel_shader_blob.GetAddressOf());
		if (FAILED(result_pixel_shader_blob)) {
			throw FormattedException("D3DReadFileToBlob failed: %08X.", result_pixel_shader_blob);
		}

		SetupShader(
			pixel_shader_blob->GetBufferPointer(), 
			pixel_shader_blob->GetBufferSize());
	}

	void PixelShader::SetupShader(const void *bytecode, SIZE_T bytecode_size) {

		// Create the pixel shader.
		const HRESULT result_pixel_shader = m_device->CreatePixelShader(bytecode,
																		bytecode_size,
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

	void PixelShader::PrepareShading(const Material &material, const Lighting &lighting) const {
		UNUSED(material);
		UNUSED(lighting);
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