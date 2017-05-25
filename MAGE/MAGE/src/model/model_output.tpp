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
namespace mage {

	template < typename VertexT >
	inline void ModelOutput< VertexT >::AddModelPart(ModelPart &&model_part, bool create_bounding_volumes) {
		m_model_parts.push_back(std::move(model_part));
		
		if (create_bounding_volumes) {
			SetupBoundingVolumes(m_model_parts.back());
		}
	}

	template < typename VertexT >
	bool ModelOutput< VertexT >::HasModelPart(const string &name) noexcept {
		for (auto it = m_model_parts.cbegin(); it != m_model_parts.cend(); ++it) {
			if (it->m_child == name) {
				return true;
			}
		}
		return false;
	}

	template < typename VertexT >
	inline void ModelOutput< VertexT >::StartModelPart(const string &child, const string &parent) {
		const uint32_t start = static_cast< uint32_t >(m_index_buffer.size());
		m_model_parts.emplace_back(child, parent, start);
	}

	template < typename VertexT >
	inline void ModelOutput< VertexT >::SetMaterial(const string &material) {
		Assert(!m_model_parts.empty());

		ModelPart &current = m_model_parts.back();
		current.m_material = material;
	}

	template < typename VertexT >
	inline void ModelOutput< VertexT >::EndModelPart(bool create_bounding_volumes) noexcept {
		Assert(!m_model_parts.empty());

		ModelPart &current = m_model_parts.back();
		const uint32_t start = current.m_start_index;
		const uint32_t end = static_cast< uint32_t >(m_index_buffer.size());
		current.m_nb_indices = end - start;

		if (create_bounding_volumes) {
			SetupBoundingVolumes(current);
		}
	}

	template < typename VertexT >
	inline void ModelOutput< VertexT >::SetupBoundingVolumes(ModelPart &model_part) noexcept {
		const size_t start = model_part.m_start_index;
		const size_t end   = start + model_part.m_nb_indices;
		
		for (size_t i = start; i < end; ++i) {
			const VertexT &v = m_vertex_buffer[m_index_buffer[i]];
			model_part.m_aabb = Union(model_part.m_aabb, v);
		}

		model_part.m_bs.m_p = model_part.m_aabb.Centroid();

		for (size_t i = start; i < end; ++i) {
			const VertexT &v = m_vertex_buffer[m_index_buffer[i]];
			model_part.m_bs = Union(model_part.m_bs, v);
		}
	}
}