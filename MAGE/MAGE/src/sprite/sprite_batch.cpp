//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "sprite\sprite_batch.hpp"
#include "collection\collection.hpp"
#include "rendering\rendering_factory.hpp"
#include "mesh\vertex.hpp"
#include "logging\error.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// System Includes
//-----------------------------------------------------------------------------
#pragma region

#include <stdint.h>

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	static const size_t initial_queue_size    = 64;
	static const size_t min_sprites_per_batch = 128;
	static const size_t max_sprites_per_batch = 2048;
	static const size_t vertices_per_sprite   = 4; // quad = 2 triangles
	static const size_t indices_per_sprite    = 6; // quad = 2 triangles

	static constexpr size_t MinVerticesPerSprite() {
		return min_sprites_per_batch * vertices_per_sprite;
	}
	static constexpr size_t MaxVerticesPerSprite() {
		return max_sprites_per_batch * vertices_per_sprite;
	}
	static constexpr size_t MinIndicesPerSprite() {
		return min_sprites_per_batch * indices_per_sprite;
	}
	static constexpr size_t MaxIndicesPerSprite() {
		return max_sprites_per_batch * indices_per_sprite;
	}

	SpriteBatch::SpriteBatch()
		: m_in_begin_end_pair(false) {

	}

	HRESULT SpriteBatch::InitializeVertexBuffer(ID3D11Device2 &device) {
		const HRESULT result_create = CreateDynamicVertexBuffer< VertexPositionColorTexture >(device, m_vertex_buffer.ReleaseAndGetAddressOf(), nullptr, MaxVerticesPerSprite());
		if (FAILED(result_create)) {
			Error("Vertex buffer creation failed: %08X.", result_create);
			return result_create;
		}

		return S_OK;
	}

	HRESULT SpriteBatch::InitializeIndexBuffer(ID3D11Device2 &device) {
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

		const HRESULT result_create = CreateIndexBuffer< uint16_t >(device, m_index_buffer.ReleaseAndGetAddressOf(), indices.data(), indices.size());
		if (FAILED(result_create)) {
			Error("Index buffer creation failed: %08X.", result_create);
			return result_create;
		}

		return S_OK;
	}

	void SpriteBatch::Begin(SpriteSortMode sort_mode, XMMATRIX transform) {
		// This SpriteBatch may not already be in a begin/end pair.
		Assert(!m_in_begin_end_pair);

		m_sort_mode           = sort_mode;
		m_transform           = transform;

		if (m_sort_mode == SpriteSortMode_Immediate) {
			// Only one SpriteBatch at a time can use SpriteSortMode_Immediate.
			//Assert(!m_context_resources->inImmediateMode);
			
			//PrepareForRendering();

			//m_context_resources->inImmediateMode = true;
		}

		// Toggle the begin/end pair.
		m_in_begin_end_pair = true;

	}
	void SpriteBatch::Draw(ID3D11ShaderResourceView *texture, const SpriteTransform &transform, XMVECTOR color, SpriteEffects effects) {

	}
	void SpriteBatch::End() {
		// This SpriteBatch must already be in a begin/end pair.
		Assert(m_in_begin_end_pair);

		if (m_sort_mode == SpriteSortMode_Immediate) {
			// Queued sprites have already been drawn.
			//m_context_resources->inImmediateMode = false;
		}
		else {
			// Draw the queued sprites.
			//Assert(m_context_resources->inImmediateMode);

			//PrepareForRendering();
			//FlushBatch();
		}

		// Untoggle the begin/end pair.
		m_in_begin_end_pair = false;
	}




	void SpriteBatch::PrepareForRendering(ID3D11DeviceContext &device_context) {}
}