//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "pass\depth_pass.hpp"
#include "rendering\rendering_state_cache.hpp"
#include "resource\resource_factory.hpp"
#include "math\view_frustum.hpp"
#include "logging\error.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Defines
//-----------------------------------------------------------------------------
#pragma region

#define MAGE_DEPTH_PASS_VS_PROJECTION_BUFFER 1
#define MAGE_DEPTH_PASS_VS_MODEL_BUFFER      2

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	DepthPass::DepthPass()
		: m_device_context(GetImmediateDeviceContext()),
		m_vs(CreateDepthVS()),
		m_projection_buffer(), m_model_buffer() {}

	DepthPass::DepthPass(DepthPass &&render_pass) = default;

	DepthPass::~DepthPass() = default;

	void XM_CALLCONV DepthPass::BindModelData(
		FXMMATRIX object_to_view) noexcept {

		m_model_buffer.UpdateData(
			m_device_context, XMMatrixTranspose(object_to_view));
		VS::BindConstantBuffer(m_device_context,
			MAGE_DEPTH_PASS_VS_MODEL_BUFFER, m_model_buffer.Get());
	}

	void XM_CALLCONV DepthPass::BindProjectionData(
		FXMMATRIX view_to_projection) noexcept {

		m_projection_buffer.UpdateData(
			m_device_context, XMMatrixTranspose(view_to_projection));
		VS::BindConstantBuffer(m_device_context,
			MAGE_DEPTH_PASS_VS_PROJECTION_BUFFER, m_projection_buffer.Get());
	}

	void DepthPass::Render(const PassBuffer *scene, const CameraNode *node) {
		Assert(scene);
		Assert(node);

		// Bind the vertex shader.
		m_vs->BindShader(m_device_context);
		// Bind no pixel shader.
		PS::BindShader(m_device_context, nullptr);
		// Bind the rasterization state.
		RenderingStateCache::Get()->BindCullCounterClockwiseRasterizerState(m_device_context);
		// Bind the depth-stencil state.
		RenderingStateCache::Get()->BindDepthDefaultDepthStencilState(m_device_context);

		// Obtain node components.
		const TransformNode * const transform = node->GetTransform();
		const Camera        * const camera    = node->GetCamera();
		const XMMATRIX world_to_view          = transform->GetWorldToViewMatrix();
		const XMMATRIX view_to_projection     = camera->GetViewToProjectionMatrix();
		const XMMATRIX world_to_projection    = world_to_view * view_to_projection;

		// Bind the projection data.
		BindProjectionData(view_to_projection);

		ProcessModels(scene->m_opaque_emissive_models, world_to_projection, world_to_view);
		ProcessModels(scene->m_opaque_brdf_models,     world_to_projection, world_to_view);
	}

	void XM_CALLCONV DepthPass::ProcessModels(
		const vector< const ModelNode * > &models,
		FXMMATRIX world_to_projection,
		FXMMATRIX world_to_view) noexcept {

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

			// Bind the model data.
			BindModelData(object_to_view);
			// Bind the model mesh.
			model->BindMesh(m_device_context);
			// Draw the model.
			model->Draw(m_device_context);
		}
	}
}