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

	SharedPtr< SpriteObject > NormalSpriteText::CloneImplementation() const {
		return SharedPtr< NormalSpriteText >(new NormalSpriteText(*this));
	}

	void NormalSpriteText::Draw(SpriteBatch &sprite_batch) const {
		ForEachSpriteTextItem([&](const SpriteTextItem &item) {
			GetRawFont()->DrawString(sprite_batch, item.GetText().c_str(), *GetTransform(), item.GetColorVector(), GetSpriteEffects());
		});
	}
}