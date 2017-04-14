#pragma once

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {
	
	template< typename ActionT >
	inline void SpriteText::ForEachSpriteTextItem(ActionT action) {
		for (vector< SpriteTextItem >::iterator it = m_items.begin(); it != m_items.end(); ++it) {
			action(*it);
		}
	}

	template< typename ActionT >
	inline void SpriteText::ForEachSpriteTextItem(ActionT action) const {
		for (vector< SpriteTextItem >::const_iterator it = m_items.cbegin(); it != m_items.cend(); ++it) {
			action(*it);
		}
	}
}