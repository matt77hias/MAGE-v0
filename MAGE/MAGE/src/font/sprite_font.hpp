#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "resource\resource.hpp"
#include "font\color_string.hpp"
#include "font\sprite_font_output.hpp"
#include "font\sprite_font_descriptor.hpp"
#include "sprite\sprite_batch.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 A class of sprite fonts.
	 */
	class SpriteFont : public FileResource {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a sprite font.

		 @pre			@a device is not equal to @c nullptr.
		 @param[in]		device
						A pointer to the device.
		 @param[in]		fname
						A reference to the filename.
		 @param[in]		desc
						A reference to the sprite font descriptor.
		 @throws		FormattedException
						Failed to initialize the sprite font.
		 */
		explicit SpriteFont(ID3D11Device2 *device, const wstring &fname, 
			const SpriteFontDescriptor &desc = SpriteFontDescriptor());

		/**
		 Constructs a sprite font from the given sprite font.

		 @param[in]		font
						A reference to the sprite font to copy.
		 */
		SpriteFont(const SpriteFont &font) = delete;

		/**
		 Constructs a sprite font by moving the given sprite font.

		 @param[in]		font
						A reference to the sprite font to move.
		 */
		SpriteFont(SpriteFont &&font);

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
		 @return		A reference to the copy of the given sprite font
						(i.e. this sprite font).
		 */
		SpriteFont &operator=(const SpriteFont &font) = delete;

		/**
		 Moves the given sprite font to this sprite font.

		 @param[in]		font
						A reference to the sprite font to move.
		 @return		A reference to the moved sprite font
						(i.e. this sprite font).
		 */
		SpriteFont &operator=(SpriteFont &&font) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Draws the given string with this sprite font using the given sprite batch.

		 @pre			@a str string is not equal to @c nullptr.
		 @param[in]		sprite_batch
						A reference to the sprite batch used for rendering
						the given string with this sprite font.
		 @param[in]		str
						A pointer to the first null-terminated byte string.
		 @param[in]		transform
						A reference to the sprite transform.
		 @param[in]		color
						A reference to the sprite color.
		 @param[in]		effects
						The sprite effects to apply.
		 */
		void DrawString(SpriteBatch &sprite_batch, 
			const wchar_t *str,
			const SpriteTransform &transform,
			const XMVECTOR &color = Colors::White, 
			SpriteEffect effects = SpriteEffect_None) const;

		/**
		 Draws the given text with this sprite font using the given sprite batch.

		 @param[in]		sprite_batch
						A reference to the sprite batch used for rendering
						the given text with this sprite font.
		 @param[in]		text
						A reference to a vector containing color strings.
		 @param[in]		transform
						A reference to the sprite transform.
		 @param[in]		effects
						The sprite effects to apply.
		 */
		void DrawString(SpriteBatch &sprite_batch, 
			const vector< ColorString > &text,
			const SpriteTransform &transform,
			SpriteEffect effects = SpriteEffect_None) const;

		/**
		 Returns the size of the given string with this sprite font in pixels.

		 @pre			@a str is not equal to @c nullptr.
		 @param[in]		str
						A pointer to the first null-terminated byte string.
		 @return		A @a XMVECTOR containing the pixel width as first
						coordinate and pixel height as second coordinate.
		 @note			The string size is computed from the origin to the 
						rightmost pixel rendered by any character glyph. 
						This has the effect of ignoring 'trailing spaces'.
		 */
		const XMVECTOR MeasureString(const wchar_t *str) const;

		/**
		 Returns the size of the given text with this sprite font in pixels.

		 @param[in]		text
						A reference to a vector containing color strings.
		 @return		A @a XMVECTOR containing the pixel width as first
						coordinate and pixel height as second coordinate.
		 @note			The text size is computed from the origin to the
						rightmost pixel rendered by any character glyph.
						This has the effect of ignoring 'trailing spaces'.
		 */
		const XMVECTOR MeasureString(const vector< ColorString > &text) const;
		
		/**
		 Returns a rectangle bounding the given string with this sprite font.

		 @pre			@a str string is not equal to @c nullptr.
		 @param[in]		str
						A pointer to the first null-terminated byte string.
		 @param[in]		position
						The top-left position of the string.
		 @return		A @c RECT bounding the given string with this sprite font.
		 */
		const RECT MeasureDrawBounds(const wchar_t *str, const XMFLOAT2 &position) const;

		/**
		 Returns a rectangle bounding the given text with this sprite font.

		 @param[in]		text
						A reference to a vector containing color strings.
		 @param[in]		position
						The top-left position of the text.
		 @return		A @c RECT bounding the given text with this sprite font.
		 */
		const RECT MeasureDrawBounds(const vector< ColorString > &text, const XMFLOAT2 &position) const;
		
		/**
		 Returns the line spacing of this sprite font.

		 @return		The line spacing of this sprite font.
		 */
		float GetLineSpacing() const noexcept {
			return m_line_spacing;
		}

		/**
		 Sets the line spacing of this sprite font to the given spacing value.

		 @param[in]		spacing
						The line spacing.
		 */
		void SetLineSpacing(float spacing) noexcept {
			m_line_spacing = spacing;
		}
		
		/**
		 Returns the default character of this sprite font.

		 If this sprite font has no default glyph, @c L'0' is returned.

		 @return		The default character of this sprite font.
		 */
		wchar_t GetDefaultCharacter() const noexcept {
			return m_default_glyph ? static_cast< wchar_t >(m_default_glyph->m_character) : L'0';
		}
		
		/**
		 Sets the default character of this sprite font to the given character.

		 If @a character is equal to @c 0, the default glyph of this sprite font
		 is set to @c nullptr.

		 @param[in]		character
						The character.
		 @throws		FormattedException
						If the given character does not match any glyphs of
						this sprite font and if this sprite font has not a default
						character.
		 */
		void SetDefaultCharacter(wchar_t character) {
			m_default_glyph = (character) ? GetGlyph(character) : nullptr;
		}
		
		/**
		 Checks whether this sprite font contains a glyp matching the given character.

		 @param[in]		character
						The character.
		 @return		@c true if this sprite font contains a glyph corresponding
						to the given character.
						@c false otherwise.
		 */
		bool ContainsCharacter(wchar_t character) const;

		/**
		 Returns the glyph of this sprite font corresponding to the given character.

		 @param[in]		character
						The character.
		 @return		A pointer to the default glyph of this sprite font
						if the given character does not match any glyphs of
						this sprite font and if this sprite font has a default
						character.
		 @return		A pointer to the glyph of this sprite font corresponding 
						to the given character.
		 @throws		FormattedException
						If the given character does not match any glyphs of
						this sprite font and if this sprite font has not a default
						character.
		 */
		const Glyph *GetGlyph(wchar_t character) const;

		/**
		 Returns a pointer to the shader resource view of the texture of this sprite font.

		 @return		A pointer to the shader resource view
						of the texture of this sprite font.
		 */
		ID3D11ShaderResourceView *Get() const noexcept {
			return m_texture_srv.Get();
		}

		/**
		 Returns the address of the shader resource view of of the texture of this sprite font.

		 @return		A pointer to the pointer to the shader resource view
						of the texture of this sprite font.
		 */
		ID3D11ShaderResourceView * const *GetAddress() const noexcept {
			return m_texture_srv.GetAddressOf();
		}

		/**
		 Returns the address of the shader resource view of of the texture of this sprite font.

		 @return		A pointer to the pointer to the shader resource view
						of the texture of this sprite font.
		 */
		ID3D11ShaderResourceView **GetAddress() noexcept {
			return m_texture_srv.GetAddressOf();
		}

	private:

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Initializes this sprite font with the given sprite font output.

		 @param[in]		output
						A reference to the sprite font output.
		 @throws		FormattedException
						The sprite font glyphs of the given sprite font
						output are not sorted.
		 */
		void InitializeSpriteFont(const SpriteFontOutput &output);

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
		vector < Glyph > m_glyphs;
		
		/**
		 A pointer to the default glyph of this sprite font.
		 */
		const Glyph *m_default_glyph;

		/**
		 The (extra) line spacing of this sprite font.
		 */
		float m_line_spacing;
	};

	/**
	 Creates a sprite font.

	 @pre			The current engine must be loaded.
	 @param[in]		fname
					A reference to the filename.
	 @param[in]		desc
					A reference to the sprite font descriptor.
	 @return		A pointer to the sprite font.
	 @throws		FormattedException
					Failed to create the sprite font.
	 */
	SharedPtr< SpriteFont > CreateFont(const wstring &fname, const SpriteFontDescriptor &desc);
}