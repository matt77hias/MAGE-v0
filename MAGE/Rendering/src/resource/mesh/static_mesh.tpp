#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "renderer\factory.hpp"
#include "exception\exception.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage::rendering {

	template< typename VertexT, typename IndexT >
	StaticMesh< VertexT, IndexT >
		::StaticMesh(ID3D11Device& device,
		             std::vector< VertexT > vertices,
		             std::vector< IndexT >  indices,
		             D3D11_PRIMITIVE_TOPOLOGY primitive_topology)
		: Mesh(sizeof(VertexT), 
			   mage::rendering::GetIndexFormat< IndexT >(),
			   primitive_topology),
	    m_vertices(std::move(vertices)), 
		m_indices(std::move(indices)) {

		SetupVertexBuffer(device);
		SetupIndexBuffer(device);
	}

	template< typename VertexT, typename IndexT >
	StaticMesh< VertexT, IndexT >
		::StaticMesh(StaticMesh&& mesh) noexcept = default;

	template< typename VertexT, typename IndexT >
	StaticMesh< VertexT, IndexT >
		::~StaticMesh() = default;

	template< typename VertexT, typename IndexT >
	StaticMesh< VertexT, IndexT >& StaticMesh< VertexT, IndexT >
		::operator=(StaticMesh&& mesh) noexcept = default;

	template< typename VertexT, typename IndexT >
	void StaticMesh< VertexT, IndexT >
		::SetupVertexBuffer(ID3D11Device& device) {
		
		const HRESULT result = CreateStaticVertexBuffer(
			device, m_vertex_buffer.ReleaseAndGetAddressOf(), 
			gsl::make_span(static_cast< const std::vector< VertexT >& >(m_vertices)));
		ThrowIfFailed(result, "Vertex buffer creation failed: %08X.", result);

		SetNumberOfVertices(m_vertices.size());
	}

	template< typename VertexT, typename IndexT >
	void StaticMesh< VertexT, IndexT >
		::SetupIndexBuffer(ID3D11Device& device) {
		
		const HRESULT result = CreateStaticIndexBuffer(
			device, m_index_buffer.ReleaseAndGetAddressOf(), 
			gsl::make_span(static_cast< const std::vector< IndexT >& >(m_indices)));
		ThrowIfFailed(result, "Index buffer creation failed: %08X.", result);

		SetNumberOfIndices(m_indices.size());
	}
}