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

	DeferredShadingPass *DeferredShadingPass::Get() {
		Assert(Renderer::Get());

		return Renderer::Get()->GetDeferredShadingPass();
	}

	DeferredShadingPass::DeferredShadingPass()
		: m_device_context(Pipeline::GetImmediateDeviceContext()),
		m_cs(CreateDeferredCS(BRDFType::Unknown)),
		m_brdf(BRDFType::Unknown) {}

	DeferredShadingPass::DeferredShadingPass(
		DeferredShadingPass &&render_pass) = default;

	DeferredShadingPass::~DeferredShadingPass() = default;

	void DeferredShadingPass::UpdateCS(BRDFType brdf) {
		if (m_brdf != brdf) {
			m_brdf = brdf;
			m_cs   = CreateDeferredCS(brdf);
		}
	}

	void DeferredShadingPass::BindFixedState(BRDFType brdf) {
		// Update the compute shader.
		UpdateCS(brdf);

		// CS: Bind the compute shader.
		m_cs->BindShader(m_device_context);
	}

	void DeferredShadingPass::Render(const Viewport &viewport) {

		// Dispatch.
		const U32 nb_groups_x 
			= static_cast< U32 >(ceil(viewport.GetWidth()
				                      / static_cast< F32 >(GROUP_SIZE_DEFAULT)));
		const U32 nb_groups_y 
			= static_cast< U32 >(ceil(viewport.GetHeight()
				                      / static_cast< F32 >(GROUP_SIZE_DEFAULT)));
		m_device_context->Dispatch(nb_groups_x, nb_groups_y, 1u);
	}
}