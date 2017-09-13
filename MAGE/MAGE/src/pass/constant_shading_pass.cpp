//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "scene\scene_renderer.hpp"
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

	ConstantShadingPass *ConstantShadingPass::Get() {
		Assert(SceneRenderer::Get());

		return SceneRenderer::Get()->GetConstantShadingPass();
	}

	ConstantShadingPass::ConstantShadingPass()
		: m_device_context(GetImmediateDeviceContext()),
		m_vs(CreateTransformVS()),
		m_ps(CreateLambertianPS()),
		m_projection_buffer(), m_model_buffer(),
		m_white(CreateWhiteTexture()) {}

	ConstantShadingPass::ConstantShadingPass(ConstantShadingPass &&render_pass) = default;

	ConstantShadingPass::~ConstantShadingPass() = default;

	void XM_CALLCONV ConstantShadingPass::BindProjectionData(
		FXMMATRIX view_to_projection) {
		
		// Update the projection buffer.
		m_projection_buffer.UpdateData(m_device_context, 
			XMMatrixTranspose(view_to_projection));
		// Bind the projection buffer.
		VS::BindConstantBuffer(m_device_context,
			SLOT_CBUFFER_PER_FRAME, m_projection_buffer.Get());
	}

	void XM_CALLCONV ConstantShadingPass::BindModelData(
		FXMMATRIX object_to_view, 
		CXMMATRIX view_to_object,
		CXMMATRIX texture_transform) {

		ModelBuffer buffer;
		buffer.m_object_to_view           = XMMatrixTranspose(object_to_view);
		buffer.m_normal_to_view           = view_to_object;
		buffer.m_texture_transform        = XMMatrixTranspose(texture_transform);
		buffer.m_Kd                       = RGBSpectrum(1.0f);
		buffer.m_dissolve                 = 1.0f;
		buffer.m_material_coefficients[0] = 1.0f;
		
		// Update the model buffer.
		m_model_buffer.UpdateData(m_device_context, 
			buffer);
		// Bind the model buffer.
		VS::BindConstantBuffer(m_device_context, 
			SLOT_CBUFFER_PER_DRAW, m_model_buffer.Get());
		PS::BindConstantBuffer(m_device_context, 
			SLOT_CBUFFER_PER_DRAW, m_model_buffer.Get());
	}

	void ConstantShadingPass::BindFixedState() {
		// Bind the vertex shader.
		m_vs->BindShader(m_device_context);
		// Bind the pixel shader.
		m_ps->BindShader(m_device_context);
		// Bind the diffuse SRV.
		PS::BindSRV(m_device_context,
			SLOT_SRV_DIFFUSE, m_white->Get());
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

	void XM_CALLCONV ConstantShadingPass::Render(
		const PassBuffer *scene,
		FXMMATRIX world_to_projection,
		CXMMATRIX world_to_view,
		CXMMATRIX view_to_world,
		CXMMATRIX view_to_projection) {

		Assert(scene);

		// Bind the projection data.
		BindProjectionData(view_to_projection);
		
		// Process the models.
		ProcessModels(scene->GetOpaqueEmissiveModels(), 
			world_to_projection, world_to_view, view_to_world);
		ProcessModels(scene->GetOpaqueBRDFModels(), 
			world_to_projection, world_to_view, view_to_world);
		ProcessModels(scene->GetTransparentEmissiveModels(), 
			world_to_projection, world_to_view, view_to_world);
		ProcessModels(scene->GetTransparentBRDFModels(), 
			world_to_projection, world_to_view, view_to_world);
	}

	void XM_CALLCONV ConstantShadingPass::ProcessModels(
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

			// Bind the model data.
			BindModelData(object_to_view, view_to_object, texture_transform);
			// Bind the model mesh.
			model->BindMesh(m_device_context);
			// Draw the model.
			model->Draw(m_device_context);
		}
	}
}