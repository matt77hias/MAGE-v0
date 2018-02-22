//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "rendering\pass\sky_pass.hpp"
#include "rendering\rendering_state_manager.hpp"
#include "shader\shader_factory.hpp"

// Include HLSL bindings.
#include "hlsl.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	SkyPass::SkyPass()
		: m_device_context(Pipeline::GetImmediateDeviceContext()),
		m_vs(CreateSkyVS()), 
		m_ps(CreateSkyPS()){}

	SkyPass::SkyPass(SkyPass &&pass) noexcept = default;

	SkyPass::~SkyPass() = default;

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
		RenderingStateManager::Get()->BindCullCounterClockwiseRasterizerState(m_device_context);
		// PS: Bind the pixel shader.
		m_ps->BindShader(m_device_context);
		// OM: Bind the depth stencil state.
		#ifdef DISABLE_INVERTED_Z_BUFFER
		RenderingStateManager::Get()->BindLessEqualDepthReadDepthStencilState(m_device_context);
		#else  // DISABLE_INVERTED_Z_BUFFER
		RenderingStateManager::Get()->BindGreaterEqualDepthReadDepthStencilState(m_device_context);
		#endif // DISABLE_INVERTED_Z_BUFFER
		// OM: Bind the blend state.
		RenderingStateManager::Get()->BindOpaqueBlendState(m_device_context);
	}

	void SkyPass::Render(const Sky &sky) const noexcept {
		// Bind the fixed state.
		BindFixedState();

		// Bind the SRV.
		Pipeline::PS::BindSRV(m_device_context, SLOT_SRV_TEXTURE, sky.GetSRV());
		
		// Draw the icosphere.
		Pipeline::Draw(m_device_context, 240u, 0u);
	}
}