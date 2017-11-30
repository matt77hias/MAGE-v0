//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "sprite\font\sprite_font.hpp"
#include "loaders\sprite_font_loader.hpp"
#include "utils\logging\error.hpp"
#include "utils\exception\exception.hpp"

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

	/**
	 A struct of glyph "less than" comparators.
	 */
	struct GlyphLessThan final {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a glyph "less than" comparator.
		 */
		GlyphLessThan() = default;

		/**
		 Constructs a glyph "less than" comparator from the given glyph 
		 "less than" comparator.

		 @param[in]		comparator
						A reference to the glyph "less than" comparator to 
						copy.
		 */
		GlyphLessThan(const GlyphLessThan &comparator) = default;

		/**
		 Constructs a glyph "less than" comparator by moving the given glyph 
		 "less than" comparator.

		 @param[in]		comparator
						A reference to the glyph "less than" comparator to 
						move.
		 */
		GlyphLessThan(GlyphLessThan &&comparator) = default;

		/**
		 Destructs this glyph "less than" comparator.
		 */
		~GlyphLessThan() = default;

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given glyph "less than" comparator to this glyph 
		 "less than" comparator.

		 @param[in]		comparator
						A reference to the glyph "less than" comparator to 
						copy.
		 @return		A reference to the copy of the given "less than" 
						comparator (i.e. this "less than" comparator).
		 */
		GlyphLessThan &operator=(const GlyphLessThan &comparator) = default;

		/**
		 Moves the given glyph "less than" comparator to this glyph "less than" 
		 comparator.

		 @param[in]		comparator
						A reference to the glyph "less than" comparator to 
						move.
		 @return		A reference to the moved "less than" comparator (i.e. 
						this "less than" comparator).
		 */
		GlyphLessThan &operator=(GlyphLessThan &&comparator) = default;

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
		bool operator()(const Glyph &lhs, const Glyph &rhs) noexcept {
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
		bool operator()(const Glyph &lhs, wchar_t rhs) noexcept {
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
		bool operator()(wchar_t lhs, const Glyph &rhs) noexcept {
			return static_cast< U32 >(lhs) < rhs.m_character;
		}
	};

	SpriteFont::SpriteFont(wstring fname, 
		const SpriteFontDescriptor &desc)
		: SpriteFont(std::move(fname), Pipeline::GetDevice(), desc) {}

	SpriteFont::SpriteFont(wstring fname, ID3D11Device5 *device, 
		const SpriteFontDescriptor &desc)
		: Resource< SpriteFont >(std::move(fname)), 
		m_texture_srv(), 
		m_glyphs(),
		m_default_glyph(nullptr), 
		m_line_spacing(0.0f) {

		Assert(device);

		SpriteFontOutput output;
		ImportSpriteFontFromFile(GetFilename(), device, output, desc);

		InitializeSpriteFont(output);
	}

	SpriteFont::SpriteFont(SpriteFont &&font) = default;

	SpriteFont::~SpriteFont() = default;

	void SpriteFont::InitializeSpriteFont(const SpriteFontOutput &output) {
		m_glyphs = std::move(output.m_glyphs);
		const bool sorted = std::is_sorted(
			m_glyphs.cbegin(), m_glyphs.cend(), GlyphLessThan());
		ThrowIfFailed(sorted, "Sprite font glyphs are not sorted.");

		SetLineSpacing(output.m_line_spacing);
		SetDefaultCharacter(output.m_default_character);
		
		m_texture_srv = std::move(output.m_texture_srv);
	}

	void XM_CALLCONV SpriteFont::DrawString(SpriteBatch &sprite_batch, 
		const wchar_t *str, const SpriteTransform &transform, FXMVECTOR color, 
		SpriteEffect effects) const {
		
		Assert(str);

		static_assert(
			static_cast< unsigned int >(SpriteEffect::FlipHorizontally) == 1 && 
			static_cast< unsigned int >(SpriteEffect::FlipVertically)   == 2,
			"The following tables must be updated to match");
		// Lookup table indicates which way to move along each axes for each 
		// SpriteEffect.
		static const XMVECTORF32 axis_direction_table[4] = {
			{-1.0f, -1.0f}, //SpriteEffect::None
			{ 1.0f, -1.0f}, //SpriteEffect::FlipHorizontally
			{-1.0f,  1.0f}, //SpriteEffect::FlipVertically
			{ 1.0f,  1.0f}  //SpriteEffect::FlipBoth
		};
		// Lookup table indiucates which axes are mirrored for each 
		// SpriteEffect.
		static const XMVECTORF32 axis_is_mirrored_table[4] = {
			{ 0.0f, 0.0f }, //SpriteEffect::None
			{ 1.0f, 0.0f }, //SpriteEffect::FlipHorizontally
			{ 0.0f, 1.0f }, //SpriteEffect::FlipVertically
			{ 1.0f, 1.0f }  //SpriteEffect::FlipBoth
		};
		const size_t index = static_cast< size_t >(effects) & 3;

		const F32x2 rotation_origin = transform.GetRotationOrigin();
		XMVECTOR base_offset = XMLoadFloat2(&rotation_origin);
		if (effects != SpriteEffect::None) {
			base_offset -= MeasureString(str) * axis_is_mirrored_table[index];
		}

		F32 x = 0;
		F32 y = 0;
		SpriteTransform sprite_transform(transform);

		for (const wchar_t *s = str; *s != L'\0'; ++s) {
			const wchar_t character = *s;
			
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

				const F32 width  = static_cast< F32 >(
					glyph->m_sub_rectangle.right  - glyph->m_sub_rectangle.left);
				const F32 height = static_cast< F32 >(
					glyph->m_sub_rectangle.bottom - glyph->m_sub_rectangle.top);
				const F32 advance = width + glyph->m_advance_x;

				if (!iswspace(character) || width > 1 || height > 1) {
					const XMVECTOR top_left 
						= XMVectorSet(x, y + glyph->m_offset_y, 0.0f, 0.0f);
					const XMVECTOR &flip 
						= axis_direction_table[index];
					XMVECTOR offset 
						= XMVectorMultiplyAdd(top_left, flip, base_offset);

					if (effects != SpriteEffect::None) {
						const XMVECTOR rect 
							= XMLoadInt4(reinterpret_cast<const U32 *>(&(glyph->m_sub_rectangle)));
						XMVECTOR glyph_rect 
							= XMConvertVectorIntToFloat(rect, 0);
						glyph_rect = XMVectorSwizzle< 2, 3, 0, 1 >(glyph_rect) - glyph_rect;
						const XMVECTOR &mirror 
							= axis_is_mirrored_table[index];
						offset 
							= XMVectorMultiplyAdd(glyph_rect, mirror, offset);
					}

					sprite_transform.SetRotationOrigin(offset);
					sprite_batch.Draw(
						m_texture_srv.Get(), color, effects, 
						sprite_transform, &glyph->m_sub_rectangle);
				}

				x += advance;
				break;
			}
			}
		}
	}
	
	void SpriteFont::DrawString(SpriteBatch &sprite_batch, 
		const vector< ColorString > &text, const SpriteTransform &transform, 
		SpriteEffect effects) const {
		
		static_assert(
			static_cast< unsigned int >(SpriteEffect::FlipHorizontally) == 1 &&
			static_cast< unsigned int >(SpriteEffect::FlipVertically)   == 2,
			"The following tables must be updated to match");
		// Lookup table indicates which way to move along each axes for each SpriteEffect.
		static const XMVECTORF32 axis_direction_table[4] = {
			{ -1.0f, -1.0f }, //SpriteEffect::None
			{  1.0f, -1.0f }, //SpriteEffect::FlipHorizontally
			{ -1.0f,  1.0f }, //SpriteEffect::FlipVertically
			{  1.0f,  1.0f }  //SpriteEffect::FlipBoth
		};
		// Lookup table indiucates which axes are mirrored for each SpriteEffect.
		static const XMVECTORF32 axis_is_mirrored_table[4] = {
			{ 0.0f, 0.0f }, //SpriteEffect::None
			{ 1.0f, 0.0f }, //SpriteEffect::FlipHorizontally
			{ 0.0f, 1.0f }, //SpriteEffect::FlipVertically
			{ 1.0f, 1.0f }  //SpriteEffect::FlipBoth
		};
		const size_t index = static_cast< size_t >(effects) & 3;

		const F32x2 rotation_origin = transform.GetRotationOrigin();
		XMVECTOR base_offset = XMLoadFloat2(&rotation_origin);
		if (effects != SpriteEffect::None) {
			base_offset -= MeasureString(text) * axis_is_mirrored_table[index];
		}

		F32 x = 0;
		F32 y = 0;
		SpriteTransform sprite_transform(transform);

		for (const auto &str : text) {
			for (const wchar_t *s = str.c_str(); *s != L'\0'; ++s) {
				const wchar_t character = *s;
				
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

					const F32 width   = static_cast< F32 >(
						glyph->m_sub_rectangle.right - glyph->m_sub_rectangle.left);
					const F32 height  = static_cast< F32 >(
						glyph->m_sub_rectangle.bottom - glyph->m_sub_rectangle.top);
					const F32 advance = width + glyph->m_advance_x;

					if (!iswspace(character) || width > 1 || height > 1) {
						const XMVECTOR top_left 
							= XMVectorSet(x, y + glyph->m_offset_y, 0.0f, 0.0f);
						const XMVECTOR &flip 
							= axis_direction_table[index];
						XMVECTOR offset 
							= XMVectorMultiplyAdd(top_left, flip, base_offset);

						if (effects != SpriteEffect::None) {
							const XMVECTOR rect 
								= XMLoadInt4(reinterpret_cast<const U32 *>(&(glyph->m_sub_rectangle)));
							XMVECTOR glyph_rect 
								= XMConvertVectorIntToFloat(rect, 0);
							glyph_rect 
								= XMVectorSwizzle< 2, 3, 0, 1 >(glyph_rect) - glyph_rect;
							const XMVECTOR &mirror 
								= axis_is_mirrored_table[index];
							offset 
								= XMVectorMultiplyAdd(glyph_rect, mirror, offset);
						}

						sprite_transform.SetRotationOrigin(offset);
						const SRGBA color = str.GetColor();
						sprite_batch.Draw(
							m_texture_srv.Get(), XMLoadFloat4(&color), effects, 
							sprite_transform, &glyph->m_sub_rectangle);
					}

					x += advance;
					break;
				}
				}
			}
		}
	}

	const XMVECTOR SpriteFont::MeasureString(
		const wchar_t *str) const {
		
		Assert(str);

		XMVECTOR result = XMVectorZero();
		F32 x = 0;
		F32 y = 0;

		for (const wchar_t *s = str; *s != L'\0'; ++s) {
			const wchar_t character = *s;

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

				const F32 width  = static_cast< F32 >(
					glyph->m_sub_rectangle.right  - glyph->m_sub_rectangle.left);
				const F32 height = static_cast< F32 >(
					glyph->m_sub_rectangle.bottom - glyph->m_sub_rectangle.top);
				const F32 advance = width + glyph->m_advance_x;

				if (!iswspace(character) || width > 1 || height > 1) {
					result = XMVectorMax(result, 
						XMVectorSet(
							x + width, 
							y + std::max(m_line_spacing, height + glyph->m_offset_y), 
							0.0f, 
							0.0f));
				}

				x += advance;
				break;
			}
			}
		}

		return result;
	}
	
	const XMVECTOR SpriteFont::MeasureString(
		const vector< ColorString > &text) const {
		
		XMVECTOR result = XMVectorZero();
		F32 x = 0;
		F32 y = 0;

		for (const auto &str : text) {
			for (const wchar_t *s = str.c_str(); *s != L'\0'; ++s) {
				const wchar_t character = *s;
				
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

					const F32 width   = static_cast< F32 >(
						glyph->m_sub_rectangle.right - glyph->m_sub_rectangle.left);
					const F32 height  = static_cast< F32 >(
						glyph->m_sub_rectangle.bottom - glyph->m_sub_rectangle.top);
					const F32 advance = width + glyph->m_advance_x;

					if (!iswspace(character) || width > 1 || height > 1) {
						result = XMVectorMax(result, 
							XMVectorSet(
								x + width, 
								y + std::max(m_line_spacing, height + glyph->m_offset_y), 
								0.0f, 
								0.0f));
					}

					x += advance;
					break;
				}
				}
			}
		}

		return result;
	}

	const RECT SpriteFont::MeasureDrawBounds(
		const wchar_t *str, const F32x2 &position) const {
		
		Assert(str);

		RECT result = { LONG_MAX, LONG_MAX, 0, 0 };
		F32 x = 0;
		F32 y = 0;

		for (const wchar_t *s = str; *s != L'\0'; ++s) {
			const wchar_t character = *s;
			
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

				const F32 width  = static_cast< F32 >(
					glyph->m_sub_rectangle.right  - glyph->m_sub_rectangle.left);
				const F32 height = static_cast< F32 >(
					glyph->m_sub_rectangle.bottom - glyph->m_sub_rectangle.top);
				const F32 advance = width + glyph->m_advance_x;

				if (!iswspace(character) || width > 1 || height > 1) {

					const F32 min_x = position.x + x;
					const F32 min_y = position.y + y + glyph->m_offset_y;
					const F32 max_x = min_x + width + std::max(0.0f, glyph->m_advance_x);
					const F32 max_y = min_y + height;

					result.left   = std::min(result.left,   static_cast< LONG >(min_x));
					result.top    = std::min(result.top,    static_cast< LONG >(min_y));
					result.right  = std::max(result.right,  static_cast< LONG >(max_x));
					result.bottom = std::max(result.bottom, static_cast< LONG >(max_y));
				}

				x += advance;
				break;
			}
			}
		}
		
		if (result.left == LONG_MAX) {
			result.left = 0;
			result.top = 0;
		}

		return result;
	}

	const RECT SpriteFont::MeasureDrawBounds(
		const vector< ColorString > &text, const F32x2 &position) const {
		
		RECT result = { LONG_MAX, LONG_MAX, 0, 0 };
		F32 x = 0;
		F32 y = 0;

		for (const auto &str : text) {
			for (const wchar_t *s = str.c_str(); *s != L'\0'; ++s) {
				const wchar_t character = *s;

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

					const F32 width   = static_cast< F32 >(
						glyph->m_sub_rectangle.right  - glyph->m_sub_rectangle.left);
					const F32 height  = static_cast< F32 >(
						glyph->m_sub_rectangle.bottom - glyph->m_sub_rectangle.top);
					const F32 advance = width + glyph->m_advance_x;

					if (!iswspace(character) || width > 1 || height > 1) {

						const F32 min_x = position.x + x;
						const F32 min_y = position.y + y + glyph->m_offset_y;
						const F32 max_x = min_x + width + std::max(0.0f, glyph->m_advance_x);
						const F32 max_y = min_y + height;

						result.left   = std::min(result.left,   static_cast< LONG >(min_x));
						result.top    = std::min(result.top,    static_cast< LONG >(min_y));
						result.right  = std::max(result.right,  static_cast< LONG >(max_x));
						result.bottom = std::max(result.bottom, static_cast< LONG >(max_y));
					}

					x += advance;
					break;
				}
				}
			}
		}

		if (result.left == LONG_MAX) {
			result.left = 0;
			result.top = 0;
		}

		return result;
	}

	bool SpriteFont::ContainsCharacter(wchar_t character) const {
		return std::binary_search(
			m_glyphs.cbegin(), m_glyphs.cend(), character, GlyphLessThan());
	}
	
	const Glyph *SpriteFont::GetGlyph(wchar_t character) const {
		if (const auto it = std::lower_bound(
			m_glyphs.cbegin(), m_glyphs.cend(), character, GlyphLessThan()); 
			it != m_glyphs.cend() && it->m_character == character) {
			return &(*it);
		}

		ThrowIfFailed((nullptr != m_default_glyph),
			"Character not found in sprite font.");

		return m_default_glyph;
	}
}