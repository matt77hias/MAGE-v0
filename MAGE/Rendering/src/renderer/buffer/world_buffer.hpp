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
	struct alignas(16) WorldBuffer final {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a world buffer.
		 */
		WorldBuffer() noexcept
			: m_display_resolution(), 
			m_display_inv_resolution_minus1(), 
			m_ss_display_resolution(), 
			m_ss_display_inv_resolution_minus1(), 
			m_voxel_grid_center(), 
			m_voxel_texture_max_mip_level(0u), 
			m_voxel_grid_resolution(0u), 
			m_voxel_grid_inv_resolution(0.0f), 
			m_voxel_size(0.0f), 
			m_voxel_inv_size(0.0f), 
			m_time(0.0f), 
			m_padding() {}

		/**
		 Constructs a world buffer from the given world buffer.

		 @param[in]		buffer
						A reference to the world buffer to copy.
		 */
		WorldBuffer(const WorldBuffer& buffer) noexcept = default;
		
		/**
		 Constructs a world buffer by moving the given world buffer.

		 @param[in]		buffer
						A reference to the world buffer to move.
		 */
		WorldBuffer(WorldBuffer&& buffer) noexcept = default;

		/**
		 Destructs this world buffer.
		 */
		~WorldBuffer() = default;
		
		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------
		
		/**
		 Copies the given world buffer to this world buffer.

		 @param[in]		buffer
						A reference to the world buffer to copy.
		 @return		A reference to the copy of the given world buffer (i.e. 
						this world buffer).
		 */
		WorldBuffer& operator=(const WorldBuffer& buffer) noexcept = default;

		/**
		 Moves the given world buffer to this world buffer.

		 @param[in]		buffer
						A reference to the world buffer to move.
		 @return		A reference to the moved world buffer (i.e. this game 
						buffer).
		 */
		WorldBuffer& operator=(WorldBuffer&& buffer) noexcept = default;

		//---------------------------------------------------------------------
		// Member Variables: Display Resolution
		//---------------------------------------------------------------------

		/**
		 The resolution of the display of this world buffer.
		 */
		U32x2 m_display_resolution;

		/**
		  The inverse of the resolution of the display minus one of this game 
		  buffer.
		 */
		F32x2 m_display_inv_resolution_minus1;

		/**
		 The resolution of the super-sampled display of this world buffer.
		 */
		U32x2 m_ss_display_resolution;

		/**
		 The inverse of the resolution of the super-sampled display minus one 
		 of this world buffer.
		 */
		F32x2 m_ss_display_inv_resolution_minus1;

		//---------------------------------------------------------------------
		// Member Variables: Voxelization
		//---------------------------------------------------------------------

		/**
		 The center of the voxel grid expressed in world space of this game 
		 buffer.
		 */
		Point3 m_voxel_grid_center;

		/**
		 The maximum mip level of the voxel texture of this world buffer.
		 */
		U32 m_voxel_texture_max_mip_level;

		/**
		 The resolution of the voxel grid for all dimensions of this game 
		 buffer.
		 */
		U32 m_voxel_grid_resolution;

		/**
		 The inverse resolution of the voxel grid for all dimensions of this 
		 world buffer.
		 */
		F32 m_voxel_grid_inv_resolution;

		/**
		 The size of a voxel for all dimensions of this world buffer.
		 */
		F32 m_voxel_size;

		/**
		 The inverse size of a voxel for all dimensions of this world buffer.
		 */
		F32 m_voxel_inv_size;

		//---------------------------------------------------------------------
		// Member Variables: Time
		//---------------------------------------------------------------------

		/**
		 The time of this world buffer. 
		 */
		F32 m_time;

		/**
		 The passing of this world buffer.
		 */
		U32x3 m_padding;
	};

	static_assert(80 == sizeof(WorldBuffer), "CPU/GPU struct mismatch");
}