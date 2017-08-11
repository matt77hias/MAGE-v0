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
		: m_transform(UniquePtr< SpriteTransform >()), 
		m_active(true), m_name(name), 
		m_effects(effects) {}

	SpriteObject::SpriteObject(const SpriteObject &sprite_object)
		: m_transform(MakeUnique< SpriteTransform >(*sprite_object.m_transform)),
		m_active(sprite_object.m_active), m_name(sprite_object.m_name),
		m_effects(sprite_object.m_effects) {}

	SpriteObject::SpriteObject(SpriteObject &&sprite_object) = default;

	SpriteObject::~SpriteObject() = default;
}