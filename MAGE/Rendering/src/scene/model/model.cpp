//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "scene\node.hpp"
#include "scene\model\model.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage::rendering {

	Model::Model(ID3D11Device& device) 
		: Component(),
		m_buffer(device),
		m_aabb(),
		m_sphere(),
		m_mesh(), 
		m_start_index(0u), 
		m_nb_indices(0u),
		m_texture_transform(),
		m_material(),
		m_light_occlusion(true) {}

	Model::Model(Model&& model) noexcept = default;

	Model::~Model() = default;

	Model& Model::operator=(Model&& model) noexcept = default;

	void Model::SetMesh(SharedPtr< const Mesh > mesh, 
						size_t start_index,
						size_t nb_indices, 
						AABB aabb, 
						BoundingSphere bs) {

		m_aabb        = std::move(aabb);
		m_sphere      = std::move(bs);
		m_mesh        = std::move(mesh);
		m_start_index = start_index;
		m_nb_indices  = nb_indices;
	}

	void Model::UpdateBuffer(ID3D11DeviceContext& device_context) const {
		Assert(HasOwner());
		
		const auto& transform         = GetOwner()->GetTransform();
		const auto  object_to_world   = transform.GetObjectToWorldMatrix();
		const auto  world_to_object   = transform.GetWorldToObjectMatrix();
		const auto  texture_transform = m_texture_transform.GetTransformMatrix();

		ModelBuffer buffer;
		// Transforms
		buffer.m_object_to_world      = XMMatrixTranspose(object_to_world);
		buffer.m_normal_to_world      = world_to_object;
		buffer.m_texture_transform    = XMMatrixTranspose(texture_transform);
		// Material
		buffer.m_base_color           = RGBA(m_material.GetBaseColor());
		buffer.m_roughness            = m_material.GetRoughness();
		buffer.m_metalness            = m_material.GetMetalness();

		// Update the model buffer.
		m_buffer.UpdateData(device_context, buffer);
	}
}