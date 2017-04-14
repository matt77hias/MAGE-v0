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
		// +1, +1
		SpriteTransform transform1(*GetTransform());
		transform1.AddTranslation(XMFLOAT2(1.0f, 1.0f));
		// -1, +1
		SpriteTransform transform2(*GetTransform());
		transform2.AddTranslation(XMFLOAT2(-1.0f, 1.0f));
		// -1, -1
		SpriteTransform transform3(*GetTransform());
		transform3.AddTranslation(XMFLOAT2(-1.0f, -1.0f));
		// +1, -1
		SpriteTransform transform4(*GetTransform());
		transform4.AddTranslation(XMFLOAT2(1.0f, -1.0f));

		const XMVECTOR border_color = GetBorderColorVector();
		ForEachSpriteTextItem([&](const SpriteTextItem &item) {
			GetRawFont()->DrawString(sprite_batch, item.GetText().c_str(), transform1, border_color, GetSpriteEffects());
			GetRawFont()->DrawString(sprite_batch, item.GetText().c_str(), transform2, border_color, GetSpriteEffects());
			GetRawFont()->DrawString(sprite_batch, item.GetText().c_str(), transform3, border_color, GetSpriteEffects());
			GetRawFont()->DrawString(sprite_batch, item.GetText().c_str(), transform4, border_color, GetSpriteEffects());
		});

		ForEachSpriteTextItem([&](const SpriteTextItem &item) {
			GetRawFont()->DrawString(sprite_batch, item.GetText().c_str(), *GetTransform(), item.GetColorVector(), GetSpriteEffects());
		});
	}
}