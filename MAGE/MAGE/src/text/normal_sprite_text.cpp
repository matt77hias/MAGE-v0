//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "text\normal_sprite_text.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	void NormalSpriteText::Draw(SpriteBatch &sprite_batch) const {
		ForEachSpriteTextItem([&](const SpriteTextItem &item) {
			GetRawFont()->DrawString(sprite_batch, item.GetText().c_str(), *GetTransform(), item.GetColorVector(), GetSpriteEffects());
		});
	}
}