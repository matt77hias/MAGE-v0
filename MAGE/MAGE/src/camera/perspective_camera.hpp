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

#define MAGE_DEFAULT_CAMERA_PERSPECTIVE_FOV_Y XM_PIDIV2

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 A class of perspective cameras.
	 */
	class PerspectiveCamera final : public Camera {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a perspective camera.

		 @param[in]		aspect_ratio
						The aspect ratio.
		 @param[in]		fov_y
						The vertical field-of-view.
		 @param[in]		near_z
						The position of the near z-plane in camera space.
		 @param[in]		far_z
						The position of the far z-plane in camera space.
		 */
		explicit PerspectiveCamera(float aspect_ratio,
			float fov_y  = MAGE_DEFAULT_CAMERA_PERSPECTIVE_FOV_Y,
			float near_z = MAGE_DEFAULT_CAMERA_NEAR_Z,
			float far_z  = MAGE_DEFAULT_CAMERA_FAR_Z);

		/**
		 Constructs a perspective camera.

		 @param[in]		width
						The width.
		 @param[in]		height
						The height.
		 @param[in]		fov_y
						The vertical field-of-view.
		 @param[in]		near_z
						The position of the near z-plane in camera space.
		 @param[in]		far_z
						The position of the far z-plane in camera space.
		 */
		explicit PerspectiveCamera(float width, float height,
			float fov_y  = MAGE_DEFAULT_CAMERA_PERSPECTIVE_FOV_Y,
			float near_z = MAGE_DEFAULT_CAMERA_NEAR_Z,
			float far_z  = MAGE_DEFAULT_CAMERA_FAR_Z);

		/**
		 Constructs a perspective camera from the given perspective camera.

		 @param[in]		camera
						A reference to the perspective camera to copy.
		 */
		PerspectiveCamera(const PerspectiveCamera &camera);
		
		/**
		 Constructs a perspective camera by moving the given perspective camera.

		 @param[in]		camera
						A reference to the perspective camera to move.
		 */
		PerspectiveCamera(PerspectiveCamera &&camera);

		/**
		 Destructs this perspective camera.
		 */
		virtual ~PerspectiveCamera();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------	

		/**
		 Copies the given perspective camera to this perspective camera.

		 @param[in]		camera
						A reference to the perspective camera to copy.
		 @return		A reference to the copy of the given perspective camera
						(i.e. this perspective camera).
		 */
		PerspectiveCamera &operator=(const PerspectiveCamera &camera);

		/**
		 Moves the given perspective camera to this perspective camera.

		 @param[in]		camera
						A reference to the perspective camera to move.
		 @return		A reference to the moved perspective camera
						(i.e. this perspective camera).
		 */
		PerspectiveCamera &operator=(PerspectiveCamera &&camera);

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Clones this perspective camera.

		 @return		A pointer to the clone of this perspective camera.
		 */
		UniquePtr< PerspectiveCamera > Clone() const {
			return static_pointer_cast< PerspectiveCamera >(CloneImplementation());
		}

		/**
		 Returns the vertical field-of-view of this perspective camera.

		 @return		The vertical field-of-view of this perspective camera.
		 */
		float GetFOVY() const noexcept {
			return m_fov_y;
		}

		/**
		 Sets the vertical field-of-view of this perspective camera to the given value.

		 @param[in]		fov_y
						The vertical field-of-view.
		 @return		A reference to this perspective camera.
		 */
		PerspectiveCamera &SetFOVY(float fov_y) noexcept {
			m_fov_y = fov_y;
			return (*this);
		}

		/**
		 Returns the aspect ratio of this perspective camera.

		 @return		The aspect ratio of this perspective camera.
		 */
		float GetAspectRatio() const noexcept {
			return m_aspect_ratio;
		}

		/**
		 Sets the aspect ratio of this perspective camera to the given value.

		 @param[in]		aspect_ratio
						The aspect ratio.
		 @return		A reference to this perspective camera.
		 */
		PerspectiveCamera &SetAspectRatio(float aspect_ratio) noexcept {
			m_aspect_ratio = aspect_ratio;
			return (*this);
		}

		/**
		 Sets the aspect ratio of this perspective camera.

		 @param[in]		width
						The width.
		 @param[in]		height
						The height.
		 @return		A reference to this perspective camera.
		 */
		PerspectiveCamera &SetAspectRatio(float width, float height) noexcept {
			m_aspect_ratio = width / height;
			return (*this);
		}
	
		/**
		 Sets the view-to-projection matrix of this perspective camera.

		 @param[in]		aspect_ratio
						The aspect ratio.
		 @param[in]		fov_y
						The vertical field-of-view.
		 @param[in]		near_z
						The position of the near z-plane in camera space.
		 @param[in]		far_z
						The position of the far z-plane in camera space.
		 */
		void SetViewToProjectionMatrix(float aspect_ratio,
			float fov_y  = MAGE_DEFAULT_CAMERA_PERSPECTIVE_FOV_Y,
			float near_z = MAGE_DEFAULT_CAMERA_NEAR_Z,
			float far_z  = MAGE_DEFAULT_CAMERA_FAR_Z) noexcept {

			SetAspectRatio(aspect_ratio);
			SetFOVY(fov_y);
			SetNearAndFarZ(near_z, far_z);
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
						The position of the near z-plane in camera space.
		 @param[in]		far_z
						The position of the far z-plane in camera space.
		 */
		void SetViewToProjectionMatrix(float width, float height, 
			float fov_y  = MAGE_DEFAULT_CAMERA_PERSPECTIVE_FOV_Y,
			float near_z = MAGE_DEFAULT_CAMERA_NEAR_Z, 
			float far_z  = MAGE_DEFAULT_CAMERA_FAR_Z) noexcept {
			
			SetAspectRatio(width, height);
			SetFOVY(fov_y);
			SetNearAndFarZ(near_z, far_z);
		}

		/**
		 Returns the view-to-projection matrix of this perspective camera.

		 @return		The view-to-projection matrix of this perspective camera.
		 */
		virtual XMMATRIX GetViewToProjectionMatrix() const noexcept override {
			return XMMatrixPerspectiveFovLH(GetFOVY(), GetAspectRatio(), GetNearZ(), GetFarZ());
		}

	private:

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Clones this perspective camera.

		 @return		A pointer to the clone of this perspective camera.
		 */
		virtual UniquePtr< Camera > CloneImplementation() const override;

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 The aspect ratio of this perspective camera.
		 */
		float m_aspect_ratio;

		/**
		 The vertical field-of-view of this perspective camera.
		 */
		float m_fov_y;
	};

	/**
	 Constructs a perspective camera.
	
	 The aspect ratio will be based on the current screen resolution.

	 @pre			The current engine and its renderer must exist.
	 @param[in]		fov_y
					The vertical field-of-view.
	 @param[in]		near_z
					The position of the near z-plane in camera space.
	 @param[in]		far_z
					The position of the far z-plane in camera space.
	 */
	UniquePtr< PerspectiveCamera > CreatePerspectiveCamera(
		float fov_y  = MAGE_DEFAULT_CAMERA_PERSPECTIVE_FOV_Y,
		float near_z = MAGE_DEFAULT_CAMERA_NEAR_Z, 
		float far_z  = MAGE_DEFAULT_CAMERA_FAR_Z);
}