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

	DepthPass *DepthPass::Get() {
		Assert(SceneRenderer::Get());

		return SceneRenderer::Get()->GetDepthPass();
	}

	DepthPass::DepthPass()
		: m_device_context(GetImmediateDeviceContext()),
		m_opaque_vs(CreateDepthVS()),
		m_transparent_vs(CreateDepthTransparentVS()),
		m_transparent_ps(CreateDepthTransparentPS()),
		m_projection_buffer(), m_opaque_model_buffer(),
		m_transparent_model_buffer(), m_dissolve_buffer() {}

	DepthPass::DepthPass(DepthPass &&render_pass) = default;

	DepthPass::~DepthPass() = default;

	void DepthPass::BindOpaqueModelShaders() const noexcept {
		// Bind the vertex shader.
		m_opaque_vs->BindShader(m_device_context);
		// Bind no pixel shader.
		Pipeline::PS::BindShader(m_device_context, nullptr);
	}

	void DepthPass::BindTransparentModelShaders() const noexcept {
		// Bind the vertex shader.
		m_transparent_vs->BindShader(m_device_context);
		// Bind the pixel shader.
		m_transparent_ps->BindShader(m_device_context);
	}

	void XM_CALLCONV DepthPass::BindProjectionData(
		FXMMATRIX view_to_projection) {

		// Update the projection buffer.
		m_projection_buffer.UpdateData(m_device_context, 
			XMMatrixTranspose(view_to_projection));
		// Bind the projection buffer.
		Pipeline::VS::BindConstantBuffer(m_device_context,
			SLOT_CBUFFER_PER_FRAME, m_projection_buffer.Get());
	}

	void XM_CALLCONV DepthPass::BindOpaqueModelData(
		FXMMATRIX object_to_view) {

		// Update the model buffer.
		m_opaque_model_buffer.UpdateData(m_device_context,
			XMMatrixTranspose(object_to_view));
		// Bind the model buffer.
		Pipeline::VS::BindConstantBuffer(m_device_context,
			SLOT_CBUFFER_PER_DRAW, m_opaque_model_buffer.Get());
	}

	void XM_CALLCONV DepthPass::BindTransparentModelData(
		FXMMATRIX object_to_view,
		CXMMATRIX texture_transform,
		const Material *material) {

		ModelTextureTransformBuffer transform;
		transform.m_object_to_view    = XMMatrixTranspose(object_to_view);
		transform.m_texture_transform = XMMatrixTranspose(texture_transform);

		// Update the model buffer.
		m_transparent_model_buffer.UpdateData(m_device_context,
			transform);
		// Bind the model buffer.
		Pipeline::VS::BindConstantBuffer(m_device_context,
			SLOT_CBUFFER_PER_DRAW, m_transparent_model_buffer.Get());

		XMVECTOR dissolve = { material->GetDissolve(), 0.0f, 0.0f, 0.0f };

		// Update the dissolve buffer.
		m_dissolve_buffer.UpdateData(m_device_context,
			dissolve);
		// Bind the dissolve buffer.
		Pipeline::PS::BindConstantBuffer(m_device_context,
			SLOT_CBUFFER_PER_DRAW, m_dissolve_buffer.Get());

		// Bind the diffuse SRV.
		Pipeline::PS::BindSRV(m_device_context,
			SLOT_SRV_DIFFUSE, material->GetDiffuseReflectivitySRV());
	}

	void DepthPass::BindFixedState() {
		// Bind the rasterization state.
		RenderingStateCache::Get()->BindCullCounterClockwiseRasterizerState(m_device_context);
		// Bind the depth-stencil state.
		RenderingStateCache::Get()->BindDepthReadWriteDepthStencilState(m_device_context);
	}

	void XM_CALLCONV DepthPass::Render(
		const PassBuffer *scene,
		FXMMATRIX world_to_projection,
		CXMMATRIX world_to_view,
		CXMMATRIX view_to_projection) {

		Assert(scene);

		// Bind the projection data.
		BindProjectionData(view_to_projection);

		// Bind the shaders.
		BindOpaqueModelShaders();

		// Process the opaque models.
		ProcessOpaqueModels(scene->GetOpaqueEmissiveModels(),
			world_to_projection, world_to_view);
		ProcessOpaqueModels(scene->GetOpaqueBRDFModels(),
			world_to_projection, world_to_view);
	}

	void XM_CALLCONV DepthPass::RenderOccluders(
		const PassBuffer *scene,
		FXMMATRIX world_to_projection,
		CXMMATRIX world_to_view,
		CXMMATRIX view_to_projection) {

		Assert(scene);

		// Bind the projection data.
		BindProjectionData(view_to_projection);

		// Bind the shaders.
		BindOpaqueModelShaders();

		// Process the opaque models.
		ProcessOpaqueOccluderModels(scene->GetOpaqueEmissiveModels(),
			world_to_projection, world_to_view);
		ProcessOpaqueOccluderModels(scene->GetOpaqueBRDFModels(),
			world_to_projection, world_to_view);

		// Bind the shaders.
		BindTransparentModelShaders();

		// Process the transparent models.
		ProcessTransparentOccluderModels(scene->GetTransparentEmissiveModels(),
			world_to_projection, world_to_view);
		ProcessTransparentOccluderModels(scene->GetTransparentBRDFModels(),
			world_to_projection, world_to_view);
	}

	void XM_CALLCONV DepthPass::ProcessOpaqueModels(
		const vector< const ModelNode * > &models,
		FXMMATRIX world_to_projection,
		CXMMATRIX world_to_view) {

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
			BindOpaqueModelData(object_to_view);
			// Bind the model mesh.
			model->BindMesh(m_device_context);
			// Draw the model.
			model->Draw(m_device_context);
		}
	}

	void XM_CALLCONV DepthPass::ProcessOpaqueOccluderModels(
		const vector< const ModelNode * > &models,
		FXMMATRIX world_to_projection,
		CXMMATRIX world_to_view) {

		for (const auto node : models) {

			// Obtain node components (1/3).
			const Model         * const model     = node->GetModel();

			// Skip non-occluder models.
			if (!model->OccludesLight()) {
				continue;
			}

			// Obtain node components (2/3).
			const TransformNode * const transform = node->GetTransform();
			const XMMATRIX object_to_world        = transform->GetObjectToWorldMatrix();
			const XMMATRIX object_to_projection   = object_to_world * world_to_projection;

			// Cull the model against the view frustum.
			if (ViewFrustum::Cull(object_to_projection, model->GetAABB())) {
				continue;
			}

			// Obtain node components (3/3).
			const XMMATRIX object_to_view         = object_to_world * world_to_view;

			// Bind the model data.
			BindOpaqueModelData(object_to_view);
			// Bind the model mesh.
			model->BindMesh(m_device_context);
			// Draw the model.
			model->Draw(m_device_context);
		}
	}

	void XM_CALLCONV DepthPass::ProcessTransparentOccluderModels(
		const vector< const ModelNode * > &models,
		FXMMATRIX world_to_projection,
		CXMMATRIX world_to_view) {

		for (const auto node : models) {

			// Obtain node components (1/3).
			const Model         * const model     = node->GetModel();
			const Material      * const material  = model->GetMaterial();

			// Skip non-occluder models and "too" transparent models.
			if (!model->OccludesLight() 
				|| material->GetDissolve() < TRANSPARENCY_THRESHOLD) {
				continue;
			}

			// Obtain node components (2/3).
			const TransformNode * const transform = node->GetTransform();
			const XMMATRIX object_to_world        = transform->GetObjectToWorldMatrix();
			const XMMATRIX object_to_projection   = object_to_world * world_to_projection;

			// Cull the model against the view frustum.
			if (ViewFrustum::Cull(object_to_projection, model->GetAABB())) {
				continue;
			}

			// Obtain node components (3/3).
			const XMMATRIX object_to_view         = object_to_world * world_to_view;
			const XMMATRIX texture_transform      = node->GetTextureTransform()->GetTransformMatrix();
			
			// Bind the model data.
			BindTransparentModelData(object_to_view, texture_transform, material);
			// Bind the model mesh.
			model->BindMesh(m_device_context);
			// Draw the model.
			model->Draw(m_device_context);
		}
	}
}