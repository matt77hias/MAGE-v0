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
		m_buffer(), 
		m_aabb(aabb),
		m_sphere(bs),
		m_mesh(std::move(mesh)), 
		m_start_index(start_index), 
		m_nb_indices(nb_indices),
		m_texture_transform(),
		m_material(),
		m_light_occlusion(true) {}

	Model::Model(const Model &model) 
		: Component(model),
		m_buffer(),
		m_aabb(model.m_aabb),
		m_sphere(model.m_sphere),
		m_mesh(model.m_mesh),
		m_start_index(model.m_start_index),
		m_nb_indices(model.m_nb_indices),
		m_texture_transform(model.m_texture_transform),
		m_material(model.m_material),
		m_light_occlusion(model.m_light_occlusion) {}

	Model::Model(Model &&model) noexcept = default;

	Model::~Model() = default;

	Model &Model::operator=(const Model &model) {
		Component::operator=(model);

		m_buffer            = ConstantBuffer< ModelBuffer >();
		m_aabb              = model.m_aabb;
		m_sphere            = model.m_sphere;
		m_mesh              = model.m_mesh;
		m_start_index       = model.m_start_index;
		m_nb_indices        = model.m_nb_indices;
		m_texture_transform = model.m_texture_transform;
		m_material          = model.m_material;
		m_light_occlusion   = model.m_light_occlusion;

		return *this;
	}

	Model &Model::operator=(Model &&model) noexcept = default;

	void Model::UpdateBuffer(ID3D11DeviceContext *device_context) const {
		const auto &transform        = GetOwner()->GetTransform();
		const auto object_to_world   = transform.GetObjectToWorldMatrix();
		const auto world_to_object   = transform.GetWorldToObjectMatrix();
		const auto texture_transform = m_texture_transform.GetTransformMatrix();

		ModelBuffer buffer;
		// Transforms
		buffer.m_object_to_world     = XMMatrixTranspose(object_to_world);
		buffer.m_normal_to_world     = world_to_object;
		buffer.m_texture_transform   = XMMatrixTranspose(texture_transform);
		// Material
		buffer.m_base_color          = RGBA(m_material.GetBaseColor());
		buffer.m_roughness           = m_material.GetRoughness();
		buffer.m_metalness           = m_material.GetMetalness();

		// Update the model buffer.
		m_buffer.UpdateData(device_context, buffer);
	}
}