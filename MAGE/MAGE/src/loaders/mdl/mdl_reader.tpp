#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "loaders\material_loader.hpp"
#include "loaders\mdl\mdl_tokens.hpp"
#include "loaders\msh\msh_loader.hpp"
#include "utils\string\string_utils.hpp"
#include "utils\exception\exception.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	template < typename VertexT >
	MDLReader< VertexT >::MDLReader(ModelOutput< VertexT > &model_output)
		: LineReader(), 
		m_model_output(model_output) {}

	template < typename VertexT >
	MDLReader< VertexT >::MDLReader(MDLReader &&reader) = default;

	template < typename VertexT >
	MDLReader< VertexT >::~MDLReader() = default;

	template < typename VertexT >
	void MDLReader< VertexT >::Preprocess() {
		ThrowIfFailed(m_model_output.m_vertex_buffer.empty(),
			"%ls: vertex buffer must be empty.", GetFilename().c_str());
		ThrowIfFailed(m_model_output.m_index_buffer.empty(),
			"%ls: index buffer must be empty.", GetFilename().c_str());

		ImportMesh();
	}

	template < typename VertexT >
	void MDLReader< VertexT >::ImportMesh() {
		const wstring msh_fname 
			= mage::GetFilenameWithoutFileExtension(GetFilename()) + L".msh";
		ImportMSHMeshFromFile(msh_fname, 
			m_model_output.m_vertex_buffer, m_model_output.m_index_buffer);
	}

	template < typename VertexT >
	void MDLReader< VertexT >::ReadLine(char *line) {
		m_context = nullptr;
		const char *token 
			= strtok_s(line, GetDelimiters().c_str(), &m_context);

		if (!token || MAGE_MDL_COMMENT_CHAR == token[0]) {
			return;
		}

		if (str_equals(token, MAGE_MDL_TOKEN_SUBMODEL)) {
			ReadMDLSubModel();
		}
		else if (str_equals(token, MAGE_MDL_TOKEN_MATERIAL_LIBRARY)) {
			ReadMDLMaterialLibrary();
		}
		else {
			Warning("%ls: line %u: unsupported keyword token: %s.", 
				GetFilename().c_str(), GetCurrentLineNumber(), token);
			return;
		}

		ReadLineRemaining();
	}

	template < typename VertexT >
	void MDLReader< VertexT >::ReadMDLSubModel() {
		ModelPart model_part;
		model_part.m_child       = ReadString();
		model_part.m_parent      = ReadString();
		model_part.m_translation = ReadF32x3();
		model_part.m_rotation    = ReadF32x3();
		model_part.m_scale       = ReadF32x3();
		model_part.m_material    = ReadString();
		model_part.m_start_index = ReadU32();
		model_part.m_nb_indices  = ReadU32();
		
		m_model_output.AddModelPart(std::move(model_part));
	}

	template < typename VertexT >
	void MDLReader< VertexT >::ReadMDLMaterialLibrary() {
		const wstring mtl_path  = mage::GetPathName(GetFilename());
		const wstring mtl_name  = str_convert(ReadString());
		const wstring mtl_fname = mage::GetFilename(mtl_path, mtl_name);

		ImportMaterialFromFile(mtl_fname, m_model_output.m_material_buffer);
	}
}