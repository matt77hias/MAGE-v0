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

		 @pre			The resource manager associated with the current engine 
						must be loaded.
		 */
		OutlineSpriteText();
		
		/**
		 Constructs a outline sprite text from the given outline sprite text.

		 @param[in]		sprite_text
						A reference to the outline sprite text to copy.
		 */
		OutlineSpriteText(const OutlineSpriteText &sprite_text);

		/**
		 Constructs a outline sprite text by moving the given outline sprite 
		 text.

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
		 @return		A reference to the copy of the given outline sprite 
						text (i.e. this outline sprite text).
		 */
		OutlineSpriteText &operator=(
			const OutlineSpriteText &sprite_text) = delete;

		/**
		 Moves the given outline sprite text to this outline sprite text.

		 @param[in]		sprite_text
						A reference to the outline sprite text to move.
		 @return		A reference to the moved outline sprite text (i.e. 
						this outline sprite text).
		 */
		OutlineSpriteText &operator=(
			OutlineSpriteText &&sprite_text) = delete;

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
						A reference to the sprite batch used for rendering this 
						outline sprite text.
		 */
		virtual void Draw(SpriteBatch &sprite_batch) const override;
	
		//---------------------------------------------------------------------
		// Member Methods: Shadow Color
		//---------------------------------------------------------------------

		/**
		 Returns the sRGB border color of this outline sprite text.

		 @return		A reference to the sRGB border color of this outline 
						sprite text.
		 */
		SRGBA &GetBorderColor() noexcept {
			return m_border_color;
		}

		/**
		 Returns the sRGB border color of this outline sprite text.

		 @return		A reference to the sRGB border color of this outline 
						sprite text.
		 */
		const SRGBA &GetBorderColor() const noexcept {
			return m_border_color;
		}

	private:

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Clones this outline sprite text.

		 @return		A pointer to the clone of this outline sprite text.
		 */
		virtual UniquePtr< Sprite > CloneImplementation() const override;

		//---------------------------------------------------------------------
		// Member Variables: Border Color
		//---------------------------------------------------------------------

		/**
		 The sRGB border color of this outline sprite text.
		 */
		SRGBA m_border_color;
	};
}