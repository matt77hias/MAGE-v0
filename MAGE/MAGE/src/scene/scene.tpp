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
	inline void Scene::ForEachCamera(ActionT action) const {
		for (auto it = m_cameras.cbegin(); it != m_cameras.cend(); ++it) {
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
	inline void Scene::ForEachAmbientLight(ActionT action) const {
		action(*m_ambient_light);
	}

	template< typename ActionT >
	inline void Scene::ForEachDirectionalLight(ActionT action) const {
		for (auto it = m_directional_lights.cbegin(); it != m_directional_lights.cend(); ++it) {
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
		ForEachAmbientLight(action);
		ForEachDirectionalLight(action);
		ForEachOmniLight(action);
		ForEachSpotLight(action);
	}

	template< typename ActionT >
	inline void Scene::ForEachSprite(ActionT action) const {
		for (auto it = m_sprites.cbegin(); it != m_sprites.cend(); ++it) {
			action(**it);
		}
	}

	template< typename SceneNodeT, typename... ConstructorArgsT >
	SharedPtr< SceneNodeT > Scene::Create(const string &name, ConstructorArgsT&&... args) {
		SharedPtr< SceneNodeT > node
			= MakeShared< SceneNodeT >(name, std::forward< ConstructorArgsT >(args)...);

		// Add this node to this scene.
		AddSceneNode(node);

		return node;
	}
}