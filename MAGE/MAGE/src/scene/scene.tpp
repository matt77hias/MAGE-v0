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
		for (auto &script : m_scripts) {
			action(script.get());
		}
	}

	template< typename ActionT >
	inline void Scene::ForEachCamera(ActionT action) const {
		vector< SharedPtr< CameraNode > > cameras;
		cameras.reserve(m_cameras.size());
		
		for (const auto &camera : m_cameras) {
			
			if (camera->IsTerminated()) {
				continue;
			}
			
			action(camera.get());
			cameras.push_back(std::move(camera));
		}

		m_cameras = std::move(cameras);
	}

	template< typename ActionT >
	inline void Scene::ForEachModel(ActionT action) const {
		vector< SharedPtr< ModelNode > > models;
		models.reserve(m_models.size());
		
		for (const auto &model : m_models) {
			
			if (model->IsTerminated()) {
				continue;
			}

			action(model.get());
			models.push_back(std::move(model));
		}
		
		m_models = std::move(models);
	}

	template< typename ActionT >
	inline void Scene::ForEachAmbientLight(ActionT action) const {
		
		if (!m_ambient_light || m_ambient_light->IsTerminated()) {
			return;
		}

		action(m_ambient_light.get());
	}

	template< typename ActionT >
	inline void Scene::ForEachDirectionalLight(ActionT action) const {
		vector< SharedPtr< DirectionalLightNode > > lights;
		lights.reserve(m_directional_lights.size());
		
		for (const auto &light : m_directional_lights) {
			
			if (light->IsTerminated()) {
				continue;
			}

			action(light.get());
			lights.push_back(std::move(light));
		}
		
		m_directional_lights = std::move(lights);
	}

	template< typename ActionT >
	inline void Scene::ForEachOmniLight(ActionT action) const {
		vector< SharedPtr< OmniLightNode > > lights;
		lights.reserve(m_omni_lights.size());
		
		for (const auto &light : m_omni_lights) {
			
			if (light->IsTerminated()) {
				continue;
			}

			action(light.get());
			lights.push_back(std::move(light));
		}
		
		m_omni_lights = std::move(lights);
	}

	template< typename ActionT >
	inline void Scene::ForEachSpotLight(ActionT action) const {
		vector< SharedPtr< SpotLightNode > > lights;
		lights.reserve(m_spot_lights.size());
		
		for (const auto &light : m_spot_lights) {
			
			if (light->IsTerminated()) {
				continue;
			}

			action(light.get());
			lights.push_back(std::move(light));
		}
		
		m_spot_lights = std::move(lights);
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
		
		for (const auto &sprite : m_sprites) {
			
			if (sprite->IsTerminated()) {
				continue;
			}

			action(sprite.get());
			sprites.push_back(std::move(sprite));
		}
		
		m_sprites = std::move(sprites);
	}
}