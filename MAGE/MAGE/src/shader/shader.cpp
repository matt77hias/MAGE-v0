//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "resource\resource_factory.hpp"
#include "shader\shading.hpp"
#include "logging\error.hpp"

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

		const HRESULT result_shader = SetupShader(input_element_desc, nb_input_elements);
		if (FAILED(result_shader)) {
			Error("Shader setup failed: %08X.", result_shader);
			return;
		}
	}

	VertexShader::VertexShader(ID3D11Device2 *device, ID3D11DeviceContext2 *device_context,
		const wstring &guid, const void *bytecode, SIZE_T bytecode_size,
		const D3D11_INPUT_ELEMENT_DESC *input_element_desc, uint32_t nb_input_elements)
		: Resource(guid), m_device(device), m_device_context(device_context),
		m_vertex_shader(), m_vertex_layout() {

		const HRESULT result_shader = SetupShader(bytecode, bytecode_size, input_element_desc, nb_input_elements);
		if (FAILED(result_shader)) {
			Error("Shader setup failed: %08X.", result_shader);
			return;
		}
	}

	HRESULT VertexShader::SetupShader(const D3D11_INPUT_ELEMENT_DESC *input_element_desc, uint32_t nb_input_elements) {

		// Compile/Read the vertex shader.
		ComPtr< ID3DBlob > vertex_shader_blob;
		const HRESULT result_vertex_shader_blob = D3DReadFileToBlob(GetGuid().c_str(), vertex_shader_blob.GetAddressOf());
		if (FAILED(result_vertex_shader_blob)) {
			Error("D3DReadFileToBlob failed: %08X.", result_vertex_shader_blob);
			return result_vertex_shader_blob;
		}

		// Create the vertex shader.
		const HRESULT result_vertex_shader = m_device->CreateVertexShader(vertex_shader_blob->GetBufferPointer(),
																		  vertex_shader_blob->GetBufferSize(),
																		  nullptr,
																		  m_vertex_shader.ReleaseAndGetAddressOf());
		if (FAILED(result_vertex_shader)) {
			Error("Vertex shader creation failed: %08X.", result_vertex_shader);
			return result_vertex_shader;
		}

		// Create the vertex input layout.
		const HRESULT result_vertex_input_layout = m_device->CreateInputLayout(input_element_desc,
																			   static_cast< UINT >(nb_input_elements),
																			   vertex_shader_blob->GetBufferPointer(),
																			   vertex_shader_blob->GetBufferSize(),
																			   m_vertex_layout.ReleaseAndGetAddressOf());
		if (FAILED(result_vertex_input_layout)) {
			Error("Vertex input layout creation failed: %08X.", result_vertex_input_layout);
			return result_vertex_input_layout;
		}

		return S_OK;
	}

	HRESULT VertexShader::SetupShader(const void *bytecode, SIZE_T bytecode_size,
		const D3D11_INPUT_ELEMENT_DESC *input_element_desc, uint32_t nb_input_elements) {

		// Create the vertex shader.
		const HRESULT result_vertex_shader = m_device->CreateVertexShader(bytecode,
																	   bytecode_size,
																	   nullptr,
																	   m_vertex_shader.ReleaseAndGetAddressOf());
		if (FAILED(result_vertex_shader)) {
			Error("Vertex shader creation failed: %08X.", result_vertex_shader);
			return result_vertex_shader;
		}

		// Create the vertex input layout.
		const HRESULT result_vertex_input_layout = m_device->CreateInputLayout(input_element_desc,
																			   static_cast< UINT >(nb_input_elements),
																			   bytecode,
																			   bytecode_size,
																			   m_vertex_layout.ReleaseAndGetAddressOf());
		if (FAILED(result_vertex_input_layout)) {
			Error("Vertex input layout creation failed: %08X.", result_vertex_input_layout);
			return result_vertex_input_layout;
		}

		return S_OK;
	}

	void VertexShader::PrepareShading(const XMMATRIX &transform) const {
		UNUSED(transform);
		Error("Unimplemented VertexShader::Draw() method called.");
	}
	
	void VertexShader::PrepareShading(const Material &material, const World &world, const TransformBuffer &transform_buffer) const {
		UNUSED(material);
		UNUSED(world);
		UNUSED(transform_buffer);
		Error("Unimplemented VertexShader::Draw() method called.");
	}

	//-------------------------------------------------------------------------
	// PixelShader
	//-------------------------------------------------------------------------

	PixelShader::PixelShader(ID3D11Device2 *device, ID3D11DeviceContext2 *device_context,
		const wstring &guid)
		: Resource(guid), m_device(device), m_device_context(device_context), 
		m_pixel_shader() {

		const HRESULT result_shader = SetupShader();
		if (FAILED(result_shader)) {
			Error("Shader setup failed: %08X.", result_shader);
			return;
		}
	}

	PixelShader::PixelShader(ID3D11Device2 *device, ID3D11DeviceContext2 *device_context,
		const wstring &guid, const void *bytecode, SIZE_T bytecode_size)
		: Resource(guid), m_device(device), m_device_context(device_context), 
		m_pixel_shader() {

		const HRESULT result_shader = SetupShader(bytecode, bytecode_size);
		if (FAILED(result_shader)) {
			Error("Shader setup failed: %08X.", result_shader);
			return;
		}
	}

	HRESULT PixelShader::SetupShader() {

		// Compile/Read the pixel shader.
		ComPtr< ID3DBlob > pixel_shader_blob;
		const HRESULT result_pixel_shader_blob = D3DReadFileToBlob(GetGuid().c_str(), pixel_shader_blob.GetAddressOf());
		if (FAILED(result_pixel_shader_blob)) {
			Error("D3DReadFileToBlob failed: %08X.", result_pixel_shader_blob);
			return result_pixel_shader_blob;
		}

		// Create the pixel shader.
		const HRESULT result_pixel_layout = m_device->CreatePixelShader(pixel_shader_blob->GetBufferPointer(),
																		pixel_shader_blob->GetBufferSize(), 
																		nullptr,
																		m_pixel_shader.ReleaseAndGetAddressOf());
		if (FAILED(result_pixel_layout)) {
			Error("Pixel shader creation failed: %08X.", result_pixel_layout);
			return result_pixel_layout;
		}

		return S_OK;
	}

	HRESULT PixelShader::SetupShader(const void *bytecode, SIZE_T bytecode_size) {

		// Create the pixel shader.
		const HRESULT result_pixel_shader = m_device->CreatePixelShader(bytecode,
																		bytecode_size,
																		nullptr,
																		m_pixel_shader.ReleaseAndGetAddressOf());
		if (FAILED(result_pixel_shader)) {
			Error("Pixel shader creation failed: %08X.", result_pixel_shader);
			return result_pixel_shader;
		}

		return S_OK;
	}

	void PixelShader::PrepareShading(ID3D11ShaderResourceView * const * texture) const {
		UNUSED(texture);
		Error("Unimplemented PixelShader::Draw() method called.");
	}

	void PixelShader::PrepareShading(const Material &material, const World &world) const {
		UNUSED(material);
		UNUSED(world);
		Error("Unimplemented PixelShader::Draw() method called.");
	}
}