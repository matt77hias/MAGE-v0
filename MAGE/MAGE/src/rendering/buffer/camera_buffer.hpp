#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "math.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	//-------------------------------------------------------------------------
	// CameraBuffer
	//-------------------------------------------------------------------------
	#pragma region

	/**
	 A struct of camera buffers.
	 */
	struct alignas(16) CameraBuffer final {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a camera buffer.
		 */
		CameraBuffer() noexcept 
			: m_world_to_camera{},
			m_camera_to_projection{},
			m_projection_to_camera{},
			m_camera_to_world{},
			m_viewport_top_left_x(0u), 
			m_viewport_top_left_y(0u), 
			m_viewport_width(0u), 
			m_viewport_height(0u), 
			m_ss_viewport_top_left_x(0u), 
			m_ss_viewport_top_left_y(0u), 
			m_ss_viewport_width(0u), 
			m_ss_viewport_height(0u), 
			m_viewport_inv_width_minus1(0.0f), 
			m_viewport_inv_height_minus1(0.0f), 
			m_ss_viewport_inv_width_minus1(0.0f), 
			m_ss_viewport_inv_height_minus1(0.0f), 
			m_lens_radius(0.0f), 
			m_focal_length(0.0f), 
			m_max_coc_radius(0.0f), 
			m_padding0(0u) {}

		/**
		 Constructs a camera buffer from the given camera buffer.

		 @param[in]		buffer
						A reference to the camera buffer to copy.
		 */
		CameraBuffer(const CameraBuffer &buffer) noexcept = default;
		
		/**
		 Constructs a camera buffer by moving the given camera buffer.

		 @param[in]		buffer
						A reference to the camera buffer to move.
		 */
		CameraBuffer(CameraBuffer &&buffer) noexcept = default;

		/**
		 Destructs this camera buffer.
		 */
		~CameraBuffer() = default;
		
		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------
		
		/**
		 Copies the given camera buffer to this camera buffer.

		 @param[in]		buffer
						A reference to the camera buffer to copy.
		 @return		A reference to the copy of the given camera buffer (i.e. 
						this camera buffer).
		 */
		CameraBuffer &operator=(const CameraBuffer &buffer) = default;

		/**
		 Moves the given camera buffer to this camera buffer.

		 @param[in]		buffer
						A reference to the camera buffer to move.
		 @return		A reference to the moved camera buffer (i.e. this camera 
						buffer).
		 */
		CameraBuffer &operator=(CameraBuffer &&buffer) = default;

		//---------------------------------------------------------------------
		// Member Variables: Transformations
		//---------------------------------------------------------------------

		// HLSL expects column-major packed matrices by default.
		// DirectXMath expects row-major packed matrices.

		/**
		 The (column-major packed, row-major matrix) world-to-camera matrix of 
		 this camera buffer.
		 */
		XMMATRIX m_world_to_camera;

		/**
		 The (column-major packed, row-major matrix) camera-to-projection 
		 matrix of this camera buffer.
		 */
		XMMATRIX m_camera_to_projection;

		/**
		 The (column-major packed, row-major matrix) projection-to-camera 
		 matrix of this camera buffer.
		 */
		XMMATRIX m_projection_to_camera;

		/**
		 The (column-major packed, row-major matrix) camera-to-world matrix of 
		 this camera buffer.
		 */
		XMMATRIX m_camera_to_world;

		//---------------------------------------------------------------------
		// Member Variables: Viewports
		//---------------------------------------------------------------------

		/**
		 The x coordinate of the left hand side of the viewport of this camera 
		 buffer.
		 */
		U32 m_viewport_top_left_x;

		/**
		 The y coordinate of the left hand side of the viewport of this camera 
		 buffer.
		 */
		U32 m_viewport_top_left_y;

		/**
		 The width of the viewport of this camera buffer. 
		 */
		U32 m_viewport_width;

		/**
		 The height of the viewport of this camera buffer. 
		 */
		U32 m_viewport_height;

		/**
		 The x coordinate of the left hand side of the super-sampled viewport of this 
		 camera buffer.
		 */
		U32 m_ss_viewport_top_left_x;

		/**
		 The y coordinate of the left hand side of the super-sampled viewport of this 
		 camera buffer.
		 */
		U32 m_ss_viewport_top_left_y;

		/**
		 The width of the super-sampled viewport of this camera buffer. 
		 */
		U32 m_ss_viewport_width;

		/**
		 The height of the super-sampled viewport of this camera buffer. 
		 */
		U32 m_ss_viewport_height;

		/**
		 The inverse width of the viewport minus 1 of this camera buffer. 
		 */
		F32 m_viewport_inv_width_minus1;

		/**
		 The inverse height of the viewport minus 1 of this camera buffer. 
		 */
		F32 m_viewport_inv_height_minus1;

		/**
		 The inverse width of the super-sampled viewport minus 1 of this 
		 camera buffer.
		 */
		F32 m_ss_viewport_inv_width_minus1;

		/**
		 The inverse height of the super-sampled viewport minus 1 of this 
		 camera buffer.
		 */
		F32 m_ss_viewport_inv_height_minus1;

		//---------------------------------------------------------------------
		// Member Variables: Post-processing
		//---------------------------------------------------------------------

		/**
		 The lens radius of the camera of this camera buffer. 
		 */
		F32 m_lens_radius;

		/**
		 The focal length of the camera of this camera buffer.
		 */
		F32 m_focal_length;

		/**
		 The maximum radius of the circle-of-confusion of the camera of this 
		 camera buffer.
		 */
		F32 m_max_coc_radius;

		/**
		 The padding of the camera of this camera buffer.
		 */
		U32 m_padding0;
	};

	static_assert(320 == sizeof(CameraBuffer), 
				  "CPU/GPU struct mismatch");

	#pragma endregion

	//-------------------------------------------------------------------------
	// SecondaryCameraBuffer
	//-------------------------------------------------------------------------
	#pragma region

	/**
	 A struct of secondary camera buffers.
	 */
	struct alignas(16) SecondaryCameraBuffer final {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a secondary camera buffer.
		 */
		SecondaryCameraBuffer() noexcept 
			: m_world_to_camera{},
			m_camera_to_projection{} {}

		/**
		 Constructs a secondary camera buffer from the given secondary camera 
		 buffer.

		 @param[in]		buffer
						A reference to the secondary camera buffer to copy.
		 */
		SecondaryCameraBuffer(
			const SecondaryCameraBuffer &buffer) noexcept = default;
		
		/**
		 Constructs a secondary camera buffer by moving the given secondary 
		 camera buffer.

		 @param[in]		buffer
						A reference to the secondary camera buffer to move.
		 */
		SecondaryCameraBuffer(
			SecondaryCameraBuffer &&buffer) noexcept = default;

		/**
		 Destructs this secondary camera buffer.
		 */
		~SecondaryCameraBuffer() = default;
		
		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------
		
		/**
		 Copies the given secondary camera buffer to this secondary camera 
		 buffer.

		 @param[in]		buffer
						A reference to the secondary camera buffer to copy.
		 @return		A reference to the copy of the given secondary camera 
						buffer (i.e. this secondary camera buffer).
		 */
		SecondaryCameraBuffer &operator=(
			const SecondaryCameraBuffer &buffer) = default;

		/**
		 Moves the given secondary camera buffer to this secondary camera 
		 buffer.

		 @param[in]		buffer
						A reference to the secondary camera buffer to move.
		 @return		A reference to the moved secondary camera buffer (i.e. 
						this camera buffer).
		 */
		SecondaryCameraBuffer &operator=(
			SecondaryCameraBuffer &&buffer) = default;

		//---------------------------------------------------------------------
		// Member Variables: Transformations
		//---------------------------------------------------------------------

		// HLSL expects column-major packed matrices by default.
		// DirectXMath expects row-major packed matrices.

		/**
		 The (column-major packed, row-major matrix) world-to-camera matrix of 
		 this secondary camera buffer.
		 */
		XMMATRIX m_world_to_camera;

		/**
		 The (column-major packed, row-major matrix) camera-to-projection 
		 matrix of this secondary camera buffer.
		 */
		XMMATRIX m_camera_to_projection;
	};

	static_assert(128 == sizeof(SecondaryCameraBuffer), 
				  "CPU/GPU struct mismatch");

	#pragma endregion
}