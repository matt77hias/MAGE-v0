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

	Model::Model(SharedPtr< const Mesh > mesh,
		size_t start_index, size_t nb_indices, const ShadedMaterial &material)
		: m_mesh(mesh), m_start_index(start_index), m_nb_indices(nb_indices),
		m_material(std::make_unique< ShadedMaterial >(material)) {}

	Model::Model(const Model &model)
		: m_mesh(model.m_mesh), m_start_index(model.m_start_index), m_nb_indices(model.m_nb_indices),
		m_material(std::make_unique<  ShadedMaterial >(*model.m_material)) {}

	Model::Model(Model &&model) = default;

	Model::~Model() = default;

	UniquePtr< Model > Model::CloneImplementation() const {
		return std::make_unique< Model >(*this);
	}
}