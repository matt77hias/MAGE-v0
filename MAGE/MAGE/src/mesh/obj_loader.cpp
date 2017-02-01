//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "mesh\obj_loader.hpp"
#include "logging\error.hpp"
#include "string\string_utils.hpp"

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

	static XMFLOAT2 ParseOBJFloat2(char **context, char *str = nullptr) {
		const char *token_x   = strtok_s(str, MAGE_OBJ_DELIMITER, context);
		const float vector3_x = strtof(token_x, nullptr);
		const char *token_y   = strtok_s(nullptr, MAGE_OBJ_DELIMITER, context);
		const float vector3_y = strtof(token_y, nullptr);
		return XMFLOAT2(vector3_x, vector3_y);
	}

	static XMFLOAT3 ParseOBJFloat3(char **context, char *str = nullptr) {
		const char *token_x   = strtok_s(str, MAGE_OBJ_DELIMITER, context);
		const float vector3_x = strtof(token_x, nullptr);
		const char *token_y   = strtok_s(nullptr, MAGE_OBJ_DELIMITER, context);
		const float vector3_y = strtof(token_y, nullptr);
		const char *token_z   = strtok_s(nullptr, MAGE_OBJ_DELIMITER, context);
		const float vector3_z = strtof(token_z, nullptr);
		return XMFLOAT3(vector3_x, vector3_y, vector3_z);
	}

	static Point3 ParseOBJVertexCoordinates(char **context, char *str = nullptr) {
		return (Point3)ParseOBJFloat3(context, str);
	}

	static Normal3 ParseOBJVertexNormalCoordinates(char **context, char *str = nullptr) {
		const XMFLOAT3 vector3   = ParseOBJFloat3(context, str);
		const XMVECTOR vector3_v = XMLoadFloat3(&vector3);
		const XMVECTOR normal3_v = XMVector3Normalize(vector3_v);
		XMFLOAT3 normal3;
		XMLoadFloat3(&normal3);
		return (Normal3)normal3;
	}

	static XMFLOAT2 ParseOBJVertexTextureCoordinates(char **context, char *str = nullptr) {
		return ParseOBJFloat2(context, str);
	}

	static XMUINT3 ParseOBJVertexIndices(char **context, char *str = nullptr) {
		const char *token = strtok_s(str, MAGE_OBJ_DELIMITER, context);
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

	static HRESULT ParseOBJVertex(char **context,
		vector< Point3 > &vertex_coordinates) {
		const Point3 vertex = ParseOBJVertexCoordinates(context);
		vertex_coordinates.push_back(vertex);
		return S_OK;
	}

	static HRESULT ParseOBJVertexTexture(char **context,
		vector< XMFLOAT2 > &vertex_texture_coordinates) {
		const XMFLOAT2 texture = ParseOBJVertexTextureCoordinates(context);
		vertex_texture_coordinates.push_back(texture);
		return S_OK;
	}
	
	static HRESULT ParseOBJVertexNormal(char **context,
		vector< Normal3 > &vertex_normal_coordinates) {
		const Normal3 normal = ParseOBJVertexNormalCoordinates(context);
		vertex_normal_coordinates.push_back(normal);
		return S_OK;
	}

	//-------------------------------------------------------------------------
	// Vertex buffer + Index buffer
	//-------------------------------------------------------------------------

	static HRESULT ParseOBJTriangleFace(char **context,
		vector< Point3 > &vertex_coordinates,
		vector< XMFLOAT2 > &vertex_texture_coordinates,
		vector< Normal3 > &vertex_normal_coordinates,
		map< XMUINT3, uint32_t, OBJComparatorXMUINT3 > &mapping,
		vector< Vertex > &vertex_buffer, vector< uint32_t > &index_buffer) {
		
		// OBJ uses a counter-clockwise vertex order in a RHS world coordinate system
		// = D3D uses a clockwise vertex order in a LHS world coordinate system
		for (size_t i = 0; i < 3; ++i) {
			const XMUINT3 vertex_indices = ParseOBJVertexIndices(context);
			const map< XMUINT3, uint32_t >::const_iterator it = mapping.find(vertex_indices);
			if (it != mapping.end()) {
				index_buffer.push_back(it->second);
			}
			else {
				const uint32_t index = (uint32_t)vertex_buffer.size();
				index_buffer.push_back(index);
				Vertex vertex;
				vertex.p   = vertex_coordinates[vertex_indices.x - 1];
				vertex.tex = (vertex_indices.y) ? vertex_texture_coordinates[vertex_indices.y - 1] : XMFLOAT2(0.0f, 0.0f);
				vertex.n   = (vertex_indices.z) ? vertex_normal_coordinates[vertex_indices.z - 1] : Normal3(0.0f, 0.0f, 0.0f);
				vertex_buffer.push_back(vertex);
				mapping[vertex_indices] = index;
			}
		}

		return S_OK;
	}

	static HRESULT ParseOBJLine(char *line, uint32_t line_number,
		vector< Point3 > &vertex_coordinates,
		vector< XMFLOAT2 > &vertex_texture_coordinates,
		vector< Normal3 > &vertex_normal_coordinates,
		map< XMUINT3, uint32_t, OBJComparatorXMUINT3 > &mapping,
		vector< Vertex > &vertex_buffer, vector< uint32_t > &index_buffer) {

		char *context = nullptr;
		const char *token = strtok_s(line, MAGE_OBJ_DELIMITER, &context);
		
		if (!token || token[0] == MAGE_OBJ_COMMENT_CHAR) {
			return S_OK;;
		}

		if (str_equals(token, MAGE_OBJ_VERTEX_TOKEN)) {
			return ParseOBJVertex(&context, vertex_coordinates);
		}
		else if (str_equals(token, MAGE_OBJ_TEXTURE_TOKEN)) {
			return ParseOBJVertexTexture(&context, vertex_texture_coordinates);
		}
		if (str_equals(token, MAGE_OBJ_NORMAL_TOKEN)) {
			return ParseOBJVertexNormal(&context, vertex_normal_coordinates);
		}
		else if (str_equals(token, MAGE_OBJ_FACE_TOKEN)) {
			return ParseOBJTriangleFace(&context, vertex_coordinates, vertex_texture_coordinates, vertex_normal_coordinates,
				mapping, vertex_buffer, index_buffer);
		}
		else {
			Warning("Unknown command '%s' in scene code at line %u: \"%s\".", token, line_number, line);
			return E_FAIL;
		}
	}

	HRESULT LoadOBJMeshFromFile(const wstring &fname,
		vector< Vertex > &vertex_buffer, vector< uint32_t > &index_buffer) {

		if (!vertex_buffer.empty()) {
			Error("Could not import .obj file: %ls due to non-empty vertex buffer", fname.c_str());
			return E_FAIL;
		}
		if (!index_buffer.empty()) {
			Error("Could not import .obj file: %ls due to non-empty index buffer", fname.c_str());
			return E_FAIL;
		}

		// Open the .obj file.
		FILE *file = nullptr;
		const errno_t result_fopen_s = _wfopen_s(&file, fname.c_str(), L"r");
		if (result_fopen_s) {
			Error("Could not import .obj file: %ls", fname.c_str());
			return E_FAIL;
		}

		// Buffers
		vector< Point3 > vertex_coordinates;
		vector< XMFLOAT2 > vertex_texture_coordinates;
		vector< Normal3 > vertex_normal_coordinates;
		map< XMUINT3, uint32_t, OBJComparatorXMUINT3 > mapping;
		
		// Parse the .obj file while populating the buffers.
		char current_line[MAX_PATH];
		uint32_t line_number = 0;
		// Continue reading from the file until the eof is reached.
		while (fgets(current_line, _countof(current_line), file)) {
			
			ParseOBJLine(current_line, line_number,
				vertex_coordinates, vertex_texture_coordinates, vertex_normal_coordinates,
				mapping, vertex_buffer, index_buffer);

			++line_number;
		}

		// Close the script file.
		fclose(file);

		return S_OK;
	}

	HRESULT LoadOBJMeshFromMemory(const char *input,
		vector< Vertex > &vertex_buffer, vector< uint32_t > &index_buffer) {

		if (!vertex_buffer.empty()) {
			Error("Could not import .obj string due to non-empty vertex buffer");
			return E_FAIL;
		}
		if (!index_buffer.empty()) {
			Error("Could not import .obj string due to non-empty index buffer");
			return E_FAIL;
		}

		// Buffers
		vector< Point3 > vertex_coordinates;
		vector< XMFLOAT2 > vertex_texture_coordinates;
		vector< Normal3 > vertex_normal_coordinates;
		map< XMUINT3, uint32_t, OBJComparatorXMUINT3 > mapping;

		// Parse the .obj string while populating the buffers.
		char current_line[MAX_PATH];
		uint32_t line_number = 0;
		// Continue reading from the file until the eof is reached.
		while (str_gets(current_line, _countof(current_line), &input)) {
			ParseOBJLine(current_line, line_number,
				vertex_coordinates, vertex_texture_coordinates, vertex_normal_coordinates,
				mapping, vertex_buffer, index_buffer);

			++line_number;
		}

		return S_OK;
	}

	//-------------------------------------------------------------------------
	// Vertex buffer
	//-------------------------------------------------------------------------

	static HRESULT ParseOBJTriangleFace(char **context,
		vector< Point3 > &vertex_coordinates,
		vector< XMFLOAT2 > &vertex_texture_coordinates,
		vector< Normal3 > &vertex_normal_coordinates,
		vector< Vertex > &vertex_buffer) {

		// OBJ uses a counter-clockwise vertex order in a RHS world coordinate system
		// = D3D uses a clockwise vertex order in a LHS world coordinate system
		for (size_t i = 0; i < 3; ++i) {
			const XMUINT3 vertex_indices = ParseOBJVertexIndices(context);
			
			Vertex vertex;
			vertex.p   = vertex_coordinates[vertex_indices.x - 1];
			vertex.tex = (vertex_indices.y) ? vertex_texture_coordinates[vertex_indices.y - 1] : XMFLOAT2(0.0f, 0.0f);
			vertex.n   = (vertex_indices.z) ? vertex_normal_coordinates[vertex_indices.z - 1] : Normal3(0.0f, 0.0f, 0.0f);
			vertex_buffer.push_back(vertex);
		}

		return S_OK;
	}

	static HRESULT ParseOBJLine(char *line, uint32_t line_number,
		vector< Point3 > &vertex_coordinates,
		vector< XMFLOAT2 > &vertex_texture_coordinates,
		vector< Normal3 > &vertex_normal_coordinates,
		vector< Vertex > &vertex_buffer) {

		char *context = nullptr;
		const char *token = strtok_s(line, MAGE_OBJ_DELIMITER, &context);

		if (!token || token[0] == MAGE_OBJ_COMMENT_CHAR) {
			return S_OK;
		}

		if (str_equals(token, MAGE_OBJ_VERTEX_TOKEN)) {
			return ParseOBJVertex(&context, vertex_coordinates);
		}
		else if (str_equals(token, MAGE_OBJ_TEXTURE_TOKEN)) {
			return ParseOBJVertexTexture(&context, vertex_texture_coordinates);
		}
		if (str_equals(token, MAGE_OBJ_NORMAL_TOKEN)) {
			return ParseOBJVertexNormal(&context, vertex_normal_coordinates);
		}
		else if (str_equals(token, MAGE_OBJ_FACE_TOKEN)) {
			return ParseOBJTriangleFace(&context, vertex_coordinates, vertex_texture_coordinates, vertex_normal_coordinates, vertex_buffer);
		}
		else {
			Warning("Unknown command '%s' in scene code at line %u: \"%s\".", token, line_number, line);
			return E_FAIL;
		}
	}

	HRESULT LoadOBJMeshFromFile(const wstring &fname,
		vector< Vertex > &vertex_buffer) {

		if (!vertex_buffer.empty()) {
			Error("Could not import .obj file: %ls due to non-empty vertex buffer", fname.c_str());
			return E_FAIL;
		}

		// Open the .obj file.
		FILE *file = nullptr;
		const errno_t result_fopen_s = _wfopen_s(&file, fname.c_str(), L"r");
		if (result_fopen_s) {
			Error("Could not import .obj file: %ls", fname.c_str());
			return E_FAIL;
		}

		// Buffers
		vector< Point3 > vertex_coordinates;
		vector< XMFLOAT2 > vertex_texture_coordinates;
		vector< Normal3 > vertex_normal_coordinates;

		// Parse the .obj file while populating the buffers.
		char current_line[MAX_PATH];
		uint32_t line_number = 0;
		// Continue reading from the file until the eof is reached.
		while (fgets(current_line, _countof(current_line), file)) {

			ParseOBJLine(current_line, line_number,
				vertex_coordinates, vertex_texture_coordinates, vertex_normal_coordinates, 
				vertex_buffer);

			++line_number;
		}

		// Close the script file.
		fclose(file);

		return S_OK;
	}

	HRESULT LoadOBJMeshFromMemory(const char *input,
		vector< Vertex > &vertex_buffer) {

		if (!vertex_buffer.empty()) {
			Error("Could not import .obj string due to non-empty vertex buffer");
			return E_FAIL;
		}

		// Buffers
		vector< Point3 > vertex_coordinates;
		vector< XMFLOAT2 > vertex_texture_coordinates;
		vector< Normal3 > vertex_normal_coordinates;

		// Parse the .obj string while populating the buffers.
		char current_line[MAX_PATH];
		uint32_t line_number = 0;
		// Continue reading from the file until the eof is reached.
		while (str_gets(current_line, _countof(current_line), &input)) {
			ParseOBJLine(current_line, line_number,
				vertex_coordinates, vertex_texture_coordinates, vertex_normal_coordinates,
				vertex_buffer);

			++line_number;
		}

		return S_OK;
	}
}