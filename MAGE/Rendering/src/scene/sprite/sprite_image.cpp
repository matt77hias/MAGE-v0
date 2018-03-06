//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "scene\node.hpp"
#include "scene\sprite\sprite_image.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations
//-----------------------------------------------------------------------------
namespace mage::rendering {

	SpriteImage::SpriteImage() noexcept
		: Component(),
		m_sprite_transform(),
		m_sprite_effects(SpriteEffect::None),
		m_base_color(SRGB(1.0f)),
		m_base_color_texture_region{},
		m_base_color_texture() {}
	
	SpriteImage::SpriteImage(const SpriteImage& sprite) noexcept = default;
		
	SpriteImage::SpriteImage(SpriteImage&& sprite) noexcept = default;

	SpriteImage::~SpriteImage() = default;

	SpriteImage& SpriteImage
		::operator=(const SpriteImage& sprite) noexcept = default;

	SpriteImage& SpriteImage
		::operator=(SpriteImage&& sprite) noexcept = default;

	void SpriteImage::Draw(SpriteBatch& sprite_batch) const {
		if (HasMaximumBaseColorTextureRegion()) {
			sprite_batch.Draw(GetBaseColorSRV(), 
				              XMLoad(m_base_color),
				              m_sprite_effects, 
				              m_sprite_transform,
				              nullptr);
		}
		else {
			sprite_batch.Draw(GetBaseColorSRV(), 
				              XMLoad(m_base_color),
				              m_sprite_effects, 
				              m_sprite_transform,
				              &m_base_color_texture_region);
		}
	}
}