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

		 @pre			@c font.get() is not equal to @c nullptr.
		 @param[in]		name
						The name.
		 @param[in]		font
						A pointer to the sprite font.
		 @param[in]		shadow_color
						A reference to the shadow color. 
		 @param[in]		effects
						The sprite effects to apply.
		 */
		explicit DropshadowSpriteText(const string &name, SharedPtr< SpriteFont > font,
			const Color &shadow_color, SpriteEffect effects = SpriteEffect_None);
		
		/**
		 Constructs a dropshadow sprite text.

		 @pre			@c font.get() is not equal to @c nullptr.
		 @param[in]		name
						The name.
		 @param[in]		font
						A pointer to the sprite font.
		 @param[in]		shadow_color
						A reference to the shadow color. 
		 @param[in]		effects
						The sprite effects to apply.
		 */
		explicit DropshadowSpriteText(const string &name, SharedPtr< SpriteFont > font,
			const XMVECTOR &shadow_color = Colors::Black, SpriteEffect effects = SpriteEffect_None);
		
		/**
		 Constructs a dropshadow sprite text from the given dropshadow sprite text.

		 @param[in]		sprite_text
						A reference to the dropshadow sprite text to copy.
		 */
		DropshadowSpriteText(const DropshadowSpriteText &sprite_text) = default;
		
		/**
		 Constructs a dropshadow sprite text by moving the given dropshadow sprite text.

		 @param[in]		sprite_text
						A reference to the dropshadow sprite text to move.
		 */
		DropshadowSpriteText(DropshadowSpriteText &&sprite_text) = default;

		/**
		 Destructs this dropshadow sprite text.
		 */
		virtual ~DropshadowSpriteText() = default;

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
	 	 Copies the given dropshadow sprite text to this dropshadow sprite text.

		 @param[in]		sprite_text
						A reference to the dropshadow sprite text to copy.
		 @return		A reference to the copy of the given dropshadow sprite text
						(i.e. this dropshadow sprite text).
		 */
		DropshadowSpriteText &operator=(const DropshadowSpriteText &sprite_text) = delete;

		/**
		 Moves the given dropshadow sprite text to this dropshadow sprite text.

		 @param[in]		sprite_text
						A reference to the dropshadow sprite text to move.
		 @return		A reference to the moved dropshadow sprite text
						(i.e. this dropshadow sprite text).
		 */
		DropshadowSpriteText &operator=(DropshadowSpriteText &&sprite_text) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Clones this dropshadow sprite text.

		 @return		A pointer to the clone of this dropshadow sprite text.
		 */
		SharedPtr< DropshadowSpriteText > Clone() const {
			return std::static_pointer_cast< DropshadowSpriteText >(CloneImplementation());
		}

		/**
		 Draws this dropshadow sprite text.

		 @param[in]		sprite_batch
						A reference to the sprite batch used for rendering
						this dropshadow sprite text.
		 */
		virtual void Draw(SpriteBatch &sprite_batch) const override;
	
		/**
		 Returns the shadow color of this dropshadow sprite text.

		 @return		The shadow color of this dropshadow sprite text.
		 */
		const Color GetShadowColor() const {
			return m_shadow_color;
		}
		
		/**
		 Sets the shadow color of this dropshadow sprite text to the given color.

		 @param[in]		A reference to the shadow color.
		 */
		void SetShadowColor(const Color &color) {
			m_shadow_color = color;
		}
		
		/**
		 Sets the shadow color of this dropshadow sprite text to the given color.

		 @param[in]		A reference to the shadow color.
		 */
		void SetShadowColor(const XMVECTOR &color) {
			XMStoreFloat4(&m_shadow_color, color);
		}

	private:

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Clones this dropshadow sprite text.

		 @return		A pointer to the clone of this dropshadow sprite text.
		 */
		virtual SharedPtr< SpriteObject > CloneImplementation() const override;

		/**
		 Returns the shadow color of this dropshadow sprite text as @c XMVECTOR.

		 @return		The shadow color of this dropshadow sprite text as @c XMVECTOR.
		 */
		const XMVECTOR GetShadowColorVector() const {
			return XMLoadFloat4(&m_shadow_color);
		};

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 The shadow color of this dropshadow sprite text.
		 */
		Color m_shadow_color;
	};
}