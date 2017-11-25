#pragma once

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	template< typename SpriteT >
	DerivedSpriteNode< SpriteT >::DerivedSpriteNode()
		: SpriteNode(MakeUnique< SpriteT >()) {}

	template< typename SpriteT >
	DerivedSpriteNode< SpriteT >::DerivedSpriteNode(
		const DerivedSpriteNode &sprite_node) = default;

	template< typename SpriteT >
	DerivedSpriteNode< SpriteT >::DerivedSpriteNode(
		DerivedSpriteNode &&sprite_node) = default;

	template< typename SpriteT >
	DerivedSpriteNode< SpriteT >::~DerivedSpriteNode() = default;

	template< typename SpriteT >
	UniquePtr< Node > DerivedSpriteNode< SpriteT >::CloneImplementation() const {
		return MakeUnique< DerivedSpriteNode >(*this);
	}
}