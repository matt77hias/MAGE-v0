#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "rendering\rendering_factory.hpp"
#include "logging\error.hpp"
#include "logging\exception.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	template < typename VertexT, typename IndexT >
	StaticMesh::StaticMesh(const VertexT *vertices, size_t nb_vertices,
		const IndexT *indices, size_t nb_indices, DXGI_FORMAT index_format,
		D3D11_PRIMITIVE_TOPOLOGY primitive_topology)
		: StaticMesh(GetRenderingDevice(), GetRenderingDeviceContext(),
			vertices, nb_vertices, indices, nb_indices, index_format, primitive_topology) {}

	template < typename VertexT, typename IndexT >
	StaticMesh::StaticMesh(ID3D11Device2 *device, ID3D11DeviceContext2 *device_context,
		const VertexT *vertices, size_t nb_vertices, 
		const IndexT *indices, size_t nb_indices, DXGI_FORMAT index_format,
		D3D11_PRIMITIVE_TOPOLOGY primitive_topology)
		: Mesh(device, device_context, sizeof(VertexT), index_format, primitive_topology), 
		m_aabb(), m_bs() {

		Assert(vertices);
		Assert(indices);
		
		SetupBoundingVolumes(vertices, nb_vertices);
		SetupVertexBuffer(vertices, nb_vertices);
		SetupIndexBuffer(indices, nb_indices);
	}

	template < typename VertexT, typename IndexT >
	StaticMesh::StaticMesh(const vector< VertexT > &vertices, 
		const vector< IndexT > &indices, DXGI_FORMAT index_format,
		D3D11_PRIMITIVE_TOPOLOGY primitive_topology)
		: StaticMesh(GetRenderingDevice(), GetRenderingDeviceContext(),
			vertices, indices, 
			index_format, primitive_topology) {}

	template < typename VertexT, typename IndexT >
	StaticMesh::StaticMesh(ID3D11Device2 *device, ID3D11DeviceContext2 *device_context,
		const vector< VertexT > &vertices, 
		const vector< IndexT > &indices, DXGI_FORMAT index_format,
		D3D11_PRIMITIVE_TOPOLOGY primitive_topology)
		: StaticMesh(device, device_context,
			vertices.data(), vertices.size(), 
			indices.data(), indices.size(), 
			index_format, primitive_topology) {}

	template < typename VertexT >
	void StaticMesh::SetupBoundingVolumes(const VertexT *vertices, size_t nb_vertices) noexcept {
		for (const VertexT *v = vertices; v < vertices + nb_vertices; ++v) {
			m_aabb = Union(m_aabb, *v);
		}
		
		m_bs.m_p = m_aabb.Centroid();
		
		for (const VertexT *v = vertices; v < vertices + nb_vertices; ++v) {
			m_bs = Union(m_bs, *v);
		}
	}

	template < typename VertexT >
	void StaticMesh::SetupVertexBuffer(const VertexT *vertices, size_t nb_vertices) {
		const HRESULT result_vertex_buffer = CreateStaticVertexBuffer< VertexT >(m_device, m_vertex_buffer.ReleaseAndGetAddressOf(), vertices, nb_vertices);
		if (FAILED(result_vertex_buffer)) {
			throw FormattedException("Vertex buffer creation failed: %08X.", result_vertex_buffer);
		}

		SetNumberOfVertices(nb_vertices);
	}

	template< typename IndexT >
	void StaticMesh::SetupIndexBuffer(const IndexT *indices, size_t nb_indices) {
		const HRESULT result_index_buffer = CreateStaticIndexBuffer< IndexT >(m_device, m_index_buffer.ReleaseAndGetAddressOf(), indices, nb_indices);
		if (FAILED(result_index_buffer)) {
			throw FormattedException("Index buffer creation failed: %08X.", result_index_buffer);
		}

		SetNumberOfIndices(nb_indices);
	}
}