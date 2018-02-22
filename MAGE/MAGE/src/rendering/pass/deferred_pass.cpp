//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "rendering\rendering_manager.hpp"
#include "shader\shader_factory.hpp"
#include "logging\error.hpp"

// Include HLSL bindings.
#include "hlsl.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	DeferredPass *DeferredPass::Get() {
		Assert(Renderer::Get());

		return Renderer::Get()->GetDeferredPass();
	}

	DeferredPass::DeferredPass()
		: m_device_context(Pipeline::GetImmediateDeviceContext()),
		m_cs(CreateDeferredCS(BRDFType::Unknown, false)),
		m_msaa_vs(CreateNearFullscreenTriangleVS()),
		m_msaa_ps(CreateDeferredMSAAPS(BRDFType::Unknown, false)),
		m_brdf(BRDFType::Unknown), 
		m_vct(false) {}

	DeferredPass::DeferredPass(
		DeferredPass &&pass) noexcept = default;

	DeferredPass::~DeferredPass() = default;

	void DeferredPass::BindFixedState() const noexcept {
		// IA: Bind the primitive topology.
		Pipeline::IA::BindPrimitiveTopology(m_device_context,
											D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		// VS: Bind the vertex shader.
		m_msaa_vs->BindShader(m_device_context);
		// HS: Bind the hull shader.
		Pipeline::HS::BindShader(m_device_context, nullptr);
		// DS: Bind the domain shader.
		Pipeline::DS::BindShader(m_device_context, nullptr);
		// GS: Bind the geometry shader.
		Pipeline::GS::BindShader(m_device_context, nullptr);
		// RS: Bind the rasterization state.
		RenderingStateManager::Get()->BindCullCounterClockwiseRasterizerState(m_device_context);
		// PS: Bind the pixel shader.
		m_msaa_ps->BindShader(m_device_context);
		// OM: Bind the depth-stencil state.
		RenderingStateManager::Get()->BindDepthNoneDepthStencilState(m_device_context);
		// OM: Bind the blend state.
		RenderingStateManager::Get()->BindOpaqueBlendState(m_device_context);
	}

	void DeferredPass::UpdateShaders(BRDFType brdf, bool vct) {
		if (m_brdf != brdf || m_vct != vct) {
			m_brdf    = brdf;
			m_vct     = vct;
			m_cs      = CreateDeferredCS(brdf, m_vct);
			m_msaa_ps = CreateDeferredMSAAPS(brdf, m_vct);
		}
	}

	void DeferredPass::Render(BRDFType brdf, bool vct) {
		// Update the compute and pixel shader.
		UpdateShaders(brdf, vct);
		// Binds the fixed state.
		BindFixedState();
		
		// Draw the fullscreen triangle.
		Pipeline::Draw(m_device_context, 3u, 0u);
	}

	void DeferredPass::Dispatch(const Viewport &viewport, 
									   BRDFType brdf, bool vct) {
		// Update the compute and pixel shader.
		UpdateShaders(brdf, vct);
		// CS: Bind the compute shader.
		m_cs->BindShader(m_device_context);
		
		// Dispatch the pass.
		const auto nb_groups_x = GetNumberOfGroups(viewport.GetWidth(),
												   GROUP_SIZE_2D_DEFAULT);
		const auto nb_groups_y = GetNumberOfGroups(viewport.GetHeight(),
												   GROUP_SIZE_2D_DEFAULT);
		Pipeline::Dispatch(m_device_context, nb_groups_x, nb_groups_y, 1u);
	}
}