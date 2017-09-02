//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "pass\constant_shading_pass.hpp"
#include "rendering\rendering_state_cache.hpp"
#include "resource\resource_factory.hpp"
#include "math\view_frustum.hpp"
#include "logging\error.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Defines
//-----------------------------------------------------------------------------
#pragma region

#define MAGE_CONSTANT_SHADING_PASS_VS_PROJECTION_BUFFER 1
#define MAGE_CONSTANT_SHADING_PASS_VS_MODEL_BUFFER      2
#define MAGE_CONSTANT_SHADING_PASS_PS_MODEL_BUFFER      2
#define MAGE_CONSTANT_SHADING_PASS_PS_DIFFUSE_SRV       3
#define MAGE_CONSTANT_SHADING_PASS_PS_SAMPLER           0

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	ConstantShadingPass::ConstantShadingPass()
		: m_device_context(GetImmediateDeviceContext()),
		m_vs(CreateTransformVS()),
		m_ps(CreateLambertianPS()),
		m_model_buffer(), m_projection_buffer(),
		m_white(CreateWhiteTexture()) {}

	ConstantShadingPass::ConstantShadingPass(ConstantShadingPass &&render_pass) = default;

	ConstantShadingPass::~ConstantShadingPass() = default;

	void XM_CALLCONV ConstantShadingPass::BindProjectionData(
		FXMMATRIX view_to_projection) noexcept {
		
		m_projection_buffer.UpdateData(
			m_device_context, XMMatrixTranspose(view_to_projection));
		VS::BindConstantBuffer(m_device_context,
			MAGE_CONSTANT_SHADING_PASS_VS_PROJECTION_BUFFER, m_projection_buffer.Get());
	}

	void XM_CALLCONV ConstantShadingPass::BindModelData(
		FXMMATRIX object_to_view, 
		FXMMATRIX view_to_object,
		FXMMATRIX texture_transform) noexcept {

		ModelBuffer buffer;
		buffer.m_object_to_view           = XMMatrixTranspose(object_to_view);
		buffer.m_normal_to_view           = view_to_object;
		buffer.m_texture_transform        = XMMatrixTranspose(texture_transform);
		buffer.m_Kd                       = RGBSpectrum(1.0f);
		buffer.m_dissolve                 = 1.0f;
		buffer.m_material_coefficients[0] = 1.0f;
		
		// Update the model buffer.
		m_model_buffer.UpdateData(m_device_context, buffer);
		// Bind the model buffer.
		VS::BindConstantBuffer(m_device_context, 
			MAGE_CONSTANT_SHADING_PASS_VS_MODEL_BUFFER, m_model_buffer.Get());
		PS::BindConstantBuffer(m_device_context, 
			MAGE_CONSTANT_SHADING_PASS_PS_MODEL_BUFFER, m_model_buffer.Get());
	}

	void ConstantShadingPass::Render(const PassBuffer *scene, const CameraNode *node) {
		Assert(scene);
		Assert(node);

		// Bind the vertex shader.
		m_vs->BindShader(m_device_context);
		// Bind the pixel shader.
		m_ps->BindShader(m_device_context);
		// Bind the diffuse SRV.
		PS::BindSRV(m_device_context, 
			MAGE_CONSTANT_SHADING_PASS_PS_DIFFUSE_SRV, m_white->Get());
		// Bind the rasterization state.
		RenderingStateCache::Get()->BindCullCounterClockwiseRasterizerState(m_device_context);
		// Bind the depth-stencil state.
		RenderingStateCache::Get()->BindDepthDefaultDepthStencilState(m_device_context);
		// Bind the blend state.
		RenderingStateCache::Get()->BindOpaqueBlendState(m_device_context);
		// Bind the sampler.
		PS::BindSampler(m_device_context, MAGE_CONSTANT_SHADING_PASS_PS_SAMPLER,
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
		
		ProcessModels(scene->m_opaque_emissive_models,      world_to_projection, world_to_view, view_to_world);
		ProcessModels(scene->m_opaque_brdf_models,          world_to_projection, world_to_view, view_to_world);
		ProcessModels(scene->m_transparent_emissive_models, world_to_projection, world_to_view, view_to_world);
		ProcessModels(scene->m_transparent_brdf_models,     world_to_projection, world_to_view, view_to_world);
	}

	void XM_CALLCONV ConstantShadingPass::ProcessModels(
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

			// Bind the model data.
			BindModelData(object_to_view, view_to_object, texture_transform);
			// Bind the model mesh.
			model->BindMesh(m_device_context);
			// Draw the model.
			model->Draw(m_device_context);
		}
	}
}