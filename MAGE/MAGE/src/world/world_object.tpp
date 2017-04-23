#pragma once

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	template< typename ActionT >
	inline void WorldObject::ForEachChild(ActionT action) const {
		for (vector< SharedPtr< WorldObject > >::const_iterator it = m_childs.cbegin(); it != m_childs.cend(); ++it) {
			action(**it);
		}
	}
}