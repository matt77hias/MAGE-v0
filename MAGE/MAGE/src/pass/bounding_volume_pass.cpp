//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "pass\bounding_volume_pass.hpp"
#include "rendering\rendering_state_cache.hpp"
#include "resource\resource_factory.hpp"
#include "math\view_frustum.hpp"
#include "logging\error.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Defines
//-----------------------------------------------------------------------------
#pragma region

#define MAGE_BOUNDING_VOLUME_PASS_VS_SCENE_BUFFER 0
#define MAGE_BOUNDING_VOLUME_PASS_VS_MODEL_BUFFER 1
#define MAGE_BOUNDING_VOLUME_PASS_PS_COLOR_BUFFER 0

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	BoundingVolumePass::BoundingVolumePass()
		: m_device_context(GetImmediateDeviceContext()),
		m_vs(CreateMinimalTransformVS()), 
		m_ps(CreateConstantColorPS()), 
		m_model_buffer(), m_scene_buffer(), 
		m_color_buffer(), m_box(CreateLineCube()) {}

	BoundingVolumePass::BoundingVolumePass(BoundingVolumePass &&render_pass) = default;

	BoundingVolumePass::~BoundingVolumePass() = default;

	void XM_CALLCONV BoundingVolumePass::BindModelData(
		FXMMATRIX box_to_view) noexcept {

		ModelTransformBuffer buffer;
		buffer.m_object_to_view = XMMatrixTranspose(box_to_view);
		// m_normal_to_view is not needed.
		// m_texture_transform is not needed.

		// Update the model buffer.
		m_model_buffer.UpdateData(m_device_context, buffer);
		// Bind the model buffer.
		VS::BindConstantBuffer(m_device_context,
			MAGE_BOUNDING_VOLUME_PASS_VS_MODEL_BUFFER, m_model_buffer.Get());
	}

	void XM_CALLCONV BoundingVolumePass::BindSceneData(
		FXMMATRIX view_to_projection) noexcept {

		// Update the scene buffer.
		m_scene_buffer.UpdateData(m_device_context, XMMatrixTranspose(view_to_projection));
		// Bind the scene buffer.
		VS::BindConstantBuffer(m_device_context,
			MAGE_BOUNDING_VOLUME_PASS_VS_SCENE_BUFFER, m_scene_buffer.Get());
	}

	void BoundingVolumePass::BindLightColorData() noexcept {
		// Update the color buffer.
		m_color_buffer.UpdateData(m_device_context, RGBASpectrum(1.0f, 0.0f, 0.0f, 1.0f));
		// Bind the color buffer.
		PS::BindConstantBuffer(m_device_context,
			MAGE_BOUNDING_VOLUME_PASS_PS_COLOR_BUFFER, m_color_buffer.Get());
	}
	
	void BoundingVolumePass::BindModelColorData() noexcept {
		// Update the color buffer.
		m_color_buffer.UpdateData(m_device_context, RGBASpectrum(0.0f, 1.0f, 0.0f, 1.0f));
		// Bind the color buffer.
		PS::BindConstantBuffer(m_device_context,
			MAGE_BOUNDING_VOLUME_PASS_PS_COLOR_BUFFER, m_color_buffer.Get());
	}

	void BoundingVolumePass::Render(const PassBuffer *scene, const CameraNode *node) {
		Assert(scene);
		Assert(node);

		// Bind the mesh.
		m_box->BindMesh(m_device_context);
		// Bind the vertex shader.
		m_vs->BindShader(m_device_context);
		// Bind the pixel shader.
		m_ps->BindShader(m_device_context);
		// Bind the rasterization state.
		RenderingStateCache::Get()->BindWireframeRasterizerState(m_device_context);
		// Bind the depth-stencil state.
		RenderingStateCache::Get()->BindDepthDefaultDepthStencilState(m_device_context);
		// Bind the blend state.
		RenderingStateCache::Get()->BindOpaqueBlendState(m_device_context);

		// Obtain node components.
		const TransformNode * const transform = node->GetTransform();
		const Camera        * const camera    = node->GetCamera();
		const XMMATRIX world_to_view          = transform->GetWorldToViewMatrix();
		const XMMATRIX view_to_projection     = camera->GetViewToProjectionMatrix();
		const XMMATRIX world_to_projection    = world_to_view * view_to_projection;

		// Bind the scene data.
		BindSceneData(view_to_projection);
		
		// Bind the light color data.
		BindLightColorData();
		ProcessLights(scene->m_omni_lights, world_to_projection, world_to_view);
		ProcessLights(scene->m_spot_lights, world_to_projection, world_to_view);

		// Bind the model color data.
		BindModelColorData();
		ProcessModels(scene->m_opaque_models,      world_to_projection, world_to_view);
		ProcessModels(scene->m_transparent_models, world_to_projection, world_to_view);
	}

	void XM_CALLCONV BoundingVolumePass::ProcessLights(
		const vector< const OmniLightNode * > &lights,
		FXMMATRIX world_to_projection, 
		FXMMATRIX world_to_view) noexcept {

		for (const auto node : lights) {

			// Obtain node components (1/2).
			const TransformNode * const transform = node->GetTransform();
			const OmniLight     * const light     = node->GetLight();
			const XMMATRIX object_to_world        = transform->GetObjectToWorldMatrix();
			const XMMATRIX object_to_projection   = object_to_world * world_to_projection;

			// Apply view frustum culling.
			if (ViewFrustum::Cull(object_to_projection, light->GetBS())) {
				continue;
			}

			// Obtain node components (2/2).
			const AABB &aabb                      = light->GetAABB();

			Transform box_transform;
			box_transform.SetScale(aabb.Diagonal());
			box_transform.SetTranslation(aabb.Centroid());

			const XMMATRIX object_to_view         = object_to_world * world_to_view;
			const XMMATRIX box_to_view            = box_transform.GetObjectToParentMatrix() * object_to_view;

			// Bind the model data.
			BindModelData(box_to_view);
			// Draw the model.
			m_box->Draw(m_device_context);
		}
	}

	void XM_CALLCONV BoundingVolumePass::ProcessLights(
		const vector< const SpotLightNode * > &lights,
		FXMMATRIX world_to_projection, 
		FXMMATRIX world_to_view) noexcept {

		for (const auto node : lights) {

			// Obtain node components (1/2).
			const TransformNode * const transform = node->GetTransform();
			const SpotLight     * const light     = node->GetLight();
			const XMMATRIX object_to_world        = transform->GetObjectToWorldMatrix();
			const XMMATRIX object_to_projection   = object_to_world * world_to_projection;
			const AABB &aabb                      = light->GetAABB();

			// Apply view frustum culling.
			if (ViewFrustum::Cull(object_to_projection, aabb)) {
				continue;
			}

			// Obtain node components (2/2).
			Transform box_transform;
			box_transform.SetScale(aabb.Diagonal());
			box_transform.SetTranslation(aabb.Centroid());

			const XMMATRIX object_to_view         = object_to_world * world_to_view;
			const XMMATRIX box_to_view            = box_transform.GetObjectToParentMatrix() * object_to_view;

			// Bind the model data.
			BindModelData(box_to_view);
			// Draw the model.
			m_box->Draw(m_device_context);
		}
	}

	void XM_CALLCONV BoundingVolumePass::ProcessModels(
		const vector< const ModelNode * > &models,
		FXMMATRIX world_to_projection, 
		FXMMATRIX world_to_view) noexcept {

		for (const auto node : models) {

			// Obtain node components (1/2).
			const TransformNode * const transform = node->GetTransform();
			const Model         * const model     = node->GetModel();
			const XMMATRIX object_to_world        = transform->GetObjectToWorldMatrix();
			const XMMATRIX object_to_projection   = object_to_world * world_to_projection;
			const AABB &aabb                      = model->GetAABB();

			// Apply view frustum culling.
			if (ViewFrustum::Cull(object_to_projection, aabb)) {
				continue;
			}

			// Obtain node components (2/2).
			Transform box_transform;
			box_transform.SetScale(aabb.Diagonal());
			box_transform.SetTranslation(aabb.Centroid());

			const XMMATRIX object_to_view         = object_to_world * world_to_view;
			const XMMATRIX box_to_view            = box_transform.GetObjectToParentMatrix() * object_to_view;

			// Bind the model data.
			BindModelData(box_to_view);
			// Draw the model.
			m_box->Draw(m_device_context);
		}
	}
}