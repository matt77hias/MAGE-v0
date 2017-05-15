#pragma once

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 An enumeration of the different sprite sorting modes.

	 This contains:
	 @c Deferred,
	 @c Immediate,
	 @c Texture,
	 @c BackToFront and
	 @c FrontToBack.
	 */
	enum struct SpriteSortMode {
		Deferred,	 // Deferred, FIFO order of the sprites.
		Immediate,   // Immediate, FIFO order of the sprites.
		Texture,     // Deferred sorting based on the texture of the sprites.
		BackToFront, // Deferred, back-to-front sorting based on the depth value of the sprites.
		FrontToBack	 // Deferred, front-to-back sorting based on the depth value of the sprites.
	};
}