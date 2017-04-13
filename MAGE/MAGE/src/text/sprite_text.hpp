#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "font\sprite_font.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	class SpriteText {

	public:

		//---------------------------------------------------------------------
		// Destructors
		//---------------------------------------------------------------------

		virtual ~SpriteText() = default;

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		SpriteText &operator=(const SpriteText &sprite_text);
		SpriteText &operator=(SpriteText &&sprite_text) = default;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		virtual SpriteText *Clone() const = 0;

		virtual void Draw(SpriteBatch &sprite_batch) const = 0;

		const string &GetName() const {
			return m_name;
		}
		void SetName(const string &name) {
			m_name = name;
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
		void SetText(const wchar_t *text) {
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
		SpriteTransform *GetTransform() {
			return m_transform.get();
		}
		const SpriteTransform *GetTransform() const {
			return m_transform.get();
		}

		XMVECTOR MeasureString(const wchar_t *text) const {
			return m_font->MeasureString(text);
		}

	protected:

		//---------------------------------------------------------------------
		// Constructors
		//---------------------------------------------------------------------

		explicit SpriteText(const string &name, const wstring &text, SharedPtr< SpriteFont > font,
			const XMVECTOR &color = Colors::White, SpriteEffect effects = SpriteEffect_None);
		SpriteText(const SpriteText &sprite_text);
		SpriteText(SpriteText &&sprite_text) = default;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		const SpriteFont *GetRawFont() const {
			return m_font.get();
		}
		const XMVECTOR GetColorVector() const {
			return m_color;
		}

	private:

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		string m_name;
		wstring m_text;

		XMVECTOR m_color;
		SpriteEffect m_effects;
		SharedPtr< SpriteFont > m_font;
		UniquePtr< SpriteTransform > m_transform;
	};
}