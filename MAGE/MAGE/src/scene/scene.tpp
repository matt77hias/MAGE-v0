#pragma once

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	template< typename SceneNodeT, typename... ConstructorArgsT >
	SharedPtr< SceneNodeT > Scene::Create(const string &name, ConstructorArgsT&&... args) {
		SharedPtr< SceneNodeT > node
			= MakeShared< SceneNodeT >(name, std::forward< ConstructorArgsT >(args)...);

		// Add this node to this scene.
		AddSceneNode(node);

		return node;
	}

	template< typename ActionT >
	inline void Scene::ForEachScript(ActionT action) const {
		for (auto it = m_scripts.cbegin(); it != m_scripts.cend(); ++it) {
			action(it->get());
		}
	}

	template< typename ActionT >
	inline void Scene::ForEachCamera(ActionT action) const {
		vector< SharedPtr< CameraNode > > cameras;
		cameras.reserve(m_cameras.size());
		
		for (auto it = m_cameras.cbegin(); it != m_cameras.cend(); ++it) {
			
			if ((*it)->IsTerminated()) {
				continue;
			}
			
			action(it->get());
			cameras.push_back(std::move(*it));
		}

		m_cameras = std::move(cameras);
	}

	template< typename ActionT >
	inline void Scene::ForEachModel(ActionT action) const {
		vector< SharedPtr< ModelNode > > models;
		models.reserve(m_models.size());
		
		for (auto it = m_models.cbegin(); it != m_models.cend(); ++it) {
			
			if ((*it)->IsTerminated()) {
				continue;
			}

			action(it->get());
			models.push_back(std::move(*it));
		}
		
		m_models = std::move(models);
	}

	template< typename ActionT >
	inline void Scene::ForEachAmbientLight(ActionT action) const {
		
		if (m_ambient_light->IsTerminated()) {
			Create< AmbientLightNode >("ambient light", RGBSpectrum());
			return;
		}

		action(m_ambient_light.get());
	}

	template< typename ActionT >
	inline void Scene::ForEachDirectionalLight(ActionT action) const {
		vector< SharedPtr< DirectionalLightNode > > directional_lights;
		directional_lights.reserve(m_directional_lights.size());
		
		for (auto it = m_directional_lights.cbegin(); it != m_directional_lights.cend(); ++it) {
			
			if ((*it)->IsTerminated()) {
				continue;
			}

			action(it->get());
			directional_lights.push_back(std::move(*it));
		}
		
		m_directional_lights = std::move(directional_lights);
	}

	template< typename ActionT >
	inline void Scene::ForEachOmniLight(ActionT action) const {
		vector< SharedPtr< OmniLightNode > > omni_lights;
		omni_lights.reserve(m_omni_lights.size());
		
		for (auto it = m_omni_lights.cbegin(); it != m_omni_lights.cend(); ++it) {
			
			if ((*it)->IsTerminated()) {
				continue;
			}

			action(it->get());
			omni_lights.push_back(std::move(*it));
		}
		
		m_omni_lights = std::move(omni_lights);
	}

	template< typename ActionT >
	inline void Scene::ForEachSpotLight(ActionT action) const {
		vector< SharedPtr< SpotLightNode > > spot_lights;
		spot_lights.reserve(m_spot_lights.size());
		
		for (auto it = m_spot_lights.cbegin(); it != m_spot_lights.cend(); ++it) {
			
			if ((*it)->IsTerminated()) {
				continue;
			}

			action(it->get());
			spot_lights.push_back(std::move(*it));
		}
		
		m_spot_lights = std::move(spot_lights);
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
		vector< SharedPtr< SpriteNode > > sprites;
		sprites.reserve(m_sprites.size());
		
		for (auto it = m_sprites.cbegin(); it != m_sprites.cend(); ++it) {
			
			if ((*it)->IsTerminated()) {
				continue;
			}

			action(it->get());
			sprites.push_back(std::move(*it));
		}
		
		m_sprites = std::move(sprites);
	}
}