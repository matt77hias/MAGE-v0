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
	 A struct of game buffers.
	 */
	struct alignas(16) GameBuffer final {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a game buffer.
		 */
		GameBuffer() noexcept
			: m_display_resolution(), 
			m_display_inv_resolution_minus1(), 
			m_ss_display_resolution(), 
			m_ss_display_inv_resolution_minus1(), 
			m_voxel_grid_center(), 
			m_voxel_texture_max_mip_level(0u), 
			m_voxel_grid_resolution(0u), 
			m_voxel_grid_inv_resolution(0.0f), 
			m_voxel_size(0.0f), 
			m_voxel_inv_size(0.0f) {}

		/**
		 Constructs a game buffer from the given game buffer.

		 @param[in]		buffer
						A reference to the game buffer to copy.
		 */
		GameBuffer(const GameBuffer& buffer) noexcept = default;
		
		/**
		 Constructs a game buffer by moving the given game buffer.

		 @param[in]		buffer
						A reference to the game buffer to move.
		 */
		GameBuffer(GameBuffer&& buffer) noexcept = default;

		/**
		 Destructs this game buffer.
		 */
		~GameBuffer() = default;
		
		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------
		
		/**
		 Copies the given game buffer to this game buffer.

		 @param[in]		buffer
						A reference to the game buffer to copy.
		 @return		A reference to the copy of the given game buffer (i.e. 
						this game buffer).
		 */
		GameBuffer& operator=(const GameBuffer& buffer) noexcept = default;

		/**
		 Moves the given game buffer to this game buffer.

		 @param[in]		buffer
						A reference to the game buffer to move.
		 @return		A reference to the moved game buffer (i.e. this game 
						buffer).
		 */
		GameBuffer& operator=(GameBuffer&& buffer) noexcept = default;

		//---------------------------------------------------------------------
		// Member Variables: Display Resolution
		//---------------------------------------------------------------------

		/**
		 The resolution of the display of this game buffer.
		 */
		U32x2 m_display_resolution;

		/**
		  The inverse of the resolution of the display minus one of this game 
		  buffer.
		 */
		F32x2 m_display_inv_resolution_minus1;

		/**
		 The resolution of the super-sampled display of this game buffer.
		 */
		U32x2 m_ss_display_resolution;

		/**
		 The inverse of the resolution of the super-sampled display minus one 
		 of this game buffer.
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
		 The maximum mip level of the voxel texture of this game buffer.
		 */
		U32 m_voxel_texture_max_mip_level;

		/**
		 The resolution of the voxel grid for all dimensions of this game 
		 buffer.
		 */
		U32 m_voxel_grid_resolution;

		/**
		 The inverse resolution of the voxel grid for all dimensions of this 
		 game buffer.
		 */
		F32 m_voxel_grid_inv_resolution;

		/**
		 The size of a voxel for all dimensions of this game buffer.
		 */
		F32 m_voxel_size;

		/**
		 The inverse size of a voxel for all dimensions of this game buffer.
		 */
		F32 m_voxel_inv_size;
	};

	static_assert(64 == sizeof(GameBuffer), "CPU/GPU struct mismatch");
}