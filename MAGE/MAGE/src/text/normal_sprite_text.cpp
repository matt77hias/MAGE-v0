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
		GetRawFont()->DrawString(sprite_batch, GetText().c_str(), *GetTransform(), GetColorVector(), GetSpriteEffects());
	}
}