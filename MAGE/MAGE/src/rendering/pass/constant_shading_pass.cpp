//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "rendering\rendering_manager.hpp"
#include "resource\resource_factory.hpp"
#include "logging\error.hpp"

// Include HLSL bindings.
#include "hlsl.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	ConstantShadingPass *ConstantShadingPass::Get() {
		Assert(Renderer::Get());

		return Renderer::Get()->GetConstantShadingPass();
	}

	ConstantShadingPass::ConstantShadingPass()
		: m_device_context(Pipeline::GetImmediateDeviceContext()),
		m_vs(CreateTransformVS()),
		m_ps(CreateForwardLambertianPS()),
		m_model_buffer(),
		m_white(CreateWhiteTexture()) {}

	ConstantShadingPass::ConstantShadingPass(
		ConstantShadingPass &&render_pass) noexcept = default;

	ConstantShadingPass::~ConstantShadingPass() = default;

	void XM_CALLCONV ConstantShadingPass::BindModelData(
		FXMMATRIX object_to_view, 
		CXMMATRIX view_to_object,
		CXMMATRIX texture_transform) {

		ModelBuffer buffer;
		// Transforms
		buffer.m_transform.m_object_to_view    = XMMatrixTranspose(object_to_view);
		buffer.m_transform.m_normal_to_view    = view_to_object;
		buffer.m_transform.m_texture_transform = XMMatrixTranspose(texture_transform);
		// Material
		buffer.m_base_color                    = RGBA(1.0f);
		
		// Update the model buffer.
		m_model_buffer.UpdateData(m_device_context, 
			buffer);
		// Bind the model buffer.
		m_model_buffer.Bind< Pipeline::VS >(
			m_device_context, SLOT_CBUFFER_MODEL);
		m_model_buffer.Bind< Pipeline::PS >(
			m_device_context, SLOT_CBUFFER_MODEL);
	}

	void ConstantShadingPass::BindFixedState() {
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
		m_ps->BindShader(m_device_context);
		// PS: Bind the diffuse SRV.
		Pipeline::PS::BindSRV(m_device_context,
			SLOT_SRV_BASE_COLOR, m_white->Get());
		// OM: Bind the depth-stencil state.
		#ifdef DISSABLE_INVERTED_Z_BUFFER
		RenderingStateManager::Get()->BindLessEqualDepthReadWriteDepthStencilState(m_device_context);
		#else  // DISSABLE_INVERTED_Z_BUFFER
		RenderingStateManager::Get()->BindGreaterEqualDepthReadWriteDepthStencilState(m_device_context);
		#endif // DISSABLE_INVERTED_Z_BUFFER
		// OM: Bind the blend state.
		RenderingStateManager::Get()->BindOpaqueBlendState(m_device_context);
	}

	void XM_CALLCONV ConstantShadingPass::Render(
		const Scene &scene,
		FXMMATRIX world_to_projection,
		CXMMATRIX world_to_view,
		CXMMATRIX view_to_world) {

		// Process the models.
		scene.ForEach< Model >([this, world_to_projection, world_to_view, view_to_world](const Model &model) {
			if (State::Active != model.GetState()) {
				return;
			}
			
			const Transform &transform          = model.GetOwner()->GetTransform();
			const XMMATRIX object_to_world      = transform.GetObjectToWorldMatrix();
			const XMMATRIX object_to_projection = object_to_world * world_to_projection;

			// Apply view frustum culling.
			if (BoundingFrustum::Cull(object_to_projection, model.GetAABB())) {
				return;
			}

			const XMMATRIX object_to_view       = object_to_world * world_to_view;
			const XMMATRIX world_to_object      = transform.GetWorldToObjectMatrix();
			const XMMATRIX view_to_object       = view_to_world * world_to_object;
			const XMMATRIX texture_transform    = model.GetTextureTransform().GetTransformMatrix();

			// Bind the model data.
			BindModelData(object_to_view, view_to_object, texture_transform);
			// Bind the model mesh.
			model.BindMesh(m_device_context);
			// Draw the model.
			model.Draw(m_device_context);
		});
	}
}