#pragma once

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	template< typename VertexT, typename IndexT >
	ModelDescriptor::ModelDescriptor(ID3D11Device& device, 
									 ResourceManager& resource_manager,
									 wstring fname,
		const MeshDescriptor< VertexT, IndexT >& desc, bool export_as_MDL)
		: Resource< ModelDescriptor >(std::move(fname)), 
		m_mesh(device),
		m_materials(), 
		m_model_parts() {

		ModelOutput< VertexT, IndexT > buffer;
		loader::ImportModelFromFile(GetFilename(), resource_manager, buffer, desc);

		if (export_as_MDL) {
			const wstring mdl_fname 
				= mage::GetFilenameWithoutFileExtension(GetFilename()) + L".mdl";
			loader::ExportModelToFile(mdl_fname, buffer);
		}

		m_mesh = MakeShared< StaticMesh< VertexT, IndexT > >(
			               device, 
			               std::move(buffer.m_vertex_buffer), 
			               std::move(buffer.m_index_buffer));
		m_materials   = std::move(buffer.m_material_buffer);
		m_model_parts = std::move(buffer.m_model_parts);
	}

	template< typename ActionT >
	inline void ModelDescriptor::ForEachMaterial(ActionT action) const {
		for (const auto& material : m_materials) {
			action(material);
		}
	}

	template< typename ActionT >
	inline void ModelDescriptor::ForEachModelPart(ActionT action) const {
		for (const auto& model_part : m_model_parts) {
			action(model_part);
		}
	}
}