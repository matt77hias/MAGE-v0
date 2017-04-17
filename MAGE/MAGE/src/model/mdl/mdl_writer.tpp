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
	HRESULT MDLWriter< VertexT >::Write() {
		// Export mesh.
		const HRESULT result_mesh = ExportMesh();
		if (FAILED(result_mesh)) {
			Error("Mesh exporting failed: %08X.", result_mesh);
			return result_mesh;
		}

		// Export materials.
		WriteMaterials();

		// Export model.
		WriteModelParts();

		return S_OK;
	}

	template < typename VertexT >
	HRESULT MDLWriter< VertexT >::ExportMesh() {
		const wstring &fname = GetFilename();
		const wstring msh_fname = mage::GetFilenameWithoutFileExtension(fname) + L".msh";
		return ExportMSHMeshToFile(msh_fname, m_model_output.vertex_buffer, m_model_output.index_buffer);
	}

	template < typename VertexT >
	void MDLWriter< VertexT >::WriteMaterials() {
		const wstring &fname = GetFilename();
		const wstring file_name = mage::GetFileName(fname);
		const wstring file_name_we = mage::GetFilenameWithoutFileExtension(file_name);
		const string mtl_name = str_convert(file_name_we) + ".mtl";

		WriteString(MAGE_MDL_TOKEN_MATERIAL_LIBRARY);
		WriteCharacter(' ');
		WriteString(mtl_name);
		WriteCharacter(' ');
		WriteCharacter('\n');
	}

	template < typename VertexT >
	void MDLWriter< VertexT >::WriteModelParts() {
		for (vector< ModelPart >::const_iterator it = m_model_output.model_parts.cbegin();
			it != m_model_output.model_parts.cend(); ++it) {

			WriteString(MAGE_MDL_TOKEN_MATERIAL_LIBRARY);
			WriteCharacter(' ');
			WriteString(it->child);
			WriteCharacter(' ');
			WriteString(it->parent);
			WriteCharacter(' ');
			WriteString(it->material);
			WriteCharacter(' ');
			WriteValue(it->start_index);
			WriteCharacter(' ');
			WriteValue(it->nb_indices);
			WriteCharacter('\n');
		}
	}
}