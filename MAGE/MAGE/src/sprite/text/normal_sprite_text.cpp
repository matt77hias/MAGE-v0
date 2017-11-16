//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "sprite\text\normal_sprite_text.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	NormalSpriteText::NormalSpriteText() = default;

	NormalSpriteText::NormalSpriteText(
		const NormalSpriteText &sprite_text) = default;

	NormalSpriteText::NormalSpriteText(
		NormalSpriteText &&sprite_text) = default;

	NormalSpriteText::~NormalSpriteText() = default;

	UniquePtr< Sprite > NormalSpriteText::CloneImplementation() const {
		return MakeUnique< NormalSpriteText >(*this);
	}

	void NormalSpriteText::Draw(SpriteBatch &sprite_batch) const {
		GetRawFont()->DrawString(sprite_batch, 
			GetTextWithColors(), *GetTransform(), GetSpriteEffects());
	}
}