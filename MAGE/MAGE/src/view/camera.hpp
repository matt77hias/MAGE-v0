#pragma once

//-----------------------------------------------------------------------------
// Engine Defines
//-----------------------------------------------------------------------------
#pragma region

#define MAGE_DEFAULT_CAMERA_FOV_Y XM_PIDIV2
#define MAGE_DEFAULT_CAMERA_NEAR_Z 0.01f
#define MAGE_DEFAULT_CAMERA_FAR_Z 100.0f

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 A class of camera.
	 */
	class Camera {

	public:

		/**
		 Destructs this camera.
		 */
		virtual ~Camera() {}

		/**
		 Returns the width of this camera.

		 @return		The width of this camera.
		 */
		float GetWidth() const {
			return m_width;
		}
		
		/**
		 Sets the width of this camera to the given value.

		 @param[in]		width
						The width.
		 @return		A reference to this camera.
		 */
		Camera &SetWidth(float width) {
			m_width = width;
			return (*this);
		}
		
		/**
		 Returns the height of this camera.

		 @return		The height of this camera.
		 */
		float GetHeight() const {
			return m_height;
		}
		
		/**
		 Sets the height of this camera to the given value.

		 @param[in]		height
						The height.
		 @return		A reference to this camera.
		 */
		Camera &SetHeight(float height) {
			m_height = height;
			return (*this);
		}
		
		/**
		 Sets the width and height of this camera to the given values.

		 @param[in]		width
						The width.
		 @param[in]		height
						The height.
		 @return		A reference to this camera.
		 */
		Camera &SetWidthAndHeight(float width, float height) {
			m_width = width;
			m_height = height;
			return (*this);
		}

		/**
		 Returns the position of the near z-plane of this camera.

		 @return		The position of the near z-plane of this camera.
		 */
		float GetNearZ() const {
			return m_near_z;
		}
		
		/**
		 Sets the position of the near z-plane of this camera to the given value.

		 @param[in]		near_z
						The position of the near z-plane.
		 @return		A reference to this camera.
		 */
		Camera &SetNearZ(float near_z) {
			m_near_z = near_z;
			return (*this);
		}
		
		/**
		 Returns the position of the far z-plane of this camera.

		 @return		The position of the far z-plane of this camera.
		 */
		float GetFarZ() const {
			return m_far_z;
		}
		
		/**
		 Sets the position of the far z-plane of this camera to the given value.

		 @param[in]		near_z
						The position of the near z-plane.
		 @return		A reference to this camera.
		 */
		Camera &SetFarZ(float far_z) {
			m_far_z = far_z;
			return (*this);
		}
		
		/**
		 Sets the position of the near and far z-plane of this camera to the given values.

		 @param[in]		near_z
						The position of the near z-plane.
		 @param[in]		far_z
						The position of the far z-plane.
		 @return		A reference to this camera.
		 */
		Camera &SetNearAndFarZ(float near_z, float far_z) {
			m_near_z = near_z;
			m_far_z = far_z;
			return (*this);
		}

		/**
		 Returns the view-to-projection matrix of this camera.

		 @return		The view-to-projection matrix of this camera.
		 */
		virtual XMMATRIX GetViewToProjectionMatrix() const = 0;
			
	protected:

		/**
		 Constructs a camera.

		 @param[in]		width
						The width.
		 @param[in]		height
						The height.
		 @param[in]		near_z
						The position of the near z-plane.
		 @param[in]		far_z
						The position of the far z-plane.
		 */
		Camera(float width, float height, float near_z = MAGE_DEFAULT_CAMERA_NEAR_Z, float far_z = MAGE_DEFAULT_CAMERA_FAR_Z)
			: m_width(width), m_height(height), m_near_z(near_z), m_far_z(far_z) {}

		/**
		 The width of this camera.
		 */
		float m_width;

		/**
		 The height of this camera.
		 */
		float m_height;

		/**
		 The position of the near z-plane. 
		 */
		float m_near_z;

		/**
		 The position of the far z-plane.
		 */
		float m_far_z;
	};
}