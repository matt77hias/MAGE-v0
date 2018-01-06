//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "scene\scene.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// System Includes
//-----------------------------------------------------------------------------
#pragma region

#include <map>

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	Scene::Scene(string name)
		: m_name(std::move(name)),
		m_nodes(),
		m_perspective_cameras(),
		m_orthographic_cameras(),
		m_ambient_lights(),
		m_directional_lights(),
		m_omni_lights(),
		m_spot_lights(),
		m_models(),
		m_sprite_images(),
		m_sprite_texts(),
		m_scripts() {}

	Scene::Scene(Scene &&scene) noexcept = default;

	Scene::~Scene() = default;

	Scene &Scene::operator=(Scene &&scene) noexcept = default;
	
	//-------------------------------------------------------------------------
	// Scene Member Methods: Lifecycle
	//-------------------------------------------------------------------------

	void Scene::Initialize() {
		// Loads this scene.
		Load();

		// Loads the behavior scripts of this scene.
		ForEach< BehaviorScript >([](BehaviorScript &script) {
			script.Load();
		});
	}
	
	void Scene::Uninitialize() {
		// Closes the behavior scripts of this scene.
		ForEach< BehaviorScript >([](BehaviorScript &script) {
			script.Close();
		});
		
		// Closes this scene.
		Close();

		// Clears this scene.
		Clear();
	}

	void Scene::Load() {}
	
	void Scene::Close() {}

	void Scene::Clear() noexcept {
		m_nodes.clear();
		m_perspective_cameras.clear();
		m_orthographic_cameras.clear();
		m_ambient_lights.clear();
		m_directional_lights.clear();
		m_omni_lights.clear();
		m_spot_lights.clear();
		m_models.clear();
		m_sprite_images.clear();
		m_sprite_texts.clear();
		m_scripts.clear();
	}

	//-------------------------------------------------------------------------
	// Scene Member Methods
	//-------------------------------------------------------------------------

	ProxyPtr< Node > Scene::Import(const ModelDescriptor &desc) {
		std::vector< ProxyPtr< Node > > nodes;
		return Import(desc, nodes);
	}

	ProxyPtr< Node > Scene::Import(const ModelDescriptor &desc, 
		std::vector< ProxyPtr< Node > > &nodes) {

		using ModelPtr = ProxyPtr< Model >;
		using NodePtr  = ProxyPtr< Node >;
		using NodePair = std::pair< NodePtr, string >;
		
		std::map< string, NodePair > mapping;
		NodePtr root;
		size_t nb_root_childs = 0;

		// Create the nodes with their model components.
		desc.ForEachModelPart([&](const ModelPart &model_part) {
			// Create the node.
			NodePtr node = Create< Node >(model_part.m_child);
			
			// Create the model component.
			const ModelPtr model = Create< Model >(desc.GetMesh(),
				                                   model_part.m_start_index,
				                                   model_part.m_nb_indices,
				                                   model_part.m_aabb,
				                                   model_part.m_bs);
			
			// Set the material of the model component.
			if (!model_part.HasDefaultMaterial()) {
				const Material * const material 
					= desc.GetMaterial(model_part.m_material);
				ThrowIfFailed((nullptr != material),
					"%ls: material '%s' not found.",
					desc.GetGuid().c_str(), model_part.m_material.c_str());
				
				model->GetMaterial() = *material;
			}

			// Set the transform of the node.
			Transform &transform = node->GetTransform();
			transform.SetLocalTransform(model_part.m_transform);

			// Add the model component to the node.
			node->AddComponent(model);

			if (model_part.HasDefaultParent()) {
				root = node;
				++nb_root_childs;
			}

			// Add the node to the mapping.
			mapping.emplace(model_part.m_child, 
							NodePair(node, model_part.m_parent));
			
			// Add the node to the collection to return.
			nodes.push_back(std::move(node));
		});

		// There must be at least one root node.
		ThrowIfFailed((0 != nb_root_childs),
			"%ls: no root node fount.",
			desc.GetGuid().c_str());

		// An additional root node needs to be created if multiple root nodes 
		// are present.
		const bool create_root_model_node = (1 < nb_root_childs);
		if (create_root_model_node) {
			// Create the root node.
			root = Create< Node >("model");
			
			// Add the node to the collection to return.
			nodes.push_back(root);
		}

		// Connect the nodes.
		for (const auto &model_pair : mapping) {
			const auto &[child, parent] = model_pair.second;
			if (MAGE_MDL_PART_DEFAULT_PARENT == parent) {
				if (create_root_model_node) {
					root->AddChild(child);
				}
			}
			else {
				mapping[parent].first->AddChild(child);
			}
		}

		return root;
	}
}