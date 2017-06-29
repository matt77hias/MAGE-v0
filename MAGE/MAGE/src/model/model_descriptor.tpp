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
	ModelDescriptor::ModelDescriptor(const wstring &fname, const MeshDescriptor< VertexT > &desc)
		: ModelDescriptor(GetRenderingDevice(), GetRenderingDeviceContext(), fname, desc) {}

	template < typename VertexT >
	ModelDescriptor::ModelDescriptor(ID3D11Device2 *device, ID3D11DeviceContext2 *device_context,
		const wstring &fname, const MeshDescriptor< VertexT > &desc)
		: Resource< ModelDescriptor >(fname, fname), m_mesh(), m_materials(), m_model_parts() {

		ModelOutput< VertexT > buffer;
		ImportModelFromFile(fname, buffer, desc);

		//ExportModelToFile(L"assets/models/model/model.mdl", buffer);

		m_mesh = std::make_shared< StaticMesh >(device, device_context, buffer.m_vertex_buffer, buffer.m_index_buffer, DXGI_FORMAT_R32_UINT);
		m_materials = std::move(buffer.m_material_buffer);
		m_model_parts = std::move(buffer.m_model_parts);
	}

	template< typename ActionT >
	inline void ModelDescriptor::ForEachMaterial(ActionT action) const {
		for (auto it = m_materials.cbegin(); it != m_materials.cend(); ++it) {
			action(*it);
		}
	}

	template< typename ActionT >
	inline void ModelDescriptor::ForEachModelPart(ActionT action) const {
		for (auto it = m_model_parts.cbegin(); it != m_model_parts.cend(); ++it) {
			action(*it);
		}
	}
}