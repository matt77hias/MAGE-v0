#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "text\sprite_text.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 A class of outline sprite texts.
	 */
	class OutlineSpriteText final : public SpriteText {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a outline sprite text.

		 @pre			@c font.get() is not equal to @c nullptr.
		 @param[in]		name
						The name.
		 @param[in]		font
						A pointer to the sprite font.
		 @param[in]		border_color
						A reference to the border color.
		 @param[in]		effects
						The sprite effects to apply.
		 */
		explicit OutlineSpriteText(const string &name, SharedPtr< SpriteFont > font,
			const Color &border_color, SpriteEffect effects = SpriteEffect_None);
		
		/**
		 Constructs a outline sprite text.

		 @pre			@c font.get() is not equal to @c nullptr.
		 @param[in]		name
						The name.
		 @param[in]		font
						A pointer to the sprite font.
		 @param[in]		border_color
						A reference to the border color.
		 @param[in]		effects
						The sprite effects to apply.
		 */
		explicit OutlineSpriteText(const string &name, SharedPtr< SpriteFont > font,
			const XMVECTOR &border_color = Colors::Black, SpriteEffect effects = SpriteEffect_None);

		/**
		 Constructs a outline sprite text from the given outline sprite text.

		 @param[in]		sprite_text
						A reference to the outline sprite text to copy.
		 */
		OutlineSpriteText(const OutlineSpriteText &sprite_text);

		/**
		 Constructs a outline sprite text by moving the given outline sprite text.

		 @param[in]		sprite_text
						A reference to the outline sprite text to move.
		 */
		OutlineSpriteText(OutlineSpriteText &&sprite_text);

		/**
		 Destructs this outline sprite text.
		 */
		virtual ~OutlineSpriteText();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given outline sprite text to this outline sprite text.

		 @param[in]		sprite_text
						A reference to the outline sprite text to copy.
		 @return		A reference to the copy of the given outline sprite text
						(i.e. this outline sprite text).
		 */
		OutlineSpriteText &operator=(const OutlineSpriteText &sprite_text) = delete;

		/**
		 Moves the given outline sprite text to this outline sprite text.

		 @param[in]		sprite_text
						A reference to the outline sprite text to move.
		 @return		A reference to the moved outline sprite text
						(i.e. this outline sprite text).
		 */
		OutlineSpriteText &operator=(OutlineSpriteText &&sprite_text) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Clones this outline sprite text.

		 @return		A pointer to the clone of this outline sprite text.
		 */
		UniquePtr< OutlineSpriteText > Clone() const {
			return static_pointer_cast< OutlineSpriteText >(CloneImplementation());
		}

		/**
		 Draws this outline sprite text.

		 @param[in]		sprite_batch
						A reference to the sprite batch used for rendering
						this outline sprite text.
		 */
		virtual void Draw(SpriteBatch &sprite_batch) const override;
	
		/**
		 Returns the border color of this outline sprite text.

		 @return		The border color of this outline sprite text.
		 */
		const Color GetBorderColor() const noexcept {
			return m_border_color;
		}
		
		/**
		 Sets the border color of this outline sprite text to the given color.

		 @param[in]		color
						A reference to the border color.
		 */
		void SetBorderColor(const Color &color) {
			m_border_color = color;
		}
		
		/**
		 Sets the border color of this outline sprite text to the given color.

		 @param[in]		color
						A reference to the border color.
		 */
		void SetBorderColor(const XMVECTOR &color) {
			XMStoreFloat4(&m_border_color, color);
		}

	private:

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Clones this outline sprite text.

		 @return		A pointer to the clone of this outline sprite text.
		 */
		virtual UniquePtr< SpriteObject > CloneImplementation() const override;

		/**
		 Returns the border color of this outline sprite text as @c XMVECTOR.

		 @return		The border color of this outline sprite text as @c XMVECTOR.
		 */
		const XMVECTOR GetBorderColorVector() const {
			return XMLoadFloat4(&m_border_color);
		};

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 The border color of this outline sprite text.
		 */
		Color m_border_color;
	};
}