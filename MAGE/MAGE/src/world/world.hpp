#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "scene\scene_node.hpp"
#include "model\model_descriptor.hpp"
#include "sprite\sprite_object.hpp"
#include "sprite\sprite_batch.hpp"
#include "rendering\structured_buffer.hpp"
#include "buffer\transform_buffer.hpp"
#include "buffer\light_buffer.hpp"
#include "shader\basic_shader.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	class World final {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		World(ID3D11Device2 *device, ID3D11DeviceContext2 *device_context);
		World(const World &world) = delete;
		World(World &&world) = default;
		~World();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------	

		World &operator=(const World &world) = delete;
		World &operator=(World &&world) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------	
		void Clear();

		void Render2D() const;
		void Render3D() const;

		//-------------------------------------------------------------------------
		// Member Methods: Camera
		//-------------------------------------------------------------------------
		
		SharedPtr< PerspectiveCameraNode > GetCamera() const {
			return m_camera;
		}
		void SetCamera(SharedPtr< PerspectiveCameraNode > camera) {
			m_camera = camera;
		}

		SharedPtr< OrthographicCameraNode > CreateOrthographicCameraNode();
		SharedPtr< PerspectiveCameraNode > CreatePerspectiveCameraNode();
		SharedPtr< OmniLightNode > CreateOmniLightNode();
		SharedPtr< SpotLightNode > CreateSpotLightNode();
		SharedPtr< ModelNode > CreateModelNode(const ModelDescriptor &desc,
			const CombinedShader &shader = CreateLambertianShader());

		void AddSprite(SharedPtr< SpriteObject > sprite);

	private:

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

		//-------------------------------------------------------------------------
		// Member Methods: Sprites
		//-------------------------------------------------------------------------

		void RemoveSprite(SharedPtr< SpriteObject > sprite);
		void RemoveAllSprites();
		template< typename ActionT >
		void ForEachSprite(ActionT action) const;

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		SharedPtr< PerspectiveCameraNode > m_camera;

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

#include "world\world.tpp"

#pragma endregion