//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "scene\scene_renderer.hpp"
#include "rendering\rendering_state_cache.hpp"
#include "resource\resource_factory.hpp"
#include "logging\error.hpp"

// Include HLSL bindings.
#include "..\..\shaders\hlsl.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	SkyPass *SkyPass::Get() {
		Assert(SceneRenderer::Get());

		return SceneRenderer::Get()->GetSkyPass();
	}

	SkyPass::SkyPass()
		: m_device_context(Pipeline::GetImmediateDeviceContext()),
		m_sky_vs(CreateFarFullscreenTriangleVS()), 
		m_sky_ps(CreateSkyPS()){}

	SkyPass::SkyPass(SkyPass &&render_pass) = default;

	SkyPass::~SkyPass() = default;

	void XM_CALLCONV SkyPass::BindTransformData(
		FXMMATRIX view_to_world,
		CXMMATRIX view_to_projection) {

		SkyBuffer buffer;
		buffer.m_projection_values = GetViewPositionConstructionValues(view_to_projection);
		buffer.m_view_to_world     = XMMatrixTranspose(view_to_world);

		// Update the transform buffer.
		m_transform_buffer.UpdateData(m_device_context, buffer);
		// Bind the transform buffer.
		Pipeline::PS::BindConstantBuffer(m_device_context,
			SLOT_CBUFFER_PER_FRAME, m_transform_buffer.Get());
	}

	void SkyPass::BindFixedState() const noexcept {
		// Bind the vertex shader.
		m_sky_vs->BindShader(m_device_context);
		// Bind the pixel shader.
		m_sky_ps->BindShader(m_device_context);
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
		CXMMATRIX view_to_projection) {
		
		Assert(scene);

		// Bind the transform data.
		BindTransformData(view_to_world, view_to_projection);
		// Bind the sky SRV.
		Pipeline::PS::BindSRV(m_device_context, 
			SLOT_SRV_TEXTURE,
			scene->GetSky()->GetSRV());
		
		// Bind the primitive topology.
		Pipeline::IA::BindPrimitiveTopology(m_device_context,
			D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		// Draw the fullscreen triangle.
		Pipeline::Draw(m_device_context, 3u, 0u);
	}
}