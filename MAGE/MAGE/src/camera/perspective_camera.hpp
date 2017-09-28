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

	//-------------------------------------------------------------------------
	// Perspective Utilities
	//-------------------------------------------------------------------------

	/**
	 Returns the horizontal field-of-view corresponding to the given aspect 
	 ratio and vertical field-of-view.

	 @param[in]		aspect_ratio
					The aspect ratio.
	 @param[in]		fov_y
					The vertical field-of-view.
	 @return		The horizontal field-of-view corresponding to the given 
					aspect ratio and vertical field-of-view.
	 */
	inline F32 FOVXFromFOVY(F32 aspect_ratio, F32 fov_y) noexcept {
		return 2.0f * atanf(aspect_ratio * tanf(0.5f * fov_y));
	}

	/**
	 Returns the vertical field-of-view corresponding to the given aspect 
	 ratio and horizontal field-of-view.

	 @param[in]		aspect_ratio
					The aspect ratio.
	 @param[in]		fov_x
					The horizontal field-of-view.
	 @return		The vertical field-of-view corresponding to the given 
					aspect ratio and horizontal field-of-view.
	 */
	inline F32 FOVYFromFOVX(F32 aspect_ratio, F32 fov_x) noexcept {
		return 2.0f * atanf(tanf(0.5f * fov_x) / aspect_ratio);
	}

	/**
	 Returns the aspect ratio corresponding to the given width and height.

	 @param[in]		width
					The width.
	 @param[in]		height
					The height.
	 @return		The aspect ratio corresponding to the given width and 
					height.
	 */
	inline F32 AspectRatioFromWidthAndHeight(F32 width, F32 height) noexcept {
		return width / height;
	}

	/**
	 Returns the aspect ratio corresponding to the given horizontal and 
	 vertical field-of-views.

	 @param[in]		fov_x
					The horizontal field-of-view.
	 @param[in]		fov_y
					The vertical field-of-view.
	 @return		The aspect ratio corresponding to the given horizontal and 
					vertical field-of-views.
	 */
	inline F32 AspectRatioFromFOVs(F32 fov_x, F32 fov_y) noexcept {
		return tanf(0.5f * fov_x) / tanf(0.5f * fov_y);
	}

	//-------------------------------------------------------------------------
	// PerspectiveCamera
	//-------------------------------------------------------------------------

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

		 The aspect ratio will be based on the current screen resolution.

		 @pre			The renderer associated with the current engine must 
						be loaded.
		 @param[in]		fov_y
						The vertical field-of-view.
		 */
		explicit PerspectiveCamera(
			F32 fov_y = MAGE_DEFAULT_CAMERA_PERSPECTIVE_FOV_Y);

		/**
		 Constructs a perspective camera.

		 The aspect ratio will be based on the current screen resolution.

		 @pre			The renderer associated with the current engine 
						must be loaded.
		 @param[in]		fov_y
						The vertical field-of-view.
		 @param[in]		near_z
						The position of the near z-plane in camera space.
		 @param[in]		far_z
						The position of the far z-plane in camera space.
		 */
		explicit PerspectiveCamera(
			F32 fov_y, F32 near_z, F32 far_z);

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
		explicit PerspectiveCamera(F32 aspect_ratio,
			F32 fov_y, F32 near_z, F32 far_z);

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
		explicit PerspectiveCamera(F32 width, F32 height,
			F32 fov_y, F32 near_z, F32 far_z);

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
		 @return		A reference to the copy of the given perspective 
						camera (i.e. this perspective camera).
		 */
		PerspectiveCamera &operator=(const PerspectiveCamera &camera);

		/**
		 Moves the given perspective camera to this perspective camera.

		 @param[in]		camera
						A reference to the perspective camera to move.
		 @return		A reference to the moved perspective camera (i.e. this 
						perspective camera).
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
		 Returns the horizontal field-of-view of this perspective camera.

		 @return		The horizontal field-of-view of this perspective 
						camera.
		 */
		F32 GetFOVX() const noexcept {
			return FOVXFromFOVY(m_aspect_ratio, m_fov_y);
		}

		/**
		 Returns the vertical field-of-view of this perspective camera.

		 @return		The vertical field-of-view of this perspective 
						camera.
		 */
		F32 GetFOVY() const noexcept {
			return m_fov_y;
		}

		/**
		 Sets the vertical field-of-view of this perspective camera to the 
		 given value.

		 @param[in]		fov_y
						The vertical field-of-view.
		 */
		void SetFOVY(F32 fov_y) noexcept {
			m_fov_y = fov_y;
		}

		/**
		 Returns the aspect ratio of this perspective camera.

		 @return		The aspect ratio of this perspective camera.
		 */
		F32 GetAspectRatio() const noexcept {
			return m_aspect_ratio;
		}

		/**
		 Sets the aspect ratio of this perspective camera to the given 
		 value.

		 @param[in]		aspect_ratio
						The aspect ratio.
		 */
		void SetAspectRatio(F32 aspect_ratio) noexcept {
			m_aspect_ratio = aspect_ratio;
		}

		/**
		 Sets the aspect ratio of this perspective camera.

		 @param[in]		width
						The width.
		 @param[in]		height
						The height.
		 */
		void SetAspectRatio(F32 width, F32 height) noexcept {
			SetAspectRatio(AspectRatioFromWidthAndHeight(width, height));
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
		void SetViewToProjectionMatrix(F32 aspect_ratio,
			F32 fov_y, F32 near_z, F32 far_z) noexcept {

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
		void SetViewToProjectionMatrix(F32 width, F32 height, 
			F32 fov_y, F32 near_z, F32 far_z) noexcept {
			
			SetAspectRatio(width, height);
			SetFOVY(fov_y);
			SetNearAndFarZ(near_z, far_z);
		}
		
		/**
		 Returns the view-to-projection matrix of this perspective camera.

		 @return		The view-to-projection matrix of this perspective 
						camera.
		 */
		virtual const XMMATRIX GetViewToProjectionMatrix() const noexcept override {
			return XMMatrixPerspectiveFovLH(
				GetFOVY(), GetAspectRatio(), GetNearZ(), GetFarZ());
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
		F32 m_aspect_ratio;

		/**
		 The vertical field-of-view of this perspective camera.
		 */
		F32 m_fov_y;
	};
}