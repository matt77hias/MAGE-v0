//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "sprite\text\sprite_text.hpp"
#include "resource\resource_manager.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	SpriteText::SpriteText()
		: Sprite(), 
		m_text(), 
		m_strings(), 
		m_font(ResourceManager::Get()->
			GetOrCreateSpriteFont(L"assets/fonts/consolas.spritefont")) {}

	SpriteText::SpriteText(const SpriteText &sprite_text) = default;

	SpriteText::SpriteText(SpriteText &&sprite_text) = default;

	SpriteText::~SpriteText() {
		m_strings.clear();
	}

	void SpriteText::SetText(const wstring &text) {
		m_strings.clear();
		m_strings.emplace_back(text);
		m_text = text;
	}

	void SpriteText::SetText(const wchar_t *text) {
		Assert(text);

		m_strings.clear();
		m_strings.emplace_back(text);
		m_text = text;
	}

	void SpriteText::SetText(const ColorString &text) {
		m_strings.clear();
		m_strings.push_back(text);
		m_text = text.GetString();
	}

	void SpriteText::AppendText(const wstring &text) {
		m_strings.emplace_back(text);
		m_text += text;
	}

	void SpriteText::AppendText(const wchar_t *text) {
		Assert(text);

		m_strings.emplace_back(text);
		m_text += text;
	}

	void SpriteText::AppendText(const ColorString &text) {
		m_strings.push_back(text);
		m_text += text.GetString();
	}
}