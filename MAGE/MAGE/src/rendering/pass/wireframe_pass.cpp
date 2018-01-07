//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "rendering\rendering_manager.hpp"
#include "resource\resource_factory.hpp"
#include "math\geometry\view_frustum.hpp"
#include "logging\error.hpp"

// Include HLSL bindings.
#include "hlsl.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	WireframePass *WireframePass::Get() {
		Assert(Renderer::Get());

		return Renderer::Get()->GetWireframePass();
	}

	WireframePass::WireframePass()
		: m_device_context(Pipeline::GetImmediateDeviceContext()),
		m_vs(CreateMinimalTransformVS()), 
		m_ps(CreateConstantColorPS()), 
		m_color_buffer(), 
		m_model_buffer() {}

	WireframePass::WireframePass(WireframePass &&render_pass) noexcept = default;

	WireframePass::~WireframePass() = default;

	void WireframePass::BindColorData() {
		// The color in linear space.
		static constexpr RGBA color(0.0f, 0.0f, 1.0f, 1.0f);

		// Update the color buffer.
		m_color_buffer.UpdateData(m_device_context, color);
		// Bind the color buffer.
		m_color_buffer.Bind< Pipeline::PS >(
			m_device_context, SLOT_CBUFFER_COLOR);
	}

	void XM_CALLCONV WireframePass::BindModelData(
		FXMMATRIX object_to_view) {

		ModelNormalTextureTransformBuffer buffer;
		buffer.m_object_to_view = XMMatrixTranspose(object_to_view);
		// m_normal_to_view    is not needed.
		// m_texture_transform is not needed.

		// Update the model buffer.
		m_model_buffer.UpdateData(m_device_context, buffer);
		// Bind the model buffer.
		m_model_buffer.Bind< Pipeline::VS >(
			m_device_context, SLOT_CBUFFER_MODEL);
	}

	void WireframePass::BindFixedState() {
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
		// PS: Bind the color data.
		BindColorData();
		// OM: Bind the depth-stencil state.
		#ifdef DISSABLE_INVERTED_Z_BUFFER
		RenderingStateManager::Get()->BindLessEqualDepthReadWriteDepthStencilState(m_device_context);
		#else  // DISSABLE_INVERTED_Z_BUFFER
		RenderingStateManager::Get()->BindGreaterEqualDepthReadWriteDepthStencilState(m_device_context);
		#endif // DISSABLE_INVERTED_Z_BUFFER
		// OM: Bind the blend state.
		RenderingStateManager::Get()->BindOpaqueBlendState(m_device_context);
	}

	void XM_CALLCONV WireframePass::Render(
		const Scene &scene,
		FXMMATRIX world_to_projection,
		CXMMATRIX world_to_view) {
		
		// Process the models.
		scene.ForEach< Model >([this, world_to_projection, world_to_view](const Model &model) {
			if (State::Active != model.GetState()) {
				return;
			}
			
			const Transform &transform          = model.GetOwner()->GetTransform();
			const XMMATRIX object_to_world      = transform.GetObjectToWorldMatrix();
			const XMMATRIX object_to_projection = object_to_world * world_to_projection;

			// Apply view frustum culling.
			if (ViewFrustum::Cull(object_to_projection, model.GetAABB())) {
				return;
			}

			const XMMATRIX object_to_view       = object_to_world * world_to_view;

			// Bind the model data.
			BindModelData(object_to_view);
			// Bind the model mesh.
			model.BindMesh(m_device_context);
			// Draw the model.
			model.Draw(m_device_context);
		});
	}
}