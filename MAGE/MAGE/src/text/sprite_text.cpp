//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "text\sprite_text.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations
//-----------------------------------------------------------------------------
namespace mage {

	SpriteText::SpriteText(const string &name, const wstring &text, SharedPtr< SpriteFont > font,
		const XMVECTOR &color, SpriteEffect effects)
		: m_name(name), m_text(text), m_font(font),
		m_color(color), m_effects(effects),
		m_transform(new SpriteTransform()) {}
		
	SpriteText::SpriteText(const SpriteText &sprite_text)
		: m_name(sprite_text.m_name), m_text(sprite_text.m_text), m_font(sprite_text.m_font),
		m_color(sprite_text.m_color), m_effects(sprite_text.m_effects),
		m_transform(new SpriteTransform(*sprite_text.m_transform)) {}

	SpriteText &SpriteText::operator=(const SpriteText &sprite_text) {
		m_name    = sprite_text.m_name;
		m_text    = sprite_text.m_text;
		m_font    = sprite_text.m_font;
		m_color   = sprite_text.m_color;
		m_effects = sprite_text.m_effects;
		m_transform.reset(new SpriteTransform(*sprite_text.m_transform));
		return (*this);
	}
}