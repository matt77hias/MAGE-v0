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
		: SpriteObject(name, effects), m_text(L""), m_strings(), m_font(font) {

		Assert(m_font);
	}

	SpriteText::SpriteText(const SpriteText &sprite_text) = default;

	SpriteText::SpriteText(SpriteText &&sprite_text) noexcept = default;

	SpriteText::~SpriteText() noexcept {
		m_strings.clear();
	}

	void SpriteText::SetFont(SharedPtr< SpriteFont > font) {
		Assert(font);

		m_font = font;
	}

	void SpriteText::SetText(const wstring &text) {
		m_strings.clear();
		m_strings.push_back(ColorString(text));
		m_text = text;
	}

	void SpriteText::SetText(const wchar_t *text) {
		Assert(text);

		m_strings.clear();
		m_strings.push_back(ColorString(text));
		m_text = text;
	}

	void SpriteText::SetText(const ColorString &text) {
		m_strings.clear();
		m_strings.push_back(ColorString(text));
		m_text = text.GetString();
	}

	void SpriteText::AppendText(const wstring &text) {
		m_strings.push_back(ColorString(text));
		m_text += text;
	}

	void SpriteText::AppendText(const wchar_t *text) {
		Assert(text);

		m_strings.push_back(ColorString(text));
		m_text += text;
	}

	void SpriteText::AppendText(const ColorString &text) {
		m_strings.push_back(ColorString(text));
		m_text += text.GetString();
	}
}