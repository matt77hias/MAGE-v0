#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "resource\resource.hpp"
#include "resource\font\color_string.hpp"
#include "resource\font\sprite_font_descriptor.hpp"
#include "resource\font\sprite_font_output.hpp"
#include "renderer\pass\sprite_batch.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage::rendering {

	//-------------------------------------------------------------------------
	// SpriteFont
	//-------------------------------------------------------------------------
	#pragma region

	/**
	 A class of sprite fonts.
	 */
	class SpriteFont : public Resource< SpriteFont > {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a sprite font.

		 @param[in]		device
						A reference to the device.
		 @param[in]		fname
						The filename (the globally unique identifier).
		 @param[in]		desc
						A reference to the sprite font descriptor.
		 @throws		Exception
						Failed to initialize the sprite font.
		 */
		explicit SpriteFont(ID3D11Device& device,
							std::wstring fname,
			                const SpriteFontDescriptor& desc
			                    = SpriteFontDescriptor());

		/**
		 Constructs a sprite font from the given sprite font.

		 @param[in]		font
						A reference to the sprite font to copy.
		 */
		SpriteFont(const SpriteFont& font) = delete;

		/**
		 Constructs a sprite font by moving the given sprite font.

		 @param[in]		font
						A reference to the sprite font to move.
		 */
		SpriteFont(SpriteFont&& font) noexcept;

		/**
		 Destructs this sprite font.
		 */
		virtual ~SpriteFont();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given sprite font to this sprite font.

		 @param[in]		font
						A reference to the sprite font to copy.
		 @return		A reference to the copy of the given sprite font (i.e.
						this sprite font).
		 */
		SpriteFont& operator=(const SpriteFont& font) = delete;

		/**
		 Moves the given sprite font to this sprite font.

		 @param[in]		font
						A reference to the sprite font to move.
		 @return		A reference to the moved sprite font (i.e. this sprite
						font).
		 */
		SpriteFont& operator=(SpriteFont&& font) noexcept;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Draws the given text with this sprite font using the given sprite
		 batch.

		 @param[in]		sprite_batch
						A reference to the sprite batch used for rendering
						the given text with this sprite font.
		 @param[in]		strings
						The strings of the text.
		 @param[in]		transform
						A reference to the sprite transform.
		 @param[in]		effects
						The sprite effects to apply.
		 @param[in]		color
						A pointer to the (linear) color. If this pointer is
						equal to @c nullptr, each string will be drawn in its
						own color. Otherwise, each string is drawn in this
						color.
		 */
		void DrawText(SpriteBatch& sprite_batch,
			          gsl::span< const ColorString > strings,
			          const SpriteTransform& transform,
			          SpriteEffect effects = SpriteEffect::None,
		              const RGBA* color = nullptr) const;

		/**
		 Returns the size of the given text with this sprite font (in pixels).

		 @param[in]		strings
						The strings of the text.
		 @return		A @a XMVECTOR containing the pixel width as first
						coordinate and pixel height as second coordinate.
		 @note			The text size is computed from the origin to the
						rightmost pixel rendered by any character glyph. This
						has the effect of ignoring 'trailing spaces'.
		 */
		[[nodiscard]]
		const XMVECTOR XM_CALLCONV
			MeasureText(gsl::span< const ColorString > strings) const;

		/**
		 Returns a rectangle bounding the given text with this sprite font.

		 @param[in]		strings
						The strings of the text.
		 @param[in]		top_left
						The top-left position of the text.
		 @return		A @c RECT bounding the given text with this sprite
						font.
		 */
		[[nodiscard]]
		const RECT MeasureDrawBounds(gsl::span< const ColorString > strings,
									 const F32x2& top_left) const;

		/**
		 Checks whether this sprite font is empty.

		 @return		@c true if this sprite font is empty. @c false
						otherwise.
		 */
		[[nodiscard]]
		bool empty() const noexcept {
			using std::empty;
			return empty(m_glyphs);
		}

		/**
		 Returns the number of characters in this sprite font.

		 @return		The number of characters in this sprite font.
		 */
		[[nodiscard]]
		std::size_t size() const noexcept {
			using std::size;
			return size(m_glyphs);
		}

		/**
		 Returns the line spacing of this sprite font.

		 @return		The line spacing of this sprite font.
		 */
		[[nodiscard]]
		F32 GetLineSpacing() const noexcept {
			return m_line_spacing;
		}

		/**
		 Sets the line spacing of this sprite font to the given spacing value.

		 @param[in]		spacing
						The line spacing.
		 */
		void SetLineSpacing(F32 spacing) noexcept {
			m_line_spacing = spacing;
		}

		/**
		 Returns the default character of this sprite font.

		 If this sprite font has no default glyph, @c L'0' is returned.

		 @return		The default character of this sprite font.
		 */
		[[nodiscard]]
		wchar_t GetDefaultCharacter() const noexcept {
			return m_default_glyph ?
				static_cast< wchar_t >(m_default_glyph->m_character) : L'0';
		}

		/**
		 Sets the default character of this sprite font to the given character.

		 If @a character is equal to @c 0, the default glyph of this sprite
		 font is set to @c nullptr.

		 @param[in]		character
						The character.
		 @throws		Exception
						If the given character does not match any glyphs of
						this sprite font and if this sprite font has not a
						default character.
		 */
		void SetDefaultCharacter(wchar_t character) {
			m_default_glyph = (character) ? GetGlyph(character) : nullptr;
		}

		/**
		 Checks whether this sprite font contains a glyp matching the given
		 character.

		 @param[in]		character
						The character.
		 @return		@c true if this sprite font contains a glyph
						corresponding to the given character. @c false
						otherwise.
		 */
		[[nodiscard]]
		bool ContainsCharacter(wchar_t character) const;

		/**
		 Returns the glyph of this sprite font corresponding to the given
		 character.

		 @param[in]		character
						The character.
		 @return		A pointer to the default glyph of this sprite font if
						the given character does not match any glyphs of this
						sprite font and if this sprite font has a default
						character.
		 @return		A pointer to the glyph of this sprite font corresponding
						to the given character.
		 @throws		Exception
						If the given character does not match any glyphs of
						this sprite font and if this sprite font has not a
						default character.
		 */
		[[nodiscard]]
		const Glyph* GetGlyph(wchar_t character) const;

		/**
		 Returns a pointer to the shader resource view of the texture of this
		 sprite font.

		 @return		A pointer to the shader resource view of the texture
						of this sprite font.
		 */
		[[nodiscard]]
		ID3D11ShaderResourceView* Get() const noexcept {
			return m_texture_srv.Get();
		}

	private:

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Initializes this sprite font with the given sprite font output.

		 @param[in]		output
						A reference to the sprite font output.
		 @throws		Exception
						The sprite font glyphs of the given sprite font output
						are not sorted.
		 */
		void InitializeSpriteFont(const SpriteFontOutput& output);

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 A pointer to the texture of this sprite font.
		 */
		ComPtr< ID3D11ShaderResourceView > m_texture_srv;

		/**
		 A vector containing the glyphs of this sprite font.
		 */
		std::vector< Glyph > m_glyphs;

		/**
		 A pointer to the default glyph of this sprite font.
		 */
		const Glyph* m_default_glyph;

		/**
		 The (extra) line spacing of this sprite font.
		 */
		F32 m_line_spacing;
	};

	#pragma endregion

	//-------------------------------------------------------------------------
	// Type Declarations and Definitions
	//-------------------------------------------------------------------------
	#pragma region

	/**
	 A pointer to a sprite font resource.
	 */
	using SpriteFontPtr = SharedPtr< const SpriteFont >;

	#pragma endregion
}