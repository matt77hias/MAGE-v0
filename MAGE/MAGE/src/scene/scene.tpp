#pragma once

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	//-------------------------------------------------------------------------
	// Member Methods: Creating
	//-------------------------------------------------------------------------

	template< typename T, typename... ConstructorArgsT >
	inline typename std::enable_if_t< std::is_base_of_v< BehaviorScript, T >, T * >
		Scene::Create(ConstructorArgsT&&... args) {
		
		UniquePtr< T > uptr
			= MakeUnique< T >(std::forward< ConstructorArgsT >(args)...);
		T * const ptr = uptr.get();
		m_scripts.push_back(std::move(uptr));
		return ptr;
	}

	template< typename T >
	inline typename std::enable_if_t< std::is_base_of_v< CameraNode, T >, T * >
		Scene::Create() {

		UniquePtr< T > uptr = MakeUnique< T >();
		T * const ptr = uptr.get();
		m_cameras.push_back(std::move(uptr));
		return ptr;
	}

	template< typename T >
	inline typename std::enable_if_t< std::is_base_of_v< AmbientLightNode, T >, T * >
		Scene::Create() {

		m_ambient_light = MakeUnique< T >();
		return m_ambient_light.get();
	}

	template< typename T >
	inline typename std::enable_if_t< std::is_base_of_v< DirectionalLightNode, T >, T * >
		Scene::Create() {

		UniquePtr< T > uptr = MakeUnique< T >();
		T * const ptr = uptr.get();
		m_directional_lights.push_back(std::move(uptr));
		return ptr;
	}

	template< typename T >
	inline typename std::enable_if_t< std::is_base_of_v< OmniLightNode, T >, T * >
		Scene::Create() {

		UniquePtr< T > uptr = MakeUnique< T >();
		T * const ptr = uptr.get();
		m_omni_lights.push_back(std::move(uptr));
		return ptr;
	}

	template< typename T >
	inline typename std::enable_if_t< std::is_base_of_v< SpotLightNode, T >, T * >
		Scene::Create() {

		UniquePtr< T > uptr = MakeUnique< T >();
		T * const ptr = uptr.get();
		m_spot_lights.push_back(std::move(uptr));
		return ptr;
	}

	template< typename T >
	inline typename std::enable_if_t< std::is_base_of_v< SpriteNode, T >, T * >
		Scene::Create() {

		UniquePtr< T > uptr = MakeUnique< T >();
		T * const ptr = uptr.get();
		m_sprites.push_back(std::move(uptr));
		return ptr;
	}

	//-------------------------------------------------------------------------
	// Member Methods: Iterating
	//-------------------------------------------------------------------------

	template< typename ActionT >
	inline void Scene::ForEachScript(
		ActionT action, bool include_passive) const {

		vector< UniquePtr< BehaviorScript > > scripts;
		scripts.reserve(m_scripts.size());

		for (auto &script : m_scripts) {

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
		
		vector< UniquePtr< CameraNode > > cameras;
		cameras.reserve(m_cameras.size());
		
		for (auto &camera : m_cameras) {
			
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
		
		vector< UniquePtr< ModelNode > > models;
		models.reserve(m_models.size());
		
		for (auto &model : m_models) {
			
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

		vector< UniquePtr< DirectionalLightNode > > lights;
		lights.reserve(m_directional_lights.size());
		
		for (auto &light : m_directional_lights) {
			
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
		
		vector< UniquePtr< OmniLightNode > > lights;
		lights.reserve(m_omni_lights.size());
		
		for (auto &light : m_omni_lights) {
			
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

		vector< UniquePtr< SpotLightNode > > lights;
		lights.reserve(m_spot_lights.size());
		
		for (auto &light : m_spot_lights) {
			
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

		vector< UniquePtr< SpriteNode > > sprites;
		sprites.reserve(m_sprites.size());
		
		for (auto &sprite : m_sprites) {
			
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