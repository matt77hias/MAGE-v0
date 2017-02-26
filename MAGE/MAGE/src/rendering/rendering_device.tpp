#pragma once

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	template < typename VertexT >
	HRESULT RenderingDevice::CreateVertexBuffer(ID3D11Buffer **buffer, const VertexT *vertices, size_t nb_vertices) const {
		// Describe the buffer resource.
		D3D11_BUFFER_DESC buffer_desc;
		ZeroMemory(&buffer_desc, sizeof(buffer_desc));
		buffer_desc.ByteWidth      = (UINT)(nb_vertices * sizeof(VertexT));
		buffer_desc.Usage          = D3D11_USAGE_DEFAULT;
		buffer_desc.BindFlags      = D3D11_BIND_VERTEX_BUFFER;
		buffer_desc.CPUAccessFlags = 0;

		// Specify data for initializing a subresource.
		D3D11_SUBRESOURCE_DATA init_data;
		ZeroMemory(&init_data, sizeof(init_data));
		init_data.pSysMem         = vertices;

		// Create the vertex buffer.
		// 1. A pointer to a D3D11_BUFFER_DESC structure that describes the buffer.
		// 2. A pointer to a D3D11_SUBRESOURCE_DATA structure that describes the initialization data.
		// 3. Address of a pointer to the ID3D11Buffer interface for the buffer object created.
		return m_device->CreateBuffer(&buffer_desc, &init_data, buffer);
	}

	template < typename IndexT >
	HRESULT RenderingDevice::CreateIndexBuffer(ID3D11Buffer **buffer, const IndexT *indices, size_t nb_indices) const {
		// Describe the buffer resource.
		D3D11_BUFFER_DESC buffer_desc;
		ZeroMemory(&buffer_desc, sizeof(buffer_desc));
		buffer_desc.ByteWidth      = (UINT)(nb_indices * sizeof(IndexT));
		buffer_desc.Usage          = D3D11_USAGE_DEFAULT;
		buffer_desc.BindFlags      = D3D11_BIND_INDEX_BUFFER;
		buffer_desc.CPUAccessFlags = 0;

		// Specify data for initializing a subresource.
		D3D11_SUBRESOURCE_DATA init_data;
		ZeroMemory(&init_data, sizeof(init_data));
		init_data.pSysMem          = indices;

		// Create the index buffer.
		// 1. A pointer to a D3D11_BUFFER_DESC structure that describes the buffer.
		// 2. A pointer to a D3D11_SUBRESOURCE_DATA structure that describes the initialization data.
		// 3. Address of a pointer to the ID3D11Buffer interface for the buffer object created.
		return m_device->CreateBuffer(&buffer_desc, &init_data, buffer);
	}

	template < typename BufferT >
	HRESULT RenderingDevice::CreateConstantBuffer(ID3D11Buffer **buffer) const {
		// Describe the buffer resource.
		D3D11_BUFFER_DESC buffer_desc;
		ZeroMemory(&buffer_desc, sizeof(buffer_desc));
		buffer_desc.ByteWidth      = (UINT)sizeof(BufferT);	     // Size of the buffer in bytes.
		buffer_desc.Usage          = D3D11_USAGE_DEFAULT;	     // How the buffer is expected to be read from and written to.
		buffer_desc.BindFlags      = D3D11_BIND_CONSTANT_BUFFER; // How the buffer will be bound to the pipeline.
		buffer_desc.CPUAccessFlags = 0;						     // No CPU access is necessary.

		// Create the index buffer.
		// 1. A pointer to a D3D11_BUFFER_DESC structure that describes the buffer.
		// 2. A pointer to a D3D11_SUBRESOURCE_DATA structure that describes the initialization data.
		// 3. Address of a pointer to the ID3D11Buffer interface for the buffer object created.
		return m_device->CreateBuffer(&buffer_desc, nullptr, buffer);
	}

	inline HRESULT RenderingDevice::CreateVertexShader(ID3D11VertexShader **shader, ComPtr< ID3DBlob > shader_blob) const {
		// Create the vertex shader
		// 1. A pointer to the compiled vertex shader.
		// 2. The size of the compiled vertex shader.
		// 3. A pointer to a class linkage interface.
		// 4. Address of a pointer to a vertex shader.
		return m_device->CreateVertexShader(shader_blob->GetBufferPointer(), shader_blob->GetBufferSize(), nullptr, shader);
	}

	inline HRESULT RenderingDevice::CreatePixelShader(ID3D11PixelShader **shader, ComPtr< ID3DBlob > shader_blob) const {
		// Create the pixel shader.
		// 1. A pointer to the compiled pixel shader.
		// 2. The size of the compiled pixel shader.
		// 3. A pointer to a class linkage interface.
		// 4. Address of a pointer to a pixel shader.
		return m_device->CreatePixelShader(shader_blob->GetBufferPointer(), shader_blob->GetBufferSize(), nullptr, shader);
	}

	inline HRESULT RenderingDevice::CreateVertexInputLayout(ID3D11InputLayout **input_layout, ComPtr< ID3DBlob > shader_blob, const D3D11_INPUT_ELEMENT_DESC *input_element_desc, uint32_t nb_input_elements) const {
		// Create the ID3D11InputLayout.
		// 1. An array of the input-assembler stage input data types; each type is described by an element description.
		// 2. The number of input-data types in the array of input-elements.
		// 3. A pointer to the compiled shader.
		// 4. The size of the compiled shader.
		// 5. A pointer to the input-layout object created
		return m_device->CreateInputLayout(input_element_desc, (UINT)nb_input_elements, shader_blob->GetBufferPointer(), shader_blob->GetBufferSize(), input_layout);
	}
}