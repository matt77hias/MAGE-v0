#pragma once

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 A class of orthographic cameras.
	 */
	class OrthographicCamera : public Camera {

		/**
		 Constructs an orthographic camera.

		 @param[in]		width
						The width.
		 @param[in]		height
						The height.
		 @param[in]		near_z
						The position of the near z-plane.
		 @param[in]		far_z
						The position of the far z-plane.
		 */
		OrthographicCamera(float width, float height,
			float near_z = MAGE_DEFAULT_CAMERA_NEAR_Z, float far_z = MAGE_DEFAULT_CAMERA_FAR_Z)
			: Camera(width, height, near_z, far_z) {}
		
		/**
		 Constructs an orthographic camera from the given orthographic camera.

		 @param[in]		camera
						A reference to the orthographic camera.
		 */
		OrthographicCamera(const OrthographicCamera &camera)
			: Camera(camera.GetWidth(), camera.GetHeight(), camera.GetNearZ(), camera.GetFarZ()) {}

		/**
		 Destructs this orthographic camera.
		 */
		virtual ~OrthographicCamera() {}
		
		/**
		 Returns the view-to-projection matrix of this orthographic camera.

		 @return		The view-to-projection matrix of this orthographic camera.
		 */
		virtual XMMATRIX GetViewToProjectionMatrix() const override {
			return XMMatrixOrthographicLH(m_width, m_height, m_near_z, m_far_z);
		}

		/**
		 Sets the view-to-projection matrix of this orthographic camera.

		 @param[in]		width
						The width.
		 @param[in]		height
						The height.
		 @param[in]		near_z
						The position of the near z-plane.
		 @param[in]		far_z
						The position of the far z-plane.
		*/
		void SetViewToProjectionMatrix(float width, float height,
			float near_z = MAGE_DEFAULT_CAMERA_NEAR_Z, float far_z = MAGE_DEFAULT_CAMERA_FAR_Z) {
			
			m_width  = width;
			m_height = height;
			m_near_z = near_z;
			m_far_z  = far_z;
		}
	};
}