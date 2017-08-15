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

	template< typename... ConstructorArgsT >
	SharedPtr< PerspectiveCameraNode > Scene::CreatePerspectiveCamera(const string &name, ConstructorArgsT&&... args) {
		SharedPtr< PerspectiveCameraNode > camera_node
			= MakeShared< PerspectiveCameraNode >(name, std::forward< ConstructorArgsT >(args)...);

		// Add this camera node to this scene.
		AddSceneNode(camera_node);

		return camera_node;
	}

	template< typename... ConstructorArgsT >
	SharedPtr< OrthographicCameraNode > Scene::CreateOrthographicCamera(const string &name, ConstructorArgsT&&... args) {
		SharedPtr< OrthographicCameraNode > camera_node
			= MakeShared< OrthographicCameraNode >(name, std::forward< ConstructorArgsT >(args)...);

		// Add this camera node to this scene.
		AddSceneNode(camera_node);

		return camera_node;
	}

	template< typename... ConstructorArgsT >
	SharedPtr< ModelNode > Scene::CreateModel(const string &name, ConstructorArgsT&&... args) {
		SharedPtr< ModelNode > model_node
			= MakeShared< ModelNode >(name, std::forward< ConstructorArgsT >(args)...);

		// Add this model node to this scene.
		AddSceneNode(model_node);

		return model_node;
	}

	template< typename... ConstructorArgsT >
	SharedPtr< AmbientLightNode > Scene::CreateAmbientLight(const string &name, ConstructorArgsT&&... args) {
		SharedPtr< AmbientLightNode > light_node
			= MakeShared< AmbientLightNode >(name, std::forward< ConstructorArgsT >(args)...);

		// Add this light node to this scene.
		AddSceneNode(light_node);

		return light_node;
	}

	template< typename... ConstructorArgsT >
	SharedPtr< DirectionalLightNode > Scene::CreateDirectionalLight(const string &name, ConstructorArgsT&&... args) {
		SharedPtr< DirectionalLightNode > light_node
			= MakeShared< DirectionalLightNode >(name, std::forward< ConstructorArgsT >(args)...);

		// Add this light node to this scene.
		AddSceneNode(light_node);

		return light_node;
	}

	template< typename... ConstructorArgsT >
	SharedPtr< OmniLightNode > Scene::CreateOmniLight(const string &name, ConstructorArgsT&&... args) {
		SharedPtr< OmniLightNode > light_node
			= MakeShared< OmniLightNode >(name, std::forward< ConstructorArgsT >(args)...);

		// Add this light node to this scene.
		AddSceneNode(light_node);

		return light_node;
	}

	template< typename... ConstructorArgsT >
	SharedPtr< SpotLightNode > Scene::CreateSpotLight(const string &name, ConstructorArgsT&&... args) {
		SharedPtr< SpotLightNode > light_node
			= MakeShared< SpotLightNode >(name, std::forward< ConstructorArgsT >(args)...);

		// Add this light node to this scene.
		AddSceneNode(light_node);

		return light_node;
	}

	template< typename... ConstructorArgsT >
	SharedPtr< SpriteImageNode > Scene::CreateSpriteImage(const string &name, ConstructorArgsT&&... args) {
		SharedPtr< SpriteImageNode > sprite_node
			= MakeShared< SpriteImageNode >(name, std::forward< ConstructorArgsT >(args)...);

		// Add this sprite node to this scene.
		AddSceneNode(sprite_node);

		return sprite_node;
	}

	template< typename... ConstructorArgsT >
	SharedPtr< NormalSpriteTextNode > Scene::CreateNormalSpriteText(const string &name, ConstructorArgsT&&... args) {
		SharedPtr< NormalSpriteTextNode > sprite_node
			= MakeShared< NormalSpriteTextNode >(name, std::forward< ConstructorArgsT >(args)...);

		// Add this sprite node to this scene.
		AddSceneNode(sprite_node);

		return sprite_node;
	}

	template< typename... ConstructorArgsT >
	SharedPtr< DropshadowSpriteTextNode > Scene::CreateDropshadowSpriteText(const string &name, ConstructorArgsT&&... args) {
		SharedPtr< DropshadowSpriteTextNode > sprite_node
			= MakeShared< DropshadowSpriteTextNode >(name, std::forward< ConstructorArgsT >(args)...);

		// Add this sprite node to this scene.
		AddSceneNode(sprite_node);

		return sprite_node;
	}

	template< typename... ConstructorArgsT >
	SharedPtr< OutlineSpriteTextNode > Scene::CreateOutlineSpriteText(const string &name, ConstructorArgsT&&... args) {
		SharedPtr< OutlineSpriteTextNode > sprite_node
			= MakeShared< OutlineSpriteTextNode >(name, std::forward< ConstructorArgsT >(args)...);

		// Add this sprite node to this scene.
		AddSceneNode(sprite_node);

		return sprite_node;
	}
}