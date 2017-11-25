//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "sprite\sprite_node.hpp"
#include "utils\logging\error.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	SpriteNode::SpriteNode(UniquePtr< Sprite > &&sprite)
		: Node("Sprite"), 
		m_sprite(std::move(sprite)) {
		
		Assert(m_sprite);
	}

	SpriteNode::SpriteNode(const SpriteNode &sprite_node)
		: Node(sprite_node), m_sprite(sprite_node.m_sprite->Clone()) {}

	SpriteNode::SpriteNode(SpriteNode &&light_node) = default;

	SpriteNode::~SpriteNode() = default;
}