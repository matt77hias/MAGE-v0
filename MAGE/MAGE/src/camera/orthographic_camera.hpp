#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "camera\camera.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Defines
//-----------------------------------------------------------------------------
#pragma region

#define MAGE_DEFAULT_CAMERA_ORTHOGRAPHIC_WIDTH 2.0f
#define MAGE_DEFAULT_CAMERA_ORTHOGRAPHIC_HEIGHT 2.0f

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 A class of orthographic cameras.
	 */
	class OrthographicCamera final : public Camera {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs an orthographic camera.

		 @param[in]		width
						The width of the camera projection plane in camera space.
		 @param[in]		height
						The height of the camera projection plane in camera space.
		 @param[in]		near_z
						The position of the near z-plane in camera space.
		 @param[in]		far_z
						The position of the far z-plane in camera space.
		 */
		explicit OrthographicCamera(
			float width  = MAGE_DEFAULT_CAMERA_ORTHOGRAPHIC_WIDTH,
			float height = MAGE_DEFAULT_CAMERA_ORTHOGRAPHIC_HEIGHT,
			float near_z = MAGE_DEFAULT_CAMERA_NEAR_Z,
			float far_z  = MAGE_DEFAULT_CAMERA_FAR_Z);
		
		/**
		 Constructs an orthographic camera from the given orthographic camera.

		 @param[in]		camera
						A reference to the orthographic camera to copy.
		 */
		OrthographicCamera(const OrthographicCamera &camera) = default;

		/**
		 Constructs an orthographic camera by moving the given orthographic camera.

		 @param[in]		camera
						A reference to the orthographic camera to move.
		 */
		OrthographicCamera(OrthographicCamera &&camera) = default;

		/**
		 Destructs this orthographic camera.
		 */
		virtual ~OrthographicCamera() = default;

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------	

		/**
		 Copies the given orthographic camera to this orthographic camera.

		 @param[in]		camera
						A reference to the orthographic camera to copy.
		 @return		A reference to the copy of the given orthographic camera
						(i.e. this orthographic camera).
		 */
		OrthographicCamera &operator=(const OrthographicCamera &camera) = default;
		
		/**
		 Moves the given orthographic camera to this orthographic camera.

		 @param[in]		camera
						A reference to the orthographic camera to move.
		 @return		A reference to the moved orthographic camera
						(i.e. this orthographic camera).
		 */
		OrthographicCamera &operator=(OrthographicCamera &&camera) = default;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Clones this orthographic camera.

		 @return		A pointer to the clone of this orthographic camera.
		 */
		SharedPtr< OrthographicCamera > Clone() const {
			return std::static_pointer_cast< OrthographicCamera >(CloneImplementation());
		}

		/**
		 Returns the width of the camera projection plane 
		 of this orthographic camera in camera space.

		 @return		The width of the camera projection plane
						of this orthographic camera in camera space.
		 */
		float GetWidth() const {
			return m_width;
		}

		/**
		 Sets the width of the camera projection plane 
		 of this orthographic camera to the given value.

		 @param[in]		width
						The width of the camera projection plane in camera space.
		 @return		A reference to this orthographic camera.
		 */
		OrthographicCamera &SetWidth(float width) {
			m_width = width;
			return (*this);
		}

		/**
		 Returns the height of the camera projection plane 
		 of this orthographic camera in camera space.

		 @return		The height of the camera projection plane 
						of this orthographic camera in camera space.
		 */
		float GetHeight() const {
			return m_height;
		}

		/**
		 Sets the height of the camera projection plane 
		 of this orthographic camera to the given value.

		 @param[in]		height
						The height of the camera projection plane in camera space.
		 @return		A reference to this orthographic camera.
		 */
		OrthographicCamera &SetHeight(float height) {
			m_height = height;
			return (*this);
		}

		/**
		 Sets the width and height of the camera projection plane 
		 of this orthographic camera to the given values.

		 @param[in]		width
						The width of the camera projection plane in camera space.
		 @param[in]		height
						The height of the camera projection plane in camera space.
		 @return		A reference to this orthographic camera.
		 */
		OrthographicCamera &SetWidthAndHeight(float width, float height) {
			m_width = width;
			m_height = height;
			return (*this);
		}

		/**
		 Sets the view-to-projection matrix of this orthographic camera.

		 @param[in]		width
						The width of the camera projection plane in camera space.
		 @param[in]		height
						The height of the camera projection plane in camera space.
		 @param[in]		near_z
						The position of the near z-plane in camera space.
		 @param[in]		far_z
						The position of the far z-plane in camera space.
		*/
		void SetViewToProjectionMatrix(
			float width  = MAGE_DEFAULT_CAMERA_ORTHOGRAPHIC_WIDTH,
			float height = MAGE_DEFAULT_CAMERA_ORTHOGRAPHIC_HEIGHT,
			float near_z = MAGE_DEFAULT_CAMERA_NEAR_Z, 
			float far_z  = MAGE_DEFAULT_CAMERA_FAR_Z) {
			
			SetWidthAndHeight(width, height);
			SetNearAndFarZ(near_z, far_z);
		}
	
		/**
		 Returns the view-to-projection matrix of this orthographic camera.

		 @return		The view-to-projection matrix of this orthographic camera.
		 */
		virtual XMMATRIX GetViewToProjectionMatrix() const override {
			return XMMatrixOrthographicLH(GetWidth(), GetHeight(), GetNearZ(), GetFarZ());
		}

	private:

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Clones this orthographic camera.

		 @return		A pointer to the clone of this orthographic camera.
		 */
		virtual SharedPtr< Camera > CloneImplementation() const override;

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 The width of the camera projection plane 
		 of this orthographic camera in camera space.
		 */
		float m_width;

		/**
		 The height of the camera projection plane 
		 of this orthographic camera in camera space.
		 */
		float m_height;
	};

	/**
	 Constructs an orthographic camera.

	 @param[in]		width
					The width of the camera projection plane in camera space.
	 @param[in]		height
					The height of the camera projection plane in camera space.
	 @param[in]		near_z
					The position of the near z-plane in camera space.
	 @param[in]		far_z
					The position of the far z-plane in camera space.
	 */
	SharedPtr< OrthographicCamera > CreateOrthographicCamera(
		float width  = MAGE_DEFAULT_CAMERA_ORTHOGRAPHIC_WIDTH,
		float height = MAGE_DEFAULT_CAMERA_ORTHOGRAPHIC_HEIGHT,
		float near_z = MAGE_DEFAULT_CAMERA_NEAR_Z,
		float far_z  = MAGE_DEFAULT_CAMERA_FAR_Z);
}