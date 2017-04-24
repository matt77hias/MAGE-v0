#pragma once

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {
	
	template< typename ActionT >
	inline void TransformNode::ForEachTransform(ActionT action) const {
		action(m_transform);

		for (vector< TransformNode * >::const_iterator it = m_transform_nodes.cbegin(); it != m_transform_nodes.cend(); ++it) {
			(*it)->ForEachTransform(action);
		}
	}
}
