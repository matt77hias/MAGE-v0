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

		explicit SpriteImage(const string &name, SharedPtr< Texture > texture,
			const Color &color, SpriteEffect effects = SpriteEffect_None)
			: m_name(name), m_color(color), m_effects(effects),
			m_region(), m_texture(texture),
			m_transform(new SpriteTransform()) {}
		explicit SpriteImage(const string &name, SharedPtr< Texture > texture, const RECT &region,
			const Color &color, SpriteEffect effects = SpriteEffect_None)
			: m_name(name), m_color(color), m_effects(effects),
			m_region(new RECT(region)), m_texture(texture),
			m_transform(new SpriteTransform()) {}
		explicit SpriteImage(const string &name, SharedPtr< Texture > texture,
			const XMVECTOR &color = Colors::White, SpriteEffect effects = SpriteEffect_None)
			: m_name(name), m_color(), m_effects(effects),
			m_region(), m_texture(texture),
			m_transform(new SpriteTransform()) {
			SetColor(color);
		}
		explicit SpriteImage(const string &name, SharedPtr< Texture > texture, const RECT &region,
			const XMVECTOR &color = Colors::White, SpriteEffect effects = SpriteEffect_None)
			: m_name(name), m_color(), m_effects(effects),
			m_region(new RECT(region)), m_texture(texture),
			m_transform(new SpriteTransform()) {
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

		void Draw(SpriteBatch &sprite_batch) const;

		const string &GetName() const {
			return m_name;
		}
		void SetName(const string &name) {
			m_name = name;
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
			return m_color;
		}
		void SetColor(const Color &color) {
			m_color = color;
		}
		void SetColor(const XMVECTOR &color) {
			XMStoreFloat4(&m_color, color);
		}
		void SetSpriteEffects(SpriteEffect effects) {
			m_effects = effects;
		}
		SpriteTransform *GetTransform() {
			return m_transform.get();
		}
		const SpriteTransform *GetTransform() const {
			return m_transform.get();
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

		string m_name;

		Color m_color;
		SpriteEffect m_effects;
		UniquePtr< RECT > m_region;
		SharedPtr< Texture > m_texture;
		UniquePtr< SpriteTransform > m_transform;
	};
}