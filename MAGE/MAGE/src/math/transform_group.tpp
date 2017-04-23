#pragma once

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {
	
	template< typename ActionT >
	inline void TransformGroup::ForEachTransform(ActionT action) const {

		for (vector< Transform * >::const_iterator it = m_transforms.cbegin(); it != m_transforms.cend(); ++it) {
			action(**it);
		}

		for (vector< TransformGroup >::const_iterator it = m_transform_groups.cbegin(); it != m_transform_groups.cend(); ++it) {
			it->ForEachTransform(action);
		}
	}
}
