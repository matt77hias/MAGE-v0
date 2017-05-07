#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "model\mdl\mdl_tokens.hpp"
#include "mesh\msh\msh_loader.hpp"
#include "string\string_utils.hpp"
#include "file\file_utils.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	template < typename VertexT >
	MDLWriter< VertexT >::MDLWriter(const ModelOutput< VertexT > &model_output)
		: Writer(), m_model_output(model_output) {}

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
		const wstring msh_fname = mage::GetFilenameWithoutFileExtension(fname) + L".msh";
		ExportMSHMeshToFile(msh_fname, m_model_output.m_vertex_buffer, m_model_output.m_index_buffer);
	}

	template < typename VertexT >
	void MDLWriter< VertexT >::WriteMaterials() {
		const wstring &fname = GetFilename();
		const wstring file_name = mage::GetFileName(fname);
		const wstring file_name_we = mage::GetFilenameWithoutFileExtension(file_name);

		char output[MAX_PATH];

		sprintf_s(output, (unsigned int)_countof(output), "%s %s.mtl",
			MAGE_MDL_TOKEN_MATERIAL_LIBRARY, str_convert(file_name_we.c_str()));

		WriteStringLine(output);
	}

	template < typename VertexT >
	void MDLWriter< VertexT >::WriteModelParts() {
		
		char output[MAX_PATH];
		
		for (auto it = m_model_output.m_model_parts.cbegin(); it != m_model_output.m_model_parts.cend(); ++it) {

			sprintf_s(output, (unsigned int)_countof(output), "%s %s %s %s %u %u", 
				MAGE_MDL_TOKEN_SUBMODEL, it->m_child.c_str(), it->m_parent.c_str(), it->m_material.c_str(),
				it->m_start_index, it->m_nb_indices);
			
			WriteStringLine(output);
		}
	}
}