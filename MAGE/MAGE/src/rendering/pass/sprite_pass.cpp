//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "rendering\pass\sprite_pass.hpp"
#include "rendering\state_manager.hpp"
#include "shader\shader_factory.hpp"

// Include HLSL bindings.
#include "hlsl.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	SpritePass::SpritePass()
		: m_device_context(Pipeline::GetImmediateDeviceContext()),
		m_vs(CreateSpriteVS()), 
		m_ps(CreateSpritePS()),
		m_sprite_batch(MakeUnique< SpriteBatch >()) {}

	SpritePass::SpritePass(SpritePass &&pass) noexcept = default;

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
		StateManager::Get()->BindCullCounterClockwiseRasterizerState(m_device_context);
		// PS: Bind the pixel shader.
		m_ps->BindShader(m_device_context);
		// OM: Bind the depth-stencil state.
		StateManager::Get()->BindDepthNoneDepthStencilState(m_device_context);
		// OM: Bind the blend state.
		StateManager::Get()->BindAlphaBlendState(m_device_context);
	}

	void SpritePass::Render(const Scene &scene) {
		// Bind the fixed state.
		BindFixedState();

		auto &sprite_batch = *m_sprite_batch;
		
		sprite_batch.Begin();

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

		sprite_batch.End();
	}
}