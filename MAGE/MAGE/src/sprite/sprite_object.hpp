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

	class SpriteObject {

	public:

		//---------------------------------------------------------------------
		// Destructors
		//---------------------------------------------------------------------

		virtual ~SpriteObject() = default;

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		SpriteObject &operator=(const SpriteObject &sprite_object);
		SpriteObject &operator=(SpriteObject &&sprite_object) = default;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		virtual SpriteObject *Clone() const = 0;

		virtual void Draw(SpriteBatch &sprite_batch) const = 0;

		const string &GetName() const {
			return m_name;
		}
		void SetName(const string &name) {
			m_name = name;
		}
		SpriteEffect GetSpriteEffects() const {
			return m_effects;
		}
		void SetSpriteEffects(SpriteEffect effects) {
			m_effects = effects;
		}
		SpriteTransform *GetTransform() {
			return m_transform.get();
		}
		const SpriteTransform *GetTransform() const {
			return m_transform.get();
		}

	protected:

		//---------------------------------------------------------------------
		// Constructors
		//---------------------------------------------------------------------

		explicit SpriteObject(const string &name, SpriteEffect effects = SpriteEffect_None)
			: m_name(name), m_effects(effects), m_transform(new SpriteTransform()) {}
		SpriteObject(const SpriteObject &sprite_object);
		SpriteObject(SpriteObject &&sprite_object) = default;

	private:

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		string m_name;
		SpriteEffect m_effects;
		UniquePtr< SpriteTransform > m_transform;
	};
}