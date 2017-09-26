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
			: m_projection_values{}, 
			m_view_to_world{} {}

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
		 The projection values of the view-to-projection transformation matrix
		 of this deferred buffer.
		 */
		XMVECTOR m_projection_values;

		/**
		 The (camera dependent) (column-major packed, row-major matrix) 
		 view-to-world matrix of this sky buffer for use in HLSL.
		 */
		XMMATRIX m_view_to_world;
	};

	static_assert(sizeof(SkyBuffer) == 80, "CPU/GPU struct mismatch");
}