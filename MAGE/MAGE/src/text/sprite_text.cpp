//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "text\sprite_text.hpp"
#include "logging\error.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	SpriteText::SpriteText(const string &name, SharedPtr< SpriteFont > font,
		SpriteEffect effects)
		: SpriteObject(name, effects), m_items(), m_font(font) {

		Assert(m_font);
	}

	SpriteText::SpriteText(const SpriteText &sprite_text) = default;

	SpriteText::SpriteText(SpriteText &&sprite_text) = default;

	SpriteText::~SpriteText() = default;

	void SpriteText::SetFont(SharedPtr< SpriteFont > font) {
		Assert(font);

		m_font = font;
	}

	void SpriteText::SetText(const wstring &text) {
		m_items.clear();
		m_items.push_back(SpriteTextItem(text));
	}

	void SpriteText::SetText(const wchar_t *text) {
		Assert(text);

		m_items.clear();
		m_items.push_back(SpriteTextItem(text));
	}

	void SpriteText::SetText(const SpriteTextItem &text) {
		m_items.clear();
		m_items.push_back(SpriteTextItem(text));
	}

	void SpriteText::AppendText(const wstring &text) {
		m_items.push_back(SpriteTextItem(text));
	}

	void SpriteText::AppendText(const wchar_t *text) {
		Assert(text);

		m_items.push_back(SpriteTextItem(text));
	}

	void SpriteText::AppendText(const SpriteTextItem &text) {
		m_items.push_back(SpriteTextItem(text));
	}
}