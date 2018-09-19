#pragma once

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage::rendering {

	template< typename VertexT, typename IndexT >
	void ModelOutput< VertexT, IndexT >
		::AddModelPart(ModelPart model_part) {
		
		const std::size_t start = model_part.m_start_index;
		const std::size_t end   = start + model_part.m_nb_indices;

		// Set the AABB.
		for (auto i = start; i < end; ++i) {
			const auto& v = m_vertex_buffer[m_index_buffer[i]];
			model_part.m_aabb = AABB::Union(model_part.m_aabb, v);
		}

		// Set the bounding sphere.
		model_part.m_sphere = BoundingSphere(model_part.m_aabb.Centroid());
		for (auto i = start; i < end; ++i) {
			const auto& v = m_vertex_buffer[m_index_buffer[i]];
			model_part.m_sphere = BoundingSphere::Union(model_part.m_sphere, v);
		}

		m_model_parts.push_back(std::move(model_part));
	}

	template< typename VertexT, typename IndexT >
	[[nodiscard]]
	bool ModelOutput< VertexT, IndexT >
		::ContainsModelPart(std::string_view name) noexcept {
		
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
		::SetMaterial(std::string material) {
		
		using std::empty;
		Assert(!empty(m_model_parts));

		auto& current = m_model_parts.back();
		current.m_material = std::move(material);
	}

	template< typename VertexT, typename IndexT >
	void ModelOutput< VertexT, IndexT >
		::EndModelPart() noexcept {
		
		using std::empty;
		Assert(!empty(m_model_parts));

		auto& current        = m_model_parts.back();
		const auto start     = current.m_start_index;
		const auto end       = static_cast< U32 >(m_index_buffer.size());
		current.m_nb_indices = end - start;

		if (current.HasDefaultChild() && (0u == current.m_nb_indices)) {
			m_model_parts.pop_back();
			return;
		}

		NormalizeModelPart(current);
	}

	template< typename VertexT, typename IndexT >
	void ModelOutput< VertexT, IndexT >
		::NormalizeModelPart(ModelPart& model_part) noexcept {
		
		const std::size_t start = model_part.m_start_index;
		const std::size_t end   = start + model_part.m_nb_indices;
		
		AABB aabb;
		for (auto i = start; i < end; ++i) {
			const auto& v = m_vertex_buffer[m_index_buffer[i]];
			aabb = AABB::Union(aabb, v);
		}

		const auto centroid  = aabb.Centroid();
		const auto diagonal  = aabb.Diagonal();
		const auto control   = XMVectorEqual(diagonal, XMVectorZero());
		const auto scale     = XMVectorSelect(diagonal, XMVectorReplicate(1.0f), control);
		const auto inv_scale = XMVectorReciprocal(scale);

		// Set the AABB.
		const auto p_min  = XMVectorSelect(XMVectorReplicate(-0.5f), XMVectorZero(), control);
		const auto p_max  = XMVectorSelect(XMVectorReplicate( 0.5f), XMVectorZero(), control);
		model_part.m_aabb = { p_min, p_max };

		// Set the transform.
		model_part.m_transform.SetTranslation(centroid);
		model_part.m_transform.SetScale(scale);

		// Normalize the vertex positions.
		for (auto i = start; i < end; ++i) {
			auto& v = m_vertex_buffer[m_index_buffer[i]];
			const auto p  = XMLoad(v.m_p);
			const auto np = (p - centroid) * inv_scale;
			v.m_p = Point3(XMStore< F32x3 >(np));
		}

		// Set the bounding sphere.
		model_part.m_sphere = BoundingSphere(model_part.m_aabb.Centroid());
		for (auto i = start; i < end; ++i) {
			const auto& v = m_vertex_buffer[m_index_buffer[i]];
			model_part.m_sphere = BoundingSphere::Union(model_part.m_sphere, v);
		}
	}
}