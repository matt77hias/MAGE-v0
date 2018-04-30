//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "resource\font\sprite_font.hpp"
#include "loaders\sprite_font_loader.hpp"
#include "exception\exception.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// System Includes
//-----------------------------------------------------------------------------
#pragma region

#include <algorithm>
#include <limits>

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage::rendering {

	//-------------------------------------------------------------------------
	// GlyphLessThan
	//-------------------------------------------------------------------------
	namespace {
		/**
		 A struct of glyph "less than" comparators.
		 */
		struct GlyphLessThan final {

		public:

			//---------------------------------------------------------------------
			// Member Methods
			//---------------------------------------------------------------------

			/**
			 Checks whether the first given glyph's character is smaller than the 
			 second given glyph's character.

			 @param[in]		lhs
							A reference to the first glyph.
			 @param[in]		rhs
							A reference to the second glyph.
			 @return		@c true if the first given glyph's character is smaller 
							than the second given glyph's character. @c false 
							otherwise.
			 */
			[[nodiscard]]
			bool operator()(const Glyph& lhs, const Glyph& rhs) noexcept {
				return lhs.m_character < rhs.m_character;
			}

			/**
			 Checks whether the given glyph's character is smaller than the given 
			 character.

			 @param[in]		lhs
							A reference to the glyph.
			 @param[in]		rhs
							The character.
			 @return		@c true if the given glyph's character is smaller than 
							the given character. @c false otherwise.
			 */
			[[nodiscard]]
			bool operator()(const Glyph& lhs, wchar_t rhs) noexcept {
				return lhs.m_character < static_cast< U32 >(rhs);
			}

			/**
			 Checks whether the given character is smaller than the given glyph's 
			 character.

			 @param[in]		lhs
							The character.
			 @param[in]		rhs
							A reference to the glyph.
			 @return		@c true if the given character is smaller than the 
							given glyph's character. @c false otherwise.
			 */
			[[nodiscard]]
			bool operator()(wchar_t lhs, const Glyph& rhs) noexcept {
				return static_cast< U32 >(lhs) < rhs.m_character;
			}
		};
	}

	//-------------------------------------------------------------------------
	// SpriteFont
	//-------------------------------------------------------------------------
	#pragma region

	SpriteFont::SpriteFont(ID3D11Device& device,
						   wstring fname,
		                   const SpriteFontDescriptor& desc)
		: Resource< SpriteFont >(std::move(fname)), 
		m_texture_srv(), 
		m_glyphs(), 
		m_default_glyph(nullptr), 
		m_line_spacing(0.0f) {

		SpriteFontOutput output;
		loader::ImportSpriteFontFromFile(GetFilename(), device, output, desc);

		InitializeSpriteFont(output);
	}

	SpriteFont::SpriteFont(SpriteFont&& font) noexcept = default;

	SpriteFont::~SpriteFont() = default;

	SpriteFont& SpriteFont::operator=(SpriteFont&& font) noexcept = default;

	void SpriteFont::InitializeSpriteFont(const SpriteFontOutput& output) {
		using std::cbegin;
		using std::cend;

		m_glyphs = std::move(output.m_glyphs);
		const auto sorted = std::is_sorted(cbegin(m_glyphs), cend(m_glyphs), 
			                               GlyphLessThan());
		ThrowIfFailed(sorted, "Sprite font glyphs are not sorted.");

		SetLineSpacing(output.m_line_spacing);
		SetDefaultCharacter(output.m_default_character);
		
		m_texture_srv = std::move(output.m_texture_srv);
	}

	void SpriteFont::DrawText(SpriteBatch& sprite_batch,
							  gsl::span< const ColorString > strings, 
		                      const SpriteTransform& transform,
		                      SpriteEffect effects,
		                      const RGBA* color) const {

		static_assert(static_cast< U8 >(SpriteEffect::MirrorX) == 1 &&
			          static_cast< U8 >(SpriteEffect::MirrorY) == 2,
			          "The following tables must be updated to match");
		// Lookup table indicates which way to move along each axes for each SpriteEffect.
		static const XMVECTORF32 axis_direction_table[] = {
			{ -1.0f, -1.0f }, //SpriteEffect::None
			{  1.0f, -1.0f }, //SpriteEffect::MirrorX
			{ -1.0f,  1.0f }, //SpriteEffect::MirrorY
			{  1.0f,  1.0f }  //SpriteEffect::MirrorXY
		};
		// Lookup table indiucates which axes are mirrored for each SpriteEffect.
		static const XMVECTORF32 axis_is_mirrored_table[] = {
			{ 0.0f, 0.0f }, //SpriteEffect::None
			{ 1.0f, 0.0f }, //SpriteEffect::MirrorX
			{ 0.0f, 1.0f }, //SpriteEffect::MirrorY
			{ 1.0f, 1.0f }  //SpriteEffect::MirrorXY
		};
		
		const auto index = static_cast< size_t >(effects) & 3u;

		const auto base_offset = (SpriteEffect::None == effects) 
			                   ? transform.GetRotationOriginV() 
			                   : transform.GetRotationOriginV()
			                     - MeasureText(strings) 
			                     * axis_is_mirrored_table[index];

		auto x = 0.0f;
		auto y = 0.0f;
		SpriteTransform sprite_transform(transform);

		for (const auto& str : strings) {
			for (auto character : str.GetString()) {
				switch (character) {

				case L'\r': {
					break;
				}

				case L'\n': {
					x = 0.0f;
					y += m_line_spacing;
					break;
				}

				default: {
					const auto glyph = GetGlyph(character);
					x = std::max(0.0f, x + glyph->m_offset[0]);

					const auto width  = static_cast< F32 >(glyph->GetWidth());
					const auto height = static_cast< F32 >(glyph->GetHeight());
					if (!iswspace(character) || width > 1.0f || height > 1.0f) {
						const auto top_left = XMVectorSet(x, y + glyph->m_offset[1], 0.0f, 0.0f);
						const auto& flip    = axis_direction_table[index];
						auto offset = XMVectorMultiplyAdd(top_left, flip, base_offset);

						if (SpriteEffect::None != effects) {
							// Left Top Right Bottom
							auto glyph_rect = XMVectorLeftTopRightBottom(glyph->m_sub_rectangle);
							// Width Height -Width -Height
							glyph_rect = XMVectorSwizzle< 2, 3, 0, 1 >(glyph_rect) - glyph_rect;
							const auto& mirror = axis_is_mirrored_table[index];
							offset = XMVectorMultiplyAdd(glyph_rect, mirror, offset);
						}

						sprite_transform.SetRotationOrigin(offset);
						
						const auto srgba = (color) ? XMLoad(*color) 
							                       : XMLoad(str.GetColor());
						
						sprite_batch.Draw(m_texture_srv.Get(), 
							              srgba, 
							              effects,
							              sprite_transform, 
							              &glyph->m_sub_rectangle);
					}

					x += width + glyph->m_advance_x;
					break;
				}

				}
			}
		}
	}

	[[nodiscard]]
	const XMVECTOR XM_CALLCONV SpriteFont
		::MeasureText(gsl::span< const ColorString > strings) const {

		auto result = XMVectorZero();
		auto x = 0.0f;
		auto y = 0.0f;

		for (const auto& str : strings) {
			for (auto character : str.GetString()) {
				switch (character) {

				case L'\r': {
					break;
				}

				case L'\n': {
					x = 0.0f;
					y += m_line_spacing;
					break;
				}

				default: {
					const auto glyph = GetGlyph(character);
					x = std::max(0.0f, x + glyph->m_offset[0]);

					const auto width  = static_cast< F32 >(glyph->GetWidth());
					const auto height = static_cast< F32 >(glyph->GetHeight());
					if (!iswspace(character) || width > 1.0f || height > 1.0f) {
						result = XMVectorMax(result, 
							XMVectorSet(x + width, 
								        y + std::max(m_line_spacing, height + glyph->m_offset[1]), 
								        0.0f, 
								        0.0f));
					}

					x += width + glyph->m_advance_x;
					break;
				}

				}
			}
		}

		return result;
	}

	[[nodiscard]]
	const RECT SpriteFont
		::MeasureDrawBounds(gsl::span< const ColorString > strings, 
							const F32x2& top_left) const {

		RECT result = { 
			std::numeric_limits< LONG >::max(), 
			std::numeric_limits< LONG >::max(), 
			0, 
			0 
		};
		auto x = 0.0f;
		auto y = 0.0f;

		for (const auto& str : strings) {
			for (auto character : str.GetString()) {
				switch (character) {

				case L'\r': {
					break;
				}

				case L'\n': {
					x = 0.0f;
					y += m_line_spacing;
					break;
				}

				default: {
					const auto glyph = GetGlyph(character);
					x = std::max(0.0f, x + glyph->m_offset[0]);
					
					const auto width  = static_cast< F32 >(glyph->GetWidth());
					const auto height = static_cast< F32 >(glyph->GetHeight());
					if (!iswspace(character) || width > 1.0f || height > 1.0f) {
						const auto min_x = top_left[0] + x;
						const auto min_y = top_left[1] + y + glyph->m_offset[1];
						const auto max_x = min_x + width + std::max(0.0f, glyph->m_advance_x);
						const auto max_y = min_y + height;

						result.left   = std::min(result.left,   static_cast< LONG >(min_x));
						result.top    = std::min(result.top,    static_cast< LONG >(min_y));
						result.right  = std::max(result.right,  static_cast< LONG >(max_x));
						result.bottom = std::max(result.bottom, static_cast< LONG >(max_y));
					}

					x += width + glyph->m_advance_x;
					break;
				}

				}
			}
		}

		if (std::numeric_limits< LONG >::max() == result.left) {
			result.left = 0;
			result.top  = 0;
		}

		return result;
	}

	[[nodiscard]]
	bool SpriteFont::ContainsCharacter(wchar_t character) const {
		using std::cbegin;
		using std::cend;

		return std::binary_search(cbegin(m_glyphs), cend(m_glyphs), 
			                      character, GlyphLessThan());
	}
	
	[[nodiscard]]
	const Glyph* SpriteFont::GetGlyph(wchar_t character) const {
		using std::cbegin;
		using std::cend;

		if (const auto it = std::lower_bound(cbegin(m_glyphs), cend(m_glyphs), 
			                                 character, GlyphLessThan()); 
			it != cend(m_glyphs) && it->m_character == character) {

			return &(*it);
		}

		ThrowIfFailed((nullptr != m_default_glyph), 
			          "Character not found in sprite font.");

		return m_default_glyph;
	}

	#pragma endregion
}