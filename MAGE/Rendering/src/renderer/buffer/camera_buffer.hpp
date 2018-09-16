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
	struct alignas(16) CameraBuffer {

	public:

		//---------------------------------------------------------------------
		// Member Variables: Transformations
		//---------------------------------------------------------------------

		// HLSL expects column-major packed matrices by default.
		// DirectXMath expects row-major packed matrices.

		/**
		 The (column-major packed, row-major matrix) world-to-camera matrix of 
		 the camera of this camera buffer.
		 */
		XMMATRIX m_world_to_camera = {};

		/**
		 The (column-major packed, row-major matrix) camera-to-projection 
		 matrix of the camera of this camera buffer.
		 */
		XMMATRIX m_camera_to_projection = {};

		/**
		 The (column-major packed, row-major matrix) projection-to-camera 
		 matrix of the camera of this camera buffer.
		 */
		XMMATRIX m_projection_to_camera = {};

		/**
		 The (column-major packed, row-major matrix) camera-to-world matrix of 
		 the camera of this camera buffer.
		 */
		XMMATRIX m_camera_to_world = {};

		//---------------------------------------------------------------------
		// Member Variables: Viewports
		//---------------------------------------------------------------------

		/**
		 The top left corner of the viewport of the camera of this camera 
		 buffer.
		 */
		F32x2 m_viewport_top_left = {};

		/**
		 The resolution of the viewport of the camera of this camera buffer. 
		 */
		U32x2 m_viewport_resolution = {};

		/**
		 The top left corner of the super-sampled viewport of the camera of 
		 this camera buffer.
		 */
		F32x2 m_ss_viewport_top_left = {};

		/**
		 The resolution of the super-sampled viewport of the camera of this 
		 camera buffer.
		 */
		U32x2 m_ss_viewport_resolution = {};

		/**
		 The inverse of the resolution of the viewport of the camera of this 
		 camera buffer. 
		 */
		F32x2 m_viewport_inv_resolution = {};

		/**
		 The inverse of the resolution of the super-sampled viewport of the 
		 camera of this camera buffer.
		 */
		F32x2 m_ss_viewport_inv_resolution = {};

		//---------------------------------------------------------------------
		// Member Variables: Fog
		//---------------------------------------------------------------------
	
		/**
		 The (linear) color of the fog of this camera buffer.
		 */
		RGB m_fog_color = {};
		
		/**
		 The density of the fog of this camera buffer.
		 */
		F32 m_fog_density = 0.0f;

		//---------------------------------------------------------------------
		// Member Variables: Sky
		//---------------------------------------------------------------------

		/**
		 The scaling factor of the z component of sky domes of this camera 
		 buffer. 
		 */
		F32 m_sky_dome_scale_z = 1.0f;

		//---------------------------------------------------------------------
		// Member Variables: Voxel Cone Tracing
		//---------------------------------------------------------------------

		/**
		 The cone step expressed in voxel UVW space of this camera buffer.
		 */
		F32 m_cone_step = 0.1f;
		
		/**
		 The maximal cone distance expressed in voxel UVW space of this camera 
		 buffer.
		 */
		F32 m_max_cone_distance = 1.0f;

		//---------------------------------------------------------------------
		// Member Variables: Post-processing
		//---------------------------------------------------------------------

		/**
		 The radius of the lens aperture of the camera lens of this camera 
		 buffer.
		 */
		F32 m_aperture_radius = 0.0f;

		/**
		 The focal length (i.e. distance between the lens aperture and the 
		 focal point/focus expressed in camera space) of the camera lens of 
		 this camera buffer.
		 */
		F32 m_focal_length = 0.0f;

		/**
		 The focus distance (i.e. distance between the lens aperture and the
		 objects in perfect focus expressed in camera space) of the camera lens 
		 of this camera buffer.
		 */
		F32 m_focus_distance = 0.0f;

		/**
		 The padding of this camera buffer.
		 */
		U32x2 m_padding = {};
	};

	static_assert(352u == sizeof(CameraBuffer), 
				  "CPU/GPU struct mismatch");

	#pragma endregion

	//-------------------------------------------------------------------------
	// SecondaryCameraBuffer
	//-------------------------------------------------------------------------
	#pragma region

	/**
	 A struct of secondary camera buffers.
	 */
	struct alignas(16) SecondaryCameraBuffer {

	public:

		//---------------------------------------------------------------------
		// Member Variables: Transformations
		//---------------------------------------------------------------------

		// HLSL expects column-major packed matrices by default.
		// DirectXMath expects row-major packed matrices.

		/**
		 The (column-major packed, row-major matrix) world-to-camera matrix of 
		 the camera of this secondary camera buffer.
		 */
		XMMATRIX m_world_to_camera = {};

		/**
		 The (column-major packed, row-major matrix) camera-to-projection 
		 matrix of the camera of this secondary camera buffer.
		 */
		XMMATRIX m_camera_to_projection = {};
	};

	static_assert(128u == sizeof(SecondaryCameraBuffer), 
				  "CPU/GPU struct mismatch");

	#pragma endregion
}