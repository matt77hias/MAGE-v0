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

	Model::Model(SharedPtr< const StaticMesh > mesh, const ShadedMaterial &material)
		: Model(static_pointer_cast< const Mesh >(mesh), 0, mesh->GetNumberOfIndices(),
			mesh->GetAABB(), mesh->GetBS(), material) {}

	Model::Model(SharedPtr< const Mesh > mesh, size_t start_index, size_t nb_indices,
		const AABB &aabb, const BS &bs, const ShadedMaterial &material)
		: m_mesh(mesh), m_start_index(start_index), m_nb_indices(nb_indices),
		m_aabb(aabb), m_bs(bs), m_material(MakeUnique< ShadedMaterial >(material)) ,
		m_cast_shadows(true) {}

	Model::Model(const Model &model)
		: m_mesh(model.m_mesh), m_start_index(model.m_start_index), m_nb_indices(model.m_nb_indices),
		m_material(MakeUnique< ShadedMaterial >(*model.m_material)),
		m_cast_shadows(model.m_cast_shadows) {}

	Model::Model(Model &&model) = default;

	Model::~Model() = default;

	UniquePtr< Model > Model::CloneImplementation() const {
		return MakeUnique< Model >(*this);
	}
}