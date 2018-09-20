#pragma once

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage::rendering {

	template< typename VertexT, typename IndexT >
	void XM_CALLCONV ModelOutput< VertexT, IndexT >
		::AddModelPart(ModelPart model_part, bool normalize) {

		const std::size_t start = model_part.m_start_index;
		const std::size_t end   = start + model_part.m_nb_indices;

		if (model_part.HasDefaultChild() && (start == end)) {
			return;
		}

		for (auto i = start; i < end; ++i) {
			const auto& v = m_vertex_buffer[m_index_buffer[i]];
			model_part.m_aabb = AABB::Union(model_part.m_aabb, v);
		}

		if (normalize) {
			const auto c = model_part.m_aabb.Centroid();
			const auto d = model_part.m_aabb.Diagonal();
			const auto s = std::max(XMVectorGetX(d),
									std::max(XMVectorGetY(d), 
											 XMVectorGetZ(d)));
			const auto inv_s = 1.0f / s;

			// Set transform.
			model_part.m_transform.SetTranslation(c);
			model_part.m_transform.SetScale(s);
			
			// Set AABB.
			const auto pmin = (model_part.m_aabb.MinPoint() - c) * inv_s;
			const auto pmax = (model_part.m_aabb.MaxPoint() - c) * inv_s;
			model_part.m_aabb = AABB(pmin, pmax);

			// Normalize vertices and set bounding sphere.
			for (auto i = start; i < end; ++i) {
				auto& v = m_vertex_buffer[m_index_buffer[i]];
				const auto p  = XMLoad(v.m_p);
				const auto np = (p - c) * inv_s;
				v.m_p = Point3(XMStore< F32x3 >(np));
				model_part.m_sphere = BoundingSphere::Union(model_part.m_sphere, v);
			}
		} 
		else {

			// Set bounding sphere.
			const auto c = model_part.m_aabb.Centroid();
			model_part.m_sphere = BoundingSphere(c);
			for (auto i = start; i < end; ++i) {
				const auto& v = m_vertex_buffer[m_index_buffer[i]];
				model_part.m_sphere = BoundingSphere::Union(model_part.m_sphere, v);
			}
		}

		m_model_parts.push_back(std::move(model_part));
	}
}