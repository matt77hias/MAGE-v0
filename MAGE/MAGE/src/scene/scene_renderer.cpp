//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "scene\scene_renderer.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	SceneRenderer::SceneRenderer()
		: m_render_pass(MakeUnique< BasicRenderPass >()),
		  m_sprite_batch(MakeUnique< SpriteBatch >()) {}
	
	SceneRenderer::SceneRenderer(SceneRenderer &&scene_renderer) = default;
	
	SceneRenderer::~SceneRenderer() = default;

	void SceneRenderer::Render(const Scene *scene) {
		PassBuffer buffer(scene);
		m_render_pass->Render(&buffer);
		
		m_sprite_batch->Begin();

		for (const auto node : buffer.m_sprites) {
			const Sprite * const sprite = node->GetSprite();
			sprite->Draw(*m_sprite_batch);
		}

		m_sprite_batch->End();
	}
}