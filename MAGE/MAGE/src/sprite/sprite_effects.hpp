#pragma once

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {
	
	/**
	 An enumeration of the different sprite effects.

	 This contains:
	 @c SpriteEffect_None,
	 @c SpriteEffect_FlipHorizontally,
	 @c SpriteEffect_FlipVertically and
	 @c SpriteEffect_FlipBoth.
	 */
	enum SpriteEffect {
		SpriteEffect_None             = 0,	// No sprite effects.
		SpriteEffect_FlipHorizontally = 1,  // Flip sprites horizontally.
		SpriteEffect_FlipVertically   = 2,  // Flip sprites vertically.
		SpriteEffect_FlipBoth         = SpriteEffect_FlipHorizontally | SpriteEffect_FlipVertically // Flip sprites both horizontally and vertically.
	};
}