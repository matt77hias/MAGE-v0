#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "world\world_object.hpp"

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
	 A class of camera.
	 */
	class Camera : public WorldObject {

	public:

		//---------------------------------------------------------------------
		// Destructors
		//---------------------------------------------------------------------

		/**
		 Destructs this camera.
		 */
		virtual ~Camera() = default;

		/**
		 Copies the given camera to this camera.

		 @param[in]		camera
						A reference to the orthographic camera.
		 */
		Camera &operator=(const Camera &camera) = default;

		/**
		 Copies the given camera to this camera.

		 @param[in]		camera
						A reference to the orthographic camera.
		 */
		Camera &operator=(Camera &&camera) = default;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Clones this camera.

		 @return		A pointer to the clone of this camera.
		 */
		virtual Camera *Clone() const = 0;

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

		 @param[in]		name
						A reference to the name of the camera.
		 @param[in]		near_z
						The position of the near z-plane in camera space.
		 @param[in]		far_z
						The position of the far z-plane in camera space.
		 */
		explicit Camera(const string &name,
			float near_z = MAGE_DEFAULT_CAMERA_NEAR_Z, 
			float far_z  = MAGE_DEFAULT_CAMERA_FAR_Z)
			: WorldObject(name), 
			m_near_z(near_z), m_far_z(far_z) {}

		/**
		 Constructs a camera from the given camera.

		 @param[in]		camera
						The camera.
		 */
		Camera(const Camera &camera) = default;

		/**
		 Constructs a camera from the given camera.

		 @param[in]		camera
						The camera.
		 */
		Camera(Camera &&camera) = default;

	private:

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 The position of the near z-plane in camera space. 
		 */
		float m_near_z;

		/**
		 The position of the far z-plane in camera space.
		 */
		float m_far_z;
	};
}