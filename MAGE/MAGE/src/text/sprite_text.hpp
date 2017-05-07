#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "sprite\sprite_object.hpp"
#include "font\sprite_font.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 A class of sprite texts.
	 */
	class SpriteText : public SpriteObject {

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
		 @return		A reference to the copy of the given sprite text
						(i.e. this sprite text).
		 */
		SpriteText &operator=(const SpriteText &sprite_text) = delete;

		/**
		 Moves the given sprite text to this sprite text.

		 @param[in]		sprite_text
						A reference to the sprite text to move.
		 @return		A reference to the moved sprite text
						(i.e. this sprite text).
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
						A reference to the sprite batch used for rendering
						this sprite text.
		 */
		virtual void Draw(SpriteBatch &sprite_batch) const = 0;

		/**
		 Returns the font of this sprite text.

		 @return		A pointer to the font of this sprite text.
		 */
		SharedPtr< SpriteFont > GetFont() const {
			return m_font;
		}
		
		/**
		 Sets the font of this sprite text to the given font.

		 @pre			@c font.get() is not equal to @c nullptr.
		 @param[in]		font
						A pointer to the font of this sprite text.
		 */
		void SetFont(SharedPtr< SpriteFont > font);
		
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
		const wchar_t *c_str() const {
			return m_text.c_str();
		}

		/**
		 Returns the text of this sprite text.

		 @return		A reference to the text of this sprite text.
		 */
		const wstring &GetText() const {
			return m_text;
		}

		/**
		 Returns the text of this sprite text with colors.

		 @return		A reference to a vector containing the
						color strings of this sprite text.
		 */
		const vector< ColorString > &GetTextWithColors() const {
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

	protected:

		//---------------------------------------------------------------------
		// Constructors
		//---------------------------------------------------------------------

		/**
		 Constructs a sprite text.

		 @pre			@c font.get() is not equal to @c nullptr.
		 @param[in]		name
						The name.
		 @param[in]		font
						A pointer to the sprite font.
		 @param[in]		effects
						The sprite effects to apply.
		 */
		explicit SpriteText(const string &name, SharedPtr< SpriteFont > font,
			SpriteEffect effects = SpriteEffect_None);

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
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Returns the font of this sprite text.

		 @return		A pointer to the font of this sprite text.
		 */
		const SpriteFont *GetRawFont() const {
			return m_font.get();
		}

		/**
		 Traverses all color strings of this sprite text.

		 @tparam		ActionT
						An action to perform on all color strings
						of this sprite text. The action must accept 
						@c ColorString& values.
		 */
		template< typename ActionT >
		inline void ForEachColorString(ActionT action);

		/**
		 Traverses all color strings of this sprite text.

		 @tparam		ActionT
						An action to perform on color strings
						of this sprite text. The action must accept
						@c const @c ColorString& values.
		 */
		template< typename ActionT >
		inline void ForEachColorString(ActionT action) const;

	private:

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Clones this sprite text.

		 @return		A pointer to the clone of this sprite text.
		 */
		virtual UniquePtr< SpriteObject > CloneImplementation() const = 0;

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 The text of this sprite text.
		 */
		wstring m_text;

		/**
		 A vector with the color strings of this sprite text.
		 */
		vector< ColorString > m_strings;

		/**
		 A pointer to the sprite font of this sprite text.
		 */
		SharedPtr< SpriteFont > m_font;
	};
}

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "text\sprite_text.tpp"

#pragma endregion