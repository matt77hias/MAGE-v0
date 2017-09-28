#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "memory\allocation.hpp"
#include "math\math.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	//-------------------------------------------------------------------------
	// GameBuffer
	//-------------------------------------------------------------------------

	/**
	 A struct of game buffers.
	 */
	_declspec(align(16)) struct GameBuffer final 
		: public AlignedData< GameBuffer > {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a game buffer.
		 */
		GameBuffer()
			: m_width(0.0f), m_height(0.0f), 
			m_inv_width_minus1(0.0f), 
			m_inv_height_minus1(0.0f),
			m_gamma(0.0f), m_inv_gamma(0.0f), 
			m_padding{} {}

		/**
		 Constructs a game buffer from the given game buffer.

		 @param[in]		buffer
						A reference to the game buffer to copy.
		 */
		GameBuffer(const GameBuffer &buffer) = default;
		
		/**
		 Constructs a game buffer by moving the given game buffer.

		 @param[in]		buffer
						A reference to the game buffer to move.
		 */
		GameBuffer(GameBuffer &&buffer) = default;

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
		GameBuffer &operator=(const GameBuffer &buffer) = default;

		/**
		 Moves the given game buffer to this game buffer.

		 @param[in]		buffer
						A reference to the game buffer to move.
		 @return		A reference to the moved game buffer (i.e. this game 
						buffer).
		 */
		GameBuffer &operator=(GameBuffer &&buffer) = default;

		//---------------------------------------------------------------------
		// Member Variables: Material
		//---------------------------------------------------------------------

		/**
		 The width of this game buffer.
		 */
		F32 m_width;

		/**
		 The height of this game buffer.
		 */
		F32 m_height;

		/**
		 The inverse width minus one of this game buffer.
		 */
		F32 m_inv_width_minus1;

		/**
		 The inverse height minus one of this game buffer.
		 */
		F32 m_inv_height_minus1;

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

	static_assert(sizeof(GameBuffer) == 32, "CPU/GPU struct mismatch");
}