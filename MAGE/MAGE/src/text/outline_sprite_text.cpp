//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "text\outline_sprite_text.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	OutlineSpriteText::OutlineSpriteText(const string &name, SharedPtr< SpriteFont > font,
		const Color &border_color, SpriteEffect effects)
		: SpriteText(name, font, effects),
		m_border_color(border_color) {}

	OutlineSpriteText::OutlineSpriteText(const string &name, SharedPtr< SpriteFont > font,
		const XMVECTOR &border_color, SpriteEffect effects)
		: SpriteText(name, font, effects),
		m_border_color() {
		SetBorderColor(border_color);
	}

	OutlineSpriteText::OutlineSpriteText(const OutlineSpriteText &sprite_text) = default;

	OutlineSpriteText::OutlineSpriteText(OutlineSpriteText &&sprite_text) noexcept = default;

	OutlineSpriteText::~OutlineSpriteText() noexcept = default;

	UniquePtr< SpriteObject > OutlineSpriteText::CloneImplementation() const {
		return UniquePtr< OutlineSpriteText >(new OutlineSpriteText(*this));
	}

	void OutlineSpriteText::Draw(SpriteBatch &sprite_batch) const {
		const wchar_t *text = c_str();
		SpriteTransform transform(*GetTransform());
		const XMVECTOR border_color = GetBorderColorVector();
		const SpriteEffect effects = GetSpriteEffects();
		
		// +1, +1
		transform.AddTranslation(XMFLOAT2(1.0f, 1.0f));
		GetRawFont()->DrawString(sprite_batch, text, transform, border_color, effects);
		// -1, +1
		transform.AddTranslationX(-2.0f);
		GetRawFont()->DrawString(sprite_batch, text, transform, border_color, effects);
		// -1, -1
		transform.AddTranslationY(-2.0f);
		GetRawFont()->DrawString(sprite_batch, text, transform, border_color, effects);
		// +1, -1
		transform.AddTranslationX(2.0f);
		GetRawFont()->DrawString(sprite_batch, text, transform, border_color, effects);

		GetRawFont()->DrawString(sprite_batch, GetTextWithColors(), *GetTransform(), effects);
	}
}