#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "mesh\obj\obj_tokens.hpp"
#include "mesh\vertex.hpp"
#include "string\string_utils.hpp"
#include "logging\exception.hpp"
#include "material\material_loader.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	template < typename VertexT >
	OBJReader< VertexT >::OBJReader(
		ModelOutput< VertexT > &model_output,
		const MeshDescriptor< VertexT > &mesh_desc)
		: LineReader(),
		m_vertex_coordinates(), m_vertex_texture_coordinates(),
		m_vertex_normal_coordinates(), m_mapping(),
		m_model_output(model_output), m_mesh_desc(mesh_desc) {}

	template < typename VertexT >
	OBJReader< VertexT >::OBJReader(OBJReader &&reader) = default;

	template < typename VertexT >
	OBJReader< VertexT >::~OBJReader() = default;

	template < typename VertexT >
	void OBJReader< VertexT >::Preprocess() {
		if (!m_model_output.m_vertex_buffer.empty()) {
			throw FormattedException("%ls: vertex buffer must be empty.", GetFilename().c_str());
		}
		if (!m_model_output.m_index_buffer.empty()) {
			throw FormattedException("%ls: index buffer must be empty.", GetFilename().c_str());
		}

		// Begin current group.
		m_model_output.StartModelPart(MAGE_MDL_PART_DEFAULT_CHILD);
	}

	template < typename VertexT >
	void OBJReader< VertexT >::Postprocess() {
		// End current group.
		m_model_output.EndModelPart();
	}

	template < typename VertexT >
	void OBJReader< VertexT >::ReadLine(char *line) {
		m_context = nullptr;
		const char *token = strtok_s(line, GetDelimiters().c_str(), &m_context);

		if (!token || token[0] == MAGE_OBJ_COMMENT_CHAR) {
			return;
		}

		if (str_equals(token, MAGE_OBJ_TOKEN_VERTEX)) {
			ReadOBJVertex();
		}
		else if (str_equals(token, MAGE_OBJ_TOKEN_TEXTURE)) {
			ReadOBJVertexTexture();
		}
		else if (str_equals(token, MAGE_OBJ_TOKEN_NORMAL)) {
			ReadOBJVertexNormal();
		}
		else if (str_equals(token, MAGE_OBJ_TOKEN_FACE)) {
			ReadOBJFace();
		}
		else if (str_equals(token, MAGE_OBJ_TOKEN_MATERIAL_LIBRARY)) {
			ReadOBJMaterialLibrary();
		}
		else if (str_equals(token, MAGE_OBJ_TOKEN_MATERIAL_USE)) {
			ReadOBJMaterialUse();
		}
		else if (str_equals(token, MAGE_OBJ_TOKEN_GROUP)) {
			ReadOBJGroup();
		}
		else if (str_equals(token, MAGE_OBJ_TOKEN_OBJECT)) {
			ReadOBJObject();
		}
		else if (str_equals(token, MAGE_OBJ_TOKEN_SMOOTHING_GROUP)) {
			ReadOBJSmoothingGroup();
		}
		else {
			Warning("%ls: line %u: unsupported keyword token: %s.", GetFilename().c_str(), GetCurrentLineNumber(), token);
			return;
		}

		ReadLineRemaining();
	}

	template < typename VertexT >
	void OBJReader< VertexT >::ReadOBJMaterialLibrary() {
		const wstring mtl_path = mage::GetPathName(GetFilename());
		const wstring mtl_name = str_convert(ReadString());
		const wstring mtl_fname = mage::GetFilename(mtl_path, mtl_name);

		ImportMaterialFromFile(mtl_fname, m_model_output.m_material_buffer);
	}

	template < typename VertexT >
	void OBJReader< VertexT >::ReadOBJMaterialUse() {
		const string mtl_name = ReadString();
		m_model_output.SetMaterial(mtl_name);
	}

	template < typename VertexT >
	void OBJReader< VertexT >::ReadOBJGroup() {
		const string child = ReadString();
		if (child == MAGE_MDL_PART_DEFAULT_CHILD) {
			if (!m_model_output.m_index_buffer.empty()) {
				throw FormattedException("%ls: line %u: default child name can only be explicitly defined before all face definitions.", GetFilename().c_str(), GetCurrentLineNumber());
			}
			return;
		}
		if (m_model_output.HasModelPart(child)) {
			throw FormattedException("%ls: line %u: child name redefinition: %s.", GetFilename().c_str(), GetCurrentLineNumber(), child.c_str());
		}
		
		const string parent = HasString() ? ReadString() : MAGE_MDL_PART_DEFAULT_PARENT;
		
		m_model_output.EndModelPart();
		m_model_output.StartModelPart(child, parent);
	}

	template < typename VertexT >
	void OBJReader< VertexT >::ReadOBJObject() {
		ReadString();
	}

	template < typename VertexT >
	void OBJReader< VertexT >::ReadOBJSmoothingGroup() {
		// Silently ignore smoothing group declarations
		ReadString();
	}

	template < typename VertexT >
	void OBJReader< VertexT >::ReadOBJVertex() {
		const Point3 vertex = m_mesh_desc.InvertHandness() ?
			InvertHandness(ReadOBJVertexCoordinates()) :
			ReadOBJVertexCoordinates();

		m_vertex_coordinates.push_back(vertex);
	}

	template < typename VertexT >
	void OBJReader< VertexT >::ReadOBJVertexTexture() {
		const UV texture = m_mesh_desc.InvertHandness() ?
			InvertHandness(ReadOBJVertexTextureCoordinates()) :
			ReadOBJVertexTextureCoordinates();

		m_vertex_texture_coordinates.push_back(texture);
	}

	template < typename VertexT >
	void OBJReader< VertexT >::ReadOBJVertexNormal() {
		const Normal3 normal = m_mesh_desc.InvertHandness() ?
			InvertHandness(ReadOBJVertexNormalCoordinates()) :
			ReadOBJVertexNormalCoordinates();
		const XMVECTOR v = XMLoadFloat3(&normal);
		const XMVECTOR normal_v = XMVector3Normalize(v);
		XMLoadFloat3(&normal);

		m_vertex_normal_coordinates.push_back(normal);
	}

	template < typename VertexT >
	void OBJReader< VertexT >::ReadOBJFace() {
		vector< uint32_t > indices;
		while (indices.size() < 3 || HasString()) {
			const XMUINT3 vertex_indices = ReadOBJVertexIndices();

			const auto it = m_mapping.find(vertex_indices);
			if (it != m_mapping.cend()) {
				indices.push_back(it->second);
			}
			else {
				const uint32_t index = static_cast< uint32_t >(m_model_output.m_vertex_buffer.size());
				indices.push_back(index);
				m_model_output.m_vertex_buffer.push_back(ConstructVertex(vertex_indices));
				m_mapping[vertex_indices] = index;
			}
		}

		if (m_mesh_desc.ClockwiseOrder()) {
			for (size_t i = 1; i < indices.size() - 1; ++i) {
				m_model_output.m_index_buffer.push_back(indices[0]);
				m_model_output.m_index_buffer.push_back(indices[i + 1]);
				m_model_output.m_index_buffer.push_back(indices[i]);
			}
		}
		else {
			for (size_t i = 1; i < indices.size() - 1; ++i) {
				m_model_output.m_index_buffer.push_back(indices[0]);
				m_model_output.m_index_buffer.push_back(indices[i]);
				m_model_output.m_index_buffer.push_back(indices[i + 1]);
			}
		}
	}

	template < typename VertexT >
	inline const Point3 OBJReader< VertexT >::ReadOBJVertexCoordinates() {
		return static_cast< Point3 >(ReadFloat3());
	}

	template < typename VertexT >
	inline const Normal3 OBJReader< VertexT >::ReadOBJVertexNormalCoordinates() {
		return static_cast< Normal3 >(ReadFloat3());
	}

	template < typename VertexT >
	inline const UV OBJReader< VertexT >::ReadOBJVertexTextureCoordinates() {
		const UV result = static_cast< UV >(ReadFloat2());
		
		if (HasFloat()) {
			// Silently ignore 3D vertex texture coordinates.
			ReadFloat();
		}

		return result;
	}

	template < typename VertexT >
	const XMUINT3 OBJReader< VertexT >::ReadOBJVertexIndices() {
		const char *token = ReadChars();

		uint32_t vertex_index = 0;
		uint32_t texture_index = 0;
		uint32_t normal_index = 0;

		if (str_contains(token, "//")) {
			// v1//vn1
			const char *index_end = strchr(token, '/');
			if (StringToUInt32(token, index_end, vertex_index) == TokenResult_Invalid) {
				throw FormattedException("%ls: line %u: invalid vertex index value found in %s.", GetFilename().c_str(), GetCurrentLineNumber(), token);
			}
			if (StringToUInt32(index_end + 2, normal_index) == TokenResult_Invalid) {
				throw FormattedException("%ls: line %u: invalid normal index value found in %s.", GetFilename().c_str(), GetCurrentLineNumber(), token);
			}
		}
		else if (str_contains(token, '/')) {
			// v1/vt1 or v1/vt1/vn1
			const char *index_end = strchr(token, '/');
			if (StringToUInt32(token, index_end, vertex_index) == TokenResult_Invalid) {
				throw FormattedException("%ls: line %u: invalid vertex index value found in %s.", GetFilename().c_str(), GetCurrentLineNumber(), token);
			}
			
			if (str_contains(index_end + 1, '/')) {
				const char *texture_end = strchr(index_end + 1, '/');
				if (StringToUInt32(index_end + 1, texture_end, texture_index) == TokenResult_Invalid) {
					throw FormattedException("%ls: line %u: invalid texture index value found in %s.", GetFilename().c_str(), GetCurrentLineNumber(), token);
				}
				if (StringToUInt32(texture_end + 1, normal_index) == TokenResult_Invalid) {
					throw FormattedException("%ls: line %u: invalid normal index value found in %s.", GetFilename().c_str(), GetCurrentLineNumber(), token);
				}
			}
			else if (StringToUInt32(index_end + 1, texture_index) == TokenResult_Invalid) {
				throw FormattedException("%ls: line %u: invalid texture index value found in %s.", GetFilename().c_str(), GetCurrentLineNumber(), token);
			}
		}
		else if (StringToUInt32(token, vertex_index) == TokenResult_Invalid) {
			throw FormattedException("%ls: line %u: invalid vertex index value found in %s.", GetFilename().c_str(), GetCurrentLineNumber(), token);
		}

		return XMUINT3(vertex_index, texture_index, normal_index);
	}

	template < typename VertexT >
	const VertexT OBJReader< VertexT >::ConstructVertex(const XMUINT3 &vertex_indices) {
		VertexT vertex;
		if (vertex_indices.x) {
			vertex.p = m_vertex_coordinates[vertex_indices.x - 1];
		}
		if (vertex_indices.y) {
			vertex.tex = m_vertex_texture_coordinates[vertex_indices.y - 1];
		}
		if (vertex_indices.z) {
			vertex.n = m_vertex_normal_coordinates[vertex_indices.z - 1];
		}
		return vertex;
	}

	template <>
	inline const VertexPosition OBJReader< VertexPosition >::ConstructVertex(const XMUINT3 &vertex_indices) {
		VertexPosition vertex;
		if (vertex_indices.x) {
			vertex.p = m_vertex_coordinates[vertex_indices.x - 1];
		}
		return vertex;
	}

	template <>
	inline const VertexPositionNormal OBJReader< VertexPositionNormal >::ConstructVertex(const XMUINT3 &vertex_indices) {
		VertexPositionNormal vertex;
		if (vertex_indices.x) {
			vertex.p = m_vertex_coordinates[vertex_indices.x - 1];
		}
		if (vertex_indices.z) {
			vertex.n = m_vertex_normal_coordinates[vertex_indices.z - 1];
		}
		return vertex;
	}

	template <>
	inline const VertexPositionTexture OBJReader< VertexPositionTexture >::ConstructVertex(const XMUINT3 &vertex_indices) {
		VertexPositionTexture vertex;
		if (vertex_indices.x) {
			vertex.p = m_vertex_coordinates[vertex_indices.x - 1];
		}
		if (vertex_indices.y) {
			vertex.tex = m_vertex_texture_coordinates[vertex_indices.y - 1];
		}
		return vertex;
	}
}