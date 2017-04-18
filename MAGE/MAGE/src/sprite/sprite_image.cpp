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
		: SpriteObject(sprite_image), m_color(sprite_image.m_color),
		m_region(new RECT(*sprite_image.m_region)), m_texture(sprite_image.m_texture) {}
		
	SpriteImage &SpriteImage::operator=(const SpriteImage &sprite_image) {
		m_color   = sprite_image.m_color;
		m_region.reset(new RECT(*sprite_image.m_region));
		m_texture = sprite_image.m_texture;
		return (*this);
	}

	void SpriteImage::Draw(SpriteBatch &sprite_batch) const {
		sprite_batch.Draw(m_texture->GetTextureResourceView(), GetColorVector(), GetSpriteEffects(), *GetTransform(), m_region.get());
	}
}