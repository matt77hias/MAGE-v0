//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "rendering\rendering_manager.hpp"
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
		Assert(Renderer::Get());

		return Renderer::Get()->GetSpritePass();
	}

	SpritePass::SpritePass()
		: m_device_context(Pipeline::GetImmediateDeviceContext()),
		m_vs(CreateSpriteVS()), m_ps(CreateSpritePS()),
		m_sprite_batch(MakeUnique< SpriteBatch >()) {}

	SpritePass::SpritePass(SpritePass &&render_pass) = default;

	SpritePass::~SpritePass() = default;

	void SpritePass::BindFixedState() {
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