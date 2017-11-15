//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "scene\scene.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	Scene::Scene(string name)
		: m_name(std::move(name)), 
		m_scripts(), 
		m_cameras(), 
		m_models(), 
		m_directional_lights(), 
		m_omni_lights(), 
		m_spot_lights(), 
		m_sprites(),
		m_ambient_light(), 
		m_scene_fog(), 
		m_sky() {}

	Scene::~Scene() {
		// Clears this scene.
		Clear();
	}
	
	//-------------------------------------------------------------------------
	// Scene Member Methods: Lifecycle
	//-------------------------------------------------------------------------

	void Scene::Initialize() {
		m_scene_fog = MakeUnique< SceneFog >();
		m_sky       = MakeUnique< Sky >();

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
		m_cameras.clear();
		m_models.clear();
		m_ambient_light.reset();
		m_directional_lights.clear();
		m_omni_lights.clear();
		m_spot_lights.clear();
		m_sprites.clear();
		m_scene_fog.reset();
		m_sky.reset();
	}

	//-------------------------------------------------------------------------
	// Scene Member Methods: Scripts
	//-------------------------------------------------------------------------

	bool Scene::HasScript(SharedPtr< const BehaviorScript > script) const {
		return std::find(m_scripts.begin(), m_scripts.end(), script) 
			!= m_scripts.end();
	}
	
	void Scene::AddScript(SharedPtr< BehaviorScript > script) {
		if (!script) {
			return;
		}

		m_scripts.push_back(std::move(script));
	}
	
	void Scene::RemoveScript(SharedPtr< BehaviorScript > script) {
		if (const auto it = std::find(m_scripts.begin(), m_scripts.end(), script); 
			it != m_scripts.end()) {

			m_scripts.erase(it);
		}
	}
	
	void Scene::RemoveAllScripts() noexcept {
		m_scripts.clear();
	}

	//-------------------------------------------------------------------------
	// Scene Member Methods: World
	//-------------------------------------------------------------------------

	SharedPtr< ModelNode > Scene::CreateModel(const ModelDescriptor &desc) {

		// Create a default material.
		const Material default_material("material");

		SharedPtr< ModelNode > root_model_node;
		size_t nb_root_childs = 0;

		using ModelPair = pair< SharedPtr< ModelNode >, string >;
		map< string, ModelPair > mapping;

		// Create model nodes.
		desc.ForEachModelPart([&](const ModelPart *model_part) {

			if (MAGE_MDL_PART_DEFAULT_CHILD == model_part->m_child
				&& 0 == model_part->m_nb_indices) {
				return;
			}

			// Create a submodel node.
			const SharedPtr< ModelNode > submodel_node 
				= MakeShared< ModelNode >(model_part->m_child, desc.GetMesh(),
										  model_part->m_start_index, 
										  model_part->m_nb_indices,
										  model_part->m_aabb, model_part->m_bs);
			// Create a material.
			const Material material 
				= (MAGE_MDL_PART_DEFAULT_MATERIAL == model_part->m_material) ?
					default_material : *desc.GetMaterial(model_part->m_material);
			*(submodel_node->GetModel()->GetMaterial()) = std::move(material);

			// Add this submodel node to this scene.
			AddSceneNode(submodel_node);

			if (MAGE_MDL_PART_DEFAULT_PARENT == model_part->m_parent) {
				root_model_node = submodel_node;
				++nb_root_childs;
			}

			// Add this submodel node to the mapping.
			mapping.emplace(model_part->m_child, 
							ModelPair(submodel_node, model_part->m_parent));
		});

		Assert(0 != nb_root_childs);

		const bool create_root_model_node = (1 < nb_root_childs);

		// Create root model node.
		if (create_root_model_node) {
			root_model_node = MakeShared< ModelNode >(
				"model", desc.GetMesh(), 0, 0, AABB(), BS());
			
			// Add this root model node to this scene.
			AddSceneNode(root_model_node);
		}

		// Connect model nodes.
		for (const auto &model_pair : mapping) {
			const auto &[child, parent] = model_pair.second;
			if (MAGE_MDL_PART_DEFAULT_PARENT == parent) {
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