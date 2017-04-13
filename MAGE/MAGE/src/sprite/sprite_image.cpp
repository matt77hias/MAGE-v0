//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "sprite\sprite_image.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations
//-----------------------------------------------------------------------------
namespace mage {

	SpriteImage::SpriteImage(const SpriteImage &sprite_image) 
		: m_name(sprite_image.m_name),
		m_color(sprite_image.m_color), m_effects(sprite_image.m_effects),
		m_region(new RECT(*sprite_image.m_region)), m_texture(sprite_image.m_texture),
		m_transform(new SpriteTransform(*sprite_image.m_transform)) {}
		
	SpriteImage &SpriteImage::operator=(const SpriteImage &sprite_image) {
		m_name    = sprite_image.m_name;
		m_color   = sprite_image.m_color;
		m_effects = sprite_image.m_effects;
		m_region.reset(new RECT(*sprite_image.m_region));
		m_texture = sprite_image.m_texture;
		m_transform.reset(new SpriteTransform(*sprite_image.m_transform));
		return (*this);
	}

	void SpriteImage::Draw(SpriteBatch &sprite_batch) const {
		sprite_batch.Draw(m_texture->GetTextureResourceView(), GetColorVector(), m_effects, *m_transform, m_region.get());
	}
}