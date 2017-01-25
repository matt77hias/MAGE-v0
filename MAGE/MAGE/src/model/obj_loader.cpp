//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "engine.hpp"

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

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	static XMFLOAT2 ParseOBJFloat2(const char *token) {
		char *end = nullptr;
		const float vector3_x = strtof(token, &end);
		const float vector3_y = strtof(end, nullptr);
		return XMFLOAT2(vector3_x, vector3_y);
	}

	static XMFLOAT3 ParseOBJFloat3(const char *token) {
		char *end1 = nullptr;
		char *end2 = nullptr;
		const float vector3_x = strtof(token, &end1);
		const float vector3_y = strtof(end1, &end2);
		const float vector3_z = strtof(end2, nullptr);
		return XMFLOAT3(vector3_x, vector3_y, vector3_z);
	}

	static XMFLOAT3 ParseOBJVertexCoordinates(const char *token) {
		return ParseOBJFloat3(token);
	}

	static XMFLOAT3 ParseOBJVertexNormalCoordinates(const char *token) {
		const XMFLOAT3 vector3 = ParseOBJFloat3(token);
		const XMVECTOR vector3_v = XMLoadFloat3(&vector3);
		const XMVECTOR normal3_v = XMVector3Normalize(vector3_v);
		XMFLOAT3 normal3;
		XMLoadFloat3(&normal3);
		return normal3;
	}

	static XMFLOAT2 ParseOBJVertexTextureCoordinates(const char *token) {
		return ParseOBJFloat2(token);
	}

	static XMUINT3 ParseOBJVertexIndices(const char *token) {
		const uint32_t vertex_index = atoi(token);
		uint32_t texture_index = 0;
		uint32_t normal_index = 0;

		if (str_contains(token, "//")) {
			//... v1//vn1 ...
			const char *normal_part = strchr(token, '/') + 2;
			normal_index = atoi(normal_part);
		}
		else if (str_contains(token, "/")) {
			//... v1/vt1 ...
			const char *texture_part = strchr(token, '/') + 1;
			texture_index = atoi(strchr(token, '/') + 1);
			if (str_contains(texture_part, "/")) {
				//... v1/vt1/vn1 ...
				const char *normal_part = strchr(texture_part, '/') + 1;
				normal_index = atoi(normal_part);
			}
		}
		return XMUINT3(vertex_index, texture_index, normal_index);
	}

	void LoadOBJModelFromFile(const string &fname, 
		vector< Vertex > &vertex_buffer, vector< uint32_t > &index_buffer) {

		// Open the .obj file.
		FILE *file = nullptr;
		const errno_t result_fopen_s = fopen_s(&file, fname.c_str(), "r");
		if (result_fopen_s) {
			Warning("Could not import .obj file: %s", fname.c_str());
			return;
		}

		// Buffers
		vector< XMFLOAT3 > vertex_coordinates;
		vector< XMFLOAT2 > vertex_texture_coordinates;
		vector< XMFLOAT3 > vertex_normal_coordinates;
		map< XMUINT3, uint32_t > mapping;
		
		// Parse the .obj file while populating the buffers.
		char *current_token = nullptr;
		char *next_token = nullptr;
		char current_line[MAX_PATH];
		uint32_t line_number = 0;
		// Continue reading from the file until the eof is reached.
		while (fgets(current_line, _countof(current_line), file)) {
			current_token = strtok_s(current_line, MAGE_OBJ_DELIMITER, &next_token);

			if (!current_token || current_token[0] == MAGE_OBJ_COMMENT_CHAR) {
				continue;
			}

			if (str_equals(current_token, MAGE_OBJ_VERTEX_TOKEN)) {
				current_token = strtok_s(nullptr, MAGE_OBJ_DELIMITER, &next_token);
				const XMFLOAT3 vertex = ParseOBJVertexCoordinates(current_token);
				vertex_coordinates.push_back(vertex);
			}
			else if (str_equals(current_token, MAGE_OBJ_TEXTURE_TOKEN)) {
				current_token = strtok_s(nullptr, MAGE_OBJ_DELIMITER, &next_token);
				const XMFLOAT2 texture = ParseOBJVertexTextureCoordinates(current_token);
				vertex_texture_coordinates.push_back(texture);
			}
			if (str_equals(current_token, MAGE_OBJ_NORMAL_TOKEN)) {
				current_token = strtok_s(nullptr, MAGE_OBJ_DELIMITER, &next_token);
				const XMFLOAT3 normal = ParseOBJVertexNormalCoordinates(current_token);
				vertex_normal_coordinates.push_back(normal);
			}
			else if (str_equals(current_token, MAGE_OBJ_FACE_TOKEN)) {
				for (size_t i = 0; i < 3; ++i) {
					current_token = strtok_s(nullptr, MAGE_OBJ_DELIMITER, &next_token);
					const XMUINT3 vertex_indices = ParseOBJVertexIndices(current_token);
					const map< XMUINT3, uint32_t >::const_iterator it = mapping.find(vertex_indices);
					if (it != mapping.end()) {
						index_buffer.push_back(it->second);
					}
					else {
						const uint32_t index = vertex_buffer.size();
						index_buffer.push_back(index);
						Vertex vertex;
						vertex.p   = vertex_coordinates[vertex_indices.x - 1];
						vertex.tex = (vertex_indices.y) ? vertex_texture_coordinates[vertex_indices.y - 1] : XMFLOAT2(0.0f, 0.0f);
						vertex.n   = (vertex_indices.z) ? vertex_normal_coordinates[ vertex_indices.z - 1] : XMFLOAT3(0.0f, 0.0f, 0.0f);
						vertex_buffer.push_back(vertex);
						mapping[vertex_indices] = index;
					}
				}
			}
			else {
				Warning("Unknown command '%s' in scene code at line %u: \"%s\".", current_token, line_number, current_line);
			}

			++line_number;
		}

		// Close the script file.
		fclose(file);
	}
}