#pragma once

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	template< typename ActionT >
	inline void TransformNode::ForEachChildTransformNode(ActionT action) const {
		for (vector< SharedPtr< TransformNode > >::const_iterator it = m_childs.cbegin(); it != m_childs.cend(); ++it) {
			action(**it);
		}
	}
	
	template< typename ActionT >
	inline void TransformNode::ForEachDescendantTransformNode(ActionT action) const {
		for (vector< SharedPtr< TransformNode > >::const_iterator it = m_childs.cbegin(); it != m_childs.cend(); ++it) {
			action(**it);
			(*it)->ForEachChildTransformNode(action);
		}
	}
}