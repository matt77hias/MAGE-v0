//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "scene\scene.hpp"
#include "rendering\display_configuration.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Defines
//-----------------------------------------------------------------------------
#pragma region

#define MAGE_DEFAULT_NEAR_Z          0.01f
#define MAGE_DEFAULT_FAR_Z          100.0f

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	Camera::Camera() noexcept
		: Component(), 
		m_buffer(), 
		m_near_z(MAGE_DEFAULT_NEAR_Z),
		m_far_z(MAGE_DEFAULT_FAR_Z),
		m_lens(),
		m_viewport(),
		m_settings() {}

	Camera::Camera(const Camera &camera) = default;

	Camera::Camera(Camera &&camera) noexcept = default;

	Camera::~Camera() = default;

	Camera &Camera::operator=(const Camera &camera) = default;

	Camera &Camera::operator=(Camera &&camera) noexcept = default;

	[[nodiscard]] const Viewport Camera::GetSSViewport() const noexcept {
		const auto desc = DisplayConfiguration::Get()->GetAADescriptor();
		return Viewport(m_viewport, desc);
	}

	void Camera::UpdateBuffer(ID3D11DeviceContext *device_context) const {
		const auto &transform                  = GetOwner()->GetTransform();
		const auto world_to_camera             = transform.GetWorldToObjectMatrix();
		const auto camera_to_world             = transform.GetObjectToWorldMatrix();
		const auto camera_to_projection        = GetCameraToProjectionMatrix();
		const auto projection_to_camera        = GetProjectionToCameraMatrix();

		CameraBuffer buffer;
		buffer.m_world_to_camera               = XMMatrixTranspose(world_to_camera);
		buffer.m_camera_to_projection          = XMMatrixTranspose(camera_to_projection);
		buffer.m_projection_to_camera          = XMMatrixTranspose(projection_to_camera);
		buffer.m_camera_to_world               = XMMatrixTranspose(camera_to_world);

		buffer.m_viewport_top_left_x           = static_cast< U32 >(m_viewport.GetTopLeftX());
		buffer.m_viewport_top_left_y           = static_cast< U32 >(m_viewport.GetTopLeftY());
		buffer.m_viewport_width                = static_cast< U32 >(m_viewport.GetWidth());
		buffer.m_viewport_height               = static_cast< U32 >(m_viewport.GetHeight());
		buffer.m_viewport_inv_width_minus1     = 1.0f / (m_viewport.GetWidth()  - 1.0f);
		buffer.m_viewport_inv_height_minus1    = 1.0f / (m_viewport.GetHeight() - 1.0f);

		const auto ss_viewport                 = GetSSViewport();
		buffer.m_ss_viewport_top_left_x        = static_cast< U32 >(ss_viewport.GetTopLeftX());
		buffer.m_ss_viewport_top_left_y        = static_cast< U32 >(ss_viewport.GetTopLeftY());
		buffer.m_ss_viewport_width             = static_cast< U32 >(ss_viewport.GetWidth());
		buffer.m_ss_viewport_height            = static_cast< U32 >(ss_viewport.GetHeight());
		buffer.m_ss_viewport_inv_width_minus1  = 1.0f / (ss_viewport.GetWidth()  - 1.0f);
		buffer.m_ss_viewport_inv_height_minus1 = 1.0f / (ss_viewport.GetHeight() - 1.0f);

		buffer.m_lens_radius                   = m_lens.GetLensRadius();
		buffer.m_focal_length                  = m_lens.GetFocalLength();
		buffer.m_max_coc_radius                = m_lens.GetMaximumCoCRadius();

		// Update the camera buffer.
		m_buffer.UpdateData(device_context, buffer);
	}
}