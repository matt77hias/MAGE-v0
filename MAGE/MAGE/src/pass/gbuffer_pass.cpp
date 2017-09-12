//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "pass\gbuffer_pass.hpp"
#include "rendering\rendering_state_cache.hpp"
#include "resource\resource_factory.hpp"
#include "math\view_frustum.hpp"
#include "logging\error.hpp"

// Include HLSL bindings.
#include "..\..\shaders\hlsl.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	GBufferPass::GBufferPass()
		: m_device_context(GetImmediateDeviceContext()),
		m_vs(CreateTransformVS()),
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
		FXMMATRIX view_to_projection) {

		m_projection_buffer.UpdateData(
			m_device_context, XMMatrixTranspose(view_to_projection));
		VS::BindConstantBuffer(m_device_context,
			SLOT_CBUFFER_PER_FRAME, m_projection_buffer.Get());
	}

	void XM_CALLCONV GBufferPass::BindModelData(
		FXMMATRIX object_to_view, 
		CXMMATRIX view_to_object,
		CXMMATRIX texture_transform,
		const Material *material) {

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
			SLOT_CBUFFER_PER_DRAW, m_model_buffer.Get());
		PS::BindConstantBuffer(m_device_context, 
			SLOT_CBUFFER_PER_DRAW, m_model_buffer.Get());

		// Bind the diffuse SRV.
		PS::BindSRV(m_device_context, 
			SLOT_SRV_DIFFUSE, material->GetDiffuseReflectivitySRV());
		// Bind the specular SRV.
		PS::BindSRV(m_device_context, 
			SLOT_SRV_SPECULAR, material->GetSpecularReflectivitySRV());
		// Bind the normal SRV.
		PS::BindSRV(m_device_context, 
			SLOT_SRV_NORMAL, material->GetNormalSRV());
	}

	void GBufferPass::BindFixedState() {
		// Reset the bound pixel shader index.
		m_bound_ps = PSIndex::Count;

		// Bind the vertex shader.
		m_vs->BindShader(m_device_context);
		// Bind the rasterization state.
		RenderingStateCache::Get()->BindCullCounterClockwiseRasterizerState(m_device_context);
		// Bind the depth-stencil state.
		RenderingStateCache::Get()->BindDepthDefaultDepthStencilState(m_device_context);
		// Bind the blend state.
		RenderingStateCache::Get()->BindOpaqueBlendState(m_device_context);
		// Bind the sampler.
		PS::BindSampler(m_device_context, SLOT_SAMPLER_DEFAULT,
			RenderingStateCache::Get()->GetLinearWrapSamplerState());
	}

	void XM_CALLCONV GBufferPass::Render(
		const PassBuffer *scene,
		FXMMATRIX world_to_projection,
		CXMMATRIX world_to_view,
		CXMMATRIX view_to_world,
		CXMMATRIX view_to_projection) {

		Assert(scene);

		// Update the material coefficient data.
		UpdateMaterialCoefficientData(scene);

		// Bind the projection data.
		BindProjectionData(view_to_projection);
		
		// Process the models.
		ProcessModels(scene->m_opaque_brdf_models, world_to_projection, world_to_view, view_to_world);
	}

	void XM_CALLCONV GBufferPass::ProcessModels(
		const vector< const ModelNode * > &models,
		FXMMATRIX world_to_projection, 
		CXMMATRIX world_to_view, 
		CXMMATRIX view_to_world) {

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