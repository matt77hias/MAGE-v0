#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "geometry\geometry.hpp"
#include "spectrum\spectrum.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage::rendering {

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
			m_viewport_top_left(), 
			m_viewport_resolution(), 
			m_ss_viewport_top_left(), 
			m_ss_viewport_resolution(), 
			m_viewport_inv_resolution_minus1(), 
			m_ss_viewport_inv_resolution_minus1(), 
			m_fog_color(), 
			m_fog_density(0.0f), 
			m_sky_dome_scale_z(1.0f), 
			m_nb_cones(0), 
			m_cone_step_multiplier(1.0f), 
			m_max_cone_distance(1.0f), 
			m_lens_radius(0.0f), 
			m_focal_length(0.0f), 
			m_max_coc_radius(0.0f), 
			m_inv_gamma(0.0f) {}

		/**
		 Constructs a camera buffer from the given camera buffer.

		 @param[in]		buffer
						A reference to the camera buffer to copy.
		 */
		CameraBuffer(const CameraBuffer& buffer) noexcept = default;
		
		/**
		 Constructs a camera buffer by moving the given camera buffer.

		 @param[in]		buffer
						A reference to the camera buffer to move.
		 */
		CameraBuffer(CameraBuffer&& buffer) noexcept = default;

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
		CameraBuffer& operator=(const CameraBuffer& buffer) = default;

		/**
		 Moves the given camera buffer to this camera buffer.

		 @param[in]		buffer
						A reference to the camera buffer to move.
		 @return		A reference to the moved camera buffer (i.e. this camera 
						buffer).
		 */
		CameraBuffer& operator=(CameraBuffer&& buffer) = default;

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
		 The top left corner of the camera viewport of this camera buffer.
		 */
		U32x2 m_viewport_top_left;

		/**
		 The resolution of the camera viewport of this camera buffer. 
		 */
		U32x2 m_viewport_resolution;

		/**
		 The top left corner of the super-sampled camera viewport of this 
		 camera buffer.
		 */
		U32x2 m_ss_viewport_top_left;

		/**
		 The resolution of the super-sampled camera viewport of this camera 
		 buffer.
		 */
		U32x2 m_ss_viewport_resolution;

		/**
		 The inverse of the resolution of the camera viewport minus one of this 
		 camera buffer. 
		 */
		F32x2 m_viewport_inv_resolution_minus1;

		/**
		 The inverse of the resolution of the super-sampled camera viewport 
		 minus one of this camera buffer.
		 */
		F32x2 m_ss_viewport_inv_resolution_minus1;

		//---------------------------------------------------------------------
		// Member Variables: Fog
		//---------------------------------------------------------------------
	
		/**
		 The (linear) color of the fog of this camera buffer.
		 */
		RGB m_fog_color;
		
		/**
		 The density of the fog of this camera buffer.
		 */
		F32 m_fog_density;

		//---------------------------------------------------------------------
		// Member Variables: Sky
		//---------------------------------------------------------------------

		/**
		 The scaling factor of the z component of sky domes of this camera 
		 buffer. 
		 */
		F32 m_sky_dome_scale_z;

		//---------------------------------------------------------------------
		// Member Variables: Voxel Cone Tracing
		//---------------------------------------------------------------------

		/**
		 The number of cones to trace for each shading point of this camera 
		 buffer.
		 */
		U32 m_nb_cones;

		/**
		 The step multiplier of the cone while marching of this camera buffer.
		 */
		F32 m_cone_step_multiplier;
		
		/**
		 The maximal cone distance expressed in normalized texture coordinates 
		 of this camera buffer.
		 */
		F32 m_max_cone_distance;

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

		//---------------------------------------------------------------------
		// Member Variables: Gamma Correction
		//---------------------------------------------------------------------

		/**
		 The inverse gamma exponent of the camera of this camera buffer.
		 */
		F32 m_inv_gamma;
	};

	static_assert(352 == sizeof(CameraBuffer), 
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
			const SecondaryCameraBuffer& buffer) noexcept = default;
		
		/**
		 Constructs a secondary camera buffer by moving the given secondary 
		 camera buffer.

		 @param[in]		buffer
						A reference to the secondary camera buffer to move.
		 */
		SecondaryCameraBuffer(
			SecondaryCameraBuffer&& buffer) noexcept = default;

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
		SecondaryCameraBuffer& operator=(
			const SecondaryCameraBuffer& buffer) = default;

		/**
		 Moves the given secondary camera buffer to this secondary camera 
		 buffer.

		 @param[in]		buffer
						A reference to the secondary camera buffer to move.
		 @return		A reference to the moved secondary camera buffer (i.e. 
						this camera buffer).
		 */
		SecondaryCameraBuffer& operator=(
			SecondaryCameraBuffer&& buffer) = default;

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