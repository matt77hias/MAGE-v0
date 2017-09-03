//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "pass\gbuffer_pass.hpp"
#include "rendering\renderer.hpp"
#include "rendering\rendering_state_cache.hpp"
#include "resource\resource_factory.hpp"
#include "math\view_frustum.hpp"
#include "logging\error.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Defines
//-----------------------------------------------------------------------------
#pragma region

#define MAGE_GBUFFER_PASS_VS_PROJECTION_BUFFER 1
#define MAGE_GBUFFER_PASS_VS_MODEL_BUFFER      2
#define MAGE_GBUFFER_PASS_PS_MODEL_BUFFER      2
#define MAGE_GBUFFER_PASS_PS_DIFFUSE_SRV       0
#define MAGE_GBUFFER_PASS_PS_SPECULAR_SRV      1
#define MAGE_GBUFFER_PASS_PS_NORMAL_SRV        2
#define MAGE_GBUFFER_PASS_PS_SAMPLER           0

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	GBufferPass::GBufferPass()
		: m_device_context(GetImmediateDeviceContext()),
		m_vs(CreateGBufferVS()),
		m_ps{ CreateGBufferPS(), CreateGBufferTSNMPS() },
		m_bound_ps(PSIndex::Count),
		m_model_buffer(), m_projection_buffer(),
		m_material_coefficient_min{}, 
		m_material_coefficient_range{} {}


	GBufferPass::GBufferPass(GBufferPass &&render_pass) = default;

	GBufferPass::~GBufferPass() = default;

	void GBufferPass::UpdateMaterialCoefficientData(
		const PassBuffer *scene) noexcept {

		for (uint8_t i = 0; i < _countof(m_material_coefficient_min); ++i) {
			m_material_coefficient_min[i]   = scene->m_material_coefficient_min[i];
			m_material_coefficient_range[i] = scene->m_material_coefficient_max[i] - scene->m_material_coefficient_min[i];
		}
	}
	
	float GBufferPass::NormalizeMaterialCoefficient(
		uint8_t index, const Material *material) const noexcept {

		Assert(index < _countof(m_material_coefficient_min));

		return (material->GetMaterialParameter(index) 
				- m_material_coefficient_min[index])
				/ m_material_coefficient_range[index];
	}

	void GBufferPass::BindPS(PSIndex index) noexcept {
		if (m_bound_ps != index) {
			m_ps[static_cast< size_t >(index)]->BindShader(m_device_context);
			m_bound_ps = index;
		}
	}

	void GBufferPass::BindPS(const Material *material) noexcept {
		if (material->GetNormalSRV()) {
			BindPS(PSIndex::TSNM);
		}
		else {
			BindPS(PSIndex::Default);
		}
	}

	void XM_CALLCONV GBufferPass::BindProjectionData(
		FXMMATRIX view_to_projection) noexcept {

		m_projection_buffer.UpdateData(
			m_device_context, XMMatrixTranspose(view_to_projection));
		VS::BindConstantBuffer(m_device_context,
			MAGE_GBUFFER_PASS_VS_PROJECTION_BUFFER, m_projection_buffer.Get());
	}

	void XM_CALLCONV GBufferPass::BindModelData(
		FXMMATRIX object_to_view, 
		FXMMATRIX view_to_object,
		FXMMATRIX texture_transform,
		const Material *material) noexcept {

		DeferredModelBuffer buffer;
		buffer.m_object_to_view           = XMMatrixTranspose(object_to_view);
		buffer.m_normal_to_view           = view_to_object;
		buffer.m_texture_transform        = XMMatrixTranspose(texture_transform);
		buffer.m_Kd                       = material->GetDiffuseReflectivity();
		buffer.m_Ks                       = material->GetSpecularReflectivity();
		buffer.m_mat1_norm                = NormalizeMaterialCoefficient(0u, material);
		buffer.m_mat2_norm                = NormalizeMaterialCoefficient(1u, material);
		
		// Update the model buffer.
		m_model_buffer.UpdateData(m_device_context, buffer);
		// Bind the model buffer.
		VS::BindConstantBuffer(m_device_context, 
			MAGE_GBUFFER_PASS_VS_MODEL_BUFFER, m_model_buffer.Get());
		PS::BindConstantBuffer(m_device_context, 
			MAGE_GBUFFER_PASS_PS_MODEL_BUFFER, m_model_buffer.Get());

		// Bind the diffuse SRV.
		PS::BindSRV(m_device_context, 
			MAGE_GBUFFER_PASS_PS_DIFFUSE_SRV, material->GetDiffuseReflectivitySRV());
		// Bind the specular SRV.
		PS::BindSRV(m_device_context, 
			MAGE_GBUFFER_PASS_PS_SPECULAR_SRV, material->GetSpecularReflectivitySRV());
		// Bind the normal SRV.
		PS::BindSRV(m_device_context, 
			MAGE_GBUFFER_PASS_PS_NORMAL_SRV, material->GetNormalSRV());
	}

	void GBufferPass::Render(const PassBuffer *scene, const CameraNode *node) {
		Assert(scene);
		Assert(node);

		// Reset the bound pixel shader index.
		m_bound_ps = PSIndex::Count;
		// Update the material coefficient data.
		UpdateMaterialCoefficientData(scene);

		// Bind the vertex shader.
		m_vs->BindShader(m_device_context);
		// Bind the rasterization state.
		RenderingStateCache::Get()->BindCullCounterClockwiseRasterizerState(m_device_context);
		// Bind the depth-stencil state.
		RenderingStateCache::Get()->BindDepthDefaultDepthStencilState(m_device_context);
		// Bind the blend state.
		RenderingStateCache::Get()->BindOpaqueBlendState(m_device_context);
		// Bind the sampler.
		PS::BindSampler(m_device_context, MAGE_GBUFFER_PASS_PS_SAMPLER,
			RenderingStateCache::Get()->GetLinearWrapSamplerState());

		// Obtain node components.
		const TransformNode * const transform = node->GetTransform();
		const Camera        * const camera    = node->GetCamera();
		const XMMATRIX world_to_view          = transform->GetWorldToViewMatrix();
		const XMMATRIX view_to_world          = transform->GetViewToWorldMatrix();
		const XMMATRIX view_to_projection     = camera->GetViewToProjectionMatrix();
		const XMMATRIX world_to_projection    = world_to_view * view_to_projection;

		// Bind the projection data.
		BindProjectionData(view_to_projection);
		
		ProcessModels(scene->m_opaque_brdf_models, world_to_projection, world_to_view, view_to_world);
	}

	void XM_CALLCONV GBufferPass::ProcessModels(
		const vector< const ModelNode * > &models,
		FXMMATRIX world_to_projection, 
		FXMMATRIX world_to_view, 
		FXMMATRIX view_to_world) noexcept {

		for (const auto node : models) {
			
			// Obtain node components (1/2).
			const TransformNode * const transform = node->GetTransform();
			const Model         * const model     = node->GetModel();
			const XMMATRIX object_to_world        = transform->GetObjectToWorldMatrix();
			const XMMATRIX object_to_projection   = object_to_world * world_to_projection;

			// Cull the model against the view frustum.
			if (ViewFrustum::Cull(object_to_projection, model->GetAABB())) {
				continue;
			}

			// Obtain node components (2/2).
			const XMMATRIX object_to_view         = object_to_world * world_to_view;
			const XMMATRIX world_to_object        = transform->GetWorldToObjectMatrix();
			const XMMATRIX view_to_object         = view_to_world * world_to_object;
			const XMMATRIX texture_transform      = node->GetTextureTransform()->GetTransformMatrix();
			const Material * const material       = model->GetMaterial();

			// Bind the model data.
			BindModelData(object_to_view, view_to_object, texture_transform, material);
			// Bind the pixel shader.
			BindPS(material);
			// Bind the model mesh.
			model->BindMesh(m_device_context);
			// Draw the model.
			model->Draw(m_device_context);
		}
	}
}