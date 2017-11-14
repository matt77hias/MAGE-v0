#pragma once

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	template< typename SceneNodeT, typename... ConstructorArgsT >
	SharedPtr< SceneNodeT > Scene::Create(
		string name, ConstructorArgsT&&... args) {
		
		SharedPtr< SceneNodeT > node = MakeShared< SceneNodeT >(
			std::move(name), std::forward< ConstructorArgsT >(args)...);

		// Add this node to this scene.
		AddSceneNode(node);

		return node;
	}

	template< typename ActionT >
	inline void Scene::ForEachScript(
		ActionT action, bool include_passive) const {
		
		vector< SharedPtr< BehaviorScript > > scripts;
		scripts.reserve(m_scripts.size());

		for (const auto &script : m_scripts) {

			if (script->IsTerminated()) {
				continue;
			}

			if (include_passive || script->IsActive()) {
				action(script.get());
			}

			scripts.push_back(std::move(script));
		}

		m_scripts = std::move(scripts);
	}

	template< typename ActionT >
	inline void Scene::ForEachCamera(
		ActionT action, bool include_passive) const {
		
		vector< SharedPtr< CameraNode > > cameras;
		cameras.reserve(m_cameras.size());
		
		for (const auto &camera : m_cameras) {
			
			if (camera->IsTerminated()) {
				continue;
			}
			
			if (include_passive || camera->IsActive()) {
				action(camera.get());
			}

			cameras.push_back(std::move(camera));
		}

		m_cameras = std::move(cameras);
	}

	template< typename ActionT >
	inline void Scene::ForEachModel(
		ActionT action, bool include_passive) const {
		
		vector< SharedPtr< ModelNode > > models;
		models.reserve(m_models.size());
		
		for (const auto &model : m_models) {
			
			if (model->IsTerminated()) {
				continue;
			}

			if (include_passive || model->IsActive()) {
				action(model.get());
			}

			models.push_back(std::move(model));
		}
		
		m_models = std::move(models);
	}

	template< typename ActionT >
	inline void Scene::ForEachAmbientLight(
		ActionT action, bool include_passive) const {
		
		if (!m_ambient_light || m_ambient_light->IsTerminated()) {
			return;
		}

		if (include_passive || m_ambient_light->IsActive()) {
			action(m_ambient_light.get());
		}
	}

	template< typename ActionT >
	inline void Scene::ForEachDirectionalLight(
		ActionT action, bool include_passive) const {
		
		vector< SharedPtr< DirectionalLightNode > > lights;
		lights.reserve(m_directional_lights.size());
		
		for (const auto &light : m_directional_lights) {
			
			if (light->IsTerminated()) {
				continue;
			}

			if (include_passive || light->IsActive()) {
				action(light.get());
			}

			lights.push_back(std::move(light));
		}
		
		m_directional_lights = std::move(lights);
	}

	template< typename ActionT >
	inline void Scene::ForEachOmniLight(
		ActionT action, bool include_passive) const {
		
		vector< SharedPtr< OmniLightNode > > lights;
		lights.reserve(m_omni_lights.size());
		
		for (const auto &light : m_omni_lights) {
			
			if (light->IsTerminated()) {
				continue;
			}

			if (include_passive || light->IsActive()) {
				action(light.get());
			}

			lights.push_back(std::move(light));
		}
		
		m_omni_lights = std::move(lights);
	}

	template< typename ActionT >
	inline void Scene::ForEachSpotLight(
		ActionT action, bool include_passive) const {
		
		vector< SharedPtr< SpotLightNode > > lights;
		lights.reserve(m_spot_lights.size());
		
		for (const auto &light : m_spot_lights) {
			
			if (light->IsTerminated()) {
				continue;
			}

			if (include_passive || light->IsActive()) {
				action(light.get());
			}

			lights.push_back(std::move(light));
		}
		
		m_spot_lights = std::move(lights);
	}

	template< typename ActionT >
	inline void Scene::ForEachLight(
		ActionT action, bool include_passive) const {
		
		ForEachAmbientLight(    action, include_passive);
		ForEachDirectionalLight(action, include_passive);
		ForEachOmniLight(       action, include_passive);
		ForEachSpotLight(       action, include_passive);
	}

	template< typename ActionT >
	inline void Scene::ForEachSprite(
		ActionT action, bool include_passive) const {
		
		vector< SharedPtr< SpriteNode > > sprites;
		sprites.reserve(m_sprites.size());
		
		for (const auto &sprite : m_sprites) {
			
			if (sprite->IsTerminated()) {
				continue;
			}
			
			if (include_passive || sprite->IsActive()) {
				action(sprite.get());
			}

			sprites.push_back(std::move(sprite));
		}
		
		m_sprites = std::move(sprites);
	}
}