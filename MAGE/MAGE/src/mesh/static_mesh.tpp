#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "rendering\rendering_factory.hpp"
#include "utils\logging\error.hpp"
#include "utils\exception\exception.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	template < typename VertexT, typename IndexT >
	StaticMesh::StaticMesh(
		const VertexT *vertices, size_t nb_vertices,
		const IndexT *indices, size_t nb_indices, 
		DXGI_FORMAT index_format, D3D11_PRIMITIVE_TOPOLOGY primitive_topology)
		: StaticMesh(Pipeline::GetDevice(),
			vertices, nb_vertices,
			indices, nb_indices, 
			index_format, primitive_topology) {}

	template < typename VertexT, typename IndexT >
	StaticMesh::StaticMesh(ID3D11Device5 *device,
		const VertexT *vertices, size_t nb_vertices, 
		const IndexT *indices, size_t nb_indices, 
		DXGI_FORMAT index_format, D3D11_PRIMITIVE_TOPOLOGY primitive_topology)
		: Mesh(sizeof(VertexT), index_format, primitive_topology), 
		m_aabb(), m_bs() {

		SetupBoundingVolumes(vertices, nb_vertices);
		SetupVertexBuffer(device, vertices, nb_vertices);
		SetupIndexBuffer(device, indices, nb_indices);
	}

	template < typename VertexT, typename IndexT >
	StaticMesh::StaticMesh(
		const vector< VertexT > &vertices, 
		const vector< IndexT > &indices, 
		DXGI_FORMAT index_format, D3D11_PRIMITIVE_TOPOLOGY primitive_topology)
		: StaticMesh(Pipeline::GetDevice(),
			vertices, indices, 
			index_format, primitive_topology) {}

	template < typename VertexT, typename IndexT >
	StaticMesh::StaticMesh(ID3D11Device5 *device,
		const vector< VertexT > &vertices, 
		const vector< IndexT > &indices, 
		DXGI_FORMAT index_format, D3D11_PRIMITIVE_TOPOLOGY primitive_topology)
		: StaticMesh(device, 
			vertices.data(), vertices.size(), 
			indices.data(), indices.size(), 
			index_format, primitive_topology) {}

	template < typename VertexT >
	void StaticMesh::SetupBoundingVolumes(
		const VertexT *vertices, size_t nb_vertices) noexcept {
		
		Assert(vertices);

		for (const VertexT *v = vertices; v < vertices + nb_vertices; ++v) {
			m_aabb = Union(m_aabb, *v);
		}
		
		m_bs.m_p = m_aabb.Centroid();
		
		for (const VertexT *v = vertices; v < vertices + nb_vertices; ++v) {
			m_bs = Union(m_bs, *v);
		}
	}

	template < typename VertexT >
	void StaticMesh::SetupVertexBuffer(ID3D11Device5 *device, 
		const VertexT *vertices, size_t nb_vertices) {
		
		Assert(device);
		Assert(vertices);

		const HRESULT result_vertex_buffer = CreateStaticVertexBuffer< VertexT >(
			device, m_vertex_buffer.ReleaseAndGetAddressOf(), vertices, nb_vertices);
		ThrowIfFailed(result_vertex_buffer, 
			"Vertex buffer creation failed: %08X.", result_vertex_buffer);

		SetNumberOfVertices(nb_vertices);
	}

	template< typename IndexT >
	void StaticMesh::SetupIndexBuffer(ID3D11Device5 *device, 
		const IndexT *indices, size_t nb_indices) {
		
		Assert(device);
		Assert(indices);

		const HRESULT result_index_buffer = CreateStaticIndexBuffer< IndexT >(
			device, m_index_buffer.ReleaseAndGetAddressOf(), indices, nb_indices);
		ThrowIfFailed(result_index_buffer, 
			"Index buffer creation failed: %08X.", result_index_buffer);

		SetNumberOfIndices(nb_indices);
	}
}