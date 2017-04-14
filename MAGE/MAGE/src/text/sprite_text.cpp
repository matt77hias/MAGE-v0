//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "text\sprite_text.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	SpriteText::SpriteText(const SpriteText &sprite_text)
		: m_name(sprite_text.m_name), m_items(sprite_text.m_items), m_effects(sprite_text.m_effects),
		m_font(sprite_text.m_font), m_transform(new SpriteTransform(*sprite_text.m_transform)) {}

	SpriteText &SpriteText::operator=(const SpriteText &sprite_text) {
		m_name    = sprite_text.m_name;
		m_items   = sprite_text.m_items;
		m_effects = sprite_text.m_effects;
		m_font    = sprite_text.m_font;
		m_transform.reset(new SpriteTransform(*sprite_text.m_transform));
		return (*this);
	}

	void SpriteText::SetColor(const Color &color) {
		ForEachSpriteTextItem([&](SpriteTextItem &item) {
			item.SetColor(color);
		});
	}
	void SpriteText::SetColor(const XMVECTOR &color) {
		ForEachSpriteTextItem([&](SpriteTextItem &item) {
			item.SetColor(color);
		});
	}

	const XMVECTOR SpriteText::MeasureString() const {
		XMVECTOR result = XMVectorSet(0, 0, 0, 0);
		ForEachSpriteTextItem([&](const SpriteTextItem &item) {
			result = XMVectorMax(result, m_font->MeasureString(item.GetText().c_str()));
		});
		return result;
	}
}