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

	template< typename VertexT, typename IndexT >
	StaticMesh< VertexT, IndexT >::StaticMesh(
		std::vector< VertexT > vertices, 
		std::vector< IndexT >  indices,
		D3D11_PRIMITIVE_TOPOLOGY primitive_topology)
		: StaticMesh(Pipeline::GetDevice(),
			         std::move(vertices), 
			         std::move(indices), 
			         primitive_topology) {}

	template< typename VertexT, typename IndexT >
	StaticMesh< VertexT, IndexT >::StaticMesh(ID3D11Device5 *device,
		std::vector< VertexT > vertices,
		std::vector< IndexT >  indices,
		D3D11_PRIMITIVE_TOPOLOGY primitive_topology)
		: Mesh(sizeof(VertexT), 
			   mage::GetIndexFormat< IndexT >(),
			   primitive_topology),
	    m_vertices(std::move(vertices)), 
		m_indices(std::move(indices)) {

		SetupVertexBuffer(device);
		SetupIndexBuffer(device);
	}

	template< typename VertexT, typename IndexT >
	StaticMesh< VertexT, IndexT >
		::StaticMesh(StaticMesh &&mesh) noexcept = default;

	template< typename VertexT, typename IndexT >
	StaticMesh< VertexT, IndexT >
		::StaticMesh::~StaticMesh() = default;

	template< typename VertexT, typename IndexT >
	StaticMesh< VertexT, IndexT > &StaticMesh< VertexT, IndexT >
		::StaticMesh::operator=(StaticMesh &&mesh) noexcept = default;

	template< typename VertexT, typename IndexT >
	void StaticMesh< VertexT, IndexT >
		::SetupVertexBuffer(ID3D11Device5 *device) {
		
		Assert(device);

		const HRESULT result = CreateStaticVertexBuffer(
			device, m_vertex_buffer.ReleaseAndGetAddressOf(), 
			m_vertices.data(), m_vertices.size());
		ThrowIfFailed(result,
			"Vertex buffer creation failed: %08X.", result);

		SetNumberOfVertices(m_vertices.size());
	}

	template< typename VertexT, typename IndexT >
	void StaticMesh< VertexT, IndexT >
		::SetupIndexBuffer(ID3D11Device5 *device) {
		
		Assert(device);

		const HRESULT result = CreateStaticIndexBuffer(
			device, m_index_buffer.ReleaseAndGetAddressOf(), 
			m_indices.data(), m_indices.size());
		ThrowIfFailed(result, 
			"Index buffer creation failed: %08X.", result);

		SetNumberOfIndices(m_indices.size());
	}
}