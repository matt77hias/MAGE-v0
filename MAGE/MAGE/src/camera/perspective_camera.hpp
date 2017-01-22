#pragma once

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	class PerspectiveCamera : private Camera {

	public:

		PerspectiveCamera(float width, float height, float fov_y = MAGE_DEFAULT_CAMERA_FOV_Y,
			float near_z = MAGE_DEFAULT_CAMERA_NEAR_Z, float far_z = MAGE_DEFAULT_CAMERA_FAR_Z,
			const Transform &transform = Transform())
			: Camera(XMMatrixOrthographicLH(width, height, near_z, far_z), width, height, near_z, far_z, transform), 
			m_fov_y(fov_y) {}
		PerspectiveCamera(const PerspectiveCamera &camera)
			: Camera(camera.GetViewToProjectionMatrix(), camera.GetWidth(), camera.GetHeight(), camera.GetNearZ(), camera.GetFarZ(), camera.GetTransform()),
			m_fov_y(camera.m_fov_y) {}
		virtual ~PerspectiveCamera() {}

		float GetFOVY() const {
			return m_fov_y;
		}
		void SetFOVY(float fov_y) {
			m_fov_y = fov_y;
			UpdateViewToProjectionMatrix();
		}
	
		void SetViewToProjectionMatrix(float width, float height, float fov_y = MAGE_DEFAULT_CAMERA_FOV_Y,
			float near_z = MAGE_DEFAULT_CAMERA_NEAR_Z, float far_z = MAGE_DEFAULT_CAMERA_FAR_Z) {
			
			m_width  = width;
			m_height = height;
			m_fov_y  = fov_y;
			m_near_z = near_z;
			m_far_z  = far_z;
			
			UpdateViewToProjectionMatrix();
		}

	protected:

		virtual void UpdateViewToProjectionMatrix() {
			m_view_to_projection = XMMatrixPerspectiveFovLH(m_fov_y, m_width / m_height, m_near_z, m_far_z);
		}

		float m_fov_y;
	};
}