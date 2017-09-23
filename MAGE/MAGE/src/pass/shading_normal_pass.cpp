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

	ShadingNormalPass *ShadingNormalPass::Get() {
		Assert(SceneRenderer::Get());

		return SceneRenderer::Get()->GetShadingNormalPass();
	}

	ShadingNormalPass::ShadingNormalPass()
		: m_device_context(Pipeline::GetImmediateDeviceContext()), 
		m_render_mode(RenderMode::None), 
		m_vs(CreateShadingNormalVS()), 
		m_ps{ CreateShadingNormalPS(), CreateShadingNormalTSNMPS() }, 
		m_bound_ps(PSIndex::Count),
		m_projection_buffer(), m_model_buffer() {}

	ShadingNormalPass::ShadingNormalPass(ShadingNormalPass &&render_pass) = default;

	ShadingNormalPass::~ShadingNormalPass() = default;

	void ShadingNormalPass::BindPS(PSIndex index) noexcept {
		if (m_bound_ps != index) {
			m_ps[static_cast< size_t >(index)]->BindShader(m_device_context);
			m_bound_ps = index;
		}
	}

	void ShadingNormalPass::BindPS(const Material *material) noexcept {
		if (RenderMode::TSNMShadingNormal == m_render_mode
			&& material->GetNormalSRV()) {

			// Bind the pixel shader.
			BindPS(PSIndex::TSNMShadingNormal);

			// Bind the normal SRV.
			Pipeline::PS::BindSRV(m_device_context,
				SLOT_SRV_NORMAL, material->GetNormalSRV());
		}
		else {

			// Bind the pixel shader.
			BindPS(PSIndex::ShadingNormal);
		}
	}

	void XM_CALLCONV ShadingNormalPass::BindProjectionData(
		FXMMATRIX view_to_projection) {

		// Update the projection buffer.
		m_projection_buffer.UpdateData(m_device_context, 
			XMMatrixTranspose(view_to_projection));
		// Bind the projection buffer.
		m_projection_buffer.Bind< Pipeline::VS >(
			m_device_context, SLOT_CBUFFER_PER_FRAME);
	}

	void XM_CALLCONV ShadingNormalPass::BindModelData(
		FXMMATRIX object_to_view, 
		CXMMATRIX world_to_object) {

		ModelNormalTransformBuffer buffer;
		buffer.m_object_to_view    = XMMatrixTranspose(object_to_view);
		buffer.m_normal_to_view    = world_to_object;

		// Update the model buffer.
		m_model_buffer.UpdateData(m_device_context, 
			buffer);
		// Bind the model buffer.
		m_model_buffer.Bind< Pipeline::VS >(
			m_device_context, SLOT_CBUFFER_PER_DRAW);
	}

	void ShadingNormalPass::BindFixedState(RenderMode render_mode) {
		// Reset the render mode.
		m_render_mode = render_mode;
		// Reset the bound pixel shader index.
		m_bound_ps = PSIndex::Count;

		// Bind the vertex shader.
		m_vs->BindShader(m_device_context);
		// Bind the rasterization state.
		RenderingStateCache::Get()->BindCullCounterClockwiseRasterizerState(m_device_context);
		// Bind the depth-stencil state.
		RenderingStateCache::Get()->BindDepthReadWriteDepthStencilState(m_device_context);
		// Bind the blend state.
		RenderingStateCache::Get()->BindOpaqueBlendState(m_device_context);
	}

	void XM_CALLCONV ShadingNormalPass::Render(
		const PassBuffer *scene, 
		FXMMATRIX world_to_projection,
		CXMMATRIX world_to_view,
		CXMMATRIX view_to_projection) {
		
		Assert(scene);

		// Bind the projection data.
		BindProjectionData(view_to_projection);
		
		// Process the models (which interact with light).
		ProcessModels(scene->GetOpaqueBRDFModels(), 
			world_to_projection, world_to_view);
		ProcessModels(scene->GetTransparentBRDFModels(), 
			world_to_projection, world_to_view);
	}

	void XM_CALLCONV ShadingNormalPass::ProcessModels(
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
			const XMMATRIX world_to_object        = transform->GetWorldToObjectMatrix();

			// Bind the model data.
			BindModelData(object_to_view, world_to_object);
			// Bind the pixel shader.
			BindPS(model->GetMaterial());
			// Bind the model mesh.
			model->BindMesh(m_device_context);
			// Draw the model.
			model->Draw(m_device_context);
		}
	}
}