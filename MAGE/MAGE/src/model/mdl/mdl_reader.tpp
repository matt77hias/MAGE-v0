#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "model\mdl\mdl_tokens.hpp"
#include "mesh\msh\msh_loader.hpp"
#include "material\material_loader.hpp"
#include "string\string_utils.hpp"
#include "logging\exception.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	template < typename VertexT >
	MDLReader< VertexT >::MDLReader(ModelOutput< VertexT > &model_output)
		: LineReader(), m_model_output(model_output) {}

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
		string child         = ReadString();
		string parent        = ReadString();
		string material      = ReadString();
		const U32 start      = ReadU32();
		const U32 nb_indices = ReadU32();
		
		m_model_output.AddModelPart(ModelPart(std::move(child), 
			                                  std::move(parent),
			                                  start, nb_indices, 
			                                  std::move(material)));
	}

	template < typename VertexT >
	void MDLReader< VertexT >::ReadMDLMaterialLibrary() {
		const wstring mtl_path  = mage::GetPathName(GetFilename());
		const wstring mtl_name  = str_convert(ReadString());
		const wstring mtl_fname = mage::GetFilename(mtl_path, mtl_name);

		ImportMaterialFromFile(mtl_fname, m_model_output.m_material_buffer);
	}
}