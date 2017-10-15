//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "scene\scene_renderer.hpp"
#include "rendering\rendering_state_manager.hpp"
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

	VariableShadingPass *VariableShadingPass::Get() {
		Assert(SceneRenderer::Get());

		return SceneRenderer::Get()->GetVariableShadingPass();
	}

	VariableShadingPass::VariableShadingPass()
		: m_device_context(Pipeline::GetImmediateDeviceContext()),
		m_vs(CreateTransformVS()),
		m_ps{ CreateEmissivePS(), CreatePS(BRDFType::Unknown), CreateTSNMPS(BRDFType::Unknown) },
		m_bound_ps(PSIndex::Count), m_brdf(BRDFType::Unknown),
		m_projection_buffer(), m_model_buffer() {}

	VariableShadingPass::VariableShadingPass(VariableShadingPass &&render_pass) = default;

	VariableShadingPass::~VariableShadingPass() = default;

	void VariableShadingPass::UpdatePSs(BRDFType brdf) {
		if (m_brdf != brdf) {
			m_brdf = brdf;
			m_ps[static_cast< size_t >(PSIndex::BRDF)]      = CreatePS(brdf);
			m_ps[static_cast< size_t >(PSIndex::BRDF_TSNM)] = CreateTSNMPS(brdf);
		}
	}

	void VariableShadingPass::BindPS(PSIndex index) noexcept {
		if (m_bound_ps != index) {
			m_ps[static_cast< size_t >(index)]->BindShader(m_device_context);
			m_bound_ps = index;
		}
	}

	void VariableShadingPass::BindPS(const Material *material) noexcept {
		
		if (!material->InteractsWithLight()) {
			BindPS(PSIndex::Emissive);
			return;
		}

		if (material->GetNormalSRV()) {
			BindPS(PSIndex::BRDF_TSNM);
		}
		else {
			BindPS(PSIndex::BRDF);
		}
	}

	void XM_CALLCONV VariableShadingPass::BindProjectionData(
		FXMMATRIX view_to_projection) {

		// Update the projection buffer.
		m_projection_buffer.UpdateData(m_device_context, 
			XMMatrixTranspose(view_to_projection));
		// Bind the projection buffer.
		m_projection_buffer.Bind< Pipeline::VS >(
			m_device_context, SLOT_CBUFFER_PER_FRAME);
	}

	void XM_CALLCONV VariableShadingPass::BindModelData(
		FXMMATRIX object_to_view, 
		CXMMATRIX view_to_object,
		CXMMATRIX texture_transform,
		const Material *material) {

		ModelBuffer buffer;
		// Transforms
		buffer.m_transform.m_object_to_view    = XMMatrixTranspose(object_to_view);
		buffer.m_transform.m_normal_to_view    = view_to_object;
		buffer.m_transform.m_texture_transform = XMMatrixTranspose(texture_transform);
		// Material
		buffer.m_base_color = material->GetBaseColorRGBA();
		buffer.m_roughness  = material->GetRoughness();
		buffer.m_metalness  = material->GetMetalness();
		
		// Update the model buffer.
		m_model_buffer.UpdateData(m_device_context, 
			buffer);
		// Bind the model buffer.
		m_model_buffer.Bind< Pipeline::VS >(
			m_device_context, SLOT_CBUFFER_PER_DRAW);
		m_model_buffer.Bind< Pipeline::PS >(
			m_device_context, SLOT_CBUFFER_PER_DRAW);

		// Bind the base color SRV.
		Pipeline::PS::BindSRV(m_device_context,
			SLOT_SRV_BASE_COLOR, material->GetBaseColorSRV());
		// Bind the material SRV.
		Pipeline::PS::BindSRV(m_device_context,
			SLOT_SRV_MATERIAL, material->GetMaterialSRV());
		// Bind the normal SRV.
		Pipeline::PS::BindSRV(m_device_context,
			SLOT_SRV_NORMAL, material->GetNormalSRV());
	}

	void VariableShadingPass::BindFixedState(BRDFType brdf) {
		// Reset the bound pixel shader index.
		m_bound_ps = PSIndex::Count;
		// Update the pixel shaders.
		UpdatePSs(brdf);

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
		// OM: Bind the depth-stencil state.
		RenderingStateManager::Get()->BindLessEqualDepthReadWriteDepthStencilState(m_device_context);
	}

	void XM_CALLCONV VariableShadingPass::RenderOpaque(
		const PassBuffer *scene,
		FXMMATRIX world_to_projection,
		CXMMATRIX world_to_view,
		CXMMATRIX view_to_world,
		CXMMATRIX view_to_projection) {

		Assert(scene);

		// Bind the projection data.
		BindProjectionData(view_to_projection);

		// Bind the blend state.
		RenderingStateManager::Get()->BindOpaqueBlendState(m_device_context);
		
		// Process the opaque models.
		ProcessModels(scene->GetOpaqueEmissiveModels(), 
			world_to_projection, world_to_view, view_to_world);
		ProcessModels(scene->GetOpaqueBRDFModels(), 
			world_to_projection, world_to_view, view_to_world);
	}

	void XM_CALLCONV VariableShadingPass::RenderOpaqueEmissive(
		const PassBuffer *scene,
		FXMMATRIX world_to_projection,
		CXMMATRIX world_to_view,
		CXMMATRIX view_to_world,
		CXMMATRIX view_to_projection) {

		Assert(scene);

		// Bind the projection data.
		BindProjectionData(view_to_projection);

		// Bind the blend state.
		RenderingStateManager::Get()->BindOpaqueBlendState(m_device_context);
		
		// Process the opaque models.
		ProcessModels(scene->GetOpaqueEmissiveModels(), 
			world_to_projection, world_to_view, view_to_world);
	}

	void XM_CALLCONV VariableShadingPass::RenderTransparent(
		const PassBuffer *scene,
		FXMMATRIX world_to_projection,
		CXMMATRIX world_to_view,
		CXMMATRIX view_to_world,
		CXMMATRIX view_to_projection) {

		Assert(scene);

		// Bind the projection data.
		BindProjectionData(view_to_projection);

		// Bind the blend state.
		RenderingStateManager::Get()->BindAlphaBlendState(m_device_context);

		// Process the transparent models.
		ProcessModels(scene->GetTransparentEmissiveModels(), 
			world_to_projection, world_to_view, view_to_world);
		ProcessModels(scene->GetTransparentBRDFModels(),
			world_to_projection, world_to_view, view_to_world);
	}

	void XM_CALLCONV VariableShadingPass::ProcessModels(
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