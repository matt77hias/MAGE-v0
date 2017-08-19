#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "scene\scene_fog.hpp"
#include "scripting\behavior_script.hpp"
#include "camera\camera_node_types.hpp"
#include "light\light_node_types.hpp"
#include "model\model_node.hpp"
#include "model\model_descriptor.hpp"
#include "sprite\sprite_node_types.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 A class of scenes.
	 */
	class Scene {

	public:

		//---------------------------------------------------------------------
		// Destructors
		//---------------------------------------------------------------------

		/**
		 Destructs this scene.
		 */
		virtual ~Scene();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------	

		Scene &operator=(const Scene &scene) = delete;
		Scene &operator=(Scene &&scene) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		const string &GetName() const noexcept {
			return m_name;
		}
		void SetName(const string &name) {
			m_name = name;
		}
		void SetName(string &&name) noexcept {
			m_name = std::move(name);
		}

		//-------------------------------------------------------------------------
		// Member Methods: Lifecycle
		//-------------------------------------------------------------------------

		/**
		 Initializes this scene.
		 */
		void Initialize();

		/**
		 Uninitializes this scene.
		 */
		void Uninitialize();

		//-------------------------------------------------------------------------
		// Member Methods: World
		//-------------------------------------------------------------------------

		/**
		 Returns the scene fog of this scene.

		 @return		A pointer to the scene fog of this scene.
		 */
		SceneFog *GetSceneFog() const noexcept {
			return m_scene_fog.get();
		}

		template< typename SceneNodeT, typename... ConstructorArgsT >
		SharedPtr< SceneNodeT > Create(const string &name, ConstructorArgsT&&... args);
		SharedPtr< ModelNode > CreateModel(const ModelDescriptor &desc);
		
		//-------------------------------------------------------------------------
		// Member Methods: Scripts
		//-------------------------------------------------------------------------

		size_t GetNumberOfScripts() const noexcept {
			return m_scripts.size();
		}
		bool HasScript(SharedPtr< const BehaviorScript > script) const;
		void AddScript(SharedPtr< BehaviorScript > script);
		void RemoveScript(SharedPtr< BehaviorScript > script);
		void RemoveAllScripts() noexcept;
		
		size_t GetNumberOfCameras() const noexcept {
			return m_cameras.size();
		}
		size_t GetNumberOfModels() const noexcept {
			return m_models.size();
		}
		size_t GetNumberOfDirectionalLights() const noexcept {
			return m_directional_lights.size();
		}
		size_t GetNumberOfOmniLights() const noexcept {
			return m_omni_lights.size();
		}
		size_t GetNumberOfSpotLights() const noexcept {
			return m_spot_lights.size();
		}
		size_t GetNumberOfSprites() const noexcept {
			return m_sprites.size();
		}

		template< typename ActionT >
		void ForEachScript(ActionT action) const;
		template< typename ActionT >
		void ForEachCamera(ActionT action) const;
		template< typename ActionT >
		void ForEachModel(ActionT action) const;
		template< typename ActionT >
		void ForEachLight(ActionT action) const;
		template< typename ActionT >
		void ForEachAmbientLight(ActionT action) const;
		template< typename ActionT >
		void ForEachDirectionalLight(ActionT action) const;
		template< typename ActionT >
		void ForEachOmniLight(ActionT action) const;
		template< typename ActionT >
		void ForEachSpotLight(ActionT action) const;
		template< typename ActionT >
		void ForEachSprite(ActionT action) const;
	
	protected:

		//---------------------------------------------------------------------
		// Constructors
		//---------------------------------------------------------------------

		explicit Scene(const string &name);
		Scene(const Scene &scene) = delete;
		Scene(Scene &&scene) = default;

	private:

		//---------------------------------------------------------------------
		// Member Methods: Lifecycle
		//---------------------------------------------------------------------

		/**
		 Loads this scene.
		 Allows this scene to preform any pre-processing construction.
		 */
		virtual void Load() {}

		/**
		 Closes this scene.
		 Allows this scene to preform any post-processing destruction.
		 */
		virtual void Close() {}

		void Clear() noexcept;

		//-------------------------------------------------------------------------
		// Member Methods: World
		//-------------------------------------------------------------------------

		void AddSceneNode(SharedPtr< CameraNode > camera);
		void AddSceneNode(SharedPtr< ModelNode > model);
		void AddSceneNode(SharedPtr< AmbientLightNode > light);
		void AddSceneNode(SharedPtr< DirectionalLightNode > light);
		void AddSceneNode(SharedPtr< OmniLightNode > light);
		void AddSceneNode(SharedPtr< SpotLightNode > light);
		void AddSceneNode(SharedPtr< SpriteNode > sprite);

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		string m_name;
		vector< SharedPtr< BehaviorScript > > m_scripts;
		UniquePtr< SceneFog > m_scene_fog;
		mutable vector< SharedPtr< CameraNode > > m_cameras;
		mutable vector< SharedPtr< ModelNode > > m_models;
		mutable SharedPtr< AmbientLightNode > m_ambient_light;
		mutable vector< SharedPtr< DirectionalLightNode > > m_directional_lights;
		mutable vector< SharedPtr< OmniLightNode > > m_omni_lights;
		mutable vector< SharedPtr< SpotLightNode > > m_spot_lights;
		mutable vector< SharedPtr < SpriteNode > > m_sprites;
	};
}

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "scene\scene.tpp"

#pragma endregion