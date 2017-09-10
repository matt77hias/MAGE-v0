#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "logging\error.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	//-------------------------------------------------------------------------
	// Buffers
	//-------------------------------------------------------------------------

	template < typename VertexT >
	HRESULT CreateStaticVertexBuffer(ID3D11Device2 *device, 
		ID3D11Buffer **buffer, 
		const VertexT *vertices, size_t nb_vertices) noexcept {
		
		Assert(device);
		Assert(buffer);
		Assert(vertices);
		
		// Describe the buffer resource.
		D3D11_BUFFER_DESC buffer_desc = {};
		buffer_desc.ByteWidth      = static_cast< UINT >(nb_vertices * sizeof(VertexT));
		buffer_desc.Usage          = D3D11_USAGE_IMMUTABLE;
		buffer_desc.BindFlags      = D3D11_BIND_VERTEX_BUFFER;
		buffer_desc.CPUAccessFlags = 0;

		// Specify data for initializing a subresource.
		D3D11_SUBRESOURCE_DATA init_data = {};
		init_data.pSysMem = vertices;

		// Create the vertex buffer.
		return device->CreateBuffer(&buffer_desc, &init_data, buffer);
	}

	template < typename VertexT >
	HRESULT CreateDynamicVertexBuffer(ID3D11Device2 *device, 
		ID3D11Buffer **buffer, 
		const VertexT *vertices, size_t nb_vertices) noexcept {
		
		Assert(device);
		Assert(buffer);
		
		// Describe the buffer resource.
		D3D11_BUFFER_DESC buffer_desc = {};
		buffer_desc.ByteWidth      = static_cast< UINT >(nb_vertices * sizeof(VertexT));
		buffer_desc.Usage          = D3D11_USAGE_DYNAMIC;
		buffer_desc.BindFlags      = D3D11_BIND_VERTEX_BUFFER;
		buffer_desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

		if (!vertices) {
			// Create the vertex buffer.
			return device->CreateBuffer(&buffer_desc, nullptr, buffer);
		}

		// Specify data for initializing a subresource.
		D3D11_SUBRESOURCE_DATA init_data = {};
		init_data.pSysMem = vertices;

		// Create the vertex buffer.
		return device->CreateBuffer(&buffer_desc, &init_data, buffer);
	}

	template < typename IndexT >
	HRESULT CreateStaticIndexBuffer(ID3D11Device2 *device, 
		ID3D11Buffer **buffer, 
		const IndexT *indices, size_t nb_indices) noexcept {
		
		Assert(device);
		Assert(buffer);
		Assert(indices);
		
		// Describe the buffer resource.
		D3D11_BUFFER_DESC buffer_desc = {};
		buffer_desc.ByteWidth      = static_cast< UINT >(nb_indices * sizeof(IndexT));
		buffer_desc.Usage          = D3D11_USAGE_IMMUTABLE;
		buffer_desc.BindFlags      = D3D11_BIND_INDEX_BUFFER;
		buffer_desc.CPUAccessFlags = 0;

		// Specify data for initializing a subresource.
		D3D11_SUBRESOURCE_DATA init_data = {};
		init_data.pSysMem = indices;

		// Create the index buffer.
		return device->CreateBuffer(&buffer_desc, &init_data, buffer);
	}

	template < typename DataT >
	HRESULT CreateStaticConstantBuffer(ID3D11Device2 *device,
		ID3D11Buffer **buffer, 
		const DataT *data, size_t count) noexcept {
		
		Assert(device);
		Assert(buffer);
		Assert(data);
		
		// Describe the buffer resource.
		D3D11_BUFFER_DESC buffer_desc = {};
		buffer_desc.ByteWidth      = static_cast< UINT >(count * sizeof(DataT));
		buffer_desc.Usage          = D3D11_USAGE_IMMUTABLE;
		buffer_desc.BindFlags      = D3D11_BIND_CONSTANT_BUFFER;
		buffer_desc.CPUAccessFlags = 0;

		// Specify data for initializing a subresource.
		D3D11_SUBRESOURCE_DATA init_data = {};
		init_data.pSysMem = data;

		// Create the constant buffer.
		return device->CreateBuffer(&buffer_desc, &init_data, buffer);
	}

	template < typename DataT >
	HRESULT CreateDynamicConstantBuffer(ID3D11Device2 *device,
		ID3D11Buffer **buffer, 
		const DataT *data, size_t count) noexcept {
		
		Assert(device);
		Assert(buffer);
		
		// Describe the buffer resource.
		D3D11_BUFFER_DESC buffer_desc = {};
		buffer_desc.ByteWidth      = static_cast< UINT >(count * sizeof(DataT));
		buffer_desc.Usage          = D3D11_USAGE_DYNAMIC;
		buffer_desc.BindFlags      = D3D11_BIND_CONSTANT_BUFFER;
		buffer_desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

		if (!data) {
			// Create the constant buffer.
			return device->CreateBuffer(&buffer_desc, nullptr, buffer);
		}

		// Specify data for initializing a subresource.
		D3D11_SUBRESOURCE_DATA init_data = {};
		init_data.pSysMem = data;

		// Create the constant buffer.
		return device->CreateBuffer(&buffer_desc, &init_data, buffer);
	}

	template < typename DataT >
	HRESULT CreateStaticStructuredBuffer(ID3D11Device2 *device,
		ID3D11Buffer **buffer, 
		const DataT *data, size_t count) noexcept {
		
		Assert(device);
		Assert(buffer);
		Assert(data);
		
		// Describe the buffer resource.
		D3D11_BUFFER_DESC buffer_desc = {};
		buffer_desc.ByteWidth           = static_cast< UINT >(count * sizeof(DataT));
		buffer_desc.Usage               = D3D11_USAGE_IMMUTABLE;
		buffer_desc.BindFlags           = D3D11_BIND_SHADER_RESOURCE;
		buffer_desc.CPUAccessFlags      = 0;
		buffer_desc.MiscFlags           = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;
		buffer_desc.StructureByteStride = static_cast< UINT >(sizeof(DataT));

		// Specify data for initializing a subresource.
		D3D11_SUBRESOURCE_DATA init_data = {};
		init_data.pSysMem = data;

		// Create the structured buffer.
		return device->CreateBuffer(&buffer_desc, &init_data, buffer);
	}

	template < typename DataT >
	HRESULT CreateDynamicStructuredBuffer(ID3D11Device2 *device,
		ID3D11Buffer **buffer, 
		const DataT *data, size_t count) noexcept {
		
		Assert(device);
		Assert(buffer);
		
		// Describe the buffer resource.
		D3D11_BUFFER_DESC buffer_desc = {};
		buffer_desc.ByteWidth           = static_cast< UINT >(count * sizeof(DataT));
		buffer_desc.Usage               = D3D11_USAGE_DYNAMIC;
		buffer_desc.BindFlags           = D3D11_BIND_SHADER_RESOURCE;
		buffer_desc.CPUAccessFlags      = D3D11_CPU_ACCESS_WRITE;
		buffer_desc.MiscFlags           = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;
		buffer_desc.StructureByteStride = static_cast< UINT >(sizeof(DataT));

		if (!data) {
			// Create the structured buffer.
			return device->CreateBuffer(&buffer_desc, nullptr, buffer);
		}

		// Specify data for initializing a subresource.
		D3D11_SUBRESOURCE_DATA init_data = {};
		init_data.pSysMem = data;

		// Create the structured buffer.
		return device->CreateBuffer(&buffer_desc, &init_data, buffer);
	}
}