//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "rendering\rendering_manager.hpp"
#include "shader\shader_factory.hpp"
#include "logging\error.hpp"

// Include HLSL bindings.
#include "hlsl.hpp"

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
		m_vs(CreateLineCubeVS()), 
		m_ps(CreateLineCubePS()),
		m_color_buffer(), 
		m_model_buffer() {}

	BoundingVolumePass::BoundingVolumePass(
		BoundingVolumePass &&pass) noexcept = default;

	BoundingVolumePass::~BoundingVolumePass() = default;

	void BoundingVolumePass::BindFixedState() const noexcept {
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
		#ifdef DISABLE_INVERTED_Z_BUFFER
		RenderingStateManager::Get()->BindLessEqualDepthReadWriteDepthStencilState(m_device_context);
		#else  // DISABLE_INVERTED_Z_BUFFER
		RenderingStateManager::Get()->BindGreaterEqualDepthReadWriteDepthStencilState(m_device_context);
		#endif // DISABLE_INVERTED_Z_BUFFER
		// OM: Bind the blend state.
		RenderingStateManager::Get()->BindOpaqueBlendState(m_device_context);
	}

	void BoundingVolumePass::BindLightColorData() {
		// The color in linear space.
		static constexpr RGBA color(1.0f, 0.0f, 0.0f, 1.0f);

		// Bind the color data.
		BindColorData(color);
	}

	void BoundingVolumePass::BindModelColorData() {
		// The color in linear space.
		static constexpr RGBA color(0.0f, 1.0f, 0.0f, 1.0f);

		// Bind the color data.
		BindColorData(color);
	}

	void BoundingVolumePass::BindColorData(const RGBA &color) {
		// Update the color buffer.
		m_color_buffer.UpdateData(m_device_context, color);
		// Bind the color buffer.
		m_color_buffer.Bind< Pipeline::PS >(m_device_context, SLOT_CBUFFER_COLOR);
	}

	void XM_CALLCONV BoundingVolumePass::BindModelData(FXMMATRIX box_to_view) {
		// Update the model buffer.
		m_model_buffer.UpdateData(m_device_context, XMMatrixTranspose(box_to_view));
		// Bind the model buffer.
		m_model_buffer.Bind< Pipeline::VS >(m_device_context, SLOT_CBUFFER_MODEL);
	}

	void XM_CALLCONV BoundingVolumePass::Render(const Scene &scene, 
												FXMMATRIX world_to_projection, 
												CXMMATRIX world_to_view) {
		// Bind the fixed state.
		BindFixedState();
		
		// Bind the light color data.
		BindLightColorData();
		
		// Process the omni lights.
		scene.ForEach< OmniLight >([this, world_to_projection, world_to_view](const OmniLight &light) {
			if (State::Active != light.GetState()) {
				return;
			}
			
			const auto &transform           = light.GetOwner()->GetTransform();
			const auto object_to_world      = transform.GetObjectToWorldMatrix();
			const auto object_to_projection = object_to_world * world_to_projection;

			// Apply view frustum culling.
			if (BoundingFrustum::Cull(object_to_projection, light.GetBoundingSphere())) {
				return;
			}

			const auto &aabb                = light.GetAABB();
			
			const LocalTransform box_transform(aabb.Centroid(), g_XMZero, aabb.Diagonal());

			const auto object_to_view       = object_to_world * world_to_view;
			const auto box_to_view          = box_transform.GetObjectToParentMatrix() * object_to_view;

			// Bind the model data.
			BindModelData(box_to_view);
			// Draw the line cube.
			Pipeline::Draw(m_device_context, 24u, 0u);
		});

		// Process the spot lights.
		scene.ForEach< SpotLight >([this, world_to_projection, world_to_view](const SpotLight &light) {
			if (State::Active != light.GetState()) {
				return;
			}
			
			const auto &transform           = light.GetOwner()->GetTransform();
			const auto object_to_world      = transform.GetObjectToWorldMatrix();
			const auto object_to_projection = object_to_world * world_to_projection;
			const auto &aabb                = light.GetAABB();

			// Apply view frustum culling.
			if (BoundingFrustum::Cull(object_to_projection, aabb)) {
				return;
			}

			const LocalTransform box_transform(aabb.Centroid(), g_XMZero, aabb.Diagonal());

			const auto object_to_view       = object_to_world * world_to_view;
			const auto box_to_view          = box_transform.GetObjectToParentMatrix() * object_to_view;

			// Bind the model data.
			BindModelData(box_to_view);
			// Draw the line cube.
			Pipeline::Draw(m_device_context, 24u, 0u);
		});

		// Bind the model color data.
		BindModelColorData();

		// Process the models.
		scene.ForEach< Model >([this, world_to_projection, world_to_view](const Model &model) {
			if (State::Active != model.GetState()) {
				return;
			}
			
			const auto &transform           = model.GetOwner()->GetTransform();
			const auto object_to_world      = transform.GetObjectToWorldMatrix();
			const auto object_to_projection = object_to_world * world_to_projection;
			const auto &aabb                = model.GetAABB();

			// Apply view frustum culling.
			if (BoundingFrustum::Cull(object_to_projection, aabb)) {
				return;
			}

			const LocalTransform box_transform(aabb.Centroid(), g_XMZero, aabb.Diagonal());

			const auto object_to_view       = object_to_world * world_to_view;
			const auto box_to_view          = box_transform.GetObjectToParentMatrix() * object_to_view;

			// Bind the model data.
			BindModelData(box_to_view);
			// Draw the line cube.
			Pipeline::Draw(m_device_context, 24u, 0u);
		});
	}
}