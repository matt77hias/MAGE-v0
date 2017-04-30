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
	 A class of normal sprite texts.
	 */
	class NormalSpriteText final : public SpriteText {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a normal sprite text.

		 @pre			@c font.get() is not equal to @c nullptr.
		 @param[in]		name
						The name.
		 @param[in]		font
						A pointer to the sprite font.
		 @param[in]		effects
						The sprite effects to apply.
		 */
		explicit NormalSpriteText(const string &name, SharedPtr< SpriteFont > font,
			SpriteEffect effects = SpriteEffect_None);

		/**
		 Constructs a normal sprite text from the given normal sprite text.

		 @param[in]		sprite_text
						A reference to the normal sprite text to copy.
		 */
		NormalSpriteText(const NormalSpriteText &sprite_text) = default;

		/**
		 Constructs a normal sprite text by moving the given normal sprite text.

		 @param[in]		sprite_text
						A reference to the normal sprite text to move.
		 */
		NormalSpriteText(NormalSpriteText &&sprite_text) = default;

		/**
		 Destructs this normal sprite text.
		 */
		virtual ~NormalSpriteText() = default;

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given normal sprite text to this normal sprite text.

		 @param[in]		sprite_text
						A reference to the normal sprite text to copy.
		 @return		A reference to the copy of the given normal sprite text
						(i.e. this normal sprite text).
		 */
		NormalSpriteText &operator=(const NormalSpriteText &sprite_text) = delete;

		/**
		 Moves the given normal sprite text to this normal sprite text.

		 @param[in]		sprite_text
						A reference to the normal sprite text to move.
		 @return		A reference to the moved normal sprite text
						(i.e. this normal sprite text).
		 */
		NormalSpriteText &operator=(NormalSpriteText &&sprite_text) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Clones this normal sprite text.

		 @return		A pointer to the clone of this normal sprite text.
		 */
		SharedPtr< NormalSpriteText > Clone() const {
			return std::static_pointer_cast< NormalSpriteText >(CloneImplementation());
		}

		/**
		 Draws this normal sprite text.

		 @param[in]		sprite_batch
						A reference to the sprite batch used for rendering
						this normal sprite text.
		 */
		virtual void Draw(SpriteBatch &sprite_batch) const override;

	private:

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Clones this normal sprite text.

		 @return		A pointer to the clone of this normal sprite text.
		 */
		virtual SharedPtr< SpriteObject > CloneImplementation() const override;
	};
}