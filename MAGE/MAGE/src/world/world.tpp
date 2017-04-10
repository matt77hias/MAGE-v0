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
		for (vector< SharedPtr< PointLight > >::const_iterator it = m_lights.cbegin(); it != m_lights.cend(); ++it) {
			action(**it);
		}
	}

	template< typename ActionT >
	inline void World::ForEachObject3D(ActionT action) const {
		ForEachModel(action);
		ForEachLight(action);
	}

	template< typename ActionT >
	inline void World::ForEachText(ActionT action) const {
		for (vector< SharedPtr< SpriteText > >::const_iterator it = m_texts.cbegin(); it != m_texts.cend(); ++it) {
			action(**it);
		}
	}

	template< typename ActionT >
	inline void World::ForEachImage(ActionT action) const {
		for (vector< SharedPtr< SpriteImage > >::const_iterator it = m_images.cbegin(); it != m_images.cend(); ++it) {
			action(**it);
		}
	}

	template< typename ActionT >
	inline void World::ForEachObject2D(ActionT action) const {
		ForEachText(action);
		ForEachImage(action);
	}

	template< typename ActionT >
	inline void World::ForEachObject(ActionT action) const {
		ForEachObject3D(action);
		ForEachObject2D(action);
	}
}