//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "pass\constant_component_pass.hpp"
#include "rendering\rendering_state_cache.hpp"
#include "resource\resource_factory.hpp"
#include "math\view_frustum.hpp"
#include "logging\error.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Defines
//-----------------------------------------------------------------------------
#pragma region

#define MAGE_CONSTANT_COMPONENT_PASS_VS_SCENE_BUFFER 0
#define MAGE_CONSTANT_COMPONENT_PASS_VS_MODEL_BUFFER 1
#define MAGE_CONSTANT_COMPONENT_PASS_PS_COLOR_BUFFER 0
#define MAGE_CONSTANT_COMPONENT_PASS_PS_TEXTURE_SRV  0
#define MAGE_CONSTANT_COMPONENT_PASS_PS_SAMPLER      0

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	ConstantComponentPass::ConstantComponentPass()
		: m_device_context(GetImmediateDeviceContext()), 
		m_vs(CreateMinimalTransformVS()),
		m_ps{ CreateConstantColorTexturePS(), CreateDistancePS() },
		m_model_buffer(), m_scene_buffer(), 
		m_color_buffer(), m_uv(CreateReferenceTexture()) {}

	ConstantComponentPass::ConstantComponentPass(ConstantComponentPass &&render_pass) = default;

	ConstantComponentPass::~ConstantComponentPass() = default;

	void ConstantComponentPass::BindPS(RenderMode render_mode) noexcept {
		switch (render_mode) {
		
		case RenderMode::UVTexture: {
			
			// Bind the pixel shader.
			m_ps[static_cast< size_t >(PSIndex::UVTexture)]->BindShader(m_device_context);

			// Update the color buffer.
			m_color_buffer.UpdateData(m_device_context, RGBASpectrum(1.0f, 1.0f, 1.0f, 1.0f));
			// Bind the color buffer.
			PS::BindConstantBuffer(m_device_context,
				MAGE_CONSTANT_COMPONENT_PASS_PS_COLOR_BUFFER, m_color_buffer.Get());

			// Bind the texture SRV.
			PS::BindSRV(m_device_context,
				MAGE_CONSTANT_COMPONENT_PASS_PS_TEXTURE_SRV, m_uv->Get());

			break;
		}
		
		case RenderMode::Distance: {

			// Bind the pixel shader.
			m_ps[static_cast< size_t >(PSIndex::Distance)]->BindShader(m_device_context);

			break;
		}

		}
	}

	void XM_CALLCONV ConstantComponentPass::BindSceneData(
		FXMMATRIX view_to_projection) noexcept {

		// Update the scene buffer.
		m_scene_buffer.UpdateData(m_device_context, XMMatrixTranspose(view_to_projection));
		// Bind the scene buffer.
		VS::BindConstantBuffer(m_device_context,
			MAGE_CONSTANT_COMPONENT_PASS_VS_SCENE_BUFFER, m_scene_buffer.Get());
	}

	void XM_CALLCONV ConstantComponentPass::BindModelData(
		FXMMATRIX object_to_view,
		FXMMATRIX view_to_object,
		FXMMATRIX texture_transform) noexcept {

		ModelTransformBuffer buffer;
		buffer.m_object_to_view    = XMMatrixTranspose(object_to_view);
		buffer.m_normal_to_view    = view_to_object;
		buffer.m_texture_transform = XMMatrixTranspose(texture_transform);

		// Update the model buffer.
		m_model_buffer.UpdateData(m_device_context, buffer);
		// Bind the model buffer.
		VS::BindConstantBuffer(m_device_context, 
			MAGE_CONSTANT_COMPONENT_PASS_VS_MODEL_BUFFER, m_model_buffer.Get());
	}

	void ConstantComponentPass::Render(const PassBuffer *scene, const CameraNode *node) {
		Assert(scene);
		Assert(node);

		// Bind the vertex shader.
		m_vs->BindShader(m_device_context);
		// Bind the pixel shader.
		BindPS(node->GetSettings()->GetRenderMode());
		// Bind the rasterization state.
		RenderingStateCache::Get()->BindCullCounterClockwiseRasterizerState(m_device_context);
		// Bind the depth-stencil state.
		RenderingStateCache::Get()->BindDepthDefaultDepthStencilState(m_device_context);
		// Bind the blend state.
		RenderingStateCache::Get()->BindOpaqueBlendState(m_device_context);
		// Bind the sampler.
		PS::BindSampler(m_device_context, MAGE_CONSTANT_COMPONENT_PASS_PS_SAMPLER,
			RenderingStateCache::Get()->GetLinearWrapSamplerState());
			
		// Obtain node components.
		const TransformNode * const transform = node->GetTransform();
		const Camera        * const camera    = node->GetCamera();
		const XMMATRIX world_to_view          = transform->GetWorldToViewMatrix();
		const XMMATRIX view_to_world          = transform->GetViewToWorldMatrix();
		const XMMATRIX view_to_projection     = camera->GetViewToProjectionMatrix();
		const XMMATRIX world_to_projection    = world_to_view * view_to_projection;

		// Bind the scene data.
		BindSceneData(view_to_projection);

		ProcessModels(scene->m_opaque_models,      world_to_projection, world_to_view, view_to_world);
		ProcessModels(scene->m_transparent_models, world_to_projection, world_to_view, view_to_world);
	}

	void XM_CALLCONV ConstantComponentPass::ProcessModels(
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

			// Apply view frustum culling.
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