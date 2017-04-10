#pragma once

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	template< typename ActionT >
	void World::ForEachWorldObject(ActionT action) const {
		ForEachModel(action);
		ForEachLight(action);
	}

	template< typename ActionT >
	void World::ForEachModel(ActionT action) const {
		for (vector< SharedPtr< Model > >::const_iterator it = m_models.cbegin(); it != m_models.cend(); ++it) {
			action(**it);
		}
	}

	template< typename ActionT >
	void World::ForEachLight(ActionT action) const {
		for (vector< SharedPtr< PointLight > >::const_iterator it = m_lights.cbegin(); it != m_lights.cend(); ++it) {
			action(**it);
		}
	}
}