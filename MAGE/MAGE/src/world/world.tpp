#pragma once

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	template< typename ActionT >
	inline void World::ForEachModel(ActionT action) const {
		for (vector< SharedPtr< ModelNode > >::const_iterator it = m_models.cbegin(); it != m_models.cend(); ++it) {
			action(**it);
		}
	}

	template< typename ActionT >
	inline void World::ForEachOmniLight(ActionT action) const {
		for (vector< SharedPtr< OmniLightNode > >::const_iterator it = m_omni_lights.cbegin(); it != m_omni_lights.cend(); ++it) {
			action(**it);
		}
	}

	template< typename ActionT >
	inline void World::ForEachSpotLight(ActionT action) const {
		for (vector< SharedPtr< SpotLightNode > >::const_iterator it = m_spot_lights.cbegin(); it != m_spot_lights.cend(); ++it) {
			action(**it);
		}
	}

	template< typename ActionT >
	inline void World::ForEachLight(ActionT action) const {
		ForEachOmniLight(action);
		ForEachSpotLight(action);
	}

	template< typename ActionT >
	inline void World::ForEachSprite(ActionT action) const {
		for (vector< SharedPtr< SpriteObject > >::const_iterator it = m_sprites.cbegin(); it != m_sprites.cend(); ++it) {
			action(**it);
		}
	}
}