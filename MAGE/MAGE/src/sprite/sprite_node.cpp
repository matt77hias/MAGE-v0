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

	SpriteNode::SpriteNode(string name, UniquePtr< Sprite > &&sprite)
		: Node(std::move(name)), 
		m_sprite(std::move(sprite)) {
		
		Assert(m_sprite);
	}

	SpriteNode::SpriteNode(const SpriteNode &sprite_node)
		: Node(sprite_node), m_sprite(sprite_node.m_sprite->Clone()) {}

	SpriteNode::SpriteNode(SpriteNode &&light_node) = default;

	SpriteNode::~SpriteNode() = default;
}