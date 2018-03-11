//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "scene\node.hpp"
#include "scene\camera\camera.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage::rendering {

	Camera::Camera(ID3D11Device& device) 
		: Component(), 
		m_buffer(device),
		m_near_z(0.01f),
		m_far_z(100.0f),
		m_lens(),
		m_viewport(),
		m_settings() {}

	Camera::Camera(Camera&& camera) noexcept = default;

	Camera::~Camera() = default;

	Camera& Camera::operator=(Camera&& camera) noexcept = default;

	void Camera::UpdateBuffer(ID3D11DeviceContext& device_context, 
							  AADescriptor desc) const {

		const auto& transform                      = GetOwner()->GetTransform();
		const auto  world_to_camera                = transform.GetWorldToObjectMatrix();
		const auto  camera_to_world                = transform.GetObjectToWorldMatrix();
		const auto  camera_to_projection           = GetCameraToProjectionMatrix();
		const auto  projection_to_camera           = GetProjectionToCameraMatrix();

		CameraBuffer buffer;
		buffer.m_world_to_camera                   = XMMatrixTranspose(world_to_camera);
		buffer.m_camera_to_projection              = XMMatrixTranspose(camera_to_projection);
		buffer.m_projection_to_camera              = XMMatrixTranspose(projection_to_camera);
		buffer.m_camera_to_world                   = XMMatrixTranspose(camera_to_world);

		const auto viewport_resolution             = m_viewport.GetResolution();
		buffer.m_viewport_top_left                 = m_viewport.GetTopLeft();
		buffer.m_viewport_resolution               = viewport_resolution;
		buffer.m_viewport_inv_resolution_minus1    = F32x2(1.0f / (viewport_resolution.m_x - 1u),
														   1.0f / (viewport_resolution.m_y - 1u));
		
		const auto ss_viewport                     = Viewport(m_viewport, desc);
		const auto ss_viewport_resolution          = ss_viewport.GetResolution();
		buffer.m_ss_viewport_top_left              = ss_viewport.GetTopLeft();
		buffer.m_ss_viewport_resolution            = ss_viewport_resolution;
		buffer.m_ss_viewport_inv_resolution_minus1 = F32x2(1.0f / (ss_viewport_resolution.m_x - 1u),
														   1.0f / (ss_viewport_resolution.m_y - 1u));
		
		buffer.m_lens_radius                       = m_lens.GetLensRadius();
		buffer.m_focal_length                      = m_lens.GetFocalLength();
		buffer.m_max_coc_radius                    = m_lens.GetMaximumCoCRadius();

		// Update the camera buffer.
		m_buffer.UpdateData(device_context, buffer);
	}
}