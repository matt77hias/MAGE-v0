//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "pass\deferred_shading_pass.hpp"
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

	DeferredShadingPass::DeferredShadingPass()
		: m_device_context(GetImmediateDeviceContext()),
		m_cs(CreateDeferredCS(BRDFType::Unknown)),
		m_brdf(BRDFType::Unknown), m_deferred_buffer() {}

	DeferredShadingPass::DeferredShadingPass(DeferredShadingPass &&render_pass) = default;

	DeferredShadingPass::~DeferredShadingPass() = default;

	void DeferredShadingPass::UpdateCS(BRDFType brdf) {
		if (m_brdf != brdf) {
			m_brdf = brdf;
			m_cs   = CreateDeferredCS(brdf);
		}
	}

	void XM_CALLCONV DeferredShadingPass::BindUnpackData(
		FXMMATRIX view_to_projection, const PassBuffer *scene) noexcept {

		DeferredComputeBuffer buffer;
		buffer.m_projection_values    = GetProjectionValues(view_to_projection);
		buffer.m_mat1_start           = scene->m_material_coefficient_min[0];
		buffer.m_mat1_range           = scene->m_material_coefficient_max[0] - scene->m_material_coefficient_min[0];
		buffer.m_mat2_start           = scene->m_material_coefficient_min[1];
		buffer.m_mat2_range           = scene->m_material_coefficient_max[1] - scene->m_material_coefficient_min[1];

		const Renderer * const renderer = Renderer::Get();
		buffer.m_resolution_minus1[0] = renderer->GetWidth()  - 1;
		buffer.m_resolution_minus1[1] = renderer->GetHeight() - 1;

		m_deferred_buffer.UpdateData(m_device_context, buffer);
		CS::BindConstantBuffer(m_device_context,
			SLOT_CBUFFER_PER_FRAME, m_deferred_buffer.Get());
	}

	void DeferredShadingPass::Render(const PassBuffer *scene, const CameraNode *node) {
		Assert(scene);
		Assert(node);

		// Update the compute shader.
		UpdateCS(node->GetSettings()->GetBRDF());

		// Bind the compute shader.
		m_cs->BindShader(m_device_context);

		// Obtain node components.
		const Camera        * const camera = node->GetCamera();
		const XMMATRIX view_to_projection  = camera->GetViewToProjectionMatrix();

		// Bind the unpack data.
		BindUnpackData(view_to_projection, scene);

		// Dispatch.
		const Renderer * const renderer = Renderer::Get();
		const UINT nb_groups_x = static_cast< UINT >(ceil(renderer->GetWidth()  
									/ static_cast< float >(GROUP_SIZE_DEFAULT)));
		const UINT nb_groups_y = static_cast< UINT >(ceil(renderer->GetHeight() 
									/ static_cast< float >(GROUP_SIZE_DEFAULT)));
		m_device_context->Dispatch(nb_groups_x, nb_groups_y, 1u);
	}
}