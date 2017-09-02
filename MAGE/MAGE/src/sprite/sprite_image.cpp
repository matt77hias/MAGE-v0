//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "sprite\sprite_image.hpp"
#include "logging\error.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations
//-----------------------------------------------------------------------------
namespace mage {

	SpriteImage::SpriteImage(SharedPtr< const Texture > texture,
		const Color &color, SpriteEffect effects)
		: Sprite(effects), m_color(color),
		m_texture_region(nullptr), m_texture(texture) {
	
		Assert(m_texture);
		SetTransparency(m_texture->HasAlpha());
	}
	
	SpriteImage::SpriteImage(SharedPtr< const Texture > texture, 
		const RECT &texture_region, const Color &color, SpriteEffect effects)
		: Sprite(effects), m_color(color),
		m_texture_region(MakeUnique< RECT >(texture_region)), 
		m_texture(texture) {
	
		Assert(m_texture);
		SetTransparency(m_texture->HasAlpha());
	}
	
	SpriteImage::SpriteImage(SharedPtr< const Texture > texture,
		const XMVECTOR &color, SpriteEffect effects)
		: Sprite(effects), m_color(),
		m_texture_region(nullptr), m_texture(texture) {
		
		Assert(m_texture);
		SetColor(color);
		SetTransparency(m_texture->HasAlpha());
	}
	
	SpriteImage::SpriteImage(SharedPtr< const Texture > texture, 
		const RECT &texture_region, const XMVECTOR &color, SpriteEffect effects)
		: Sprite(effects), m_color(),
		m_texture_region(MakeUnique< RECT >(texture_region)), 
		m_texture(texture) {

		Assert(m_texture);
		SetColor(color);
		SetTransparency(m_texture->HasAlpha());
	}

	SpriteImage::SpriteImage(const SpriteImage &sprite_image) 
		: Sprite(sprite_image), m_color(sprite_image.m_color),
		m_texture_region(MakeUnique< RECT >(*sprite_image.m_texture_region)), 
		m_texture(sprite_image.m_texture) {}
		
	SpriteImage::SpriteImage(SpriteImage &&sprite_image) = default;

	SpriteImage::~SpriteImage() = default;

	UniquePtr< Sprite > SpriteImage::CloneImplementation() const {
		return MakeUnique< SpriteImage >(*this);
	}

	void SpriteImage::SetTextureRegion(const RECT &texture_region) {
		m_texture_region = MakeUnique< RECT >(texture_region);
	}

	void SpriteImage::SetTexture(SharedPtr< const Texture > texture) {
		Assert(texture);

		m_texture = texture;
	}

	void SpriteImage::Draw(SpriteBatch &sprite_batch) const {
		sprite_batch.Draw(m_texture->Get(), GetColorVector(), GetSpriteEffects(), *GetTransform(), m_texture_region.get());
	}
}