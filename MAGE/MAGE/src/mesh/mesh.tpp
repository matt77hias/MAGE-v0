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

	template < typename VertexT >
	Mesh::Mesh(ComPtr< ID3D11Device2 > device, const VertexT *vertices, size_t nb_vertices, const uint32_t *indices, size_t nb_indices)
		: m_nb_vertices(nb_vertices), m_nb_indices(nb_indices), m_vertex_size(sizeof(VertexT)) {
		
		const HRESULT result_initialization = InitializeMesh< VertexT >(device, vertices, indices);
		if (FAILED(result_initialization)) {
			Error("Mesh initialization failed: %08X.", result_initialization);
			return;
		}
	}

	template < typename VertexT >
	HRESULT Mesh::InitializeMesh(ComPtr< ID3D11Device2 > device, const VertexT *vertices, const uint32_t *indices) {

		const HRESULT result_vertex_buffer = CreateVertexBuffer< VertexT >(device, m_vertex_buffer.ReleaseAndGetAddressOf(), vertices, m_nb_vertices);
		if (FAILED(result_vertex_buffer)) {
			Error("Vertex buffer creation failed: %08X.", result_vertex_buffer);
			return result_vertex_buffer;
		}

		const HRESULT result_index_buffer = CreateIndexBuffer< uint32_t >(device, m_index_buffer.ReleaseAndGetAddressOf(), indices, m_nb_indices);
		if (FAILED(result_index_buffer)) {
			Error("Index buffer creation failed: %08X.", result_index_buffer);
			return result_index_buffer;
		}

		return S_OK;
	}

	inline void Mesh::Render(ComPtr< ID3D11DeviceContext2 > device_context) const {
		// Set the vertex buffer.
		UINT stride = static_cast< UINT >(m_vertex_size); // The size (in bytes) of the elements that are to be used from a vertex buffer.
		UINT offset = 0;								// The number of bytes between the first element of a vertex buffer and the first element that will be used.
		// 1. The first input slot for binding.
		// 2. The number of vertex buffers in the array.
		// 3. A pointer to an array of vertex buffers.
		// 4. A pointer to an array of stride values.
		// 5. A pointer to an array of offset values.
		device_context->IASetVertexBuffers(0, 1, m_vertex_buffer.GetAddressOf(), &stride, &offset);

		// Set the index buffer.
		// 1. A pointer to an ID3D11Buffer object.
		// 2. The format of the data in the index buffer.
		// 3. Offset (in bytes) from the start of the index buffer to the first index to use.
		device_context->IASetIndexBuffer(m_index_buffer.Get(), DXGI_FORMAT_R32_UINT, 0);

		// Bind information about the primitive type, and data order that describes input data for the input assembler stage.
		device_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	}
}