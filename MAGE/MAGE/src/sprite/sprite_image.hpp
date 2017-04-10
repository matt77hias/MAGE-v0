#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "sprite\sprite_batch.hpp"
#include "texture\texture.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations
//-----------------------------------------------------------------------------
namespace mage {

	class SpriteImage {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		explicit SpriteImage(SharedPtr< Texture > texture,
			const XMVECTOR &color = Colors::White, SpriteEffect effects = SpriteEffect_None)
			: m_region(), m_texture(texture), 
			m_color(color), m_effects(effects), 
			m_transform() {}
		explicit SpriteImage(SharedPtr< Texture > texture, const RECT &region,
			const XMVECTOR &color = Colors::White, SpriteEffect effects = SpriteEffect_None)
			: m_region(new RECT(region)), m_texture(texture),
			m_color(color), m_effects(effects),
			m_transform() {}
		SpriteImage(const SpriteImage &sprite_image) = default;
		SpriteImage(SpriteImage &&sprite_image) = default;
		virtual ~SpriteImage() = default;

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		SpriteImage &operator=(const SpriteImage &sprite_image) = default;
		SpriteImage &operator=(SpriteImage &&sprite_image) = default;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		void Draw(SpriteBatch &sprite_batch) const {
			sprite_batch.Draw(m_texture->GetTextureResourceView(), m_color, m_effects, m_transform, m_region.get());
		}

		void SetRegion(const RECT &region) {
			m_region.reset(new RECT(region));
		}
		SharedPtr< Texture > GetTexture() const {
			return m_texture;
		}
		void SetTexture(SharedPtr< Texture > texture) {
			m_texture = texture;
		}
		const Color GetColor() const {
			Color c;
			XMStoreFloat4(&c, m_color);
			return c;
		}
		void SetColor(const Color &color) {
			m_color = XMLoadFloat4(&color);
		}
		void SetColor(const XMVECTOR &color) {
			m_color = color;
		}
		SpriteEffect GetSpriteEffects() const {
			return m_effects;
		}
		void SetSpriteEffects(SpriteEffect effects) {
			m_effects = effects;
		}
		SpriteTransform &GetTransform() {
			return m_transform;
		}
		const SpriteTransform &GetTransform() const {
			return m_transform;
		}

	private:

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		UniquePtr< RECT > m_region;
		SharedPtr< Texture > m_texture;
		XMVECTOR m_color;
		SpriteEffect m_effects;
		SpriteTransform m_transform;
	};
}