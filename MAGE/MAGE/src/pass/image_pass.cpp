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

	ImagePass *ImagePass::Get() {
		Assert(SceneRenderer::Get());

		return SceneRenderer::Get()->GetImagePass();
	}

	ImagePass::ImagePass()
		: m_device_context(GetImmediateDeviceContext()),
		m_vs(CreateFullscreenTriangleVS()), 
		m_image_ps(CreateImagePS()),
		m_image_depth_ps(CreateImageDepthPS()) {}

	ImagePass::ImagePass(ImagePass &&render_pass) = default;

	ImagePass::~ImagePass() = default;

	void ImagePass::BindFixedState(bool transfer_depth) {
		// Bind the vertex shader.
		m_vs->BindShader(m_device_context);

		if (transfer_depth) {
			// Bind the pixel shader.
			m_image_depth_ps->BindShader(m_device_context);
			// Bind the depth-stencil state.
			RenderingStateCache::Get()->BindDepthReadWriteDepthStencilState(m_device_context);
		}
		else {
			// Bind the pixel shader.
			m_image_ps->BindShader(m_device_context);
			// Bind the depth-stencil state.
			RenderingStateCache::Get()->BindDepthNoneDepthStencilState(m_device_context);
		}

		// Bind the rasterization state.
		RenderingStateCache::Get()->BindCullCounterClockwiseRasterizerState(m_device_context);
		// Bind the blend state.
		RenderingStateCache::Get()->BindOpaqueBlendState(m_device_context);
	}

	void ImagePass::Render() const noexcept {
		// Draw the fullscreen triangle.
		m_device_context->Draw(3u, 0u);
		EngineStatistics::Get()->IncrementNumberOfDrawCalls();
	}
}