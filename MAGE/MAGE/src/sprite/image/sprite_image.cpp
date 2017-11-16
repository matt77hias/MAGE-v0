//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "sprite\image\sprite_image.hpp"
#include "utils\logging\error.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations
//-----------------------------------------------------------------------------
namespace mage {

	SpriteImage::SpriteImage()
		: Sprite(), 
		m_base_color(SRGBA(1.0f)),
		m_base_color_texture(), 
		m_base_color_texture_region(nullptr) {}
	
	SpriteImage::SpriteImage(const SpriteImage &sprite_image) 
		: Sprite(sprite_image), 
		m_base_color(sprite_image.m_base_color),
		m_base_color_texture(sprite_image.m_base_color_texture),
		m_base_color_texture_region(
			MakeUnique< RECT >(*sprite_image.m_base_color_texture_region)) {}
		
	SpriteImage::SpriteImage(SpriteImage &&sprite_image) = default;

	SpriteImage::~SpriteImage() = default;

	UniquePtr< Sprite > SpriteImage::CloneImplementation() const {
		return MakeUnique< SpriteImage >(*this);
	}

	void SpriteImage::Draw(SpriteBatch &sprite_batch) const {
		sprite_batch.Draw(
			GetBaseColorSRV(), XMLoadFloat4(&m_base_color), 
			GetSpriteEffects(), *GetTransform(), 
			GetBaseColorTextureRegion());
	}
}