//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "renderer\pass\deferred_pass.hpp"
#include "resource\shader\shader_factory.hpp"

// Include HLSL bindings.
#include "hlsl.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage::rendering {

	DeferredPass::DeferredPass(ID3D11DeviceContext& device_context,
							   StateManager& state_manager,
							   ResourceManager& resource_manager)
		: m_device_context(device_context),
		m_state_manager(state_manager), 
		m_resource_manager(resource_manager),
		m_msaa_vs(CreateNearFullscreenTriangleVS(resource_manager)) {}

	DeferredPass::DeferredPass(DeferredPass&& pass) noexcept = default;

	DeferredPass::~DeferredPass() = default;

	DeferredPass& DeferredPass::operator=(DeferredPass&& pass) noexcept = default;

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
		m_state_manager.get().Bind(m_device_context, 
								   RasterizerStateID::CounterClockwiseCulling);
		// OM: Bind the depth-stencil state.
		m_state_manager.get().Bind(m_device_context, 
								   DepthStencilStateID::DepthNone);
		// OM: Bind the blend state.
		m_state_manager.get().Bind(m_device_context, 
								   BlendStateID::Opaque);
	}

	void DeferredPass::Render(BRDF brdf, bool vct) {
		// Binds the fixed state.
		BindFixedState();

		const auto ps = CreateDeferredMSAAPS(m_resource_manager, brdf, vct);
		// PS: Bind the pixel shader.
		ps->BindShader(m_device_context);
		
		// Draw the fullscreen triangle.
		Pipeline::Draw(m_device_context, 3u, 0u);
	}

	void DeferredPass::Dispatch(const U32x2& viewport_size,
								BRDF brdf, bool vct) {
		
		const auto cs = CreateDeferredCS(m_resource_manager, brdf, vct);
		// CS: Bind the compute shader.
		cs->BindShader(m_device_context);
		
		// Dispatch the pass.
		const auto nb_groups_x = GetNumberOfGroups(viewport_size.m_x,
												   GROUP_SIZE_2D_DEFAULT);
		const auto nb_groups_y = GetNumberOfGroups(viewport_size.m_y,
												   GROUP_SIZE_2D_DEFAULT);
		Pipeline::Dispatch(m_device_context, nb_groups_x, nb_groups_y, 1u);
	}
}