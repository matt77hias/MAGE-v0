#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "sprite\sprite.hpp"
#include "font\sprite_font.hpp"
#include "logging\error.hpp"

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
		// Destructors
		//---------------------------------------------------------------------

		/**
		 Destruct this sprite text.
		 */
		virtual ~SpriteText();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given sprite text to this sprite text.

		 @param[in]		sprite_text
						A reference to the sprite text to copy.
		 @return		A reference to the copy of the given sprite text (i.e. 
						this sprite text).
		 */
		SpriteText &operator=(const SpriteText &sprite_text) = delete;

		/**
		 Moves the given sprite text to this sprite text.

		 @param[in]		sprite_text
						A reference to the sprite text to move.
		 @return		A reference to the moved sprite text (i.e. this sprite 
						text).
		 */
		SpriteText &operator=(SpriteText &&sprite_text) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Clones this sprite text.

		 @return		A pointer to the clone of this sprite text.
		 */
		UniquePtr< SpriteText > Clone() const {
			return static_pointer_cast< SpriteText >(CloneImplementation());
		}

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
		void ClearText() {
			m_text = L"";
			m_strings.clear();
		}

		/**
		 Returns the text of this sprite text.

		 @return		A pointer to the text of this sprite text.
		 */
		const wchar_t *c_str() const noexcept {
			return m_text.c_str();
		}

		/**
		 Returns the text of this sprite text.

		 @return		A reference to the text of this sprite text.
		 */
		const wstring &GetText() const noexcept {
			return m_text;
		}
		
		/**
		 Returns the text of this sprite text with colors.

		 @return		A reference to a vector containing the color strings 
						of this sprite text.
		 */
		const vector< ColorString > &GetTextWithColors() const noexcept {
			return m_strings;
		}

		/**
		 Sets the text of this sprite text to the given text.

		 @param[in]		text
						A reference to the text.
		 */
		void SetText(const wstring &text);
		
		/**
		 Sets the text of this sprite text to the given text.

		 @pre			@a text is not equal to @c nullptr.
		 @param[in]		text
						A pointer to the text.
		 */
		void SetText(const wchar_t *text);
		
		/**
		 Sets the text of this sprite text to the given text.

		 @param[in]		text
						A reference to the text.
		 */
		void SetText(const ColorString &text);
		
		/**
		 Appends the given text to the end of the text of this sprite text.

		 @param[in]		text
						A reference to the text.
		 */
		void AppendText(const wstring &text);

		/**
		 Appends the given text to the end of the text of this sprite text.

		 @pre			@a text is not equal to @c nullptr.
		 @param[in]		text
						A pointer to the text.
		 */
		void AppendText(const wchar_t *text);
		
		/**
		 Appends the given text to the end of the text of this sprite text.

		 @param[in]		text
						A reference to the text.
		 */
		void AppendText(const ColorString &text);

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

	protected:

		//---------------------------------------------------------------------
		// Constructors
		//---------------------------------------------------------------------

		/**
		 Constructs a sprite text.

		 @pre			The resource manager associated with the current engine 
						must be loaded.
		 */
		SpriteText();

		/**
		 Constructs a sprite text from the given sprite text.

		 @param[in]		sprite_text
						A reference to the sprite text to copy.
		 */
		SpriteText(const SpriteText &sprite_text);

		/**
		 Constructs a sprite text by moving the given sprite text.

		 @param[in]		sprite_text
						A reference to the sprite text to move.
		 */
		SpriteText(SpriteText &&sprite_text);

		//---------------------------------------------------------------------
		// Member Methods: Text
		//---------------------------------------------------------------------

		/**
		 Traverses all color strings of this sprite text.

		 @tparam		ActionT
						An action to perform on all color strings of this 
						sprite text. The action must accept @c ColorString* 
						values.
		 */
		template< typename ActionT >
		inline void ForEachColorString(ActionT action);

		/**
		 Traverses all color strings of this sprite text.

		 @tparam		ActionT
						An action to perform on all color strings of this 
						sprite text. The action must accept @c const 
						@c ColorString* values.
		 */
		template< typename ActionT >
		inline void ForEachColorString(ActionT action) const;

		//---------------------------------------------------------------------
		// Member Methods: Font
		//---------------------------------------------------------------------

		/**
		 Returns the font of this sprite text.

		 @return		A pointer to the font of this sprite text.
		 */
		const SpriteFont *GetRawFont() const noexcept {
			return m_font.get();
		}

	private:

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Clones this sprite text.

		 @return		A pointer to the clone of this sprite text.
		 */
		virtual UniquePtr< Sprite > CloneImplementation() const = 0;

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
		vector< ColorString > m_strings;

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

#include "text\sprite_text.tpp"

#pragma endregion