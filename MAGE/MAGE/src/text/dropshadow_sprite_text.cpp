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

	void DropshadowSpriteText::Draw(SpriteBatch &sprite_batch) const {
		SpriteTransform transform(*GetTransform());
		// +1, +1
		transform.AddTranslation(XMFLOAT2(1.0f, 1.0f));
		GetRawFont()->DrawString(sprite_batch, GetText().c_str(), transform, m_shadow_color, GetSpriteEffects());
		// -1, +1
		transform.AddTranslationX(-2.0f);
		GetRawFont()->DrawString(sprite_batch, GetText().c_str(), transform, m_shadow_color, GetSpriteEffects());

		GetRawFont()->DrawString(sprite_batch, GetText().c_str(), transform, GetColorVector(), GetSpriteEffects());
	}
}