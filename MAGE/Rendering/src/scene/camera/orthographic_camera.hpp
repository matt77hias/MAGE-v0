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

	#pragma warning( push )
	#pragma warning( disable : 4324 ) // Added padding.

	/**
	 A class of orthographic cameras.
	 */
	class alignas(16) OrthographicCamera : public Camera {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs an orthographic camera.

		 @param[in]		device
						A reference to the device.
		 */
		OrthographicCamera(ID3D11Device& device);

		/**
		 Constructs an orthographic camera from the given orthographic 
		 camera.

		 @param[in]		camera
						A reference to the orthographic camera to copy.
		 */
		OrthographicCamera(const OrthographicCamera& camera) = delete;

		/**
		 Constructs an orthographic camera by moving the given orthographic 
		 camera.

		 @param[in]		camera
						A reference to the orthographic camera to move.
		 */
		OrthographicCamera(OrthographicCamera&& camera) noexcept;

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
		OrthographicCamera& operator=(const OrthographicCamera& camera) = delete;
		
		/**
		 Moves the given orthographic camera to this orthographic camera.

		 @param[in]		camera
						A reference to the orthographic camera to move.
		 @return		A reference to the moved orthographic camera (i.e. this 
						orthographic camera).
		 */
		OrthographicCamera& operator=(OrthographicCamera&& camera) noexcept;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Returns the size of the projection plane of this orthographic camera 
		 expressed in camera space.

		 @return		The size of the projection plane of this orthographic 
						camera expressed in camera space.
		 */
		[[nodiscard]]
		const F32x2 GetSize() const noexcept {
			return m_size;
		}

		/**
		 Sets the size of the projection plane of this orthographic camera 
		 expressed in camera space to the given size.

		 @param[in]		size
						The size.
		 */
		void SetSize(F32x2 size) noexcept {
			m_size = std::move(size);
		}

		/**
		 Returns the camera-to-projection matrix of this orthographic camera.

		 @return		The camera-to-projection matrix of this orthographic 
						camera.
		 */
		[[nodiscard]]
		virtual const XMMATRIX XM_CALLCONV 
			GetCameraToProjectionMatrix() const noexcept override {

			#ifdef DISABLE_INVERTED_Z_BUFFER
			const auto [near_plane, far_plane] = GetClippingPlanes();
			#else  // DISABLE_INVERTED_Z_BUFFER
			const auto [far_plane, near_plane] = GetClippingPlanes();
			#endif // DISABLE_INVERTED_Z_BUFFER

			return XMMatrixOrthographicLH(m_size[0], m_size[1], 
										  near_plane, far_plane);
		}

		/**
		 Returns the projection-to-camera matrix of this orthographic camera.

		 @return		The projection-to-camera matrix of this orthographic 
						camera.
		 */
		[[nodiscard]]
		virtual const XMMATRIX XM_CALLCONV 
			GetProjectionToCameraMatrix() const noexcept override {

			const auto camera_to_projection = GetCameraToProjectionMatrix();

			const auto m00 = 1.0f / XMVectorGetX(camera_to_projection.r[0]);
			const auto m11 = 1.0f / XMVectorGetY(camera_to_projection.r[1]);
			const auto m22 = 1.0f / XMVectorGetZ(camera_to_projection.r[2]);
			const auto m32 = -XMVectorGetZ(camera_to_projection.r[3]) * m22;
			
			return {
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
		 The size of the projection plane of this orthographic camera expressed 
		 in camera space.
		 */
		F32x2 m_size;
	};

	#pragma warning( pop )
}