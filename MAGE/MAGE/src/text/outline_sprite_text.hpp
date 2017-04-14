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

		explicit OutlineSpriteText(const string &name, SharedPtr< SpriteFont > font,
			const Color &border_color, SpriteEffect effects = SpriteEffect_None)
			: SpriteText(name, font, effects),
			m_border_color(border_color) {}
		explicit OutlineSpriteText(const string &name, SharedPtr< SpriteFont > font,
			const XMVECTOR &border_color = Colors::Black, SpriteEffect effects = SpriteEffect_None)
			: SpriteText(name, font, effects), 
			m_border_color() {
			SetBorderColor(border_color);
		}
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
			return m_border_color;
		}
		void SetBorderColor(const Color &color) {
			m_border_color = color;
		}
		void SetBorderColor(const XMVECTOR &color) {
			XMStoreFloat4(&m_border_color, color);
		}

	private:

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		const XMVECTOR GetBorderColorVector() const {
			return XMLoadFloat4(&m_border_color);
		};

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		Color m_border_color;
	};
}