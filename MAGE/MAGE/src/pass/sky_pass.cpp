//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "scene\scene_renderer.hpp"
#include "rendering\rendering_state_cache.hpp"
#include "resource\resource_factory.hpp"
#include "core\engine_statistics.hpp"
#include "logging\error.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	SkyPass *SkyPass::Get() {
		Assert(SceneRenderer::Get());

		return nullptr;// SceneRenderer::Get()->GetSkyPass();
	}

	SkyPass::SkyPass()
		: m_device_context(GetImmediateDeviceContext()),
		m_vs(CreateFullscreenTriangleVS()), 
		m_sky_ps(CreateSkyPS()){}

	SkyPass::SkyPass(SkyPass &&render_pass) = default;

	SkyPass::~SkyPass() = default;

	void SkyPass::BindFixedState() {
		// Bind the vertex shader.
		m_vs->BindShader(m_device_context);
		// Bind the pixel shader.
		m_ps->BindShader(m_device_context);
		// Bind the rasterization state.
		RenderingStateCache::Get()->BindCullCounterClockwiseRasterizerState(m_device_context);
		// Bind the depth stencil state.
		RenderingStateCache::Get()->BindDepthReadWriteDepthStencilState(m_device_context);
		// Bind the blend state.
		RenderingStateCache::Get()->BindOpaqueBlendState(m_device_context);
	}

	void SkyPass::Render(
		const PassBuffer *scene,
		FXMMATRIX view_to_world,
		CXMMATRIX view_to_projection) const noexcept {
		
		Assert(scene);
		
		// Bind the primitive topology.
		IA::BindPrimitiveTopology(m_device_context,
			D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		// Draw the fullscreen triangle.
		m_device_context->Draw(3u, 0u);
		EngineStatistics::Get()->IncrementNumberOfDrawCalls();
	}
}