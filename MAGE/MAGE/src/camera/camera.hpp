#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "math\math.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Defines
//-----------------------------------------------------------------------------
#pragma region

#define MAGE_DEFAULT_CAMERA_NEAR_Z        0.01f
#define MAGE_DEFAULT_CAMERA_FAR_Z        100.0f
#define MAGE_DEFAULT_LIGHT_CAMERA_NEAR_Z   0.1f

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
		virtual ~Camera();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given camera to this camera.

		 @param[in]		camera
						A reference to the camera to copy.
		 @return		A reference to the copy of the given camera (i.e. this 
						camera).
		 */
		Camera &operator=(const Camera &camera);

		/**
		 Moves the given camera to this camera.

		 @param[in]		camera
						A reference to the camera to move.
		 @return		A reference to the moved camera (i.e. this camera).
		 */
		Camera &operator=(Camera &&camera);

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Clones this camera.

		 @return		A pointer to the clone of this camera.
		 */
		UniquePtr< Camera > Clone() const {
			return static_pointer_cast< Camera >(CloneImplementation());
		}

		//---------------------------------------------------------------------
		// Member Methods: Projection
		//---------------------------------------------------------------------

		/**
		 Returns the position of the near z-plane of this camera in camera 
		 view space.

		 @return		The position of the near z-plane of this camera in 
						camera view space.
		 */
		F32 GetNearZ() const noexcept {
			return m_near_z;
		}
		
		/**
		 Sets the position of the near z-plane of this camera to the given 
		 value.

		 @param[in]		near_z
						The position of the near z-plane in camera view space.
		 */
		void SetNearZ(F32 near_z) noexcept {
			m_near_z = near_z;
		}
		
		/**
		 Returns the position of the far z-plane of this camera in camera 
		 view space.

		 @return		The position of the far z-plane of this camera in 
						camera view space.
		 */
		F32 GetFarZ() const noexcept {
			return m_far_z;
		}
		
		/**
		 Sets the position of the far z-plane of this camera to the given 
		 value.

		 @param[in]		far_z
						The position of the far z-plane in camera view space.
		 */
		void SetFarZ(F32 far_z) noexcept {
			m_far_z = far_z;
		}
		
		/**
		 Sets the position of the near and far z-plane of this camera to the 
		 given values.

		 @param[in]		near_z
						The position of the near z-plane in view space.
		 @param[in]		far_z
						The position of the far z-plane in view space.
		 */
		void SetNearAndFarZ(F32 near_z, F32 far_z) noexcept {
			SetNearZ(near_z);
			SetFarZ(far_z);
		}

		/**
		 Returns the view-to-projection matrix of this camera.

		 @return		The view-to-projection matrix of this camera.
		 */
		virtual const XMMATRIX XM_CALLCONV GetViewToProjectionMatrix() const noexcept = 0;

		/**
		 Returns the projection-to-view matrix of this camera.

		 @return		The projection-to-view matrix of this camera.
		 */
		virtual const XMMATRIX XM_CALLCONV GetProjectionToViewMatrix() const noexcept = 0;

		//---------------------------------------------------------------------
		// Member Methods: Depth-of-Field
		//---------------------------------------------------------------------

		/**
		 Checks whether this camera has a finite aperture.

		 @return		@c true if this camera has a finite aperture.
						@c false otherwise.
		 */
		bool HasFiniteAperture() const noexcept {
			return 0.0f != m_lens_radius;
		}

		/**
		 Returns the lens radius of this camera in camera.

		 @return		The lens radius of this camera.
		 */
		F32 GetLensRadius() const noexcept {
			return m_lens_radius;
		}
		
		/**
		 Sets the lens radius of this camera to the given value.

		 @param[in]		lens_radius
						The lens radius.
		 */
		void SetLensRadius(F32 lens_radius) noexcept {
			m_lens_radius = lens_radius;
		}

		/**
		 Returns the focal length of this camera in camera.

		 @return		The focal length of this camera.
		 */
		F32 GetFocalLength() const noexcept {
			return m_focal_length;
		}
		
		/**
		 Sets the focal length of this camera to the given value.

		 @param[in]		focal_length
						The focal length.
		 */
		void SetFocalLength(F32 focal_length) noexcept {
			m_focal_length = focal_length;
		}

		/**
		 Returns the maximum radius of the circle of confusion of this camera in 
		 camera.

		 @return		The maximum radius of the circle of confusion of this 
						camera.
		 */
		F32 GetMaximumCoCRadius() const noexcept {
			return m_max_coc_radius;
		}
		
		/**
		 Sets the maximum radius of the circle of confusion of this camera to 
		 the given value.

		 @param[in]		max_coc_radius
						The maximum radius of the circle of confusion.
		 */
		void SetMaximumCoCRadius(F32 max_coc_radius) noexcept {
			m_max_coc_radius = max_coc_radius;
		}

	protected:

		//---------------------------------------------------------------------
		// Constructors
		//---------------------------------------------------------------------

		/**
		 Constructs a camera.

		 @param[in]		near_z
						The position of the near z-plane in view space.
		 @param[in]		far_z
						The position of the far z-plane in view space.
		 */
		explicit Camera(F32 near_z = MAGE_DEFAULT_CAMERA_NEAR_Z,
			            F32 far_z  = MAGE_DEFAULT_CAMERA_FAR_Z);

		/**
		 Constructs a camera from the given camera.

		 @param[in]		camera
						A reference to the camera to copy.
		 */
		Camera(const Camera &camera);

		/**
		 Constructs a camera by moving the given camera.

		 @param[in]		camera
						A reference to the camera to move.
		 */
		Camera(Camera &&camera);

	private:

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Clones this camera.

		 @return		A pointer to the clone of this camera.
		 */
		virtual UniquePtr< Camera > CloneImplementation() const = 0;

		//---------------------------------------------------------------------
		// Member Variables: Projection
		//---------------------------------------------------------------------

		/**
		 The position of the near z-plane of this camera in view space. 
		 */
		F32 m_near_z;

		/**
		 The position of the far z-plane of this camera in view space.
		 */
		F32 m_far_z;

		//---------------------------------------------------------------------
		// Member Variables: Depth-of-Field
		//---------------------------------------------------------------------

		/**
		 The lens radius of this camera (for depth-of-field effects).
		 */
		F32 m_lens_radius;

		/**
		 The focal length of this camera (for depth-of-field effects).
		 */
		F32 m_focal_length;

		/**
		 The maximum radius of the circle-of-confusion of this camera (for 
		 depth-of-field effects).
		 */
		F32 m_max_coc_radius;
	};
}