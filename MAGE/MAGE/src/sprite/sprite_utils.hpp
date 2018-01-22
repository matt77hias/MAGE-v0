#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "type\scalar_types.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {
	
	/**
	 An enumeration of the different sprite effects.

	 This contains:
	 @c None,
	 @c MirrorX,
	 @c MirrorY and
	 @c MirrorXY.
	 */
	enum class SpriteEffect : U8 {
		None     = 0,                 // No sprite effects.
		MirrorX  = 1,                 // Mirror sprites along the x-axis.
		MirrorY  = 2,                 // Mirror sprites along the y-axis.
		MirrorXY = MirrorX | MirrorY  // Mirror sprites along the x- and y-axis.
	};

	/**
	 An enumeration of the different sprite sorting modes.

	 This contains:
	 @c Deferred,
	 @c Immediate,
	 @c Texture,
	 @c BackToFront and
	 @c FrontToBack.
	 */
	enum class SpriteSortMode : U8 {
		Deferred,	 // Deferred, FIFO order of the sprites.
		Immediate,   // Immediate, FIFO order of the sprites.
		Texture,     // Deferred sorting based on the texture of the sprites.
		BackToFront, // Deferred, back-to-front sorting based on the depth 
		             // value of the sprites.
		FrontToBack	 // Deferred, front-to-back sorting based on the depth 
		             // value of the sprites.
	};
}