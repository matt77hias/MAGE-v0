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
		const XMVECTOR &shadow_color, SpriteEffect effects)
		: SpriteText(name, font, effects),
		m_shadow_color() {
		SetShadowColor(shadow_color);
	}

	DropshadowSpriteText::DropshadowSpriteText(const DropshadowSpriteText &sprite_text) = default;

	DropshadowSpriteText::DropshadowSpriteText(DropshadowSpriteText &&sprite_text) = default;

	DropshadowSpriteText::~DropshadowSpriteText() = default;

	SharedPtr< SpriteObject > DropshadowSpriteText::CloneImplementation() const {
		return SharedPtr< DropshadowSpriteText >(new DropshadowSpriteText(*this));
	}

	void DropshadowSpriteText::Draw(SpriteBatch &sprite_batch) const {
		// +1, +1
		SpriteTransform transform1(*GetTransform());
		transform1.AddTranslation(XMFLOAT2(1.0f, 1.0f));
		// -1, +1
		SpriteTransform transform2(*GetTransform());
		transform2.AddTranslation(XMFLOAT2(-1.0f, 1.0f));
		
		const XMVECTOR shadow_color = GetShadowColorVector();
		ForEachSpriteTextItem([&](const SpriteTextItem &item) {
			GetRawFont()->DrawString(sprite_batch, item.GetText().c_str(), transform1, shadow_color, GetSpriteEffects());
			GetRawFont()->DrawString(sprite_batch, item.GetText().c_str(), transform2, shadow_color, GetSpriteEffects());
		});

		ForEachSpriteTextItem([&](const SpriteTextItem &item) {
			GetRawFont()->DrawString(sprite_batch, item.GetText().c_str(), *GetTransform(), item.GetColorVector(), GetSpriteEffects());
		});
	}
}