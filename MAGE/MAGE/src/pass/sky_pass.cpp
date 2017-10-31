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
#ifdef DISSABLE_INVERTED_Z_BUFFER
		RenderingStateManager::Get()->BindLessEqualDepthReadWriteDepthStencilState(m_device_context);
#else  // DISSABLE_INVERTED_Z_BUFFER
		RenderingStateManager::Get()->BindGreaterEqualDepthReadWriteDepthStencilState(m_device_context);
#endif // DISSABLE_INVERTED_Z_BUFFER
		// OM: Bind the blend state.
		RenderingStateManager::Get()->BindOpaqueBlendState(m_device_context);
	}

	void SkyPass::Render(const PassBuffer *scene) {
		
		Assert(scene);

		Pipeline::PS::BindSRV(m_device_context, 
			SLOT_SRV_TEXTURE,
			scene->GetSky()->GetSRV());
		
		// Draw the icosphere.
		Pipeline::Draw(m_device_context, 240u, 0u);
	}
}