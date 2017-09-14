//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "scene\scene_renderer.hpp"
#include "rendering\renderer.hpp"
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

	VariableShadingPass *VariableShadingPass::Get() {
		Assert(SceneRenderer::Get());

		return SceneRenderer::Get()->GetVariableShadingPass();
	}

	VariableShadingPass::VariableShadingPass()
		: m_device_context(GetImmediateDeviceContext()),
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
		VS::BindConstantBuffer(m_device_context,
			SLOT_CBUFFER_PER_FRAME, m_projection_buffer.Get());
	}

	void XM_CALLCONV VariableShadingPass::BindModelData(
		FXMMATRIX object_to_view, 
		CXMMATRIX view_to_object,
		CXMMATRIX texture_transform,
		const Material *material) {

		ForwardModelBuffer buffer;
		// Transforms
		buffer.m_transform.m_object_to_view    = XMMatrixTranspose(object_to_view);
		buffer.m_transform.m_normal_to_view    = view_to_object;
		buffer.m_transform.m_texture_transform = XMMatrixTranspose(texture_transform);
		// Material
		buffer.m_Kd                       = material->GetDiffuseReflectivity();
		buffer.m_dissolve                 = material->GetDissolve();
		buffer.m_Ks                       = material->GetSpecularReflectivity();
		buffer.m_material_coefficients[0] = material->GetMaterialParameter(0u);
		buffer.m_material_coefficients[1] = material->GetMaterialParameter(1u);
		
		// Update the model buffer.
		m_model_buffer.UpdateData(m_device_context, 
			buffer);
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

	void VariableShadingPass::BindFixedState(BRDFType brdf) {
		// Reset the bound pixel shader index.
		m_bound_ps = PSIndex::Count;
		// Update the pixel shaders.
		UpdatePSs(brdf);

		// Bind the vertex shader.
		m_vs->BindShader(m_device_context);
		// Bind the rasterization state.
		RenderingStateCache::Get()->BindCullCounterClockwiseRasterizerState(m_device_context);
		// Bind the depth-stencil state.
		RenderingStateCache::Get()->BindDepthDefaultDepthStencilState(m_device_context);
		// Bind the sampler.
		PS::BindSampler(m_device_context, SLOT_SAMPLER_DEFAULT,
			RenderingStateCache::Get()->GetLinearWrapSamplerState());
	}

	void XM_CALLCONV VariableShadingPass::Render(
		const PassBuffer *scene,
		FXMMATRIX world_to_projection,
		CXMMATRIX world_to_view,
		CXMMATRIX view_to_world,
		CXMMATRIX view_to_projection) {

		Assert(scene);

		// Bind the projection data.
		BindProjectionData(view_to_projection);

		// Bind the blend state.
		RenderingStateCache::Get()->BindOpaqueBlendState(m_device_context);
		
		// Process the opaque models.
		ProcessModels(scene->GetOpaqueEmissiveModels(), 
			world_to_projection, world_to_view, view_to_world);
		ProcessModels(scene->GetOpaqueBRDFModels(), 
			world_to_projection, world_to_view, view_to_world);
		
		// Bind the blend state.
		if (Renderer::Get()->HasMSAA()) {
			RenderingStateCache::Get()->BindAlphaToCoverageBlendState(m_device_context);
		}
		else {
			RenderingStateCache::Get()->BindAlphaBlendState(m_device_context);
		}

		// Process the transparent models.
		ProcessModels(scene->GetTransparentEmissiveModels(), 
			world_to_projection, world_to_view, view_to_world);
		ProcessModels(scene->GetTransparentBRDFModels(),
			world_to_projection, world_to_view, view_to_world);
	}

	void XM_CALLCONV VariableShadingPass::RenderPostDeferred(
		const PassBuffer *scene,
		FXMMATRIX world_to_projection,
		CXMMATRIX world_to_view,
		CXMMATRIX view_to_world,
		CXMMATRIX view_to_projection) {

		Assert(scene);

		// Bind the projection data.
		BindProjectionData(view_to_projection);

		// Bind the blend state.
		RenderingStateCache::Get()->BindOpaqueBlendState(m_device_context);
		
		// Process the opaque models.
		ProcessModels(scene->GetOpaqueEmissiveModels(), 
			world_to_projection, world_to_view, view_to_world);
		
		// Bind the blend state.
		if (Renderer::Get()->HasMSAA()) {
			RenderingStateCache::Get()->BindAlphaToCoverageBlendState(m_device_context);
		}
		else {
			RenderingStateCache::Get()->BindAlphaBlendState(m_device_context);
		}

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