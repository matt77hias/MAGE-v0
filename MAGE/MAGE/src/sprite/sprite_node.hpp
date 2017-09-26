#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "scene\scene_node.hpp"
#include "sprite\sprite.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	//-------------------------------------------------------------------------
	// SpriteNode
	//-------------------------------------------------------------------------

	/**
	 A class of sprite nodes.
	 */
	class SpriteNode : public SceneNode {

	public:

		//---------------------------------------------------------------------
		// Destructors
		//---------------------------------------------------------------------

		/**
		 Destructs this sprite node.
		 */
		virtual ~SpriteNode();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given sprite node to this sprite node.

		 @param[in]		sprite_node
						A reference to the sprite node to copy.
		 @return		A reference to the copy of the given sprite node (i.e. 
						this sprite node).
		 */
		SpriteNode &operator=(const SpriteNode &sprite_node) = delete;

		/**
		 Moves the given sprite node to this sprite node.

		 @param[in]		sprite_node
						A reference to the sprite node to move.
		 @return		A reference to the moved sprite node (i.e. this sprite 
						node).
		 */
		SpriteNode &operator=(SpriteNode &&sprite_node) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Clones this sprite node.

		 @return		A pointer to the clone of this sprite node.
		 */
		UniquePtr< SpriteNode > Clone() const {
			return static_pointer_cast< SpriteNode >(CloneImplementation());
		}

		/**
		 Returns the sprite transform of this node.

		 @return		A pointer to the sprite transform of this node.
		 */
		SpriteTransform *GetSpriteTransform() noexcept {
			return m_sprite->GetTransform();
		}

		/**
		 Returns the sprite transform of this node.

		 @return		A pointer to the sprite transform of this node.
		 */
		const SpriteTransform *GetSpriteTransform() const noexcept {
			return m_sprite->GetTransform();
		}

		/**
		 Returns the sprite of this sprite node.

		 @return		A pointer to the sprite of this sprite node.
		 */
		Sprite *GetSprite() noexcept {
			return m_sprite.get();
		}

		/**
		 Returns the sprite of this sprite node.

		 @return		A pointer to the sprite of this sprite node.
		 */
		const Sprite *GetSprite() const noexcept {
			return m_sprite.get();
		}

	protected:

		//---------------------------------------------------------------------
		// Constructors
		//---------------------------------------------------------------------

		/**
		 Constructs a sprite node.

		 @pre			@a sprite refers to a non @c nullptr.
		 @param[in]		name
						A reference to the name.
		 @param[in]		sprite
						A reference to the sprite to move.
		 */
		explicit SpriteNode(const string &name, UniquePtr< Sprite > &&sprite);

		/**
		 Constructs a sprite node from the given sprite node.

		 @param[in]		sprite_node
						A reference to the sprite node to copy.
		 */
		SpriteNode(const SpriteNode &sprite_node);

		/**
		 Constructs a sprite node by moving the given sprite node.

		 @param[in]		sprite_node
						A reference to the sprite node to move.
		 */
		SpriteNode(SpriteNode &&sprite_node);

	private:

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Clones this sprite node.

		 @return		A pointer to the clone of this sprite node.
		 */
		virtual UniquePtr< Node > CloneImplementation() const override = 0;

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		A pointer to the sprite of this sprite node.
		*/
		UniquePtr< Sprite > m_sprite;
	};

	//-------------------------------------------------------------------------
	// DerivedSpriteNode
	//-------------------------------------------------------------------------

	/**
	 A class of derived sprite nodes.

	 @tparam		SpriteT
					The Sprite type.
	 */
	template< typename SpriteT >
	class DerivedSpriteNode final : public SpriteNode {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a derived sprite node.

		 @tparam		ConstructorArgsT
						The constructor argument types of the Sprite.
		 @param[in]		name
						A reference to the name.
		 @param[in]		args
						A reference to the constructor arguments for the 
						sprite.
		 */
		template< typename... ConstructorArgsT >
		explicit DerivedSpriteNode(
			const string &name, ConstructorArgsT&&... args);

		/**
		 Constructs a derived sprite node.

		 @pre			@a sprite refers to a non @c nullptr.
		 @param[in]		name
						A reference to the name.
		 @param[in]		sprite
						A reference to the Sprite to move.
		 */
		explicit DerivedSpriteNode(
			const string &name, UniquePtr< SpriteT > &&sprite);

		/**
		 Constructs a derived sprite node from the given derived sprite node.

		 @param[in]		sprite_node
						A reference to the derived sprite node to copy.
		 */
		DerivedSpriteNode(const DerivedSpriteNode &sprite_node);

		/**
		 Constructs a derived sprite node by moving the given derived sprite 
		 node.

		 @param[in]		sprite_node
						A reference to the derived sprite node to move.
		 */
		DerivedSpriteNode(DerivedSpriteNode &&sprite_node);

		/**
		 Destructs this derived sprite node.
		 */
		virtual ~DerivedSpriteNode();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given derived sprite node to this derived sprite node.

		 @param[in]		sprite_node
						A reference to the derived sprite node to copy.
		 @return		A reference to the copy of the given derived sprite 
						node (i.e. this derived sprite node).
		 */
		DerivedSpriteNode &operator=(const DerivedSpriteNode &sprite_node) = delete;

		/**
		 Moves the given derived sprite node to this derived sprite node.

		 @param[in]		sprite_node
						A reference to the derived sprite node to move.
		 @return		A reference to the moved derived sprite node (i.e. this 
						derived sprite node).
		 */
		DerivedSpriteNode &operator=(DerivedSpriteNode &&sprite_node) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Clones this derived sprite node.

		 @return		A pointer to the clone of this derived sprite node.
		 */
		UniquePtr< DerivedSpriteNode > Clone() const {
			return static_pointer_cast< DerivedSpriteNode >(CloneImplementation());
		}

		/**
		 Returns the Sprite of this derived sprite node.

		 @return		A pointer to the Sprite of this derived sprite node.
		 */
		SpriteT *GetSprite() noexcept {
			return static_cast< SpriteT * >(SpriteNode::GetSprite());
		}

		/**
		 Returns the Sprite of this derived sprite node.

		 @return		A pointer to the Sprite of this derived sprite node.
		 */
		const SpriteT *GetSprite() const noexcept {
			return static_cast< const SpriteT * >(SpriteNode::GetSprite());
		}

	private:

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Clones this derived sprite node.

		 @return		A pointer to the clone of this derived sprite node.
		 */
		virtual UniquePtr< Node > CloneImplementation() const override;
	};
}

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "sprite\sprite_node.tpp"

#pragma endregion