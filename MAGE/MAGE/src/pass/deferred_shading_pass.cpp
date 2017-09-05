//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "pass\deferred_shading_pass.hpp"
#include "rendering\rendering_state_cache.hpp"
#include "resource\resource_factory.hpp"
#include "logging\error.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Defines
//-----------------------------------------------------------------------------
#pragma region

#define MAGE_DEFERRED_SHADING_PASS_PS_DEFERRED_BUFFER 1

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	DeferredShadingPass::DeferredShadingPass()
		: m_device_context(GetImmediateDeviceContext()),
		m_vs(CreateFullscreenTriangleVS()),
		m_ps(CreateDeferredPS(BRDFType::Unknown)),
		m_brdf(BRDFType::Unknown), m_deferred_buffer() {}

	DeferredShadingPass::DeferredShadingPass(DeferredShadingPass &&render_pass) = default;

	DeferredShadingPass::~DeferredShadingPass() = default;

	void DeferredShadingPass::UpdatePS(BRDFType brdf) {
		if (m_brdf != brdf) {
			m_brdf = brdf;
			m_ps   = CreateDeferredPS(brdf);
		}
	}

	void XM_CALLCONV DeferredShadingPass::BindUnpackData(
		FXMMATRIX view_to_projection, const PassBuffer *scene) noexcept {

		DeferredBuffer buffer;
		buffer.m_projection_values = GetProjectionValues(view_to_projection);
		buffer.m_mat1_start        = scene->m_material_coefficient_min[0];
		buffer.m_mat1_range        = scene->m_material_coefficient_max[0] - scene->m_material_coefficient_min[0];
		buffer.m_mat2_start        = scene->m_material_coefficient_min[1];
		buffer.m_mat2_range        = scene->m_material_coefficient_max[1] - scene->m_material_coefficient_min[1];

		m_deferred_buffer.UpdateData(m_device_context, buffer);
		PS::BindConstantBuffer(m_device_context,
			MAGE_DEFERRED_SHADING_PASS_PS_DEFERRED_BUFFER, m_deferred_buffer.Get());
	}

	void DeferredShadingPass::Render(const PassBuffer *scene, const CameraNode *node) {
		Assert(scene);
		Assert(node);

		// Update the pixel shader.
		UpdatePS(node->GetSettings()->GetBRDF());

		// Bind the vertex shader.
		m_vs->BindShader(m_device_context);
		// Bind the pixel shader.
		m_ps->BindShader(m_device_context);

		// Obtain node components.
		const Camera        * const camera = node->GetCamera();
		const XMMATRIX view_to_projection  = camera->GetViewToProjectionMatrix();

		// Bind the unpack data.
		BindUnpackData(view_to_projection, scene);

		// Bind the fullscreen triangle.
		IA::BindPrimitiveTopology(m_device_context, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
		// Draw the fullscreen triangle.
		m_device_context->Draw(3, 0);
	}
}