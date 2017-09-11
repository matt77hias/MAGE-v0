//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "pass\image_pass.hpp"
#include "rendering\rendering_state_cache.hpp"
#include "resource\resource_factory.hpp"
#include "core\engine_statistics.hpp"
#include "logging\error.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	ImagePass::ImagePass()
		: m_device_context(GetImmediateDeviceContext()),
		m_vs(CreateFullscreenTriangleVS()), 
		m_ps(CreateImagePS()),
		m_ms_ps(CreateMultiSampleImagePS()) {}

	ImagePass::ImagePass(ImagePass &&render_pass) = default;

	ImagePass::~ImagePass() = default;

	void ImagePass::Render(bool transfer_depth) {
		// Bind the vertex shader.
		m_vs->BindShader(m_device_context);
		
		if (transfer_depth) {
			// Bind the pixel shader.
			m_ms_ps->BindShader(m_device_context);
			// Bind the depth-stencil state.
			RenderingStateCache::Get()->BindDepthDefaultDepthStencilState(m_device_context);
		}
		else {
			// Bind the pixel shader.
			m_ps->BindShader(m_device_context);
			// Bind the depth-stencil state.
			RenderingStateCache::Get()->BindDepthNoneDepthStencilState(m_device_context);
		}

		// Bind the rasterization state.
		RenderingStateCache::Get()->BindCullCounterClockwiseRasterizerState(m_device_context);
		// Bind the blend state.
		RenderingStateCache::Get()->BindOpaqueBlendState(m_device_context);

		// Draw the fullscreen triangle.
		m_device_context->Draw(3u, 0u);
		EngineStatistics::Get()->IncrementNumberOfDrawCalls();
	}
}