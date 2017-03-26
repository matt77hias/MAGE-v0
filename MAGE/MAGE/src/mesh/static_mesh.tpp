#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "rendering\rendering_factory.hpp"
#include "logging\error.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	template < typename VertexT >
	StaticMesh::StaticMesh(ComPtr< ID3D11Device2 > device, ComPtr< ID3D11DeviceContext2 > device_context,
		const VertexT *vertices, size_t nb_vertices, const uint32_t *indices, size_t nb_indices)
		: Mesh(device, device_context, sizeof(VertexT)) {
		
		const HRESULT result_vertex_buffer = SetupVertexBuffer< VertexT >(vertices, nb_vertices);
		if (FAILED(result_vertex_buffer)) {
			Error("Vertex buffer setup failed: %08X.", result_vertex_buffer);
			return;
		}

		const HRESULT result_index_buffer = SetupIndexBuffer(indices, nb_indices);
		if (FAILED(result_index_buffer)) {
			Error("Index buffer setup failed: %08X.", result_index_buffer);
			return;
		}
	}

	template < typename VertexT >
	HRESULT StaticMesh::SetupVertexBuffer(const VertexT *vertices, size_t nb_vertices) {
		const HRESULT result_vertex_buffer = CreateStaticVertexBuffer< VertexT >(*m_device.Get(), m_vertex_buffer.ReleaseAndGetAddressOf(), vertices, nb_vertices);
		if (FAILED(result_vertex_buffer)) {
			Error("Vertex buffer creation failed: %08X.", result_vertex_buffer);
			return result_vertex_buffer;
		}

		SetNumberOfVertices(nb_vertices);

		return S_OK;
	}
}