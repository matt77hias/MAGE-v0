#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "logging\error.hpp"
#include "file\file_utils.hpp"
#include "material\mtl_loader.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Defines
//-----------------------------------------------------------------------------
#pragma region

#define MAGE_OBJ_DELIMITER " \t\n\r"
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

	/**
	 A struct of @c XMUINT3 comparators for OBJ vertex indices.
	 */
	struct OBJComparatorXMUINT3 {

	public:

		/**
		 Compares the two given @c XMUINT3 vectors against each other.

		 @param[in]		a
						A reference to the first vector.
		 @param[in]		b
						A reference to the second vector.
		 @return		@c true if the @a a is smaller than @a b.
						@c false otherwise.
		 */
		bool operator()(const XMUINT3& a, const XMUINT3& b) const {
			return (a.x == b.x) ? ((a.y == b.y) ? (a.z < b.z) : (a.y < b.y)) : (a.x < b.x);
		}
	};

	struct OBJBuffer {

	public:

		vector< Point3 >  vertex_coordinates;
		vector< UV >      vertex_texture_coordinates;
		vector< Normal3 > vertex_normal_coordinates;
		map< XMUINT3, uint32_t, OBJComparatorXMUINT3 > mapping;
	};

	string ParseOBJString(uint32_t line_number, char **context, char *str = nullptr);
	XMUINT3 ParseOBJVertexIndices(uint32_t line_number, char **context, char *str = nullptr);

	void ParseOBJVertex(uint32_t line_number, char **context, OBJBuffer &buffer, const MeshDescriptor &mesh_desc);
	void ParseOBJVertexTexture(uint32_t line_number, char **context, OBJBuffer &buffer, const MeshDescriptor &mesh_desc);
	void ParseOBJVertexNormal(uint32_t line_number, char **context, OBJBuffer &buffer, const MeshDescriptor &mesh_desc);

	template < typename Vertex >
	inline Vertex ConstructVertex(const XMUINT3 &vertex_indices, OBJBuffer &buffer) {
		Vertex vertex;
		if (vertex_indices.x) {
			vertex.p = buffer.vertex_coordinates[vertex_indices.x - 1];
		}
		if (vertex_indices.y) {
			vertex.tex = buffer.vertex_texture_coordinates[vertex_indices.y - 1];
		}
		if (vertex_indices.z) {
			vertex.n = buffer.vertex_normal_coordinates[vertex_indices.z - 1];
		}
		return vertex;
	}

	template <>
	inline VertexPosition ConstructVertex< VertexPosition >(const XMUINT3 &vertex_indices, OBJBuffer &buffer) {
		VertexPosition vertex;
		if (vertex_indices.x) {
			vertex.p = buffer.vertex_coordinates[vertex_indices.x - 1];
		}
		return vertex;
	}

	template <>
	inline VertexPositionNormal ConstructVertex< VertexPositionNormal >(const XMUINT3 &vertex_indices, OBJBuffer &buffer) {
		VertexPositionNormal vertex;
		if (vertex_indices.x) {
			vertex.p = buffer.vertex_coordinates[vertex_indices.x - 1];
		}
		if (vertex_indices.z) {
			vertex.n = buffer.vertex_normal_coordinates[vertex_indices.z - 1];
		}
		return vertex;
	}

	template <>
	inline VertexPositionTexture ConstructVertex< VertexPositionTexture >(const XMUINT3 &vertex_indices, OBJBuffer &buffer) {
		VertexPositionTexture vertex;
		if (vertex_indices.x) {
			vertex.p = buffer.vertex_coordinates[vertex_indices.x - 1];
		}
		if (vertex_indices.y) {
			vertex.tex = buffer.vertex_texture_coordinates[vertex_indices.y - 1];
		}
		return vertex;
	}

	template < typename Vertex >
	static void ParseOBJTriangleFace(uint32_t line_number, char **context, OBJBuffer &buffer,
		ModelOutput< Vertex > &model_output, const MeshDescriptor &mesh_desc) {

		uint32_t indices[3];
		for (size_t i = 0; i < 3; ++i) {
			const XMUINT3 vertex_indices = ParseOBJVertexIndices(line_number, context);
			const map< XMUINT3, uint32_t >::const_iterator it = buffer.mapping.find(vertex_indices);
			if (it != buffer.mapping.cend()) {
				indices[i] = it->second;
			}
			else {
				const uint32_t index = (uint32_t)model_output.vertex_buffer.size();
				indices[i] = index;
				model_output.vertex_buffer.push_back(ConstructVertex< Vertex >(vertex_indices, buffer));
				buffer.mapping[vertex_indices] = index;
			}
		}

		if (mesh_desc.ClockwiseOrder()) {
			model_output.index_buffer.push_back(indices[2]);
			model_output.index_buffer.push_back(indices[1]);
			model_output.index_buffer.push_back(indices[0]);
		}
		else {
			model_output.index_buffer.push_back(indices[0]);
			model_output.index_buffer.push_back(indices[1]);
			model_output.index_buffer.push_back(indices[2]);
		}
	}

	template < typename Vertex >
	void ParseOBJMaterialLibrary(const string &fname, uint32_t line_number, char **context, ModelOutput< Vertex > &model_output) {
		const string mtl_path = GetPathName(fname);
		const string mtl_name = ParseOBJString(line_number, context);
		const string mtl_fname = GetFilename(mtl_path, mtl_name);

		const HRESULT result = LoadMTLMaterialFromFile(mtl_fname, model_output.material_buffer);
		if (FAILED(result)) {
			Error("Could not import .mtl file: %s.", fname.c_str());
		}
	}

	template < typename Vertex >
	void ParseOBJMaterialUse(uint32_t line_number, char **context, ModelOutput< Vertex > &model_output) {
		const string mtl_name = ParseOBJString(line_number, context);
		model_output.SetMaterial(mtl_name);
	}

	template < typename Vertex >
	void ParseOBJGroup(uint32_t line_number, char **context, ModelOutput< Vertex > &model_output) {
		const string child = ParseOBJString(line_number, context);

		const char *token = strtok_s(nullptr, MAGE_OBJ_DELIMITER, context);
		if (!token) {
			model_output.StartModelPart(child);
			return;
		}
		
		const string parent = string(token);
		model_output.StartModelPart(child, parent);
	}

	template < typename Vertex >
	static void ParseOBJLine(const string &fname, char *line, uint32_t line_number, 
		OBJBuffer &buffer, ModelOutput< Vertex > &model_output, const MeshDescriptor &mesh_desc) {

		char *context = nullptr;
		const char *token = strtok_s(line, MAGE_OBJ_DELIMITER, &context);

		if (!token || token[0] == MAGE_OBJ_COMMENT_CHAR) {
			return;
		}

		if (str_equals(token, MAGE_OBJ_MATERIAL_LIBRARY_TOKEN)) {
			ParseOBJMaterialLibrary(fname, line_number, &context, model_output);
		}
		else if (str_equals(token, MAGE_OBJ_MATERIAL_USE_TOKEN)) {
			ParseOBJMaterialUse(line_number, &context, model_output);
		}
		else if (str_equals(token, MAGE_OBJ_GROUP_TOKEN)) {
			// End current group.
			model_output.EndModelPart();
			// Begin current group.
			ParseOBJGroup(line_number, &context, model_output);
		}
		else if (str_equals(token, MAGE_OBJ_VERTEX_TOKEN)) {
			ParseOBJVertex(line_number, &context, buffer, mesh_desc);
		}
		else if (str_equals(token, MAGE_OBJ_TEXTURE_TOKEN)) {
			ParseOBJVertexTexture(line_number, &context, buffer, mesh_desc);
		}
		else if (str_equals(token, MAGE_OBJ_NORMAL_TOKEN)) {
			ParseOBJVertexNormal(line_number, &context, buffer, mesh_desc);
		}
		else if (str_equals(token, MAGE_OBJ_FACE_TOKEN)) {
			ParseOBJTriangleFace< Vertex >(line_number, &context, buffer, model_output, mesh_desc);
		}
		else {
			Warning("Unsupported keyword in OBJ specification at line %u: %s.", line_number, token);
		}

		char *next_token = strtok_s(nullptr, MAGE_OBJ_DELIMITER, &context);
		while (next_token) {
			Warning("Unused token in OBJ specification at line %u: %s.", line_number, next_token);
			next_token = strtok_s(nullptr, MAGE_OBJ_DELIMITER, &context);
		}
	}

	template < typename Vertex >
	HRESULT LoadOBJMeshFromFile(const string &fname, ModelOutput< Vertex > &model_output, const MeshDescriptor &mesh_desc) {

		if (!model_output.vertex_buffer.empty()) {
			Error("Could not import .obj file: %s due to non-empty vertex buffer.", fname.c_str());
			return E_FAIL;
		}
		if (!model_output.index_buffer.empty()) {
			Error("Could not import .obj file: %s due to non-empty index buffer.", fname.c_str());
			return E_FAIL;
		}

		// Open the .obj file.
		FILE *file = nullptr;
		const errno_t result_fopen_s = fopen_s(&file, fname.c_str(), "r");
		if (result_fopen_s) {
			Error("Could not import .obj file: %s.", fname.c_str());
			return E_FAIL;
		}

		// Buffer
		OBJBuffer buffer;

		// Begin current group.
		model_output.StartModelPart();

		// Parse the .obj file while populating the buffers.
		char current_line[MAX_PATH];
		uint32_t line_number = 1;
		// Continue reading from the file until the eof is reached.
		while (fgets(current_line, _countof(current_line), file)) {

			ParseOBJLine< Vertex >(fname, current_line, line_number, buffer, model_output, mesh_desc);

			++line_number;
		}

		// End current group.
		model_output.EndModelPart();

		// Close the script file.
		fclose(file);

		return S_OK;
	}
}