//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "renderer\pass\sprite_pass.hpp"
#include "resource\shader\shader_factory.hpp"

// Include HLSL bindings.
#include "hlsl.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage::rendering {

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

	SpritePass& SpritePass::operator=(SpritePass&& pass) noexcept = default;

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
		m_state_manager.get().Bind(m_device_context, 
								   RasterizerStateID::CounterClockwiseCulling);
		// PS: Bind the pixel shader.
		m_ps->BindShader(m_device_context);
		// OM: Bind the depth-stencil state.
		m_state_manager.get().Bind(m_device_context, 
								   DepthStencilStateID::DepthNone);
		// OM: Bind the blend state.
		m_state_manager.get().Bind(m_device_context, 
								   BlendStateID::Alpha);
	}

	void SpritePass::Render(const World& world) {
		// Bind the fixed state.
		BindFixedState();

		m_sprite_batch.Begin();

		// Processes the sprite images.
		world.ForEach< SpriteImage >([&sprite_batch(m_sprite_batch)]
		(const SpriteImage& sprite) {
			if (State::Active != sprite.GetState()) {
				return;
			}

			// Draw the sprite.
			sprite.Draw(sprite_batch);
		});

		// Processes the sprite texts.
		world.ForEach< SpriteText >([&sprite_batch(m_sprite_batch)]
		(const SpriteText& sprite) {
			if (State::Active != sprite.GetState()) {
				return;
			}

			// Draw the sprite.
			sprite.Draw(sprite_batch);
		});

		m_sprite_batch.End();
	}
}