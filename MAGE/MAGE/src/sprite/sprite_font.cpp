#include "sprite\sprite_font.hpp"
#include "logging\error.hpp"

#include <algorithm>

namespace mage {

	


	SpriteFont::SpriteFont(const RenderingDevice &device, const wstring &fname, bool force_srgb) {

	}

	void SpriteFont::DrawString(SpriteBatch &sprite_batch, const wchar_t *text, const SpriteTransform &transform,
		XMVECTOR color, SpriteEffects effects, float layer_depth) const {

	}

	XMVECTOR SpriteFont::MeasureString(const wchar_t *text) {
		XMVECTOR result = XMVectorZero();
		float x = 0;
		float y = 0;

		while (text != L'\0') {
			const wchar_t character = *text;
			switch (character) {

			case '\r': {
				continue;
			}

			case '\n': {
				x = 0;
				y += m_line_spacing;
				break;
			}

			default: {
				const Glyph *glyph = GetGlyph(character);

				x += glyph->m_offset_x;
				if (x < 0) {
					x = 0;
				}

				const float width  = static_cast< float >(glyph->m_sub_rectangle.right  - glyph->m_sub_rectangle.left);
				const float height = static_cast< float >(glyph->m_sub_rectangle.bottom - glyph->m_sub_rectangle.top) + glyph->m_offset_y;
				const float advance = width + glyph->m_advance_x;

				if (!iswspace(character) || width > 1 || height > 1) {
					result = XMVectorMax(result, XMVectorSet(x + width, y + std::max(m_line_spacing, height), 0.0f, 0.0f));
				}

				x += advance;
				break;
			}
			}

			++text;
		}

		return result;
	}
	RECT SpriteFont::MeasureDrawBounds(const wchar_t *text, const XMFLOAT2 &position) {
		RECT result = { LONG_MAX, LONG_MAX, 0, 0 };
		float x = 0;
		float y = 0;

		while (text != L'\0') {
			const wchar_t character = *text;
			switch (character) {
			
			case '\r': {
				continue;
			}
	
			case '\n': {
				x = 0;
				y += m_line_spacing;
				break;
			}

			default: {
				const Glyph *glyph = GetGlyph(character);

				x += glyph->m_offset_x;
				if (x < 0) {
					x = 0;
				}

				const float width  = static_cast< float >(glyph->m_sub_rectangle.right  - glyph->m_sub_rectangle.left);
				const float height = static_cast< float >(glyph->m_sub_rectangle.bottom - glyph->m_sub_rectangle.top);
				const float advance = width + glyph->m_advance_x;

				if (!iswspace(character) || width > 1 || height > 1) {

					const float min_x = position.x + x;
					const float min_y = position.y + y + glyph->m_offset_y;
					const float max_x = min_x + width + std::max(0.0f, glyph->m_advance_x);
					const float max_y = min_y + height;

					if (min_x < result.left) {
						result.left = static_cast< LONG >(min_x);
					}
					if (min_y < result.top) {
						result.top = static_cast< LONG >(min_y);
					}
					if (result.right < max_x) {
						result.right = static_cast< LONG >(max_x);
					}
					if (result.bottom < max_y) {
						result.bottom = static_cast< LONG >(max_y);
					}
				}

				x += advance;
				break;
			}
			}

			++text;
		}
		
		if (result.left == LONG_MAX) {
			result.left = 0;
			result.top = 0;
		}

		return result;
	}

	float SpriteFont::GetLineSpacing() const {
		return m_line_spacing;
	}
	void SpriteFont::SetLineSpacing(float spacing) {
		m_line_spacing = spacing;
	}
	wchar_t SpriteFont::GetDefaultCharacter() const {
		return m_default_glyph ? (wchar_t)m_default_glyph->m_character : 0;
	}
	void SpriteFont::SetDefaultCharacter(wchar_t character) {
		m_default_glyph = nullptr;
		if (character) {
			m_default_glyph = GetGlyph(character);
		}
	}
	bool SpriteFont::ContainsCharacter(wchar_t character) const {
		return std::binary_search(m_glyphs.cbegin(), m_glyphs.cend(), character);
	}

	const Glyph *SpriteFont::GetGlyph(wchar_t character) const {
		const vector< Glyph >::const_iterator it;// = std::lower_bound(m_glyphs.cbegin(), m_glyphs.cend(), character);
		if (it != m_glyphs.cend() && it->m_character == character) {
			return &(*it);
		}

		return m_default_glyph;
	}
	void GetSpriteSheet(ID3D11ShaderResourceView **texture);
}