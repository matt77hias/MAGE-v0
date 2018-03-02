//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "rendering\pass\deferred_pass.hpp"
#include "shader\shader_factory.hpp"

// Include HLSL bindings.
#include "hlsl.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	DeferredPass::DeferredPass(ID3D11DeviceContext& device_context,
							   StateManager& state_manager,
							   ResourceManager& resource_manager)
		: m_device_context(device_context),
		m_state_manager(state_manager), 
		m_resource_manager(resource_manager),
		m_msaa_vs(CreateNearFullscreenTriangleVS(resource_manager)) {}

	DeferredPass::DeferredPass(DeferredPass&& pass) noexcept = default;

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
		m_state_manager.get().BindCullCounterClockwiseRasterizerState(m_device_context);
		// PS: Bind the pixel shader.
		m_msaa_ps->BindShader(m_device_context);
		// OM: Bind the depth-stencil state.
		m_state_manager.get().BindDepthNoneDepthStencilState(m_device_context);
		// OM: Bind the blend state.
		m_state_manager.get().BindOpaqueBlendState(m_device_context);
	}

	void DeferredPass::Render(BRDFType brdf, bool vct) {
		// Binds the fixed state.
		BindFixedState();

		const auto ps = CreateDeferredMSAAPS(m_resource_manager, brdf, vct);
		// PS: Bind the pixel shader.
		ps->BindShader(m_device_context);
		
		// Draw the fullscreen triangle.
		Pipeline::Draw(m_device_context, 3u, 0u);
	}

	void DeferredPass::Dispatch(const Viewport& viewport, 
								BRDFType brdf, bool vct) {
		
		const auto cs = CreateDeferredCS(m_resource_manager, brdf, vct);
		// CS: Bind the compute shader.
		cs->BindShader(m_device_context);
		
		// Dispatch the pass.
		const auto nb_groups_x = GetNumberOfGroups(viewport.GetWidth(),
												   GROUP_SIZE_2D_DEFAULT);
		const auto nb_groups_y = GetNumberOfGroups(viewport.GetHeight(),
												   GROUP_SIZE_2D_DEFAULT);
		Pipeline::Dispatch(m_device_context, nb_groups_x, nb_groups_y, 1u);
	}
}