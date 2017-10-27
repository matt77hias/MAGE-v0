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
	// SkyBuffer
	//-------------------------------------------------------------------------

	/**
	 A struct of game buffers.
	 */
	_declspec(align(16)) struct SkyBuffer final 
		: public AlignedData< SkyBuffer > {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a game buffer.
		 */
		SkyBuffer()
			: m_world_to_view{},
			m_view_to_projection{} {}

		/**
		 Constructs a game buffer from the given game buffer.

		 @param[in]		buffer
						A reference to the game buffer to copy.
		 */
		SkyBuffer(const SkyBuffer &buffer) = default;
		
		/**
		 Constructs a game buffer by moving the given game buffer.

		 @param[in]		buffer
						A reference to the game buffer to move.
		 */
		SkyBuffer(SkyBuffer &&buffer) = default;

		/**
		 Destructs this game buffer.
		 */
		~SkyBuffer() = default;
		
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
		SkyBuffer &operator=(const SkyBuffer &buffer) = default;

		/**
		 Moves the given game buffer to this game buffer.

		 @param[in]		buffer
						A reference to the game buffer to move.
		 @return		A reference to the moved game buffer (i.e. this game 
						buffer).
		 */
		SkyBuffer &operator=(SkyBuffer &&buffer) = default;

		//---------------------------------------------------------------------
		// Member Variables: Transforms
		//---------------------------------------------------------------------

		// HLSL expects column-major packed matrices by default.
		// DirectXMath expects row-major packed matrices.

		/**
		 The (camera dependent) (column-major packed, row-major matrix) 
		 world-to-view matrix of this sky buffer for use in HLSL.
		 */
		XMMATRIX m_world_to_view;

		/**
		 The (camera dependent) (column-major packed, row-major matrix) 
		 view-to-projection matrix of this sky buffer for use in HLSL.
		 */
		XMMATRIX m_view_to_projection;
	};

	static_assert(sizeof(SkyBuffer) == 128, "CPU/GPU struct mismatch");
}