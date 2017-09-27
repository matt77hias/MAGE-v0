#pragma once

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	template< typename ActionT >
	inline void TransformNode::ForEachChildTransformNode(
		ActionT action) const {
		
		for (const auto &child : m_childs) {
			// Visit child transform node.
			TransformNode * const transform_node = child->GetTransform();
			action(transform_node);
		}
	}
	
	template< typename ActionT >
	inline void TransformNode::ForEachDescendantTransformNode(
		ActionT action) const {
		
		for (const auto &child : m_childs) {
			// Visit child transform node.
			TransformNode * const transform_node = child->GetTransform();
			action(transform_node);
			// Visit child transform node's child transform nodes.
			transform_node->ForEachDescendantTransformNode(action);
		}
	}

	template< typename ActionT >
	inline void TransformNode::ForEachChildNode(ActionT action) const {
		
		for (const auto &child : m_childs) {
			// Visit child node.
			action(child.get());
		}
	}

	template< typename ActionT >
	inline void TransformNode::ForEachDescendantNode(ActionT action) const {
		
		for (const auto &child : m_childs) {
			// Visit child node.
			action(child.get());
			// Visit child node's child nodes.
			child->GetTransform()->ForEachDescendantNode(action);
		}
	}
}