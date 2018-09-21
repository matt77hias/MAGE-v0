#pragma once

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage::rendering {

	template< typename VertexT, typename IndexT >
	void XM_CALLCONV ModelOutput< VertexT, IndexT >
		::AddModelPart(ModelPart model_part) {

		const std::size_t start = model_part.m_start_index;
		const std::size_t end   = start + model_part.m_nb_indices;

		if (model_part.HasDefaultChild() && (start == end)) {
			return;
		}

		m_model_parts.push_back(std::move(model_part));
	}

	template< typename VertexT, typename IndexT >
	void ModelOutput< VertexT, IndexT >::ComputeBoundingVolumes() noexcept {
		for (auto& model_part : m_model_parts) {
			const std::size_t start = model_part.m_start_index;
			const std::size_t end   = start + model_part.m_nb_indices;

			// Set AABB.
			model_part.m_aabb = AABB();
			for (auto i = start; i < end; ++i) {
				const auto& vertex = m_vertex_buffer[m_index_buffer[i]];
				model_part.m_aabb = AABB::Union(model_part.m_aabb, vertex);
			}

			const auto centroid = model_part.m_aabb.Centroid();

			// Set bounding sphere.
			model_part.m_sphere = BoundingSphere(centroid);
			for (auto i = start; i < end; ++i) {
				const auto& vertex = m_vertex_buffer[m_index_buffer[i]];
				model_part.m_sphere = BoundingSphere::Union(model_part.m_sphere, vertex);
			}
		}
	}

	template< typename VertexT, typename IndexT >
	void ModelOutput< VertexT, IndexT >::NormalizeModelParts() noexcept {
		NormalizeInWorldSpace();
		NormalizeInObjectSpace();
	}

	template< typename VertexT, typename IndexT >
	void ModelOutput< VertexT, IndexT >::NormalizeInWorldSpace() noexcept {
		AABB aabb;
		for (const auto& vertex : m_vertex_buffer) {
			aabb = AABB::Union(aabb, vertex);
		}

		const auto c = aabb.Centroid();
		const auto d = aabb.Diagonal();
		const auto s = std::max(XMVectorGetX(d), 
								std::max(XMVectorGetY(d), 
										 XMVectorGetZ(d)));
		const auto inv_s = 1.0f / s;

		for (auto& vertex : m_vertex_buffer) {
			const auto p  = XMLoad(vertex.m_p);
			const auto np = (p - c) * inv_s;
			vertex.m_p = Point3(XMStore< F32x3 >(np));
		}
	}

	template< typename VertexT, typename IndexT >
	void ModelOutput< VertexT, IndexT >::NormalizeInObjectSpace() noexcept {
		for (auto& model_part : m_model_parts) {
			const std::size_t start = model_part.m_start_index;
			const std::size_t end   = start + model_part.m_nb_indices;
			std::size_t min_index   = m_vertex_buffer.size();
			std::size_t max_index   = 0u;

			// Model parts are not allowed to share vertices.
			for (auto i = start; i < end; ++i) {
				const auto index = static_cast< std::size_t >(m_index_buffer[i]);
				min_index = std::min(min_index, index);
				max_index = std::max(max_index, index);
			}

			AABB aabb;
			for (auto i = min_index; i <= max_index; ++i) {
				const auto& vertex = m_vertex_buffer[i];
				aabb = AABB::Union(aabb, vertex);
			}

			const auto c = aabb.Centroid();
			const auto d = aabb.Diagonal();
			const auto s = std::max(XMVectorGetX(d),
									std::max(XMVectorGetY(d),
											 XMVectorGetZ(d)));
			const auto inv_s = 1.0f / s;

			// Set transform.
			model_part.m_transform.SetTranslation(c);
			model_part.m_transform.SetScale(s);

			// Set AABB.
			const auto pmin = (aabb.MinPoint() - c) * inv_s;
			const auto pmax = (aabb.MaxPoint() - c) * inv_s;
			model_part.m_aabb = AABB(pmin, pmax);

			// Normalize vertices and set bounding sphere.
			model_part.m_sphere = BoundingSphere();
			for (auto i = min_index; i <= max_index; ++i) {
				auto& vertex = m_vertex_buffer[i];
				const auto p  = XMLoad(vertex.m_p);
				const auto np = (p - c) * inv_s;
				vertex.m_p = Point3(XMStore< F32x3 >(np));
				model_part.m_sphere = BoundingSphere::Union(model_part.m_sphere, vertex);
			}
		}
	}
}