#pragma once

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	//-------------------------------------------------------------------------
	// Buffers
	//-------------------------------------------------------------------------

	template < typename VertexT >
	HRESULT CreateStaticVertexBuffer(ID3D11Device2 *device, ID3D11Buffer **buffer, const VertexT *vertices, size_t nb_vertices) {
		// Describe the buffer resource.
		D3D11_BUFFER_DESC buffer_desc;
		ZeroMemory(&buffer_desc, sizeof(buffer_desc));
		buffer_desc.ByteWidth      = static_cast< UINT >(nb_vertices * sizeof(VertexT));
		buffer_desc.Usage          = D3D11_USAGE_DEFAULT;
		buffer_desc.BindFlags      = D3D11_BIND_VERTEX_BUFFER;
		buffer_desc.CPUAccessFlags = 0;

		// Specify data for initializing a subresource.
		D3D11_SUBRESOURCE_DATA init_data;
		ZeroMemory(&init_data, sizeof(init_data));
		init_data.pSysMem = vertices;

		// Create the vertex buffer.
		// 1. A pointer to a D3D11_BUFFER_DESC structure that describes the buffer.
		// 2. A pointer to a D3D11_SUBRESOURCE_DATA structure that describes the initialization data.
		// 3. Address of a pointer to the ID3D11Buffer interface for the buffer object created.
		return device->CreateBuffer(&buffer_desc, &init_data, buffer);
	}

	template < typename VertexT >
	HRESULT CreateDynamicVertexBuffer(ID3D11Device2 *device, ID3D11Buffer **buffer, const VertexT *vertices, size_t nb_vertices) {
		// Describe the buffer resource.
		D3D11_BUFFER_DESC buffer_desc;
		ZeroMemory(&buffer_desc, sizeof(buffer_desc));
		buffer_desc.ByteWidth      = static_cast< UINT >(nb_vertices * sizeof(VertexT));
		buffer_desc.Usage          = D3D11_USAGE_DYNAMIC;
		buffer_desc.BindFlags      = D3D11_BIND_VERTEX_BUFFER;
		buffer_desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

		if (!vertices) {
			return device->CreateBuffer(&buffer_desc, nullptr, buffer);
		}

		// Specify data for initializing a subresource.
		D3D11_SUBRESOURCE_DATA init_data;
		ZeroMemory(&init_data, sizeof(init_data));
		init_data.pSysMem = vertices;

		// Create the vertex buffer.
		// 1. A pointer to a D3D11_BUFFER_DESC structure that describes the buffer.
		// 2. A pointer to a D3D11_SUBRESOURCE_DATA structure that describes the initialization data.
		// 3. Address of a pointer to the ID3D11Buffer interface for the buffer object created.
		return device->CreateBuffer(&buffer_desc, &init_data, buffer);
	}

	template < typename IndexT >
	HRESULT CreateIndexBuffer(ID3D11Device2 *device, ID3D11Buffer **buffer, const IndexT *indices, size_t nb_indices) {
		// Describe the buffer resource.
		D3D11_BUFFER_DESC buffer_desc;
		ZeroMemory(&buffer_desc, sizeof(buffer_desc));
		buffer_desc.ByteWidth      = static_cast< UINT >(nb_indices * sizeof(IndexT));
		buffer_desc.Usage          = D3D11_USAGE_DEFAULT;
		buffer_desc.BindFlags      = D3D11_BIND_INDEX_BUFFER;
		buffer_desc.CPUAccessFlags = 0;

		// Specify data for initializing a subresource.
		D3D11_SUBRESOURCE_DATA init_data;
		ZeroMemory(&init_data, sizeof(init_data));
		init_data.pSysMem = indices;

		// Create the index buffer.
		// 1. A pointer to a D3D11_BUFFER_DESC structure that describes the buffer.
		// 2. A pointer to a D3D11_SUBRESOURCE_DATA structure that describes the initialization data.
		// 3. Address of a pointer to the ID3D11Buffer interface for the buffer object created.
		return device->CreateBuffer(&buffer_desc, &init_data, buffer);
	}

	template < typename BufferT >
	HRESULT CreateConstantBuffer(ID3D11Device2 *device, ID3D11Buffer **buffer) {
		// Describe the buffer resource.
		D3D11_BUFFER_DESC buffer_desc;
		ZeroMemory(&buffer_desc, sizeof(buffer_desc));
		buffer_desc.ByteWidth      = static_cast< UINT >(sizeof(BufferT)); // Size of the buffer in bytes.
		buffer_desc.Usage          = D3D11_USAGE_DEFAULT;	               // How the buffer is expected to be read from and written to.
		buffer_desc.BindFlags      = D3D11_BIND_CONSTANT_BUFFER;           // How the buffer will be bound to the pipeline.
		buffer_desc.CPUAccessFlags = 0;						               // No CPU access is necessary.

		// Create the index buffer.
		// 1. A pointer to a D3D11_BUFFER_DESC structure that describes the buffer.
		// 2. A pointer to a D3D11_SUBRESOURCE_DATA structure that describes the initialization data.
		// 3. Address of a pointer to the ID3D11Buffer interface for the buffer object created.
		return device->CreateBuffer(&buffer_desc, nullptr, buffer);
	}
}