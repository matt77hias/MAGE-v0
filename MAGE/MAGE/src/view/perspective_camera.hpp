#pragma once

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 A class of perspective camera.
	 */
	class PerspectiveCamera : public Camera {

	public:

		/**
		 Constructs a perspective camera.

		 @param[in]		width
						The width.
		 @param[in]		height
						The height.
		 @param[in]		fov_y
						The vertical field-of-view.
		 @param[in]		near_z
						The position of the near z-plane.
		 @param[in]		far_z
						The position of the far z-plane.
		 */
		PerspectiveCamera(float width, float height, float fov_y = MAGE_DEFAULT_CAMERA_FOV_Y,
			float near_z = MAGE_DEFAULT_CAMERA_NEAR_Z, float far_z = MAGE_DEFAULT_CAMERA_FAR_Z)
			: Camera(width, height, near_z, far_z), m_fov_y(fov_y) {}

		/**
		 Constructs a perspective camera from the given perpsective camera.

		 @param[in]		camera
						A reference to the perspective camera.
		 */
		PerspectiveCamera(const PerspectiveCamera &camera)
			: Camera(camera), m_fov_y(camera.m_fov_y) {}
		
		/**
		 Destructs this perspective camera.
		 */
		virtual ~PerspectiveCamera() {}

		/**
		 Clones this perspective camera.

		 @return		A pointer to the clone of this perspective camera.
		 */
		virtual Camera *Clone() const {
			return new PerspectiveCamera(*this);
		}

		/**
		 Returns the vertical field-of-view of this perspective camera.

		 @return		The vertical field-of-view of this perspective camera.
		 */
		float GetFOVY() const {
			return m_fov_y;
		}

		/**
		 Sets the vertical field-of-view of this perspective camera to the given value.

		 @param[in]		fov_y
						The vertical field-of-view.
		 @return		A reference to this perspective camera.
		 */
		Camera &SetFOVY(float fov_y) {
			m_fov_y = fov_y;
			return (*this);
		}

		/**
		 Returns the aspect ratio of this perspective camera.

		 @return		The aspect ratio of this perspective camera.
		 */
		float GetAspectRatio() const {
			return GetWidth() / GetHeight();
		}
	
		/**
		 Returns the view-to-projection matrix of this perspective camera.

		 @return		The view-to-projection matrix of this perspective camera.
		 */
		virtual XMMATRIX GetViewToProjectionMatrix() const override {
			return XMMatrixPerspectiveFovLH(GetFOVY(), GetAspectRatio(), GetNearZ(), GetFarZ());
		}

		/**
		 Sets the view-to-projection matrix of this perspective camera.

		 @param[in]		width
						The width.
		 @param[in]		height
						The height.
		 @param[in]		fov_y
						The vertical field-of-view.
		 @param[in]		near_z
						The position of the near z-plane.
		 @param[in]		far_z
						The position of the far z-plane.
		 */
		void SetViewToProjectionMatrix(float width, float height, float fov_y = MAGE_DEFAULT_CAMERA_FOV_Y,
			float near_z = MAGE_DEFAULT_CAMERA_NEAR_Z, float far_z = MAGE_DEFAULT_CAMERA_FAR_Z) {
			
			SetWidthAndHeight(width, height);
			SetFOVY(fov_y);
			SetNearAndFarZ(near_z, far_z);
		}

	protected:

		/**
		 The vertical field-of-view of this perspective camera. 
		 */
		float m_fov_y;
	};
}