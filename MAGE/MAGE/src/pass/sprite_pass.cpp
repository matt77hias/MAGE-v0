//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "scene\scene_renderer.hpp"
#include "rendering\rendering_state_cache.hpp"
#include "resource\resource_factory.hpp"
#include "logging\error.hpp"

// Include HLSL bindings.
#include "..\..\shaders\hlsl.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	SpritePass *SpritePass::Get() {
		Assert(SceneRenderer::Get());

		return SceneRenderer::Get()->GetSpritePass();
	}

	SpritePass::SpritePass()
		: m_device_context(GetImmediateDeviceContext()),
		m_vs(CreateSpriteVS()), m_ps(CreateSpritePS()),
		m_sprite_batch(MakeUnique< SpriteBatch >()) {}

	SpritePass::SpritePass(SpritePass &&render_pass) = default;

	SpritePass::~SpritePass() = default;

	void SpritePass::BindFixedState() {
		// Bind the vertex shader.
		m_vs->BindShader(m_device_context);
		// Bind the pixel shader.
		m_ps->BindShader(m_device_context);
		// Bind the rasterization state.
		RenderingStateCache::Get()->BindCullCounterClockwiseRasterizerState(m_device_context);
		// Bind the depth-stencil state.
		RenderingStateCache::Get()->BindDepthNoneDepthStencilState(m_device_context);
		// Bind the blend state.
		RenderingStateCache::Get()->BindAlphaBlendState(m_device_context);
	}

	void SpritePass::Render(const PassBuffer *scene) {
		
		Assert(scene);
		
		m_sprite_batch->Begin();

		for (const auto node : scene->GetSprites()) {
			// Obtain node components.
			const Sprite * const sprite = node->GetSprite();

			// Draw the sprite.
			sprite->Draw(*m_sprite_batch);
		}

		m_sprite_batch->End();
	}
}