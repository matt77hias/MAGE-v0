//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "sprite\text\dropshadow_sprite_text.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	DropshadowSpriteText::DropshadowSpriteText()
		: SpriteText(),
		m_shadow_color(SRGBA(1.0f)) {}

	DropshadowSpriteText::DropshadowSpriteText(
		const DropshadowSpriteText &sprite_text) = default;

	DropshadowSpriteText::DropshadowSpriteText(
		DropshadowSpriteText &&sprite_text) = default;

	DropshadowSpriteText::~DropshadowSpriteText() = default;

	UniquePtr< Sprite > DropshadowSpriteText::CloneImplementation() const {
		return MakeUnique< DropshadowSpriteText >(*this);
	}

	void DropshadowSpriteText::Draw(SpriteBatch &sprite_batch) const {
		const wchar_t * const text  = c_str();
		SpriteTransform transform(*GetTransform());
		const XMVECTOR shadow_color = XMLoadFloat4(&m_shadow_color);
		const SpriteEffect effects  = GetSpriteEffects();
		
		// +1, +1
		transform.AddTranslation(F32x2(1.0f, 1.0f));
		GetRawFont()->DrawString(sprite_batch, 
			text, transform, shadow_color, effects);
		// -1, +1
		transform.AddTranslationX(-2.0f);
		GetRawFont()->DrawString(sprite_batch, 
			text, transform, shadow_color, effects);

		GetRawFont()->DrawString(sprite_batch, 
			GetTextWithColors(), *GetTransform(), effects);
	}
}