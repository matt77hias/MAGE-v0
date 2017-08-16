//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "sprite\sprite_node.hpp"
#include "logging\error.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	SpriteNode::SpriteNode(const string &name, UniquePtr< Sprite > &&sprite)
		: SceneNode(name), m_sprite(std::move(sprite)) {
		Assert(m_sprite);
	}

	SpriteNode::SpriteNode(const SpriteNode &sprite_node)
		: SceneNode(sprite_node), m_sprite(sprite_node.GetSprite()->Clone()) {}

	SpriteNode::SpriteNode(SpriteNode &&light_node) = default;

	SpriteNode::~SpriteNode() = default;
}