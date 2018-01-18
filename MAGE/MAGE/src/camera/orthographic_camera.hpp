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

	#pragma warning( push )
	#pragma warning( disable : 4324 ) // Added padding.

	/**
	 A class of orthographic cameras.
	 */
	class alignas(16) OrthographicCamera final : public Camera {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs an orthographic camera.

		 @pre			The rendering manager associated with the current
						engine must be loaded.
		 */
		OrthographicCamera() noexcept;

		/**
		 Constructs an orthographic camera from the given orthographic 
		 camera.

		 @param[in]		camera
						A reference to the orthographic camera to copy.
		 */
		OrthographicCamera(const OrthographicCamera &camera) noexcept;

		/**
		 Constructs an orthographic camera by moving the given orthographic 
		 camera.

		 @param[in]		camera
						A reference to the orthographic camera to move.
		 */
		OrthographicCamera(OrthographicCamera &&camera) noexcept;

		/**
		 Destructs this orthographic camera.
		 */
		virtual ~OrthographicCamera();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------	

		/**
		 Copies the given orthographic camera to this orthographic camera.

		 @param[in]		camera
						A reference to the orthographic camera to copy.
		 @return		A reference to the copy of the given orthographic 
						camera (i.e. this orthographic camera).
		 */
		OrthographicCamera &operator=(const OrthographicCamera &camera) noexcept;
		
		/**
		 Moves the given orthographic camera to this orthographic camera.

		 @param[in]		camera
						A reference to the orthographic camera to move.
		 @return		A reference to the moved orthographic camera (i.e. this 
						orthographic camera).
		 */
		OrthographicCamera &operator=(OrthographicCamera &&camera) noexcept;

		//---------------------------------------------------------------------
		// Member Methods: Projection
		//---------------------------------------------------------------------

		/**
		 Returns the width of the camera projection plane of this orthographic 
		 camera in view space.

		 @return		The width of the camera projection plane of this 
						orthographic camera in view space.
		 */
		[[nodiscard]] F32 GetWidth() const noexcept {
			return m_width;
		}

		/**
		 Sets the width of the camera projection plane of this orthographic 
		 camera to the given value.

		 @param[in]		width
						The width of the camera projection plane in camera 
						space.
		 */
		void SetWidth(F32 width) noexcept {
			m_width = width;
		}

		/**
		 Returns the height of the camera projection plane of this orthographic 
		 camera in view space.

		 @return		The height of the camera projection plane of this 
						orthographic camera in view space.
		 */
		[[nodiscard]] F32 GetHeight() const noexcept {
			return m_height;
		}
		
		/**
		 Sets the height of the camera projection plane of this orthographic 
		 camera to the given value.

		 @param[in]		height
						The height of the camera projection plane in camera 
						space.
		 */
		void SetHeight(F32 height) noexcept {
			m_height = height;
		}
		
		/**
		 Sets the width and height of the camera projection plane of this 
		 orthographic camera to the given values.

		 @param[in]		width
						The width of the camera projection plane in camera 
						space.
		 @param[in]		height
						The height of the camera projection plane in camera 
						space.
		 */
		void SetWidthAndHeight(F32 width, F32 height) noexcept {
			m_width  = width;
			m_height = height;
		}
		
		/**
		 Sets the view-to-projection matrix of this orthographic camera.

		 @param[in]		width
						The width of the camera projection plane in camera 
						space.
		 @param[in]		height
						The height of the camera projection plane in camera 
						space.
		 @param[in]		near_z
						The position of the near z-plane in view space.
		 @param[in]		far_z
						The position of the far z-plane in view space.
		*/
		void SetViewToProjectionMatrix(F32 width,  F32 height, 
			F32 near_z, F32 far_z) noexcept {
			
			SetWidthAndHeight(width, height);
			SetNearAndFarZ(near_z, far_z);
		}
	
		/**
		 Returns the view-to-projection matrix of this orthographic camera.

		 @return		The view-to-projection matrix of this orthographic 
						camera.
		 */
		[[nodiscard]] virtual const XMMATRIX XM_CALLCONV GetViewToProjectionMatrix() const noexcept override {
			#ifdef DISSABLE_INVERTED_Z_BUFFER
			return XMMatrixOrthographicLH(
				GetWidth(), GetHeight(), GetNearZ(), GetFarZ());
			#else  // DISSABLE_INVERTED_Z_BUFFER
			return XMMatrixOrthographicLH(
				GetWidth(), GetHeight(), GetFarZ(), GetNearZ());
			#endif // DISSABLE_INVERTED_Z_BUFFER
		}

		/**
		 Returns the projection-to-view matrix of this orthographic camera.

		 @return		The projection-to-view matrix of this orthographic 
						camera.
		 */
		[[nodiscard]] virtual const XMMATRIX XM_CALLCONV GetProjectionToViewMatrix() const noexcept override {
			const XMMATRIX view_to_projection = GetViewToProjectionMatrix();

			const F32 m00 = 1.0f / XMVectorGetX(view_to_projection.r[0]);
			const F32 m11 = 1.0f / XMVectorGetY(view_to_projection.r[1]);
			const F32 m22 = 1.0f / XMVectorGetZ(view_to_projection.r[2]);
			const F32 m32 = -XMVectorGetZ(view_to_projection.r[3]) * m22;
			
			return XMMATRIX {
				 m00, 0.0f, 0.0f, 0.0f,
				0.0f,  m11, 0.0f, 0.0f,
				0.0f, 0.0f,  m22, 0.0f,
				0.0f, 0.0f,  m32, 1.0f
			};
		}

	private:

		//---------------------------------------------------------------------
		// Member Variables: Projection
		//---------------------------------------------------------------------

		/**
		 The width of the camera projection plane of this orthographic camera 
		 in view space.
		 */
		F32 m_width;

		/**
		 The height of the camera projection plane of this orthographic camera 
		 in view space.
		 */
		F32 m_height;
	};

	#pragma warning( pop )
}