//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "rendering\rendering_manager.hpp"
#include "resource\resource_factory.hpp"
#include "utils\logging\error.hpp"

// Include HLSL bindings.
#include "hlsl.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	SpritePass *SpritePass::Get() {
		Assert(Renderer::Get());

		return Renderer::Get()->GetSpritePass();
	}

	SpritePass::SpritePass()
		: m_device_context(Pipeline::GetImmediateDeviceContext()),
		m_vs(CreateSpriteVS()), 
		m_ps(CreateSpritePS()),
		m_sprite_batch(MakeUnique< SpriteBatch >()) {}

	SpritePass::SpritePass(SpritePass &&render_pass) noexcept = default;

	SpritePass::~SpritePass() = default;

	void SpritePass::BindFixedState() const noexcept {
		// VS: Bind the vertex shader.
		m_vs->BindShader(m_device_context);
		// HS: Bind the hull shader.
		Pipeline::HS::BindShader(m_device_context, nullptr);
		// DS: Bind the domain shader.
		Pipeline::DS::BindShader(m_device_context, nullptr);
		// GS: Bind the geometry shader.
		Pipeline::GS::BindShader(m_device_context, nullptr);
		// RS: Bind the rasterization state.
		RenderingStateManager::Get()->BindCullCounterClockwiseRasterizerState(m_device_context);
		// PS: Bind the pixel shader.
		m_ps->BindShader(m_device_context);
		// OM: Bind the depth-stencil state.
		RenderingStateManager::Get()->BindDepthNoneDepthStencilState(m_device_context);
		// OM: Bind the blend state.
		RenderingStateManager::Get()->BindAlphaBlendState(m_device_context);
	}

	void SpritePass::Render(const Scene &scene) const {
		m_sprite_batch->Begin();

		SpriteBatch &sprite_batch = *m_sprite_batch;

		// Processes the sprite images.
		scene.ForEach< SpriteImage >([&sprite_batch](const SpriteImage &sprite) {
			if (State::Active != sprite.GetState()) {
				return;
			}

			// Draw the sprite.
			sprite.Draw(sprite_batch);
		});

		// Processes the sprite texts.
		scene.ForEach< SpriteText >([&sprite_batch](const SpriteText &sprite) {
			if (State::Active != sprite.GetState()) {
				return;
			}

			// Draw the sprite.
			sprite.Draw(sprite_batch);
		});

		m_sprite_batch->End();
	}
}