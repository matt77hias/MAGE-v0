//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "math\transform_node.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	TransformNode::TransformNode(const TransformNode &transform_node)
		: m_transform(new Transform(*transform_node.m_transform)), 
		m_parent(nullptr), m_childs() {

		transform_node.ForEachChildTransformNode([&](const TransformNode &child_transform_node) {
			AddChildTransformNode(child_transform_node.Clone());
		});

		SetDirty();
	}

	TransformNode::~TransformNode() {
		RemoveAllChildTransformNodes();
	}

	bool TransformNode::HasChildTransformNode(SharedPtr< const TransformNode > transform_node) const {
		return std::find(m_childs.begin(), m_childs.end(), transform_node) != m_childs.end();
	}

	void TransformNode::AddChildTransformNode(SharedPtr< TransformNode > transform_node) {
		if (!transform_node) {
			return;
		}
		if (transform_node->m_parent && transform_node->m_parent != this) {
			transform_node->m_parent->RemoveChildTransformNode(transform_node);
		}

		transform_node->m_parent = this;
		transform_node->SetDirty();
		
		m_childs.push_back(transform_node);
	}

	void TransformNode::RemoveChildTransformNode(SharedPtr< TransformNode > transform_node) {
		if (transform_node->m_parent != this) {
			return;
		}

		transform_node->m_parent = nullptr;
		transform_node->SetDirty();
		
		vector< SharedPtr< TransformNode > >::iterator it = std::find(m_childs.begin(), m_childs.end(), transform_node);
		if (it != m_childs.end()) {
			m_childs.erase(it);
		}
	}

	void TransformNode::RemoveAllChildTransformNodes() {
		
		ForEachChildTransformNode([](TransformNode &transform_node) {
			transform_node.m_parent = nullptr;
			transform_node.SetDirty();
		});

		m_childs.clear();
	}
}