#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "sprite\sprite_batch.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 A class of sprites.
	 */
	class Sprite {

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
		Sprite &operator=(const Sprite &sprite) = delete;

		/**
		 Moves the given sprite to this sprite.

		 @param[in]		sprite
						A reference to the sprite to move.
		 @return		A reference to the moved sprite (i.e. this sprite).
		 */
		Sprite &operator=(Sprite &&sprite) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Clones this sprite.

		 @return		A pointer to the clone of this sprite.
		 */
		UniquePtr< Sprite > Clone() const {
			return CloneImplementation();
		}

		/**
		 Draws this sprite.

		 @param[in]		sprite_batch
						A reference to the sprite batch used for rendering 
						this sprite.
		 */
		virtual void Draw(SpriteBatch &sprite_batch) const = 0;

		/**
		 Returns the transform of this sprite.

		 @return		A pointer to the transform of this sprite.
		 */
		SpriteTransform *GetTransform() noexcept {
			return m_transform.get();
		}

		/**
		 Returns the transform of this sprite.

		 @return		A pointer to the transform of this sprite.
		 */
		const SpriteTransform *GetTransform() const noexcept {
			return m_transform.get();
		}
		
		/**
		 Checks whether this sprite is opaque (i.e. contains alpha channel 
		 equal to 1.0).

		 @return		@c true if and only if this sprite is opaque. @c false 
						otherwise.
		 */
		bool IsOpaque() const noexcept {
			return !IsTransparant();
		}
		
		/**
		 Checks whether this sprite is transparent (i.e. contains alpha channel 
		 not equal to 1.0).

		 @return		@c true if and only if this sprite is transparent. 
						@c false otherwise.
		 */
		bool IsTransparant() const noexcept {
			return m_transparent;
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

		 @param[in]		effects
						The sprite effects to apply.
		 */
		explicit Sprite(SpriteEffect effects = SpriteEffect::None);

		/**
		 Constructs a sprite from the given sprite.

		 @param[in]		sprite
						A reference to the sprite to copy.
		 */
		Sprite(const Sprite &sprite);

		/**
		 Constructs a sprite by moving the given sprite.

		 @param[in]		sprite
						A reference to the sprite to move.
		 */
		Sprite(Sprite &&sprite);

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Sets the transparency of this sprite to the given value.

		 @param[in]		transparent
						@c true if this sprite is transparent. @c false 
						otherwise.
		 */
		void SetTransparency(bool transparent) noexcept {
			m_transparent = transparent;
		}

	private:

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Clones this sprite.

		 @return		A pointer to the clone of this sprite.
		 */
		virtual UniquePtr< Sprite > CloneImplementation() const = 0;

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 A pointer to the sprite transform of this sprite.
		 */
		UniquePtr< SpriteTransform > m_transform;

		/**
		 Flag indicating whether this sprite is transparent. This flag is 
		 @c true if this sprite could contain transparent parts. @c false 
		 otherwise.
		 */
		bool m_transparent;

		/**
		 The sprite effects of this sprite.
		 */
		SpriteEffect m_effects;
	};
}