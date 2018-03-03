#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "rendering\rendering_factory.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	template< typename VertexT, typename IndexT >
	PrimitiveBatchMesh< VertexT, IndexT >
		::PrimitiveBatchMesh(ID3D11Device& device,
			                 size_t nb_vertices,
			                 const std::vector< IndexT >& indices,
			                 D3D11_PRIMITIVE_TOPOLOGY primitive_topology)
		: Mesh(sizeof(VertexT), 
			   mage::GetIndexFormat< IndexT >(),
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
		
		Assert(0 < nb_vertices);

		const HRESULT result
			= CreateDynamicVertexBuffer< VertexT >(
				device, m_vertex_buffer.ReleaseAndGetAddressOf(),
				nullptr, nb_vertices);
		ThrowIfFailed(result,
			"Vertex buffer creation failed: %08X.", result);

		SetNumberOfVertices(nb_vertices);
	}

	template< typename VertexT, typename IndexT >
	void PrimitiveBatchMesh< VertexT, IndexT >
		::SetupIndexBuffer(ID3D11Device& device, 
			               const std::vector< IndexT >& indices) {
		
		Assert(0 < indices.size());

		const HRESULT result = CreateStaticIndexBuffer(
			device, m_index_buffer.ReleaseAndGetAddressOf(),
			indices.data(), indices.size());
		ThrowIfFailed(result,
			"Index buffer creation failed: %08X.", result);

		SetNumberOfIndices(indices.size());
	}
}