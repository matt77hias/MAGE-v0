#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "string\string.hpp"
#include "math\math.hpp"
#include "material\color.hpp"
#include "logging\error.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 A struct of sprite text items representing text and markup.
	 */
	struct SpriteTextItem final {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a sprite text item fromt the given text and color.

		 @param[in]		A reference to the text.
		 @param[in]		A reference to the color.
		 */
		explicit SpriteTextItem(const wstring &text, const Color &color)
			: m_text(text), m_color(color) {}
		
		/**
		 Constructs a sprite text item fromt the given text and color.

		 @param[in]		A reference to the text.
		 @param[in]		A reference to the color.
		 */
		explicit SpriteTextItem(const wstring &text, const XMVECTOR &color = Colors::White)
			: m_text(text), m_color() {
			SetColor(color);
		}

		/**
		 Constructs a sprite text item fromt the given text and color.

		 @pre			@a text is not equal to @c nullptr.
		 @param[in]		A pointer to the text.
		 @param[in]		A reference to the color.
		 */
		explicit SpriteTextItem(const wchar_t *text, const Color &color)
			: m_text(text), m_color(color) {}

		/**
		 Constructs a sprite text item fromt the given text and color.

		 @pre			@a text is not equal to @c nullptr.
		 @param[in]		A pointer to the text.
		 @param[in]		A reference to the color.
		 */
		explicit SpriteTextItem(const wchar_t *text, const XMVECTOR &color = Colors::White)
			: m_text(text), m_color() {
			SetColor(color);
		}

		/**
		 Constructs a sprite text item from the given sprite text item.

		 @param[in]		A reference to the sprite text item to copy.
		 */
		SpriteTextItem(const SpriteTextItem &sprite_text_item) = default;

		/**
		 Constructs a sprite text item by moving the given sprite text item.

		 @param[in]		A reference to the sprite text item to move.
		 */
		SpriteTextItem(SpriteTextItem &&sprite_text_item) = default;

		/**
		 Destructs this sprite text item.
		 */
		~SpriteTextItem() = default;

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given sprite text item to this sprite text item.

		 @param[in]		A reference to the sprite text item to copy.
		 @return		A reference to the copy of the given sprite text item
						(i.e. this sprite text item).
		 */
		SpriteTextItem &operator=(const SpriteTextItem &sprite_text_item) = default;

		/**
		 Moves the given sprite text item to this sprite text item.

		 @param[in]		A reference to the sprite text item to move.
		 @return		A reference to the moved sprite text item
						(i.e. this sprite text item).
		 */
		SpriteTextItem &operator=(SpriteTextItem &&sprite_text_item) = default;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Returns the text of this sprite text item.

		 @return		A reference to the text of this sprite text item.
		 */
		const wstring &GetText() const {
			return m_text;
		}
		
		/**
		 Sets the text of this sprite text item to the given text.

		 @param[in]		A reference to the text.
		 */
		void SetText(const wstring &text) {
			m_text = text;
		}

		/**
		 Sets the text of this sprite text item to the given text.

		 @pre			@a text is not equal to @c nullptr. 
		 @param[in]		A pointer to the text.
		 */
		void SetText(const wchar_t *text) {
			Assert(text);
			m_text = text;
		}

		/**
		 Returns the color of this sprite text item.

		 @return		The color of this sprite text item.
		 */
		const Color GetColor() const {
			return m_color;
		}

		/**
		 Returns the color of this sprite text item as @c XMVECTOR.

		 @return		The color of this sprite text item as @c XMVECTOR.
		 */
		const XMVECTOR GetColorVector() const {
			return XMLoadFloat4(&m_color);
		}

		/**
		 Sets the color of this sprite text item to the given color.

		 @param[in]		A reference to the color.
		 */
		void SetColor(const Color &color) {
			m_color = color;
		}

		/**
		 Sets the color of this sprite text item to the given color.

		 @param[in]		A reference to the color.
		 */
		void SetColor(const XMVECTOR &color) {
			XMStoreFloat4(&m_color, color);
		}

	private:

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 The text of this sprite text item.
		 */
		wstring m_text;

		/**
		 The color of this sprite text item. 
		 */
		Color m_color;
	};
}