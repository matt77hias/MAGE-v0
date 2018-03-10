#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "renderer\factory.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage::rendering {

	template< typename VertexT, typename IndexT >
	PrimitiveBatchMesh< VertexT, IndexT >
		::PrimitiveBatchMesh(ID3D11Device& device,
			                 size_t nb_vertices,
			                 const std::vector< IndexT >& indices,
			                 D3D11_PRIMITIVE_TOPOLOGY primitive_topology)
		: Mesh(sizeof(VertexT), 
			   mage::rendering::GetIndexFormat< IndexT >(),
			   primitive_topology) {

		SetupVertexBuffer(device, nb_vertices);
		SetupIndexBuffer(device, indices);
	}

	template< typename VertexT, typename IndexT >
	PrimitiveBatchMesh< VertexT, IndexT >
		::PrimitiveBatchMesh(PrimitiveBatchMesh&& mesh) noexcept = default;

	template< typename VertexT, typename IndexT >
	PrimitiveBatchMesh< VertexT, IndexT >
		::~PrimitiveBatchMesh() = default;

	template< typename VertexT, typename IndexT >
	PrimitiveBatchMesh< VertexT, IndexT >& PrimitiveBatchMesh< VertexT, IndexT >
		::operator=(PrimitiveBatchMesh&& mesh) noexcept = default;

	template< typename VertexT, typename IndexT >
	void PrimitiveBatchMesh< VertexT, IndexT >
		::SetupVertexBuffer(ID3D11Device& device, size_t nb_vertices) {
		
		const HRESULT result
			= CreateDynamicVertexBuffer< VertexT >(
				device, m_vertex_buffer.ReleaseAndGetAddressOf(),
				gsl::span< const VertexT >());
		ThrowIfFailed(result, "Vertex buffer creation failed: %08X.", result);

		SetNumberOfVertices(nb_vertices);
	}

	template< typename VertexT, typename IndexT >
	void PrimitiveBatchMesh< VertexT, IndexT >
		::SetupIndexBuffer(ID3D11Device& device, 
			               const std::vector< IndexT >& indices) {
		
		const HRESULT result = CreateStaticIndexBuffer(
			device, m_index_buffer.ReleaseAndGetAddressOf(),
			gsl::make_span(indices));
		ThrowIfFailed(result, "Index buffer creation failed: %08X.", result);

		SetNumberOfIndices(indices.size());
	}
}