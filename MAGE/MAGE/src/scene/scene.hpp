#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "scripting\behavior_script.hpp"
#include "camera\camera_node.hpp"
#include "light\light_node.hpp"
#include "model\model_node.hpp"
#include "model\model_descriptor.hpp"
#include "shader\basic_shader_factory.hpp"
#include "sprite\sprite_object.hpp"
#include "sprite\sprite_batch.hpp"

#include "rendering\structured_buffer.hpp"
#include "buffer\transform_buffer.hpp"
#include "buffer\light_buffer.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	class Scene {

	public:

		//---------------------------------------------------------------------
		// Destructors
		//---------------------------------------------------------------------

		virtual ~Scene();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------	

		Scene &operator=(const Scene &scene) = delete;
		Scene &operator=(Scene &&scene) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		const string &GetName() const {
			return m_name;
		}
		void SetName(const string &name) {
			m_name = name;
		}

		//-------------------------------------------------------------------------
		// Member Methods: Lifecycle
		//-------------------------------------------------------------------------

		/**
		 Initializes this scene.
		 */
		void Initialize();

		/**
		 Updates this scene.

		 @param[in]		delta_time
						The elapsed time since the previous update.
		 */
		void Update(double delta_time) {
			ForEachScript([delta_time](BehaviorScript &script) {
				script.Update(delta_time);
			});
		}

		/**
		 Renders this scene.
		 */
		void Render2D() const;

		/**
		 Renders this scene.
		 */
		void Render3D() const;

		/**
		 Uninitializes this scene.
		 */
		void Uninitialize();

		//-------------------------------------------------------------------------
		// Member Methods: Factory Methods
		//-------------------------------------------------------------------------

		SharedPtr< CameraNode > GetCamera() const {
			return m_camera;
		}
		void SetCamera(SharedPtr< CameraNode > camera) {
			m_camera = camera;
		}

		SharedPtr< OrthographicCameraNode > CreateOrthographicCameraNode();
		SharedPtr< PerspectiveCameraNode > CreatePerspectiveCameraNode();
		SharedPtr< OmniLightNode > CreateOmniLightNode();
		SharedPtr< SpotLightNode > CreateSpotLightNode();
		SharedPtr< ModelNode > CreateModelNode(const ModelDescriptor &desc,
			const CombinedShader &shader = CreateLambertianShader());

		//-------------------------------------------------------------------------
		// Member Methods: Scripts
		//-------------------------------------------------------------------------

		size_t GetNumberOfScripts() const {
			return m_scripts.size();
		}
		bool HasScript(SharedPtr< const BehaviorScript > script) const;
		void AddScript(SharedPtr< BehaviorScript > script);
		void RemoveScript(SharedPtr< BehaviorScript > script);
		void RemoveAllScripts();
		template< typename ActionT >
		void ForEachScript(ActionT action) const;

		//-------------------------------------------------------------------------
		// Member Methods: Sprites
		//-------------------------------------------------------------------------

		void AddSprite(SharedPtr< SpriteObject > sprite);
		void RemoveSprite(SharedPtr< SpriteObject > sprite);
		void RemoveAllSprites();
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

		void Clear();

		//-------------------------------------------------------------------------
		// Member Methods: Models
		//-------------------------------------------------------------------------

		void AddModel(SharedPtr< ModelNode > model);
		void RemoveModel(SharedPtr< ModelNode > model);
		void RemoveAllModels();
		template< typename ActionT >
		void ForEachModel(ActionT action) const;

		//-------------------------------------------------------------------------
		// Member Methods: Lights
		//-------------------------------------------------------------------------

		void AddLight(SharedPtr< OmniLightNode > light);
		void AddLight(SharedPtr< SpotLightNode > light);
		void RemoveLight(SharedPtr< OmniLightNode > light);
		void RemoveLight(SharedPtr< SpotLightNode > light);
		void RemoveAllLights();
		template< typename ActionT >
		void ForEachOmniLight(ActionT action) const;
		template< typename ActionT >
		void ForEachSpotLight(ActionT action) const;
		template< typename ActionT >
		void ForEachLight(ActionT action) const;

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		string m_name;
		
		vector< SharedPtr< BehaviorScript > > m_scripts;

		SharedPtr< CameraNode > m_camera;

		// 3D
		vector< SharedPtr< ModelNode > > m_models;
		vector< SharedPtr< OmniLightNode > > m_omni_lights;
		vector< SharedPtr< SpotLightNode > > m_spot_lights;

		// 2D
		vector< SharedPtr < SpriteObject > > m_sprites;
		SharedPtr< SpriteBatch > m_sprite_batch;

		// Buffers
		ConstantBuffer< TransformBuffer > m_transform_buffer;
		ConstantBuffer< LightDataBuffer > m_light_data_buffer;
		StructuredBuffer< OmniLightBuffer > m_omni_lights_buffer;
		StructuredBuffer< SpotLightBuffer > m_spot_lights_buffer;
	};
}

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "scene\scene.tpp"

#pragma endregion