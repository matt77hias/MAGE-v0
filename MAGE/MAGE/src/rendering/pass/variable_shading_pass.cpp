//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "rendering\rendering_manager.hpp"
#include "resource\resource_factory.hpp"
#include "math\view_frustum.hpp"
#include "utils\logging\error.hpp"

// Include HLSL bindings.
#include "..\..\..\shaders\hlsl.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	VariableShadingPass *VariableShadingPass::Get() {
		Assert(Renderer::Get());

		return Renderer::Get()->GetVariableShadingPass();
	}

	VariableShadingPass::VariableShadingPass()
		: m_device_context(Pipeline::GetImmediateDeviceContext()),
		m_vs(CreateTransformVS()),
		m_ps{ 
			CreateForwardEmissivePS(false), 
			CreateForwardPS(BRDFType::Unknown, false, false), 
			CreateForwardPS(BRDFType::Unknown, true, false),
			CreateForwardEmissivePS(true),
			CreateForwardPS(BRDFType::Unknown, false, true),
			CreateForwardPS(BRDFType::Unknown, true, true),
		},
		m_bound_ps(PSIndex::Count), 
		m_brdf(BRDFType::Unknown),
		m_model_buffer() {}

	VariableShadingPass::VariableShadingPass(VariableShadingPass &&render_pass) = default;

	VariableShadingPass::~VariableShadingPass() = default;

	void VariableShadingPass::UpdatePSs(BRDFType brdf) {
		if (m_brdf != brdf) {
			m_brdf = brdf;
			m_ps[static_cast< size_t >(PSIndex::BRDF)] 
				= CreateForwardPS(brdf, false, false);
			m_ps[static_cast< size_t >(PSIndex::BRDF_TSNM)] 
				= CreateForwardPS(brdf, true, false);
			m_ps[static_cast< size_t >(PSIndex::Transparent_BRDF)] 
				= CreateForwardPS(brdf, false, true);
			m_ps[static_cast< size_t >(PSIndex::Transparent_BRDF_TSNM)] 
				= CreateForwardPS(brdf, true, true);
		}
	}

	void VariableShadingPass::BindPS(PSIndex index) noexcept {
		if (m_bound_ps != index) {
			m_ps[static_cast< size_t >(index)]->BindShader(m_device_context);
			m_bound_ps = index;
		}
	}

	void VariableShadingPass::BindPS(
		const Material *material, bool transparency) noexcept {
		
		if (transparency) {
			if (!material->InteractsWithLight()) {
				BindPS(PSIndex::Transparent_Emissive);
				return;
			}

			if (material->GetNormalSRV()) {
				BindPS(PSIndex::Transparent_BRDF_TSNM);
			}
			else {
				BindPS(PSIndex::Transparent_BRDF);
			}
		}
		else {
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
		buffer.m_base_color = RGBA(material->GetBaseColor());
		buffer.m_roughness  = material->GetRoughness();
		buffer.m_metalness  = material->GetMetalness();
		
		// Update the model buffer.
		m_model_buffer.UpdateData(m_device_context, 
			buffer);
		// Bind the model buffer.
		m_model_buffer.Bind< Pipeline::VS >(
			m_device_context, SLOT_CBUFFER_MODEL);
		m_model_buffer.Bind< Pipeline::PS >(
			m_device_context, SLOT_CBUFFER_MODEL);

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
	}

	void XM_CALLCONV VariableShadingPass::Render(
		const PassBuffer *scene,
		FXMMATRIX world_to_projection,
		CXMMATRIX world_to_view,
		CXMMATRIX view_to_world) {

		Assert(scene);

		// OM: Bind the depth-stencil state.
#ifdef DISSABLE_INVERTED_Z_BUFFER
		RenderingStateManager::Get()->BindLessEqualDepthReadWriteDepthStencilState(m_device_context);
#else  // DISSABLE_INVERTED_Z_BUFFER
		RenderingStateManager::Get()->BindGreaterEqualDepthReadWriteDepthStencilState(m_device_context);
#endif // DISSABLE_INVERTED_Z_BUFFER
		// OM: Bind the blend state.
		RenderingStateManager::Get()->BindOpaqueBlendState(m_device_context);
		
		// Process the models.
		ProcessModels(scene->GetOpaqueEmissiveModels(), 
			world_to_projection, world_to_view, view_to_world);
		ProcessModels(scene->GetTransparentEmissiveModels(),
			world_to_projection, world_to_view, view_to_world);
		ProcessModels(scene->GetOpaqueBRDFModels(), 
			world_to_projection, world_to_view, view_to_world);
		ProcessModels(scene->GetTransparentBRDFModels(),
			world_to_projection, world_to_view, view_to_world);
	}

	void XM_CALLCONV VariableShadingPass::RenderEmissive(
		const PassBuffer *scene,
		FXMMATRIX world_to_projection,
		CXMMATRIX world_to_view,
		CXMMATRIX view_to_world) {

		Assert(scene);

		// OM: Bind the depth-stencil state.
#ifdef DISSABLE_INVERTED_Z_BUFFER
		RenderingStateManager::Get()->BindLessEqualDepthReadWriteDepthStencilState(m_device_context);
#else  // DISSABLE_INVERTED_Z_BUFFER
		RenderingStateManager::Get()->BindGreaterEqualDepthReadWriteDepthStencilState(m_device_context);
#endif // DISSABLE_INVERTED_Z_BUFFER
		// OM: Bind the blend state.
		RenderingStateManager::Get()->BindOpaqueBlendState(m_device_context);
		
		// Process the emissive models.
		ProcessModels(scene->GetOpaqueEmissiveModels(),
			world_to_projection, world_to_view, view_to_world);
		ProcessModels(scene->GetTransparentEmissiveModels(),
			world_to_projection, world_to_view, view_to_world);
	}

	void XM_CALLCONV VariableShadingPass::RenderTransparent(
		const PassBuffer *scene,
		FXMMATRIX world_to_projection,
		CXMMATRIX world_to_view,
		CXMMATRIX view_to_world) {

		Assert(scene);

		// OM: Bind the depth-stencil state.
#ifdef DISSABLE_INVERTED_Z_BUFFER
		RenderingStateManager::Get()->BindLessDepthReadWriteDepthStencilState(m_device_context);
#else  // DISSABLE_INVERTED_Z_BUFFER
		RenderingStateManager::Get()->BindGreaterDepthReadWriteDepthStencilState(m_device_context);
#endif // DISSABLE_INVERTED_Z_BUFFER
		// OM: Bind the blend state.
		RenderingStateManager::Get()->BindTransparencyBlendState(m_device_context);

		// Process the transparent models.
		ProcessModels(scene->GetTransparentEmissiveModels(), 
			world_to_projection, world_to_view, view_to_world, true);
		ProcessModels(scene->GetTransparentBRDFModels(),
			world_to_projection, world_to_view, view_to_world, true);
	}

	void XM_CALLCONV VariableShadingPass::ProcessModels(
		const vector< const ModelNode * > &models,
		FXMMATRIX world_to_projection, 
		CXMMATRIX world_to_view, 
		CXMMATRIX view_to_world,
		bool transparency) {

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
			BindPS(material, transparency);
			// Bind the model mesh.
			model->BindMesh(m_device_context);
			// Draw the model.
			model->Draw(m_device_context);
		}
	}
}