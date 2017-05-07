#pragma once

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	template< typename ActionT >
	inline void Scene::ForEachScript(ActionT action) const {
		for (auto it = m_scripts.cbegin(); it != m_scripts.cend(); ++it) {
			action(**it);
		}
	}

	template< typename ActionT >
	inline void Scene::ForEachModel(ActionT action) const {
		for (auto it = m_models.cbegin(); it != m_models.cend(); ++it) {
			action(**it);
		}
	}

	template< typename ActionT >
	inline void Scene::ForEachOmniLight(ActionT action) const {
		for (auto it = m_omni_lights.cbegin(); it != m_omni_lights.cend(); ++it) {
			action(**it);
		}
	}

	template< typename ActionT >
	inline void Scene::ForEachSpotLight(ActionT action) const {
		for (auto it = m_spot_lights.cbegin(); it != m_spot_lights.cend(); ++it) {
			action(**it);
		}
	}

	template< typename ActionT >
	inline void Scene::ForEachLight(ActionT action) const {
		ForEachOmniLight(action);
		ForEachSpotLight(action);
	}

	template< typename ActionT >
	inline void Scene::ForEachSprite(ActionT action) const {
		for (auto it = m_sprites.cbegin(); it != m_sprites.cend(); ++it) {
			action(**it);
		}
	}
}