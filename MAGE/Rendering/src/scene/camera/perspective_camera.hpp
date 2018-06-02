#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "scene\camera\camera.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage::rendering {

	//-------------------------------------------------------------------------
	// Perspective Utilities
	//-------------------------------------------------------------------------
	#pragma region

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
	[[nodiscard]]
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
	[[nodiscard]]
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
	[[nodiscard]]
	constexpr F32 AspectRatioFromWidthAndHeight(F32 width, F32 height) noexcept {
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
	[[nodiscard]]
	inline F32 AspectRatioFromFOVs(F32 fov_x, F32 fov_y) noexcept {
		return tanf(0.5f * fov_x) / tanf(0.5f * fov_y);
	}

	#pragma endregion

	//-------------------------------------------------------------------------
	// PerspectiveCamera
	//-------------------------------------------------------------------------
	#pragma region

	#pragma warning( push )
	#pragma warning( disable : 4324 ) // Added padding.

	/**
	 A class of perspective cameras.
	 */
	class alignas(16) PerspectiveCamera final : public Camera {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a perspective camera.

		 @param[in]		device
						A reference to the device.
		 */
		PerspectiveCamera(ID3D11Device& device);

		/**
		 Constructs a perspective camera from the given perspective camera.

		 @param[in]		camera
						A reference to the perspective camera to copy.
		 */
		PerspectiveCamera(const PerspectiveCamera& camera) = delete;
		
		/**
		 Constructs a perspective camera by moving the given perspective camera.

		 @param[in]		camera
						A reference to the perspective camera to move.
		 */
		PerspectiveCamera(PerspectiveCamera&& camera) noexcept;

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
		PerspectiveCamera& operator=(const PerspectiveCamera& camera) = delete;

		/**
		 Moves the given perspective camera to this perspective camera.

		 @param[in]		camera
						A reference to the perspective camera to move.
		 @return		A reference to the moved perspective camera (i.e. this 
						perspective camera).
		 */
		PerspectiveCamera& operator=(PerspectiveCamera&& camera) noexcept;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Returns the horizontal field-of-view of this perspective camera.

		 @return		The horizontal field-of-view of this perspective 
						camera.
		 */
		[[nodiscard]]
		F32 GetFOVX() const noexcept {
			return FOVXFromFOVY(m_aspect_ratio, m_fov_y);
		}

		/**
		 Returns the vertical field-of-view of this perspective camera.

		 @return		The vertical field-of-view of this perspective 
						camera.
		 */
		[[nodiscard]]
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
		[[nodiscard]]
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
		 Returns the camera-to-projection matrix of this perspective camera.

		 @return		The camera-to-projection matrix of this perspective 
						camera.
		 */
		[[nodiscard]]
		virtual const XMMATRIX XM_CALLCONV 
			GetCameraToProjectionMatrix() const noexcept override {

			const auto clipping_planes = GetClippingPlanes();

			#ifdef DISABLE_INVERTED_Z_BUFFER
			const auto near_plane = clipping_planes[0];
			const auto far_plane  = clipping_planes[1];
			#else  // DISABLE_INVERTED_Z_BUFFER
			const auto near_plane = clipping_planes[1];
			const auto far_plane  = clipping_planes[0];
			#endif // DISABLE_INVERTED_Z_BUFFER

			return XMMatrixPerspectiveFovLH(GetFOVY(), 
											GetAspectRatio(), 
											near_plane,
											far_plane);
		}

		/**
		 Returns the projection-to-camera matrix of this perspective camera.

		 @return		The projection-to-camera matrix of this perspective 
						camera.
		 */
		[[nodiscard]]
		virtual const XMMATRIX XM_CALLCONV 
			GetProjectionToCameraMatrix() const noexcept override {

			const auto camera_to_projection = GetCameraToProjectionMatrix();

			const auto m00 = 1.0f / XMVectorGetX(camera_to_projection.r[0]);
			const auto m11 = 1.0f / XMVectorGetY(camera_to_projection.r[1]);
			const auto m23 = 1.0f / XMVectorGetZ(camera_to_projection.r[3]);
			const auto m33 = -XMVectorGetZ(camera_to_projection.r[2]) * m23;

			return {
				 m00, 0.0f, 0.0f, 0.0f,
				0.0f,  m11, 0.0f, 0.0f,
				0.0f, 0.0f, 0.0f,  m23,
				0.0f, 0.0f, 1.0f,  m33
			};
		}

	private:

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

	#pragma warning( pop )

	#pragma endregion
}