//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "light\light_node.hpp"
#include "logging\error.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	LightNode::LightNode(const string &name, UniquePtr< Light > &&light)
		: SceneNode(name), m_light(std::move(light)) {
		
		Assert(m_light);
	}

	LightNode::LightNode(const LightNode &light_node)
		: SceneNode(light_node), m_light(light_node.m_light->Clone()) {}

	LightNode::LightNode(LightNode &&light_node) = default;

	LightNode::~LightNode() = default;
}