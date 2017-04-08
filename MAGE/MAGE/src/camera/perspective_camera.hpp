#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "camera\camera.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 A class of perspective camera.
	 */
	class PerspectiveCamera : public Camera {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a perspective camera.

		 @param[in]		name
						A reference to the name of the perspective camera.
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
		PerspectiveCamera(const string &name, float width, float height, float fov_y = MAGE_DEFAULT_CAMERA_FOV_Y,
			float near_z = MAGE_DEFAULT_CAMERA_NEAR_Z, float far_z = MAGE_DEFAULT_CAMERA_FAR_Z)
			: Camera(name, width, height, near_z, far_z), m_fov_y(fov_y) {}

		/**
		 Constructs a perspective camera from the given perpsective camera.

		 @param[in]		camera
						A reference to the perspective camera.
		 */
		PerspectiveCamera(const PerspectiveCamera &camera) = default;
		
		/**
		 Constructs a perspective camera from the given perpsective camera.

		 @param[in]		camera
						A reference to the perspective camera.
		 */
		PerspectiveCamera(PerspectiveCamera &&camera) = default;

		/**
		 Destructs this perspective camera.
		 */
		virtual ~PerspectiveCamera() = default;

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------	

		/**
		 Copies the given perspective camera to this perspective camera.

		 @param[in]		perspective_camera
						The perspective camera.
		 */
		PerspectiveCamera &operator=(const PerspectiveCamera &perspective_camera) = default;

		/**
		 Copies the given perspective camera to this perspective camera.

		 @param[in]		perspective_camera
						The perspective camera.
		 */
		PerspectiveCamera &operator=(PerspectiveCamera &&perspective_camera) = default;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Clones this perspective camera.

		 @return		A pointer to the clone of this perspective camera.
		 */
		virtual PerspectiveCamera *Clone() const override {
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

	private:

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 The vertical field-of-view of this perspective camera.
		 */
		float m_fov_y;
	};
}