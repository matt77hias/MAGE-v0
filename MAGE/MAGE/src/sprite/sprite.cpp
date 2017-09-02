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

	Sprite::Sprite(SpriteEffect effects)
		: m_transform(MakeUnique< SpriteTransform >()), 
		m_transparent(false), m_effects(effects) {}

	Sprite::Sprite(const Sprite &sprite)
		: m_transform(MakeUnique< SpriteTransform >(*sprite.m_transform)),
		m_transparent(sprite.m_transparent), m_effects(sprite.m_effects) {}

	Sprite::Sprite(Sprite &&sprite) = default;

	Sprite::~Sprite() = default;
}