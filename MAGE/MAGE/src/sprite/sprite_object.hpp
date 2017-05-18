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
	 A class of sprite objects.
	 */
	class SpriteObject {

	public:

		//---------------------------------------------------------------------
		// Destructors
		//---------------------------------------------------------------------

		/**
		 Destruct this sprite object.
		 */
		virtual ~SpriteObject();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given sprite object to this sprite object.

		 @param[in]		sprite_object
						A reference to the sprite text to copy.
		 @return		A reference to the copy of the given sprite object
						(i.e. this sprite object).
		 */
		SpriteObject &operator=(const SpriteObject &sprite_object) = delete;

		/**
		 Moves the given sprite object to this sprite object.

		 @param[in]		sprite_object
						A reference to the sprite object to move.
		 @return		A reference to the moved sprite object
						(i.e. this sprite object).
		 */
		SpriteObject &operator=(SpriteObject &&sprite_object) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Clones this sprite object.

		 @return		A pointer to the clone of this sprite object.
		 */
		UniquePtr< SpriteObject > Clone() const {
			return CloneImplementation();
		}

		/**
		 Draws this sprite object.

		 @param[in]		sprite_batch
						A reference to the sprite batch used for rendering
						this sprite object.
		 */
		virtual void Draw(SpriteBatch &sprite_batch) const = 0;

		/**
		 Checks whether this sprite object is active.

		 @return		@c true if this sprite object is active.
						@c false otherwise (i.e. passive).
		 */
		bool IsActive() const noexcept {
			return m_active;
		}

		/**
		 Checks whether this sprite object is passive.

		 @return		@c true if this sprite object is passive.
						@c false otherwise (i.e. active).
		 */
		bool IsPassive() const noexcept {
			return !m_active;
		}

		/**
		 Makes this sprite object active.
		 */
		void MakeActive() noexcept {
			SetActive(true);
		}

		/**
		 Makes this sprite object passive.
		 */
		void MakePassive() noexcept {
			SetActive(false);
		}

		/**
		 Sets this sprite object active flag to the given value.

		 @param[in]		active
						The active flag.
		 */
		void SetActive(bool active) noexcept {
			m_active = active;
		}

		/**
		 Returns the name of this sprite object.

		 @return		A reference to the name of this sprite object.
		 */
		const string &GetName() const noexcept {
			return m_name;
		}
		
		/**
		 Sets the name of this sprite object to the given name.

		 @param[in]		name
						A reference to the name.
		 */
		void SetName(const string &name) {
			m_name = name;
		}

		/**
		 Sets the name of this sprite object to the given name.

		 @param[in]		name
						A reference to the name.
		 */
		void SetName(string &&name) noexcept {
			m_name = std::move(name);
		}
		
		/**
		 Returns the sprite effects of this sprite object.

		 @return		The sprite effects of this sprite object.
		 */
		SpriteEffect GetSpriteEffects() const noexcept {
			return m_effects;
		}
		
		/**
		 Sets the sprite effects of this sprite object to the given sprite effects.

		 @param[in]		effects
						The sprite effects.
		 */
		void SetSpriteEffects(SpriteEffect effects) noexcept {
			m_effects = effects;
		}
		
		/**
		 Returns the transform of this sprite object.

		 @return		A pointer to the transform of this sprite object.
		 */
		SpriteTransform *GetTransform() noexcept {
			return m_transform.get();
		}
		
		/**
		 Returns the transform of this sprite object.

		 @return		A pointer to the transform of this sprite object.
		 */
		const SpriteTransform *GetTransform() const noexcept {
			return m_transform.get();
		}

	protected:

		//---------------------------------------------------------------------
		// Constructors
		//---------------------------------------------------------------------

		/**
		 Constructs a sprite object.

		 @param[in]		name
						The name.
		 @param[in]		effects
						The sprite effects to apply.
		 */
		explicit SpriteObject(const string &name, 
			SpriteEffect effects = SpriteEffect::None);

		/**
		 Constructs a sprite object from the given sprite object.

		 @param[in]		sprite_object
						A reference to the sprite object to copy.
		 */
		SpriteObject(const SpriteObject &sprite_object);

		/**
		 Constructs a sprite object by moving the given sprite object.

		 @param[in]		sprite_object
						A reference to the sprite object to move.
		 */
		SpriteObject(SpriteObject &&sprite_object);

	private:

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Clones this sprite object.

		 @return		A pointer to the clone of this sprite object.
		 */
		virtual UniquePtr< SpriteObject > CloneImplementation() const = 0;

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 A pointer to the sprite transform of this sprite object.
		 */
		UniquePtr< SpriteTransform > m_transform;

		/**
		 A flag indicating whether this node is active or not (i.e. passive).
		 */
		bool m_active;

		/**
		 The name of this sprite object.
		 */
		string m_name;

		/**
		 The sprite effects of this sprite object.
		 */
		SpriteEffect m_effects;
	};
}