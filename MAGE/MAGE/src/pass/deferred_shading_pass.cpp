//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "scene\scene_renderer.hpp"
#include "rendering\renderer.hpp"
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
		Assert(SceneRenderer::Get());

		return SceneRenderer::Get()->GetDeferredShadingPass();
	}

	DeferredShadingPass::DeferredShadingPass()
		: m_device_context(Pipeline::GetImmediateDeviceContext()),
		m_cs(CreateDeferredCS(BRDFType::Unknown)),
		m_brdf(BRDFType::Unknown), m_transform_buffer() {}

	DeferredShadingPass::DeferredShadingPass(
		DeferredShadingPass &&render_pass) = default;

	DeferredShadingPass::~DeferredShadingPass() = default;

	void DeferredShadingPass::UpdateCS(BRDFType brdf) {
		if (m_brdf != brdf) {
			m_brdf = brdf;
			m_cs   = CreateDeferredCS(brdf);
		}
	}

	void XM_CALLCONV DeferredShadingPass::BindUnpackData(
		FXMMATRIX view_to_projection) {

		// Update the transform buffer.
		m_transform_buffer.UpdateData(m_device_context, 
			GetViewPositionConstructionValues(view_to_projection));
		// Bind the deferred buffer.
		m_transform_buffer.Bind< Pipeline::CS >(
			m_device_context, SLOT_CBUFFER_PER_FRAME);
	}

	void DeferredShadingPass::BindFixedState(BRDFType brdf) {
		// Update the compute shader.
		UpdateCS(brdf);

		// Bind the compute shader.
		m_cs->BindShader(m_device_context);
	}

	void XM_CALLCONV DeferredShadingPass::Render(
		FXMMATRIX view_to_projection) {

		// Bind the unpack data.
		BindUnpackData(view_to_projection);

		// Dispatch.
		const Renderer * const renderer = Renderer::Get();
		const U32 nb_groups_x = static_cast< U32 >(ceil(renderer->GetWidth()
									/ static_cast< F32 >(GROUP_SIZE_DEFAULT)));
		const U32 nb_groups_y = static_cast< U32 >(ceil(renderer->GetHeight()
									/ static_cast< F32 >(GROUP_SIZE_DEFAULT)));
		m_device_context->Dispatch(nb_groups_x, nb_groups_y, 1u);
	}
}