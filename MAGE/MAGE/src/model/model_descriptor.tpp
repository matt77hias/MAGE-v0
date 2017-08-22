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
	ModelDescriptor::ModelDescriptor(const wstring &fname, 
		const MeshDescriptor< VertexT > &desc, bool export_as_MDL)
		: ModelDescriptor(fname, GetRenderingDevice(), 
			GetRenderingDeviceContext(), desc, export_as_MDL) {}

	template < typename VertexT >
	ModelDescriptor::ModelDescriptor(const wstring &fname, 
		ID3D11Device2 *device, ID3D11DeviceContext2 *device_context,
		const MeshDescriptor< VertexT > &desc, bool export_as_MDL)
		: Resource< ModelDescriptor >(fname), m_mesh(), m_materials(), m_model_parts() {

		ModelOutput< VertexT > buffer;
		ImportModelFromFile(fname, buffer, desc);

		if (export_as_MDL) {
			const wstring mdl_fname = mage::GetFilenameWithoutFileExtension(fname) + L".mdl";
			ExportModelToFile(mdl_fname, buffer);
		}

		m_mesh = MakeShared< StaticMesh >(device, device_context, buffer.m_vertex_buffer, buffer.m_index_buffer, DXGI_FORMAT_R32_UINT);
		m_materials = std::move(buffer.m_material_buffer);
		m_model_parts = std::move(buffer.m_model_parts);
	}

	template< typename ActionT >
	inline void ModelDescriptor::ForEachMaterial(ActionT action) const {
		for (const auto &material : m_materials) {
			action(&material);
		}
	}

	template< typename ActionT >
	inline void ModelDescriptor::ForEachModelPart(ActionT action) const {
		for (const auto &model_part : m_model_parts) {
			action(&model_part);
		}
	}
}