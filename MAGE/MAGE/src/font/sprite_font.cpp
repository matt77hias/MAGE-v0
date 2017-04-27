//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "resource\resource_factory.hpp"
#include "font\sprite_font_loader.hpp"
#include "logging\error.hpp"
#include "logging\exception.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// System Includes
//-----------------------------------------------------------------------------
#pragma region

#include <algorithm>

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	struct GlyphLessThan final {

	public:

		GlyphLessThan() = default;
		GlyphLessThan(const GlyphLessThan &comparator) = default;
		GlyphLessThan(GlyphLessThan &&comparator) = default;
		~GlyphLessThan() = default;

		GlyphLessThan &operator=(const GlyphLessThan &comparator) = default;
		GlyphLessThan &operator=(GlyphLessThan &&comparator) = default;

		inline bool operator()(const Glyph &lhs, const Glyph &rhs) {
			return lhs.m_character < rhs.m_character;
		}
		inline bool operator()(const Glyph &lhs, wchar_t rhs) {
			return lhs.m_character < static_cast< uint32_t >(rhs);
		}
		inline bool operator()(wchar_t lhs, const Glyph &rhs) {
			return static_cast< uint32_t >(lhs) < rhs.m_character;
		}
	};

	SpriteFont::SpriteFont(ID3D11Device2 *device, const wstring &fname, const SpriteFontDescriptor &desc)
		: Resource(fname), m_texture(), m_glyphs(), 
		m_default_glyph(nullptr), m_line_spacing(0.0f) {

		SpriteFontOutput output;
		ImportSpriteFontFromFile(fname, device, output, desc);

		InitializeSpriteFont(output);
	}

	HRESULT SpriteFont::InitializeSpriteFont(const SpriteFontOutput &output) {
		m_glyphs = std::move(output.m_glyphs);
		if (!std::is_sorted(m_glyphs.cbegin(), m_glyphs.cend(), GlyphLessThan())) {
			Error("Sprite font glyphs are not sorted.");
			return E_FAIL;
		}

		SetLineSpacing(output.m_line_spacing);
		SetDefaultCharacter(output.m_default_character);
		
		m_texture = std::move(output.m_texture);

		return S_OK;
	}

	void SpriteFont::DrawString(SpriteBatch &sprite_batch, const wchar_t *text, 
		const SpriteTransform &transform, const XMVECTOR &color, SpriteEffect effects) const {

		static_assert(SpriteEffect_FlipHorizontally == 1 && SpriteEffect_FlipVertically == 2,
			"The following tables must be updated to match");
		// Lookup table indicates which way to move along each axes for each SpriteEffect.
		static const XMVECTORF32 axis_direction_table[4] = {
			{-1.0f, -1.0f}, //SpriteEffect_None
			{ 1.0f, -1.0f}, //SpriteEffect_FlipHorizontally
			{-1.0f,  1.0f}, //SpriteEffect_FlipVertically
			{ 1.0f,  1.0f}  //SpriteEffect_FlipBoth
		};
		// Lookup table indiucates which axes are mirrored for each SpriteEffect.
		static const XMVECTORF32 axis_is_mirrored_table[4] = {
			{ 0.0f, 0.0f }, //SpriteEffect_None
			{ 1.0f, 0.0f }, //SpriteEffect_FlipHorizontally
			{ 0.0f, 1.0f }, //SpriteEffect_FlipVertically
			{ 1.0f, 1.0f } //SpriteEffect_FlipBoth
		};

		const XMFLOAT2 rotation_origin = transform.GetRotationOrigin();
		XMVECTOR base_offset = XMLoadFloat2(&rotation_origin);
		if (effects != SpriteEffect_None) {
			base_offset -= MeasureString(text) * axis_is_mirrored_table[effects & 3];
		}

		float x = 0;
		float y = 0;
		SpriteTransform sprite_transform(transform);

		while (*text != L'\0') {
			const wchar_t character = *text;
			switch (character) {

			case L'\r': {
				continue;
			}
			case L'\n': {
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
					const XMVECTOR top_left = XMVectorSet(x, y + glyph->m_offset_y, 0.0f, 0.0f);
					const XMVECTOR &flip = axis_direction_table[effects & 3];
					XMVECTOR offset = XMVectorMultiplyAdd(top_left, flip, base_offset);

					if (effects != SpriteEffect_None) {
						const XMVECTOR rect = XMLoadInt4(reinterpret_cast<const uint32_t *>(&(glyph->m_sub_rectangle)));
						XMVECTOR glyph_rect = XMConvertVectorIntToFloat(rect, 0);
						glyph_rect = XMVectorSwizzle< 2, 3, 0, 1 >(glyph_rect) - glyph_rect;
						const XMVECTOR &mirror = axis_is_mirrored_table[effects & 3];
						offset = XMVectorMultiplyAdd(glyph_rect, mirror, offset);
					}

					sprite_transform.SetRotationOrigin(offset);
					sprite_batch.Draw(m_texture.Get(), color, effects, sprite_transform, &glyph->m_sub_rectangle);
				}

				x += advance;
				break;
			}
			}

			++text;
		}
	}
	const XMVECTOR SpriteFont::MeasureString(const wchar_t *text) const {
		XMVECTOR result = XMVectorZero();
		float x = 0;
		float y = 0;

		while (*text != L'\0') {
			const wchar_t character = *text;
			switch (character) {

			case L'\r': {
				continue;
			}
			case L'\n': {
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
					result = XMVectorMax(result, XMVectorSet(x + width, y + std::max(m_line_spacing, height + glyph->m_offset_y), 0.0f, 0.0f));
				}

				x += advance;
				break;
			}
			}

			++text;
		}

		return result;
	}
	const RECT SpriteFont::MeasureDrawBounds(const wchar_t *text, const XMFLOAT2 &position) const {
		RECT result = { LONG_MAX, LONG_MAX, 0, 0 };
		float x = 0;
		float y = 0;

		while (*text != L'\0') {
			const wchar_t character = *text;
			switch (character) {
			
			case L'\r': {
				continue;
			}
			case L'\n': {
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

					result.left   = std::min(result.left,   static_cast< LONG >(min_x));
					result.top    = std::min(result.top,    static_cast< LONG >(min_y));
					result.right  = std::max(result.right,  static_cast< LONG >(max_x));
					result.bottom = std::max(result.bottom, static_cast< LONG >(max_y));
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

	bool SpriteFont::ContainsCharacter(wchar_t character) const {
		return std::binary_search(m_glyphs.cbegin(), m_glyphs.cend(), character, GlyphLessThan());
	}

	const Glyph *SpriteFont::GetGlyph(wchar_t character) const {
		const vector< Glyph >::const_iterator it = std::lower_bound(m_glyphs.cbegin(), m_glyphs.cend(), character, GlyphLessThan());
		if (it != m_glyphs.cend() && it->m_character == character) {
			return &(*it);
		}

		if (!m_default_glyph) {
			throw exception("Character not found in sprite font.");
		}

		return m_default_glyph;
	}

	SharedPtr< SpriteFont > CreateFont(const wstring &fname, const SpriteFontDescriptor &desc) {
		ID3D11Device2 *device = GetRenderingDevice();
		ResourceFactory *factory = GetResourceFactory();
		return factory->CreateFont(device, fname, desc);
	}
}