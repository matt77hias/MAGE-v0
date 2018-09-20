#pragma once

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage::rendering {

	template< typename VertexT, typename IndexT >
	void XM_CALLCONV ModelOutput< VertexT, IndexT >
		::AddModelPart(ModelPart model_part, bool normalize) {

		const std::size_t min_index = model_part.m_min_index;
		const std::size_t max_index = model_part.m_max_index;

		if (model_part.HasDefaultChild() && (min_index == max_index)) {
			return;
		}

		for (auto i = min_index; i <= max_index; ++i) {
			const auto& v = m_vertex_buffer[m_index_buffer[i]];
			model_part.m_aabb = AABB::Union(model_part.m_aabb, v);
		}

		if (!normalize) {
			const auto centroid = model_part.m_aabb.Centroid();
			model_part.m_sphere = BoundingSphere(centroid);

			for (auto i = min_index; i <= max_index; ++i) {
				const auto& v = m_vertex_buffer[m_index_buffer[i]];
				model_part.m_sphere = BoundingSphere::Union(model_part.m_sphere, v);
			}

			m_model_parts.push_back(std::move(model_part));
			return;
		}

		const auto centroid  = model_part.m_aabb.Centroid();
		const auto diagonal  = model_part.m_aabb.Diagonal();
		const auto control   = XMVectorEqual(diagonal, XMVectorZero());
		const auto scale     = XMVectorSelect(diagonal, XMVectorReplicate(1.0f), control);
		const auto inv_scale = XMVectorReciprocal(scale);

		model_part.m_transform.SetTranslation(centroid);
		model_part.m_transform.SetScale(scale);

		const auto p_min    = XMVectorSelect(XMVectorReplicate(-0.5f), XMVectorZero(), control);
		const auto p_max    = XMVectorSelect(XMVectorReplicate( 0.5f), XMVectorZero(), control);
		model_part.m_aabb   = { p_min, p_max };
		model_part.m_sphere = BoundingSphere(centroid);

		for (auto i = min_index; i <= max_index; ++i) {
			auto& v = m_vertex_buffer[m_index_buffer[i]];
			const auto p  = XMLoad(v.m_p);
			const auto np = (p - centroid) * inv_scale;
			v.m_p = Point3(XMStore< F32x3 >(np));
			model_part.m_sphere = BoundingSphere::Union(model_part.m_sphere, v);
		}

		m_model_parts.push_back(std::move(model_part));
	}
}