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

		explicit DropshadowSpriteText(const string &name, SharedPtr< SpriteFont > font,
			const Color &shadow_color, SpriteEffect effects = SpriteEffect_None)
			: SpriteText(name, font, effects),
			m_shadow_color(shadow_color) {}
		explicit DropshadowSpriteText(const string &name, SharedPtr< SpriteFont > font,
			const XMVECTOR &shadow_color = Colors::Black, SpriteEffect effects = SpriteEffect_None)
			: SpriteText(name, font, effects), 
			m_shadow_color() {
			SetShadowColor(shadow_color);
		}
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
			return m_shadow_color;
		}
		void SetShadowColor(const Color &color) {
			m_shadow_color = color;
		}
		void SetShadowColor(const XMVECTOR &color) {
			XMStoreFloat4(&m_shadow_color, color);
		}

	private:

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		const XMVECTOR GetShadowColorVector() const {
			return XMLoadFloat4(&m_shadow_color);
		};

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		Color m_shadow_color;
	};
}