//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "scene\scene_renderer.hpp"
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
		FXMMATRIX projection_to_view) {

		// Update the transform buffer.
		m_transform_buffer.UpdateData(m_device_context, 
			XMMatrixTranspose(projection_to_view));
		// Bind the deferred buffer.
		m_transform_buffer.Bind< Pipeline::CS >(
			m_device_context, SLOT_CBUFFER_PER_FRAME);
	}

	void DeferredShadingPass::BindFixedState(BRDFType brdf) {
		// Update the compute shader.
		UpdateCS(brdf);

		// CS: Bind the compute shader.
		m_cs->BindShader(m_device_context);
	}

	void XM_CALLCONV DeferredShadingPass::Render(
		FXMMATRIX projection_to_view) {

		// Bind the unpack data.
		BindUnpackData(projection_to_view);

		// Dispatch.
		const RenderingManager * const rendering_manager 
			= RenderingManager::Get();
		const U32 nb_groups_x 
			= static_cast< U32 >(ceil(rendering_manager->GetWidth()
				                      / static_cast< F32 >(GROUP_SIZE_DEFAULT)));
		const U32 nb_groups_y 
			= static_cast< U32 >(ceil(rendering_manager->GetHeight()
				                      / static_cast< F32 >(GROUP_SIZE_DEFAULT)));
		m_device_context->Dispatch(nb_groups_x, nb_groups_y, 1u);
	}
}