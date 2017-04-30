#pragma once

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 An enumeration of the different sprite sorting modes.

	 This contains:
	 @c SpriteSortMode_Deferred,
	 @c SpriteSortMode_Immediate,
	 @c SpriteSortMode_Texture,
	 @c SpriteSortMode_BackToFront and
	 @c SpriteSortMode_FrontToBack.
	 */
	enum SpriteSortMode {
		SpriteSortMode_Deferred,	// Deferred, FIFO order of the sprites.
		SpriteSortMode_Immediate,   // Immediate, FIFO order of the sprites.
		SpriteSortMode_Texture,     // Deferred sorting based on the texture of the sprites.
		SpriteSortMode_BackToFront, // Deferred, back-to-front sorting based on the depth value of the sprites.
		SpriteSortMode_FrontToBack	// Deferred, front-to-back sorting based on the depth value of the sprites.
	};
}