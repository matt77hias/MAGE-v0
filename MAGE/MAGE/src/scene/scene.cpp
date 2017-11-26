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

	Scene::~Scene() = default;
	
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
		m_scripts.clear();
		m_cameras.clear();
		m_models.clear();
		m_directional_lights.clear();
		m_omni_lights.clear();
		m_spot_lights.clear();
		m_sprites.clear();
		m_ambient_light.reset();
		m_scene_fog.reset();
		m_sky.reset();
	}

	//-------------------------------------------------------------------------
	// Scene Member Methods
	//-------------------------------------------------------------------------

	ModelNode *Scene::CreateModel(const ModelDescriptor &desc) {
		vector< ModelNode * > models;
		return CreateModel(desc, models);
	}

	ModelNode *Scene::CreateModel(const ModelDescriptor &desc, 
		vector< ModelNode * > &models) {

		// Create a default material.
		const Material default_material("material");

		ModelNode *root = nullptr;
		size_t nb_root_childs = 0;

		using ModelPair = pair< ModelNode * , string >;
		map< string, ModelPair > mapping;

		// Create model nodes.
		desc.ForEachModelPart([&](const ModelPart *model_part) {

			if (model_part->HasDefaultChild() && (0 == model_part->m_nb_indices)) {
				return;
			}

			// Create a submodel node.
			UniquePtr< ModelNode > node = MakeUnique< ModelNode >(
				                              model_part->m_child, 
				                              desc.GetMesh(),
										      model_part->m_start_index, 
										      model_part->m_nb_indices,
										      model_part->m_aabb, 
					                          model_part->m_bs);
			
			TransformNode * const transform = node->GetTransform();
			transform->SetTranslation(model_part->m_translation);
			transform->SetRotation(model_part->m_rotation);
			transform->SetScale(model_part->m_scale);

			// Create a material.
			if (model_part->HasDefaultMaterial()) {
				*(node->GetModel()->GetMaterial()) = default_material;
			}
			else {
				*(node->GetModel()->GetMaterial()) = *(desc.GetMaterial(model_part->m_material));
			}

			// Add the submodel node to this scene.
			ModelNode * const ptr = node.get();
			models.push_back(ptr);
			m_models.push_back(std::move(node));

			if (model_part->HasDefaultParent()) {
				root = ptr;
				++nb_root_childs;
			}

			// Add the submodel node to the mapping.
			mapping.emplace(model_part->m_child, 
							ModelPair(ptr, model_part->m_parent));
		});

		Assert(0 != nb_root_childs);

		const bool create_root_model_node = (1 < nb_root_childs);
		if (create_root_model_node) {
			// Create root model node.
			UniquePtr< ModelNode > node = MakeUnique< ModelNode >(
				"model", desc.GetMesh(), 0, 0, AABB(), BS());
			
			// Add the root model node to this scene.
			root = node.get();
			models.push_back(root);
			m_models.push_back(std::move(node));
		}

		// Connect model nodes.
		for (const auto &model_pair : mapping) {
			const auto &[child, parent] = model_pair.second;
			if (MAGE_MDL_PART_DEFAULT_PARENT == parent) {
				if (create_root_model_node) {
					root->AddChildNode(child);
				}
			}
			else {
				mapping[parent].first->AddChildNode(child);
			}
		}

		return root;
	}
}