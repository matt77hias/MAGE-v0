#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "memory\memory.hpp"
#include "math\math.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Defines
//-----------------------------------------------------------------------------
#pragma region

#define MAGE_DEFAULT_CAMERA_NEAR_Z 0.01f
#define MAGE_DEFAULT_CAMERA_FAR_Z 100.0f

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 A class of cameras.
	 */
	class Camera {

	public:

		//---------------------------------------------------------------------
		// Destructors
		//---------------------------------------------------------------------

		/**
		 Destructs this camera.
		 */
		virtual ~Camera() = default;

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given camera to this camera.

		 @param[in]		camera
						A reference to the camera to copy.
		 @return		A reference to the copy of the given camera
						(i.e. this camera).
		 */
		Camera &operator=(const Camera &camera) = default;

		/**
		 Moves the given camera to this camera.

		 @param[in]		camera
						A reference to the camera to move.
		 @return		A reference to the moved camera
						(i.e. this camera).
		 */
		Camera &operator=(Camera &&camera) = default;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Clones this camera.

		 @return		A pointer to the clone of this camera.
		 */
		SharedPtr< Camera > Clone() {
			return std::static_pointer_cast< Camera >(CloneImplementation());
		}

		/**
		 Returns the position of the near z-plane of this camera in camera space.

		 @return		The position of the near z-plane of this camera.
		 */
		float GetNearZ() const {
			return m_near_z;
		}
		
		/**
		 Sets the position of the near z-plane of this camera to the given value.

		 @param[in]		near_z
						The position of the near z-plane in camera space.
		 @return		A reference to this camera in camera space.
		 */
		Camera &SetNearZ(float near_z) {
			m_near_z = near_z;
			return (*this);
		}
		
		/**
		 Returns the position of the far z-plane of this camera in camera space.

		 @return		The position of the far z-plane of this camera.
		 */
		float GetFarZ() const {
			return m_far_z;
		}
		
		/**
		 Sets the position of the far z-plane of this camera to the given value.

		 @param[in]		far_z
						The position of the far z-plane in camera space.
		 @return		A reference to this camera in camera space.
		 */
		Camera &SetFarZ(float far_z) {
			m_far_z = far_z;
			return (*this);
		}
		
		/**
		 Sets the position of the near and far z-plane of this camera to the given values.

		 @param[in]		near_z
						The position of the near z-plane in camera space.
		 @param[in]		far_z
						The position of the far z-plane in camera space.
		 @return		A reference to this camera.
		 */
		Camera &SetNearAndFarZ(float near_z, float far_z) {
			m_near_z = near_z;
			m_far_z  = far_z;
			return (*this);
		}

		/**
		 Returns the view-to-projection matrix of this camera.

		 @return		The view-to-projection matrix of this camera.
		 */
		virtual XMMATRIX GetViewToProjectionMatrix() const = 0;
			
	protected:

		//---------------------------------------------------------------------
		// Constructors
		//---------------------------------------------------------------------

		/**
		 Constructs a camera.

		 @param[in]		near_z
						The position of the near z-plane in camera space.
		 @param[in]		far_z
						The position of the far z-plane in camera space.
		 */
		explicit Camera(
			float near_z = MAGE_DEFAULT_CAMERA_NEAR_Z, 
			float far_z  = MAGE_DEFAULT_CAMERA_FAR_Z)
			: m_near_z(near_z), m_far_z(far_z) {}

		/**
		 Constructs a camera from the given camera.

		 @param[in]		camera
						A reference to the camera to copy.
		 */
		Camera(const Camera &camera) = default;

		/**
		 Constructs a camera by moving the given camera.

		 @param[in]		camera
						A reference to the camera to move.
		 */
		Camera(Camera &&camera) = default;

	private:

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Clones this camera.

		 @return		A pointer to the clone of this camera.
		 */
		virtual SharedPtr< Camera > CloneImplementation() const = 0;

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 The position of the near z-plane of this camera in camera space. 
		 */
		float m_near_z;

		/**
		 The position of the far z-plane of this camera in camera space.
		 */
		float m_far_z;
	};
}