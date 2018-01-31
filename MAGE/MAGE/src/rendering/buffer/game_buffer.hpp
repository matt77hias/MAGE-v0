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
			: m_display_width(0u), 
			m_display_height(0u),
			m_display_inv_width_minus1(0.0f),
			m_display_inv_height_minus1(0.0f),
			m_ss_display_width(0u),
			m_ss_display_height(0u),
			m_ss_display_inv_width_minus1(0.0f),
			m_ss_display_inv_height_minus1(0.0f),
			m_gamma(0.0f), 
			m_inv_gamma(0.0f), 
			m_padding{} {}

		/**
		 Constructs a game buffer from the given game buffer.

		 @param[in]		buffer
						A reference to the game buffer to copy.
		 */
		GameBuffer(const GameBuffer &buffer) noexcept = default;
		
		/**
		 Constructs a game buffer by moving the given game buffer.

		 @param[in]		buffer
						A reference to the game buffer to move.
		 */
		GameBuffer(GameBuffer &&buffer) noexcept = default;

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
		GameBuffer &operator=(const GameBuffer &buffer) noexcept = default;

		/**
		 Moves the given game buffer to this game buffer.

		 @param[in]		buffer
						A reference to the game buffer to move.
		 @return		A reference to the moved game buffer (i.e. this game 
						buffer).
		 */
		GameBuffer &operator=(GameBuffer &&buffer) noexcept = default;

		//---------------------------------------------------------------------
		// Member Variables: Display Resolution
		//---------------------------------------------------------------------

		/**
		 The width of the display of this game buffer.
		 */
		U32 m_display_width;

		/**
		 The height of the display of this game buffer.
		 */
		U32 m_display_height;

		/**
		 The inverse width of the display minus one of this game buffer.
		 */
		F32 m_display_inv_width_minus1;

		/**
		 The inverse height of the display minus one of this game buffer.
		 */
		F32 m_display_inv_height_minus1;

		/**
		 The width of the super-sampled display of this game buffer.
		 */
		U32 m_ss_display_width;

		/**
		 The height of the super-sampled display of this game buffer.
		 */
		U32 m_ss_display_height;

		/**
		 The inverse width of the super-sampled display minus one of this game 
		 buffer.
		 */
		F32 m_ss_display_inv_width_minus1;

		/**
		 The inverse height of the super-sampled display minus one of this game 
		 buffer.
		 */
		F32 m_ss_display_inv_height_minus1;

		//---------------------------------------------------------------------
		// Member Variables: Gamma Correction
		//---------------------------------------------------------------------

		/**
		 The gamma exponent of this game buffer.
		 */
		F32 m_gamma;

		/**
		 The inverse gamma exponent of this game buffer.
		 */
		F32 m_inv_gamma;

		/**
		 The padding of this game buffer.
		 */
		U32 m_padding[2];
	};

	static_assert(48 == sizeof(GameBuffer), "CPU/GPU struct mismatch");
}