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

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	DepthPass::DepthPass()
		: m_device_context(GetImmediateDeviceContext()),
		m_vs(CreateDepthVS()),
		m_projection_buffer() {}

	DepthPass::DepthPass(DepthPass &&render_pass) = default;

	DepthPass::~DepthPass() = default;

	void XM_CALLCONV DepthPass::BindProjectionData(
		FXMMATRIX object_to_projection) noexcept {

		m_projection_buffer.UpdateData(
			m_device_context, XMMatrixTranspose(object_to_projection));
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

		ProcessModels(scene->m_opaque_emissive_models, world_to_projection);
		ProcessModels(scene->m_opaque_brdf_models,     world_to_projection);
	}

	void XM_CALLCONV DepthPass::ProcessModels(
		const vector< const ModelNode * > &models,
		FXMMATRIX world_to_projection) noexcept {

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

			// Bind the model data.
			BindProjectionData(object_to_projection);
			// Bind the model mesh.
			model->BindMesh(m_device_context);
			// Draw the model.
			model->Draw(m_device_context);
		}
	}
}