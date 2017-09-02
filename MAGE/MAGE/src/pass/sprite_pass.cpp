//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "pass\sprite_pass.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	SpritePass::SpritePass()
		: m_sprite_batch(MakeUnique< SpriteBatch >()) {}

	SpritePass::SpritePass(SpritePass &&render_pass) = default;

	SpritePass::~SpritePass() = default;

	void SpritePass::Render(const PassBuffer *scene) {
		m_sprite_batch->Begin();

		ProcessSprites(scene->m_opaque_sprites);
		ProcessSprites(scene->m_transparent_sprites);

		m_sprite_batch->End();
	}

	void SpritePass::RenderOpaque(const PassBuffer *scene) {
		m_sprite_batch->Begin();

		ProcessSprites(scene->m_opaque_sprites);

		m_sprite_batch->End();
	}

	void SpritePass::RenderTransparent(const PassBuffer *scene) {
		m_sprite_batch->Begin();

		ProcessSprites(scene->m_transparent_sprites);

		m_sprite_batch->End();
	}

	void SpritePass::ProcessSprites(
		const vector< const SpriteNode * > &sprites) noexcept {

		for (const auto node : sprites) {
			// Obtain node components.
			const Sprite * const sprite = node->GetSprite();

			// Draw the sprite.
			sprite->Draw(*m_sprite_batch);
		}
	}
}