#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "sprite\sprite.hpp"
#include "sprite\font\sprite_font.hpp"
#include "utils\logging\error.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 A class of sprite texts.
	 */
	class SpriteText : public Sprite {

	public:

		//---------------------------------------------------------------------
		// Effect
		//---------------------------------------------------------------------

		/**
		 An enumeration of the different text effects.

		 This contains:
		 @c None,
		 @c DropShadow and
		 @c Outline.
		 */
		enum struct TextEffect {
			None,
			DropShadow,
			Outline
		};

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a sprite text.

		 @pre			The resource manager associated with the current engine 
						must be loaded.
		 */
		SpriteText();

		/**
		 Constructs a sprite text from the given sprite text.

		 @param[in]		sprite
						A reference to the sprite text to copy.
		 */
		SpriteText(const SpriteText &sprite);

		/**
		 Constructs a sprite text by moving the given sprite text.

		 @param[in]		sprite
						A reference to the sprite text to move.
		 */
		SpriteText(SpriteText &&sprite) noexcept;

		/**
		 Destruct this sprite text.
		 */
		virtual ~SpriteText();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given sprite text to this sprite text.

		 @param[in]		sprite
						A reference to the sprite text to copy.
		 @return		A reference to the copy of the given sprite text (i.e. 
						this sprite text).
		 */
		SpriteText &operator=(const SpriteText &sprite);

		/**
		 Moves the given sprite text to this sprite text.

		 @param[in]		sprite
						A reference to the sprite text to move.
		 @return		A reference to the moved sprite text (i.e. this sprite 
						text).
		 */
		SpriteText &operator=(SpriteText &&sprite) noexcept;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Draws this sprite text.

		 @param[in]		sprite_batch
						A reference to the sprite batch used for rendering this 
						sprite text.
		 */
		virtual void Draw(SpriteBatch &sprite_batch) const = 0;

		//---------------------------------------------------------------------
		// Member Methods: Text
		//---------------------------------------------------------------------

		/**
		 Clears the text of this sprite text.
		 */
		void ClearText() noexcept {
			m_strings.clear();
			m_text.clear();
		}

		/**
		 Returns the text of this sprite text.

		 @return		A reference to a vector containing the color strings 
						of this sprite text.
		 */
		const std::vector< ColorString > &GetText() const noexcept {
			return m_strings;
		}

		/**
		 Sets the text of this sprite text to the given text.

		 @param[in]		text
						The text.
		 */
		void SetText(ColorString text) {
			ClearText();
			m_text = text.c_str();
			m_strings.push_back(std::move(text));
		}
		
		/**
		 Appends the given text to the end of the text of this sprite text.

		 @param[in]		text
						The text.
		 */
		void AppendText(ColorString text) {
			m_text += text.c_str();
			m_strings.push_back(std::move(text));
		}

		/**
		 Traverses all color strings of this sprite text.

		 @tparam		ActionT
						An action to perform on all color strings of this 
						sprite text. The action must accept @c ColorString& 
						values.
		 @param[in]		action
						The action.
		 */
		template< typename ActionT >
		inline void ForEachColorString(ActionT action);

		/**
		 Traverses all color strings of this sprite text.

		 @tparam		ActionT
						An action to perform on all color strings of this 
						sprite text. The action must accept @c const 
						@c ColorString& values.
		 @param[in]		action
						The action.
		 */
		template< typename ActionT >
		inline void ForEachColorString(ActionT action) const;

		//---------------------------------------------------------------------
		// Member Methods: Text Effect
		//---------------------------------------------------------------------

		/**
		 Returns the sRGB text effect color of this sprite text.

		 @return		A reference to the sRGB text effect color of this 
						sprite text.
		 */
		SRGBA &GetTextEffectColor() noexcept {
			return m_text_effect_color;
		}

		/**
		 Returns the sRGB text effect color of this sprite text.

		 @return		A reference to the sRGB text effect color of this 
						sprite text.
		 */
		const SRGBA &GetTextEffectColor() const noexcept {
			return m_text_effect_color;
		}

		/**
		 Returns the text effect of this sprite text.

		 @return		The text effect of this sprite text.
		 */
		TextEffect GetTextEffect() const noexcept {
			return m_text_effect;
		}

		/**
		 Sets the text effect of this sprite text to the given text effect.

		 @param[in]		text_effect
						The text effect.
		 */
		void SetTextEffect(TextEffect text_effect) noexcept {
			m_text_effect = text_effect;
		}

		//---------------------------------------------------------------------
		// Member Methods: Font
		//---------------------------------------------------------------------

		/**
		 Returns the font of this sprite text.

		 @return		A pointer to the font of this sprite text.
		 */
		SharedPtr< const SpriteFont > GetFont() const noexcept {
			return m_font;
		}
		
		/**
		 Sets the font of this sprite text to the given font.

		 @pre			@c font.get() is not equal to @c nullptr.		
		 @param[in]		font
						A pointer to the font of this sprite text.
		 */
		void SetFont(SharedPtr< const SpriteFont > font) noexcept {
			Assert(font);

			m_font = std::move(font);
		}

	private:

		//---------------------------------------------------------------------
		// Member Variables: Text
		//---------------------------------------------------------------------

		/**
		 The text of this sprite text.
		 */
		wstring m_text;

		/**
		 A vector with the color strings of this sprite text.
		 */
		std::vector< ColorString > m_strings;

		//---------------------------------------------------------------------
		// Member Variables: Text Effect
		//---------------------------------------------------------------------

		/**
		 The sRGB text effect color of this sprite text.
		 */
		SRGBA m_text_effect_color;

		/**
		 The text effect of this sprite text.
		 */
		TextEffect m_text_effect;

		//---------------------------------------------------------------------
		// Member Variables: Font
		//---------------------------------------------------------------------

		/**
		 A pointer to the sprite font of this sprite text.
		 */
		SharedPtr< const SpriteFont > m_font;
	};
}

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "sprite\sprite_text.tpp"

#pragma endregion