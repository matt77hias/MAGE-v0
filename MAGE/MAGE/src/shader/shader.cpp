//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "shader\shading.hpp"
#include "shader\shader.hpp"
#include "logging\error.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	VertexShader::VertexShader(ComPtr< ID3D11Device2 > device, const wstring &fname, const D3D11_INPUT_ELEMENT_DESC *input_element_desc, uint32_t nb_input_elements)
		: Resource(fname) {

		const HRESULT result_shader = InitializeShader(device, input_element_desc, nb_input_elements);
		if (FAILED(result_shader)) {
			Error("Shader initialization failed: %ld.", result_shader);
			return;
		}
	}

	HRESULT VertexShader::InitializeShader(ComPtr< ID3D11Device2 > device, const D3D11_INPUT_ELEMENT_DESC *input_element_desc, uint32_t nb_input_elements) {

		// Compile the vertex shader.
		ComPtr< ID3DBlob > vertex_shader_blob;
		const HRESULT result_vertex_shader_blob = D3DReadFileToBlob(GetFilename().c_str(), vertex_shader_blob.GetAddressOf());
		if (FAILED(result_vertex_shader_blob)) {
			Error("D3DReadFileToBlob failed: %ld.", result_vertex_shader_blob);
			return result_vertex_shader_blob;
		}

		// Create the vertex shader
		// 1. A pointer to the compiled vertex shader.
		// 2. The size of the compiled vertex shader.
		// 3. A pointer to a class linkage interface.
		// 4. Address of a pointer to a vertex shader.
		const HRESULT result_vertex_shader = device->CreateVertexShader(vertex_shader_blob->GetBufferPointer(), vertex_shader_blob->GetBufferSize(), nullptr, m_vertex_shader.ReleaseAndGetAddressOf());
		if (FAILED(result_vertex_shader)) {
			Error("VertexShader creation failed: %ld.", result_vertex_shader);
			return result_vertex_shader;
		}

		// Create the ID3D11InputLayout.
		// 1. An array of the input-assembler stage input data types; each type is described by an element description.
		// 2. The number of input-data types in the array of input-elements.
		// 3. A pointer to the compiled shader.
		// 4. The size of the compiled shader.
		// 5. A pointer to the input-layout object created
		const HRESULT result_vertex_layout = device->CreateInputLayout(input_element_desc, (UINT)nb_input_elements, vertex_shader_blob->GetBufferPointer(), vertex_shader_blob->GetBufferSize(), m_vertex_layout.ReleaseAndGetAddressOf());
		if (FAILED(result_vertex_layout)) {
			Error("InputLayout creation failed: %ld.", result_vertex_shader);
			return result_vertex_layout;
		}

		return S_OK;
	}

	PixelShader::PixelShader(ComPtr< ID3D11Device2 > device, const wstring &fname)
		: Resource(fname) {

		const HRESULT result_shader = InitializeShader(device);
		if (FAILED(result_shader)) {
			Error("Shader initialization failed: %ld.", result_shader);
			return;
		}
	}

	HRESULT PixelShader::InitializeShader(ComPtr< ID3D11Device2 > device) {

		// Compile the pixel shader.
		ComPtr< ID3DBlob > pixel_shader_blob;
		const HRESULT result_pixel_shader_blob = D3DReadFileToBlob(GetFilename().c_str(), pixel_shader_blob.GetAddressOf());
		if (FAILED(result_pixel_shader_blob)) {
			Error("D3DReadFileToBlob failed: %ld.", result_pixel_shader_blob);
			return result_pixel_shader_blob;
		}

		// Create the pixel shader.
		// 1. A pointer to the compiled pixel shader.
		// 2. The size of the compiled pixel shader.
		// 3. A pointer to a class linkage interface.
		// 4. Address of a pointer to a pixel shader.
		const HRESULT result_pixel_shader = device->CreatePixelShader(pixel_shader_blob->GetBufferPointer(), pixel_shader_blob->GetBufferSize(), nullptr, m_pixel_shader.ReleaseAndGetAddressOf());
		if (FAILED(result_pixel_shader)) {
			Error("PixelShader creation failed: %ld.", result_pixel_shader_blob);
			return result_pixel_shader;
		}

		return S_OK;
	}
}