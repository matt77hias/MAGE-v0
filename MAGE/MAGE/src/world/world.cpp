//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "world\world.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	World::World(ID3D11Device2 *device, ID3D11DeviceContext2 *device_context)
		: m_camera(nullptr), 
		m_models(), m_omni_lights(), m_spot_lights(), m_sprites(), 
		m_sprite_batch(new SpriteBatch(device, device_context)),
		m_transform_buffer(device, device_context),
		m_light_data_buffer(device, device_context), 
		m_omni_lights_buffer(device, device_context, 64),
		m_spot_lights_buffer(device, device_context, 64) {}

	World::~World() {
		Clear();
	}

	void World::Clear() {
		RemoveAllModels();
		RemoveAllLights();
		RemoveAllSprites();
	}

	void World::Render2D() const {
		m_sprite_batch->Begin();
		
		ForEachSprite([this](const SpriteObject &sprite) {
			sprite.Draw(*m_sprite_batch);
		});
		
		m_sprite_batch->End();
	}
	void World::Render3D() const {
		
		const XMMATRIX world_to_view = m_camera->GetWorldToViewMatrix();
		const XMMATRIX view_to_world = XMMatrixInverse(nullptr, world_to_view);

		// Update omni light structured buffer.
		vector< OmniLightBuffer > omni_lights_buffer;
		ForEachOmniLight([&omni_lights_buffer, &world_to_view](const OmniLightNode &light_node) {
			OmniLightBuffer light_buffer;
			
			XMStoreFloat4(&light_buffer.m_p, XMVector4Transform(light_node.GetWorldEye(), world_to_view));
			light_buffer.m_I                      = light_node.GetObject()->GetIntensity();
			light_buffer.m_distance_falloff_start = light_node.GetObject()->GetStartDistanceFalloff();
			light_buffer.m_distance_falloff_end   = light_node.GetObject()->GetEndDistanceFalloff();
			
			omni_lights_buffer.push_back(light_buffer);
		});
		m_omni_lights_buffer.UpdateData(omni_lights_buffer);

		// Update spot light structured buffer.
		vector< SpotLightBuffer > spot_lights_buffer;
		ForEachSpotLight([&spot_lights_buffer, &world_to_view](const SpotLightNode &light_node) {
			SpotLightBuffer light_buffer;

			XMStoreFloat4(&light_buffer.m_p, XMVector4Transform(light_node.GetWorldEye(), world_to_view));
			light_buffer.m_I                      = light_node.GetObject()->GetIntensity();
			light_buffer.m_exponent_property      = light_node.GetObject()->GetExponentProperty();
			XMStoreFloat3(&light_buffer.m_d, XMVector4Transform(light_node.GetWorldForward(), world_to_view));
			light_buffer.m_distance_falloff_start = light_node.GetObject()->GetStartDistanceFalloff();
			light_buffer.m_distance_falloff_end   = light_node.GetObject()->GetEndDistanceFalloff();
			light_buffer.m_cos_penumbra           = light_node.GetObject()->GetStartAngualCutoff();
			light_buffer.m_cos_umbra              = light_node.GetObject()->GetEndAngualCutoff();

			spot_lights_buffer.push_back(light_buffer);
		});
		m_spot_lights_buffer.UpdateData(spot_lights_buffer);

		// Update light data constant buffer.
		LightDataBuffer light_data_buffer;
		light_data_buffer.m_nb_omni_lights = static_cast< uint32_t >(omni_lights_buffer.size());
		light_data_buffer.m_nb_spot_lights = static_cast< uint32_t >(spot_lights_buffer.size());
		m_light_data_buffer.UpdateData(light_data_buffer);
		
		// Create lighting buffer.
		Lighting lighting;
		lighting.light_data  = m_light_data_buffer.Get();
		lighting.omni_lights = m_omni_lights_buffer.Get();
		lighting.spot_lights = m_spot_lights_buffer.Get();

		// Create Transform buffer.
		TransformBuffer transform_buffer(
			m_camera->GetWorldToViewMatrix(),
			m_camera->GetObject()->GetViewToProjectionMatrix());

		// Render models.
		ForEachModel([&](const ModelNode &model_node) {
			const Model *model = model_node.GetObject();
			if (model->GetNumberOfIndices() != 0) {

				// Update transform constant buffer.
				const XMMATRIX object_to_world = model_node.GetObjectToWorldMatrix();
				const XMMATRIX world_to_object = model_node.GetWorldToObjectMatrix();

				XMFLOAT4X4 m;
				XMStoreFloat4x4(&m, world_to_object);
				const XMMATRIX view_to_object  = view_to_world * world_to_object;
				transform_buffer.SetObjectMatrices(object_to_world, view_to_object);
				m_transform_buffer.UpdateData(transform_buffer);

				// Draw model.
				model->PrepareDrawing();
				model->PrepareShading(m_transform_buffer.Get(), lighting);
				model->Draw();
			}
		});
	}

	SharedPtr< OrthographicCameraNode > World::CreateOrthographicCameraNode() {
		SharedPtr< OrthographicCamera > camera = CreateOrthographicCamera();
		SharedPtr< OrthographicCameraNode > camera_node(new OrthographicCameraNode("camera", camera));
		//SetCamera(camera_node);
		return camera_node;
	}
	SharedPtr< PerspectiveCameraNode > World::CreatePerspectiveCameraNode() {
		SharedPtr< PerspectiveCamera > camera = CreatePerspectiveCamera();
		SharedPtr< PerspectiveCameraNode > camera_node(new PerspectiveCameraNode("camera", camera));
		SetCamera(camera_node);
		return camera_node;
	}
	SharedPtr< OmniLightNode > World::CreateOmniLightNode() {
		SharedPtr< OmniLight > light(new OmniLight());
		SharedPtr< OmniLightNode > light_node(new OmniLightNode("light", light));
		AddLight(light_node);
		return light_node;
	}
	SharedPtr< SpotLightNode > World::CreateSpotLightNode() {
		SharedPtr< SpotLight > light(new SpotLight());
		SharedPtr< SpotLightNode > light_node(new SpotLightNode("light", light));
		AddLight(light_node);
		return light_node;
	}
	SharedPtr< ModelNode > World::CreateModelNode(const ModelDescriptor &desc,
		const CombinedShader &shader) {

		const Material default_material(MAGE_MDL_PART_DEFAULT_MATERIAL);
		const ShadedMaterial default_shaded_material(shader, default_material);

		SharedPtr< Model > root_model(new Model(desc.GetMesh(), 0, 0, default_shaded_material));
		SharedPtr< ModelNode > root_model_node(new ModelNode("model", root_model));
		AddModel(root_model_node);

		typedef pair< SharedPtr< ModelNode >, string > ModelNodePair;
		map< string, ModelNodePair > mapping;

		desc.ForEachModelPart([&](const ModelPart &model_part) {
			if (model_part.m_child == MAGE_MDL_PART_DEFAULT_CHILD && model_part.m_nb_indices == 0) {
				return;
			}

			if (model_part.m_material == MAGE_MDL_PART_DEFAULT_MATERIAL) {
				SharedPtr< Model > submodel(new Model(desc.GetMesh(), model_part.m_start_index, model_part.m_nb_indices, default_shaded_material));
				SharedPtr< ModelNode > submodel_node(new ModelNode(model_part.m_child, submodel));
				AddModel(submodel_node);
				mapping[model_part.m_child] = ModelNodePair(submodel_node, model_part.m_parent);
			}
			else {
				const Material material(*desc.GetMaterial(model_part.m_material));
				const ShadedMaterial shaded_material(shader, material);
				SharedPtr< Model > submodel(new Model(desc.GetMesh(), model_part.m_start_index, model_part.m_nb_indices, shaded_material));
				SharedPtr< ModelNode > submodel_node(new ModelNode(model_part.m_child, submodel));
				AddModel(submodel_node);
				mapping[model_part.m_child] = ModelNodePair(submodel_node, model_part.m_parent);
			}
		});

		for (map< string, ModelNodePair >::const_iterator it = mapping.cbegin(); it != mapping.cend(); ++it) {
			const ModelNodePair &element = it->second;
			const string &parent = element.second;
			if (parent == MAGE_MDL_PART_DEFAULT_PARENT) {
				root_model_node->AddChildTransformNode(element.first);
			}
			else {
				mapping[parent].first->AddChildTransformNode(element.first);
			}
		}

		return root_model_node;
	}

	//-------------------------------------------------------------------------
	// Models
	//-------------------------------------------------------------------------

	void World::AddModel(SharedPtr< ModelNode > model) {
		if (!model) {
			return;
		}
		m_models.push_back(model);
	}
	void World::RemoveModel(SharedPtr< ModelNode > model) {
		vector< SharedPtr< ModelNode > >::iterator it = std::find(m_models.begin(), m_models.end(), model);
		if (it != m_models.end()) {
			m_models.erase(it);
		}
	}
	void World::RemoveAllModels() {
		m_models.clear();
	}

	//-------------------------------------------------------------------------
	// Lights
	//-------------------------------------------------------------------------

	void World::AddLight(SharedPtr< OmniLightNode > light) {
		if (!light) {
			return;
		}
		m_omni_lights.push_back(light);
	}
	void World::AddLight(SharedPtr< SpotLightNode > light) {
		if (!light) {
			return;
		}
		m_spot_lights.push_back(light);
	}
	void World::RemoveLight(SharedPtr< OmniLightNode > light) {
		vector< SharedPtr< OmniLightNode > >::iterator it = std::find(m_omni_lights.begin(), m_omni_lights.end(), light);
		if (it != m_omni_lights.end()) {
			m_omni_lights.erase(it);
		}
	}
	void World::RemoveLight(SharedPtr< SpotLightNode > light) {
		vector< SharedPtr< SpotLightNode > >::iterator it = std::find(m_spot_lights.begin(), m_spot_lights.end(), light);
		if (it != m_spot_lights.end()) {
			m_spot_lights.erase(it);
		}
	}
	void World::RemoveAllLights() {
		m_omni_lights.clear();
		m_spot_lights.clear();
	}

	//-------------------------------------------------------------------------
	// Sprites
	//-------------------------------------------------------------------------

	void World::AddSprite(SharedPtr< SpriteObject > sprite) {
		if (!sprite) {
			return;
		}
		m_sprites.push_back(sprite);
	}
	void World::RemoveSprite(SharedPtr< SpriteObject > sprite) {
		vector< SharedPtr< SpriteObject > >::iterator it = std::find(m_sprites.begin(), m_sprites.end(), sprite);
		if (it != m_sprites.end()) {
			m_sprites.erase(it);
		}
	}
	void World::RemoveAllSprites() {
		m_sprites.clear();
	}
}