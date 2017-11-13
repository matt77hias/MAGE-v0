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

	ConstantComponentPass *ConstantComponentPass::Get() {
		Assert(Renderer::Get());

		return Renderer::Get()->GetConstantComponentPass();
	}

	ConstantComponentPass::ConstantComponentPass()
		: m_device_context(Pipeline::GetImmediateDeviceContext()), 
		m_vs(CreateMinimalTransformVS()),
		m_ps{ CreateConstantColorTexturePS(), CreateDistancePS() },
		m_color_buffer(), m_model_buffer(),
		m_uv(CreateReferenceTexture()) {}

	ConstantComponentPass::ConstantComponentPass(
		ConstantComponentPass &&render_pass) = default;

	ConstantComponentPass::~ConstantComponentPass() = default;

	void ConstantComponentPass::BindPS(RenderMode render_mode) {
		switch (render_mode) {
		
		case RenderMode::UVTexture: {
			
			// Bind the pixel shader.
			m_ps[static_cast< size_t >(PSIndex::UVTexture)]->BindShader(m_device_context);

			// Update the color buffer.
			m_color_buffer.UpdateData(m_device_context, 
				RGBA(1.0f));
			// Bind the color buffer.
			m_color_buffer.Bind< Pipeline::PS >(
				m_device_context, SLOT_CBUFFER_COLOR);

			// Bind the texture SRV.
			Pipeline::PS::BindSRV(m_device_context,
				SLOT_SRV_TEXTURE, m_uv->Get());

			break;
		}
		
		case RenderMode::Distance: {

			// Bind the pixel shader.
			m_ps[static_cast< size_t >(PSIndex::Distance)]->BindShader(m_device_context);

			break;
		}

		}
	}

	void XM_CALLCONV ConstantComponentPass::BindModelData(
		FXMMATRIX object_to_view,
		CXMMATRIX view_to_object,
		CXMMATRIX texture_transform) {

		ModelNormalTextureTransformBuffer buffer;
		buffer.m_object_to_view    = XMMatrixTranspose(object_to_view);
		buffer.m_normal_to_view    = view_to_object;
		buffer.m_texture_transform = XMMatrixTranspose(texture_transform);

		// Update the model buffer.
		m_model_buffer.UpdateData(m_device_context, buffer);
		// Bind the model buffer.
		m_model_buffer.Bind< Pipeline::VS >(
			m_device_context, SLOT_CBUFFER_MODEL);
	}

	void ConstantComponentPass::BindFixedState(RenderMode render_mode) {
		// VS: Bind the vertex shader.
		m_vs->BindShader(m_device_context);
		// HS: Bind the hull shader.
		Pipeline::HS::BindShader(m_device_context, nullptr);
		// DS: Bind the domain shader.
		Pipeline::DS::BindShader(m_device_context, nullptr);
		// GS: Bind the geometry shader.
		Pipeline::GS::BindShader(m_device_context, nullptr);
		// RS: Bind the rasterization state.
		RenderingStateManager::Get()->BindCullCounterClockwiseRasterizerState(m_device_context);
		// PS: Bind the pixel shader.
		BindPS(render_mode);
		// OM: Bind the depth-stencil state.
#ifdef DISSABLE_INVERTED_Z_BUFFER
		RenderingStateManager::Get()->BindLessEqualDepthReadWriteDepthStencilState(m_device_context);
#else  // DISSABLE_INVERTED_Z_BUFFER
		RenderingStateManager::Get()->BindGreaterEqualDepthReadWriteDepthStencilState(m_device_context);
#endif // DISSABLE_INVERTED_Z_BUFFER
		// OM: Bind the blend state.
		RenderingStateManager::Get()->BindOpaqueBlendState(m_device_context);
	}

	void XM_CALLCONV ConstantComponentPass::Render(
		const PassBuffer *scene, 
		FXMMATRIX world_to_projection,
		CXMMATRIX world_to_view,
		CXMMATRIX view_to_world) {
		
		Assert(scene);

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

	void XM_CALLCONV ConstantComponentPass::ProcessModels(
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