//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "pass\sprite_pass.hpp"
#include "logging\error.hpp"

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
		
		Assert(scene);
		
		m_sprite_batch->Begin();

		for (const auto node : scene->m_sprites) {
			// Obtain node components.
			const Sprite * const sprite = node->GetSprite();

			// Draw the sprite.
			sprite->Draw(*m_sprite_batch);
		}

		m_sprite_batch->End();
	}
}