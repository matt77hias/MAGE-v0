//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "sprite\sprite.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations
//-----------------------------------------------------------------------------
namespace mage {

	Sprite::Sprite()
		: m_transform(MakeUnique< SpriteTransform >()), 
		m_effects(SpriteEffect::None) {}

	Sprite::Sprite(const Sprite &sprite)
		: m_transform(MakeUnique< SpriteTransform >(*sprite.m_transform)),
		m_effects(sprite.m_effects) {}

	Sprite::Sprite(Sprite &&sprite) = default;

	Sprite::~Sprite() = default;
}