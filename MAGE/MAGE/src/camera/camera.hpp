#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "scene\component.hpp"
#include "camera\camera_settings.hpp"
#include "camera\viewport.hpp"
#include "rendering\buffer\constant_buffer.hpp"
#include "rendering\buffer\camera_buffer.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	//-------------------------------------------------------------------------
	// CameraLens
	//-------------------------------------------------------------------------
	#pragma region

	/**
	 A class of camera lenses.
	 */
	class CameraLens final {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a camera settings.
		 */
		constexpr CameraLens() noexcept
			: m_radius(0.0f),
			m_focal_length(100.0f),
			m_max_coc_radius(10.0f) {}

		/**
		 Constructs a camera lens from the given camera lens.

		 @param[in]		lens
						A reference to the camera lens to copy.
		 */
		constexpr CameraLens(const CameraLens &lens) noexcept = default;

		/**
		 Constructs a camera lens by moving the given camera lens.

		 @param[in]		lens
						A reference to the camera lens to move.
		 */
		constexpr CameraLens(CameraLens &&lens) noexcept = default;

		/**
		 Destructs this camera lens.
		 */
		~CameraLens() = default;

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given camera lens to this camera lens.

		 @param[in]		lens
						A reference to the camera lens to copy.
		 @return		A reference to the copy of the given camera lens (i.e. 
						this camera lens).
		 */
		constexpr CameraLens &operator=(const CameraLens &lens) noexcept = default;

		/**
		 Moves the given camera lens to this camera lens.

		 @param[in]		lens
						A reference to the camera lens to move.
		 @return		A reference to the moved camera lens (i.e. this camera 
						lens).
		 */
		constexpr CameraLens &operator=(CameraLens &&lens) noexcept = default;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Checks whether this camera lens has a finite aperture.

		 @return		@c true if this camera lens has a finite aperture.
						@c false otherwise.
		 */
		[[nodiscard]] constexpr bool HasFiniteAperture() const noexcept {
			return 0.0f != m_radius;
		}

		/**
		 Returns the radius of this camera lens.

		 @return		The radius of this camera lens.
		 */
		[[nodiscard]] constexpr F32 GetLensRadius() const noexcept {
			return m_radius;
		}
		
		/**
		 Sets the radius of this camera lens to the given value.

		 @param[in]		radius
						The radius of the camera lens.
		 */
		constexpr void SetLensRadius(F32 radius) noexcept {
			m_radius = radius;
		}

		/**
		 Returns the focal length of this camera lens.

		 @return		The focal length of this camera lens.
		 */
		[[nodiscard]] constexpr F32 GetFocalLength() const noexcept {
			return m_focal_length;
		}
		
		/**
		 Sets the focal length of this camera lens to the given value.

		 @param[in]		focal_length
						The focal length.
		 */
		constexpr void SetFocalLength(F32 focal_length) noexcept {
			m_focal_length = focal_length;
		}

		/**
		 Returns the maximum radius of the circle of confusion of this camera 
		 lens.

		 @return		The maximum radius of the circle of confusion of this 
						camera lens.
		 */
		[[nodiscard]] constexpr F32 GetMaximumCoCRadius() const noexcept {
			return m_max_coc_radius;
		}
		
		/**
		 Sets the maximum radius of the circle of confusion of this camera lens 
		 to the given value.

		 @param[in]		max_coc_radius
						The maximum radius of the circle of confusion.
		 */
		constexpr void SetMaximumCoCRadius(F32 max_coc_radius) noexcept {
			m_max_coc_radius = max_coc_radius;
		}

	private:

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 The radius of this camera lens.
		 */
		F32 m_radius;

		/**
		 The focal length of this camera lens.
		 */
		F32 m_focal_length;

		/**
		 The maximum radius of the circle-of-confusion of this camera lens.
		 */
		F32 m_max_coc_radius;
	};

	#pragma endregion

	//-------------------------------------------------------------------------
	// Camera
	//-------------------------------------------------------------------------
	#pragma region

	/**
	 A class of cameras.
	 */
	class Camera : public Component {

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
		Camera &operator=(Camera &&camera) noexcept;

		//---------------------------------------------------------------------
		// Member Methods: Projection
		//---------------------------------------------------------------------

		/**
		 Returns the position of the near z-plane of this camera in camera 
		 view space.

		 @return		The position of the near z-plane of this camera in 
						camera view space.
		 */
		[[nodiscard]] F32 GetNearZ() const noexcept {
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
		[[nodiscard]] F32 GetFarZ() const noexcept {
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
		 Returns the camera-to-projection matrix of this camera.

		 @return		The camera-to-projection matrix of this camera.
		 */
		[[nodiscard]] virtual const XMMATRIX XM_CALLCONV 
			GetCameraToProjectionMatrix() const noexcept = 0;

		/**
		 Returns the projection-to-camera matrix of this camera.

		 @return		The projection-to-camera matrix of this camera.
		 */
		[[nodiscard]] virtual const XMMATRIX XM_CALLCONV 
			GetProjectionToCameraMatrix() const noexcept = 0;

		//---------------------------------------------------------------------
		// Member Methods: Lens
		//---------------------------------------------------------------------

		/**
		 Returns the lens of this camera.

		 @return		A reference to the lens of this camera.	
		 */
		[[nodiscard]] CameraLens &GetLens() noexcept {
			return m_lens;
		}
		
		/**
		 Returns the lens of this camera.

		 @return		A reference to the lens of this camera.	
		 */
		[[nodiscard]] const CameraLens &GetLens() const noexcept {
			return m_lens;
		}

		//---------------------------------------------------------------------
		// Member Methods: Viewport
		//---------------------------------------------------------------------

		/**
		 Returns the viewport of this camera.

		 @return		A reference to the viewport of this camera.
		 */
		[[nodiscard]] Viewport &GetViewport() noexcept {
			return m_viewport;
		}

		/**
		 Returns the viewport of this camera.

		 @return		A reference to the viewport of this camera.
		 */
		[[nodiscard]] const Viewport &GetViewport() const noexcept {
			return m_viewport;
		}

		/**
		 Returns the super-sampled viewport of this camera.

		 @pre			The rendering manager associated with the current 
						engine must be loaded.
		 @return		The super-sampled viewport of this camera.
		 */
		[[nodiscard]] const Viewport GetSSViewport() const noexcept;

		/**
		 Binds the viewport of this camera.

		 @pre			@a device_context is not equal to @c nullptr.
		 @param[in]		device_context
						A pointer to the device context.
		 */
		void BindViewport(D3D11DeviceContext *device_context) const noexcept {
			GetViewport().BindViewport(device_context);
		}

		/**
		 Binds the super-sampled viewport of this camera.

		 @pre			@a device_context is not equal to @c nullptr.
		 @param[in]		device_context
						A pointer to the device context.
		 */
		void BindSSViewport(ID3D11DeviceContext *device_context) const noexcept {
			GetSSViewport().BindViewport(device_context);
		}

		//---------------------------------------------------------------------
		// Member Methods: Settings
		//---------------------------------------------------------------------

		/**
		 Returns the settings of this camera.

		 @return		A reference to the settings of this camera.	
		 */
		[[nodiscard]] CameraSettings &GetSettings() noexcept {
			return m_settings;
		}
		
		/**
		 Returns the settings of this camera.

		 @return		A reference to the settings of this camera.
		 */
		[[nodiscard]] const CameraSettings &GetSettings() const noexcept {
			return m_settings;
		}

		//---------------------------------------------------------------------
		// Member Methods: Buffer
		//---------------------------------------------------------------------

		/**
		 Updates the buffer of this camera.

		 @pre			@a device_context is not equal to @c nullptr.
		 @param[in]		device_context
						A pointer to the device context.
		 */
		void UpdateBuffer(ID3D11DeviceContext *device_context) const;

		/**
		 Binds the buffer of this camera to the given pipeline stage.

		 @pre			@a device_context is not equal to @c nullptr.
		 @tparam		PipelineStageT
						The pipeline stage type.
		 @param[in]		device_context
						A pointer to the device context.
		 @param[in]		slot
						The index into the device's zero-based array to set 
						the constant buffer to (ranges from 0 to 
						@c D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - 1).
		 */
		template< typename PipelineStageT >
		void BindBuffer(ID3D11DeviceContext *device_context, 
						U32 slot) const noexcept;

	protected:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a camera.

		 @pre			The rendering manager associated with the current
						engine must be loaded.
		 */
		Camera() noexcept;

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
		Camera(Camera &&camera) noexcept;

	private:

		//---------------------------------------------------------------------
		// Member Variables: Buffer
		//---------------------------------------------------------------------

		/**
		 The buffer of this camera.
		 */
		mutable ConstantBuffer< CameraBuffer > m_buffer;

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
		// Member Variables: Lens
		//---------------------------------------------------------------------

		/**
		 The lens of this camera.
		 */
		CameraLens m_lens;

		//---------------------------------------------------------------------
		// Member Variables: Viewport
		//---------------------------------------------------------------------

		/**
		 The viewport of this camera.
		 */
		Viewport m_viewport;

		//---------------------------------------------------------------------
		// Member Variables: Settings
		//---------------------------------------------------------------------

		/**
		 The settings of this camera.
		 */
		CameraSettings m_settings;
	};

	#pragma endregion
}

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "camera\camera.tpp"

#pragma endregion