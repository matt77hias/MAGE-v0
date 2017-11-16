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
namespace mage {

	template < typename VertexT >
	MDLWriter< VertexT >::MDLWriter(const ModelOutput< VertexT > &model_output)
		: Writer(), 
		m_model_output(model_output) {}

	template < typename VertexT >
	MDLWriter< VertexT >::MDLWriter(MDLWriter &&writer) = default;

	template < typename VertexT >
	MDLWriter< VertexT >::~MDLWriter() = default;

	template < typename VertexT >
	void MDLWriter< VertexT >::Write() {
		// Export mesh.
		ExportMesh();
		// Export materials.
		WriteMaterials();
		// Export model.
		WriteModelParts();
	}

	template < typename VertexT >
	void MDLWriter< VertexT >::ExportMesh() {
		const wstring &fname = GetFilename();
		const wstring msh_fname 
			= mage::GetFilenameWithoutFileExtension(fname) + L".msh";
		ExportMSHMeshToFile(msh_fname, 
			m_model_output.m_vertex_buffer, m_model_output.m_index_buffer);
	}

	template < typename VertexT >
	void MDLWriter< VertexT >::WriteMaterials() {
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
		const size_t output_count = static_cast< size_t >(_countof(output));

		const string temp = str_convert(file_name_we);

		sprintf_s(output, output_count, "%s %s.mtl",
			MAGE_MDL_TOKEN_MATERIAL_LIBRARY, str_convert(file_name_we).c_str());

		WriteStringLine(output);
	}

	template < typename VertexT >
	void MDLWriter< VertexT >::WriteModelParts() {
		
		char output[MAX_PATH];
		const size_t output_count = static_cast< size_t >(_countof(output));
		
		for (const auto &model_part : m_model_output.m_model_parts) {

			sprintf_s(output, output_count, "%s %s %s %s %u %u",
				MAGE_MDL_TOKEN_SUBMODEL, model_part.m_child.c_str(), 
				model_part.m_parent.c_str(), model_part.m_material.c_str(),
				model_part.m_start_index, model_part.m_nb_indices);
			
			WriteStringLine(output);
		}
	}
}