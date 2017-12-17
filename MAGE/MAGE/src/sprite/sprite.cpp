//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "scene\scene.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations
//-----------------------------------------------------------------------------
namespace mage {

	Sprite::Sprite() noexcept
		: Component(),
		m_sprite_transform(), 
		m_effects(SpriteEffect::None) {}

	Sprite::Sprite(const Sprite &sprite) noexcept = default;

	Sprite::Sprite(Sprite &&sprite) noexcept = default;

	Sprite::~Sprite() = default;

	Sprite &Sprite::operator=(const Sprite &sprite) noexcept = default;

	Sprite &Sprite::operator=(Sprite &&sprite) noexcept = default;
}