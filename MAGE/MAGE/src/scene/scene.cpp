//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "scene\scene.hpp"
#include "resource\resource_manager.hpp"
#include "resource\resource_factory.hpp"
#include "math\view_frustum.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	Scene::Scene(const string &name)
		: m_name(name), m_scripts(),
		m_scene_fog(MakeUnique< SceneFog >()), 
		m_cameras(), m_models(), m_ambient_light(), 
		m_directional_lights(), m_omni_lights(), m_spot_lights(), m_sprites(),
		m_sprite_batch(MakeUnique< SpriteBatch >()),
		m_transform_buffer(), m_scene_buffer(),
		m_directional_lights_buffer(3), 
		m_omni_lights_buffer(64), 
		m_spot_lights_buffer(64) {
		
		Create< AmbientLightNode >("ambient light");

		//TODO
		Material box_material("_mat_aabb");
		SharedPtr< Texture > white = CreateWhiteTexture();
		box_material.SetDiffuseReflectivityTexture(white);
		box_material.SetDiffuseReflectivity(RGBSpectrum(0.0f, 1.0f, 0.0f));
		const ShadedMaterial box_shaded_material(box_material, BRDFType::Emissive);

		SharedPtr< const StaticMesh > box_mesh = CreateLineCube();
		m_box = MakeUnique< ModelNode >("_mdl_aabb", box_mesh, box_shaded_material);
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

	void Scene::Clear() noexcept {
		// Scripts
		RemoveAllScripts();

		// World
		m_scene_fog.reset();
		m_cameras.clear();
		m_models.clear();
		m_ambient_light.reset();
		m_directional_lights.clear();
		m_omni_lights.clear();
		m_spot_lights.clear();
		m_sprites.clear();
	}

	void Scene::Render2D() const {
		m_sprite_batch->Begin();

		ForEachSprite([this](const SpriteNode &sprite) {
			if (sprite.IsPassive()) {
				return;
			}

			sprite.GetSprite()->Draw(*m_sprite_batch);
		});

		m_sprite_batch->End();
	}

	void Scene::Render3D() const {
		const XMMATRIX world_to_view = m_cameras[0]->GetTransform()->GetWorldToViewMatrix();
		const XMMATRIX view_to_world = m_cameras[0]->GetTransform()->GetViewToWorldMatrix();

		// Update directional light structured buffer.
		vector< DirectionalLightBuffer > directional_lights_buffer;
		ForEachDirectionalLight([&directional_lights_buffer, &world_to_view](const DirectionalLightNode &light_node) {
			if (light_node.IsPassive()) {
				return;
			}

			const TransformNode * const transform = light_node.GetTransform();
			const DirectionalLight * const light  = light_node.GetLight();

			DirectionalLightBuffer light_buffer;
			XMStoreFloat3(&light_buffer.m_d, XMVector3TransformNormal(transform->GetWorldForward(), world_to_view));
			light_buffer.m_I = light->GetIntensity();

			directional_lights_buffer.push_back(std::move(light_buffer));
		});
		m_directional_lights_buffer.UpdateData(directional_lights_buffer);

		// Update omni light structured buffer.
		vector< OmniLightBuffer > omni_lights_buffer;
		ForEachOmniLight([&omni_lights_buffer, &world_to_view](const OmniLightNode &light_node) {
			if (light_node.IsPassive()) {
				return;
			}

			const TransformNode * const transform = light_node.GetTransform();
			const OmniLight     * const light     = light_node.GetLight();
			
			OmniLightBuffer light_buffer;
			XMStoreFloat3(&light_buffer.m_p, XMVector3TransformCoord(transform->GetWorldEye(), world_to_view));
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
			XMStoreFloat3(&light_buffer.m_p, XMVector3TransformCoord(transform->GetWorldEye(), world_to_view));
			XMStoreFloat3(&light_buffer.m_d, XMVector3TransformNormal(transform->GetWorldForward(), world_to_view));
			light_buffer.m_I                      = light->GetIntensity();
			light_buffer.m_exponent_property      = light->GetExponentProperty();
			light_buffer.m_distance_falloff_end   = light->GetEndDistanceFalloff();
			light_buffer.m_distance_falloff_range = light->GetRangeDistanceFalloff();
			light_buffer.m_cos_umbra              = light->GetEndAngularCutoff();
			light_buffer.m_cos_range              = light->GetRangeAngularCutoff();

			spot_lights_buffer.push_back(std::move(light_buffer));
		});
		m_spot_lights_buffer.UpdateData(spot_lights_buffer);

		// Update scene constant buffer.
		SceneBuffer scene_buffer;
		scene_buffer.m_Ia = m_ambient_light->GetLight()->GetIntensity();
		scene_buffer.m_nb_directional_lights      = static_cast< uint32_t >(directional_lights_buffer.size());
		scene_buffer.m_nb_omni_lights             = static_cast< uint32_t >(omni_lights_buffer.size());
		scene_buffer.m_nb_spot_lights             = static_cast< uint32_t >(spot_lights_buffer.size());
		scene_buffer.m_fog_color                  = m_scene_fog->GetIntensity();
		scene_buffer.m_fog_distance_falloff_start = m_scene_fog->GetStartDistanceFalloff();
		scene_buffer.m_fog_distance_falloff_range = m_scene_fog->GetRangeDistanceFalloff();

		m_scene_buffer.UpdateData(scene_buffer);

		// Create lighting buffer.
		SceneInfo scene_info;
		scene_info.m_scene_buffer       = m_scene_buffer.Get();
		scene_info.m_directional_lights = m_directional_lights_buffer.Get();
		scene_info.m_omni_lights        = m_omni_lights_buffer.Get();
		scene_info.m_spot_lights        = m_spot_lights_buffer.Get();

		const XMMATRIX view_to_projection  = m_cameras[0]->GetCamera()->GetViewToProjectionMatrix();
		const XMMATRIX world_to_projection = world_to_view * view_to_projection;

		// Create Transform buffer.
		TransformBuffer transform_buffer(world_to_view, view_to_projection);

		for (bool transparency : {false, true}) {

			// Render models.
			ForEachModel([this, transparency, &transform_buffer, &scene_info,
				&view_to_world, &world_to_projection](const ModelNode &model_node) {
				
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

				// Update transform constant buffer (1/2).
				const XMMATRIX object_to_world      = transform->GetObjectToWorldMatrix();
				const XMMATRIX object_to_projection = object_to_world * world_to_projection;
				
				// View Frustum Culling.
				ViewFrustum view_frustum(object_to_projection);
				const AABB &aabb = model->GetAABB();
				if (!view_frustum.Overlaps(aabb)) {
					return;
				}
				
				// Update transform constant buffer (2/2).
				const XMMATRIX world_to_object      = transform->GetWorldToObjectMatrix();
				const XMMATRIX view_to_object       = view_to_world * world_to_object;
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

		// Optimization: Use a separate shader + instancing (1 draw call)

		// Update scene constant buffer.
		SceneBuffer scene_buffer;
		scene_buffer.m_fog_distance_falloff_start = FLT_MAX;
		scene_buffer.m_fog_distance_falloff_range = FLT_MAX;

		m_scene_buffer.UpdateData(scene_buffer);

		// Create lighting buffer.
		SceneInfo scene_info;
		scene_info.m_scene_buffer = m_scene_buffer.Get();

		const XMMATRIX world_to_view       = m_cameras[0]->GetTransform()->GetWorldToViewMatrix();
		const XMMATRIX view_to_world       = m_cameras[0]->GetTransform()->GetViewToWorldMatrix();
		const XMMATRIX view_to_projection  = m_cameras[0]->GetCamera()->GetViewToProjectionMatrix();
		const XMMATRIX world_to_projection = world_to_view * view_to_projection;

		// Create Transform buffer.
		TransformBuffer transform_buffer(world_to_view, view_to_projection);

		// Render models.
		ForEachModel([this, &transform_buffer, &scene_info,
			&view_to_world, &world_to_projection](const ModelNode &model_node) {
			
			if (model_node.IsPassive()) {
				return;
			}

			const Model * const model = model_node.GetModel();

			if (model->GetNumberOfIndices() == 0) {
				return;
			}

			const TransformNode * const transform = model_node.GetTransform();

			// Update transform constant buffer (1/2).
			const XMMATRIX object_to_world      = transform->GetObjectToWorldMatrix();
			const XMMATRIX object_to_projection = object_to_world * world_to_projection;

			// View Frustum Culling.
			ViewFrustum view_frustum(object_to_projection);
			const AABB &aabb = model->GetAABB();
			if (!view_frustum.Overlaps(aabb)) {
				return;
			}

			Transform box_transform;
			box_transform.SetScale(aabb.Diagonal());
			box_transform.SetTranslation(aabb.Centroid());
			
			// Update transform constant buffer (2/2).
			const XMMATRIX world_to_object = transform->GetWorldToObjectMatrix();
			const XMMATRIX box_to_world    = box_transform.GetObjectToParentMatrix() * object_to_world;
			const XMMATRIX world_to_box    = world_to_object * box_transform.GetParentToObjectMatrix();
			const XMMATRIX view_to_box     = view_to_world * world_to_box;
			transform_buffer.SetObjectMatrices(box_to_world, view_to_box);
			m_transform_buffer.UpdateData(transform_buffer);

			// Draw bounding box.
			const Model * const box_model = m_box->GetModel();
			box_model->PrepareDrawing();
			box_model->PrepareShading(m_transform_buffer.Get(), scene_info);
			box_model->Draw();
		});
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
	
	void Scene::RemoveAllScripts() noexcept {
		m_scripts.clear();
	}

	//-------------------------------------------------------------------------
	// Scene Member Methods: World
	//-------------------------------------------------------------------------

	SharedPtr< ModelNode > Scene::CreateModel(
		const ModelDescriptor &desc, BRDFType brdf) {

		// Create a default material.
		const Material default_material("material");
		// Create a default shaded material.
		const ShadedMaterial default_shaded_material(default_material, brdf);

		SharedPtr< ModelNode > root_model_node;
		size_t nb_root_childs = 0;

		using ModelPair = pair< SharedPtr< ModelNode >, string >;
		map< string, ModelPair > mapping;

		// Create model nodes.
		desc.ForEachModelPart([&](const ModelPart &model_part) {

			if (model_part.m_child == MAGE_MDL_PART_DEFAULT_CHILD && model_part.m_nb_indices == 0) {
				return;
			}

			// Create a material.
			const Material material = (model_part.m_material == MAGE_MDL_PART_DEFAULT_MATERIAL) ?
				default_material : *desc.GetMaterial(model_part.m_material);
			// Create a shaded material.
			const ShadedMaterial shaded_material(material, brdf);

			// Create a submodel node.
			SharedPtr< ModelNode > submodel_node = MakeShared< ModelNode >(
														model_part.m_child, desc.GetMesh(), 
														model_part.m_start_index, model_part.m_nb_indices,
														model_part.m_aabb, model_part.m_bs, shaded_material);
			// Add this submodel node to this scene.
			AddSceneNode(submodel_node);

			if (model_part.m_parent == MAGE_MDL_PART_DEFAULT_PARENT) {
				root_model_node = submodel_node;
				++nb_root_childs;
			}

			// Add this submodel node to the mapping.
			mapping.insert(std::make_pair(model_part.m_child, ModelPair(submodel_node, model_part.m_parent)));
		});

		Assert(nb_root_childs != 0);

		const bool create_root_model_node = (nb_root_childs > 1);

		// Create root model node.
		if (create_root_model_node) {
			root_model_node = MakeShared< ModelNode >(
				"model", desc.GetMesh(), 0, 0, AABB(), BS(), default_shaded_material);
			
			// Add this root model node to this scene.
			AddSceneNode(root_model_node);
		}

		// Connect model nodes.
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

	SharedPtr< ModelNode > Scene::CreateModel(
		const ModelDescriptor &desc, const CombinedShader &shader) {

		// Create a default material.
		const Material default_material("material");
		// Create a default shaded material.
		const ShadedMaterial default_shaded_material(default_material, shader);

		SharedPtr< ModelNode > root_model_node;
		size_t nb_root_childs = 0;

		using ModelPair = pair< SharedPtr< ModelNode >, string >;
		map< string, ModelPair > mapping;

		// Create model nodes.
		desc.ForEachModelPart([&](const ModelPart &model_part) {

			if (model_part.m_child == MAGE_MDL_PART_DEFAULT_CHILD && model_part.m_nb_indices == 0) {
				return;
			}

			// Create a material.
			const Material material = (model_part.m_material == MAGE_MDL_PART_DEFAULT_MATERIAL) ?
				default_material : *desc.GetMaterial(model_part.m_material);
			// Create a shaded material.
			const ShadedMaterial shaded_material(material, shader);

			// Create a submodel node.
			SharedPtr< ModelNode > submodel_node = MakeShared< ModelNode >(
														model_part.m_child, desc.GetMesh(), 
														model_part.m_start_index, model_part.m_nb_indices,
														model_part.m_aabb, model_part.m_bs, shaded_material);
			// Add this submodel node to this scene.
			AddSceneNode(submodel_node);

			if (model_part.m_parent == MAGE_MDL_PART_DEFAULT_PARENT) {
				root_model_node = submodel_node;
				++nb_root_childs;
			}

			// Adds this submodel node to the mapping.
			mapping.insert(std::make_pair(model_part.m_child, ModelPair(submodel_node, model_part.m_parent)));
		});

		Assert(nb_root_childs != 0);

		const bool create_root_model_node = (nb_root_childs > 1);

		// Create root model node.
		if (create_root_model_node) {
			root_model_node = MakeShared< ModelNode >(
				"model", desc.GetMesh(), 0, 0, AABB(), BS(), default_shaded_material);
			
			// Add this root model node to this scene.
			AddSceneNode(root_model_node);
		}

		// Connect model nodes.
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

	void Scene::AddSceneNode(SharedPtr< CameraNode > camera) {
		if (!camera) {
			return;
		}

		m_cameras.push_back(std::move(camera));
	}
	
	void Scene::AddSceneNode(SharedPtr< ModelNode > model) {
		if (!model) {
			return;
		}

		m_models.push_back(std::move(model));
	}
	
	void Scene::AddSceneNode(SharedPtr< AmbientLightNode > light) {
		if (!light) {
			return;
		}

		m_ambient_light = std::move(light);
	}
	
	void Scene::AddSceneNode(SharedPtr< DirectionalLightNode > light) {
		if (!light) {
			return;
		}

		m_directional_lights.push_back(std::move(light));
	}
	
	void Scene::AddSceneNode(SharedPtr< OmniLightNode > light) {
		if (!light) {
			return;
		}

		m_omni_lights.push_back(std::move(light));
	}
	
	void Scene::AddSceneNode(SharedPtr< SpotLightNode > light) {
		if (!light) {
			return;
		}

		m_spot_lights.push_back(std::move(light));
	}
	
	void Scene::AddSceneNode(SharedPtr< SpriteNode > sprite) {
		if (!sprite) {
			return;
		}

		m_sprites.push_back(std::move(sprite));
	}
}