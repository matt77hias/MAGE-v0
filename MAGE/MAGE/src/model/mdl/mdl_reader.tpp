#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "model\mdl\mdl_tokens.hpp"
#include "mesh\msh\msh_loader.hpp"
#include "string\string_utils.hpp"
#include "logging\error.hpp"
#include "material\material_loader.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	template < typename VertexT >
	HRESULT MDLReader< VertexT >::Preprocess() {
		if (!m_model_output.vertex_buffer.empty()) {
			Error("%ls: vertex buffer must be empty.", GetFilename().c_str());
			return E_FAIL;
		}
		if (!m_model_output.index_buffer.empty()) {
			Error("%ls: index buffer must be empty.", GetFilename().c_str());
			return E_FAIL;
		}

		const HRESULT result_mesh = ImportMesh();
		if (FAILED(result_mesh)) {
			Error("Mesh importing failed: %08X.", result_mesh);
			return result_mesh;
		}

		return S_OK;
	}

	template < typename VertexT >
	HRESULT MDLReader< VertexT >::ImportMesh() {
		const wstring &fname = GetFilename();
		const wstring msh_fname = mage::GetFilenameWithoutFileExtension(fname) + L".msh";
		return ImportMSHMeshFromFile(msh_fname, m_model_output.vertex_buffer, m_model_output.index_buffer);
	}

	template < typename VertexT >
	HRESULT MDLReader< VertexT >::ReadLine(char *line) {
		m_context = nullptr;
		const char *token = strtok_s(line, GetDelimiters().c_str(), &m_context);

		if (!token || token[0] == MAGE_MDL_COMMENT_CHAR) {
			return S_OK;
		}

		if (str_equals(token, MAGE_MDL_TOKEN_SUBMODEL)) {
			ReadMDLSubModel();
		}
		else if (str_equals(token, MAGE_MDL_TOKEN_MATERIAL_LIBRARY)) {
			ReadMDLMaterialLibrary();
		}
		else {
			Warning("%ls: line %u: unsupported keyword token: %s.", GetFilename().c_str(), GetCurrentLineNumber(), token);
			return S_OK;
		}

		ReadLineRemaining();

		return S_OK;
	}

	template < typename VertexT >
	void MDLReader< VertexT >::ReadMDLSubModel() {
		ModelPart model_part;
		model_part.child       = ReadString();
		model_part.parent      = ReadString();
		model_part.material    = ReadString();
		model_part.start_index = ReadUInt32();
		model_part.nb_indices  = ReadUInt32();

		m_model_output.model_parts.push_back(model_part);
	}

	template < typename VertexT >
	void MDLReader< VertexT >::ReadMDLMaterialLibrary() {
		const wstring mtl_path = mage::GetPathName(GetFilename());
		const wstring mtl_name = str_convert(ReadString());
		const wstring mtl_fname = mage::GetFilename(mtl_path, mtl_name);

		const HRESULT result = ImportMaterialFromFile(mtl_fname, m_model_output.material_buffer);
		if (FAILED(result)) {
			Error("%ls: line %u: %ls could not be loaded.", GetFilename().c_str(), GetCurrentLineNumber(), mtl_fname.c_str());
		}
	}
}