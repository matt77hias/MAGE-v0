//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "model\model.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	Model::Model(SharedPtr< const StaticMesh > mesh)
		: Model(static_pointer_cast< const Mesh >(mesh), 
			0, mesh->GetNumberOfIndices(),
			mesh->GetAABB(), mesh->GetBS()) {}

	Model::Model(SharedPtr< const Mesh > mesh, 
		size_t start_index, size_t nb_indices,
		AABB aabb, BS bs)
		: m_mesh(std::move(mesh)), 
		m_start_index(start_index), 
		m_nb_indices(nb_indices),
		m_aabb(std::move(aabb)), 
		m_bs(std::move(bs)), 
		m_material(MakeUnique< Material >()),
		m_light_occlusion(true) {}

	Model::Model(const Model &model)
		: m_mesh(model.m_mesh), 
		m_start_index(model.m_start_index), 
		m_nb_indices(model.m_nb_indices),
		m_aabb(model.m_aabb), 
		m_bs(model.m_bs),
		m_material(MakeUnique< Material >(*model.m_material)),
		m_light_occlusion(model.m_light_occlusion) {}

	Model::Model(Model &&model) = default;

	Model::~Model() = default;

	UniquePtr< Model > Model::CloneImplementation() const {
		return MakeUnique< Model >(*this);
	}
}