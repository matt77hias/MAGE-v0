//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "scene\scene.hpp"
#include "resource\resource_manager.hpp"
#include "texture\texture_factory.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	Scene::Scene(const string &name)
		: m_name(name), m_scripts(), m_scene_fog(), m_camera(nullptr),
		m_models(), m_omni_lights(), m_spot_lights(), m_sprites(),
		m_sprite_batch(new SpriteBatch()),
		m_transform_buffer(), m_scene_buffer(),
		m_omni_lights_buffer(64), m_spot_lights_buffer(64) {
		
		MeshDescriptor< VertexPositionNormalTexture > mesh_desc(true, true);
		SharedPtr< ModelDescriptor > model_desc_box = GetOrCreateModelDescriptor(L"assets/models/cube/cube.mdl", mesh_desc);
		m_box = CreateModelNode(*model_desc_box, BRDFType::Emissive);
		m_box->MakePassive();
		
		SharedPtr< Texture > white = CreateWhiteTexture();
		ShadedMaterial *material = m_box->GetModel()->GetMaterial();
		material->SetDiffuseReflectivity(RGBSpectrum(0.0f, 1.0f, 0.0f));
		material->SetDiffuseReflectivityTexture(white);
	}

	Scene::~Scene() {
		// Clears this scene.
		Clear();
	}
	
	//-------------------------------------------------------------------------
	// Scene Member Methods: Lifecycle
	//-------------------------------------------------------------------------

	void Scene::Initialize() {
		// Loads this scene.
		Load();
	}
	
	void Scene::Uninitialize() {
		// Closes this scene.
		Close();
		// Clears this scene.
		Clear();
	}

	void Scene::Clear() {
		RemoveAllScripts();
		RemoveAllModels();
		RemoveAllLights();
		RemoveAllSprites();
	}

	void Scene::Render2D() const {
		m_sprite_batch->Begin();

		ForEachSprite([this](const SpriteObject &sprite) {
			if (sprite.IsPassive()) {
				return;
			}

			sprite.Draw(*m_sprite_batch);
		});

		m_sprite_batch->End();
	}

	void Scene::Render3D() const {

		const XMMATRIX world_to_view = m_camera->GetTransform()->GetWorldToViewMatrix();
		const XMMATRIX view_to_world = m_camera->GetTransform()->GetViewToWorldMatrix();

		// Update omni light structured buffer.
		vector< OmniLightBuffer > omni_lights_buffer;
		ForEachOmniLight([&omni_lights_buffer, &world_to_view](const OmniLightNode &light_node) {
			if (light_node.IsPassive()) {
				return;
			}

			const TransformNode * const transform = light_node.GetTransform();
			const OmniLight     * const light     = light_node.GetLight();
			
			OmniLightBuffer light_buffer;
			XMStoreFloat4(&light_buffer.m_p, XMVector4Transform(transform->GetWorldEye(), world_to_view));
			light_buffer.m_I                      = light->GetIntensity();
			light_buffer.m_distance_falloff_end   = light->GetEndDistanceFalloff();
			light_buffer.m_distance_falloff_range = light->GetRangeDistanceFalloff();

			omni_lights_buffer.push_back(std::move(light_buffer));
		});
		m_omni_lights_buffer.UpdateData(omni_lights_buffer);

		// Update spotlight structured buffer.
		vector< SpotLightBuffer > spot_lights_buffer;
		ForEachSpotLight([&spot_lights_buffer, &world_to_view](const SpotLightNode &light_node) {
			if (light_node.IsPassive()) {
				return;
			}
			
			const TransformNode * const transform = light_node.GetTransform();
			const SpotLight     * const light     = light_node.GetLight();
			
			SpotLightBuffer light_buffer;
			XMStoreFloat4(&light_buffer.m_p, XMVector4Transform(transform->GetWorldEye(), world_to_view));
			light_buffer.m_I                      = light->GetIntensity();
			light_buffer.m_exponent_property      = light->GetExponentProperty();
			XMStoreFloat3(&light_buffer.m_d, XMVector4Transform(transform->GetWorldForward(), world_to_view));
			light_buffer.m_distance_falloff_end   = light->GetEndDistanceFalloff();
			light_buffer.m_distance_falloff_range = light->GetRangeDistanceFalloff();
			light_buffer.m_cos_umbra              = light->GetEndAngularCutoff();
			light_buffer.m_cos_range              = light->GetRangeAngularCutoff();

			spot_lights_buffer.push_back(std::move(light_buffer));
		});
		m_spot_lights_buffer.UpdateData(spot_lights_buffer);

		// Update scene constant buffer.
		SceneBuffer scene_buffer;
		scene_buffer.m_nb_omni_lights             = static_cast< uint32_t >(omni_lights_buffer.size());
		scene_buffer.m_nb_spot_lights             = static_cast< uint32_t >(spot_lights_buffer.size());
		scene_buffer.m_fog_color                  = m_scene_fog.GetIntensity();
		scene_buffer.m_fog_distance_falloff_start = m_scene_fog.GetStartDistanceFalloff();
		scene_buffer.m_fog_distance_falloff_range = m_scene_fog.GetRangeDistanceFalloff();

		m_scene_buffer.UpdateData(scene_buffer);

		// Create lighting buffer.
		SceneInfo scene_info;
		scene_info.m_scene_buffer = m_scene_buffer.Get();
		scene_info.m_omni_lights  = m_omni_lights_buffer.Get();
		scene_info.m_spot_lights  = m_spot_lights_buffer.Get();

		const XMMATRIX view_to_projection = m_camera->GetCamera()->GetViewToProjectionMatrix();

		// Create Transform buffer.
		TransformBuffer transform_buffer(world_to_view, view_to_projection);

		for (bool transparency : {false, true}) {

			// Render models.
			ForEachModel([this, transparency, &transform_buffer, &scene_info, &view_to_world](const ModelNode &model_node) {
				if (model_node.IsPassive()) {
					return;
				}

				const Model * const model = model_node.GetModel();

				if (model->GetNumberOfIndices() == 0) {
					return;
				}
				if (model->GetMaterial()->IsTransparant() != transparency) {
					return;
				}

				const TransformNode * const transform = model_node.GetTransform();

				// Update transform constant buffer.
				const XMMATRIX object_to_world = transform->GetObjectToWorldMatrix();
				const XMMATRIX world_to_object = transform->GetWorldToObjectMatrix();
				const XMMATRIX view_to_object = view_to_world * world_to_object;
				transform_buffer.SetObjectMatrices(object_to_world, view_to_object);
				m_transform_buffer.UpdateData(transform_buffer);

				// Draw model.
				model->PrepareDrawing();
				model->PrepareShading(m_transform_buffer.Get(), scene_info);
				model->Draw();
			});
		}
	}

	void Scene::RenderBoundingBoxes() const {
		const XMMATRIX world_to_view = m_camera->GetTransform()->GetWorldToViewMatrix();
		const XMMATRIX view_to_world = m_camera->GetTransform()->GetViewToWorldMatrix();
		const XMMATRIX view_to_projection = m_camera->GetCamera()->GetViewToProjectionMatrix();

		// Create Transform buffer.
		TransformBuffer transform_buffer(world_to_view, view_to_projection);

		// Render models.
		ForEachModel([this, &transform_buffer, &view_to_world](const ModelNode &model_node) {
			if (model_node.IsPassive()) {
				return;
			}

			const Model * const model = model_node.GetModel();

			if (model->GetNumberOfIndices() == 0) {
				return;
			}

			const AABB &aabb = model->GetAABB();
			const Point3 centroid = aabb.Centroid();
			const Direction3 direction = aabb.Diagonal();
			Transform box_transform;
			box_transform.SetScale(direction);
			box_transform.SetTranslation(centroid.x, centroid.y - 0.5f * direction.y, centroid.z);
			const TransformNode * const transform = model_node.GetTransform();

			// Update transform constant buffer.
			const XMMATRIX object_to_world = box_transform.GetObjectToParentMatrix() * transform->GetObjectToWorldMatrix();
			const XMMATRIX world_to_object = transform->GetWorldToObjectMatrix() * box_transform.GetParentToObjectMatrix();
			const XMMATRIX view_to_object = view_to_world * world_to_object;
			transform_buffer.SetObjectMatrices(object_to_world, view_to_object);
			m_transform_buffer.UpdateData(transform_buffer);

			// Draw bounding box.
			const Model * const box_model = m_box->GetModel();
			box_model->PrepareDrawing();
			box_model->PrepareShading(m_transform_buffer.Get(), SceneInfo());
			box_model->Draw();
		});
	}

	//-------------------------------------------------------------------------
	// Scene Member Methods: Factory Methods
	//-------------------------------------------------------------------------

	SharedPtr< OrthographicCameraNode > Scene::CreateOrthographicCameraNode() {
		return std::make_shared< OrthographicCameraNode >("camera");
	}

	SharedPtr< PerspectiveCameraNode > Scene::CreatePerspectiveCameraNode() {
		return std::make_shared< PerspectiveCameraNode >("camera");
	}

	SharedPtr< OmniLightNode > Scene::CreateOmniLightNode() {
		SharedPtr< OmniLightNode > light_node = std::make_shared< OmniLightNode >("light");
		
		// Adds this omni light node to this scene.
		AddLight(light_node);
		
		return light_node;
	}

	SharedPtr< SpotLightNode > Scene::CreateSpotLightNode() {
		SharedPtr< SpotLightNode > light_node = std::make_shared< SpotLightNode >("light");
		
		// Adds this spotlight node to this scene.
		AddLight(light_node);

		return light_node;
	}

	SharedPtr< ModelNode > Scene::CreateModelNode(const ModelDescriptor &desc,
		BRDFType brdf) {

		// Creates a default material.
		const Material default_material(MAGE_MDL_PART_DEFAULT_MATERIAL);
		// Creates a default shaded material.
		const ShadedMaterial default_shaded_material(default_material, brdf);

		SharedPtr< ModelNode > root_model_node;
		size_t nb_root_childs = 0;

		using ModelNodePair = pair< SharedPtr< ModelNode >, string >;
		map< const string, ModelNodePair > mapping;

		desc.ForEachModelPart([&](const ModelPart &model_part) {

			if (model_part.m_child == MAGE_MDL_PART_DEFAULT_CHILD && model_part.m_nb_indices == 0) {
				return;
			}

			// Creates a material.
			const Material material = (model_part.m_material == MAGE_MDL_PART_DEFAULT_MATERIAL) ?
				default_material : *desc.GetMaterial(model_part.m_material);
			// Creates a shaded material.
			const ShadedMaterial shaded_material(material, brdf);

			// Creates a submodel node.
			SharedPtr< ModelNode > submodel_node = std::make_shared< ModelNode >(model_part.m_child,
				desc.GetMesh(), model_part.m_start_index, model_part.m_nb_indices, 
				model_part.m_aabb, model_part.m_bs, shaded_material);
			// Adds this submodel node to this scene.
			AddModel(submodel_node);

			if (model_part.m_parent == MAGE_MDL_PART_DEFAULT_PARENT) {
				root_model_node = submodel_node;
				++nb_root_childs;
			}

			// Adds this submodel node to the mapping.
			mapping.insert(std::make_pair(model_part.m_child, ModelNodePair(submodel_node, model_part.m_parent)));
		});

		Assert(nb_root_childs != 0);

		const bool create_root_model_node = (nb_root_childs > 1);

		if (create_root_model_node) {
			// Creates a root model node.
			root_model_node = std::make_shared< ModelNode >("model",
				desc.GetMesh(), 0, 0, AABB(), BS(), default_shaded_material);
			// Adds this root model node to this scene.
			AddModel(root_model_node);
		}

		for (auto it = mapping.cbegin(); it != mapping.cend(); ++it) {
			const SharedPtr< ModelNode > &child = it->second.first;
			const string &parent = it->second.second;
			if (parent == MAGE_MDL_PART_DEFAULT_PARENT) {
				if (create_root_model_node) {
					root_model_node->AddChildNode(child);
				}
			}
			else {
				mapping[parent].first->AddChildNode(child);
			}
		}

		return root_model_node;
	}

	SharedPtr< ModelNode > Scene::CreateModelNode(const ModelDescriptor &desc,
		const CombinedShader &shader) {

		// Creates a default material.
		const Material default_material(MAGE_MDL_PART_DEFAULT_MATERIAL);
		// Creates a default shaded material.
		const ShadedMaterial default_shaded_material(default_material, shader);

		SharedPtr< ModelNode > root_model_node;
		size_t nb_root_childs = 0;

		using ModelNodePair = pair< SharedPtr< ModelNode >, string >;
		map< const string, ModelNodePair > mapping;

		desc.ForEachModelPart([&](const ModelPart &model_part) {
			
			if (model_part.m_child == MAGE_MDL_PART_DEFAULT_CHILD && model_part.m_nb_indices == 0) {
				return;
			}

			// Creates a material.
			const Material material = (model_part.m_material == MAGE_MDL_PART_DEFAULT_MATERIAL) ?
				default_material : *desc.GetMaterial(model_part.m_material);
			// Creates a shaded material.
			const ShadedMaterial shaded_material(material, shader);

			// Creates a submodel node.
			SharedPtr< ModelNode > submodel_node = std::make_shared< ModelNode >(model_part.m_child,
				desc.GetMesh(), model_part.m_start_index, model_part.m_nb_indices, 
				model_part.m_aabb, model_part.m_bs, shaded_material);
			// Adds this submodel node to this scene.
			AddModel(submodel_node);

			if (model_part.m_parent == MAGE_MDL_PART_DEFAULT_PARENT) {
				root_model_node = submodel_node;
				++nb_root_childs;
			}

			// Adds this submodel node to the mapping.
			mapping.insert(std::make_pair(model_part.m_child, ModelNodePair(submodel_node, model_part.m_parent)));
		});

		Assert(nb_root_childs != 0);

		const bool create_root_model_node = (nb_root_childs > 1);

		if (create_root_model_node) {
			// Creates a root model node.
			root_model_node = std::make_shared< ModelNode >("model",
				desc.GetMesh(), 0, 0, AABB(), BS(), default_shaded_material);
			// Adds this root model node to this scene.
			AddModel(root_model_node);
		}

		for (auto it = mapping.cbegin(); it != mapping.cend(); ++it) {
			const SharedPtr< ModelNode > &child = it->second.first;
			const string &parent = it->second.second;
			if (parent == MAGE_MDL_PART_DEFAULT_PARENT) {
				if (create_root_model_node) {
					root_model_node->AddChildNode(child);
				}
			}
			else {
				mapping[parent].first->AddChildNode(child);
			}
		}

		return root_model_node;
	}

	//-------------------------------------------------------------------------
	// Scene Member Methods: Scripts
	//-------------------------------------------------------------------------

	bool Scene::HasScript(SharedPtr< const BehaviorScript > script) const {
		return std::find(m_scripts.begin(), m_scripts.end(), script) != m_scripts.end();
	}
	
	void Scene::AddScript(SharedPtr< BehaviorScript > script) {
		if (!script) {
			return;
		}

		m_scripts.push_back(std::move(script));
	}
	
	void Scene::RemoveScript(SharedPtr< BehaviorScript > script) {
		const auto it = std::find(m_scripts.begin(), m_scripts.end(), script);
		if (it != m_scripts.end()) {
			m_scripts.erase(it);
		}
	}
	
	void Scene::RemoveAllScripts() {
		m_scripts.clear();
	}

	//-------------------------------------------------------------------------
	// Scene Member Methods: Models
	//-------------------------------------------------------------------------

	void Scene::AddModel(SharedPtr< ModelNode > model) {
		if (!model) {
			return;
		}
		m_models.push_back(std::move(model));
	}
	
	void Scene::RemoveModel(SharedPtr< ModelNode > model) {
		const auto it = std::find(m_models.begin(), m_models.end(), model);
		if (it != m_models.end()) {
			m_models.erase(it);
		}
	}
	
	void Scene::RemoveAllModels() {
		m_models.clear();
	}

	//-------------------------------------------------------------------------
	// Scene Member Methods: Lights
	//-------------------------------------------------------------------------

	void Scene::AddLight(SharedPtr< OmniLightNode > light) {
		if (!light) {
			return;
		}
		m_omni_lights.push_back(std::move(light));
	}

	void Scene::AddLight(SharedPtr< SpotLightNode > light) {
		if (!light) {
			return;
		}
		m_spot_lights.push_back(std::move(light));
	}

	void Scene::RemoveLight(SharedPtr< OmniLightNode > light) {
		const auto it = std::find(m_omni_lights.begin(), m_omni_lights.end(), light);
		if (it != m_omni_lights.end()) {
			m_omni_lights.erase(it);
		}
	}

	void Scene::RemoveLight(SharedPtr< SpotLightNode > light) {
		const auto it = std::find(m_spot_lights.begin(), m_spot_lights.end(), light);
		if (it != m_spot_lights.end()) {
			m_spot_lights.erase(it);
		}
	}

	void Scene::RemoveAllLights() {
		m_omni_lights.clear();
		m_spot_lights.clear();
	}

	//-------------------------------------------------------------------------
	// Scene Member Methods: Sprites
	//-------------------------------------------------------------------------

	void Scene::AddSprite(SharedPtr< SpriteObject > sprite) {
		if (!sprite) {
			return;
		}
		m_sprites.push_back(std::move(sprite));
	}

	void Scene::RemoveSprite(SharedPtr< SpriteObject > sprite) {
		const auto it = std::find(m_sprites.begin(), m_sprites.end(), sprite);
		if (it != m_sprites.end()) {
			m_sprites.erase(it);
		}
	}

	void Scene::RemoveAllSprites() {
		m_sprites.clear();
	}
}