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

	void OutlineSpriteText::Draw(SpriteBatch &sprite_batch) const {
		SpriteTransform transform(*GetTransform());
		// +1, +1
		transform.AddTranslation(XMFLOAT2(1.0f, 1.0f));
		GetRawFont()->DrawString(sprite_batch, GetText().c_str(), transform, m_border_color, GetSpriteEffects());
		// -1, +1
		transform.AddTranslationX(-2.0f);
		GetRawFont()->DrawString(sprite_batch, GetText().c_str(), transform, m_border_color, GetSpriteEffects());
		// -1, -1
		transform.AddTranslationY(-2.0f);
		GetRawFont()->DrawString(sprite_batch, GetText().c_str(), transform, m_border_color, GetSpriteEffects());
		// +1, -1
		transform.AddTranslationX(2.0f);
		GetRawFont()->DrawString(sprite_batch, GetText().c_str(), transform, m_border_color, GetSpriteEffects());

		GetRawFont()->DrawString(sprite_batch, GetText().c_str(), *GetTransform(), GetColorVector(), GetSpriteEffects());
	}
}