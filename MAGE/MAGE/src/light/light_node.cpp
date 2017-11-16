//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "light\light_node.hpp"
#include "utils\logging\error.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	LightNode::LightNode(string name, UniquePtr< Light > &&light)
		: Node(std::move(name)), 
		m_light(std::move(light)) {
		
		Assert(m_light);
	}

	LightNode::LightNode(const LightNode &light_node)
		: Node(light_node), m_light(light_node.m_light->Clone()) {}

	LightNode::LightNode(LightNode &&light_node) = default;

	LightNode::~LightNode() = default;
}