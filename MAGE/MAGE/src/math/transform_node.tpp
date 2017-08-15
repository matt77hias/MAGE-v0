#pragma once

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	template< typename ActionT >
	inline void TransformNode::ForEachChildTransformNode(ActionT action) const {
		for (auto it = m_childs.cbegin(); it != m_childs.cend(); ++it) {
			// Visit child transform node.
			TransformNode *transform_node = (*it)->GetTransform();
			action(transform_node);
		}
	}
	
	template< typename ActionT >
	inline void TransformNode::ForEachDescendantTransformNode(ActionT action) const {
		for (auto it = m_childs.cbegin(); it != m_childs.cend(); ++it) {
			// Visit child transform node.
			TransformNode *transform_node = (*it)->GetTransform();
			action(transform_node);
			// Visit child transform node's child transform nodes.
			transform_node->ForEachDescendantTransformNode(action);
		}
	}

	template< typename ActionT >
	inline void TransformNode::ForEachChildNode(ActionT action) const {
		for (auto it = m_childs.cbegin(); it != m_childs.cend(); ++it) {
			// Visit child node.
			action(it->get());
		}
	}

	template< typename ActionT >
	inline void TransformNode::ForEachDescendantNode(ActionT action) const {
		for (auto it = m_childs.cbegin(); it != m_childs.cend(); ++it) {
			// Visit child node.
			action(it->get());
			// Visit child node's child nodes.
			(*it)->GetTransform()->ForEachDescendantNode(action);
		}
	}
}