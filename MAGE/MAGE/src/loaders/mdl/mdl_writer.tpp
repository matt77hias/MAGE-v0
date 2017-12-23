#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "loaders\mdl\mdl_tokens.hpp"
#include "loaders\msh\msh_loader.hpp"
#include "utils\string\string_utils.hpp"
#include "utils\file\file_utils.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage::loader {

	template< typename VertexT, typename IndexT >
	MDLWriter< VertexT, IndexT >
		::MDLWriter(const ModelOutput< VertexT, IndexT > &model_output)
		: Writer(), 
		m_model_output(model_output) {}

	template< typename VertexT, typename IndexT >
	MDLWriter< VertexT, IndexT >::MDLWriter(MDLWriter &&writer) noexcept = default;

	template< typename VertexT, typename IndexT >
	MDLWriter< VertexT, IndexT >::~MDLWriter() = default;

	template< typename VertexT, typename IndexT >
	void MDLWriter< VertexT, IndexT >::Write() {
		// Export mesh.
		ExportMesh();
		// Export materials.
		WriteMaterials();
		// Export model.
		WriteModelParts();
	}

	template< typename VertexT, typename IndexT >
	void MDLWriter< VertexT, IndexT >::ExportMesh() {
		const wstring &fname = GetFilename();
		const wstring msh_fname 
			= mage::GetFilenameWithoutFileExtension(fname) + L".msh";
		ExportMSHMeshToFile(msh_fname, m_model_output.m_vertex_buffer, 
			                           m_model_output.m_index_buffer);
	}

	template< typename VertexT, typename IndexT >
	void MDLWriter< VertexT, IndexT >::WriteMaterials() {
		const wstring &fname = GetFilename();
		
		const wstring mtl_fname 
			= mage::GetFilenameWithoutFileExtension(fname) + L".mtl";
		if (!FileExists(mtl_fname)) {
			return;
		}

		const wstring file_name 
			= mage::GetFileName(fname);
		const wstring file_name_we 
			= mage::GetFilenameWithoutFileExtension(file_name);

		char output[MAX_PATH];
		sprintf_s(output, _countof(output), 
			"%s %s.mtl",
			g_mdl_token_material_library, 
			str_convert(file_name_we).c_str());

		WriteStringLine(output);
	}

	template< typename VertexT, typename IndexT >
	void MDLWriter< VertexT, IndexT >::WriteModelParts() {
		char output[MAX_PATH];

		for (const auto &model_part : m_model_output.m_model_parts) {

			sprintf_s(output, _countof(output),
				"%s %s %s %f %f %f %f %f %f %f %f %f %s %u %u",
				g_mdl_token_submodel, 
				model_part.m_child.c_str(), 
				model_part.m_parent.c_str(),
				model_part.m_translation.m_x,
				model_part.m_translation.m_y,
				model_part.m_translation.m_z,
				model_part.m_rotation.m_x,
				model_part.m_rotation.m_y,
				model_part.m_rotation.m_z,
				model_part.m_scale.m_x,
				model_part.m_scale.m_y,
				model_part.m_scale.m_z,
				model_part.m_material.c_str(),
				model_part.m_start_index, 
				model_part.m_nb_indices);
			
			WriteStringLine(output);
		}
	}
}