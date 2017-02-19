#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "shader\shading.hpp"
#include "logging\error.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	template < typename Vertex >
	VertexShader< Vertex >::VertexShader(const wstring &fname, ComPtr< ID3D11Device2 > device)
		: Resource(fname) {

		const HRESULT result_shader = InitializeShader(device);
		if (FAILED(result_shader)) {
			Error("Shader initialization failed: %ld.", result_shader);
			return;
		}

		const HRESULT result_buffers = SetupBuffers(device);
		if (FAILED(result_buffers)) {
			Error("Buffer setup failed: %ld.", result_buffers);
			return;
		}
	}

	template < typename Vertex >
	HRESULT VertexShader< Vertex >::InitializeShader(ComPtr< ID3D11Device2 > device) {

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
		const HRESULT result_vertex_layout = device->CreateInputLayout(Vertex::input_element_desc, (UINT)Vertex::nb_input_elements, vertex_shader_blob->GetBufferPointer(), vertex_shader_blob->GetBufferSize(), m_vertex_layout.ReleaseAndGetAddressOf());
		if (FAILED(result_vertex_layout)) {
			Error("InputLayout creation failed: %ld.", result_vertex_shader);
			return result_vertex_layout;
		}

		return S_OK;
	}

	template < typename Vertex >
	HRESULT VertexShader< Vertex >::SetupBuffers(ComPtr< ID3D11Device2 > device) {
		// Describe the buffer resource.
		D3D11_BUFFER_DESC buffer_desc;
		ZeroMemory(&buffer_desc, sizeof(buffer_desc));
		buffer_desc.Usage          = D3D11_USAGE_DEFAULT;	         // How the buffer is expected to be read from and written to.
		buffer_desc.BindFlags      = D3D11_BIND_CONSTANT_BUFFER;     // How the buffer will be bound to the pipeline.
		buffer_desc.CPUAccessFlags = 0;						         // No CPU access is necessary.

		buffer_desc.ByteWidth      = sizeof(CameraTransformBuffer);	 // Size of the buffer in bytes.
		
																	 // Create the index buffer.
		// 1. A pointer to a D3D11_BUFFER_DESC structure that describes the buffer.
		// 2. A pointer to a D3D11_SUBRESOURCE_DATA structure that describes the initialization data.
		// 3. Address of a pointer to the ID3D11Buffer interface for the buffer object created.
		const HRESULT result_cb_camera = device->CreateBuffer(&buffer_desc, nullptr, m_cb_camera.ReleaseAndGetAddressOf());
		if (FAILED(result_cb_camera)) {
			return result_cb_camera;
		}

		buffer_desc.ByteWidth       = sizeof(ModelTransformBuffer);  // Size of the buffer in bytes.
		
		// Create the index buffer.
		// 1. A pointer to a D3D11_BUFFER_DESC structure that describes the buffer.
		// 2. A pointer to a D3D11_SUBRESOURCE_DATA structure that describes the initialization data.
		// 3. Address of a pointer to the ID3D11Buffer interface for the buffer object created.
		const HRESULT result_cb_model = device->CreateBuffer(&buffer_desc, nullptr, m_cb_model.ReleaseAndGetAddressOf());
		if (FAILED(result_cb_model)) {
			return result_cb_model;
		}

		return S_OK;
	}

	template < typename Vertex >
	void VertexShader< Vertex >::Update(ComPtr< ID3D11DeviceContext2 > device_context,
		const CameraTransformBuffer &camera, const ModelTransformBuffer &model) {
		device_context->IASetInputLayout(m_vertex_layout.Get());
		device_context->UpdateSubresource(m_cb_camera.Get(), 0, nullptr, &camera, 0, 0);
		device_context->UpdateSubresource(m_cb_model.Get(), 0, nullptr, &model, 0, 0);
		device_context->VSSetShader(m_vertex_shader.Get(), nullptr, 0);
		device_context->VSSetConstantBuffers(0, 1, m_cb_camera.GetAddressOf());
		device_context->VSSetConstantBuffers(1, 1, m_cb_model.GetAddressOf());
	}
}