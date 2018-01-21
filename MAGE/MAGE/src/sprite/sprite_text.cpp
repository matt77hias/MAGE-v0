//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "scene\scene.hpp"
#include "resource\resource_manager.hpp"

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
		m_text(),
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
		const auto text = m_text.c_str();
		const auto effect_color = XMLoadFloat4(&m_text_effect_color);
		SpriteTransform effect_transform(m_sprite_transform);
		
		switch (m_text_effect) {
		
		case TextEffect::Outline: {
			// -1, -1
			effect_transform.AddTranslation(-1.0f, -1.0f);
			m_font->DrawString(sprite_batch, 
				               text, 
				               effect_transform, 
				               effect_color, 
				               m_sprite_effects);
			// +1, -1
			effect_transform.AddTranslationX(2.0f);
			m_font->DrawString(sprite_batch, 
				               text, 
				               effect_transform, 
				               effect_color, 
				               m_sprite_effects);
			
			[[fallthrough]];
		}

		case TextEffect::DropShadow: {
			// +1, +1
			effect_transform.AddTranslationY(2.0f);
			m_font->DrawString(sprite_batch, 
				               text, 
				               effect_transform, 
				               effect_color, 
				               m_sprite_effects);
			// -1, +1
			effect_transform.AddTranslationX(-2.0f);
			m_font->DrawString(sprite_batch, 
				               text, 
				               effect_transform, 
				               effect_color, 
				               m_sprite_effects);

			[[fallthrough]];
		}

		default: {
			m_font->DrawString(sprite_batch, 
				               m_strings, 
				               m_sprite_transform, 
				               m_sprite_effects);
		}

		}
	}
}