#pragma once

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {
	
	/**
	 An enumeration of the different sprite effects.

	 This contains:
	 @c None,
	 @c FlipHorizontally,
	 @c FlipVertically and
	 @c FlipBoth.
	 */
	enum struct SpriteEffect {
		None             = 0, // No sprite effects.
		FlipHorizontally = 1, // Flip sprites horizontally.
		FlipVertically   = 2, // Flip sprites vertically.
		FlipBoth         = FlipHorizontally | FlipVertically 
							  // Flip sprites both horizontally and vertically.
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
	enum struct SpriteSortMode {
		Deferred,	 // Deferred, FIFO order of the sprites.
		Immediate,   // Immediate, FIFO order of the sprites.
		Texture,     // Deferred sorting based on the texture of the sprites.
		BackToFront, // Deferred, back-to-front sorting based on the depth 
		             // value of the sprites.
		FrontToBack	 // Deferred, front-to-back sorting based on the depth 
		             // value of the sprites.
	};
}