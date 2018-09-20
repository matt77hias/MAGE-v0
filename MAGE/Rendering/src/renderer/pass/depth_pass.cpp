//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "renderer\pass\depth_pass.hpp"
#include "resource\shader\shader_factory.hpp"

// Include HLSL bindings.
#include "hlsl.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage::rendering {

	DepthPass::DepthPass(ID3D11Device& device,
						 ID3D11DeviceContext& device_context,
						 StateManager& state_manager,
						 ResourceManager& resource_manager)
		: m_device_context(device_context),
		m_state_manager(state_manager),
		m_opaque_vs(CreateDepthVS(resource_manager)),
		m_transparent_vs(CreateDepthTransparentVS(resource_manager)),
		m_transparent_ps(CreateDepthTransparentPS(resource_manager)),
		m_camera_buffer(device) {}

	DepthPass::DepthPass(DepthPass&& pass) noexcept = default;

	DepthPass::~DepthPass() = default;

	DepthPass& DepthPass::operator=(DepthPass&& pass) noexcept = default;

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
		m_state_manager.get().Bind(m_device_context,
								   RasterizerStateID::CounterClockwiseCulling);
		// OM: Bind the depth-stencil state.
		#ifdef DISABLE_INVERTED_Z_BUFFER
		m_state_manager.get().Bind(m_device_context,
								   DepthStencilStateID::LessDepthReadWrite);
		#else  // DISABLE_INVERTED_Z_BUFFER
		m_state_manager.get().Bind(m_device_context,
								   DepthStencilStateID::GreaterDepthReadWrite);
		#endif // DISABLE_INVERTED_Z_BUFFER
	}

	void XM_CALLCONV DepthPass::BindCamera(FXMMATRIX world_to_camera,
										   CXMMATRIX camera_to_projection) {
		SecondaryCameraBuffer buffer;
		buffer.m_world_to_camera      = XMMatrixTranspose(world_to_camera);
		buffer.m_camera_to_projection = XMMatrixTranspose(camera_to_projection);

		// Update the camera buffer.
		m_camera_buffer.UpdateData(m_device_context, buffer);
		// Bind the camera buffer.
		m_camera_buffer.Bind< Pipeline::VS >(m_device_context,
											 SLOT_CBUFFER_SECONDARY_CAMERA);
	}

	void XM_CALLCONV DepthPass::Render(const World& world,
									   FXMMATRIX world_to_camera,
									   CXMMATRIX camera_to_projection) {
		// Bind the projection data.
		BindCamera(world_to_camera, camera_to_projection);

		const auto world_to_projection = world_to_camera * camera_to_projection;

		//---------------------------------------------------------------------
		// All opaque models.
		//---------------------------------------------------------------------

		// Bind the shaders.
		BindOpaqueShaders();

		// Process the opaque models.
		world.ForEach< Model >([this, world_to_projection](const Model& model) {
			if (State::Active != model.GetState()
				|| model.GetMaterial().IsTransparant()) {
				return;
			}

			RenderOpaque(model, world_to_projection);
		});

		//---------------------------------------------------------------------
		// All transparent models.
		//---------------------------------------------------------------------

		// Bind the shaders.
		BindTransparentShaders();

		// Process the transparent models.
		world.ForEach< Model >([this, world_to_projection](const Model& model) {

			const auto& material = model.GetMaterial();

			if (State::Active != model.GetState()
				|| !material.IsTransparant()
				|| material.GetBaseColor()[3] < TRANSPARENCY_SHADOW_THRESHOLD) {
				return;
			}

			RenderTransparent(model, world_to_projection);
		});
	}

	void XM_CALLCONV DepthPass::RenderOccluders(const World& world,
												FXMMATRIX world_to_camera,
												CXMMATRIX camera_to_projection) {
		// Bind the projection data.
		BindCamera(world_to_camera, camera_to_projection);

		const auto world_to_projection = world_to_camera * camera_to_projection;

		//---------------------------------------------------------------------
		// All opaque models.
		//---------------------------------------------------------------------

		// Bind the shaders.
		BindOpaqueShaders();

		// Process the opaque models.
		world.ForEach< Model >([this, world_to_projection](const Model& model) {
			if (State::Active != model.GetState()
				|| !model.OccludesLight()
				|| model.GetMaterial().IsTransparant()) {
				return;
			}

			RenderOpaque(model, world_to_projection);
		});

		//---------------------------------------------------------------------
		// All transparent models.
		//---------------------------------------------------------------------

		// Bind the shaders.
		BindTransparentShaders();

		// Process the transparent models.
		world.ForEach< Model >([this, world_to_projection](const Model& model) {

			const auto& material = model.GetMaterial();

			if (State::Active != model.GetState()
				|| !model.OccludesLight()
				|| !material.IsTransparant()
				|| material.GetBaseColor()[3] < TRANSPARENCY_SHADOW_THRESHOLD) {
				return;
			}

			RenderTransparent(model, world_to_projection);
		});
	}

	void XM_CALLCONV DepthPass::RenderOpaque(const Model& model,
											 FXMMATRIX world_to_projection) const noexcept {

		const auto& transform            = model.GetOwner()->GetTransform();
		const auto  object_to_world      = transform.GetObjectToWorldMatrix();
		const auto  object_to_projection = object_to_world * world_to_projection;

		// Apply view frustum culling.
		if (BoundingFrustum::Cull(object_to_projection, model.GetAABB())) {
			return;
		}

		// Bind the constant buffer of the model.
		model.BindBuffer< Pipeline::VS >(m_device_context, SLOT_CBUFFER_MODEL);
		// Bind the mesh of the model.
		model.BindMesh(m_device_context);
		// Draw the model.
		model.Draw(m_device_context);
	}

	void XM_CALLCONV DepthPass::RenderTransparent(const Model& model,
												  FXMMATRIX world_to_projection) const noexcept {

		const auto& transform            = model.GetOwner()->GetTransform();
		const auto  object_to_world      = transform.GetObjectToWorldMatrix();
		const auto  object_to_projection = object_to_world * world_to_projection;

		// Apply view frustum culling.
		if (BoundingFrustum::Cull(object_to_projection, model.GetAABB())) {
			return;
		}

		// Bind the constant buffer of the model.
		model.BindBuffer< Pipeline::VS >(m_device_context, SLOT_CBUFFER_MODEL);
		model.BindBuffer< Pipeline::PS >(m_device_context, SLOT_CBUFFER_MODEL);
		// Bind the SRV of the model.
		Pipeline::PS::BindSRV(m_device_context, SLOT_SRV_BASE_COLOR,
							  model.GetMaterial().GetBaseColorSRV());
		// Bind the mesh of the model.
		model.BindMesh(m_device_context);
		// Draw the model.
		model.Draw(m_device_context);
	}
}