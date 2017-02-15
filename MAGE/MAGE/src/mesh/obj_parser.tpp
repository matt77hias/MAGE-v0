#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "logging\error.hpp"
#include "string\string_utils.hpp"
#include "file\file_utils.hpp"
#include "material\mtl_loader.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Defines
//-----------------------------------------------------------------------------
#pragma region

#define MAGE_OBJ_COMMENT_CHAR '#'
#define MAGE_OBJ_VERTEX_TOKEN "v"
#define MAGE_OBJ_TEXTURE_TOKEN "vt"
#define MAGE_OBJ_NORMAL_TOKEN "vn"
#define MAGE_OBJ_FACE_TOKEN "f"
#define MAGE_OBJ_MATERIAL_LIBRARY_TOKEN "mtllib"
#define MAGE_OBJ_MATERIAL_USE_TOKEN "usemtl"
#define MAGE_OBJ_GROUP_TOKEN "g"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	template < typename Vertex >
	HRESULT OBJParser< Vertex >::Preprocess() {
		if (!m_model_output.vertex_buffer.empty()) {
			Error("%ls: vertex buffer must be empty.", GetFilename().c_str());
			return E_FAIL;
		}
		if (!m_model_output.index_buffer.empty()) {
			Error("%ls: index buffer must be empty.", GetFilename().c_str());
			return E_FAIL;
		}

		// Begin current group.
		m_model_output.StartModelPart();

		return S_OK;
	}

	template < typename Vertex >
	HRESULT OBJParser< Vertex >::Postprocess() {
		// End current group.
		m_model_output.EndModelPart();

		return S_OK;
	}

	template < typename Vertex >
	HRESULT OBJParser< Vertex >::ParseLine(char *line) {
		m_context = nullptr;
		const char *token = strtok_s(line, GetDelimiters().c_str(), &m_context);

		if (!token || token[0] == MAGE_OBJ_COMMENT_CHAR) {
			return S_OK;
		}

		if (str_equals(token, MAGE_OBJ_MATERIAL_LIBRARY_TOKEN)) {
			ParseOBJMaterialLibrary();
		}
		else if (str_equals(token, MAGE_OBJ_MATERIAL_USE_TOKEN)) {
			ParseOBJMaterialUse();
		}
		else if (str_equals(token, MAGE_OBJ_GROUP_TOKEN)) {
			// End current group.
			m_model_output.EndModelPart();
			// Begin current group.
			ParseOBJGroup();
		}
		else if (str_equals(token, MAGE_OBJ_VERTEX_TOKEN)) {
			ParseOBJVertex();
		}
		else if (str_equals(token, MAGE_OBJ_TEXTURE_TOKEN)) {
			ParseOBJVertexTexture();
		}
		else if (str_equals(token, MAGE_OBJ_NORMAL_TOKEN)) {
			ParseOBJVertexNormal();
		}
		else if (str_equals(token, MAGE_OBJ_FACE_TOKEN)) {
			ParseOBJTriangleFace();
		}
		else {
			Warning("%ls: line %u: unsupported keyword token: %s.", GetFilename().c_str(), GetCurrentLineNumber(), token);
		}

		ParseLineRemaining();

		return S_OK;
	}

	template < typename Vertex >
	void OBJParser< Vertex >::ParseOBJMaterialLibrary() {
		const wstring mtl_path = GetPathName(GetFilename());
		const wstring mtl_name = str_convert(ParseString());
		const wstring mtl_fname = mage::GetFilename(mtl_path, mtl_name);

		const HRESULT result = LoadMTLMaterialFromFile(mtl_fname, m_model_output.material_buffer);
		if (FAILED(result)) {
			Error("%ls: line %u: %ls could not be loaded.", GetFilename().c_str(), GetCurrentLineNumber(), mtl_fname.c_str());
		}
	}

	template < typename Vertex >
	void OBJParser< Vertex >::ParseOBJMaterialUse() {
		const string mtl_name = ParseString();
		m_model_output.SetMaterial(mtl_name);
	}

	template < typename Vertex >
	void OBJParser< Vertex >::ParseOBJGroup() {
		const string child = ParseString();
		const string parent = ParseOptionalString("root");
		m_model_output.StartModelPart(child, parent);
	}

	template < typename Vertex >
	void OBJParser< Vertex >::ParseOBJVertex() {
		Point3 vertex = ParseOBJVertexCoordinates();
		if (m_mesh_desc.InvertHandness()) {
			vertex.z = -vertex.z;
		}

		m_buffer.vertex_coordinates.push_back(vertex);
	}

	template < typename Vertex >
	void OBJParser< Vertex >::ParseOBJVertexTexture() {
		UV texture = ParseOBJVertexTextureCoordinates();
		if (m_mesh_desc.InvertHandness()) {
			texture.y = 1.0f - texture.y;
		}

		m_buffer.vertex_texture_coordinates.push_back(texture);
	}

	template < typename Vertex >
	void OBJParser< Vertex >::ParseOBJVertexNormal() {
		Normal3 normal = ParseOBJVertexNormalCoordinates();
		if (m_mesh_desc.InvertHandness()) {
			normal.z = -normal.z;
		}
		const XMVECTOR v = XMLoadFloat3(&normal);
		const XMVECTOR normal_v = XMVector3Normalize(v);
		XMLoadFloat3(&normal);

		m_buffer.vertex_normal_coordinates.push_back(normal);
	}

	template < typename Vertex >
	void OBJParser< Vertex >::ParseOBJTriangleFace() {
		uint32_t indices[3];
		for (size_t i = 0; i < 3; ++i) {
			const XMUINT3 vertex_indices = ParseOBJVertexIndices();
			const map< XMUINT3, uint32_t >::const_iterator it = m_buffer.mapping.find(vertex_indices);
			if (it != m_buffer.mapping.cend()) {
				indices[i] = it->second;
			}
			else {
				const uint32_t index = (uint32_t)m_model_output.vertex_buffer.size();
				indices[i] = index;
				m_model_output.vertex_buffer.push_back(ConstructVertex(vertex_indices));
				m_buffer.mapping[vertex_indices] = index;
			}
		}

		if (m_mesh_desc.ClockwiseOrder()) {
			m_model_output.index_buffer.push_back(indices[2]);
			m_model_output.index_buffer.push_back(indices[1]);
			m_model_output.index_buffer.push_back(indices[0]);
		}
		else {
			m_model_output.index_buffer.push_back(indices[0]);
			m_model_output.index_buffer.push_back(indices[1]);
			m_model_output.index_buffer.push_back(indices[2]);
		}
	}

	template < typename Vertex >
	Point3 OBJParser< Vertex >::ParseOBJVertexCoordinates() {
		return (Point3)ParseFloat3();
	}

	template < typename Vertex >
	Normal3 OBJParser< Vertex >::ParseOBJVertexNormalCoordinates() {
		return (Normal3)ParseFloat3();
	}

	template < typename Vertex >
	UV OBJParser< Vertex >::ParseOBJVertexTextureCoordinates() {
		return (UV)ParseFloat2();
	}

	template < typename Vertex >
	XMUINT3 OBJParser< Vertex >::ParseOBJVertexIndices() {
		const char *token = strtok_s(nullptr, GetDelimiters().c_str(), &m_context);
		if (!token) {
			Error("%ls: line %u: no vertex index value found.", GetFilename().c_str(), GetCurrentLineNumber());
			return XMUINT3();
		}

		uint32_t vertex_index = 0;
		if (StringToUnsignedInt(token, vertex_index) == invalid_token) {
			Error("%ls: line %u: no integer index value found in %s.", GetFilename().c_str(), GetCurrentLineNumber(), token);
			return XMUINT3();
		}

		uint32_t texture_index = 0;
		uint32_t normal_index = 0;
		if (str_contains(token, "//")) {
			//... v1//vn1 ...
			const char *normal_part = strchr(token, '/') + 2;
			if (StringToUnsignedInt(normal_part, normal_index) == invalid_token) {
				Error("%ls: line %u: no normal index value found in %s.", GetFilename().c_str(), GetCurrentLineNumber(), normal_part);
				return XMUINT3(vertex_index, 0, 0);
			}
		}
		else if (str_contains(token, "/")) {
			//... v1/vt1 ...
			const char *texture_part = strchr(token, '/') + 1;
			if (StringToUnsignedInt(texture_part, texture_index) == invalid_token) {
				Error("%ls: line %u: no texture index value found in %s.", GetFilename().c_str(), GetCurrentLineNumber(), texture_part);
				return XMUINT3(vertex_index, 0, 0);
			}
			if (str_contains(texture_part, "/")) {
				//... v1/vt1/vn1 ...
				const char *normal_part = strchr(texture_part, '/') + 1;
				if (StringToUnsignedInt(normal_part, normal_index) == invalid_token) {
					Error("%ls: line %u: no normal index value found in %s.", GetFilename().c_str(), GetCurrentLineNumber(), normal_part);
					return XMUINT3(vertex_index, texture_index, 0);
				}
			}
		}

		return XMUINT3(vertex_index, texture_index, normal_index);
	}

	template < typename Vertex >
	Vertex OBJParser< Vertex >::ConstructVertex(const XMUINT3 &vertex_indices) {
		Vertex vertex;
		if (vertex_indices.x) {
			vertex.p = m_buffer.vertex_coordinates[vertex_indices.x - 1];
		}
		if (vertex_indices.y) {
			vertex.tex = m_buffer.vertex_texture_coordinates[vertex_indices.y - 1];
		}
		if (vertex_indices.z) {
			vertex.n = m_buffer.vertex_normal_coordinates[vertex_indices.z - 1];
		}
		return vertex;
	}

	template <>
	VertexPosition OBJParser< VertexPosition >::ConstructVertex(const XMUINT3 &vertex_indices) {
		VertexPosition vertex;
		if (vertex_indices.x) {
			vertex.p = m_buffer.vertex_coordinates[vertex_indices.x - 1];
		}
		return vertex;
	}

	template <>
	VertexPositionNormal OBJParser< VertexPositionNormal >::ConstructVertex(const XMUINT3 &vertex_indices) {
		VertexPositionNormal vertex;
		if (vertex_indices.x) {
			vertex.p = m_buffer.vertex_coordinates[vertex_indices.x - 1];
		}
		if (vertex_indices.z) {
			vertex.n = m_buffer.vertex_normal_coordinates[vertex_indices.z - 1];
		}
		return vertex;
	}

	template <>
	VertexPositionTexture OBJParser< VertexPositionTexture >::ConstructVertex(const XMUINT3 &vertex_indices) {
		VertexPositionTexture vertex;
		if (vertex_indices.x) {
			vertex.p = m_buffer.vertex_coordinates[vertex_indices.x - 1];
		}
		if (vertex_indices.y) {
			vertex.tex = m_buffer.vertex_texture_coordinates[vertex_indices.y - 1];
		}
		return vertex;
	}
}