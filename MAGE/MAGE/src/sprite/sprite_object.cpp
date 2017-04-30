//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "sprite\sprite_object.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations
//-----------------------------------------------------------------------------
namespace mage {

	SpriteObject::SpriteObject(const string &name, SpriteEffect effects)
		: m_name(name), m_effects(effects), m_transform(new SpriteTransform()) {}

	SpriteObject::SpriteObject(const SpriteObject &sprite_object)
		: m_name(sprite_object.m_name),
		m_effects(sprite_object.m_effects),
		m_transform(new SpriteTransform(*sprite_object.m_transform)) {}
}