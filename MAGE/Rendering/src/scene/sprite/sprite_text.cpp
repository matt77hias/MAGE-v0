//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "scene\node.hpp"
#include "scene\sprite\sprite_text.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage::rendering {

	SpriteText::SpriteText()
		: Component(),
		m_sprite_transform(),
		m_sprite_effects(SpriteEffect::None),
		m_strings(),
		m_text_effect_color(SRGB(1.0f)),
		m_text_effect(TextEffect::None),
		m_font() {}

	SpriteText::SpriteText(const SpriteText& sprite) = default;

	SpriteText::SpriteText(SpriteText&& sprite) noexcept = default;

	SpriteText::~SpriteText() = default;

	SpriteText& SpriteText::operator=(const SpriteText& sprite) = default;

	SpriteText& SpriteText::operator=(SpriteText&& sprite) noexcept = default;

	void SpriteText::Draw(SpriteBatch& sprite_batch) const {
		if (!m_font) {
			return;
		}
		
		SpriteTransform effect_transform(m_sprite_transform);
		
		switch (m_text_effect) {
		
		case TextEffect::Outline: {
			// -1, -1
			effect_transform.AddTranslation(-1.0f, -1.0f);
			m_font->DrawText(sprite_batch, 
							 gsl::make_span(m_strings), 
				             effect_transform, 
							 m_sprite_effects, 
							 &m_text_effect_color);
			// +1, -1
			effect_transform.AddTranslationX(2.0f);
			m_font->DrawText(sprite_batch, 
							 gsl::make_span(m_strings),
				             effect_transform, 
							 m_sprite_effects, 
							 &m_text_effect_color);
			
			[[fallthrough]];
		}

		case TextEffect::DropShadow: {
			// +1, +1
			effect_transform.AddTranslationY(2.0f);
			m_font->DrawText(sprite_batch, 
							 gsl::make_span(m_strings), 
				             effect_transform, 
							 m_sprite_effects, 
							 &m_text_effect_color);
			// -1, +1
			effect_transform.AddTranslationX(-2.0f);
			m_font->DrawText(sprite_batch, 
							 gsl::make_span(m_strings), 
				             effect_transform, 
							 m_sprite_effects, 
							 &m_text_effect_color);

			[[fallthrough]];
		}

		default: {
			m_font->DrawText(sprite_batch, 
							 gsl::make_span(m_strings),
				             m_sprite_transform, 
							 m_sprite_effects);
		}

		}
	}
}