#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "text\sprite_text.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	class OutlineSpriteText final : public SpriteText {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		explicit OutlineSpriteText(const string &name, const wstring &text, SharedPtr< SpriteFont > font,
			const XMVECTOR &color = Colors::White, const XMVECTOR &border_color = Colors::Black,
			SpriteEffect effects = SpriteEffect_None)
			: SpriteText(name, text, font, color, effects), 
			m_border_color(border_color) {}
		OutlineSpriteText(const OutlineSpriteText &sprite_text) = default;
		OutlineSpriteText(OutlineSpriteText &&sprite_text) = default;
		virtual ~OutlineSpriteText() = default;

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		OutlineSpriteText &operator=(const OutlineSpriteText &sprite_text) = default;
		OutlineSpriteText &operator=(OutlineSpriteText &&sprite_text) = default;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		virtual OutlineSpriteText *Clone() const override {
			return new OutlineSpriteText(*this);
		}

		virtual void Draw(SpriteBatch &sprite_batch) const override;
	
		const Color GetBorderColor() const {
			Color c;
			XMStoreFloat4(&c, m_border_color);
			return c;
		}
		void SetBorderColor(const Color &color) {
			m_border_color = XMLoadFloat4(&color);
		}
		void SetBorderColor(const XMVECTOR &color) {
			m_border_color = color;
		}

	private:

		XMVECTOR m_border_color;
	};
}