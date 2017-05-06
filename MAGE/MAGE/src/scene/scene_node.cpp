//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "scene\scene_node.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	SceneNode::SceneNode(const string &name)
		: m_name(name) {}

	SceneNode::SceneNode(const SceneNode &scene_node) = default;

	SceneNode::SceneNode(SceneNode &&scene_node) = default;

	SceneNode::~SceneNode() = default;

	UniquePtr< Node > SceneNode::CloneImplementation() const {
		return UniquePtr< Node >(new SceneNode(*this));
	}
}