#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "type\types.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage::rendering {

	/**
	 A struct of world buffers.
	 */
	struct alignas(16) WorldBuffer {

	public:

		//---------------------------------------------------------------------
		// Member Variables: Display Resolution
		//---------------------------------------------------------------------

		/**
		 The resolution of the display of this world buffer.
		 */
		U32x2 m_display_resolution = {};

		/**
		 The inverse of the resolution of the display of this game buffer.
		 */
		F32x2 m_display_inv_resolution = {};

		/**
		 The resolution of the super-sampled display of this world buffer.
		 */
		U32x2 m_ss_display_resolution = {};

		/**
		 The inverse of the resolution of the super-sampled display of this 
		 world buffer.
		 */
		F32x2 m_ss_display_inv_resolution = {};

		//---------------------------------------------------------------------
		// Member Variables: Voxelization
		//---------------------------------------------------------------------

		/**
		 The center of the voxel grid expressed in world space of this game 
		 buffer.
		 */
		Point3 m_voxel_grid_center = {};

		/**
		 The maximum mip level of the voxel texture of this world buffer.
		 */
		U32 m_voxel_texture_max_mip_level = 0u;

		/**
		 The resolution of the voxel grid for all dimensions of this game 
		 buffer.
		 */
		U32 m_voxel_grid_resolution = 0u;

		/**
		 The inverse resolution of the voxel grid for all dimensions of this 
		 world buffer.
		 */
		F32 m_voxel_grid_inv_resolution = 0.0f;

		/**
		 The size of a voxel for all dimensions of this world buffer.
		 */
		F32 m_voxel_size = 0.0f;

		/**
		 The inverse size of a voxel for all dimensions of this world buffer.
		 */
		F32 m_voxel_inv_size = 0.0f;

		//---------------------------------------------------------------------
		// Member Variables: Time
		//---------------------------------------------------------------------

		/**
		 The time of this world buffer. 
		 */
		F32 m_time = 0.0f;

		//---------------------------------------------------------------------
		// Member Variables: Gamma Correction
		//---------------------------------------------------------------------

		/**
		 The inverse gamma exponent of this world buffer.
		 */
		F32 m_inv_gamma = 1.0f;

		/**
		 The passing of this world buffer.
		 */
		U32x2 m_padding = {};
	};

	static_assert(80u == sizeof(WorldBuffer), "CPU/GPU struct mismatch");
}