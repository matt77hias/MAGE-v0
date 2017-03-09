#pragma once

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {
	
	enum SpriteEffects {
		SpriteEffects_None = 0,
		SpriteEffects_FlipHorizontally = 1,
		SpriteEffects_FlipVertically = 2,
		SpriteEffects_FlipBoth = SpriteEffects_FlipHorizontally | SpriteEffects_FlipVertically
	};
}