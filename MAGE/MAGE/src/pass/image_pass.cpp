//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "scene\scene_renderer.hpp"
#include "rendering\rendering_state_cache.hpp"
#include "resource\resource_factory.hpp"
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
		: m_device_context(Pipeline::GetImmediateDeviceContext()),
		m_vs(CreateNearFullscreenTriangleVS()), 
		m_image_ps(CreateImagePS()),
		m_image_depth_ps(CreateImageDepthPS()) {}

	ImagePass::ImagePass(ImagePass &&render_pass) = default;

	ImagePass::~ImagePass() = default;

	void ImagePass::BindFixedState(bool transfer_depth) {
		// VS: Bind the vertex shader.
		m_vs->BindShader(m_device_context);
		// HS: Bind the hull shader.
		Pipeline::HS::BindShader(m_device_context, nullptr);
		// DS: Bind the domain shader.
		Pipeline::DS::BindShader(m_device_context, nullptr);
		// GS: Bind the geometry shader.
		Pipeline::GS::BindShader(m_device_context, nullptr);
		// RS: Bind the rasterization state.
		RenderingStateCache::Get()->BindCullCounterClockwiseRasterizerState(m_device_context);
		// OM: Bind the blend state.
		RenderingStateCache::Get()->BindOpaqueBlendState(m_device_context);

		if (transfer_depth) {
			// PS: Bind the pixel shader.
			m_image_depth_ps->BindShader(m_device_context);
			// OM: Bind the depth-stencil state.
			RenderingStateCache::Get()->BindDepthReadWriteDepthStencilState(m_device_context);
		}
		else {
			// PS: Bind the pixel shader.
			m_image_ps->BindShader(m_device_context);
			// OM: Bind the depth-stencil state.
			RenderingStateCache::Get()->BindDepthNoneDepthStencilState(m_device_context);
		}
	}

	void ImagePass::Render() const noexcept {
		
		// Bind the primitive topology.
		Pipeline::IA::BindPrimitiveTopology(m_device_context, 
			D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		
		// Draw the fullscreen triangle.
		Pipeline::Draw(m_device_context, 3u, 0u);
	}
}