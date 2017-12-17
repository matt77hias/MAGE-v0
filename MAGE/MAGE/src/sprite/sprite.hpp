#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "scene\component.hpp"
#include "sprite\sprite_batch.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 A class of sprites.
	 */
	class Sprite : public Component {

	public:

		//---------------------------------------------------------------------
		// Destructors
		//---------------------------------------------------------------------

		/**
		 Destruct this sprite.
		 */
		virtual ~Sprite();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given sprite to this sprite.

		 @param[in]		sprite
						A reference to the sprite text to copy.
		 @return		A reference to the copy of the given sprite (i.e. this 
						sprite).
		 */
		Sprite &operator=(const Sprite &sprite) noexcept;

		/**
		 Moves the given sprite to this sprite.

		 @param[in]		sprite
						A reference to the sprite to move.
		 @return		A reference to the moved sprite (i.e. this sprite).
		 */
		Sprite &operator=(Sprite &&sprite) noexcept;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Draws this sprite.

		 @param[in]		sprite_batch
						A reference to the sprite batch used for rendering 
						this sprite.
		 */
		virtual void Draw(SpriteBatch &sprite_batch) const = 0;

		/**
		 Returns the sprite transform of this sprite.

		 @return		A reference to the sprite transform of this sprite.
		 */
		SpriteTransform &GetSpriteTransform() noexcept {
			return m_sprite_transform;
		}

		/**
		 Returns the sprite transform of this sprite.

		 @return		A reference to the sprite transform of this sprite.
		 */
		const SpriteTransform &GetSpriteTransform() const noexcept {
			return m_sprite_transform;
		}
		
		/**
		 Returns the sprite effects of this sprite.

		 @return		The sprite effects of this sprite.
		 */
		SpriteEffect GetSpriteEffects() const noexcept {
			return m_effects;
		}
		
		/**
		 Sets the sprite effects of this sprite to the given sprite effects.

		 @param[in]		effects
						The sprite effects.
		 */
		void SetSpriteEffects(SpriteEffect effects) noexcept {
			m_effects = effects;
		}
		
	protected:

		//---------------------------------------------------------------------
		// Constructors
		//---------------------------------------------------------------------

		/**
		 Constructs a sprite.
		 */
		Sprite() noexcept;

		/**
		 Constructs a sprite from the given sprite.

		 @param[in]		sprite
						A reference to the sprite to copy.
		 */
		Sprite(const Sprite &sprite) noexcept;

		/**
		 Constructs a sprite by moving the given sprite.

		 @param[in]		sprite
						A reference to the sprite to move.
		 */
		Sprite(Sprite &&sprite) noexcept;

	private:

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 The sprite transform of this sprite.
		 */
		SpriteTransform m_sprite_transform;

		/**
		 The sprite effects of this sprite.
		 */
		SpriteEffect m_effects;
	};
}