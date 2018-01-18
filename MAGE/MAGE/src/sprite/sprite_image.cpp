//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "scene\scene.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Defines
//-----------------------------------------------------------------------------
#pragma region

#define MAGE_DEFAULT_BASE_COLOR 1.0f

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations
//-----------------------------------------------------------------------------
namespace mage {

	SpriteImage::SpriteImage() noexcept
		: Component(),
		m_sprite_transform(),
		m_sprite_effects(SpriteEffect::None),
		m_base_color(SRGB(MAGE_DEFAULT_BASE_COLOR)),
		m_base_color_texture_region{},
		m_base_color_texture() {}
	
	SpriteImage::SpriteImage(const SpriteImage &sprite) noexcept = default;
		
	SpriteImage::SpriteImage(SpriteImage &&sprite) noexcept = default;

	SpriteImage::~SpriteImage() = default;

	SpriteImage &SpriteImage
		::operator=(const SpriteImage &sprite) noexcept = default;

	SpriteImage &SpriteImage
		::operator=(SpriteImage &&sprite) noexcept = default;

	void SpriteImage::Draw(SpriteBatch &sprite_batch) const {
		if (HasMaximumBaseColorTextureRegion()) {
			sprite_batch.Draw(GetBaseColorSRV(), 
				              XMLoadFloat4(&m_base_color),
				              m_sprite_effects, 
				              m_sprite_transform,
				              nullptr);
		}
		else {
			sprite_batch.Draw(GetBaseColorSRV(), 
				              XMLoadFloat4(&m_base_color),
				              m_sprite_effects, 
				              m_sprite_transform,
				              &m_base_color_texture_region);
		}
	}
}