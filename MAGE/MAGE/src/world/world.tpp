#pragma once

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	template< typename ActionT >
	void World::ForEachModel(ActionT action) {
		for (set< SharedPtr< Model > >::iterator it = m_models.begin(); it != m_models.end(); ++it) {
			action(**it);
		}
	}
	template< typename ActionT >
	void World::ForEachModel(ActionT action) const {
		for (set< SharedPtr< Model > >::const_iterator it = m_models.cbegin(); it != m_models.cend(); ++it) {
			action(**it);
		}
	}

	template< typename ActionT >
	void World::ForEachLight(ActionT action) {
		for (set< SharedPtr< PointLight > >::iterator it = m_lights.begin(); it != m_lights.end(); ++it) {
			action(**it);
		}
	}
	template< typename ActionT >
	void World::ForEachLight(ActionT action) const {
		for (set< SharedPtr< PointLight > >::const_iterator it = m_lights.cbegin(); it != m_lights.cend(); ++it) {
			action(**it);
		}
	}
}