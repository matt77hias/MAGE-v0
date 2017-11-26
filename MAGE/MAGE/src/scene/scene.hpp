#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "scene\scene_fog.hpp"
#include "scene\sky.hpp"
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
		void SetName(string name) noexcept {
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
		// Member Methods
		//-------------------------------------------------------------------------

		/**
		 Returns the scene fog of this scene.

		 @return		A pointer to the scene fog of this scene.
		 */
		SceneFog *GetSceneFog() const noexcept {
			return m_scene_fog.get();
		}

		/**
		 Returns the sky of this scene.

		 @return		A pointer to the sky of this scene.
		 */
		Sky *GetSky() const noexcept {
			return m_sky.get();
		}

		template< typename T, typename... ConstructorArgsT >
		typename std::enable_if_t< std::is_base_of< BehaviorScript, T >::value, T * >
			Create(ConstructorArgsT&&... args);

		template< typename T >
		typename std::enable_if_t< std::is_base_of< CameraNode, T >::value, T * >
			Create();

		template< typename T >
		typename std::enable_if_t< std::is_base_of< AmbientLightNode, T >::value, T * >
			Create();

		template< typename T >
		typename std::enable_if_t< std::is_base_of< DirectionalLightNode, T >::value, T * >
			Create();

		template< typename T >
		typename std::enable_if_t< std::is_base_of< OmniLightNode, T >::value, T * >
			Create();

		template< typename T >
		typename std::enable_if_t< std::is_base_of< SpotLightNode, T >::value, T * >
			Create();

		template< typename T >
		typename std::enable_if_t< std::is_base_of< SpriteNode, T >::value, T * >
			Create();

		ModelNode *CreateModel(const ModelDescriptor &desc);
		ModelNode *CreateModel(const ModelDescriptor &desc, vector< ModelNode * > &models);

		//-------------------------------------------------------------------------
		// Member Methods
		//-------------------------------------------------------------------------

		size_t GetNumberOfScripts() const noexcept {
			return m_scripts.size();
		}
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
		void ForEachScript(ActionT action, bool include_passive = false) const;
		template< typename ActionT >
		void ForEachCamera(ActionT action, bool include_passive = false) const;
		template< typename ActionT >
		void ForEachModel(ActionT action, bool include_passive = false) const;
		template< typename ActionT >
		void ForEachLight(ActionT action, bool include_passive = false) const;
		template< typename ActionT >
		void ForEachAmbientLight(ActionT action, bool include_passive = false) const;
		template< typename ActionT >
		void ForEachDirectionalLight(ActionT action, bool include_passive = false) const;
		template< typename ActionT >
		void ForEachOmniLight(ActionT action, bool include_passive = false) const;
		template< typename ActionT >
		void ForEachSpotLight(ActionT action, bool include_passive = false) const;
		template< typename ActionT >
		void ForEachSprite(ActionT action, bool include_passive = false) const;
	
	protected:

		//---------------------------------------------------------------------
		// Constructors
		//---------------------------------------------------------------------

		explicit Scene(string name);
		Scene(const Scene &scene) = delete;
		Scene(Scene &&scene) = default;

	private:

		//---------------------------------------------------------------------
		// Member Methods: Lifecycle
		//---------------------------------------------------------------------

		/**
		 Loads this scene. Allows this scene to preform any pre-processing 
		 construction.
		 */
		virtual void Load() {}

		/**
		 Closes this scene. Allows this scene to preform any post-processing 
		 destruction.
		 */
		virtual void Close() {}

		void Clear() noexcept;

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		string m_name;
		
		mutable vector< UniquePtr< BehaviorScript > > m_scripts;
		mutable vector< UniquePtr< CameraNode > > m_cameras;
		mutable vector< UniquePtr< ModelNode > > m_models;
		mutable vector< UniquePtr< DirectionalLightNode > > m_directional_lights;
		mutable vector< UniquePtr< OmniLightNode > > m_omni_lights;
		mutable vector< UniquePtr< SpotLightNode > > m_spot_lights;
		mutable vector< UniquePtr< SpriteNode > > m_sprites;

		UniquePtr< AmbientLightNode > m_ambient_light;
		UniquePtr< SceneFog > m_scene_fog;
		UniquePtr< Sky > m_sky;
	};
}

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "scene\scene.tpp"

#pragma endregion