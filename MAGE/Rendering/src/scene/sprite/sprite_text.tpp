#pragma once

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage::rendering {
	
	template< typename ActionT >
	void SpriteText::ForEachColorString(ActionT action) {
		for (auto& str : m_strings) {
			action(str);
		}
	}

	template< typename ActionT >
	void SpriteText::ForEachColorString(ActionT action) const {
		for (const auto& str : m_strings) {
			action(str);
		}
	}
}