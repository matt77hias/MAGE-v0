//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "rendering\rendering_manager.hpp"
#include "resource\resource_factory.hpp"
#include "math\geometry\view_frustum.hpp"
#include "utils\logging\error.hpp"

// Include HLSL bindings.
#include "..\..\..\shaders\hlsl.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	DepthPass *DepthPass::Get() {
		Assert(Renderer::Get());

		return Renderer::Get()->GetDepthPass();
	}

	DepthPass::DepthPass()
		: m_device_context(Pipeline::GetImmediateDeviceContext()),
		m_opaque_vs(CreateDepthVS()),
		m_transparent_vs(CreateDepthTransparentVS()),
		m_transparent_ps(CreateDepthTransparentPS()),
		m_projection_buffer(), 
		m_opaque_model_buffer(),
		m_transparent_model_buffer(), 
		m_dissolve_buffer() {}

	DepthPass::DepthPass(DepthPass &&render_pass) noexcept = default;

	DepthPass::~DepthPass() = default;

	void DepthPass::BindOpaqueModelShaders() const noexcept {
		// Bind the vertex shader.
		m_opaque_vs->BindShader(m_device_context);
		// Bind no pixel shader.
		Pipeline::PS::BindShader(m_device_context, nullptr);
	}

	void DepthPass::BindTransparentModelShaders() const noexcept {
		// Bind the vertex shader.
		m_transparent_vs->BindShader(m_device_context);
		// Bind the pixel shader.
		m_transparent_ps->BindShader(m_device_context);
	}

	void XM_CALLCONV DepthPass::BindProjectionData(
		FXMMATRIX view_to_projection) {

		// Update the projection buffer.
		m_projection_buffer.UpdateData(m_device_context, 
			XMMatrixTranspose(view_to_projection));
		// Bind the projection buffer.
		m_projection_buffer.Bind< Pipeline::VS >(
			m_device_context, SLOT_CBUFFER_SECONDARY_CAMERA);
	}

	void XM_CALLCONV DepthPass::BindOpaqueModelData(
		FXMMATRIX object_to_view) {

		// Update the model buffer.
		m_opaque_model_buffer.UpdateData(m_device_context,
			XMMatrixTranspose(object_to_view));
		// Bind the model buffer.
		m_opaque_model_buffer.Bind< Pipeline::VS >(
			m_device_context, SLOT_CBUFFER_MODEL);
	}

	void XM_CALLCONV DepthPass::BindTransparentModelData(
		FXMMATRIX object_to_view,
		CXMMATRIX texture_transform,
		const Material &material) {

		ModelTextureTransformBuffer transform;
		transform.m_object_to_view    = XMMatrixTranspose(object_to_view);
		transform.m_texture_transform = XMMatrixTranspose(texture_transform);

		// Update the model buffer.
		m_transparent_model_buffer.UpdateData(m_device_context,
			transform);
		// Bind the model buffer.
		m_transparent_model_buffer.Bind< Pipeline::VS >(
			m_device_context, SLOT_CBUFFER_MODEL);

		// Update the dissolve buffer.
		m_dissolve_buffer.UpdateData(m_device_context,
			XMVectorSet(material.GetBaseColor().m_w, 0.0f, 0.0f, 0.0f));
		// Bind the dissolve buffer.
		m_dissolve_buffer.Bind< Pipeline::PS >(
			m_device_context, SLOT_CBUFFER_MODEL);

		// Bind the diffuse SRV.
		Pipeline::PS::BindSRV(m_device_context,
			SLOT_SRV_BASE_COLOR, material.GetBaseColorSRV());
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
		#ifdef DISSABLE_INVERTED_Z_BUFFER
		RenderingStateManager::Get()->BindLessDepthReadWriteDepthStencilState(m_device_context);
		#else  // DISSABLE_INVERTED_Z_BUFFER
		RenderingStateManager::Get()->BindGreaterDepthReadWriteDepthStencilState(m_device_context);
		#endif // DISSABLE_INVERTED_Z_BUFFER
	}

	void XM_CALLCONV DepthPass::Render(
		const Scene &scene,
		FXMMATRIX world_to_projection,
		CXMMATRIX world_to_view,
		CXMMATRIX view_to_projection) {

		// Bind the projection data.
		BindProjectionData(view_to_projection);

		// Bind the shaders.
		BindOpaqueModelShaders();

		// Process the opaque models.
		scene.ForEach< Model >([this, world_to_projection, world_to_view](const Model &model) {
			if (State::Active != model.GetState()
				|| model.GetMaterial().IsTransparant()) {
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
			BindOpaqueModelData(object_to_view);
			// Bind the model mesh.
			model.BindMesh(m_device_context);
			// Draw the model.
			model.Draw(m_device_context);
		});

		// Bind the shaders.
		BindTransparentModelShaders();

		// Process the transparent models.
		scene.ForEach< Model >([this, world_to_projection, world_to_view](const Model &model) {
			if (State::Active != model.GetState()
				|| !model.GetMaterial().IsTransparant()
				||  model.GetMaterial().GetBaseColor().m_w < TRANSPARENCY_SHADOW_THRESHOLD) {
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
			const XMMATRIX texture_transform    = model.GetTextureTransform().GetTransformMatrix();

			// Bind the model data.
			BindTransparentModelData(object_to_view, texture_transform, model.GetMaterial());
			// Bind the model mesh.
			model.BindMesh(m_device_context);
			// Draw the model.
			model.Draw(m_device_context);
		});
	}

	void XM_CALLCONV DepthPass::RenderOccluders(
		const Scene &scene,
		FXMMATRIX world_to_projection,
		CXMMATRIX world_to_view,
		CXMMATRIX view_to_projection) {

		// Bind the projection data.
		BindProjectionData(view_to_projection);

		// Bind the shaders.
		BindOpaqueModelShaders();

		// Process the opaque models.
		scene.ForEach< Model >([this, world_to_projection, world_to_view](const Model &model) {
			if (State::Active != model.GetState()
				|| model.GetMaterial().IsTransparant()
				|| !model.OccludesLight()) {
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
			BindOpaqueModelData(object_to_view);
			// Bind the model mesh.
			model.BindMesh(m_device_context);
			// Draw the model.
			model.Draw(m_device_context);
		});

		// Bind the shaders.
		BindTransparentModelShaders();

		// Process the transparent models.
		scene.ForEach< Model >([this, world_to_projection, world_to_view](const Model &model) {
			if (State::Active != model.GetState()
				|| !model.GetMaterial().IsTransparant()
				||  model.GetMaterial().GetBaseColor().m_w < TRANSPARENCY_SHADOW_THRESHOLD
				|| !model.OccludesLight()) {
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
			const XMMATRIX texture_transform    = model.GetTextureTransform().GetTransformMatrix();

			// Bind the model data.
			BindTransparentModelData(object_to_view, texture_transform, model.GetMaterial());
			// Bind the model mesh.
			model.BindMesh(m_device_context);
			// Draw the model.
			model.Draw(m_device_context);
		});
	}
}