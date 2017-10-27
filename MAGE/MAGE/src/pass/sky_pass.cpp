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

	SkyPass *SkyPass::Get() {
		Assert(Renderer::Get());

		return Renderer::Get()->GetSkyPass();
	}

	SkyPass::SkyPass()
		: m_device_context(Pipeline::GetImmediateDeviceContext()),
		m_sky_vs(CreateSkyVS()), 
		m_sky_ps(CreateSkyPS()){}

	SkyPass::SkyPass(SkyPass &&render_pass) = default;

	SkyPass::~SkyPass() = default;

	void XM_CALLCONV SkyPass::BindTransformData(
		FXMMATRIX world_to_view,
		CXMMATRIX view_to_projection) {

		SkyBuffer buffer;
		buffer.m_world_to_view      = XMMatrixTranspose(world_to_view);
		buffer.m_view_to_projection = XMMatrixTranspose(view_to_projection);
		
		// Update the transform buffer.
		m_transform_buffer.UpdateData(m_device_context, 
			buffer);
		// Bind the transform buffer.
		m_transform_buffer.Bind< Pipeline::VS >(
			m_device_context, SLOT_CBUFFER_PER_FRAME);
	}

	void SkyPass::BindFixedState() const noexcept {
		// IA: Bind the primitive topology.
		Pipeline::IA::BindPrimitiveTopology(m_device_context,
			D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		// VS: Bind the vertex shader.
		m_sky_vs->BindShader(m_device_context);
		// HS: Bind the hull shader.
		Pipeline::HS::BindShader(m_device_context, nullptr);
		// DS: Bind the domain shader.
		Pipeline::DS::BindShader(m_device_context, nullptr);
		// GS: Bind the geometry shader.
		Pipeline::GS::BindShader(m_device_context, nullptr);
		// RS: Bind the rasterization state.
		RenderingStateManager::Get()->BindCullCounterClockwiseRasterizerState(m_device_context);
		// PS: Bind the pixel shader.
		m_sky_ps->BindShader(m_device_context);
		// OM: Bind the depth stencil state.
		RenderingStateManager::Get()->BindGreaterEqualDepthReadWriteDepthStencilState(m_device_context);
		// OM: Bind the blend state.
		RenderingStateManager::Get()->BindOpaqueBlendState(m_device_context);
	}

	void SkyPass::Render(
		const PassBuffer *scene,
		FXMMATRIX world_to_view,
		CXMMATRIX view_to_projection) {
		
		Assert(scene);

		// Bind the transform data.
		BindTransformData(world_to_view, view_to_projection);
		// Bind the sky SRV.
		Pipeline::PS::BindSRV(m_device_context, 
			SLOT_SRV_TEXTURE,
			scene->GetSky()->GetSRV());
		
		// Draw the icosphere.
		Pipeline::Draw(m_device_context, 240u, 0u);
	}
}