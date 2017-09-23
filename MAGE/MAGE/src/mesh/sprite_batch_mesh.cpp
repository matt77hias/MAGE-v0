//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "mesh\sprite_batch_mesh.hpp"
#include "mesh\vertex.hpp"
#include "rendering\rendering_factory.hpp"
#include "collection\collection.hpp"
#include "logging\error.hpp"
#include "logging\exception.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	SpriteBatchMesh::SpriteBatchMesh()
		: SpriteBatchMesh(Pipeline::GetDevice()) {}

	SpriteBatchMesh::SpriteBatchMesh(ID3D11Device2 *device)
	 : Mesh(sizeof(VertexPositionColorTexture), 
		 DXGI_FORMAT_R16_UINT, 
		 D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST) {

		SetupVertexBuffer(device);
		SetupIndexBuffer(device);
	}

	SpriteBatchMesh::SpriteBatchMesh(SpriteBatchMesh &&sprite_batch_mesh) = default;

	SpriteBatchMesh::~SpriteBatchMesh() = default;

	void SpriteBatchMesh::SetupVertexBuffer(ID3D11Device2 *device) {
		
		Assert(device);
		
		const HRESULT result_vertex_buffer = CreateDynamicVertexBuffer< VertexPositionColorTexture >(
			device, m_vertex_buffer.ReleaseAndGetAddressOf(), nullptr, MaxVerticesPerBatch());
		ThrowIfFailed(result_vertex_buffer, "Vertex buffer creation failed: %08X.", result_vertex_buffer);
	
		SetNumberOfVertices(MaxVerticesPerBatch());
	}

	void SpriteBatchMesh::SetupIndexBuffer(ID3D11Device2 *device) {
		
		Assert(device);
		
		static_assert(MaxVerticesPerBatch() < USHRT_MAX, 
			"s_max_sprites_per_batch too large for 16-bit indices.");

		// Create indices.
		vector< uint16_t > indices;
		indices.reserve(MaxIndicesPerBatch());
		for (uint16_t i = 0; i < MaxVerticesPerBatch(); i += s_vertices_per_sprite) {
			// First triangle
			indices.push_back(i);
			indices.push_back(i + 1);
			indices.push_back(i + 2);
			// Second triangle
			indices.push_back(i + 1);
			indices.push_back(i + 3);
			indices.push_back(i + 2);
		}

		const HRESULT result_index_buffer = CreateStaticIndexBuffer< uint16_t >(
			device, m_index_buffer.ReleaseAndGetAddressOf(), indices.data(), indices.size());
		ThrowIfFailed(result_index_buffer, "Index buffer creation failed: %08X.", result_index_buffer);

		SetNumberOfIndices(indices.size());
	}

	HRESULT SpriteBatchMesh::MapVertexBuffer(ID3D11DeviceContext2 *device_context,
		D3D11_MAP map_type, D3D11_MAPPED_SUBRESOURCE *mapped_buffer) {
		
		Assert(mapped_buffer);

		return Pipeline::Map(device_context, 
			m_vertex_buffer.Get(), 0u, map_type, 0u, mapped_buffer);
	}

	void SpriteBatchMesh::UnmapVertexBuffer(ID3D11DeviceContext2 *device_context) {
		
		Pipeline::Unmap(device_context, 
			m_vertex_buffer.Get(), 0u);
	}
}