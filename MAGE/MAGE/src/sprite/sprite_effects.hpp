#pragma once

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {
	
	enum SpriteEffect {
		SpriteEffect_None             = 0,
		SpriteEffect_FlipHorizontally = 1,
		SpriteEffect_FlipVertically   = 2,
		SpriteEffect_FlipBoth         = SpriteEffect_FlipHorizontally | SpriteEffect_FlipVertically
	};
}