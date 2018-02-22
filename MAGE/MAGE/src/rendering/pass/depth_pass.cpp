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

	DepthPass::DepthPass()
		: m_device_context(Pipeline::GetImmediateDeviceContext()),
		m_opaque_vs(CreateDepthVS()),
		m_transparent_vs(CreateDepthTransparentVS()),
		m_transparent_ps(CreateDepthTransparentPS()),
		m_projection_buffer(), 
		m_opaque_model_buffer(),
		m_transparent_model_buffer(), 
		m_dissolve_buffer() {}

	DepthPass::DepthPass(DepthPass &&pass) noexcept = default;

	DepthPass::~DepthPass() = default;

	void DepthPass::BindOpaqueShaders() const noexcept {
		// Bind the vertex shader.
		m_opaque_vs->BindShader(m_device_context);
		// Bind no pixel shader.
		Pipeline::PS::BindShader(m_device_context, nullptr);
	}

	void DepthPass::BindTransparentShaders() const noexcept {
		// Bind the vertex shader.
		m_transparent_vs->BindShader(m_device_context);
		// Bind the pixel shader.
		m_transparent_ps->BindShader(m_device_context);
	}

	void DepthPass::BindFixedState() const noexcept {
		// HS: Bind the hull shader.
		Pipeline::HS::BindShader(m_device_context, nullptr);
		// DS: Bind the domain shader.
		Pipeline::DS::BindShader(m_device_context, nullptr);
		// GS: Bind the geometry shader.
		Pipeline::GS::BindShader(m_device_context, nullptr);
		// RS: Bind the rasterization state.
		RenderingStateManager::Get()->BindCullCounterClockwiseRasterizerState(m_device_context);
		// OM: Bind the depth-stencil state.
		#ifdef DISABLE_INVERTED_Z_BUFFER
		RenderingStateManager::Get()->BindLessDepthReadWriteDepthStencilState(m_device_context);
		#else  // DISABLE_INVERTED_Z_BUFFER
		RenderingStateManager::Get()->BindGreaterDepthReadWriteDepthStencilState(m_device_context);
		#endif // DISABLE_INVERTED_Z_BUFFER
	}

	void XM_CALLCONV DepthPass
		::BindProjectionData(FXMMATRIX view_to_projection) {

		// Update the projection buffer.
		m_projection_buffer.UpdateData(m_device_context, 
									   XMMatrixTranspose(view_to_projection));
		// Bind the projection buffer.
		m_projection_buffer.Bind< Pipeline::VS >(m_device_context, 
												 SLOT_CBUFFER_SECONDARY_CAMERA);
	}

	void XM_CALLCONV DepthPass
		::BindOpaqueModelData(FXMMATRIX object_to_view) {

		// Update the model buffer.
		m_opaque_model_buffer.UpdateData(m_device_context, 
										 XMMatrixTranspose(object_to_view));
		// Bind the model buffer.
		m_opaque_model_buffer.Bind< Pipeline::VS >(m_device_context, 
												   SLOT_CBUFFER_MODEL);
	}

	void XM_CALLCONV DepthPass
		::BindTransparentModelData(FXMMATRIX object_to_view, 
								   CXMMATRIX texture_transform, 
								   const Material &material) {

		ModelTextureTransformBuffer transform;
		transform.m_object_to_view    = XMMatrixTranspose(object_to_view);
		transform.m_texture_transform = XMMatrixTranspose(texture_transform);

		// Update the model buffer.
		m_transparent_model_buffer.UpdateData(m_device_context, transform);
		// Bind the model buffer.
		m_transparent_model_buffer.Bind< Pipeline::VS >(m_device_context, 
														SLOT_CBUFFER_MODEL);
		// Update the dissolve buffer.
		m_dissolve_buffer.UpdateData(m_device_context,
			XMVectorSet(material.GetBaseColor().m_w, 0.0f, 0.0f, 0.0f));
		// Bind the dissolve buffer.
		m_dissolve_buffer.Bind< Pipeline::PS >(m_device_context, 
											   SLOT_CBUFFER_MODEL);
		// Bind the diffuse SRV.
		Pipeline::PS::BindSRV(m_device_context, SLOT_SRV_BASE_COLOR, 
							  material.GetBaseColorSRV());
	}

	void XM_CALLCONV DepthPass::Render(const Scene &scene, 
									   FXMMATRIX world_to_projection, 
									   CXMMATRIX world_to_view, 
									   CXMMATRIX view_to_projection) {
		// Bind the projection data.
		BindProjectionData(view_to_projection);

		// Bind the shaders.
		BindOpaqueShaders();

		// Process the opaque models.
		scene.ForEach< Model >([this, world_to_projection, world_to_view](const Model &model) {
			if (State::Active != model.GetState()
				|| model.GetMaterial().IsTransparant()) {
				return;
			}
			
			const auto &transform           = model.GetOwner()->GetTransform();
			const auto object_to_world      = transform.GetObjectToWorldMatrix();
			const auto object_to_projection = object_to_world * world_to_projection;

			// Apply view frustum culling.
			if (BoundingFrustum::Cull(object_to_projection, model.GetAABB())) {
				return;
			}

			const auto object_to_view       = object_to_world * world_to_view;

			// Bind the model data.
			BindOpaqueModelData(object_to_view);
			// Bind the model mesh.
			model.BindMesh(m_device_context);
			// Draw the model.
			model.Draw(m_device_context);
		});

		// Bind the shaders.
		BindTransparentShaders();

		// Process the transparent models.
		scene.ForEach< Model >([this, world_to_projection, world_to_view](const Model &model) {
			if (State::Active != model.GetState()
				|| !model.GetMaterial().IsTransparant()
				||  model.GetMaterial().GetBaseColor().m_w < TRANSPARENCY_SHADOW_THRESHOLD) {
				return;
			}
			
			const auto &transform           = model.GetOwner()->GetTransform();
			const auto object_to_world      = transform.GetObjectToWorldMatrix();
			const auto object_to_projection = object_to_world * world_to_projection;

			// Apply view frustum culling.
			if (BoundingFrustum::Cull(object_to_projection, model.GetAABB())) {
				return;
			}

			const auto object_to_view       = object_to_world * world_to_view;
			const auto texture_transform    = model.GetTextureTransform().GetTransformMatrix();

			// Bind the model data.
			BindTransparentModelData(object_to_view, texture_transform, model.GetMaterial());
			// Bind the model mesh.
			model.BindMesh(m_device_context);
			// Draw the model.
			model.Draw(m_device_context);
		});
	}

	void XM_CALLCONV DepthPass::RenderOccluders(const Scene &scene, 
												FXMMATRIX world_to_projection, 
												CXMMATRIX world_to_view, 
												CXMMATRIX view_to_projection) {
		// Bind the projection data.
		BindProjectionData(view_to_projection);

		// Bind the shaders.
		BindOpaqueShaders();

		// Process the opaque models.
		scene.ForEach< Model >([this, world_to_projection, world_to_view](const Model &model) {
			if (State::Active != model.GetState()
				|| model.GetMaterial().IsTransparant()
				|| !model.OccludesLight()) {
				return;
			}
			
			const auto &transform           = model.GetOwner()->GetTransform();
			const auto object_to_world      = transform.GetObjectToWorldMatrix();
			const auto object_to_projection = object_to_world * world_to_projection;

			// Apply view frustum culling.
			if (BoundingFrustum::Cull(object_to_projection, model.GetAABB())) {
				return;
			}

			const auto object_to_view       = object_to_world * world_to_view;

			// Bind the model data.
			BindOpaqueModelData(object_to_view);
			// Bind the model mesh.
			model.BindMesh(m_device_context);
			// Draw the model.
			model.Draw(m_device_context);
		});

		// Bind the shaders.
		BindTransparentShaders();

		// Process the transparent models.
		scene.ForEach< Model >([this, world_to_projection, world_to_view](const Model &model) {
			if (State::Active != model.GetState()
				|| !model.GetMaterial().IsTransparant()
				||  model.GetMaterial().GetBaseColor().m_w < TRANSPARENCY_SHADOW_THRESHOLD
				|| !model.OccludesLight()) {
				return;
			}
			
			const auto &transform           = model.GetOwner()->GetTransform();
			const auto object_to_world      = transform.GetObjectToWorldMatrix();
			const auto object_to_projection = object_to_world * world_to_projection;

			// Apply view frustum culling.
			if (BoundingFrustum::Cull(object_to_projection, model.GetAABB())) {
				return;
			}

			const auto object_to_view       = object_to_world * world_to_view;
			const auto texture_transform    = model.GetTextureTransform().GetTransformMatrix();

			// Bind the model data.
			BindTransparentModelData(object_to_view, texture_transform, model.GetMaterial());
			// Bind the model mesh.
			model.BindMesh(m_device_context);
			// Draw the model.
			model.Draw(m_device_context);
		});
	}
}