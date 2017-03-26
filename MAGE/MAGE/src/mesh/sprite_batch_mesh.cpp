//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "mesh\sprite_batch_mesh.hpp"
#include "mesh\vertex.hpp"
#include "rendering\rendering_factory.hpp"
#include "collection\collection.hpp"
#include "logging\error.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	SpriteBatchMesh::SpriteBatchMesh(ComPtr< ID3D11Device2 > device, ComPtr< ID3D11DeviceContext2 > device_context)
	 : Mesh(device, device_context, sizeof(VertexPositionColorTexture), DXGI_FORMAT_R16_UINT) {

			const HRESULT result_vertex_buffer = SetupVertexBuffer();
			if (FAILED(result_vertex_buffer)) {
				Error("Vertex buffer setup failed: %08X.", result_vertex_buffer);
				return;
			}

			const HRESULT result_index_buffer = SetupIndexBuffer();
			if (FAILED(result_index_buffer)) {
				Error("Index buffer setup failed: %08X.", result_index_buffer);
				return;
			}
	}

	HRESULT SpriteBatchMesh::SetupVertexBuffer() {
		const HRESULT result_vertex_buffer = CreateDynamicVertexBuffer< VertexPositionColorTexture >(*m_device.Get(), m_vertex_buffer.ReleaseAndGetAddressOf(), nullptr, MaxVerticesPerSprite());
		if (FAILED(result_vertex_buffer)) {
			Error("Vertex buffer creation failed: %08X.", result_vertex_buffer);
			return result_vertex_buffer;
		}

		return S_OK;
	}

	HRESULT SpriteBatchMesh::SetupIndexBuffer() {
		static_assert(MaxVerticesPerSprite() < USHRT_MAX, "max_sprites_per_batch too large for 16-bit indices.");

		// Create indices.
		vector< uint16_t > indices;
		indices.reserve(MaxIndicesPerSprite());
		for (uint16_t i = 0; i < MaxVerticesPerSprite(); i += vertices_per_sprite) {
			// First triangle
			indices.push_back(i);
			indices.push_back(i + 1);
			indices.push_back(i + 2);
			// Second triangle
			indices.push_back(i + 1);
			indices.push_back(i + 3);
			indices.push_back(i + 2);
		}

		const HRESULT result_index_buffer = CreateIndexBuffer< uint16_t >(*m_device.Get(), m_index_buffer.ReleaseAndGetAddressOf(), indices.data(), indices.size());
		if (FAILED(result_index_buffer)) {
			Error("Index buffer creation failed: %08X.", result_index_buffer);
			return result_index_buffer;
		}

		SetNumberOfIndices(indices.size());

		return S_OK;
	}
}