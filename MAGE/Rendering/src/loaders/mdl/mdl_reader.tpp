#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "loaders\material_loader.hpp"
#include "loaders\mdl\mdl_tokens.hpp"
#include "loaders\msh\msh_loader.hpp"
#include "string\string_utils.hpp"
#include "exception\exception.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage::loader {

	template< typename VertexT, typename IndexT >
	MDLReader< VertexT, IndexT >
		::MDLReader(ResourceManager& resource_manager, 
					ModelOutput< VertexT, IndexT >& model_output)
		: LineReader(), 
		m_resource_manager(resource_manager),
		m_model_output(model_output) {}

	template< typename VertexT, typename IndexT >
	MDLReader< VertexT, IndexT >::MDLReader(MDLReader&& reader) noexcept = default;

	template< typename VertexT, typename IndexT >
	MDLReader< VertexT, IndexT >::~MDLReader() = default;

	template< typename VertexT, typename IndexT >
	void MDLReader< VertexT, IndexT >::Preprocess() {
		ThrowIfFailed(m_model_output.m_vertex_buffer.empty(), 
					  "%ls: vertex buffer must be empty.", 
					  GetFilename().c_str());
		ThrowIfFailed(m_model_output.m_index_buffer.empty(), 
					  "%ls: index buffer must be empty.", 
					  GetFilename().c_str());

		ImportMesh();
	}

	template< typename VertexT, typename IndexT >
	void MDLReader< VertexT, IndexT >::ImportMesh() {
		const auto msh_fname
			= mage::GetFilenameWithoutFileExtension(GetFilename()) + L".msh";
		ImportMSHMeshFromFile(msh_fname, m_model_output.m_vertex_buffer, 
			                             m_model_output.m_index_buffer);
	}

	template< typename VertexT, typename IndexT >
	void MDLReader< VertexT, IndexT >::ReadLine(NotNull< zstring > line) {
		m_context = nullptr;
		const auto* const token
			= strtok_s(line, GetDelimiters().c_str(),& m_context);

		if (!token || g_mdl_token_comment == token[0]) {
			return;
		}

		if (str_equals(token, g_mdl_token_submodel)) {
			ReadMDLSubModel();
		}
		else if (str_equals(token, g_mdl_token_material_library)) {
			ReadMDLMaterialLibrary();
		}
		else {
			Warning("%ls: line %u: unsupported keyword token: %s.", 
				    GetFilename().c_str(), GetCurrentLineNumber(), token);
			return;
		}

		ReadLineRemaining();
	}

	template< typename VertexT, typename IndexT >
	void MDLReader< VertexT, IndexT >::ReadMDLSubModel() {
		ModelPart model_part;
		model_part.m_child       = Read< string >();
		model_part.m_parent      = Read< string >();
		model_part.m_transform.SetTranslation(Read< F32x3 >());
		model_part.m_transform.SetRotation(   Read< F32x3 >());
		model_part.m_transform.SetScale(      Read< F32x3 >());
		model_part.m_material    = Read< string >();
		model_part.m_start_index = Read< U32 >();
		model_part.m_nb_indices  = Read< U32 >();
		
		m_model_output.AddModelPart(std::move(model_part));
	}

	template< typename VertexT, typename IndexT >
	void MDLReader< VertexT, IndexT >::ReadMDLMaterialLibrary() {
		const auto mtl_path  = mage::GetPathName(GetFilename());
		const auto mtl_name  = str_convert(Read< string >());
		const auto mtl_fname = mage::GetFilename(mtl_path, mtl_name);

		ImportMaterialFromFile(mtl_fname, 
							   m_resource_manager, 
							   m_model_output.m_material_buffer);
	}
}