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

	Model::Model(SharedPtr< const Mesh > mesh, 
		         size_t start_index, 
		         size_t nb_indices,
		         const AABB &aabb, 
		         const BoundingSphere &bs) 
		: Component(),
		m_aabb(aabb),
		m_sphere(bs),
		m_mesh(std::move(mesh)), 
		m_start_index(start_index), 
		m_nb_indices(nb_indices),
		m_texture_transform(),
		m_material(),
		m_light_occlusion(true) {}

	Model::Model(const Model &model) = default;

	Model::Model(Model &&model) noexcept = default;

	Model::~Model() = default;

	Model &Model::operator=(Model &&model) noexcept = default;
}