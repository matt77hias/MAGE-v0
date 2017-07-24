//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "text\dropshadow_sprite_text.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	DropshadowSpriteText::DropshadowSpriteText(const string &name, SharedPtr< SpriteFont > font,
		const Color &shadow_color, SpriteEffect effects)
		: SpriteText(name, font, effects),
		m_shadow_color(shadow_color) {}

	DropshadowSpriteText::DropshadowSpriteText(const string &name, SharedPtr< SpriteFont > font,
		FXMVECTOR shadow_color, SpriteEffect effects)
		: SpriteText(name, font, effects),
		m_shadow_color() {
		SetShadowColor(shadow_color);
	}

	DropshadowSpriteText::DropshadowSpriteText(const DropshadowSpriteText &sprite_text) = default;

	DropshadowSpriteText::DropshadowSpriteText(DropshadowSpriteText &&sprite_text) = default;

	DropshadowSpriteText::~DropshadowSpriteText() = default;

	UniquePtr< SpriteObject > DropshadowSpriteText::CloneImplementation() const {
		return std::make_unique< DropshadowSpriteText >(*this);
	}

	void DropshadowSpriteText::Draw(SpriteBatch &sprite_batch) const {
		const wchar_t *text = c_str();
		SpriteTransform transform(*GetTransform());
		const XMVECTOR shadow_color = GetShadowColorVector();
		const SpriteEffect effects = GetSpriteEffects();
		
		// +1, +1
		transform.AddTranslation(XMFLOAT2(1.0f, 1.0f));
		GetRawFont()->DrawString(sprite_batch, text, transform, shadow_color, effects);
		// -1, +1
		transform.AddTranslationX(-2.0f);
		GetRawFont()->DrawString(sprite_batch, text, transform, shadow_color, effects);

		GetRawFont()->DrawString(sprite_batch, GetTextWithColors(), *GetTransform(), effects);
	}
}