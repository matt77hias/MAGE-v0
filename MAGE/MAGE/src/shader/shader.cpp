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

	VertexShader::VertexShader(ComPtr< ID3D11Device2 > device, const wstring &guid,
		const D3D11_INPUT_ELEMENT_DESC *input_element_desc, uint32_t nb_input_elements)
		: Resource(guid) {

		const HRESULT result_shader = InitializeShader(device, input_element_desc, nb_input_elements);
		if (FAILED(result_shader)) {
			Error("Shader initialization failed: %08X.", result_shader);
			return;
		}
	}

	VertexShader::VertexShader(ComPtr< ID3D11Device2 > device, const wstring &guid,
		const void *bytecode, SIZE_T bytecode_size,
		const D3D11_INPUT_ELEMENT_DESC *input_element_desc, uint32_t nb_input_elements)
		: Resource(guid) {

		const HRESULT result_shader = InitializeShader(device, bytecode, bytecode_size, input_element_desc, nb_input_elements);
		if (FAILED(result_shader)) {
			Error("Shader initialization failed: %08X.", result_shader);
			return;
		}
	}

	HRESULT VertexShader::InitializeShader(ComPtr< ID3D11Device2 > device,
		const D3D11_INPUT_ELEMENT_DESC *input_element_desc, uint32_t nb_input_elements) {

		// Compile/Read the vertex shader.
		ComPtr< ID3DBlob > vertex_shader_blob;
		const HRESULT result_vertex_shader_blob = D3DReadFileToBlob(GetGuid().c_str(), vertex_shader_blob.GetAddressOf());
		if (FAILED(result_vertex_shader_blob)) {
			Error("D3DReadFileToBlob failed: %08X.", result_vertex_shader_blob);
			return result_vertex_shader_blob;
		}

		// Create the vertex shader.
		const HRESULT result_vertex_shader = device->CreateVertexShader(vertex_shader_blob->GetBufferPointer(),
																		vertex_shader_blob->GetBufferSize(),
																		nullptr,
																		m_vertex_shader.ReleaseAndGetAddressOf());
		if (FAILED(result_vertex_shader)) {
			Error("Vertex shader creation failed: %08X.", result_vertex_shader);
			return result_vertex_shader;
		}

		// Create the vertex input layout.
		const HRESULT result_vertex_input_layout = device->CreateInputLayout(input_element_desc,
																			 static_cast<UINT>(nb_input_elements),
																			 vertex_shader_blob->GetBufferPointer(),
																			 vertex_shader_blob->GetBufferSize(),
																			 m_vertex_layout.ReleaseAndGetAddressOf());
		if (FAILED(result_vertex_input_layout)) {
			Error("Vertex input layout creation failed: %08X.", result_vertex_input_layout);
			return result_vertex_input_layout;
		}

		return S_OK;
	}

	HRESULT VertexShader::InitializeShader(ComPtr< ID3D11Device2 > device,
		const void *bytecode, SIZE_T bytecode_size,
		const D3D11_INPUT_ELEMENT_DESC *input_element_desc, uint32_t nb_input_elements) {

		// Create the vertex shader.
		const HRESULT result_vertex_shader = device->CreateVertexShader(bytecode,
																		bytecode_size,
																		nullptr,
																		m_vertex_shader.ReleaseAndGetAddressOf());
		if (FAILED(result_vertex_shader)) {
			Error("Vertex shader creation failed: %08X.", result_vertex_shader);
			return result_vertex_shader;
		}

		// Create the vertex input layout.
		const HRESULT result_vertex_input_layout = device->CreateInputLayout(input_element_desc,
																			 static_cast<UINT>(nb_input_elements),
																			 bytecode,
																			 bytecode_size,
																			 m_vertex_layout.ReleaseAndGetAddressOf());
		if (FAILED(result_vertex_input_layout)) {
			Error("Vertex input layout creation failed: %08X.", result_vertex_input_layout);
			return result_vertex_input_layout;
		}

		return S_OK;
	}

	//-------------------------------------------------------------------------
	// PixelShader
	//-------------------------------------------------------------------------

	PixelShader::PixelShader(ComPtr< ID3D11Device2 > device, const wstring &guid)
		: Resource(guid) {

		const HRESULT result_shader = InitializeShader(device);
		if (FAILED(result_shader)) {
			Error("Shader initialization failed: %08X.", result_shader);
			return;
		}
	}

	PixelShader::PixelShader(ComPtr< ID3D11Device2 > device, const wstring &guid,
		const void *bytecode, SIZE_T bytecode_size)
		: Resource(guid) {

		const HRESULT result_shader = InitializeShader(device, bytecode, bytecode_size);
		if (FAILED(result_shader)) {
			Error("Shader initialization failed: %08X.", result_shader);
			return;
		}
	}

	HRESULT PixelShader::InitializeShader(ComPtr< ID3D11Device2 > device) {

		// Compile/Read the pixel shader.
		ComPtr< ID3DBlob > pixel_shader_blob;
		const HRESULT result_pixel_shader_blob = D3DReadFileToBlob(GetGuid().c_str(), pixel_shader_blob.GetAddressOf());
		if (FAILED(result_pixel_shader_blob)) {
			Error("D3DReadFileToBlob failed: %08X.", result_pixel_shader_blob);
			return result_pixel_shader_blob;
		}

		// Create the pixel shader.
		const HRESULT result_pixel_layout = device->CreatePixelShader(pixel_shader_blob->GetBufferPointer(), 
																	  pixel_shader_blob->GetBufferSize(), 
																	  nullptr,
																	  m_pixel_shader.ReleaseAndGetAddressOf());
		if (FAILED(result_pixel_layout)) {
			Error("Pixel shader creation failed: %08X.", result_pixel_layout);
			return result_pixel_layout;
		}

		return S_OK;
	}

	HRESULT PixelShader::InitializeShader(ComPtr< ID3D11Device2 > device,
		const void *bytecode, SIZE_T bytecode_size) {

		// Create the pixel shader.
		const HRESULT result_pixel_shader = device->CreatePixelShader(bytecode,
																	  bytecode_size,
																	  nullptr,
																	  m_pixel_shader.ReleaseAndGetAddressOf());
		if (FAILED(result_pixel_shader)) {
			Error("Pixel shader creation failed: %08X.", result_pixel_shader);
			return result_pixel_shader;
		}

		return S_OK;
	}
}