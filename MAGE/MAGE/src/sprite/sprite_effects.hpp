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
		None             = 0,	// No sprite effects.
		FlipHorizontally = 1,  // Flip sprites horizontally.
		FlipVertically   = 2,  // Flip sprites vertically.
		FlipBoth         = FlipHorizontally | FlipVertically // Flip sprites both horizontally and vertically.
	};
}