//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "scene\scene.hpp"
#include "resource\model\material_factory.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	Scene::Scene(std::string name)
		: m_name(std::move(name)),
		m_nodes(),
		m_scripts() {}

	Scene::Scene(Scene&& scene) noexcept = default;

	Scene::~Scene() = default;

	Scene& Scene::operator=(Scene&& scene) noexcept = default;

	//-------------------------------------------------------------------------
	// Scene Member Methods: Lifecycle
	//-------------------------------------------------------------------------

	void Scene::Initialize(Engine& engine) {
		// Loads this scene.
		Load(engine);

		// Loads the behavior scripts of this scene.
		ForEach< BehaviorScript >([&engine](BehaviorScript& script) {
			script.Load(engine);
		});
	}

	void Scene::Uninitialize(Engine& engine) {
		// Closes the behavior scripts of this scene.
		ForEach< BehaviorScript >([&engine](BehaviorScript& script) {
			script.Close(engine);
		});

		// Closes this scene.
		Close(engine);

		engine.GetRenderingManager().GetWorld().Clear();

		// Clears this scene.
		Clear();
	}

	void Scene::Load([[maybe_unused]] Engine& engine) {}

	void Scene::Close([[maybe_unused]] Engine& engine) {}

	void Scene::Clear() noexcept {
		m_nodes.clear();
		m_scripts.clear();
	}

	//-------------------------------------------------------------------------
	// Scene Member Methods
	//-------------------------------------------------------------------------

	ProxyPtr< Node > Scene::Import(Engine& engine,
								   const rendering::ModelDescriptor& desc) {
		std::vector< ProxyPtr< Node > > nodes;
		return Import(engine, desc, nodes);
	}

	ProxyPtr< Node > Scene::Import(Engine& engine,
								   const rendering::ModelDescriptor& desc,
								   std::vector< ProxyPtr< Node > >& nodes) {

		using namespace rendering;
		using ModelPtr = ProxyPtr< Model >;
		using NodePtr  = ProxyPtr< Node >;

		NodePtr root;
		std::size_t nb_root_childs = 0u;
		std::map< std::string_view, NodePtr > mapping;
		std::size_t first_index = nodes.size();

		auto& rendering_manager = engine.GetRenderingManager();
		auto& world = rendering_manager.GetWorld();
		auto& resource_manager  = rendering_manager.GetResourceManager();
		auto default_material   = CreateDefaultMaterial(resource_manager);

		// Create the nodes with their model components.
		desc.ForEachModelPart([&](const rendering::ModelPart& model_part) {
			// Create the node.
			auto node = Create< Node >(model_part.m_child);

			// Create the model component.
			auto model = world.Create< Model >();

			// Set the mesh of the model component.
			model->SetMesh(desc.GetMesh(),
						   model_part.m_start_index,
						   model_part.m_nb_indices,
						   model_part.m_aabb,
						   model_part.m_sphere);

			// Set the material of the model component.
			const auto material = desc.GetMaterial(model_part.m_material);
			model->GetMaterial() = (material) ? *material : default_material;

			// Set the transform of the node.
			auto& transform = node->GetTransform();
			transform.SetLocalTransform(model_part.m_transform);

			// Add the model component to the node.
			node->Add(model);

			if (model_part.HasDefaultParent()) {
				root = node;
				++nb_root_childs;
			}

			// Add the node to the mapping.
			// Actual parent nodes must have a unique name.
			mapping.emplace(model_part.m_child, node);

			// Add the node to the collection to return.
			nodes.push_back(node);
		});

		// There must be at least one root node.
		ThrowIfFailed((0u != nb_root_childs),
					  "{}: no root node fount.", desc.GetGuid());

		// An additional root node needs to be created if multiple root nodes
		// are present.
		const bool create_root_model_node = (1u < nb_root_childs);
		if (create_root_model_node) {
			// Create the root node.
			root = Create< Node >("model");

			// Add the node to the collection to return.
			nodes.push_back(root);
		}

		// Connect the nodes.
		desc.ForEachModelPart([&](const rendering::ModelPart& model_part) {
			auto child = nodes[first_index++];
			if (model_part.HasDefaultParent()) {
				if (create_root_model_node) {
					root->AddChild(child);
				}
			}
			else {
				mapping[model_part.m_parent]->AddChild(child);
			}
		});

		return root;
	}
}