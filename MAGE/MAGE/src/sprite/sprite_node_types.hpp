#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "sprite\sprite_node.hpp"
#include "sprite\image\sprite_image.hpp"
#include "sprite\text\normal_sprite_text.hpp"
#include "sprite\text\dropshadow_sprite_text.hpp"
#include "sprite\text\outline_sprite_text.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	//-------------------------------------------------------------------------
	// Type Declarations and Definitions
	//-------------------------------------------------------------------------

	/**
	 A class of sprite image nodes.
	 */
	using SpriteImageNode = DerivedSpriteNode< SpriteImage >;

	/**
	 A class of normal sprite text nodes.
	 */
	using NormalSpriteTextNode = DerivedSpriteNode< NormalSpriteText >;

	/**
	 A class of dropshadow sprite text nodes.
	 */
	using DropshadowSpriteTextNode = DerivedSpriteNode< DropshadowSpriteText >;

	/**
	 A class of outline sprite text nodes.
	 */
	using OutlineSpriteTextNode = DerivedSpriteNode< OutlineSpriteText >;
}
