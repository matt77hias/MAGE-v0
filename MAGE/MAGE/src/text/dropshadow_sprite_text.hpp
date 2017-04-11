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

	class DropshadowSpriteText final : public SpriteText {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		explicit DropshadowSpriteText(const string &name, const wstring &text, SharedPtr< SpriteFont > font,
			const XMVECTOR &color = Colors::White, const XMVECTOR &shadow_color = Colors::Black,
			SpriteEffect effects = SpriteEffect_None)
			: SpriteText(name, text, font, color, effects), 
			m_shadow_color(shadow_color) {}
		DropshadowSpriteText(const DropshadowSpriteText &sprite_text) = default;
		DropshadowSpriteText(DropshadowSpriteText &&sprite_text) = default;
		virtual ~DropshadowSpriteText() = default;

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		DropshadowSpriteText &operator=(const DropshadowSpriteText &sprite_text) = default;
		DropshadowSpriteText &operator=(DropshadowSpriteText &&sprite_text) = default;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		virtual DropshadowSpriteText *Clone() const override {
			return new DropshadowSpriteText(*this);
		}

		virtual void Draw(SpriteBatch &sprite_batch) const override;
	
		const Color GetShadowColor() const {
			Color c;
			XMStoreFloat4(&c, m_shadow_color);
			return c;
		}
		void SetShadowColor(const Color &color) {
			m_shadow_color = XMLoadFloat4(&color);
		}
		void SetShadowColor(const XMVECTOR &color) {
			m_shadow_color = color;
		}

	private:

		XMVECTOR m_shadow_color;
	};
}