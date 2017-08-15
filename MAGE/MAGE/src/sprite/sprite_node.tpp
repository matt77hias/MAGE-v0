#pragma once

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	template< typename SpriteT >
	template< typename... ConstructorArgsT >
	DerivedSpriteNode< SpriteT >::DerivedSpriteNode(const string &name, ConstructorArgsT&&... args)
		: SpriteNode(name, MakeUnique< SpriteT >(std::forward< ConstructorArgsT >(args)...)) {}

	template< typename SpriteT >
	DerivedSpriteNode< SpriteT >::DerivedSpriteNode(const string &name, UniquePtr< SpriteT > &&sprite)
		: SpriteNode(name, std::move(sprite)) {}

	template< typename SpriteT >
	DerivedSpriteNode< SpriteT >::DerivedSpriteNode(const DerivedSpriteNode &sprite_node) = default;

	template< typename SpriteT >
	DerivedSpriteNode< SpriteT >::DerivedSpriteNode(DerivedSpriteNode &&sprite_node) = default;

	template< typename SpriteT >
	DerivedSpriteNode< SpriteT >::~DerivedSpriteNode() = default;

	template< typename SpriteT >
	UniquePtr< Node > DerivedSpriteNode< SpriteT >::CloneImplementation() const {
		return MakeUnique< DerivedSpriteNode >(*this);
	}
}