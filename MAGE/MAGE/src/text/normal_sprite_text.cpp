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

	NormalSpriteText::NormalSpriteText(const string &name, SharedPtr< SpriteFont > font,
		SpriteEffect effects)
		: SpriteText(name, font, effects) {}

	NormalSpriteText::NormalSpriteText(const NormalSpriteText &sprite_text) = default;

	NormalSpriteText::NormalSpriteText(NormalSpriteText &&sprite_text) = default;

	NormalSpriteText::~NormalSpriteText() = default;

	UniquePtr< SpriteObject > NormalSpriteText::CloneImplementation() const {
		return UniquePtr< NormalSpriteText >(new NormalSpriteText(*this));
	}

	void NormalSpriteText::Draw(SpriteBatch &sprite_batch) const {
		GetRawFont()->DrawString(sprite_batch, GetTextWithColors(), *GetTransform(), GetSpriteEffects());
	}
}