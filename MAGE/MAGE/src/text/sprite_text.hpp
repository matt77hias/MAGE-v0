#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "font\sprite_font.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations
//-----------------------------------------------------------------------------

namespace mage {

	class SpriteText {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		explicit SpriteText(const wstring &text, SharedPtr< SpriteFont > font,
			const XMVECTOR &color = Colors::White, SpriteEffect effects = SpriteEffect_None) 
			: m_text(text), m_font(font), 
			m_color(color), m_effects(effects), 
			m_transform() {}
		SpriteText(const SpriteText &sprite_text) = default;
		SpriteText(SpriteText &&sprite_text) = default;
		virtual ~SpriteText() = default;

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		SpriteText &operator=(const SpriteText &sprite_text) = default;
		SpriteText &operator=(SpriteText &&sprite_text) = default;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		void Draw(SpriteBatch &sprite_batch) const {
			m_font->DrawString(sprite_batch, m_text.c_str(), m_transform, m_color, m_effects);
		}

		SharedPtr< SpriteFont > GetFont() const {
			return m_font;
		}
		void SetFont(SharedPtr< SpriteFont > font) {
			m_font = font;
		}
		const wstring &GetText() const {
			return m_text;
		}
		void SetText(const wstring &text) {
			m_text = text;
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

		SharedPtr< SpriteFont > m_font;
		wstring m_text;
		XMVECTOR m_color;
		SpriteEffect m_effects;
		SpriteTransform m_transform;
	};
}