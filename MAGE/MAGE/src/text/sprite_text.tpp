#pragma once

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {
	
	template< typename ActionT >
	inline void SpriteText::ForEachColorString(ActionT action) {
		for (auto it = m_strings.begin(); it != m_strings.end(); ++it) {
			action(&*it);
		}
	}

	template< typename ActionT >
	inline void SpriteText::ForEachColorString(ActionT action) const {
		for (auto it = m_strings.cbegin(); it != m_strings.cend(); ++it) {
			action(&*it);
		}
	}
}