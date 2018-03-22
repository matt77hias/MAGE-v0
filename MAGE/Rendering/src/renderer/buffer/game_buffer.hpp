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
			m_ss_display_inv_resolution_minus1() {}

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
	};

	static_assert(32 == sizeof(GameBuffer), "CPU/GPU struct mismatch");
}