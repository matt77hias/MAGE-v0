#pragma once

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {
	
	template< typename ActionT >
	inline void SpriteText::ForEachColorString(ActionT action) {
		for (auto &str : m_strings) {
			action(&str);
		}
	}

	template< typename ActionT >
	inline void SpriteText::ForEachColorString(ActionT action) const {
		for (const auto &str : m_strings) {
			action(&str);
		}
	}
}