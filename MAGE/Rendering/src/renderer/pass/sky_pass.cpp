//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "renderer\pass\sky_pass.hpp"
#include "resource\shader\shader_factory.hpp"

// Include HLSL bindings.
#include "hlsl.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage::rendering {

	SkyPass::SkyPass(ID3D11DeviceContext& device_context,
					 StateManager& state_manager,
					 ResourceManager& resource_manager)
		: m_device_context(device_context),
		m_state_manager(state_manager),
		m_vs(CreateSkyVS(resource_manager)),
		m_ps(CreateSkyPS(resource_manager)) {}

	SkyPass::SkyPass(SkyPass&& pass) noexcept = default;

	SkyPass::~SkyPass() = default;

	SkyPass& SkyPass::operator=(SkyPass&& pass) noexcept = default;

	void SkyPass::BindFixedState() const noexcept {
		// IA: Bind the primitive topology.
		Pipeline::IA::BindPrimitiveTopology(m_device_context, 
											D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		// VS: Bind the vertex shader.
		m_vs->BindShader(m_device_context);
		// HS: Bind the hull shader.
		Pipeline::HS::BindShader(m_device_context, nullptr);
		// DS: Bind the domain shader.
		Pipeline::DS::BindShader(m_device_context, nullptr);
		// GS: Bind the geometry shader.
		Pipeline::GS::BindShader(m_device_context, nullptr);
		// RS: Bind the rasterization state.
		m_state_manager.get().Bind(m_device_context, 
								   RasterizerStateID::CounterClockwiseCulling);
		// PS: Bind the pixel shader.
		m_ps->BindShader(m_device_context);
		// OM: Bind the depth stencil state.
		#ifdef DISABLE_INVERTED_Z_BUFFER
		m_state_manager.get().Bind(m_device_context, 
								   DepthStencilStateID::LessEqualDepthRead);
		#else  // DISABLE_INVERTED_Z_BUFFER
		m_state_manager.get().Bind(m_device_context, 
								   DepthStencilStateID::GreaterEqualDepthRead);
		#endif // DISABLE_INVERTED_Z_BUFFER
		// OM: Bind the blend state.
		m_state_manager.get().Bind(m_device_context, 
								   BlendStateID::Opaque);
	}

	void SkyPass::Render(const Sky& sky) const noexcept {
		// Bind the fixed state.
		BindFixedState();

		// Bind the SRV.
		Pipeline::PS::BindSRV(m_device_context, SLOT_SRV_TEXTURE, sky.GetSRV());
		
		// Draw the icosphere.
		Pipeline::Draw(m_device_context, 240u, 0u);
	}
}