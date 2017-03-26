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

	SpriteBatch::SpriteBatch()
		: m_in_begin_end_pair(false) {

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