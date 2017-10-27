//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "rendering\rendering_manager.hpp"
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

	BoundingVolumePass *BoundingVolumePass::Get() {
		Assert(Renderer::Get());

		return Renderer::Get()->GetBoundingVolumePass();
	}

	BoundingVolumePass::BoundingVolumePass()
		: m_device_context(Pipeline::GetImmediateDeviceContext()),
		m_vs(CreateBoundingVolumeVS()), 
		m_ps(CreateBoundingVolumePS()),
		m_color_buffer(), m_model_buffer() {}

	BoundingVolumePass::BoundingVolumePass(
		BoundingVolumePass &&render_pass) = default;

	BoundingVolumePass::~BoundingVolumePass() = default;

	void BoundingVolumePass::BindColorData(const RGBASpectrum &color) {
		
		// Update the color buffer.
		m_color_buffer.UpdateData(m_device_context, color);
		// Bind the color buffer.
		m_color_buffer.Bind< Pipeline::PS >(
			m_device_context, SLOT_CBUFFER_COLOR);
	}

	void BoundingVolumePass::BindLightColorData() {
		// The color in linear space.
		static const RGBASpectrum color(1.0f, 0.0f, 0.0f, 1.0f);

		// Bind the color data.
		BindColorData(color);
	}

	void BoundingVolumePass::BindModelColorData() {
		// The color in linear space.
		static const RGBASpectrum color(0.0f, 1.0f, 0.0f, 1.0f);

		// Bind the color data.
		BindColorData(color);
	}

	void XM_CALLCONV BoundingVolumePass::BindModelData(
		FXMMATRIX box_to_projection) {

		// Update the model buffer.
		m_model_buffer.UpdateData(m_device_context, 
			XMMatrixTranspose(box_to_projection));
		// Bind the model buffer.
		m_model_buffer.Bind< Pipeline::VS >(
			m_device_context, SLOT_CBUFFER_PER_DRAW);
	}

	void BoundingVolumePass::BindFixedState() {
		// IA: Bind the primitive topology.
		Pipeline::IA::BindPrimitiveTopology(m_device_context,
			D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
		// VS: Bind the vertex shader.
		m_vs->BindShader(m_device_context);
		// HS: Bind the hull shader.
		Pipeline::HS::BindShader(m_device_context, nullptr);
		// DS: Bind the domain shader.
		Pipeline::DS::BindShader(m_device_context, nullptr);
		// GS: Bind the geometry shader.
		Pipeline::GS::BindShader(m_device_context, nullptr);
		// RS: Bind the rasterization state.
		RenderingStateManager::Get()->BindWireframeRasterizerState(m_device_context);
		// PS: Bind the pixel shader.
		m_ps->BindShader(m_device_context);
		// OM: Bind the depth-stencil state.
		RenderingStateManager::Get()->BindGreaterEqualDepthReadWriteDepthStencilState(m_device_context);
		// OM: Bind the blend state.
		RenderingStateManager::Get()->BindOpaqueBlendState(m_device_context);
	}

	void XM_CALLCONV BoundingVolumePass::Render(
		const PassBuffer *scene, 
		FXMMATRIX world_to_projection) {
		
		Assert(scene);

		// Bind the light color data.
		BindLightColorData();
		
		// Process the lights.
		ProcessLights(scene->GetOmniLights(), 
			world_to_projection);
		ProcessLights(scene->GetOmniLightsWithShadowMapping(), 
			world_to_projection);
		ProcessLights(scene->GetSpotLights(), 
			world_to_projection);
		ProcessLights(scene->GetSpotLightsWithShadowMapping(), 
			world_to_projection);

		// Bind the model color data.
		BindModelColorData();

		// Process the models.
		ProcessModels(scene->GetOpaqueEmissiveModels(),
			world_to_projection);
		ProcessModels(scene->GetOpaqueBRDFModels(),
			world_to_projection);
		ProcessModels(scene->GetTransparentEmissiveModels(),
			world_to_projection);
		ProcessModels(scene->GetTransparentBRDFModels(),
			world_to_projection);
	}

	void XM_CALLCONV BoundingVolumePass::ProcessLights(
		const vector< const OmniLightNode * > &lights,
		FXMMATRIX world_to_projection) {

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

			const XMMATRIX box_to_projection      = box_transform.GetObjectToParentMatrix() * object_to_projection;

			// Bind the model data.
			BindModelData(box_to_projection);
			// Draw the lines cube.
			Pipeline::Draw(m_device_context, 24u, 0u);
		}
	}

	void XM_CALLCONV BoundingVolumePass::ProcessLights(
		const vector< const SpotLightNode * > &lights,
		FXMMATRIX world_to_projection) {

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

			const XMMATRIX box_to_projection     = box_transform.GetObjectToParentMatrix() * object_to_projection;

			// Bind the model data.
			BindModelData(box_to_projection);
			// Draw the lines cube.
			Pipeline::Draw(m_device_context, 24u, 0u);
		}
	}

	void XM_CALLCONV BoundingVolumePass::ProcessModels(
		const vector< const ModelNode * > &models,
		FXMMATRIX world_to_projection) {

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

			const XMMATRIX box_to_projection      = box_transform.GetObjectToParentMatrix() * object_to_projection;

			// Bind the model data.
			BindModelData(box_to_projection);
			// Draw the lines cube.
			Pipeline::Draw(m_device_context, 24u, 0u);
		}
	}
}