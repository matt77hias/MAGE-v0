//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "scene\scene_renderer.hpp"
#include "rendering\rendering_state_manager.hpp"
#include "resource\resource_factory.hpp"
#include "logging\error.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	BackBufferPass *BackBufferPass::Get() {
		Assert(SceneRenderer::Get());

		return SceneRenderer::Get()->GetBackBufferPass();
	}

	BackBufferPass::BackBufferPass()
		: m_device_context(Pipeline::GetImmediateDeviceContext()),
		m_vs(CreateNearFullscreenTriangleVS()), 
		m_ps(CreateBackBufferPS()) {}

	BackBufferPass::BackBufferPass(BackBufferPass &&render_pass) = default;

	BackBufferPass::~BackBufferPass() = default;

	void BackBufferPass::BindFixedState() {
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
		RenderingStateManager::Get()->BindOpaqueBlendState(m_device_context);
	}

	void BackBufferPass::Render() const noexcept {
		
		// Bind the primitive topology.
		Pipeline::IA::BindPrimitiveTopology(m_device_context, 
			D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		
		// Draw the fullscreen triangle.
		Pipeline::Draw(m_device_context, 3u, 0u);
	}
}