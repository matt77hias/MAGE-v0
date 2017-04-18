#pragma once

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	template< typename ActionT >
	inline void World::ForEachModel(ActionT action) const {
		for (vector< SharedPtr< Model > >::const_iterator it = m_models.cbegin(); it != m_models.cend(); ++it) {
			action(**it);
		}
	}

	template< typename ActionT >
	inline void World::ForEachLight(ActionT action) const {
		for (vector< SharedPtr< Light > >::const_iterator it = m_lights.cbegin(); it != m_lights.cend(); ++it) {
			action(**it);
		}
	}

	template< typename ActionT >
	inline void World::ForEachObject3D(ActionT action) const {
		ForEachModel(action);
		ForEachLight(action);
	}

	template< typename ActionT >
	inline void World::ForEachSprite(ActionT action) const {
		for (vector< SharedPtr< SpriteObject > >::const_iterator it = m_sprites.cbegin(); it != m_sprites.cend(); ++it) {
			action(**it);
		}
	}

	template< typename ActionT >
	inline void World::ForEachObject2D(ActionT action) const {
		ForEachSprite(action);
	}

	template< typename ActionT >
	inline void World::ForEachObject(ActionT action) const {
		ForEachObject3D(action);
		ForEachObject2D(action);
	}
}