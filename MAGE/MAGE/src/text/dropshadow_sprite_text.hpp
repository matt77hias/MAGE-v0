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
	 A class of dropshadow sprite texts.
	 */
	class DropshadowSpriteText final : public SpriteText {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a dropshadow sprite text.

		 @pre			The resource manager associated with the current engine 
						must be loaded.
		 */
		DropshadowSpriteText();
		
		/**
		 Constructs a dropshadow sprite text from the given dropshadow sprite 
		 text.

		 @param[in]		sprite_text
						A reference to the dropshadow sprite text to copy.
		 */
		DropshadowSpriteText(const DropshadowSpriteText &sprite_text);
		
		/**
		 Constructs a dropshadow sprite text by moving the given dropshadow 
		 sprite text.

		 @param[in]		sprite_text
						A reference to the dropshadow sprite text to move.
		 */
		DropshadowSpriteText(DropshadowSpriteText &&sprite_text);

		/**
		 Destructs this dropshadow sprite text.
		 */
		virtual ~DropshadowSpriteText();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
	 	 Copies the given dropshadow sprite text to this dropshadow sprite 
		 text.

		 @param[in]		sprite_text
						A reference to the dropshadow sprite text to copy.
		 @return		A reference to the copy of the given dropshadow sprite 
						text (i.e. this dropshadow sprite text).
		 */
		DropshadowSpriteText &operator=(
			const DropshadowSpriteText &sprite_text) = delete;

		/**
		 Moves the given dropshadow sprite text to this dropshadow sprite text.

		 @param[in]		sprite_text
						A reference to the dropshadow sprite text to move.
		 @return		A reference to the moved dropshadow sprite text (i.e. 
						this dropshadow sprite text).
		 */
		DropshadowSpriteText &operator=(
			DropshadowSpriteText &&sprite_text) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Clones this dropshadow sprite text.

		 @return		A pointer to the clone of this dropshadow sprite text.
		 */
		UniquePtr< DropshadowSpriteText > Clone() const {
			return static_pointer_cast< DropshadowSpriteText >(CloneImplementation());
		}

		/**
		 Draws this dropshadow sprite text.

		 @param[in]		sprite_batch
						A reference to the sprite batch used for rendering this 
						dropshadow sprite text.
		 */
		virtual void Draw(SpriteBatch &sprite_batch) const override;

		//---------------------------------------------------------------------
		// Member Methods: Shadow Color
		//---------------------------------------------------------------------

		/**
		 Returns the sRGB shadow color of this dropshadow sprite text.

		 @return		A reference to the sRGB shadow color of this dropshadow 
						sprite text.
		 */
		SRGBA &GetShadowColor() noexcept {
			return m_shadow_color;
		}

		/**
		 Returns the sRGB shadow color of this dropshadow sprite text.

		 @return		A reference to the sRGB shadow color of this dropshadow 
						sprite text.
		 */
		const SRGBA &GetShadowColor() const noexcept {
			return m_shadow_color;
		}

	private:

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Clones this dropshadow sprite text.

		 @return		A pointer to the clone of this dropshadow sprite text.
		 */
		virtual UniquePtr< Sprite > CloneImplementation() const override;

		//---------------------------------------------------------------------
		// Member Variables: Shadow Color
		//---------------------------------------------------------------------

		/**
		 The sRGB shadow color of this dropshadow sprite text.
		 */
		SRGBA m_shadow_color;
	};
}