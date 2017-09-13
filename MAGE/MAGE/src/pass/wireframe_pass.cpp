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

	WireframePass *WireframePass::Get() {
		Assert(SceneRenderer::Get());

		return SceneRenderer::Get()->GetWireframePass();
	}

	WireframePass::WireframePass()
		: m_device_context(GetImmediateDeviceContext()),
		m_vs(CreateMinimalTransformVS()), m_ps(CreateConstantColorPS()), 
		m_color_buffer(), m_projection_buffer(), m_model_buffer() {}

	WireframePass::WireframePass(WireframePass &&render_pass) = default;

	WireframePass::~WireframePass() = default;

	void WireframePass::BindColorData() {
		static const RGBASpectrum color(0.0f, 0.0f, 1.0f, 1.0f);

		// Update the color buffer.
		m_color_buffer.UpdateData(m_device_context, color);
		// Bind the color buffer.
		PS::BindConstantBuffer(m_device_context,
			SLOT_CBUFFER_COLOR, m_color_buffer.Get());
	}

	void XM_CALLCONV WireframePass::BindProjectionData(
		FXMMATRIX view_to_projection) {

		// Update the projection buffer.
		m_projection_buffer.UpdateData(m_device_context, 
			XMMatrixTranspose(view_to_projection));
		// Bind the projection buffer.
		VS::BindConstantBuffer(m_device_context,
			SLOT_CBUFFER_PER_FRAME, m_projection_buffer.Get());
	}

	void XM_CALLCONV WireframePass::BindModelData(
		FXMMATRIX object_to_view) {

		ModelTransformBuffer buffer;
		buffer.m_object_to_view = XMMatrixTranspose(object_to_view);
		// m_normal_to_view    is not needed.
		// m_texture_transform is not needed.

		// Update the model buffer.
		m_model_buffer.UpdateData(m_device_context, buffer);
		// Bind the model buffer.
		VS::BindConstantBuffer(m_device_context,
			SLOT_CBUFFER_PER_DRAW, m_model_buffer.Get());
	}

	void WireframePass::BindFixedState() {
		// Bind the vertex shader.
		m_vs->BindShader(m_device_context);
		// Bind the pixel shader.
		m_ps->BindShader(m_device_context);
		// Bind the color data.
		BindColorData();
		// Bind the rasterization state.
		RenderingStateCache::Get()->BindWireframeRasterizerState(m_device_context);
		// Bind the depth-stencil state.
		RenderingStateCache::Get()->BindDepthDefaultDepthStencilState(m_device_context);
		// Bind the blend state.
		RenderingStateCache::Get()->BindOpaqueBlendState(m_device_context);
	}

	void XM_CALLCONV WireframePass::Render(
		const PassBuffer *scene,
		FXMMATRIX world_to_projection,
		CXMMATRIX world_to_view,
		CXMMATRIX view_to_projection) {
		
		Assert(scene);

		// Bind the projection data.
		BindProjectionData(view_to_projection);
		
		// Process the models.
		ProcessModels(scene->m_opaque_emissive_models,      world_to_projection, world_to_view);
		ProcessModels(scene->m_opaque_brdf_models,          world_to_projection, world_to_view);
		ProcessModels(scene->m_transparent_emissive_models, world_to_projection, world_to_view);
		ProcessModels(scene->m_transparent_brdf_models,     world_to_projection, world_to_view);
	}

	void XM_CALLCONV WireframePass::ProcessModels(
		const vector< const ModelNode * > &models,
		FXMMATRIX world_to_projection, 
		CXMMATRIX world_to_view) {

		for (const auto node : models) {

			// Obtain node components (1/2).
			const TransformNode * const transform = node->GetTransform();
			const Model         * const model     = node->GetModel();
			const XMMATRIX object_to_world        = transform->GetObjectToWorldMatrix();
			const XMMATRIX object_to_projection   = object_to_world * world_to_projection;

			// Apply view frustum culling.
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