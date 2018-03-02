//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "rendering\pass\sprite_pass.hpp"
#include "shader\shader_factory.hpp"

// Include HLSL bindings.
#include "hlsl.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	SpritePass::SpritePass(ID3D11Device& device,
						   ID3D11DeviceContext& device_context,
						   StateManager& state_manager,
						   ResourceManager& resource_manager)
		: m_device_context(device_context),
		m_state_manager(state_manager),
		m_vs(CreateSpriteVS(resource_manager)),
		m_ps(CreateSpritePS(resource_manager)),
		m_sprite_batch(device, device_context) {}

	SpritePass::SpritePass(SpritePass&& pass) noexcept = default;

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
		m_state_manager.get().BindCullCounterClockwiseRasterizerState(m_device_context);
		// PS: Bind the pixel shader.
		m_ps->BindShader(m_device_context);
		// OM: Bind the depth-stencil state.
		m_state_manager.get().BindDepthNoneDepthStencilState(m_device_context);
		// OM: Bind the blend state.
		m_state_manager.get().BindAlphaBlendState(m_device_context);
	}

	void SpritePass::Render(const Scene& scene) {
		// Bind the fixed state.
		BindFixedState();

		m_sprite_batch.Begin();

		// Processes the sprite images.
		scene.ForEach< SpriteImage >([&sprite_batch(m_sprite_batch)](const SpriteImage& sprite) {
			if (State::Active != sprite.GetState()) {
				return;
			}

			// Draw the sprite.
			sprite.Draw(sprite_batch);
		});

		// Processes the sprite texts.
		scene.ForEach< SpriteText >([&sprite_batch(m_sprite_batch)](const SpriteText& sprite) {
			if (State::Active != sprite.GetState()) {
				return;
			}

			// Draw the sprite.
			sprite.Draw(sprite_batch);
		});

		m_sprite_batch.End();
	}
}