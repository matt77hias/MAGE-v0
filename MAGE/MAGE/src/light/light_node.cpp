//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "light\light_node.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	LightNode::LightNode(const string &name, UniquePtr< Light > &&light)
		: Node(), m_name(name), m_light(std::move(light)) {}

	LightNode::LightNode(const LightNode &light_node)
		: Node(light_node), m_name(light_node.m_name),
		m_light(light_node.GetLight()->Clone()) {}

	LightNode::LightNode(LightNode &&light_node) = default;

	LightNode::~LightNode() = default;
}