//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "scene\scene.hpp"
#include "rendering\resource_manager.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Defines
//-----------------------------------------------------------------------------
#pragma region

#define MAGE_DEFAULT_TEXT_EFFECT_COLOR 1.0f

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	SpriteText::SpriteText()
		: Component(),
		m_sprite_transform(),
		m_sprite_effects(SpriteEffect::None),
		m_strings(),
		m_text_effect_color(SRGB(MAGE_DEFAULT_TEXT_EFFECT_COLOR)),
		m_text_effect(TextEffect::None),
		m_font(ResourceManager::Get()->
			GetOrCreate< SpriteFont >(L"assets/fonts/consolas.font")) {}

	SpriteText::SpriteText(const SpriteText &sprite) = default;

	SpriteText::SpriteText(SpriteText &&sprite) noexcept = default;

	SpriteText::~SpriteText() = default;

	SpriteText &SpriteText::operator=(const SpriteText &sprite) = default;

	SpriteText &SpriteText::operator=(SpriteText &&sprite) noexcept = default;

	void SpriteText::Draw(SpriteBatch &sprite_batch) const {
		SpriteTransform effect_transform(m_sprite_transform);
		
		switch (m_text_effect) {
		
		case TextEffect::Outline: {
			// -1, -1
			effect_transform.AddTranslation(-1.0f, -1.0f);
			m_font->DrawText(sprite_batch, m_strings.data(), m_strings.size(),
				             effect_transform, m_sprite_effects, &m_text_effect_color);
			// +1, -1
			effect_transform.AddTranslationX(2.0f);
			m_font->DrawText(sprite_batch, m_strings.data(), m_strings.size(),
				             effect_transform, m_sprite_effects, &m_text_effect_color);
			
			[[fallthrough]];
		}

		case TextEffect::DropShadow: {
			// +1, +1
			effect_transform.AddTranslationY(2.0f);
			m_font->DrawText(sprite_batch, m_strings.data(), m_strings.size(),
				             effect_transform, m_sprite_effects, &m_text_effect_color);
			// -1, +1
			effect_transform.AddTranslationX(-2.0f);
			m_font->DrawText(sprite_batch, m_strings.data(), m_strings.size(), 
				             effect_transform, m_sprite_effects, &m_text_effect_color);

			[[fallthrough]];
		}

		default: {
			m_font->DrawText(sprite_batch, m_strings.data(), m_strings.size(), 
				             m_sprite_transform, m_sprite_effects);
		}

		}
	}
}