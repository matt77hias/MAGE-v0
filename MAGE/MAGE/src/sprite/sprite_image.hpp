#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "sprite\sprite_object.hpp"
#include "texture\texture.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations
//-----------------------------------------------------------------------------
namespace mage {

	class SpriteImage : public SpriteObject {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		explicit SpriteImage(const string &name, SharedPtr< Texture > texture,
			const Color &color, SpriteEffect effects = SpriteEffect_None)
			: SpriteObject(name, effects), m_color(color),
			m_region(), m_texture(texture) {}
		explicit SpriteImage(const string &name, SharedPtr< Texture > texture, const RECT &region,
			const Color &color, SpriteEffect effects = SpriteEffect_None)
			: SpriteObject(name, effects), m_color(color),
			m_region(new RECT(region)), m_texture(texture) {}
		explicit SpriteImage(const string &name, SharedPtr< Texture > texture,
			const XMVECTOR &color = Colors::White, SpriteEffect effects = SpriteEffect_None)
			: SpriteObject(name, effects), m_color(),
			m_region(), m_texture(texture) {
			SetColor(color);
		}
		explicit SpriteImage(const string &name, SharedPtr< Texture > texture, const RECT &region,
			const XMVECTOR &color = Colors::White, SpriteEffect effects = SpriteEffect_None)
			: SpriteObject(name, effects), m_color(),
			m_region(new RECT(region)), m_texture(texture) {
			SetColor(color);
		}
		SpriteImage(const SpriteImage &sprite_image);
		SpriteImage(SpriteImage &&sprite_image) = default;
		virtual ~SpriteImage() = default;

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		SpriteImage &operator=(const SpriteImage &sprite_image);
		SpriteImage &operator=(SpriteImage &&sprite_image) = default;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		virtual SpriteImage *Clone() const {
			return new SpriteImage(*this);
		}

		void Draw(SpriteBatch &sprite_batch) const;

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
			return m_color;
		}
		void SetColor(const Color &color) {
			m_color = color;
		}
		void SetColor(const XMVECTOR &color) {
			XMStoreFloat4(&m_color, color);
		}

	private:

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		const XMVECTOR GetColorVector() const {
			return XMLoadFloat4(&m_color);
		}

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		Color m_color;
		UniquePtr< RECT > m_region;
		SharedPtr< Texture > m_texture;
	};
}