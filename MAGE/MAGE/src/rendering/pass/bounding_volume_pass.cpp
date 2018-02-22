//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "rendering\pass\bounding_volume_pass.hpp"
#include "rendering\rendering_state_manager.hpp"
#include "shader\shader_factory.hpp"

// Include HLSL bindings.
#include "hlsl.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

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

	void BoundingVolumePass::BindLightColor() {
		// The color in linear space.
		static constexpr RGBA color(1.0f, 0.0f, 0.0f, 1.0f);

		// Bind the color data.
		BindColor(color);
	}

	void BoundingVolumePass::BindModelColor() {
		// The color in linear space.
		static constexpr RGBA color(0.0f, 1.0f, 0.0f, 1.0f);

		// Bind the color data.
		BindColor(color);
	}

	void BoundingVolumePass::BindColor(const RGBA &color) {
		// Update the color buffer.
		m_color_buffer.UpdateData(m_device_context, color);
		// Bind the color buffer.
		m_color_buffer.Bind< Pipeline::PS >(m_device_context, SLOT_CBUFFER_COLOR);
	}

	void XM_CALLCONV BoundingVolumePass::BindTransform(FXMMATRIX cube_to_world) {
		// Update the transform buffer.
		m_transform_buffer.UpdateData(m_device_context, XMMatrixTranspose(cube_to_world));
		// Bind the transform buffer.
		m_transform_buffer.Bind< Pipeline::VS >(m_device_context, SLOT_CBUFFER_MODEL);
	}

	void XM_CALLCONV BoundingVolumePass::Render(const Scene &scene, 
												FXMMATRIX world_to_projection) {
		// Bind the fixed state.
		BindFixedState();
		
		// Bind the light color.
		BindLightColor();
		
		// Process the omni lights.
		scene.ForEach< OmniLight >([this, world_to_projection](const OmniLight &light) {
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

			Render(light.GetAABB(), object_to_world);
		});

		// Process the spot lights.
		scene.ForEach< SpotLight >([this, world_to_projection](const SpotLight &light) {
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

			Render(aabb, object_to_world);
		});

		// Bind the model color.
		BindModelColor();

		// Process the models.
		scene.ForEach< Model >([this, world_to_projection](const Model &model) {
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

			Render(aabb, object_to_world);
		});
	}

	void XM_CALLCONV BoundingVolumePass::Render(const AABB &aabb, 
												FXMMATRIX object_to_world) {

		const LocalTransform aabb_transform(aabb.Centroid(), g_XMZero, aabb.Diagonal());
		const auto cube_to_object = aabb_transform.GetObjectToParentMatrix();
		const auto cube_to_world  = cube_to_object * object_to_world;

		// Bind the transform.
		BindTransform(cube_to_world);
		// Draw the line cube.
		Pipeline::Draw(m_device_context, 24u, 0u);
	}
}