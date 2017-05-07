#pragma once

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {
	
	template< typename ActionT >
	inline void SpriteText::ForEachColorString(ActionT action) {
		for (auto it = m_text.begin(); it != m_text.end(); ++it) {
			action(*it);
		}
	}

	template< typename ActionT >
	inline void SpriteText::ForEachColorString(ActionT action) const {
		for (auto it = m_text.cbegin(); it != m_text.cend(); ++it) {
			action(*it);
		}
	}
}