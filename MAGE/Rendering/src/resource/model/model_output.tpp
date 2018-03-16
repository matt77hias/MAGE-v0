#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "logging\error.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage::rendering {

	template< typename VertexT, typename IndexT >
	void ModelOutput< VertexT, IndexT >
		::AddModelPart(ModelPart model_part, bool create_bounding_volumes) {
		
		m_model_parts.push_back(std::move(model_part));
		
		if (create_bounding_volumes) {
			SetupBoundingVolumes(m_model_parts.back());
		}
	}

	template< typename VertexT, typename IndexT >
	[[nodiscard]]
	bool ModelOutput< VertexT, IndexT >
		::ContainsModelPart(const string& name) noexcept {
		
		for (const auto& model_part : m_model_parts) {
			if (name == model_part.m_child) {
				return true;
			}
		}

		return false;
	}

	template< typename VertexT, typename IndexT >
	void ModelOutput< VertexT, IndexT >
		::StartModelPart(ModelPart model_part) {
		
		model_part.m_start_index = static_cast< U32 >(m_index_buffer.size());
		
		m_model_parts.push_back(std::move(model_part));
	}

	template< typename VertexT, typename IndexT >
	void ModelOutput< VertexT, IndexT >
		::SetMaterial(string material) {
		
		Assert(!m_model_parts.empty());

		auto& current = m_model_parts.back();
		current.m_material = std::move(material);
	}

	template< typename VertexT, typename IndexT >
	void ModelOutput< VertexT, IndexT >
		::EndModelPart(bool create_bounding_volumes) noexcept {
		
		Assert(!m_model_parts.empty());

		auto& current        = m_model_parts.back();
		const auto start     = current.m_start_index;
		const auto end       = static_cast< U32 >(m_index_buffer.size());
		current.m_nb_indices = end - start;

		if (current.HasDefaultChild() && (0u == current.m_nb_indices)) {
			m_model_parts.clear();
			return;
		}

		if (create_bounding_volumes) {
			SetupBoundingVolumes(current);
		}
	}

	template< typename VertexT, typename IndexT >
	void ModelOutput< VertexT, IndexT >
		::SetupBoundingVolumes(ModelPart& model_part) noexcept {
		
		const size_t start = model_part.m_start_index;
		const size_t end   = start + model_part.m_nb_indices;
		
		for (auto i = start; i < end; ++i) {
			const auto& v = m_vertex_buffer[m_index_buffer[i]];
			model_part.m_aabb = AABB::Union(model_part.m_aabb, v);
		}

		model_part.m_sphere = BoundingSphere(model_part.m_aabb.Centroid());

		for (auto i = start; i < end; ++i) {
			const auto& v = m_vertex_buffer[m_index_buffer[i]];
			model_part.m_sphere = BoundingSphere::Union(model_part.m_sphere, v);
		}
	}
}