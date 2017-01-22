#pragma once

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	class OrthographicCamera : private Camera {

		OrthographicCamera(float width, float height,
			float near_z = MAGE_DEFAULT_CAMERA_NEAR_Z, float far_z = MAGE_DEFAULT_CAMERA_FAR_Z,
			const Transform &transform = Transform())
			: Camera(XMMatrixOrthographicLH(width, height, near_z, far_z), width, height, near_z, far_z, transform) {}
		OrthographicCamera(const OrthographicCamera &camera)
			: Camera(camera.GetViewToProjectionMatrix(), camera.GetWidth(), camera.GetHeight(), camera.GetNearZ(), camera.GetFarZ(), camera.GetTransform()) {}
		virtual ~OrthographicCamera() {}
		
		void SetViewToProjectionMatrix(float width, float height,
			float near_z = MAGE_DEFAULT_CAMERA_NEAR_Z, float far_z = MAGE_DEFAULT_CAMERA_FAR_Z) {
			
			m_width  = width;
			m_height = height;
			m_near_z = near_z;
			m_far_z  = far_z;
			
			UpdateViewToProjectionMatrix();
		}

	protected:

		virtual void UpdateViewToProjectionMatrix() {
			m_view_to_projection = XMMatrixOrthographicLH(m_width, m_height, m_near_z, m_far_z);
		}
	};
}